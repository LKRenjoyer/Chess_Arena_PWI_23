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


print(kolor)




def ruch_clienta():
    return c.recv_msg()

if kolor=="biale":
    #wykonaj pierwszy ruch
    wyjscie = bot.stdout.readline().decode('utf-8')
    if chess.Move.from_uci(wyjscie.strip()) in board.legal_moves:#(2)
        board.push(chess.Move.from_uci(wyjscie.strip()))
    else:
        c.send(DISCONNEcT_MSG)
        exit(0)
    if board.is_game_over():
        c.send(wyjscie)
        c.send(DISCONNEcT_MSG)
        exit(0)
    print(f"moj ruch: {wyjscie}")
    c.send(wyjscie)

while not(board.is_game_over()):
    wejscie = f"{ruch_clienta()}\n"
    if chess.Move.from_uci(wejscie.strip()) in board.legal_moves:#(2)
        board.push(chess.Move.from_uci(wejscie.strip()))
    else:
        c.send(DISCONNEcT_MSG)
        exit(0)
    if board.is_game_over():
        c.send(DISCONNEcT_MSG)
        exit(0)
    print(f"ruch przeciwnika: {wejscie.strip()}")
    bot.stdin.write(wejscie.encode("utf-8"))
    bot.stdin.flush()
    # print("xd")
    wyjscie = bot.stdout.readline().decode('utf-8')
    if chess.Move.from_uci(wyjscie.strip()) in board.legal_moves:#(2)
        board.push(chess.Move.from_uci(wyjscie.strip()))
    else:
        c.send(DISCONNEcT_MSG)
        exit(0)
    if board.is_game_over():
        c.send(wyjscie)
        c.send(DISCONNEcT_MSG)
        exit(0)
    print(f"moj ruch: {wyjscie}")
    c.send(wyjscie)
    

# c = Client()
# c.send("Gitara siema")
# print(c.recv_msg())
# c.send(f"{DISCONNEcT_MSG}")
