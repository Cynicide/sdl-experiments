#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <array>

// Constants and Global Variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int Length;
const Uint8* keyboardState = SDL_GetKeyboardState(&Length);

enum CollisionType {
    HORIZONTAL,
    VERTICAL,
    NONE
};

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
    SDL_FRect rect()
    {
        return { pos.x, pos.y, (float)width, (float)height };
    }
};

struct Paddle {
    Vector2d pos;
    Vector2d vel;
    int width;
    int height;
    int score;
    SDL_FRect rect()
    {
        return { pos.x, pos.y, (float)width, (float)height };
    }
};

// Method  Definitions
bool initSDL();
void closeSDL();
void renderScreen(SDL_FRect rectList);
CollisionType checkCollision(SDL_FRect rectA, SDL_FRect rectB);

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
            SDL_RenderSetVSync(gRenderer, 1);
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

void renderScreen(SDL_FRect rectList[3]) 
{
    SDL_SetRenderDrawColor(gRenderer, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    int rectdraw = SDL_RenderDrawRectsF(gRenderer, rectList, 3);
    if (rectdraw == -1) 
        {
        printf("Rectangles could not be created! SDL_Error: %s\n", SDL_GetError());
        }
            SDL_RenderPresent(gRenderer);
}

CollisionType checkCollision(SDL_FRect rectA, SDL_FRect rectB) 
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = rectA.x;
    rightA = rectA.x + rectA.w;
    topA = rectA.y;
    bottomA = rectA.y + rectA.h;

    leftB = rectB.x;
    rightB = rectB.x + rectB.w;
    topB = rectB.y;
    bottomB = rectB.y + rectB.h;

    if (bottomA <= topB) 
    {
        return NONE;
    }
    if (topA >= bottomB) 
    {
        return NONE;
    }
    if (rightA <= leftB) 
    {
        return NONE;
    }
    if (leftA >= rightB) 
    {
        return NONE;
    }

    printf("------\n");
    if (leftA < leftB) 
    {
        printf("Left\n");
        return HORIZONTAL;
    }
    if (leftA > leftB) 
    {
        printf("Right\n");
        return HORIZONTAL;
    }
    if (topA < topB) 
    {
        printf("Top\n");
        return VERTICAL;
    }
    if (topA > topB) 
    {
        printf("Bottom\n");
        return VERTICAL;
    }
    return NONE;
}

// Main
int main (int argc, char* args[]) 
{
    printf("SDL is starting");
    if( !initSDL()) 
    {
        printf("Failed to Initialize!\n");
        closeSDL();
        return 1;
    }
    bool quit = false;
    SDL_Event e;

    Ball ball{};
    ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
    ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;
    ball.vel.x = 2.f;
    ball.vel.y = 2.f;
    ball.width = 20;
    ball.height = 20;

    Paddle paddle_p1{};

    paddle_p1.pos.x = SCREEN_WIDTH / 5;
    paddle_p1.pos.y = SCREEN_HEIGHT /2 + paddle_p1.height / 2;
    paddle_p1.vel.x = 4.f;
    paddle_p1.vel.y = 4.f;
    paddle_p1.width = 20;
    paddle_p1.height = 80;
    paddle_p1.score = 0;

    Paddle paddle_p2{};

    paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 5);
    paddle_p2.pos.y = SCREEN_HEIGHT / 2 + paddle_p2.height / 2;
    paddle_p2.vel.x = 4.f;
    paddle_p2.vel.y = 4.f;
    paddle_p2.width = 20;
    paddle_p2.height = 80;
    paddle_p2.score = 0;

    while( !quit )
    {
        // Move the Ball
        ball.pos.x += ball.vel.x;
        ball.pos.y += ball.vel.y;

        // Reverse the Direction if it hits a wall
        if (ball.pos.x < 0 || ball.pos.x > SCREEN_WIDTH - ball.width) 
        {
            ball.vel.x = ball.vel.x * -1;
        }
    
        if (ball.pos.y < 0 || ball.pos.y > SCREEN_HEIGHT - ball.height) 
        {
            ball.vel.y = ball.vel.y * -1;
        }

        // Reverse Direction if we hit a paddle
        CollisionType p1_collision = checkCollision(ball.rect(), paddle_p1.rect());
        CollisionType p2_collision = checkCollision(ball.rect(), paddle_p2.rect());

        switch (p1_collision)
        {
            case HORIZONTAL:
                ball.vel.x = ball.vel.x * -1;
                break;
            case VERTICAL:
                ball.vel.y = ball.vel.y * -1;
                break;
            case NONE:          
                break;   
            default:
                break;
        }

        switch (p2_collision)
        {
            case HORIZONTAL:
                ball.vel.x = ball.vel.x * -1;
                break;
            case VERTICAL:
                ball.vel.y = ball.vel.y * -1;
                break;
            case NONE:          
                break;   
            default:
                break;
        }

        //if (p1_collision || p2_collision)
        //{
        //    ball.vel.x = ball.vel.x * -1;
        //}

        // Player Controls
        if(keyboardState[SDL_SCANCODE_A]) 
        {
            if (paddle_p1.pos.y > 0) 
            {
                paddle_p1.pos.y = paddle_p1.pos.y - paddle_p1.vel.y;
            }
        }
        if(keyboardState[SDL_SCANCODE_Z]) 
        {
            if (paddle_p1.pos.y < SCREEN_HEIGHT - paddle_p1.height) 
            {
                paddle_p1.pos.y = paddle_p1.pos.y + paddle_p1.vel.y;
            }
        }
        if(keyboardState[SDL_SCANCODE_K]) 
        {
            if (paddle_p2.pos.y > 0) 
            {
                paddle_p2.pos.y = paddle_p2.pos.y - paddle_p2.vel.y;
            }
        }
        if(keyboardState[SDL_SCANCODE_M]) 
        {
            if (paddle_p2.pos.y < SCREEN_HEIGHT - paddle_p2.height) 
            {
                paddle_p2.pos.y = paddle_p2.pos.y + paddle_p2.vel.y;
            }
        }   

        // Check for Events
        while ( SDL_PollEvent( &e ) != 0) 
        {
            // Quit if we get a quit event 
            if( e.type == SDL_QUIT) 
            {
                quit = true;
            } 
            else 
            {
                if (e.type == SDL_KEYDOWN) 
                {
                   
                }                        
            }
        }
        SDL_FRect rectList[] = {ball.rect(), paddle_p1.rect(), paddle_p2.rect()};
        renderScreen(rectList);
    }
    closeSDL();
    return 0;
}