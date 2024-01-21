import chess
from MinMax import *
import sys
from sys import argv
from contextlib import redirect_stdout

board = chess.Board(fen=argv[2])

if (argv[1]=='b' and board.turn) or (argv[1]=='w' and not board.turn):
    move=input()
    board.push_uci(move)

class Log:
    def __init__(self, file):
        self.file=open(file, 'w')
    def write(self, data):
        self.file.write(data)
        # sys.__stdout__.write(data)
    def flush(self):
        self.file.flush()
        # sys.__stdout__.flush()
    def __del__(self):
        self.file.close()

log = Log('test.txt')

while not board.is_game_over():
    move = get_best_move(board, argv[1]=='w')
    with redirect_stdout(log):
        print(move)
    board.push(move)
    print(move, flush=True)
    if board.is_game_over():
        break
    move = input()
    board.push_uci(move)
