from chess_rewrite import *
import math

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

def evaluate(state):
    #even before we begin we need to check whether the game is already over
    if len(state.getLegalMoves()) == 0:
        if state.isInCheck(state.turn):
            return -infinity
        else:
            return 0
    score = 0
    #we begin by determining the part of the game
    #we do so by adding the total number of pieces on board, counting major pieces as double
    howManyPieces = 0
    for x in range(8):
        for y in range(8):
            piece = state.getPiece(x, y)
            if piece >= 0:
                howManyPieces += 1
            if piece > 0:
                howManyPieces += 1
    if howManyPieces > 6:
        #the main loop
        for x in range(8):
            for y in range(8):
                piece = state.getPiece(x, y)
                if piece == -1: #we skip empty squares for simplicity
                    continue
                owner = state.getOwner(x, y)
                if owner == 0:
                    score += materialValue[piece]
                    score += squareValue[piece][x * 8 + y]
                else:
                    score -= materialValue[piece]
                    score -= squareValue[piece][(7 - x) * 8 + 7 - y]
    else:
        #mating loop
        whiteKingX = 0
        whiteKingY = 0
        blackKingX = 0
        blackKingY = 0
        for x in range(8):
            for y in range(8):
                piece = state.getPiece(x, y)
                if piece == -1: #we skip empty squares for simplicity
                    continue
                owner = state.getOwner(x, y)
                if owner == 0:
                    score += materialValue[piece] * 20
                    if piece == 5:
                        score += matingGrid[x * 8 + y]
                        whiteKingX = x
                        whiteKingY = y
                else:
                    score -= materialValue[piece] * 20
                    if piece == 5:
                        score -= matingGrid[x * 8 + y]
                        blackKingX = x
                        blackKingY = y
        if state.turn == 0:
            score -= 20 * (abs(whiteKingX - blackKingX) + abs(whiteKingY - blackKingY))
        else:
            score += 20 * (abs(whiteKingX - blackKingX) + abs(whiteKingY - blackKingY))


    if state.turn == 1:
        score *= -1
    score += 50 # bonus for having a tempo advantage
    return score
