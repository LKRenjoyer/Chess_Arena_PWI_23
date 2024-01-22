import chess
import math
from data import *
from zobrist import *

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

matingGrid = [
    -391, -381, -371, -361, -360, -370, -380, -390,
    -380, -150, -130, -100, -100, -130, -150, -390,
    -370, -130,    0,    0,    0,    0, -130, -370,
    -360, -100,    0,    0,    0,    0, -100, -360,
    -360, -100,    0,    0,    0,    0, -100, -360,
    -370, -130,    0,    0,    0,    0, -130, -370,
    -380, -150, -130, -100, -100, -130, -150, -380,
    -390, -380, -370, -360, -361, -371, -381, -391
]

def evaluate(board):
    #even before we begin we need to check whether the game is already over
    if board.is_stalemate():
        return 0
    if board.is_checkmate():
        return -infinity
    score = 0
    howManyPieces = len(board.piece_map())
    if howManyPieces > 6:
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
    else:
        #mating loop
        whiteKingX = 0
        whiteKingY = 0
        blackKingX = 0
        blackKingY = 0
        for square, piece in board.piece_map().items():
            trueSquare = (7 - (square // 8)) * 8 + (square % 8)
            if piece.color == chess.WHITE:
                score += materialValue[piece.piece_type - 1] * 20
                if piece.piece_type == 6:
                    score += matingGrid[trueSquare]
                    whiteKingX = trueSquare // 8
                    whiteKingY = trueSquare % 8
            else:
                score -= materialValue[piece.piece_type - 1] * 20
                if piece.piece_type == 6:
                    score -= matingGrid[trueSquare]
                    blackKingX = trueSquare // 8
                    blackKingY = trueSquare % 8
        if board.turn == chess.WHITE:
            score -= 20 * (abs(whiteKingX - blackKingX) + abs(whiteKingY - blackKingY))
        else:
            score += 20 * (abs(whiteKingX - blackKingX) + abs(whiteKingY - blackKingY))
    
    if board.turn == chess.BLACK:
        score *= -1
    score += 50 # bonus for having a tempo advantage
    return score

'''board = chess.Board("5k2/Q7/8/8/8/4K3/8/8 w - - 0 1")
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