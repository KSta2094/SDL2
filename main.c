#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "WinCondition.h"

#define TITLE "SPACE INVADERS"


int Hasfinish(struct Alines *alien,struct Player *player)
{
    
    for(int i =0;i <= sizeof(alien->alines)/sizeof(alien->alines[0]);i++){
        
     
        if(alien->alines[i].y == 800){
            return 1;
        }
        if( SDL_HasIntersection(&alien->alines[i],&player->playerHitBox)){
            return 1;
        }
        
    }
   
    
    return  0;
}
 



int main(int argc, const char * argv[]) {
    
    
    
    struct Alines aliens;
 
struct Bullet bullet;
    
    bullet.hitBox.x = 800/2;
    bullet.hitBox.y = 800/2;
    
    bullet.hitBox.w = 4;
    bullet.hitBox.h = 4;
    
   
    // returns zero on success else non-zero
    if( ! IMG_Init(IMG_INIT_PNG)){
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    };
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow(TITLE,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800, 800, SDL_WINDOW_SHOWN);
    
    
    SDL_Surface *icon= IMG_Load("/Users/konstantinasz/sdl2/SDL2/SDL2/Photos/LOGO.png");

    SDL_SetWindowIcon(win, icon);
    
    SDL_FreeSurface(icon);

    
    
    
    
    
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(renderer, 247, 247, 247, 255 );

    
    
    
    struct Player player;
    
  
    
    player.playerHitBox.x = 100;
    player.playerHitBox.y = 700;
    bullet.hasHit =1;
    bullet.postition.x = -10;
    bullet.postition.y = -10;
    
    SDL_RenderClear(renderer);
    
    SDL_Surface *surfice = IMG_Load("/Users/konstantinasz/sdl2/SDL2/SDL2/Photos/spaceship.png");
    //
    
    
    SDL_Texture *bulletText = IMG_LoadTexture(renderer, "/Users/konstantinasz/sdl2/SDL2/SDL2/red-square-png-14.png");
    SDL_SetTextureColorMod(bulletText, 0, 255, 255);
    
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surfice);


    
    if(!text){
        printf("Error : %s", SDL_GetError());
        SDL_DestroyTexture(text);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    
    SDL_FreeSurface(surfice);
    
    
    
    
    SDL_QueryTexture(text, NULL, NULL, &player.playerHitBox.w,  &player.playerHitBox.h );
    SDL_QueryTexture(bulletText, NULL, NULL,&player.playerHitBox.w,  &player.playerHitBox.h );
    
    
    

    
    
    

    int down =0;
    int up =0;
    int left =0;
    int right =0;
    int a =1;
    int shoot =0;
 
    SDL_Texture *alienText =IMG_LoadTexture(renderer, "/Users/konstantinasz/sdl2/SDL2/SDL2/Photos/invaders.png");
    
    
    aliensInit(&aliens, alienText, renderer);
    printf("%i",aliens.alines[0].x);
    while (a)
    {
      
        SDL_RenderClear(renderer);
        
        update(&bullet, &player, &aliens,alienText,renderer);
        
        
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            
            //keyboard contoll
            switch (e.type){
                    
                case SDL_KEYDOWN:
                
                    switch(e.key.keysym.scancode){
                        case SDL_SCANCODE_W:
                            up = 1;
                            break;
                    case SDL_SCANCODE_S:
                            down = 1;
                            break;
                    case SDL_SCANCODE_D:
                            right = 1;
                            break;
                    case SDL_SCANCODE_A:
                            left = 1;
                            break;
                        case SDL_SCANCODE_Q:
                            shootBullet(&bullet,player ,&shoot);
                            bullet.hasHit =0;
                            
                           
                            break;
                            
                        default:
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.scancode){
                       
                        case SDL_SCANCODE_W:
                            up = 0;
                            break;
                    case SDL_SCANCODE_S:
                            down = 0;
                            break;
                    case SDL_SCANCODE_D:
                            right = 0;
                            break;
                    case SDL_SCANCODE_A:
                            left = 0;
                            break;
                            
                            
                        default:
                            break;
                    }
                
            }
            
            if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                SDL_DestroyTexture(alienText);
                SDL_DestroyTexture(text);
                SDL_DestroyTexture(bulletText);
               
                SDL_DestroyWindow(win);
                SDL_Quit();
                a =0;
                break;
            }
            
            
        }
        
        // main code :
        
       
       moveBullet(&bullet);
        
        
        if(shoot){
            
            bullet.hitBox.y =    player.playerHitBox.y;
            bullet.hitBox.x =    player.playerHitBox.x;
            shoot = 0;
            
        }
       
      
        //controll
        if(up){
            player.playerHitBox.y -= 3;
            
        }
        if(down){
            player.playerHitBox.y += 3;
            
        }if(right){
            player.playerHitBox.x += 3;
            
        }if(left){
            player.playerHitBox.x -= 3;
            
        }
    
    
       
        
        if(Hasfinish(&aliens, &player)){
            break;
        }
    

    SDL_RenderCopy(renderer, text, NULL, &player.playerHitBox);
    SDL_RenderCopy(renderer, bulletText, NULL,&bullet.hitBox );
       
    
    SDL_RenderPresent(renderer);
    
    SDL_Delay(1000/60);
    
    
}
    SDL_DestroyRenderer(renderer);
    return 0;
}
