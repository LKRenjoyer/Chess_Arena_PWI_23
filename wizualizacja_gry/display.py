from contextlib import redirect_stdout
import io

with redirect_stdout(io.StringIO()):
    import pygame as pg

import chess
from board import Board
from promotion_box import Promotion_Box
import os
from functools import partial
import threading
import sys
from argparse import ArgumentParser

parser = ArgumentParser(description="program do wizualizacji gry między botami/graczami")

parser.add_argument('-w', action='store_true', help="oznacza, że gracz biały nie jest botem.", required=False)
parser.add_argument('-b', action='store_true', help="oznacza, że gracz czarny nie jest botem.", required=False)

args = parser.parse_args(sys.argv[1:])

path = partial(os.path.join, os.path.dirname(os.path.abspath(__file__)))

pg.init()

screen = pg.display.set_mode((64*8,64*8), pg.RESIZABLE)

clock = pg.time.Clock()
running = True

board = Board(chess.STARTING_FEN)

# with open(path("game.txt"), "r") as f:
#     game = f.read().splitlines()

promotion_box = Promotion_Box(-1,'l') 

current_move = 0

offsets = [0,0]

def redraw(screen, update=True):
    screen.fill((62,61,57))
    scrsize = screen.get_size()
    bsize = min(scrsize)*9//80
    if update:
        board.update(bsize)
        if promotion_box.size!=-1:
            promotion_box.update(bsize, promotion_box.color)
    surface = pg.Surface(scrsize)
    offsets[0] = (scrsize[0]-bsize*8)//2
    offsets[1] = (scrsize[1]-bsize*8)//2
    board.draw(surface)
    screen.blit(surface, offsets)
    promotion_box.draw(screen)

opponent_moved=False
def get_move():
    while running:
        global opponent_moved
        move = input()
        opponent_moved = True
        board.push_uci(move)

threading.Thread(target=get_move).start()

if args.b and not args.w:
    board.flip()

redraw(screen)
clicked = None
cursor_on_piece = False

default_cursor = pg.cursors.arrow
on_piece_cursor = pg.cursors.broken_x
drag_cursor = pg.cursors.diamond
start_pos = None
old_board = None

def conv_to_uci(pos1, pos2):
    return "".join(chr(p[0]+ord('a'))+str(8-p[1]) for p in (pos1, pos2))

def try_move(board, move): #sprawdza czy ruch promuje i jeśli nie, to wykonuje go
    global old_board
    try:
        board.push_uci(move+'p') #to nie powinno działać, ale naprawia błąd z roszadą
    except (chess.IllegalMoveError, ValueError):
        try: #promocja
            old_board = board.copy()
            board.push_uci(move+'q')
        except (chess.IllegalMoveError, ValueError):
            try:
                board.push_uci(move)
                print(move,flush=True)
            except (chess.IllegalMoveError, ValueError):
                pass
            return False
        else:
            promotion_box.update(board.size, ('ld')[board.turn])
            pmap = board.piece_map()
            pmap[(ord(move[2])-ord('a'))+(int(move[3])-1)*8] = chess.Piece.from_symbol('Pp'[board.turn])
            board.set_piece_map(pmap)
            return True
    else:
        print(move,flush=True)
        return False

def flip_pos(pos):
    return (pos[0],7-pos[1])

last_move = None
move_promotes = False
player_colors = set()
if args.w:
    player_colors.add('l')
if args.b:
    player_colors.add('d') 

while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
            pg.quit()
            sys.exit(7)
        elif event.type == pg.MOUSEBUTTONDOWN:
            if event.button == 1:
                if move_promotes:
                    promoted_piece = promotion_box.get_clicked_piece(event.pos)
                    if promoted_piece is not None:
                        board = old_board
                        old_board = None
                        promotion_box.update(-1,'l')
                        if promoted_piece != 'x':
                            last_move = last_move+promoted_piece
                            board.push_uci(last_move)
                            print(last_move, flush=True)
                        promoted_piece = None
                        move_promotes = False
                        redraw(screen, True)
                else:  
                    pos = (event.pos[0]-offsets[0], event.pos[1]-offsets[1])
                    clicked = board.get_clicked_piece(pos)
                    if clicked is not None and clicked.piece_type[1] in player_colors:
                        pos = (event.pos[0]-clicked.rect.size[0]//2-offsets[0], event.pos[1]-clicked.rect.size[1]//2-offsets[1])
                        clicked.rect.update(pos, clicked.rect.size)
                        start_pos = ((event.pos[0]-offsets[0])//board.size, (event.pos[1]-offsets[1])//board.size)
                        redraw(screen, False)
                        pg.mouse.set_cursor(*pg.cursors.diamond)
                    else:
                        clicked = None
                    
        elif event.type == pg.MOUSEBUTTONUP:
            if event.button == 1:
                if clicked is not None:
                    pos = (event.pos[0]-offsets[0], event.pos[1]-offsets[1])
                    dest = (pos[0]//board.size, pos[1]//board.size)
                    clicked.rect.update((dest[0]*board.size, dest[1]*board.size), clicked.rect.size)
                    if board.flipped:
                        move = conv_to_uci(flip_pos(start_pos), flip_pos(dest))
                    else:
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
            for piece in board.piece_sprites:
                if piece.rect.collidepoint(pos) and piece.piece_type[1] in player_colors:
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
        # elif event.type == pg.KEYDOWN:
        #     if event.key == pg.K_RIGHT:
        #         board.push_uci(game[current_move])
        #         current_move += 1
        #     elif event.key == pg.K_LEFT:
        #         board.pop()
        #         current_move-=1
        #     redraw(screen)
        elif event.type == pg.WINDOWRESIZED:
            redraw(screen,True)
    if opponent_moved:
        redraw(screen,True)
        opponent_moved = False
    else:
        redraw(screen, False)
    pg.display.update()
    clock.tick()

pg.quit()