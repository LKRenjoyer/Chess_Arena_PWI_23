import chess
import random

class Bot:
    def __init__(self):
        self.board = chess.Board()
        self.tura = True #True - moja tura, False - tura przeciwnika

    def get_move(self):
        with open('komunikacja.txt','a') as file:
            # legal_moves_for_white = self.board.legal_moves
            # legal_moves_for_white_list = [move for move in legal_moves_for_white if self.board.piece_at(move.from_square).color == chess.WHITE]
            # print("1.",legal_moves_for_white_list,"2.",legal_moves_for_white)
            ruch = random.choice(list(move.uci() for move in self.board.legal_moves))
            print(f'bot {ruch}')
            file.write(f'\nbot {ruch}')
            file.flush()
        # print(f'bot {ruch}') 
        self.tura = False
        # return random.choice(list(move.uci() for move in self.board.legal_moves))
            

    def pass_opponent_move(self):
        invalid_ruch = True
        # zm = 0
        while invalid_ruch:
            with open('komunikacja.txt','r') as file:
                move = file.read()
            move = move.split()
            # print(move)
            # zm+=1
            # if zm == 100000:
            #     break
            if len(move)>2 and move[-2]=='client':
                invalid_ruch = False
                move = move[-1]

        # print(move)
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