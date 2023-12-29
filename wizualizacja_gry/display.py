from contextlib import redirect_stdout
import io

with redirect_stdout(io.StringIO()):
    import pygame as pg

from chess import STARTING_FEN, IllegalMoveError
from board import Board
from promotion_box import Promotion_Box
import os
from functools import partial
import threading
import sys

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

pg.init()

screen = pg.display.set_mode((64*8,64*8), pg.RESIZABLE)

clock = pg.time.Clock()
running = True

board = Board(STARTING_FEN)

# with open(path("game.txt"), "r") as f:
#     game = f.read().splitlines()

promotion_box = Promotion_Box(0,'l') 

current_move = 0

offsets = [0,0]

lock = threading.Lock()
def redraw(screen, update=True):
    with lock:
        screen.fill((62,61,57))
        scrsize = screen.get_size()
        bsize = min(scrsize)*9//80
        if update:
            board.update(bsize)
        surface = pg.Surface(scrsize)
        offsets[0] = (scrsize[0]-bsize*8)//2
        offsets[1] = (scrsize[1]-bsize*8)//2
        board.draw(surface)
        screen.blit(surface, offsets)
        promotion_box.draw(screen)
        pg.display.update()

def get_move():
    while running:
        move = input()
        board.push_uci(move)
        redraw(screen)

threading.Thread(target=get_move).start()

redraw(screen)
clicked = None
cursor_on_piece = False

default_cursor = pg.cursors.arrow
on_piece_cursor = pg.cursors.broken_x
drag_cursor = pg.cursors.diamond
start_pos = None

def conv_to_uci(pos1, pos2):
    return "".join(chr(p[0]+ord('a'))+str(8-p[1]) for p in (pos1, pos2))

def try_move(board, move): #sprawdza czy ruch promuje i jeśli nie, to wykonuje go
    try:
        board.push_uci(move+'p') #to nie powinno działać, ale naprawia błąd z roszadą
        print(move,flush=True)
        return False
    except (IllegalMoveError, ValueError):
        try: #promocja
            board.push_uci(move+'q')
            board.pop()
            promotion_box.update(board.size, ('dl')[board.turn])
            redraw(screen,True)
            return True
            # print(move,flush=True)
        except (IllegalMoveError, ValueError):
            try:
                board.push_uci(move)
                print(move,flush=True)
            except (IllegalMoveError, ValueError):
                pass
            return False

last_move = None
move_promotes = False

while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
            pg.quit()
            sys.exit(7)
        elif event.type == pg.MOUSEBUTTONDOWN:
            if event.button == 1:
                if move_promotes:
                    promoted_piece = promotion_box.check_clicked(event.pos)
                    if promoted_piece is not None:
                        promotion_box.update(0,'l')
                        last_move = last_move+promoted_piece
                        board.push_uci(last_move)
                        print(last_move, flush=True)
                        redraw(screen)
                        promoted_piece = None
                        move_promotes = False
                else:  
                    for sprite in board.piece_sprites:
                        pos = (event.pos[0]-offsets[0], event.pos[1]-offsets[1])
                        if sprite.rect.collidepoint(pos):
                            clicked = sprite
                            pos = (event.pos[0]-clicked.rect.size[0]//2-offsets[0], event.pos[1]-clicked.rect.size[1]//2-offsets[1])
                            clicked.rect.update(pos, clicked.rect.size)
                            start_pos = ((event.pos[0]-offsets[0])//board.size, (event.pos[1]-offsets[1])//board.size)
                            redraw(screen, False)
                            pg.mouse.set_cursor(*pg.cursors.diamond)
                            break
                    
        elif event.type == pg.MOUSEBUTTONUP:
            if event.button == 1:
                if clicked:
                    pos = (event.pos[0]-offsets[0], event.pos[1]-offsets[1])
                    dest = (pos[0]//board.size,pos[1]//board.size)
                    clicked.rect.update((dest[0]*board.size, dest[1]*board.size), clicked.rect.size)
                    move = conv_to_uci(start_pos, dest)
                    last_move = move
                    move_promotes = try_move(board, move)
                    redraw(screen, True)
                if not cursor_on_piece:
                    pg.mouse.set_cursor(*pg.cursors.arrow)
                else:
                    pg.mouse.set_cursor(*pg.cursors.broken_x)
                clicked = None
        elif event.type == pg.MOUSEMOTION:
            pos = (event.pos[0]-offsets[0], event.pos[1]-offsets[1])
            for sprite in board.piece_sprites:
                if sprite.rect.collidepoint(pos):
                    if not cursor_on_piece:
                        pg.mouse.set_cursor(*pg.cursors.broken_x)
                        cursor_on_piece=True
                    break
                else:
                    if cursor_on_piece and clicked is None:
                        pg.mouse.set_cursor(*pg.cursors.arrow)
                        cursor_on_piece = False
            if clicked is not None:
                pos = (event.pos[0]-clicked.rect.size[0]//2-offsets[0], event.pos[1]-clicked.rect.size[1]//2-offsets[1])
                clicked.rect.update(pos, clicked.rect.size)
            redraw(screen, False)
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