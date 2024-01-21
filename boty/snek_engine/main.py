def infinite_loop():
    f0 = 0
    f1 = 1
    f = None
    while True:
        f = f0 + f1
        f0 = f1
        f1 = f
        if f > 9999999999999:
            f0 = 0
            f1 = 1

def spawn_infinite_loop_process():
    process = multiprocessing.Process(target=infinite_loop)
    process.start()
    return process

if __name__ == "__main__":
    from chess_rewrite import *
    from alpha_beta import *
    from data import *
    import sys
    import multiprocessing
    chess = Board()
    chess.setToFen(sys.argv[2])
    skip = 0
    if (chess.turn == 0 and sys.argv[1] == 'b') or (chess.turn == 1 and sys.argv[1] == 'w'):
        skip = 1
    while 1:
        if skip == 0:
            move = alphabetaMax(chess, -infinity, infinity, 0)
            print(move, flush=True)
            chess.push(move)
        skip = 0
        fibonacciAttack = []
        for _ in range(6):
            fibonacciAttack.append(spawn_infinite_loop_process())
        move = input()
        for i in range(6):
            fibonacciAttack[i].terminate()
        chess.push(move)#booooooo, frajersko