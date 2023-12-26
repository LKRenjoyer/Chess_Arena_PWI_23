import chess
import random

class Bot:
    def __init__(self):
        self.board = chess.Board()
        self.tura = False #True - moja tura, False - tura przeciwnika
        self.licznik=3

    def get_move(self):
        with open('komunikacja.txt','a') as file:
            # legal_moves_for_black = self.board.legal_moves
            # legal_moves_for_black_list = [move for move in legal_moves_for_black if self.board.piece_at(move.from_square).color == chess.BLACK]
            # print(legal_moves_for_black_list)
            ruch = random.choice(list(move.uci() for move in self.board.legal_moves))
            print(f'client {ruch} {self.licznik}')
            file.write(f'\nclient {ruch} {self.licznik}')
            file.flush()
            self.licznik+=2
        # print(f'client {ruch}') 
        self.board.push(chess.Move.from_uci(ruch))
        self.tura = False
        # return random.choice(list(move.uci() for move in self.board.legal_moves))
            

    def pass_opponent_move(self):
        invalid_ruch = True
        while invalid_ruch:
            with open('komunikacja.txt','r') as file:
                move = file.read()
            move = move.split()
            # print(move)
            if len(move)>2 and move[-3]=='bot' and int(move[-1])==self.licznik-1:
                invalid_ruch = False
                move = move[-2]
            

        self.board.push(chess.Move.from_uci(move))
        self.tura = True
        


def run():
    bot = Bot()

    # while bot.board.is_stalemate==False and bot.board.is_checkmate==False:
    while bot.board.is_stalemate()==False and bot.board.is_checkmate()==False:
        if bot.tura:
            bot.get_move()
        else:
            bot.pass_opponent_move()




run()