FenToNum = {'p': 0, 'n': 1, 'b': 2, 'r': 3, 'q':4, 'k': 5}
NumToFen = {0: 'p', 1: 'n', 2: 'b', 3: 'r', 4:'q', 5: 'k'}
CastlingConversion = {'K': 0, 'Q': 1, 'k': 2, 'q':3}
CastlingDeconversion = {0: "K", 1: "Q", 2: "k", 3: "q"}
startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
MinMaxDepth = 2 #while the maximum depth the bot can handle is 3 odd depths are so terrible that using only 2 is better
infinity = 100000