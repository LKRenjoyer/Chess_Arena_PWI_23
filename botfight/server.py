#Główny serwer, który komunikuje:
#1.server -> boty(client) 2. boty(client) -> server 3. server -> wizualiazja(client) 4. wizualiazja(client) -> server (4. punkt tylko dla pvp lub pvb)

import socket
import threading
from server_const import *

kanal1_main = [""]
kanal2_main = [""]
kanal3_main = [""]
kanal4_main = [""]
lock = threading.Lock()
gotowy_kanal_1_main = [False]
gotowy_kanal_2_main = [False]
gotowy_kanal_3_main = [False]
gotowy_kanal_4_main = [False]

class Server:
    def __init__(self):
        self.server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.server.bind(ADDR)
        # self.kanal1 = ""
        # self.kanal2 = ""

    def send_msg_to_client(self,conn,msg):
        msg = msg.encode('utf-8')
        msg_len = len(msg)
        send_len = str(msg_len).encode('utf-8')
        send_len += b' ' * (64 - len(send_len))
        conn.send(send_len)
        conn.send(msg)

    def recv_msg_from_client(self,conn):#może nie działać
        msg_len = conn.recv(64).decode('utf-8')
        if msg_len:
            msg_len = int(msg_len)
            msg = conn.recv(msg_len).decode("utf-8")
            return msg
        else:
            return self.recv_msg_from_client(conn)
            
    
    def handle_client(self,conn,addr,kanal1,kanal2,kolor,gotowy_kanal_1,gotowy_kanal_2): #wykonaj_ruch == True - zwróć na kanał ruch bota, wykonaj_ruch == False - wyślij clientowi ruch przeciwnika
        active = True                                                               #

        self.send_msg_to_client(conn,kolor)


        if kolor == "biale":
            wykonaj_ruch = True
        else:
            wykonaj_ruch = False

        # print(kolor)

        while active:
            if wykonaj_ruch:
                # print(kanal1[0],"otrzymano",kolor)
                kanal1[0] = self.recv_msg_from_client(conn)
                gotowy_kanal_1[0]=True
                wykonaj_ruch = not wykonaj_ruch
            else:
                while gotowy_kanal_2[0]==False:
                    pass

                self.send_msg_to_client(conn,kanal2[0])             

                gotowy_kanal_2[0]=False
                wykonaj_ruch = not wykonaj_ruch


        # while active:
        #     msg_len = conn.recv(64).decode('utf-8')
        #     if msg_len:
        #         msg_len = int(msg_len)
        #         msg = conn.recv(msg_len).decode("utf-8")
        #         print(conn,msg)
        #         self.send_msg_to_client(f"Otrzymano wiadomosc: {msg}")
        #         if msg==DISCONNEcT_MSG:
        #             active = False
        #             print(f"{addr} sie rozlaczyl")
            
        conn.close()

    def pull_white_move(self):
        while gotowy_kanal_1_main[0] == False:
            pass
        
        gotowy_kanal_1_main[0] = False
        return kanal1_main[0]


    def pull_black_move(self):
        while gotowy_kanal_3_main[0] == False:
            pass
        
        gotowy_kanal_3_main[0] = False
        return kanal3_main[0]
    
    def run(self):
        self.server.listen()
        ile_polaczen = 0
        while ile_polaczen<2:
            conn,addr = self.server.accept()
            ile_polaczen+=1
            print(f"{addr} wlasnie sie polaczyl")
            if ile_polaczen==1:#zmienic na losowe przydzielenie kanalow, bo od tego zalezy czy kto gra czarnymi czy ktos gra bialymi
                thr = threading.Thread(target=self.handle_client,args=(conn,addr,kanal1_main,kanal2_main,"biale",gotowy_kanal_1_main,gotowy_kanal_2_main))
            else:
                thr = threading.Thread(target=self.handle_client,args=(conn,addr,kanal3_main,kanal4_main,"czarne",gotowy_kanal_3_main,gotowy_kanal_4_main))
            thr.start()
        # dopoki prawda(gra się nie skończyła):
        #     zapytaj białego o ruch (1)
        #     sprawdź legalność ruchu (to do zaimplemetowania później) (2)
        #     sprawdź czy gra się nie skończyła (3)
        #     wyślij ten ruch do czarnego (4)
        #     zapytaj czarnego o ruch (5)
        #     sprawdź legalność ruchu(to do zaimplementowania) (6)
        #     sprawdź czy gra się nie skończyła (7)
        #     wyślij ten ruch do białego (8)
        
        print("Oba boty sie polaczyly")
        
        while True:
            white_move = self.pull_white_move() #(1)
            print("ruch białego: ",white_move)
            kanal4_main[0]=white_move#(4)
            gotowy_kanal_4_main[0]=True
            black_move = self.pull_black_move()#(5)
            print("ruch czarnego: ",black_move)
            kanal2_main[0]=black_move#(8)
            gotowy_kanal_2_main[0] = True


        
        
        
        


s = Server()
# server_thread = threading.Thread(target=s.run)
s.run()