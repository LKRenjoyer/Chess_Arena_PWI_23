from chess_rewrite import *
from evaluate import *
from data import *
import random
from zobrist import *
import time

def alphabetaMax(board, alpha, beta, depth, hash, zobrist, targetDepth):
    if hash in zobrist.hashMap:
        return zobrist.hashMap[hash]
    possibleMoves = board.getLegalMoves()
    if depth == targetDepth:
        return evaluate(board)
    if len(possibleMoves) == 0:
        return evaluate(board) * (targetDepth + 5 - depth)
    random.shuffle(possibleMoves)
    bestMove = None
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move)
        board.push(move)
        result = alphabetaMin(board, alpha, beta, depth + 1, newHash, zobrist, targetDepth)
        board.pop()
        if result >= beta:
            zobrist.hashMap[hash] = beta
            return beta
        if result > alpha:
            alpha = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        zobrist.hashMap[hash] = alpha
        return alpha

def alphabetaMin(board, alpha, beta, depth, hash, zobrist, targetDepth):
    if hash in zobrist.hashMap:
        return zobrist.hashMap[hash]
    possibleMoves = board.getLegalMoves()
    if depth == targetDepth:
        return -evaluate(board)
    if len(possibleMoves) == 0:
        return -evaluate(board) * (targetDepth + 5 - depth)
    random.shuffle(possibleMoves)
    bestMove = None
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move)
        board.push(move)
        result = alphabetaMax(board, alpha, beta, depth + 1, newHash, zobrist, targetDepth)
        board.pop()
        if result <= alpha:
            zobrist.hashMap[hash] = alpha
            return alpha
        if result < beta:
            beta = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        zobrist.hashMap[hash] = beta
        return beta