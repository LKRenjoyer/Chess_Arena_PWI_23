#Działanie tego pliku:
#Wpisujesz: "python walka.py nazwa_bota1 nazwa_bota2 [flagi]"
#Zaimplementowane boty są w folderze boty
#Puszczenie tego programu powoduje pojedynek między dwoma botami, flagi specyfikują czy ma być on wizualizowany czy nie

import sys
import subprocess
import argparse
import time
from server.server_const import *

parser = argparse.ArgumentParser(description='Główny program do runowania botów, musisz dodać folder z nazwą twojego bota do folderu boty i w nim plik main.py lub main.exe')
parser.add_argument('bot1', type=str, nargs='?', default='gracz', help='Nazwa pierwszego bota')
parser.add_argument('bot2', type=str, nargs='?', default='gracz', help='Nazwa drugiego bota')
parser.add_argument('-fen', type=str, nargs='?', default='rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1', help='Od jakiego fena gra ma sie zaczac')
parser.add_argument("-kolor", type=str, nargs='?',default="nic", help='Ustaw kolor jakim ma grac gracz')
parser.add_argument("-pvp", action='store_true', help='Player vs Player')
parser.add_argument("-pve", action='store_true', help='Player vs Entity')
parser.add_argument("-eve", action='store_true', help='Entity vs Entity')
parser.add_argument("-nv", action='store_true', help='Włącz walkę botów bez wizualizacji')

parser.add_argument("-online", action='store_true', help='Ta flaga mówi czy grasz jako online, czyli czy jest serwer a ty się do niego łączysz')
parser.add_argument("-host", action='store_true', help='Ta flaga wystepuje tylko jak gracz online i mówi czy jesteś hostem')
parser.add_argument("-player", action='store_true', help='Ta flaga wystepuje tylko jak gracz online i mówi, że chcesz grać jako człowiek')
parser.add_argument("-ngrok", type=str, nargs='?',default="localhost", help='Podaj ngroka')

# if len(sys.argv)<3:
#     raise AttributeError("Bots' names not passed")

args = parser.parse_args()

bot1,bot2 = args.bot1,args.bot2

# if len(args.boty)<2 and args.eve:
#     raise ValueError("Nie podano wystarczajaco botow")
# if len(args.boty)<1 and args.pve:
#     raise ValueError("Nie podano wystarczajaco botow")


if args.eve:
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    client1 = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}"],stdout=subprocess.PIPE)
    client2 = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot2}"],stdout=subprocess.PIPE)

    imie_bialego,imie_czarnego = server.stdout.readline().decode('utf-8').split()

    if not(args.nv):
        visualization = subprocess.Popen([sys.executable,'wizualizacja_gry/display.py',f'--fen={args.fen}',f"--nazwa_bialego={imie_bialego}",f"--nazwa_czarnego={imie_czarnego}"], stdin=subprocess.PIPE, encoding="utf-8")

    # print(args.nv)
    while True:
        package = server.stdout.readline().decode('utf-8').strip().split("|")
        move,white_time,black_time = package

        if len(move)>5:
            koniec = server.stdout.readline().decode('utf-8').strip()
            print(move)
            break  
            
        if not(args.nv):
            print(move,white_time,black_time, file=visualization.stdin, flush=True)

elif(args.pve):
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    client = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}"],stdout=subprocess.PIPE)
    player = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz 1",f'--fen={args.fen}','--player'],stdout=subprocess.PIPE)
    while True:
        package = server.stdout.readline().decode('utf-8').strip().split("|")
        move,white_time,black_time = package

        if len(move)>5:
            koniec = server.stdout.readline().decode('utf-8').strip()
            print(move)
            break  
elif args.online:
    if args.host:
        if args.player:
            server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
            player = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz 1",f'--fen={args.fen}','--player'],stdout=subprocess.PIPE)
            while True:
                package = server.stdout.readline().decode('utf-8').strip().split("|")
                move,white_time,black_time = package

                if len(move)>5:
                    koniec = server.stdout.readline().decode('utf-8').strip()
                    print(move)
                    break 
        else:
            server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
            client = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}"],stdout=subprocess.PIPE)
            while True:
                package = server.stdout.readline().decode('utf-8').strip().split("|")
                move,white_time,black_time = package

                if len(move)>5:
                    koniec = server.stdout.readline().decode('utf-8').strip()
                    print(move)
                    break  
    else:
        ngrok = args.ngrok
        if args.player:
            player = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz 2",f'--fen={args.fen}','--player',f"--ngrok={ngrok}"],stdout=subprocess.PIPE)
        else:
            client = subprocess.Popen([sys.executable,'boty/client.py',f"--name={bot1}",f"--ngrok={ngrok}"],stdout=subprocess.PIPE)
elif(args.pvp):
    server = subprocess.Popen([sys.executable,'server/main.py',f'--fen={args.fen}'],stdout=subprocess.PIPE)
    player1 = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz 1",f'--fen={args.fen}','--player'],stdout=subprocess.PIPE)
    player2 = subprocess.Popen([sys.executable,'boty/client.py',"--name=gracz 2",f'--fen={args.fen}','--player'],stdout=subprocess.PIPE)
    while True:
        package = server.stdout.readline().decode('utf-8').strip().split("|")
        move,white_time,black_time = package

        if len(move)>5:
            koniec = server.stdout.readline().decode('utf-8').strip()
            print(move)
            break  