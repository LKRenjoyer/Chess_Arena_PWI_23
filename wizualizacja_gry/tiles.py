import pygame as pg
import os
from functools import partial

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

class Tile(pg.sprite.Sprite):
    colors = ((237,214,176),(184,135,98))
    alt_colors = ((200,100,200),(100,200,100))
    highlight_colors = ((237,214,100),(237,214,100))
    def __init__(self, x, y, size, color):
        pg.sprite.Sprite.__init__(self)
        self.image=pg.Surface((size,size))
        self.rect = self.image.get_rect()
        pg.draw.rect(self.image, color, self.rect)
        self.rect.x = x*size
        self.rect.y = y*size

class Piece(pg.sprite.Sprite):
    def __init__(self, piece, x, y, size):
        pg.sprite.Sprite.__init__(self)
        self.piece_type = piece
        self.image = pg.image.load(path("images",f"{piece}.png")).convert_alpha()
        self.image = pg.transform.smoothscale(self.image, (size, size))
        self.rect = self.image.get_rect()
        self.rect.x = x*size
        self.rect.y = y*size