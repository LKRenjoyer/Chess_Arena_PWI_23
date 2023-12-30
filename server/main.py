#Główny serwer, który komunikuje:
#1.server -> boty(client) 2. boty(client) -> server 3. server -> wizualiazja(client) 4. wizualiazja(client) -> server (4. punkt tylko dla pvp lub pvb)

#Należy dodać sprawdzanie, czy otrzymany ruch to None. Dzieje się to, gdy bot przedwcześnie zakończył swoje działanie
#Jego brak powoduje błąd przy uruchomieniu np. python run_duel.py fast_q_bot bot_jana_1_lepszy

import socket
import threading
from server_const import *
import chess
import os
import functools
import random
import time

kanal1_main = [""]
kanal2_main = [""]
kanal3_main = [""]
kanal4_main = [""]
lock = threading.Lock()
gotowy_kanal_1_main = [False]
gotowy_kanal_2_main = [False]
gotowy_kanal_3_main = [False]
gotowy_kanal_4_main = [False]
name1 = [""]
name2 = [""]
koniec = [False]

board = chess.Board()

print = functools.partial(print,flush=True)

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
        # else:
        #     return self.recv_msg_from_client(conn)
        
    def settrue(self):
        koniec[0]=True
        # gotowy_kanal_1_main[0] = True
        # gotowy_kanal_2_main[0] = True
        # gotowy_kanal_3_main[0] = True
        # gotowy_kanal_4_main[0] = True
        pass
            
    
    def handle_client(self,conn,addr,kanal1,kanal2,kolor,gotowy_kanal_1,gotowy_kanal_2,nazwa,koniec_th): #wykonaj_ruch == True - zwróć na kanał ruch bota, wykonaj_ruch == False - wyślij clientowi ruch przeciwnika
        active = True                                                               #

        self.send_msg_to_client(conn,kolor)
        nazwa[0] = self.recv_msg_from_client(conn)


        if kolor == "biale":
            wykonaj_ruch = True
        else:
            wykonaj_ruch = False

        # print(kolor)

        while active:
            if wykonaj_ruch:
                # print(kanal1[0],"otrzymano",kolor)
                wiadomosc = self.recv_msg_from_client(conn)
                if wiadomosc==DISCONNEcT_MSG:
                    active=False
                    break
                kanal1[0] = wiadomosc
                gotowy_kanal_1[0]=True
                wykonaj_ruch = not wykonaj_ruch
            else:
                while gotowy_kanal_2[0]==False and koniec_th[0]==False:
                    pass

                if koniec_th[0]:
                    active=False
                    break

                self.send_msg_to_client(conn,kanal2[0])             

                gotowy_kanal_2[0]=False
                wykonaj_ruch = not wykonaj_ruch
        
        conn.close()


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
            

    def pull_white_move(self):
        while gotowy_kanal_1_main[0] == False and koniec[0]==False:
            pass

        if koniec[0]:
            return ""
        
        gotowy_kanal_1_main[0] = False
        return kanal1_main[0]


    def pull_black_move(self):
        while gotowy_kanal_3_main[0] == False and koniec[0]==False:
            pass

        if koniec[0]:
            return ""
        
        gotowy_kanal_3_main[0] = False
        return kanal3_main[0]
    
    def eval_res(self,res):
        if res=='1-0':
            return f"Wygrywa: {name1[0]}"
        elif res=='0-1':
            return f"Wygrywa: {name2[0]}"
        else:
            return "Remis obu graczy"
    
    def run(self):
        self.server.listen()
        ile_polaczen = 0
        kto_bialy=random.randint(1,2)
        while ile_polaczen<2:
            conn,addr = self.server.accept()
            ile_polaczen+=1
            # print(f"{addr} wlasnie sie polaczyl")
            if ile_polaczen==kto_bialy:
                thr = threading.Thread(target=self.handle_client,args=(conn,addr,kanal1_main,kanal2_main,"biale",gotowy_kanal_1_main,gotowy_kanal_2_main,name1,koniec))
                bialy_conn = conn
            else:
                thr = threading.Thread(target=self.handle_client,args=(conn,addr,kanal3_main,kanal4_main,"czarne",gotowy_kanal_3_main,gotowy_kanal_4_main,name2,koniec))
                czarny_conn = conn
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
        
        # print("Oba boty sie polaczyly")
        
        while not(board.is_game_over()):
            white_move = self.pull_white_move() #(1)
            white_move = white_move.strip()
            # print(white_move)

            print(white_move)
            if chess.Move.from_uci(white_move) in board.legal_moves:#(2)
                board.push(chess.Move.from_uci(white_move))
            else:
                # print("Nie legalny ruch!!! Rogrywka przerwana :(")
                print("Wygrywa:",name2[0],flush=True)
                print(DISCONNEcT_MSG,flush=True)
                self.settrue()
                break


            # print("ruch białego: ",white_move)
            # os.system('cls')
            # print(board)
            # print()
            if board.is_game_over():#(3)
                # print("Koniec gry!")
                # time.sleep(5)
                kanal4_main[0]=white_move
                self.send_msg_to_client(czarny_conn,kanal4_main[0]) 



                print(self.eval_res(board.result()))
                print(DISCONNEcT_MSG)
                self.settrue()
                break

            kanal4_main[0]=white_move#(4)
            gotowy_kanal_4_main[0]=True

            black_move = self.pull_black_move()#(5)
            black_move = black_move.strip()
            print(black_move)
            # print("ruch czarnego: ",black_move)
            # os.system('cls')
            # print(board)
            # print()

            if chess.Move.from_uci(black_move) in board.legal_moves:#(6)
                board.push(chess.Move.from_uci(black_move))
            else:
                # print("Nie legalny ruch!!! Rogrywka przerwana :(")
                print("Wygrywa:",name1[0],flush=True)
                print(DISCONNEcT_MSG,flush=True)
                self.settrue()
                break


            if board.is_game_over():#(7)
                # print("Koniec gry!")
                # time.sleep(5)
                kanal2_main[0]=black_move
                self.send_msg_to_client(bialy_conn,kanal2_main[0])             

                print(self.eval_res(board.result()),flush=True)
                print(DISCONNEcT_MSG,flush=True)
                self.settrue()
                break

            kanal2_main[0]=black_move#(8)
            gotowy_kanal_2_main[0] = True
        
        # time.sleep(5)
        self.server.close()


        
        
        
        


s = Server()
# server_thread = threading.Thread(target=s.run)
s.run()