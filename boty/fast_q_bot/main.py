import chess
import random
import sys

class Bot:
    def __init__(self):
        self.board = chess.Board()
        if sys.argv[1] == 'b':
            self.data = ['e7e5','d8h4']
        else:
            self.data = ['f2f4','g2g4']
        self.tura = False if sys.argv[1]=='b' else True #True - moja tura, False - tura przeciwnika
        self.turn_num = 0

    def make_move(self):
        print(self.data[self.turn_num],flush=True)
        self.turn_num+=1
        self.tura = False
            

    def pass_opponent_move(self):
        move = input()
        self.tura = True
        


def run():
    bot = Bot()

    # while bot.board.is_stalemate==False and bot.board.is_checkmate==False:
    while bot.turn_num <= 1:
        if bot.tura:
            bot.make_move()
        else:
            bot.pass_opponent_move()


run()