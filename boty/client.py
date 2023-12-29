import subprocess
import socket
from client_const import *
import sys
import os


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
        else:
            return self.recv_msg()
                
c = Client()
kolor = c.recv_msg()
czy_bialy = True if kolor=="biale" else False

# curr_path = os.path.abspath(sys.argv[0])
path = f"boty/{sys.argv[1]}/main.py"

if czy_bialy:
    bot = subprocess.Popen(['python',path,"w"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
else:
    bot = subprocess.Popen(['python',path,"b"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)

print(kolor)




def ruch_clienta():
    return c.recv_msg()

if kolor=="biale":
    #wykonaj pierwszy ruch
    wyjscie = bot.stdout.readline().decode('utf-8')
    c.send(wyjscie)

while True:
    wejscie = f"{ruch_clienta()}\n"
    print(wejscie)
    bot.stdin.write(wejscie.encode("utf-8"))
    bot.stdin.flush()
    # print("xd")
    wyjscie = bot.stdout.readline().decode('utf-8')
    print(f"ruch bota {wyjscie}")
    c.send(wyjscie)
    

# c = Client()
# c.send("Gitara siema")
# print(c.recv_msg())
# c.send(f"{DISCONNEcT_MSG}")
