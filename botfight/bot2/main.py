import chess
import random
import sys

class Bot:
    def __init__(self):
        self.board = chess.Board()
        self.tura = False if sys.argv[1]=='b' else True #True - moja tura, False - tura przeciwnika
        self.licznik = 2

    def make_move(self):
        move = None
        while move==None:
            move = random.choice(list(move.uci() for move in self.board.legal_moves))
        print(move)
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
    while bot.board.is_stalemate()==False and bot.board.is_checkmate()==False:
        if bot.tura:
            bot.make_move()
        else:
            bot.pass_opponent_move()


run()