import random
from data import *
import chess

class Zobrist:
    def __init__(self, seed = 21734):
        random.seed(seed)
        self.hashKeys = []
        for i in range(12 * 64 + 1):
            self.hashKeys.append(random.randint(1, infinity * infinity * infinity))
        self.hashMap = {}
    def getHash(self, board):
        hash = 0
        if board.turn == chess.BLACK:
            hash ^= self.hashKeys[-1]
        for square, piece in board.piece_map().items():
            hash ^= self.hashKeys[64 * (piece.piece_type - 1 + 6 * piece.color) + square]
        return hash
    def changeHash(self, board, hash, move):
        hash ^= self.hashKeys[-1]
        square1 = ((int)(move[1]) - 1) * 8 + (ord(move[0]) - ord('a'))
        square2 = ((int)(move[3]) - 1) * 8 + (ord(move[2]) - ord('a'))
        piece = board.piece_at(square2)
        if piece != None:
            hash ^= self.hashKeys[64 * (piece.piece_type - 1 + 6 * piece.color) + square2]
        piece = board.piece_at(square1)
        hash ^= self.hashKeys[64 * (piece.piece_type - 1 + 6 * piece.color) + square1]
        hash ^= self.hashKeys[64 * (piece.piece_type - 1 + 6 * piece.color) + square2]
        return hash

'''chess = chess.Board(startingFen)
print(chess.piece_at(3))
print(chess)
for square, piece in chess.piece_map().items():
    print(f"{piece}, {square}")
for i in range(64):
    piece = chess.piece_at(i)
    print(piece)
    if piece != None:
        print(piece.piece_type)
    else:
        print("None")'''
