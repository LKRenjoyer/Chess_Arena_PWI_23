from chess_rewrite import *
from evaluate import *
from data import *
import math


#the max part of min-max, maximizing from the perspective of the bot
def maxDFS(state, depth):
    possibleMoves = state.getLegalMoves() #we get a list of legal moves
    if depth == 0 or len(possibleMoves) == 0: #if we reached the desired depth we evaluate the position. If the game is over we do so as well
        return evaluate(state) * (1 + -2 * state.turn) #evaluation is always from white's perspective hence we need to account for enigine's color
    score = -math.inf
    bestMove = None
    for move in possibleMoves: #for every possible move
        state.push(move) #we perform it
        result = minDFS(state, depth) #evaluate the resulting position
        state.pop() #undo it
        if result > score: #compare the result of that move to the current best
            score = result
            bestMove = move
    if depth == MinMaxDepth: #if this is the root of the min-max tree we return the best move found
        return bestMove
    else: #else we are concerned only about the score
        return score
    
#the min part of min-max, maximizing from the perspective of the enemy of our bot
def minDFS(state, depth):
    possibleMoves = state.getLegalMoves() #we get a list of legal moves
    if len(possibleMoves) == 0: #if the game is over we are unable to go deeper
        return evaluate(state) * (1 + -2 * (1 - state.turn)) #if evaluation is called during an enemy's turn we need to reverse the active player role
    score = math.inf
    for move in possibleMoves: #for every possible move
        state.push(move) #we perform it
        result = maxDFS(state, depth - 1) #evaluate the resulting position
        state.pop() #undo it
        if result < score: #compare the result of that move to the current best
            score = result
    return score

'''chess = Board()
chess.setToFen(startingFen)
while(1):
    move = input("make your move: ")
    chess.push(move)
    response = maxDFS(chess, MinMaxDepth)
    print(f"my response: {response}")
    chess.push(response)'''

eksperyment = []
for _ in eksperyment:
    print(_)