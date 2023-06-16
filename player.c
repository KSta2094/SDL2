//
//  player.c
//  SDL2
//
//  Created by Konstantinas Zaveckas on 2023-06-12.
//

#include "player.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

void setUp(){
    
}


void aliensInit(struct Alines *aliens,SDL_Texture *text,SDL_Renderer *render){
    
    int x =10;

    for(int i =0;i <= sizeof((*aliens).alines)/sizeof((*aliens).alines[0]);i++){
        
        x+=45;
        (*aliens).alines[i].x = x;
        (*aliens).alines[i].y = 45;
        (*aliens).alines[i].w = 45;
        (*aliens).alines[i].h = 45;
    }
   
}


void renderAliens(struct Alines *alien,SDL_Texture *text,SDL_Renderer *render){
    
    
    
    
    
    for (int i=0; i <= sizeof((*alien).alines)/sizeof((*alien).alines[0]); i++) {
        
       (*alien).move++;
        if( (*alien).move >=2 ){
            (*alien).move =0;
            (*alien).alines[i].y++;
            (*alien).alines[i].x = (*alien).alines[i].x ;
        }
        
        SDL_RenderCopy(render, text, NULL, &(*alien).alines[i]);
        
      

        
    }
    
}




void shootBullet(struct Bullet *bullet,struct Player player,int *boolean){

    
    if((*bullet).hasHit == 1 ){
        (*bullet).hasHit = 0;
        (*boolean) =1;
        
    }
    
    
}

void moveBullet(struct Bullet *bullet){
    (*bullet).hitBox.y-=7;
}


void update(struct Bullet *bullet,struct Player *player,struct Alines *aliens,SDL_Texture *text,SDL_Renderer *render){
    
    renderAliens(aliens, text, render);
    
    for (int i=0; i <= sizeof((*aliens).alines)/sizeof((*aliens).alines[0]); i++) {

        
        if(SDL_HasIntersection(&(*aliens).alines[i], &(*bullet).hitBox)){
                        (*bullet).hitBox.y -=800;
            
                        (*aliens).alines[i].y =0;

            printf("Hit \n");
        }
        
//        if(doOverlap((*aliens).alines[i], (*bullet).hitBox)){
//
//            (*bullet).hitBox.y -=800;
//
//            (*aliens).alines[i].y =0;
//
//        }
       
    }
    
    
    if(bullet){
        if((*bullet).hitBox.y <= 0 ){
            
            
            
            (*bullet).hasHit =1;
            
        }
    }
    
    
    
    
    
}




int doOverlap(SDL_Rect alien,SDL_Rect bullet)
{
    // if rectangle has area 0, no overlap
    if (alien.x == alien.x +5|| alien.y == alien.y+5 || bullet.x == bullet.x+5|| bullet.y == bullet.y+5){
        printf("flase \n");
        return 0;
        
    }
    // If one rectangle is on left side of other
    if (alien.x > bullet.x+5 || alien.x+5 > bullet.x){
        printf("flase \n");
        return 0;
    }
    // If one rectangle is above other
    if (bullet.y > alien.y+5 || bullet.y +5> alien.y){
        printf("flase \n");
        return 0;
    }
    printf("hit");
    return 1;
}



