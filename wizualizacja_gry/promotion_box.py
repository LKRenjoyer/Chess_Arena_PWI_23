import pygame as pg

from tiles import Tile, Piece

class Promotion_Box:
    def __init__(self, size, color): #color - l for white, d for black
        self.update(size, color)

    def draw(self, surface):
        self.tiles.draw(surface)
        self.pieces.draw(surface)

    def update(self, size, color):
        self.size = size
        self.color = color
        self.tiles = pg.sprite.Group()
        self.pieces = pg.sprite.Group()
        if self.size!=-1:
            for i, p in enumerate("rnbq"):
                self.tiles.add(Tile(0,i,self.size,Tile.colors[i%2]))
                self.pieces.add(Piece(f"{p}{self.color}", 0,i,self.size))
            self.pieces.add(Piece("x_button", 0,4,self.size))
        
    def get_clicked_piece(self, pos):
        for piece in self.pieces:
            if piece.rect.collidepoint(pos):
                return piece.piece_type[0]
