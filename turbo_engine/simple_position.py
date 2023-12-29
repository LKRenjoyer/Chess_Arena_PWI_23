import chess
import chess.svg
import random

def get_random_legal_move(board):
    legal_moves = list(board.legal_moves)
    if not legal_moves:
        return None
    return random.choice(legal_moves)

def print_board_fen(board):
    print(board.fen())

if __name__ == "__main__":
    # Wczytywanie FEN ze standardowego wejścia
    fen_input = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    
    # Tworzenie obiektu szachownicy na podstawie wczytanego FEN
    board = chess.Board(fen_input) 
    x = random.randint(2, 10)
    good = 1
    for i in range(x):
        # Wybieranie losowego legalnego ruchu
        random_move = get_random_legal_move(board)

        if random_move is not None:
            # Wykonywanie ruchu na szachownicy
            board.push(random_move)
            # Wypisywanie aktualnego FEN po wykonaniu ruchu
        else:
            print(0)  
            good = 0
            break 
    if good == 1: 
        print_board_fen(board)


