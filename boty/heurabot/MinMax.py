import chess
from functools import partial
from random import randint, seed, shuffle
from itertools import chain
from data import *
from time import perf_counter

seed(692137)
hashtable = [randint(1,2**64) for i in range(12*64+3)]
currentHash = 0

def genHash(board):
    hash = 0
    if board.turn:
        hash ^= hashtable[-1]
    for square, piece in board.piece_map().items():
        hash ^= hashtable[(6*piece.color+piece.piece_type-1)+12*square]
    return hash

def nextHash(board, move:chess.Move, hash):
    hash ^= hashtable[-1]
    piece = board.piece_at(move.to_square)
    if piece is not None:
        hash ^= hashtable[(6*piece.color+piece.piece_type-1)+12*move.to_square]
    piece = board.piece_at(move.from_square)
    hash ^= hashtable[(6*piece.color+piece.piece_type-1)+12*move.from_square]
    hash ^= hashtable[(6*piece.color+piece.piece_type-1)+12*move.to_square]
    return hash

piece_values = {chess.Piece.from_symbol(symbol):value for symbol, value in zip('PNBRQKpnbrqk', (100,325,350,500,1000,1000000000,-100,-325,-350,-500,-1000,-100000000))}

boosts = [0,0]
evaluated = {}
searched = {}

def evaluate(board:chess.Board, hash):
    if hash in evaluated:
        return evaluated[hash]
    result = board.outcome()
    if result is not None:
        if result.winner is None:
            return 0
        if result.winner:
            return float('inf')
        else:
            return float('-inf')
    material_bonus = 0
    position_bonus = 0
    for tile, piece in board.piece_map().items():
        material_bonus+=piece_values[piece]
        if piece.color:
            position_bonus+=tables[piece.piece_type-1][8*(7-tile//8)+tile%8]
        else:
            position_bonus-=tables[piece.piece_type-1][tile]
    score = material_bonus+position_bonus
    if not board.turn:
        score*=-1
    evaluated[hash]=score
    return score

def move_eval(board:chess.Board, hash, move):
    return board.is_capture(move)*2-board.is_attacked_by(not board.turn, move.to_square)

total = [0,0]

def AlphaBetaSearch(board, max_depth, hash, alpha=float('-inf'), beta=float('inf'), maximize=True, start_from=None):
    time = perf_counter()
    legal_moves = list(board.legal_moves)
    # shuffle(legal_moves)
    # legal_moves.sort(key=lambda move:move_eval(board, hash, move))
    total[0] += perf_counter()-time

    if max_depth <= 0 or len(legal_moves)==0:
        time=perf_counter()
        score = evaluate(board, hash)
        total[1]+=perf_counter()-time
        return score, None
    if hash in searched:
        boosts[0]+=1
        return searched[hash]
    
    if max_depth>1:
        board.push(chess.Move.null())
        score = -AlphaBetaSearch(board, max_depth-2, hash, -beta, -alpha, False)[0]
        board.pop()
        if score >= beta:
            boosts[1]+=1
            return score, None
        
    best_move=None
    best_score = float('-inf')
    for move in (chain((start_from,), legal_moves) if start_from else legal_moves):
        new_hash = nextHash(board, move, hash)
        board.push(move)
        score = -AlphaBetaSearch(board, max_depth-1, new_hash, -beta, -alpha, False)[0]
        board.pop()
        if score >= beta:
            boosts[1]+=1
            return score, move
        if score>best_score:
            best_score=score
            best_move=move
            if score > alpha:
                alpha = score
    searched[hash]=alpha,best_move
    return alpha, best_move

def get_best_move(board):
    max_depth = 4

    boosts[0]=boosts[1]=total[0]=total[1]=0
    value, best_move = AlphaBetaSearch(board, 1, genHash(board))
    print(1,boosts, len(evaluated), total, sum(total), flush=True)
    searched.clear()
    # evaluated.clear()
    # print(value)
    for i in range(2, max_depth+1):
        # boosts[0]=boosts[1]=total[0]=total[1]=0
        value, best_move = AlphaBetaSearch(board, i, genHash(board), start_from=best_move)
        print(i,boosts, len(evaluated), total, sum(total), flush=True)
        searched.clear()
        # lwindow = 100
        # rwindow = 100
        # while True:
        #     # alpha = value-lwindow
        #     # beta = value+rwindow
        #     new_value, best_move = AlphaBetaSearch(board, i, genHash(board), alpha, beta)
        #     if new_value<alpha:
        #         lwindow*=2
        #         print('recalculation')
        #     elif new_value>beta:
        #         rwindow*=2
        #         print('recalculation')
        #     else:
        #         break
        # value=new_value
    # print(alpha, beta, value, flush=True)
    searched.clear()
    return best_move
