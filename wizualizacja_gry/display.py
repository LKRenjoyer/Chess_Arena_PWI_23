import pygame as pg
from pieces import *
from chess import STARTING_BOARD_FEN
from board import Board
import os
from functools import partial

path = partial(os.path.join, f'{__file__}\\..')

pg.init()

screen = pg.display.set_mode((64*8,64*8))

clock = pg.time.Clock()
running = True

board = Board(STARTING_BOARD_FEN)

with open(path("game.txt"), "r") as f:
    game = f.read().splitlines()

current_move = 0

screen.fill("red")
board.draw(screen)
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
        elif event.type == pg.KEYDOWN:
            if event.key == pg.K_RIGHT:
                board.push_uci(game[current_move])
                current_move += 1
            elif event.key == pg.K_LEFT:
                board.pop()
                current_move-=1
            board.draw(screen)
    pg.display.update()

    clock.tick(60)

pg.quit()