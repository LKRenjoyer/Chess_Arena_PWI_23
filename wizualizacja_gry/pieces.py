import pygame as pg
import os
from functools import partial

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

class Piece(pg.sprite.Sprite):
    def __init__(self, piece, x, y, size):
        pg.sprite.Sprite.__init__(self)
        self.image = pg.image.load(path("pieces",f"{piece}.png")).convert_alpha()
        self.image = pg.transform.smoothscale(self.image, (size, size))
        self.rect = self.image.get_rect()
        self.rect.x = x*size
        self.rect.y = y*size