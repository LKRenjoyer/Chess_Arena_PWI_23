import pygame as pg

class TimerBox:
    def __init__(self, x, y, size, twhite, tblack): #add size
        self.font = pg.font.SysFont(None, size//2)
        self.x = x
        self.y = y
        self.resize(size)
        self.update(twhite, tblack)

    def draw(self, surface):
        s = pg.Surface((5*self.size,2*self.size))
        s.fill((62,61,57))
        t1 = self.font.render(f'white: {int(self.twhite)//60}:{int(self.twhite)%60:02}', True, "white")
        t2 = self.font.render(f'black: {int(self.tblack)//60}:{int(self.tblack)%60:02}', True, "white")
        s.blit(t1, (0, 0))
        s.blit(t2, (0, self.size))
        surface.blit(s, (self.x, self.y))

    def resize(self, size):
        self.font = pg.font.SysFont(None, size//3)
        self.size = size//2

    def update(self, twhite, tblack):
        self.twhite = float(twhite)
        self.tblack = float(tblack)
        
    def get_clicked_piece(self, pos):
        for piece in self.pieces:
            if piece.rect.collidepoint(pos):
                return piece.piece_type[0]
