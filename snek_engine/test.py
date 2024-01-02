# testing utiity

import chess_rewrite, chess
import os
from functools import partial

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

b1 = chess_rewrite.Board()
b2 = chess.Board()

fens = [chess_rewrite.startingFen, "4k3/P7/2PP2Rp/4pK2/b5nP/PPb1p3/8/4B3 w - - 0 1"]
with open(path("random200_positions.txt"), "r") as f:
    new_fens = f.read().splitlines()[::3]
new_fens = [fen[5:] for fen in new_fens]
fens.extend(new_fens)

for fen in fens:
    print(fen)
    b1.setToFen(fen)
    b2.set_fen(fen)
    m1 = sorted(b1.getLegalMoves())
    m2 = sorted(move.uci() for move in b2.legal_moves)
    print(m1==m2)