import pygame as pg
from pieces import *
from chess import STARTING_BOARD_FEN
from board import Board
import os
from functools import partial
import threading
import sys

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

pg.init()

screen = pg.display.set_mode((64*8,64*8), pg.RESIZABLE)

clock = pg.time.Clock()
running = True

board = Board(STARTING_BOARD_FEN)

with open(path("game.txt"), "r") as f:
    game = f.read().splitlines()

current_move = 0

def redraw(screen):
    scrsize = screen.get_size()
    bsize = min(scrsize)*9//80
    surface = pg.Surface(scrsize)
    screen.fill((62,61,57))
    offsets = ((scrsize[0]-bsize*8)//2, (scrsize[1]-bsize*8)//2)
    board.draw(surface, bsize)
    screen.blit(surface, offsets)
    pg.display.update()

def get_move():
    while running:
        move = input()
        board.push_uci(move)
        redraw(screen)

threading.Thread(target=get_move).start()

redraw(screen)
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
            pg.quit()
            sys.exit(7)
        # elif event.type == pg.KEYDOWN:
        #     if event.key == pg.K_RIGHT:
        #         board.push_uci(game[current_move])
        #         current_move += 1
        #     elif event.key == pg.K_LEFT:
        #         board.pop()
        #         current_move-=1
        #     redraw(screen)
        elif event.type == pg.WINDOWRESIZED:
            redraw(screen)

    clock.tick(60)

pg.quit()