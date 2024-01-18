import pygame as pg
import chess
from tiles import Piece, Tile

class Board(chess.Board):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.size = None
        self.piece_sprites = pg.sprite.Group()
        self.tiles = pg.sprite.Group()
        self.flipped = False
        self.all_moves = []

    def base_push(self, move):
        super().push_uci(move)

    def push_uci(self, move):
        self.base_push(move)
        self.all_moves.append(move)

    def revert_undos(self):
        for move in self.all_moves[len(self.move_stack):]:
            self.base_push(move)

    def flip(self):
        self.flipped = not self.flipped

    def update_tiles(self, size):
        highlight = set()
        if len(self.move_stack)>0:
            last_move = str(self.move_stack[-1])
            if self.flipped:
                highlight = {(ord(last_move[0])-ord('a'), int(last_move[1])-1), (ord(last_move[2])-ord('a'), int(last_move[3])-1)}
            else:
                highlight = {(ord(last_move[0])-ord('a'), 8-int(last_move[1])), (ord(last_move[2])-ord('a'), 8-int(last_move[3]))}
        self.tiles = pg.sprite.Group()
        for i in range(8):
            for j in range(8):
                if (i,j) in highlight:
                    self.tiles.add(Tile(i,j, size, Tile.highlight_colors[(i+j)%2]))
                else:
                    self.tiles.add(Tile(i,j, size, Tile.colors[(i+j)%2]))

    def update_pieces(self, size):
        self.piece_sprites = pg.sprite.Group()
        row = 0
        column = 0
        for char in self.fen():
            if char == ' ':
                break

            if char.lower() in "rnbqkp":
                piece = char.lower()
                piece_color = "ld"[char.islower()]
                dest_row = 7-row if self.flipped else row
                self.piece_sprites.add(Piece(f"{piece}{piece_color}", column, dest_row, size))
            elif char!='/':
                n = int(char)
                column+=n-1
            else:
                column=-1
                row+=1
            column+=1

    def update(self, size):
        self.size = size
        self.update_tiles(size)
        self.update_pieces(size)

    def draw(self, surface):
        surface.fill((62,61,57))
        self.tiles.draw(surface)
        self.piece_sprites.draw(surface)

    def get_clicked_piece(self, pos):
        for piece in self.piece_sprites:
            if piece.rect.collidepoint(pos):
                return piece
            
    def copy(self):
        cp = super().copy()
        cp.flipped = self.flipped
        return cp