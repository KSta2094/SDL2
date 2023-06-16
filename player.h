//
//  player.h
//  SDL2
//
//  Created by Konstantinas Zaveckas on 2023-06-12.
//
#pragma once
#ifndef player_h
#define player_h

#include <stdio.h>

#endif /* player_h */



#include <stdlib.h>
#include <SDL2/SDL.h>



struct Vector {
    
    int x;
    int y;
    
};

struct Bullet{
    
    SDL_Rect hitBox;
    
    
    
    struct Vector postition ;
    
    int hasHit;
    
    
};

struct Player{
  
    SDL_Rect playerHitBox;
    
    
};

struct Alines{
    
    SDL_Rect alines[12];
    int move;
    

    
};
void update(struct Bullet *bullet,struct Player *player,struct Alines *aliens,SDL_Texture *text,SDL_Renderer *render);

void aliensInit(struct Alines *aliens,SDL_Texture *text,SDL_Renderer *render);
void shootBullet(struct Bullet *bullet,struct Player player,int *boolean);

void moveBullet(struct Bullet *bullet);
int doOverlap(SDL_Rect alien,SDL_Rect bullet);
