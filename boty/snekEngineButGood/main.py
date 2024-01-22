import chess
from alpha_beta import *
from data import *
from zobrist import *
import sys

board = chess.Board(sys.argv[2])
zobrist = Zobrist()
hash = zobrist.getHash(board)
skip = 0
if (board.turn == chess.WHITE and sys.argv[1] == 'b') or (board.turn == chess.BLACK and sys.argv[1] == 'w'):
    skip = 1
while 1:
    if skip == 0:
        #print(board)
        zobrist.hashMap.clear()
        move = alphabetaMax(board, -infinity*infinity, infinity*infinity, 0, hash, zobrist)
        print(move.uci(), flush=True)
        hash = zobrist.changeHash(board, hash, move.uci())
        board.push(move)
        if board.is_checkmate():
            break
    #print(board)
    skip = 0
    move = input()
    move = chess.Move.from_uci(move)
    hash = zobrist.changeHash(board, hash, move.uci())
    board.push(move)
    if board.is_checkmate():
        break
exit(0)