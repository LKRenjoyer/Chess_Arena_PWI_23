import chess
from functools import partial
from random import randint, seed, shuffle
from data import *

seed(213769)
hashtable = [randint(1,2**64) for i in range(12*64+1)]
currentHash = 0

def genHash(board):
    hash = 0
    if board.turn:
        hash ^= hashtable[-1]
    for square, piece in board.piece_map().items():
        hash ^= hashtable[(6*piece.color+piece.piece_type-1)*(square+1)]
    return hash

def nextHash(board, move:chess.Move, hash):
    hash ^= hashtable[-1]
    piece = board.piece_at(move.to_square)
    if piece is not None:
        hash ^= hashtable[(6*piece.color+piece.piece_type-1)*(move.to_square+1)]
    piece = board.piece_at(move.from_square)
    hash ^= hashtable[(6*piece.color+piece.piece_type-1)*(move.from_square+1)]
    hash ^= hashtable[(6*piece.color+piece.piece_type-1)*(move.to_square+1)]
    return hash

piece_values = {chess.Piece.from_symbol(symbol):value for symbol, value in zip('PNBRQKpnbrqk', (100,325,350,500,1000,0,-100,-325,-350,-500,-1000,0))}

evaluated = {}

def evaluate(board:chess.Board):
    fen = board.fen()
    if fen in evaluated:
        return evaluated[fen]
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
    board.push(chess.Move.null())
    opponent_moves = len(list(board.generate_legal_moves()))
    board.pop()
    mobility_bonus = (1 if board.turn else -1)*(len(list(board.legal_moves))-opponent_moves)
    score = material_bonus+position_bonus+mobility_bonus
    if not board.turn:
        score*=-1
    evaluated[fen]=score
    return score

def move_eval(board:chess.Board, move):
    return board.is_capture(move)

def AlphaBetaSearch(board, max_depth, hash, depth=0, alpha=float('-inf'), beta=float('inf'), maximize=True):
    legal_moves = list(board.legal_moves)
    shuffle(legal_moves)
    # legal_moves.sort(key=partial(move_eval, board))
    if depth == max_depth or len(legal_moves)==0:
        return evaluate(board)
    if hash in evaluated:
        return evaluated[hash]
    best_move=legal_moves[0]
    for move in legal_moves:
        new_hash = nextHash(board, move, hash)
        board.push(move)
        score = -AlphaBetaSearch(board, max_depth, new_hash, depth+1, -beta, -alpha, False)
        board.pop()
        if score >= beta:
            return beta
        if score > alpha:
            alpha = score
            best_move=move
    if depth == 0:
        return best_move
    evaluated[hash]=alpha
    return alpha

def get_best_move(board):
    global evaluated
    evaluated={}
    return AlphaBetaSearch(board, 4, genHash(board))