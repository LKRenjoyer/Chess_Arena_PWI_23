#Działanie tego pliku:
#Wpisujesz: "python walka.py nazwa_bota1 nazwa_bota2 [flagi]"
#Zaimplementowane boty są w folderze boty
#Puszczenie tego programu powoduje pojedynek między dwoma botami, flagi specyfikują czy ma być on wizualizowany czy nie

import sys
import subprocess

if len(sys.argv)<3:
    print("Bots' names not passed")
    exit(1)

names = sys.argv[1:3]

if len(sys.argv)>3:
    flags = sys.argv[3:]
else:
    flags = []


server = subprocess.Popen(['python','server/main.py'],stdout=subprocess.PIPE)
client1 = subprocess.Popen(['python','boty/client.py',names[0]],stdout=subprocess.PIPE)
client2 = subprocess.Popen(['python','boty/client.py',names[1]],stdout=subprocess.PIPE)

while True:
    print(server.stdout.readline().decode('utf-8'))







