import chess
import random
import sys
#zapozyczone z bot_jana_2 
global aktu
class Bot:
    def __init__(self):
        self.board = chess.Board()
        #self.tura = False if sys.argv[1]=='b' else True #True - moja tura, False - tura przeciwnika

    def make_move(self):
        move = None
        while move==None:
            move = random.choice(list(move.uci() for move in self.board.legal_moves))
        self.board.push(chess.Move.from_uci(move))
        self.tura = False
        print(move)
        
            

    def pass_opponent_move(self):
        global aktu
        move = input()
        if(move != "a1a1"):
        # print(move)
            self.board.push(chess.Move.from_uci(move))
            self.tura = True
        aktu = move
        
def initialize_board_from_fen(fen):
    try:
        board = chess.Board(fen)
        return board
    except ValueError as e:
        print(f"Błąd: Nieprawidłowy FEN. {e}")
        sys.exit(5)

def run(): 
    global aktu
    bot = Bot()
    begin = input()   
    if begin == "isready?":
        print(begin[2:7])
    else: 
        exit(1)
    value = input()

    if value[0:7] == "color: ":
        if value[7:] in ["white", "black"]: 
            value = value[7:12]  
            print(value)
        else: 
            exit(2)
    else: 
        exit(3)
    fen = input() 
    if fen[0:5] == "FEN: ": 
        fen = fen[5:]
    else:
        exit(4)
    bot.board = initialize_board_from_fen(fen)
    print("understood") 
    if (value=="white" and bot.board.turn == chess.WHITE) or (value=="black" and bot.board.turn == chess.BLACK): 
        bot.tura = True 
    else:
        bot.tura = False
    # while bot.board.is_stalemate==False and bot.board.is_checkmate==False:
    while not(bot.board.is_game_over()):
        if bot.tura:
            bot.make_move()
        else:
            bot.pass_opponent_move() 
            if aktu == "a1a1": 
                break


run()