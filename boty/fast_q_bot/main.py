import chess
import random
import sys

class Bot:
    def __init__(self):
        self.board = chess.Board()
        self.tura = False if sys.argv[1]=='b' else True #True - moja tura, False - tura przeciwnika

    def make_move(self):
        move = next(iter(self.board.legal_moves)).uci()
        print(move,flush=True)
        self.board.push(chess.Move.from_uci(move))
        self.tura = False
            

    def pass_opponent_move(self):
        move = input()
        # print(move)
        self.board.push(chess.Move.from_uci(move))
        self.tura = True
        


def run():
    bot = Bot()

    # while bot.board.is_stalemate==False and bot.board.is_checkmate==False:
    while not(bot.board.is_game_over()):
        if bot.tura:
            bot.make_move()
        else:
            bot.pass_opponent_move()


run()