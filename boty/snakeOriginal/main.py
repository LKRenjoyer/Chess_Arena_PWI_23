from chess_rewrite import *
from alpha_beta import *
from data import *
import sys
import multiprocessing

chess = Board()
chess.setToFen(sys.argv[2])
skip = 0
if (chess.turn == 0 and sys.argv[1] == 'b') or (chess.turn == 1 and sys.argv[1] == 'w'):
    skip = 1
while 1:
    if skip == 0:
        move = alphabetaMax(chess, -infinity*infinity, infinity*infinity, 0)
        print(move, flush=True)
        chess.push(move)
        if len(chess.getLegalMoves()) == 0:
            break
    skip = 0
    move = input()
    chess.push(move)
    if len(chess.getLegalMoves()) == 0:
        break