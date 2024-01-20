#Działanie tego pliku:
#Wpisujesz: "python walka.py nazwa_bota1 nazwa_bota2 [flagi]"
#Zaimplementowane boty są w folderze boty
#Puszczenie tego programu powoduje pojedynek między dwoma botami, flagi specyfikują czy ma być on wizualizowany czy nie

import sys
import subprocess
import argparse
import time
from server.server_const import *

parser = argparse.ArgumentParser(description='Główny program do runowania botów')
parser.add_argument('bot1', type=str, nargs='?', default='gracz', help='Nazwa pierwszego bota')
parser.add_argument('bot2', type=str, nargs='?', default='gracz', help='Nazwa drugiego bota')
parser.add_argument('-fen', type=str, nargs='?', default='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1', help='Od jakiego fena gra ma sie zaczac')
parser.add_argument("-pvp", action='store_true', help='Player vs Player')
parser.add_argument("-pve", action='store_true', help='Player vs Entity')
parser.add_argument("-eve", action='store_true', help='Entity vs Entity')
parser.add_argument("-nv", action='store_true', help='Włącz walkę botów bez wizualizacji')

# if len(sys.argv)<3:
#     raise AttributeError("Bots' names not passed")

args = parser.parse_args()

bot1,bot2 = args.bot1,args.bot2

# if len(args.boty)<2 and args.eve:
#     raise ValueError("Nie podano wystarczajaco botow")
# if len(args.boty)<1 and args.pve:
#     raise ValueError("Nie podano wystarczajaco botow")


if args.eve or (not args.pvp and not args.pvp and not args.pve):
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    client1 = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}"],stdout=subprocess.PIPE)
    client2 = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot2}"],stdout=subprocess.PIPE)
    if not(args.nv):
        visualization = subprocess.Popen([sys.executable,'wizualizacja_gry/display.py',f'--fen={args.fen}'], stdin=subprocess.PIPE, encoding="utf-8")

    # print(args.nv)
    while True:
        package = server.stdout.readline().decode('utf-8').strip().split("|")
        move,white_time,black_time = package

        if len(move)>5:
            koniec = server.stdout.readline().decode('utf-8').strip()
            break  
            
        if not(args.nv):
            print(move,white_time,black_time, file=visualization.stdin, flush=True)

elif(args.pve):
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    client = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}"],stdout=subprocess.PIPE)
    player = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz",'--player'],stdout=subprocess.PIPE)
    while True:
        pass
elif(args.pvp):
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    player = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz",'--player'],stdout=subprocess.PIPE)
    while True:
        pass


