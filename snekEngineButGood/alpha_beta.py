import chess
from evaluate import *
from data import *
import random
from zobrist import *
import time

def alphabetaMax(board, alpha, beta, depth, hash, zobrist):
    possibleMoves = list(board.legal_moves)
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        score = 0
        if hash in zobrist.hashMap:
            score = zobrist.hashMap[hash]
        else:
            score = evaluate(board)
            zobrist.hashMap[hash] = score
        return score
        #return evaluate(board)
    bestMove = None
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move.uci())
        board.push(move)
        result = alphabetaMin(board, alpha, beta, depth + 1, newHash, zobrist)
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

def alphabetaMin(board, alpha, beta, depth, hash, zobrist):
    possibleMoves = list(board.legal_moves)
    if depth == MinMaxDepth or len(possibleMoves) == 0:
        score = 0
        if hash in zobrist.hashMap:
            score = zobrist.hashMap[hash]
        else:
            score = -evaluate(board)
            zobrist.hashMap[hash] = score
        return score
        #return -evaluate(board)
    bestMove = None
    random.shuffle(possibleMoves)
    for move in possibleMoves:
        newHash = zobrist.changeHash(board, hash, move.uci())
        board.push(move)
        result = alphabetaMax(board, alpha, beta, depth + 1, newHash, zobrist)
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
    
'''board = chess.Board(startingFen)
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
    move = alphabetaMax(board, -infinity*infinity, infinity*infinity, 0, hash, zobrist)
    print(move.uci(), flush=True)
    hash = zobrist.changeHash(board, hash, move.uci())
    board.push(move)'''