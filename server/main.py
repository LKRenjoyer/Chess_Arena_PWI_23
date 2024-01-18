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
start_time = 0
end_time = 0

board = chess.Board()

# print = functools.partial(print,flush=True)

class Timer:
    def __init__(self) -> None:
        self.czas_bialego = 600
        self.czas_czarnego = 600
        self.kogo_tura = "nikt"
    

        
timer = Timer()


        

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
        gotowy_kanal_1_main[0] = True
        gotowy_kanal_2_main[0] = True
        gotowy_kanal_3_main[0] = True
        gotowy_kanal_4_main[0] = True
    #  print("Wygrywa:",name2[0],flush=True)
    #     print(DISCONNEcT_MSG,flush=True)

    def wypisz_zwyciezce(self,kto_wygral):
        if kto_wygral==1:
            print(f"Wygrywa: {name1[0]}\n{DISCONNEcT_MSG}",flush=True)
        else:
            print(f"Wygrywa: {name2[0]}\n{DISCONNEcT_MSG}",flush=True)
            
    
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
                    # if nazwa[0]==name1[0]:
                    #     print(f"Wygrywa: {name2[0]}")
                    # else:
                    #     print(f"Wygrywa: {name1[0]}")
                    kanal1[0] = DISCONNEcT_MSG
                    gotowy_kanal_1[0]=True
                    koniec[0]=True
                    break
                kanal1[0] = wiadomosc
                gotowy_kanal_1[0]=True
                wykonaj_ruch = not wykonaj_ruch
            else:
                while gotowy_kanal_2[0]==False and koniec_th[0]==False:
                    pass

                if koniec_th[0]:
                    try:
                        self.send_msg_to_client(conn,DISCONNEcT_MSG)
                    except ConnectionAbortedError:
                        pass
                    finally:
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
            if timer.czas_bialego - (time.time() - start_time) <= 0 and timer.kogo_tura=="bialy":
                # with open("xd.txt",'a') as f:
                #     f.write(f"{time.time() - start_time}  {time.time()} {start_time}\n")
                return 1

        if koniec[0]:
            return DISCONNEcT_MSG
        
        gotowy_kanal_1_main[0] = False
        return kanal1_main[0]


    def pull_black_move(self):
        while gotowy_kanal_3_main[0] == False and koniec[0]==False:
            if timer.czas_czarnego - (time.time() - start_time) <= 0 and timer.kogo_tura=="czarny":
                # with open("xd.txt",'a') as f:
                #     f.write(f"{time.time() - start_time}  {time.time()} {start_time}\n")
                return 1

        if koniec[0]:
            return DISCONNEcT_MSG
        
        gotowy_kanal_3_main[0] = False
        return kanal3_main[0]
    
    def eval_res(self,res):
        if res=='1-0':
            return f"Wygrywa: {name1[0]}\n{DISCONNEcT_MSG}"
        elif res=='0-1':
            return f"Wygrywa: {name2[0]}\n{DISCONNEcT_MSG}"
        else:
            return f"Remis obu graczy\n{DISCONNEcT_MSG}"
    
    def run(self):
        global start_time
        global end_time
        global timer
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
            start_time = time.time()
            timer.kogo_tura = "bialy"
            white_move = self.pull_white_move() #(1)
            timer.kogo_tura = "nikt"
            end_time = time.time()
            timer.czas_bialego -= (end_time-start_time)

            if type(white_move)!=str:
                self.wypisz_zwyciezce(2)
                self.settrue()
                break

            white_move = white_move.strip()
            # print(white_move)


            try:
                if chess.Move.from_uci(white_move) in board.legal_moves:#(2)
                    board.push(chess.Move.from_uci(white_move))
                else:
                    self.wypisz_zwyciezce(2)
                    self.settrue()
                    break
            except ValueError:
                self.wypisz_zwyciezce(2)
                self.settrue()
                break

            print(f"{white_move}|{timer.czas_bialego}|{timer.czas_czarnego}",flush=True)

            # print("ruch białego: ",white_move)
            # os.system('cls')
            # print(board)
            # print()
            if board.is_game_over():#(3)
                # print("Koniec gry!")
                # time.sleep(5)
                kanal4_main[0]=white_move
                self.send_msg_to_client(czarny_conn,kanal4_main[0]) 



                print(self.eval_res(board.result()),flush=True)
                self.settrue()
                break

            kanal4_main[0]=f"{white_move}|{timer.czas_bialego}|{timer.czas_czarnego}"#(4)
            gotowy_kanal_4_main[0]=True

            start_time = time.time()
            timer.kogo_tura = "czarny"
            black_move = self.pull_black_move()#(5)
            timer.kogo_tura = "nikt"
            end_time = time.time()
            timer.czas_czarnego -= (end_time-start_time)

            if type(black_move)!=str:
                self.wypisz_zwyciezce(1)
                self.settrue()
                break


            black_move = black_move.strip()
            # print("ruch czarnego: ",black_move)
            # os.system('cls')
            # print(board)
            # print()
            try:
                if chess.Move.from_uci(black_move) in board.legal_moves:#(6)
                    board.push(chess.Move.from_uci(black_move))
                else:
                    # print("Nie legalny ruch!!! Rogrywka przerwana :(")
                    self.wypisz_zwyciezce(1)
                    self.settrue()
                    break
            except ValueError:
                self.wypisz_zwyciezce(1)
                self.settrue()
                break

            print(f"{black_move}|{timer.czas_bialego}|{timer.czas_czarnego}",flush=True)

            if board.is_game_over():#(7)
                # print("Koniec gry!")
                # time.sleep(5)
                kanal2_main[0]=black_move
                self.send_msg_to_client(bialy_conn,kanal2_main[0])             

                print(self.eval_res(board.result()),flush=True)
                self.settrue()
                break

            kanal2_main[0]=f"{black_move}|{timer.czas_bialego}|{timer.czas_czarnego}"#(8)
            gotowy_kanal_2_main[0] = True
        
        # time.sleep(5)
        self.server.close()


        
        
        
        


s = Server()
# server_thread = threading.Thread(target=s.run)
s.run()