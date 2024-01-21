import chess

piece_values = {chess.Piece.from_symbol(symbol):value for symbol, value in zip('PNBRQKpnbrqk', (1,3,3,5,9,0,-1,-3,-3,-5,-9,0))}

def evaluate(board:chess.Board):
    result = board.outcome()
    if result is not None:
        if result.winner is None:
            return 0
        if result.winner:
            return float('inf')
        else:
            return float('-inf')
    material_bonus = 0
    for tile, piece in board.piece_map().items():
        material_bonus+=piece_values[piece]
    mobility_bonus = 0.01*len(list(board.legal_moves))
    score = material_bonus+mobility_bonus
    return score

def AlphaBetaSearch(board, max_depth, depth=0, alpha=float('-inf'), beta=float('inf'), maximize=True):
    legal_moves = list(board.legal_moves)
    if depth == max_depth or len(legal_moves)==0:
        return evaluate(board)
    best_move=legal_moves[0]
    value = float('-inf') if maximize else float('inf')
    for move in legal_moves:
        board.push(move)
        if maximize:
            value = max(value, AlphaBetaSearch(board, max_depth, depth+1, alpha, beta, False))
            if value > beta:
                board.pop()
                return value
            if value > alpha:
                alpha = value
                best_move = move
        else:
            value = min(value, AlphaBetaSearch(board, max_depth, depth+1, alpha, beta, True))
            if value < alpha:
                board.pop()
                return value
            if value<beta:
                beta = value
                best_move = move
        board.pop()
    if depth == 0:
        return best_move
    return value

def get_best_move(board, maximize):
    return AlphaBetaSearch(board, max_depth=2, maximize=maximize)