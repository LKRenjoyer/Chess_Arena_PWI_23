import subprocess
import socket
from client_const import *
import sys
import os
from functools import partial
import argparse
import chess

parser = argparse.ArgumentParser(description='Główna program do runowania botów')
parser.add_argument('--name', nargs='?', default='gracz', type=str, help='Nazwa bota')
parser.add_argument("--player", action='store_true', help='Oznacza, że to będzie prawdziwy gracz')
parser.add_argument('--fen', type=str, nargs='?', default='base_start', help='Od jakiego fena gra ma sie zaczac')
parser.add_argument("--ngrok", type=str, nargs='?',default="localhost", help='Podaj ngroka')

args = parser.parse_args()

class Client:
    def __init__(self,ngrok):
        self.client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        if ngrok == "localhost":
            self.client.connect(ADDR)
        else:
            self.client.connect((ngrok.split(":")[0],ngrok.split(":")[1]))
    
    def send(self,msg):
        msg = msg.encode('utf-8')
        msg_len = len(msg)
        send_len = str(msg_len).encode('utf-8')
        send_len += b' ' * (64 - len(send_len))
        self.client.send(send_len)
        self.client.send(msg)
    
    def recv_msg(self):
        msg_len = self.client.recv(64).decode('utf-8')
        if msg_len:
            msg_len = int(msg_len)
            msg = self.client.recv(msg_len).decode("utf-8")
            return msg
        # else:
        #     return self.recv_msg()
        
                
c = Client(args.ngrok)
wiadomosc = c.recv_msg()
fen, kolor = wiadomosc.split("|")
# print(kolor,flush=True)
czy_bialy = True if kolor=="biale" else False

# with open("xd.txt","a") as f:
#     f.write(f"{fen} {kolor}\n")

board = chess.Board(fen)

# curr_path = os.path.abspath(sys.argv[0])
if args.player:
    # merge_path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))
    # path = merge_path(args.name, "main.py")
    path = "wizualizacja_gry/display.py"
    if czy_bialy:
        c.send("gracz bialy")
        bot = subprocess.Popen([sys.executable, path,"-w",f'--fen={args.fen}'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    else:
        c.send("gracz czarny")
        bot = subprocess.Popen([sys.executable,path,"-b",f'--fen={args.fen}'],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
else:
    merge_path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))
    if os.path.exists(merge_path(args.name, "main.py")):
        path = merge_path(args.name, "main.py")
        c.send(args.name)
        if czy_bialy:
            bot = subprocess.Popen([sys.executable,path,"w",fen],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
        else:
            bot = subprocess.Popen([sys.executable,path,"b",fen],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    else:
        path = merge_path(args.name, "main.exe")
        c.send(args.name)
        if czy_bialy:
            bot = subprocess.Popen([path,"w",fen],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
        else:
            bot = subprocess.Popen([path,"b",fen],stdin=subprocess.PIPE,stdout=subprocess.PIPE)






def ruch_clienta():
    xde=c.recv_msg()
    # with open("xd.txt","w") as f:
    #     f.write(xd)
    return xde

try:
    if (kolor=="biale" and board.turn == chess.WHITE) or (kolor=="czarne" and board.turn == chess.BLACK):
        #wykonaj pierwszy ruch
        wyjscie = bot.stdout.readline().decode('utf-8')
        wyjscie = wyjscie.strip()
        try:
            if chess.Move.from_uci(wyjscie.strip()) in board.legal_moves:#(2)
                board.push(chess.Move.from_uci(wyjscie.strip()))
            else:
                c.send(DISCONNEcT_MSG)
                exit(0)
        except ValueError:
            bot.terminate()
            c.send(DISCONNEcT_MSG)
            exit(0)
        if board.is_game_over():
            c.send(wyjscie)
            c.send(DISCONNEcT_MSG)
            exit(0)
        # print(f"moj ruch: {wyjscie}",flush=True)
        # with open("xd.txt","a") as f:
        #     f.write(f"{wyjscie}haha\n")
        # with open("xd.txt","a") as f:
        #     f.write(f"{wyjscie} {kolor}\n")
        c.send(wyjscie)

    while not(board.is_game_over()):
        wejscie,twhite,tblack = ruch_clienta().split('|')
        wejscie+="\n"

        # if not(args.player):
        #     with open("xd.txt","w") as f:
        #         f.write(f"{wejscie}1")
        if wejscie.strip("\n")==parsed_DISCONNEcT_MSG:
            bot.terminate()
            c.send(DISCONNEcT_MSG)
            exit(0)
        if chess.Move.from_uci(wejscie.strip()) in board.legal_moves:#(2)
            board.push(chess.Move.from_uci(wejscie.strip()))
        else:
            bot.terminate()
            c.send(DISCONNEcT_MSG)
            exit(0)
        if board.is_game_over():
            bot.stdin.write(wejscie.encode("utf-8"))
            bot.stdin.flush()
            # c.send(DISCONNEcT_MSG)
            exit(0)
        # print(f"ruch przeciwnika: {wejscie.strip()}",flush=True)
        # with open("xd.txt","w") as f:
        #     f.write(f"{wejscie},{twhite},{tblack}")
        if args.player:
            bot.stdin.write(f"{wejscie.strip()} {twhite.strip()} {tblack.strip()}\n".encode("utf-8"))
            bot.stdin.flush()
        else:
            bot.stdin.write(wejscie.encode("utf-8"))
            bot.stdin.flush()
        # print("xd")
        wyjscie = bot.stdout.readline().decode('utf-8')
        # with open("xd2.txt","a") as f:
        #     f.write(wyjscie)
        try:
            if chess.Move.from_uci(wyjscie.strip()) in board.legal_moves:#(2)
                board.push(chess.Move.from_uci(wyjscie.strip()))
            else:
                bot.terminate()
                c.send(DISCONNEcT_MSG)
                exit(0)
        except ValueError:
            bot.terminate()
            c.send(DISCONNEcT_MSG)
            exit(0)
        if board.is_game_over():
            c.send(wyjscie)
            # c.send(DISCONNEcT_MSG)
            exit(0)
        # print(f"moj ruch: {wyjscie}",flush=True)
        c.send(wyjscie)
        
except (BrokenPipeError, OSError):
    pass