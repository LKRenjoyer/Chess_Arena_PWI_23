#Główny serwer, który komunikuje:
#1.server -> boty(client) 2. boty(client) -> server 3. server -> wizualiazja(client) 4. wizualiazja(client) -> server (4. punkt tylko dla pvp lub pvb)

import socket
import threading
from server_const import *

class Server:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.server.bind(ADDR)

    def send_msg_to_client(self,conn,msg):
        msg = msg.encode('utf-8')
        msg_len = len(msg)
        send_len = str(msg_len).encode('utf-8')
        send_len += b' ' * (64 - len(send_len))
        conn.send(send_len)
        conn.send(msg)

    
    def handle_client(self,conn,addr):
        active = True

        while active:
            msg_len = conn.recv(64).decode('utf-8')
            if msg_len:
                msg_len = int(msg_len)
                msg = conn.recv(msg_len).decode("utf-8")
                print(conn,msg)
                self.send_msg_to_client(f"Otrzymano wiadomosc: {msg}")
                if msg==DISCONNEcT_MSG:
                    active = False
                    print(f"{addr} sie rozlaczyl")
            
        conn.close()
    
    def run(self):
        self.server.listen()
        while True:
            conn,addr = self.server.accept()
            print(f"{addr} wlasnie sie polaczyl")
            thr = threading.Thread(target=self.handle_client,args=(conn,addr))
            thr.start()

s = Server()
s.run()