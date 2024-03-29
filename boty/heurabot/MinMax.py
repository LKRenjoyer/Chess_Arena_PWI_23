import chess
from random import randint, seed
from itertools import chain
from data import *

global_max_depth = 2

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

piece_values = {chess.Piece.from_symbol(symbol):value for symbol, value in zip('PNBRQKpnbrqk', (100,325,350,500,1000,0,-100,-325,-350,-500,-1000,0))}

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
        if result.winner == board.turn:
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

def AlphaBetaSearch(board, max_depth, hash, alpha=float('-inf'), beta=float('inf'), maximize=True, start_from=None):
    legal_moves = list(board.legal_moves)

    if max_depth <= 0 or len(legal_moves)==0:
        score = evaluate(board, hash)
        return score, None
    if hash in searched:
        return searched[hash]
    
    legal_moves = chain((start_from,), legal_moves) if start_from else legal_moves
    best_score=float('-inf')
    for move in legal_moves:
        new_hash = nextHash(board, move, hash)
        board.push(move)
        score = -AlphaBetaSearch(board, max_depth-1, new_hash, -beta, -alpha, False)[0]
        board.pop()
        if score >= beta:
            return score, move
        if score>best_score:
            best_score=score
            best_move=move
            if score > alpha:
                alpha = score
    return alpha, best_move

def get_best_move(board):
    value, best_move = AlphaBetaSearch(board, 2, genHash(board))
    searched.clear()
    for i in range(3, global_max_depth+1):
        value, best_move = AlphaBetaSearch(board, i, genHash(board), start_from=best_move)
        searched.clear()
    return best_move
