import random
from data import *
from chess_rewrite import *

class Zobrist:
    def __init__(self, seed = 21734):
        random.seed(seed)
        self.hashKeys = []
        for i in range(12 * 64 + 1):
            self.hashKeys.append(random.randint(1, infinity * infinity * infinity))
        self.hashMap = {}
    def getHash(self, board):
        hash = 0
        if board.turn == 1:
            hash ^= self.hashKeys[-1]
        for x in range(8):
            for y in range(8):
                piece = board.getPiece(x, y)
                if piece == -1: #we skip empty squares for simplicity
                    continue
                owner = board.getOwner(x, y)
                hash ^= self.hashKeys[64 * (piece + 6 * owner) + x * 8 + y]
        return hash
    def changeHash(self, board, hash, move):
        hash ^= self.hashKeys[-1]
        x1 = (int)(move[1]) - 1
        y1 = ord(move[0]) - ord('a')
        x2 = (int)(move[3]) - 1
        y2 = ord(move[2]) - ord('a')
        piece = board.getPiece(x2, y2)
        owner = board.getOwner(x2, y2)
        if piece != -1:
            hash ^= self.hashKeys[64 * (piece + 6 * owner) + x2 * 8 + y2]
        piece = board.getPiece(x1, y1)
        owner = board.getOwner(x1, y1)
        hash ^= self.hashKeys[64 * (piece + 6 * owner) + x1 * 8 + y1]
        hash ^= self.hashKeys[64 * (piece + 6 * owner) + x2 * 8 + y2]
        return hash
