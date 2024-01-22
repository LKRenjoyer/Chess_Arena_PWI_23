import chess
from MinMax import *
import sys
from sys import argv

board = chess.Board(fen=argv[2])

if (argv[1]=='b' and board.turn) or (argv[1]=='w' and not board.turn):
    move=input()
    board.push_uci(move)

while not board.is_game_over():
    move = get_best_move(board)
    board.push(move)
    print(move, flush=True)
    # if board.is_game_over():
    #     break
    move = input()
    board.push_uci(move)
