import chess
import random

class Bot:
    def __init__(self):
        pass
        self.board = chess.Board()

    def get_move(self):
        return random.choice(list(move.uci() for move in self.board.legal_moves))

    def pass_opponent_move(self,move):
        self.board.push(chess.Move.from_uci(move))
        


def run():
    bot = Bot()

    while bot.board.is_stalemate==False and bot.board.is_checkmate==False:
        

run()

# print("Jestem main2")

# try:
#     data = input()
# except:
#     print("Nie dziala main2")
#     exit(1)

# print(data + " zadzialalo")