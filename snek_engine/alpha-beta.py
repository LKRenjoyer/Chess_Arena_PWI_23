from chess_rewrite import *
from evaluate import *
from data import *

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

chess = Board()
chess.setToFen(startingFen)
chess.visualize()
while(1):
    move = input("make your move: ")
    print(move)
    chess.push(move)
    chess.visualize()
    response = alphabetaMax(chess, -infinity, infinity, 0)
    print(response)
    chess.push(response)
    chess.visualize()