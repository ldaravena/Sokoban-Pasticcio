import pygame
import sys
from pygame.locals import *
import constants as SOKOBAN
from level import *
from player import *
from scores import *
from player_interface import *
import time

class Game:
    def __init__(self, window, numero):
        self.window = window
        self.load_textures()
        self.player = None
        self.index_level = numero
        self.load_level()
        self.play = True
        self.contador = 0
        self.scores = Scores(self)
        self.player_interface = PlayerInterface(self.player, self.level)

    def load_textures(self):
       self.textures = {
           SOKOBAN.WALL: pygame.image.load('assets/images/wall.png').convert_alpha(),
           SOKOBAN.BOX: pygame.image.load('assets/images/box.png').convert_alpha(),
           SOKOBAN.TARGET: pygame.image.load('assets/images/target.png').convert_alpha(),
           SOKOBAN.TARGET_FILLED: pygame.image.load('assets/images/valid_box.png').convert_alpha(),
           SOKOBAN.PLAYER: pygame.image.load('assets/images/player_sprites.png').convert_alpha()
       }

    def load_level(self):
        self.level = Level(self.index_level)
        self.board = pygame.Surface((self.level.width, self.level.height))
        if self.player:
            self.player.pos = self.level.position_player
            self.player_interface.level = self.level
        else:
            self.player = Player(self.level)

    def start(self, numero):
        f = open("soluciones/" + str(numero) + ".txt","r")
        lines = []
        lines = f.readlines()
        
        while self.play:
            
            self.process_event(pygame.event.wait(), lines)
            self.update_screen()

        f.close()    

    def process_event(self, event, lines):
        if event.type == QUIT:
            pygame.quit()
            sys.exit()

        if event.type == KEYDOWN:
            if(event.key == K_ESCAPE):
                # Quit game
                self.play = False
                pygame.quit()
                sys.exit()

            #if(event.key == K_SPACE):

            while True:
                
                comando = lines[self.contador]

                if(comando == "F\n"):
                    
                    print("\nFIN\n")
                    
                    break
                    
                self.contador += 1
                self.player.move(event.key, self.level, self.player_interface, comando)
                
                self.update_screen()
                
                time.sleep(0.4)
                
            if(comando == "F\n"):

                time.sleep(2)
                
                pygame.quit()
                sys.exit()    
              
        if event.type == MOUSEBUTTONUP:
            self.player_interface.click(event.pos, self.level, self)
        if event.type == MOUSEMOTION:
            self.player_interface.mouse_pos = event.pos

    def update_screen(self):
        pygame.draw.rect(self.board, SOKOBAN.WHITE, (0,0, self.level.width * SOKOBAN.SPRITESIZE, self.level.height * SOKOBAN.SPRITESIZE))
        pygame.draw.rect(self.window, SOKOBAN.WHITE, (0,0,SOKOBAN.WINDOW_WIDTH,SOKOBAN.WINDOW_HEIGHT))

        self.level.render(self.board, self.textures)
        self.player.render(self.board, self.textures)

        pox_x_board = (SOKOBAN.WINDOW_WIDTH / 2) - (self.board.get_width() / 2)
        pos_y_board = (SOKOBAN.WINDOW_HEIGHT / 2) - (self.board.get_height() / 2)
        self.window.blit(self.board, (pox_x_board, pos_y_board))

        self.player_interface.render(self.window, self.index_level)

        pygame.display.flip()

    def has_win(self):
        nb_missing_target = 0
        for y in range(len(self.level.structure)):
            for x in range(len(self.level.structure[y])):
                if self.level.structure[y][x] == SOKOBAN.TARGET:
                    nb_missing_target += 1

        return nb_missing_target == 0
