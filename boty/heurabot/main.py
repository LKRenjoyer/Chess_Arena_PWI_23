import chess
from MinMax import *
import sys
from sys import argv
from contextlib import redirect_stdout
from time import perf_counter

board = chess.Board(fen=argv[2])

# before = perf_counter()
# for i in range(29474):
#     # l = []
#     # l.extend(board.legal_moves)
#     # for _ in board.legal_moves:...
#     list(board.legal_moves).sort(key=lambda x:x.from_square)
#     board.push_uci('e2e4')
#     board.pop()
# time = perf_counter()-before
# print(time)

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

log = Log(f'test_{argv[1]}.txt')

while not board.is_game_over():
    with redirect_stdout(log):
        move = get_best_move(board)
    board.push(move)
    print(move, flush=True)
    # if board.is_game_over():
    #     break
    move = input()
    board.push_uci(move)
