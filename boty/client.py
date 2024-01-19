import subprocess
import socket
from client_const import *
import sys
import os
from functools import partial
import argparse
import chess

board = chess.Board()

class Client:
    def __init__(self):
        self.client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.client.connect(ADDR)
    
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
        
parser = argparse.ArgumentParser(description='Główna program do runowania botów')
parser.add_argument('name', type=str, help='Nazwa bota')
parser.add_argument("--player", action='store_true', help='Oznacza, że to będzie prawdziwy gracz')

args = parser.parse_args()
                
c = Client()
kolor = c.recv_msg()
# print(kolor,flush=True)
czy_bialy = True if kolor=="biale" else False


# curr_path = os.path.abspath(sys.argv[0])
if args.player:
    # merge_path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))
    # path = merge_path(args.name, "main.py")
    path = "wizualizacja_gry/display.py"
    if czy_bialy:
        c.send("gracz bialy")
        bot = subprocess.Popen([sys.executable, path,"-w"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    else:
        c.send("gracz czarny")
        bot = subprocess.Popen([sys.executable,path,"-b"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
else:
    merge_path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))
    path = merge_path(args.name, "main.py")
    c.send(args.name)
    if czy_bialy:
        bot = subprocess.Popen([sys.executable,path,"w"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    else:
        bot = subprocess.Popen([sys.executable,path,"b"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)






def ruch_clienta():
    xde=c.recv_msg()
    # with open("xd.txt","w") as f:
    #     f.write(xd)
    return xde

try:
    if kolor=="biale":
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
        c.send(wyjscie)

    while not(board.is_game_over()):
        wejscie,twhite,tblack = ruch_clienta().split('|')
        wejscie+="\n"

        # if not(args.player):
        #     with open("xd.txt","w") as f:
        #         f.write(f"{wejscie}1")
        if wejscie.strip("\n")==DISCONNEcT_MSG:
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
        

    # c = Client()
    # c.send("Gitara siema")
    # print(c.recv_msg())
    # c.send(f"{DISCONNEcT_MSG}")
except (BrokenPipeError, OSError):
    pass