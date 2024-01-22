import chess
import math
from data import *
from zobrist import *
#temporary version to get replace my subpar chess library with a professional one

#square tables and material values from https://www.chessprogramming.org/Simplified_Evaluation_Function with some tweaks

materialValue = [100, 320, 330, 500, 1000,  0]

squareValue = [
    #pawn
    [
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 10, 30, 30, 10, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5, -6, 15, 15, -6, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    ],
    #knight
    [
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 10, 10, 10,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 10, 10, 10, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-15,-30,-30,-30,-30,-15,-50
    ],
    #bishop
    [
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    ],
    #rook
    [
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
    ],
    #queen
    [
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -5,  0,  5,  5,  5,  5,  0, -5,
        0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    ],
    #king
    [
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        20, 20,  0,  0,  0,  0, 20, 20,
        20, 30, 10,  0,  0, 10, 30, 20
    ]
]

def evaluate(board):
    #even before we begin we need to check whether the game is already over
    if board.is_stalemate():
        return 0
    if board.is_checkmate():
        return -infinity
    score = 0
    #we begin by determining the part of the game
    howManyPieces = len(board.piece_map())
    partOfTheGame = 0
    if howManyPieces <= 16:
        partOfTheGame = 1
    #the main loop
    for square, piece in board.piece_map().items():
        trueSquare = (7 - (square // 8)) * 8 + (square % 8)
        if piece.color == chess.WHITE:
            #print(f"white {piece.color}, {piece.piece_type - 1}, {trueSquare}")
            score += materialValue[piece.piece_type - 1]
            score += squareValue[piece.piece_type - 1][trueSquare]
        else:
            #print(f"black {piece.color}, {piece.piece_type - 1}, {trueSquare}")
            score -= materialValue[piece.piece_type - 1]
            score -= squareValue[piece.piece_type - 1][63 - trueSquare]
    if board.turn == chess.BLACK:
        score *= -1
    score += 50
    return score

'''board = chess.Board(startingFen)
print(evaluate(board))
print(board)
legal_moves = list(board.legal_moves)
print("Legal Moves:")
for move in legal_moves:
    print(move.uci())
for square, piece in board.piece_map().items():
    print(piece.color)
    print(piece.piece_type)
    print(square)
print("test")
print(evaluate(board))'''