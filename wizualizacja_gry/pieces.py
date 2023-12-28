import pygame as pg
import os
from functools import partial

path = partial(os.path.join, f'{__file__}\\..')

class Piece(pg.sprite.Sprite):
    def __init__(self, piece, x, y):
        pg.sprite.Sprite.__init__(self)
        self.image = pg.image.load(path(f"pieces\\{piece}.png")).convert_alpha()
        self.image = pg.transform.smoothscale(self.image, (64,64))
        self.rect = self.image.get_rect()
        self.rect.x = x*64
        self.rect.y = y*64