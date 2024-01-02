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
parser.add_argument('bot1', type=str, help='Nazwa pierwszego bota')
parser.add_argument('bot2', type=str, help='Nazwa drugiego bota')
parser.add_argument("-pvp", action='store_true', help='Player vs Player')
parser.add_argument("-pve", action='store_true', help='Player vs Entity')
parser.add_argument("-eve", action='store_true', help='Entity vs Entity')
parser.add_argument("-nv", action='store_true', help='Włącz walkę potów bez wizualizacji')

if len(sys.argv)<3:
    raise AttributeError("Bots' names not passed")

args = parser.parse_args()

if args.eve or (not args.pvp and not args.pvp and not args.pve):
    server = subprocess.Popen([sys.executable,'server/main.py'],stdout=subprocess.PIPE)
    client1 = subprocess.Popen([sys.executable,'boty/client.py',args.bot1],stdout=subprocess.PIPE)
    client2 = subprocess.Popen([sys.executable,'boty/client.py',args.bot2],stdout=subprocess.PIPE)
    if not(args.nv):
        visualization = subprocess.Popen([sys.executable,'wizualizacja_gry/display.py'], stdin=subprocess.PIPE, encoding="utf-8")

    while True:
        move = server.stdout.readline().decode('utf-8').strip()
        print(move)

        if len(move)>5:
            koniec = server.stdout.readline().decode('utf-8').strip()
            # print(koniec)
            # print(DISCONNEcT_MSG, file=visualization.stdin, flush=True)
            # print(move)
            break

        if not(args.nv):
            print(move, file=visualization.stdin, flush=True)

elif(args.pve):
    server = subprocess.Popen([sys.executable,'server/main.py'],stdout=subprocess.PIPE)
    client = subprocess.Popen([sys.executable,'boty/client.py',args.bot1],stdout=subprocess.PIPE)
    # time.sleep(1)
    player = subprocess.Popen([sys.executable,'boty/client.py',args.bot2,'--player'],stdout=subprocess.PIPE)
    # time.sleep(0.5)
    # visualization = subprocess.Popen([sys.executable,'wizualizacja_gry/display.py'], stdin=subprocess.PIPE, encoding="utf-8")
    # while True:
    #     move = server.stdout.readline().decode('utf-8').strip()
    #     print(move)
    #     print(move, file=visualization.stdin, flush=True)
    while True:
        pass
elif(args.pvp):
    server = subprocess.Popen([sys.executable,'server/main.py'],stdout=subprocess.PIPE)
    player = subprocess.Popen([sys.executable,'boty/client.py',args.bot2,'--player'],stdout=subprocess.PIPE)
    while True:
        pass


