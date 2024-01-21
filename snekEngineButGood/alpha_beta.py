import chess
from evaluate import *
from data import *
import random

def alphabetaMax(board, alpha, beta, depth):
    possibleMoves = list(board.legal_moves)
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        return evaluate(board)
    bestMove = None
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        board.push(move)
        result = alphabetaMin(board, alpha, beta, depth + 1)
        board.pop()
        if result >= beta:
            return beta
        if result > alpha:
            alpha = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        return alpha

def alphabetaMin(board, alpha, beta, depth):
    possibleMoves = list(board.legal_moves)
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        return -evaluate(board)
    bestMove = None
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        board.push(move)
        result = alphabetaMax(board, alpha, beta, depth + 1)
        board.pop()
        if result <= alpha:
            return alpha
        if result < beta:
            beta = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        return beta
    
board = chess.Board(startingFen)
while 1:
    print(board)
    move = input()
    print(move)
    move = chess.Move.from_uci(move)
    board.push(move)
    print(board)
    move = alphabetaMax(board, -infinity, infinity, 0)
    print(move, flush=True)
    board.push(move)