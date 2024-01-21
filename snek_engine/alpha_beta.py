from chess_rewrite import *
from evaluate import *
from data import *
import sys

def alphabetaMax(state, alpha, beta, depth):
    possibleMoves = state.getLegalMoves()
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        return evaluate(state)
    bestMove = None
    for move in possibleMoves:
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
    for move in possibleMoves:
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

chess = Board(sys.argv[2])
skip = 0
if (chess.turn == 0 and sys.argv[1] == 'b') or (chess.turn == 1 and sys.argv[1] == 'w'):
    skip = 1
while 1:
    if skip == 0:
        move = alphabetaMax(chess, -infinity, infinity, 0)
        print(move)
        chess.push(move)
    skip = 0
    move = input()
    chess.push(move)