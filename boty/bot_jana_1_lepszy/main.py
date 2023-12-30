import chess
import random
import sys


class Bot:
    def __init__(self):
        self.board = chess.Board()
        self.tura = False if sys.argv[1]=='b' else True #True - moja tura, False - tura przeciwnika

    def check_stalemate(self, move):
        self.board.push(move)
        ret = self.board.is_stalemate()
        self.board.pop()
        return not ret

    def make_move(self):
        move = None
        l_moves = list(filter(self.check_stalemate, self.board.legal_moves))
        if not l_moves:
            l_moves = self.board.legal_moves
        try:
            move = random.choice([move.uci() for move in l_moves if self.board.piece_at(move.to_square) is not None])
        except IndexError:
            try:
                move = random.choice([move.uci() for move in l_moves if self.board.piece_at(move.from_square).symbol().lower()=='p'
                                    and len(move.uci())==5 and move.uci()[-1]=="q"])
            except IndexError:
                try:
                    move = random.choice(list(move.uci() for move in l_moves if self.board.piece_at(move.from_square).symbol().lower()=='p'))
                except IndexError:
                    move = random.choice(list(move.uci() for move in l_moves))
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
    while not(bot.board.is_game_over()):
        if bot.tura:
            bot.make_move()
        else:
            bot.pass_opponent_move()


run()