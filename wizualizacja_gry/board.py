import pygame as pg
import chess
from pieces import Piece

class Board(chess.Board):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def draw(self, surface, size):
        surface.fill((62,61,57))
        group = pg.sprite.Group()
        row = 0
        column = 0
        for char in self.fen():
            if char == ' ':
                break
            tile_colour = (184,135,98) if (column+row)%2 else (237,214,176)

            if char.lower() in "rnbqkp":
                piece = char.lower()
                piece_colour = "ld"[char.islower()]
                group.add(Piece(f"{piece}{piece_colour}", column, row, size))
                pg.draw.rect(surface, tile_colour, pg.rect.Rect((column*size,row*size,size,size)))
            elif char!='/':
                n = int(char)
                for i in range(n):
                    tile_colour = (184,135,98) if (column+row+i)%2 else (237,214,176)
                    pg.draw.rect(surface, tile_colour, pg.rect.Rect(((column+i)*size,row*size,size,size)))
                column+=n-1
            else:
                column=-1
                row+=1
            column+=1

        group.draw(surface)