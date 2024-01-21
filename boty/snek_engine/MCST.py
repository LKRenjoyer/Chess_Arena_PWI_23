from chess_rewrite import Board as game
import math
import random

class Node:
    def __init__(self, chess, parameters, move, parent=None):
        self.chess = chess
        self.parameters = parameters
        self.move = move
        self.parent = parent
        self.children = []
        self.visits = 0
        self.score = 0
        self.legal_moves = self.chess.getLegalMoves()
    def getUCT(self):
        return (self.score / self.visits) + self.parameters['C'] * math.sqrt(math.log(self.parent.visits) / self.visits)

class MCTS:
    def __init__(self, chess, parameters, root):
        self.chess = chess
        self.parameters = parameters
        self.root = root
    def moveForward(self, move):
        self.chess.push(move)
    def moveBack(self):
        self.chess.pop()
    def select(self, node):
        if len(node.legal_moves) > 0:
            return node
        bestChild = None
        bestUCT = -math.inf
        for child in node.children:
            childUCT = child.getUCT()
            if childUCT > bestUCT:
                bestUCT = childUCT
                bestChild = child
        self.moveForward(bestChild.move)
        return self.select(bestChild)
    def expand(self, node):
        move = random.choice(node.legal_moves)
        node.legal_moves.remove(move)
        self.moveForward(self, move)
        newChild = Node(self.chess, move, node)
        node.children.append(newChild)
        return newChild
    def simulate(self, node):
        pass
    def backPropagate(self, node, score):
        node.visits += 1
        node.score += score
        if node == self.root:
            return
        self.moveBack()
        self.backPropagate(self, node.parent, score)
    def search(self):
        leaf = self.select(self.root)
        newNode = self.expand(leaf)
        self.simulate(newNode)
        self.backPropagate(newNode)

