from chess_rewrite import *
from evaluate import *
from data import *
import sys
import random

def alphabetaMax(state, alpha, beta, depth):
    possibleMoves = state.getLegalMoves()
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        return evaluate(state)
    bestMove = None
    ile = 0
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        ile += 1
        if ile > 7:
            break
        state.push(move)
        result = alphabetaMin(state, alpha, beta, depth + 1)
        state.pop()
        if result >= beta:
            return beta
        if result > alpha:
            alpha = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        return alpha

def alphabetaMin(state, alpha, beta, depth):
    possibleMoves = state.getLegalMoves()
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        return -evaluate(state)
    bestMove = None
    ile = 0
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        ile += 1
        if ile > 20:
            break
        state.push(move)
        result = alphabetaMax(state, alpha, beta, depth + 1)
        state.pop()
        if result <= alpha:
            return alpha
        if result < beta:
            beta = result
            bestMove = move
    if depth == 0:
        return bestMove
    else:
        return beta