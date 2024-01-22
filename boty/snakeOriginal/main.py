from chess_rewrite import *
from alpha_beta import *
from data import *
import sys
import multiprocessing

chess = Board()
zobrist = Zobrist()
chess.setToFen(sys.argv[2])
hash = zobrist.getHash(chess)
skip = 0
if (chess.turn == 0 and sys.argv[1] == 'b') or (chess.turn == 1 and sys.argv[1] == 'w'):
    skip = 1
depth = MinMaxDepth
while 1:
    howManyPieces = 0
    for x in range(8):
        for y in range(8):
            if(chess.getPiece(x, y) != -1):
                howManyPieces += 1
    if howManyPieces <= 10:
        depth = LateGameDepth
    if skip == 0:
        #chess.visualize()
        zobrist.hashMap.clear()
        move = alphabetaMax(chess, -infinity*infinity, infinity*infinity, 0, hash, zobrist, depth)
        print(move, flush=True)
        hash = zobrist.changeHash(chess, hash, move)
        chess.push(move)
        if len(chess.getLegalMoves()) == 0:
            break
    #chess.visualize()
    skip = 0
    move = input()
    hash = zobrist.changeHash(chess, hash, move)
    chess.push(move)
    if len(chess.getLegalMoves()) == 0:
        break
exit(0)