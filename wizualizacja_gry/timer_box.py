import pygame as pg

class TimerBox:
    def __init__(self, x, y, twhite, tblack): #add size
        self.font = pg.font.SysFont(None, 24)
        self.x = x
        self.y = y
        self.update(twhite, tblack)

    def draw(self, surface):
        s = pg.Surface((200,60))
        t1 = self.font.render(f'white: {int(self.twhite)//60}:{int(self.twhite)%60}', True, "black")
        t2 = self.font.render(f'black {int(self.tblack)//60}:{int(self.tblack)%60}', True, "black")
        s.fill("white")
        s.blit(t1, (0, 0))
        s.blit(t2, (0, 30))
        surface.blit(s, (self.x, self.y))

    def update(self, twhite, tblack):
        self.twhite = float(twhite)
        self.tblack = float(tblack)
        
    def get_clicked_piece(self, pos):
        for piece in self.pieces:
            if piece.rect.collidepoint(pos):
                return piece.piece_type[0]
