import subprocess
import chess 
import random
def run_bot(bot_command):
    return subprocess.Popen(bot_command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
#proces.kill / terminate
global_dict = {}
global null_move 
null_move = "a1a1\n"


def is_valid_uci_move(move_str):
    try:
        move = chess.Move.from_uci(move_str)
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

def main():
    # Uruchamianie dwóch botów
    botA = run_bot(["python3", "botA.py"])
    botB = run_bot(["python3", "botB.py"])
    global null_move
    # Przykładowy stan początkowy
    initial_position = "FEN: r1bqkbnr/1ppppp2/2n3p1/p6p/4P2P/P1P5/1P1P1PP1/RNBQKBNR w KQkq - 0 5\n"

    # Przesyłanie stanu początkowego do obu botów
    botA.stdin.write("isready?\n")
    botA.stdin.flush()
    botB.stdin.write("isready?\n")
    botB.stdin.flush()
    kolory = []
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
            print(board.fen())
            print(move_A)
            if not is_valid_uci_move(move_A): 
               print("botA podal ruch w nieprawidlowym formacie") 
               zwyciezca = "botB"
               break
            if chess.Move.from_uci(move_A) not in board.legal_moves:
                print("botA probowal wykonac nielegalny ruch") 
                zwyciezca = "botB"
                break
            board.push(chess.Move.from_uci(move_A))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                print("potrojne powtorzenie pozycji") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                print("Niewystarczajacy material") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                print("mat!") 
                zwyciezca = "botA"
                break
            if board.is_stalemate():  
                print("pat!") 
                zwyciezca = " "
                break
            botB.stdin.write(move_A + "\n")
            botB.stdin.flush()

            move_B = botB.stdout.readline().strip()
            print(board.fen())
            print(move_B) 
            if not is_valid_uci_move(move_B): 
                print("botB podal ruch w nieprawidlowym formacie") 
                zwyciezca = "botA"
                break
            if chess.Move.from_uci(move_B) not in board.legal_moves:
                print("botB probowal wykonac nielegalny ruch") 
                zwyciezca = "botA"
                break
            board.push(chess.Move.from_uci(move_B))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                print("potrojne powtorzenie pozycji") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                print("Niewystarczajacy material") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                print("mat!") 
                zwyciezca = "botB"
                break
            if board.is_stalemate():  
                print("pat!") 
                zwyciezca = " "
                break
            # Przesyłanie ruchu od bota B do bota A
            botA.stdin.write(move_B + "\n")
            botA.stdin.flush() 
    else: 
        while True: 
            move_B = botB.stdout.readline().strip()
            print(board.fen())
            print(move_B) 
            if not is_valid_uci_move(move_B): 
                print("botB podal ruch w nieprawidlowym formacie") 
                zwyciezca = "botA"
                break
            if chess.Move.from_uci(move_B) not in board.legal_moves:
                print("botB probowal wykonac nielegalny ruch") 
                zwyciezca = "botA"
                break
            board.push(chess.Move.from_uci(move_B))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                print("potrojne powtorzenie pozycji") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                print("Niewystarczajacy material") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                print("mat!") 
                zwyciezca = "botB"
                break
            if board.is_stalemate():  
                print("pat!") 
                zwyciezca = " "
                break
            # Przesyłanie ruchu od bota B do bota A
            botA.stdin.write(move_B + "\n")
            botA.stdin.flush() 

            move_A = botA.stdout.readline().strip()
            print(board.fen())
            print(move_A)
            if not is_valid_uci_move(move_A): 
               print("botA podal ruch w nieprawidlowym formacie") 
               zwyciezca = "botB"
               break
            if chess.Move.from_uci(move_A) not in board.legal_moves:
                print("botA probowal wykonac nielegalny ruch") 
                zwyciezca = "botB"
                break
            board.push(chess.Move.from_uci(move_A))
            add(board.fen()) 
            if is_threefold_repetition(board.fen()): 
                print("potrojne powtorzenie pozycji") 
                zwyciezca = " "
                break
            if board.is_insufficient_material():
                print("Niewystarczajacy material") 
                zwyciezca = " "
                break
            if board.is_checkmate():  
                print("mat!") 
                zwyciezca = "botA"
                break
            if board.is_stalemate():  
                print("pat!") 
                zwyciezca = " "
                break
            botB.stdin.write(move_A + "\n")
            botB.stdin.flush()
    if zwyciezca == " ": 
        print("Remis!")
    else: 
        print("Zwyciezca to: " + zwyciezca)
    botA.stdin.write(null_move)
    botA.stdin.flush() 
    botB.stdin.write(null_move)
    botB.stdin.flush()  
    botA.terminate() 
    botB.terminate()
if __name__ == "__main__":
    main()
