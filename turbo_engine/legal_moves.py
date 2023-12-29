import chess

def print_legal_moves(fen):
    # Tworzymy obiekt szachownicy na podstawie FEN
    board = chess.Board(fen)

    # Pobieramy listę wszystkich legalnych ruchów
    legal_moves = list(board.legal_moves)

    # Wypisujemy liczbę legalnych ruchów
    print(len(legal_moves))
    moves = []
    # Pętla po wszystkich legalnych ruchach
    for move in legal_moves:
        # Wypisujemy ruch w formacie UCI
        moves.append(move.uci()) 
    posortowana = sorted(moves) 
    for x in posortowana: 
        print(x)

if __name__ == "__main__":
    # Wczytywanie FEN ze standardowego wejścia
    fen_input = input()

    # Wypisanie liczby i wszystkich legalnych ruchów
    print_legal_moves(fen_input)
