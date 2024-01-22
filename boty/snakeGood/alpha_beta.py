import chess
from evaluate import *
from data import *
import random
from zobrist import *
import time

def alphabetaMax(board, alpha, beta, depth, hash, zobrist, targetDepth):
    if hash in zobrist.hashMap:
        return zobrist.hashMap[hash]
    possibleMoves = list(board.legal_moves)
    if depth == targetDepth:
        return evaluate(board)
    if len(possibleMoves) == 0:
        return evaluate(board) * (targetDepth - depth)
        '''score = 0
        if hash in zobrist.hashMap:
            score = zobrist.hashMap[hash]
        else:
            score = evaluate(board)
            zobrist.hashMap[hash] = score
        return score
        return evaluate(board)'''
    bestMove = None
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move.uci())
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
    possibleMoves = list(board.legal_moves)
    if depth == targetDepth:
        return -evaluate(board)
    if len(possibleMoves) == 0:
        return -evaluate(board) * (targetDepth - depth)
        '''score = 0
        if hash in zobrist.hashMap:
            score = zobrist.hashMap[hash]
        else:
            score = -evaluate(board)
            zobrist.hashMap[hash] = score
        return score
        return -evaluate(board)'''
    bestMove = None
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move.uci())
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
    
'''board = chess.Board("4k3/1r1bbp2/1p1p3p/2p3p1/8/6P1/1P1P1P1P/1RN1K3 w - - 0 1")
zobrist = Zobrist()
hash = zobrist.getHash(board)
while 1:
    print(board)
    move = input()
    print(move)
    move = chess.Move.from_uci(move)
    hash = zobrist.changeHash(board, hash, move.uci())
    board.push(move)
    print(board)
    move = alphabetaMax(board, -infinity*infinity, infinity*infinity, 0, hash, zobrist, 6)
    print(move.uci(), flush=True)
    hash = zobrist.changeHash(board, hash, move.uci())
    board.push(move)'''