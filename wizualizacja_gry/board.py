import pygame as pg
import chess
from pieces import Piece

class Board(chess.Board):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def draw(self, surface):
        group = pg.sprite.Group()
        row = 0
        column = 0
        for char in self.fen():
            if char == ' ':
                break
            tile_colour = "green" if (column+row)%2 else "blue"
            pg.draw.rect(surface, tile_colour, pg.rect.Rect((column*64,row*64,64,64)))
            if char.lower() in "rnbqkp":
                piece = char.lower()
                piece_colour = "ld"[char.islower()]
                group.add(Piece(f"{piece}{piece_colour}", column, row))
            elif char!='/':
                n = int(char)
                for i in range(n):
                    tile_colour = "green" if (column+row+i)%2 else "blue"
                    pg.draw.rect(surface, tile_colour, pg.rect.Rect(((column+i)*64,row*64,64,64)))
                column+=n-1
            else:
                column=-1
                row+=1
            column+=1

        group.draw(surface)