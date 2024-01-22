import numpy as np
from data import *

class Board:
    def __init__(self):
        self.board = None
        self.turn = None
        self.castling_data = None
        self.en_passant_data = None
        self.halfmove_clock = None
        self.fullmove_clock = None
        self.board_record = [] #stores the tiles changed during a move -> specificly which tile was changed and what was there before
        self.data_record = [] #stores: turn castling_data en_passant_data hallfmove_clock and fullmove_clock in this order
    #part 1 - methods related to FEN notation/board notation methods
    def setToFen(self, fen):
        self.board_record.clear()
        self.data_record.clear()
        fen += " "
        i = 0
        #getting the board state
        self.board = np.zeros((2, 6, 8, 8))
        row = 0
        column = 0
        while fen[i] != ' ':
            c = fen[i]
            if c == '/':
                row += 1
                column = 0
            elif c >='1' and c <= '9':
                column += int(c)
            else:
                color = int(c.islower())
                piece = FenToNum[c.lower()]
                self.setTile(row, column, color, piece)
                column += 1
            i += 1
        i += 1
        #getting active player
        if fen[i] == 'w':
            self.turn = 0
        else:
            self.turn = 1
        i += 2
        #getting castling data
        self.castling_data = [0, 0, 0, 0]
        while fen[i] != ' ':
            c = fen[i]
            if c != '-':
                self.castling_data[CastlingConversion[c]] = 1
            i += 1
        i += 1
        #getting en passant data
        self.en_passant_data = [-1, -1]
        if fen[i] == '-':
            i += 2
        else:
            self.en_passant_data[0] = ord(fen[i]) - ord('a')
            self.en_passant_data[1] = 8 - int(fen[i+1])
            i+=3
        #getting halfmove clock
        self.halfmove_clock = 0
        while fen[i] != ' ':
            c = fen[i]
            self.halfmove_clock *= 10
            self.halfmove_clock += int(c)
            i += 1
        i += 1
        #getting fullmove clock
        self.fullmove_clock = 0
        while fen[i] != ' ':
            c = fen[i]
            self.fullmove_clock *= 10
            self.fullmove_clock += int(c)
            i += 1
        i += 1
    def getFen(self):
        fen = ""
        #board
        for i in range(8):
            tmp = ['0', '0', '0', '0', '0', '0', '0', '0']
            for j in range(8):
                for f in range(6):
                    for k in range(2):
                        if self.isTile(i, j, k, f):
                            tmp[j] = NumToFen[f]
                            if k == 0:
                                tmp[j] = tmp[j].upper()
            ile = 0
            for j in tmp:
                if j == '0':
                    ile += 1
                else:
                    if ile > 0:
                        fen += str(ile)
                        ile = 0
                    fen += j
            if ile > 0:
                fen += str(ile)
            if i!=7:
                fen += "/"
        fen += " "
        #active player
        if self.turn == 0:
            fen += "w "
        else:
            fen += "b "
        #castling data
        isBlank = True
        for i in range(4):
            if self.castling_data[i] == 1:
                fen += CastlingDeconversion[i]
                isBlank = False
        if isBlank == True:
            fen += "-"
        fen += " "
        #en passant target square
        if self.en_passant_data[0] == -1:
            fen += "- "
        else:
            fen += chr(self.en_passant_data[0] + ord('a'))
            fen += str(8 - self.en_passant_data[1])
            fen += " "
        #halfmove clock
        fen += str(self.halfmove_clock)
        fen += " "
        #fullmove clock
        fen += str(self.fullmove_clock)
        return fen
    #part 2 - move notation methods
    def convertMoveSmithToXYZ(self, move):
        x1 = 8 - int(move[1])
        y1 = ord(move[0]) - ord('a')
        x2 = 8 - int(move[3])
        y2 = ord(move[2]) - ord('a')
        z = -1
        if len(move) == 5:
            z = FenToNum[move[4]]
        if not (x1 >= 0 and x1 < 8 and y1 >= 0 and y1 < 8 and x2 >= 0 and x2 < 8 and y2 >= 0 and y2 < 8): #we deal with moves with invalid cooridnates by transforming them into a move no chess piece can make (a1 to b7 exactly) (that is 7 0 1 1 in XYZ notation) (let's also attach a king promotion just to be sure)
            return 7, 0, 1, 1, 5
        return x1, y1, x2, y2, z
    def convertMoveXYZToSmith(self, x1, y1, x2, y2, z = -1):
        fen = ""
        fen += chr(y1 + ord('a'))
        fen += str(8 - x1)
        fen += chr(y2 + ord('a'))
        fen += str(8 - x2)
        if z != -1:
            fen += NumToFen[z]
        return fen
    #part 3 - board access auxiliary functions
    def getPiece(self, x, y):
        for i in range(2):
            for j in range(6):
                if self.isTile(x, y, i, j):
                    return j
        return -1
    def getOwner(self, x, y):
        for i in range(2):
            for j in range(6):
                if self.isTile(x, y, i, j):
                    return i
        return -1
    def getTileData(self, x, y):
        piece = self.getPiece(x, y)
        owner = self.getOwner(x, y)
        return (x, y, owner, piece)
    def setTile(self, x, y, owner, piece):
        self.board[owner][piece][x][y] = 1
    def isTile(self, x, y, owner, piece):
        if self.board[owner][piece][x][y] == 1:
            return True
        else:
            return False
    def getKingTile(self, who):
        for i in range(8):
            for j in range(8):
                if self.isTile(i, j, who, 5):
                    return i, j
    #part 4 - chess piece methods
    #these generate list of moves that a piece can make from a chosen tile
    def moveHelperVector(self, x, y, moveVector):
        who = self.getOwner(x, y)
        if who == -1:
            return [], []
        moveTiles = []
        captureTiles = []
        i = x + moveVector[0]
        j = y + moveVector[1]
        while i >= 0 and i < 8 and j >= 0 and j < 8:
            own = self.getOwner(i, j)
            if own == who:
                break
            if own == 1 - who:
                captureTiles.append((i, j))
                break
            if own == -1:
                moveTiles.append((i, j))
            i += moveVector[0]
            j += moveVector[1]
        return moveTiles, captureTiles
    def rook(self, x, y, capturesOnly = False):
        moveTiles = []
        captureTiles = []
        tmp1, tmp2 = self.moveHelperVector(x, y, [1, 0])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [-1, 0])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [0, 1])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [0, -1])
        moveTiles += tmp1
        captureTiles += tmp2
        if capturesOnly == True:
            return captureTiles
        return moveTiles + captureTiles
    def bishop(self, x, y, capturesOnly = False):
        moveTiles = []
        captureTiles = []
        tmp1, tmp2 = self.moveHelperVector(x, y, [1, 1])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [1, -1])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [-1, 1])
        moveTiles += tmp1
        captureTiles += tmp2
        tmp1, tmp2 = self.moveHelperVector(x, y, [-1, -1])
        moveTiles += tmp1
        captureTiles += tmp2
        if capturesOnly == True:
            return captureTiles
        return moveTiles + captureTiles
    def queen(self, x, y, capturesOnly = False):
        return self.rook(x, y, capturesOnly) + self.bishop(x, y, capturesOnly)
    def moveHelperList(self, x, y, moveList):
        who = self.getOwner(x, y)
        if who == -1:
            return []
        moveTiles = []
        for tile in moveList:
            if tile[0] >= 0 and tile[0] < 8 and tile[1] >= 0 and tile[1] < 8:
                own = self.getOwner(tile[0], tile[1])
                if own != who:
                    moveTiles.append(tile)
        return moveTiles
    def knight(self, x, y, _ = False):
        return self.moveHelperList(x, y, [(x+1, y+2), (x-1, y+2), (x+1, y-2), (x-1, y-2), (x+2, y+1), (x+2, y-1), (x-2, y+1), (x-2, y-1)])
    def king(self, x, y, _ = False):
        return self.moveHelperList(x, y, [(x-1, y-1), (x-1, y), (x-1, y+1), (x, y+1), (x+1, y+1), (x+1, y), (x+1, y-1), (x, y-1)])
    def pawn(self, x, y, attacking = False):
        #I DO NOT LIKE PAWNS
        who = self.getOwner(x, y)
        if who == -1:
            return []
        if attacking == True:
            if who == 0:
                return self.moveHelperList(x, y, [(x-1, y-1), (x-1, y+1)])
            else:
                return self.moveHelperList(x, y, [(x+1, y-1), (x+1, y+1)])
        moveTiles = []
        if who == 0:
            if x-1 >= 0:
                if self.getOwner(x-1, y) == -1:
                    moveTiles.append((x-1, y))
                    if x == 6 and self.getOwner(x-2, y) == -1:
                        moveTiles.append((x-2, y))
                if y-1 >= 0 and ( self.getOwner(x-1, y-1) == 1 or (x-1, y-1) == self.en_passant_data ):
                    moveTiles.append((x-1, y-1))
                if y+1 < 8 and ( self.getOwner(x-1, y+1) == 1 or (x-1, y+1) == self.en_passant_data ):
                    moveTiles.append((x-1, y+1))
        else:
            if x+1 < 8:
                if self.getOwner(x+1, y) == -1:
                    moveTiles.append((x+1, y))
                    if x == 1 and self.getOwner(x+2, y) == -1:
                        moveTiles.append((x+2, y))
                if y-1 >= 0 and ( self.getOwner(x+1, y-1) == 0 or (x+1, y-1) == self.en_passant_data ):
                    moveTiles.append((x+1, y-1))
                if y+1 < 8 and ( self.getOwner(x+1, y+1) == 0 or (x+1, y+1) == self.en_passant_data ):
                    moveTiles.append((x+1, y+1))
        #pawns weren't that bad actually
        return moveTiles
    #part 5 - auxiliary board and move methods
    def isInCheck(self, who):
        #for every piece except for pawns we are making use of symmetry of attacks for example:
        #a tile is attacked by an enemy rook if and only if where there an ally rook on this tile it would be able to capture that enemy rook
        x, y = self.getKingTile(who)
        tmp = self.pawn(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 0:
                return True
        tmp = self.knight(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 1:
                return True
        tmp = self.bishop(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 2:
                return True
        tmp = self.rook(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 3:
                return True
        tmp = self.queen(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 4:
                return True
        tmp = self.king(x, y, True)
        for tile in tmp:
            if self.getPiece(tile[0], tile[1]) == 5:
                return True
        return False
    def isPromotion(self, move):
        #checks if a move is a pawn promotion
        #does not check validity
        x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
        if self.getPiece(x1, y1) == 0 and (x2 == 7 or x2 == 0):
            return True
        return False
    def isEnPassant(self, move):
        #checks for weird French moves
        #does not check validity
        x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
        if self.getPiece(x1, y1) == 0 and (x2, y2) == self.en_passant_data:
            return True
        return False
    def isRationalCastle(self, move):
        #checks if a castle makes sense according to chess rules except for checks
        x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
        who = self.getOwner(x1, y1)
        if self.getPiece(x1, y1) != 5: #we immediately get rid of non king moves
            return False
        if self.getOwner(x1, y1) != self.turn: #this catches attemps to move wrong color
            return False
        if z != -1: #castles should have default z
            return False
        #we can get the information what castle is being attempted from tile coordinates alone
        #we needn't worry about white attempting to castle on the 8-th rank (and black on 1-st)
        #yes it gets treated as if the attempt was by the wrong color and thus uses wrong castling_data
        #but for that situation to take place the other color must have also moved their king
        #thus resulting in the wrongly used castling_data used being a 0 anyways
        #observation: writing this took way longer that fixing it in code would have
        #I added an extra condition into the code but I am not deleting this anyways, I am attached to this awful wall of text now
        #white kingside
        if x1 == 7 and y1 == 4 and x2 == 7 and y2 == 6 and self.castling_data[0] == 1 and who == 0 :
            if self.getPiece(7, 7) == 3 and self.getOwner(7, 7) == who and self.getPiece(7, 6) == -1 and self.getPiece(7, 5) == -1:
                return True
        #white queenside
        if x1 == 7 and y1 == 4 and x2 == 7 and y2 == 2 and self.castling_data[1] == 1 and who == 0:
            if self.getPiece(7, 0) == 3 and self.getOwner(7, 0) == who and self.getPiece(7, 1) == -1 and self.getPiece(7, 2) == -1 and self.getPiece(7, 3) == -1:
                return True
        #black kingside
        if x1 == 0 and y1 == 4 and x2 == 0 and y2 == 6 and self.castling_data[2] == 1 and who == 1:
            if self.getPiece(0, 7) == 3 and self.getOwner(0, 7) == who and self.getPiece(0, 6) == -1 and self.getPiece(0, 5) == -1:
                return True
        #black queenside
        if x1 == 0 and y1 == 4 and x2 == 0 and y2 == 2 and self.castling_data[3] == 1 and who == 1:
            if self.getPiece(0, 0) == 3 and self.getOwner(0, 0) == who and self.getPiece(0, 1) == -1 and self.getPiece(0, 2) == -1 and self.getPiece(0, 3) == -1:
                return True
        return False
    def isRational(self, move):
        #checks if move makes sense according to chess rules but does not account for checks
        if self.isRationalCastle(move): #castles use their dedicated function
            return True
        x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
        piece = self.getPiece(x1, y1)
        who = self.getOwner(x1, y1)
        if self.turn != who: #this catches attemps to move wrong color pieces or air
            return False
        if self.isPromotion(move) == False and z != -1: #non promotion moves should have default z
            return False
        if self.isPromotion(move) == True and not(z >= 0 and z <= 4): #promotions must be to either knight, bishop, rook or queen !!!IMPORTANT!!! -> at the request of the visualization team promotions to a pawn are now allowed; however it is assumed they will be immediately undone because their implications were not previously considered
            return False
        if piece == 0:
            tiles = self.pawn(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        if piece == 1:
            tiles = self.knight(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        if piece == 2:
            tiles = self.bishop(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        if piece == 3:
            tiles = self.rook(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        if piece == 4:
            tiles = self.queen(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        if piece == 5:
            tiles = self.king(x1, y1)
            if (x2, y2) in tiles:
                return True
            return False
        return True
    #part 6: board modification methods
    def clearTile(self, x, y):
        for i in range(2):
            for j in range(6):
                self.board[i][j][x][y] = 0
    def push(self, move):
        if not self.isRational(move):
            return
        x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
        #recording data
        self.data_record.append([self.turn, self.castling_data.copy(), self.en_passant_data, self.halfmove_clock, self.fullmove_clock])
        #iterating counters
        if self.turn == 1:
            self.fullmove_clock += 1
        if self.getPiece(x1, y1) != 0 and self.getPiece(x2, y2) == -1:
            self.halfmove_clock +=1
        else:
            self.halfmove_clock = 0
        #board modifications
        if self.isRationalCastle(move):
            memory = []
            #white kingside
            if x2 == 7 and y2 == 6:
                memory.append(self.getTileData(7, 4))
                memory.append(self.getTileData(7, 5))
                memory.append(self.getTileData(7, 6))
                memory.append(self.getTileData(7, 7))
                self.clearTile(7, 4)
                self.clearTile(7, 5)
                self.clearTile(7, 6)
                self.clearTile(7, 7)
                self.setTile(7, 6, 0, 5)
                self.setTile(7, 5, 0, 3)
            #white queenside
            if x2 == 7 and y2 == 2:
                memory.append(self.getTileData(7, 4))
                memory.append(self.getTileData(7, 3))
                memory.append(self.getTileData(7, 2))
                #memory.append(self.getTileData(7, 1))
                memory.append(self.getTileData(7, 0))
                self.clearTile(7, 4)
                self.clearTile(7, 3)
                self.clearTile(7, 2)
                self.clearTile(7, 1)
                self.clearTile(7, 0)
                self.setTile(7, 2, 0, 5)
                self.setTile(7, 3, 0, 3)
            #black kingside
            if x2 == 0 and y2 == 6:
                memory.append(self.getTileData(0, 4))
                memory.append(self.getTileData(0, 5))
                memory.append(self.getTileData(0, 6))
                memory.append(self.getTileData(0, 7))
                self.clearTile(0, 4)
                self.clearTile(0, 5)
                self.clearTile(0, 6)
                self.clearTile(0, 7)
                self.setTile(0, 6, 1, 5)
                self.setTile(0, 5, 1, 3)
            #black queenside
            if x2 == 0 and y2 == 2:
                memory.append(self.getTileData(0, 4))
                memory.append(self.getTileData(0, 3))
                memory.append(self.getTileData(0, 2))
                #memory.append(self.getTileData(0, 1))
                memory.append(self.getTileData(0, 0))
                self.clearTile(0, 4)
                self.clearTile(0, 3)
                self.clearTile(0, 2)
                self.clearTile(0, 1)
                self.clearTile(0, 0)
                self.setTile(0, 2, 1, 5)
                self.setTile(0, 3, 1, 3)
            self.board_record.append(memory)
        else:
            memory = []
            memory.append(self.getTileData(x1, y1))
            memory.append(self.getTileData(x2, y2))
            piece = self.getPiece(x1, y1)
            self.clearTile(x1, y1)
            self.clearTile(x2, y2)
            if self.isEnPassant(move):
                if self.turn == 0:
                    memory.append(self.getTileData(x2 + 1, y2))
                    self.clearTile(x2 + 1, y2)
                else:
                    memory.append(self.getTileData(x2 - 1, y2))
                    self.clearTile(x2 - 1, y2)
            if self.isPromotion(move):
                self.setTile(x2, y2, self.turn, z)
            else:
                self.setTile(x2, y2, self.turn, piece)
            self.board_record.append(memory)
        #data modifications
        #turn
        self.turn = 1 - self.turn
        #castling info
        if x1 == 7 and y1 == 4:
            self.castling_data[0] = 0
            self.castling_data[1] = 0
        if x1 == 7 and y1 == 7:
            self.castling_data[0] = 0
        if x1 == 7 and y1 == 0:
            self.castling_data[1] = 0
        if x1 == 0 and y1 == 4:
            self.castling_data[2] = 0
            self.castling_data[3] = 0
        if x1 == 0 and y1 == 7:
            self.castling_data[2] = 0
        if x1 == 0 and y1 == 0:
            self.castling_data[3] = 0
        #en passant info
        if self.getPiece(x2, y2) == 0 and abs(x1 - x2) == 2:
            self.en_passant_data[0] = (x1 + x2)//2
            self.en_passant_data[1] = y1
        else:
            self.en_passant_data[0] = -1
            self.en_passant_data[1] = -1
    #undoing a move
    def pop(self):
        if len(self.board_record or self.data_record) == 0:
            return
        undo = self.board_record[-1]
        self.board_record.pop()
        for tile in undo:
            self.clearTile(tile[0], tile[1])
            if tile[2] != -1:
                self.setTile(tile[0], tile[1], tile[2], tile[3])
        undo = self.data_record[-1]
        self.data_record.pop()
        self.turn = undo[0]
        self.castling_data = undo[1]
        self.en_passant_data = undo[2]
        self.halfmove_clock = undo[3]
        self.fullmove_clock = undo[4]
    #part 7: getting all viable moves
    #checking for move legality fully including checks
    def isLegal(self, move):
        if not self.isRational(move):
            return False
        who = self.turn
        #we perform a move and then check if it resultet in us being checked, if so the move was not legal
        resultsInCheck = False
        self.push(move)
        resultsInCheck = self.isInCheck(who)
        self.pop()
        if resultsInCheck == True:
            return False
        if self.isRationalCastle(move):
            #castles get two additional checks
            #if the king is in check at the moment he cannot castle
            if self.isInCheck(who):
                return False
            #we also attempt making a halfcastle (moving the king 1 square in castling direction) and check for legality of that move
            x1, y1, x2, y2, z = self.convertMoveSmithToXYZ(move)
            halfCastle = self.convertMoveXYZToSmith(x1, y1, (x1+x2)//2, y2, z)
            resultsInCheck = False
            self.push(halfCastle)
            resultsInCheck = self.isInCheck(who)
            self.pop()
            if resultsInCheck == True:
                return False
        return True
    def getLegalMoves(self):
        #return list of all legal moves
        legal = []
        for x in range(8):
            for y in range(8):
                if self.getOwner(x, y) == self.turn:
                    piece = self.getPiece(x, y)
                    possibilities = []
                    if piece == 0:
                        possibilities += self.pawn(x, y)
                    if piece == 1:
                        possibilities += self.knight(x, y)
                    if piece == 2:
                        possibilities += self.bishop(x, y)
                    if piece == 3:
                        possibilities += self.rook(x, y)
                    if piece == 4:
                        possibilities += self.queen(x, y)
                    if piece == 5:
                        possibilities += self.king(x, y)
                        if y == 4:
                            possibilities.append((x, y-2))
                            possibilities.append((x, y+2))
                    for p in possibilities:
                        move = self.convertMoveXYZToSmith(x, y, p[0], p[1])
                        if self.isLegal(move) == True:
                            legal.append(move)
                        if piece == 0 and (x == 6 or x == 1):
                            for promo in range(1, 5):
                                move = self.convertMoveXYZToSmith(x, y, p[0], p[1], promo)
                                if self.isLegal(move) == True:
                                    legal.append(move)
        # print(legal)       
        return legal     
    #part 8: bonus debug functions
    #printing everything
    def test(self):
        print(self.board)
        print(self.turn)
        print(self.castling_data)
        print(self.en_passant_data)
        print(self.halfmove_clock)
        print(self.fullmove_clock)
        print(self.board_record)
        print(self.data_record)
    #very basic text visualization
    def visualize(self):
        for i in range(8):
            line = ""
            for j in range(8):
                owner = self.getOwner(i, j)
                piece = self.getPiece(i, j)
                c = '-'
                if piece != -1:
                    c = NumToFen[piece]
                if owner == 0:
                    c = c.upper()
                line += c
                line +=" "
            print(line)

if __name__ == "__main__":
    board=Board()
    board.setToFen("rnbqk2r/2ppb1pp/p2N4/1p2p1N1/1P2PpnP/8/P1PPBPP1/R1BQ1RK1 b kq - 1 10")
    print(board.isLegal("e1c1"))
    board.visualize()
    print(board.getLegalMoves())
