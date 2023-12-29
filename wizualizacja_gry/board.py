import pygame as pg
import chess
from tiles import Piece, Tile

class Board(chess.Board):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.size = None
        self.piece_sprites = pg.sprite.Group()
        self.tiles = pg.sprite.Group()

    def update_tiles(self, size):
        self.tiles = pg.sprite.Group()
        tile_colors = ((184,135,98),(237,214,176))
        for i in range(8):
            for j in range(8):
                self.tiles.add(Tile(i,j, size, tile_colors[(i+j)%2]))

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
                self.piece_sprites.add(Piece(f"{piece}{piece_color}", column, row, size))
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