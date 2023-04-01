#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

// Constants and Global Variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Structs
typedef struct {
    float x;
    float y;
} Vector2d;

struct Ball {
    Vector2d pos;
    Vector2d vel;
    int width;
    int height;
    SDL_FRect rect;
};

struct Paddle {
    Vector2d pos;
    Vector2d vel;
    int width;
    int height;
    SDL_FRect rect;
};

// Method  Definitions
bool initSDL();
void closeSDL();

// Methods
bool initSDL () {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Could not be initialized! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } 
    else 
    {
        gWindow = SDL_CreateWindow("SDL Tutorial 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) 
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } 
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            //SDL_RenderSetVSync(gRenderer, 1);
        }
    }
    return success;
}

void closeSDL() 
{
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_Quit();
}

// Main
int main (int argc, char* args[]) {
    printf("SDL is starting");
    if( !initSDL()) 
    {
        printf("Failed to Initialize!\n");
    }
    else 
    {
            bool quit = false;
            SDL_Event e;

            Ball ball;
            ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
            ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;
            ball.vel.x = 2.f;
            ball.vel.y = 2.f;
            ball.width = 20;
            ball.height = 20;
            ball.rect = { ball.pos.x, ball.pos.y, (float)ball.width, (float)ball.height}; 

            Paddle paddle_p1;

            paddle_p1.pos.x = SCREEN_WIDTH / 5;
            paddle_p1.pos.y = SCREEN_HEIGHT /2 + paddle_p1.height / 2;
            paddle_p1.vel.x = 0.f;
            paddle_p1.vel.y = 0.f;
            paddle_p1.width = 20;
            paddle_p1.height = 80;
            paddle_p1.rect = {paddle_p1.pos.x, paddle_p1.pos.y, (float)paddle_p1.width, (float)paddle_p1.height};

            Paddle paddle_p2;

            paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 5);
            paddle_p2.pos.y = SCREEN_HEIGHT / 2 + paddle_p2.height / 2;
            paddle_p2.vel.x = 0.f;
            paddle_p2.vel.y = 0.f;
            paddle_p2.width = 20;
            paddle_p2.height = 80;
            paddle_p2.rect = {paddle_p2.pos.x, paddle_p2.pos.y, (float)paddle_p2.width, (float)paddle_p2.height};
    
            while( !quit )
            {

                /*ball.pos.x += ball.vel.x;
                ball.pos.y += ball.vel.y;

                if (ball.pos.x < 0 || ball.pos.x > SCREEN_WIDTH - ball.width) {
                    ball.vel.x = ball.vel.x * -1;
                    }
            
                if (ball.pos.y < 0 || ball.pos.y > SCREEN_HEIGHT - ball.height) {
                    ball.vel.y = ball.vel.y * -1;
                    }

                ball.rect.x = ball.pos.x;
                ball.rect.y = ball.pos.y;*/

                while ( SDL_PollEvent( &e ) != 0) 
                {
                    if( e.type == SDL_QUIT) 
                    {
                        quit = true;
                    } 
                }

            SDL_FRect rectlist[] = {ball.rect, paddle_p1.rect, paddle_p2.rect};            
            int rectlistsize = sizeof(rectlist) / sizeof(SDL_FRect);

            SDL_SetRenderDrawColor(gRenderer, 0,0,0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(gRenderer);
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            int rectdraw = SDL_RenderDrawRectsF(gRenderer, rectlist, rectlistsize);
            if (rectdraw == -1) 
                {
                printf("Rectangles could not be created! SDL_Error: %s\n", SDL_GetError());
                }
            SDL_RenderPresent(gRenderer);
            }
    }
    closeSDL();
    return 0;
}