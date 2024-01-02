import subprocess
import chess 
import random
import sys
import os
from functools import partial

# todo: 
# dodanie reguly 50 nuda-ruchow 
# dodanie ograniczenia czasowego na wykonanie ruchu

def run_bot(bot_command):
    return subprocess.Popen(bot_command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
#proces.kill / terminate 
global_dict = {}
null_move = "a1a1\n"
file =1 
path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))
def load(): 
    with open(path("data"), "r") as f: 
        return f.read().splitlines(False)

moje_fajne_feny = load()

def is_valid_uci_move(move_str):
    try:
        move = chess.Move.from_uci(move_str)
        return True
    except ValueError:
        return False

def is_valid_fen(fen):
    try:
        board = chess.Board(fen)
        return True
    except ValueError:
        return False

def poly_hash(s, base=131, mod=10**9 + 7):

    hash_value = 0
    base_power = 1
    for char in s:
        hash_value = (hash_value * base + ord(char)) % mod
        base_power = (base_power * base) % mod
    return hash_value

def add(s):
    global global_dict

    hash_value = poly_hash(s)
    
    if hash_value in global_dict:
        global_dict[hash_value] += 1
    else:
        global_dict[hash_value] = 1

def is_threefold_repetition(s):
    global global_dict

    hash_value = poly_hash(s)

    return global_dict.get(hash_value, 0) >= 3

def run(color1, color2, moj_fen):
    # Uruchamianie dwóch botów
    botA = run_bot([sys.executable, "botA.py"])
    botB = run_bot([sys.executable, "old_botB.py"])
    global null_move, Ascore, Bscore, Draws
    # Przykładowy stan początkowy
    if not is_valid_fen(moj_fen): 
        print("Niepoprawny fen szachownicy") 
        return
    initial_position = "FEN: " + moj_fen + "\n"

    # Przesyłanie stanu początkowego do obu botów
    botA.stdin.write("isready?\n")
    botA.stdin.flush()
    botB.stdin.write("isready?\n")
    botB.stdin.flush()
    kolory = [color1, color2]
    if random.randint(0,1) == 1:
        kolory.append("white") 
        kolory.append("black") 
    else : 
        kolory.append("black") 
        kolory.append("white") 
    ansA = botA.stdout.readline().strip() 
    ansB = botB.stdout.readline().strip() 
    if( ansA != "ready") : 
            print("botA not responding propely")  
            exit(12) 
    if(ansB != "ready"): 
            print("botB not responding propely") 
            exit(13) 
    botA.stdin.write("color: "+kolory[0] +"\n") 
    botA.stdin.flush()
    ansA = botA.stdout.readline().strip()  
    if ansA != kolory[0]: 
        print("botA does not understand how colors work") 
        exit(14)
    
    botB.stdin.write("color: "+kolory[1] + "\n") 
    botB.stdin.flush()
    ansB = botB.stdout.readline().strip()  
    if ansB != kolory[1]: 
        print("botB does not understand how colors work") 
        exit(15)
    botA.stdin.write(initial_position) 
    botA.stdin.flush()
    ansA = botA.stdout.readline().strip()  
    if ansA != "understood": 
        print("botA does not understand FEN") 
        exit(16)
    
    botB.stdin.write(initial_position ) 
    botB.stdin.flush()
    ansB = botB.stdout.readline().strip()  
    if ansB != "understood": 
        print("botb does not understand FEN") 
        exit(17)
    fen = initial_position[5:]
    
    board = chess.Board(fen)
    if not board.is_valid(): 
        print("Invalid fen format ~ administrator")
        exit(33) 
    add(board.fen())
    zwyciezca = " " 
    #dodac 50 nuda ruchow rule 
    #dodac inssuficient material
    if (board.turn == chess.WHITE and kolory[0] == "white") or (board.turn == chess.BLACK and kolory[0] == "black"):
        while True:
            # Oczekiwanie na ruch od bota A 
            move_A = botA.stdout.readline().strip()
            file.write(board.fen() + "\n")
            file.write("botA: "+move_A + "\n")
            if not is_valid_uci_move(move_A): 
               file.write("botA podal ruch w nieprawidlowym formacie\n") 
               zwyciezca = "botB"
               break
            if chess.Move.from_uci(move_A) not in board.legal_moves:
                file.write("botA probowal wykonac nielegalny ruch\n") 
                zwyciezca = "botB"
                break
            board.push(chess.Move.from_uci(move_A))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                file.write("potrojne powtorzenie pozycji\n") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                file.write("Niewystarczajacy material\n") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                file.write("mat!\n") 
                zwyciezca = "botA"
                break
            if board.is_stalemate():  
                file.write("pat!\n") 
                zwyciezca = " "
                break
            botB.stdin.write(move_A + "\n")
            botB.stdin.flush()

            move_B = botB.stdout.readline().strip()
            file.write(board.fen()+"\n")
            file.write("botB: "+move_B +"\n") 
            if not is_valid_uci_move(move_B): 
                file.write("botB podal ruch w nieprawidlowym formacie\n") 
                zwyciezca = "botA"
                break
            if chess.Move.from_uci(move_B) not in board.legal_moves:
                file.write("botB probowal wykonac nielegalny ruch\n") 
                zwyciezca = "botA"
                break
            board.push(chess.Move.from_uci(move_B))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                file.write("potrojne powtorzenie pozycji\n") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                file.write("Niewystarczajacy material\n") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                file.write("mat!\n") 
                zwyciezca = "botB"
                break
            if board.is_stalemate():  
                file.write("pat!\n") 
                zwyciezca = " "
                break
            # Przesyłanie ruchu od bota B do bota A
            botA.stdin.write(move_B + "\n")
            botA.stdin.flush() 
    else: 
        while True: 
            move_B = botB.stdout.readline().strip()
            file.write(board.fen()+"\n")
            file.write("botB: "+move_B +"\n") 
            if not is_valid_uci_move(move_B): 
                file.write("botB podal ruch w nieprawidlowym formacie\n") 
                zwyciezca = "botA"
                break
            if chess.Move.from_uci(move_B) not in board.legal_moves:
                file.write("botB probowal wykonac nielegalny ruch\n") 
                zwyciezca = "botA"
                break
            board.push(chess.Move.from_uci(move_B))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                file.write("potrojne powtorzenie pozycji\n") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                file.write("Niewystarczajacy material\n") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                file.write("mat!\n") 
                zwyciezca = "botB"
                break
            if board.is_stalemate():  
                file.write("pat!\n") 
                zwyciezca = " "
                break
            # Przesyłanie ruchu od bota B do bota A
            botA.stdin.write(move_B + "\n")
            botA.stdin.flush() 

            move_A = botA.stdout.readline().strip()
            file.write(board.fen()+"\n")
            file.write("botA: "+move_A+"\n")
            if not is_valid_uci_move(move_A): 
               file.write("botA podal ruch w nieprawidlowym formacie\n") 
               zwyciezca = "botB"
               break
            if chess.Move.from_uci(move_A) not in board.legal_moves:
                file.write("botA probowal wykonac nielegalny ruch\n") 
                zwyciezca = "botB"
                break
            board.push(chess.Move.from_uci(move_A))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                file.write("potrojne powtorzenie pozycji\n") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                file.write("Niewystarczajacy material\n") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                file.write("mat!\n") 
                zwyciezca = "botA"
                break
            if board.is_stalemate():  
                file.write("pat!\n") 
                zwyciezca = " "
                break
            botB.stdin.write(move_A + "\n")
            botB.stdin.flush()
    if zwyciezca == " ": 
        print("Remis!") 
        Draws += 1
    else: 
        print("Zwyciezca to: " + zwyciezca)  
        if zwyciezca == "botA": 
            Ascore += 1 
        if zwyciezca == "botB": 
            Bscore += 1 
    #print(Ascore, Bscore, Draws) 
    if botA.poll() == None: 
        botA.stdin.write(null_move)
        botA.stdin.flush() 
        botA.terminate() 
    if botB.poll() == None: 
        botB.stdin.write(null_move)
        botB.stdin.flush()  
        botB.terminate()
if __name__ == "__main__":
    N = 100 # do modyfiakcji przez usera, liczba szachownic
    assert(N <= len(moje_fajne_feny)) #liczba partii nie moze przekraczac liczby dostepnych fenow  
    Ascore=0; Bscore =0; Draws = 0
    file = open('log_partii', 'w')
    numer = 1; 
    for k in range(1, N+1):
        print(f"Szachownica numer {k}:") 
        file.write((f"\n\nSzachownica numer {k}:\n\n"))
        kolory = ["white", "black"] 
        print(f"Partia numer: {numer}") 
        file.write(f"\nPartia numer: {numer}\n\n")
        numer += 1
        run(kolory[0], kolory[1], moje_fajne_feny[k-1])
        print(f"Partia numer: {numer}") 
        file.write(f"\nPartia numer: {numer}\n\n")
        numer += 1 
        run(kolory[1], kolory[0], moje_fajne_feny[k-1])
    print(f"botA wins: {Ascore} Draws: {Draws} botB wins: {Bscore}")
    file.close()
