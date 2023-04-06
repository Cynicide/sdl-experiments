#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <iostream>


// Constants and Global Variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int Length;
const Uint8* keyboardState = SDL_GetKeyboardState(&Length);

// Enums
enum State {
    WAITINGTOSTART,
    PLAYING,
    SERVE,
    GAMEOVER
};

// Templates

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Structs
typedef struct {
    float x;
    float y;
} Vector2d;

struct Text {
    SDL_Texture * texture;
    SDL_Rect textRect;
    SDL_Surface * surface;
    int textW;
    int textH;
};

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
    Text scoreText;
};

// Method  Definitions
bool initSDL();
void closeSDL();
Text createText(TTF_Font * font, std::string text, int x_loc, int y_loc);
void renderScreen(SDL_FRect rectList, State &state, Text attractText, Paddle paddle_p1, Paddle paddle_p2, Text gameOverText, Text playAgainText);
void checkCollision(Ball &rectA, Paddle rectB);
void gameplayState(Ball &ball, Paddle &paddle_p1, Paddle &paddle_p2, State &state, TTF_Font * font);
void gamestartState(State &state);
void gameserveState(State &state);
void gameoverState(Paddle &paddle_p1, Paddle &paddle_p2, State &state, Ball &ball, TTF_Font * font);

// Methods
bool initSDL () {

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL Could not be initialized! SDL_Error: %s\n", SDL_GetError();
        return false;
    } 
    if (TTF_Init() < 0)
    {
        std::cout << "SDL TTF Could not be initialized! SDL_Error: %s\n", SDL_GetError();
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) 
    {
        std::cout << "Window could not be created! SDL_Error: %s\n", SDL_GetError();
        return false;
    } 

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetVSync(gRenderer, 1);
    return true;
}

void closeSDL() 
{
    SDL_DestroyWindow( gWindow );
    TTF_Quit();
    gWindow = NULL;
    SDL_Quit();
}

void renderScreen(SDL_FRect rectList[3], State &state,  Text attractText, Paddle paddle_p1, Paddle paddle_p2, Text gameOverText, Text playAgainText) 
{
    SDL_SetRenderDrawColor(gRenderer, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
    switch (state) {
        case WAITINGTOSTART:
            SDL_RenderCopy(gRenderer, attractText.texture, NULL, &attractText.textRect);
            break;
        case PLAYING:
            SDL_RenderCopy(gRenderer, paddle_p1.scoreText.texture, NULL, &paddle_p1.scoreText.textRect);
            SDL_RenderCopy(gRenderer, paddle_p2.scoreText.texture, NULL, &paddle_p2.scoreText.textRect);
            break;
        case SERVE:
            SDL_RenderCopy(gRenderer, paddle_p1.scoreText.texture, NULL, &paddle_p1.scoreText.textRect);
            SDL_RenderCopy(gRenderer, paddle_p2.scoreText.texture, NULL, &paddle_p2.scoreText.textRect);
            break;
        case GAMEOVER:
            SDL_RenderCopy(gRenderer, gameOverText.texture, NULL, &gameOverText.textRect);
            SDL_RenderCopy(gRenderer, playAgainText.texture, NULL, &playAgainText.textRect);
            SDL_RenderCopy(gRenderer, paddle_p1.scoreText.texture, NULL, &paddle_p1.scoreText.textRect);
            SDL_RenderCopy(gRenderer, paddle_p2.scoreText.texture, NULL, &paddle_p2.scoreText.textRect);
            break;
        } 
    
    int rectdraw = SDL_RenderDrawRectsF(gRenderer, rectList, 3);
    if (rectdraw == -1) 
        {
        std::cout << "Rectangles could not be created! SDL_Error: %s\n", SDL_GetError();
        }
        SDL_RenderPresent(gRenderer);
}

Text createText(TTF_Font * font, std::string text, int x_loc, int y_loc) {
    Text txt;
    SDL_Color color = { 255, 255, 255 };
    txt.surface = TTF_RenderText_Solid(font, text.c_str(), color);
    txt.texture = SDL_CreateTextureFromSurface(gRenderer, txt.surface);
    SDL_QueryTexture(txt.texture, NULL, NULL, &txt.textW, &txt.textH);
    txt.textRect = {x_loc, y_loc, txt.textW, txt.textH};
    return txt;
}

void checkCollision(Ball &rectA, Paddle rectB) 
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    int nextLeftA, nextRightA;
    int nextTopA, nextBottomA;

    leftA = rectA.pos.x;
    rightA = rectA.pos.x + rectA.width;
    topA = rectA.pos.y;
    bottomA = rectA.pos.y + rectA.height;

    leftB = rectB.pos.x;
    rightB = rectB.pos.x + rectB.width;
    topB = rectB.pos.y;
    bottomB = rectB.pos.y + rectB.height;

    // Variables for looking 1 frame ahead
    nextLeftA = leftA + rectA.vel.x;
    nextRightA = rightA + rectA.vel.x;
    nextTopA = topA + rectA.vel.y;
    nextBottomA = bottomA + rectA.vel.y;

    // Taken from - https://happycoding.io/tutorials/processing/collision-detection#collision-detection-with-moving-objects
    //if I keep moving in my current X direction, will I collide with the paddle rectangle?
    if (nextRightA > leftB &&
        nextLeftA < rightB &&
        bottomA > topB &&
        topA < bottomB)        
        {
            int rectAMidpoint_x = leftA + rightA / 2;
            int rectBMidpoint_x = leftA + leftB / 2;
            if (rectAMidpoint_x > rectBMidpoint_x) {
                if (sgn(rectA.vel.x) != 1) {
                    rectA.vel.x = rectA.vel.x * -1;
                }
            } else {
                if (sgn(rectA.vel.x) != -1) {
                    rectA.vel.x = rectA.vel.x * -1;
                }
            }
        }

    //if I keep moving in my current Y direction, will I collide with the paddle rectangle?
    if (rightA > leftB &&
        leftA < rightB &&
        nextBottomA > topB &&
        nextTopA < bottomB) {
            float rectAMidpoint_y = topA + bottomA / 2;
            float rectBMidpoint_y = topB + bottomB / 2;
            // If we are below the paddle check that the ball is moving in the right direction and adjust if not
            if (rectAMidpoint_y > rectBMidpoint_y) {
                if (sgn(rectA.vel.y) != 1) {
                    rectA.vel.y = rectA.vel.y * -1;
                }
            } else {
                // If we are above the paddle check that the ball is moving in the right direction and adjust if not
                if (sgn(rectA.vel.y) != -1) {
                    rectA.vel.y = rectA.vel.y * -1;
                }
            }
        }
}

void gamestartState(State &state) {
     if(keyboardState[SDL_SCANCODE_SPACE]) 
        {
            state = PLAYING;
        }
}

void gameserveState(State &state, Ball &ball, Paddle &paddle_p1, Paddle &paddle_p2) {
    ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
    ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;
    ball.vel.x = 5.f;
    if (std::rand() % 2 == 0) {
        ball.vel.x = 5.f * (float)-1;
    }
    ball.vel.y = 5.f;
    if (std::rand() % 2 == 0) {
        ball.vel.y = 5.f * (float)-1;
    }  
    paddle_p1.pos.x = SCREEN_WIDTH / 6;
    paddle_p1.pos.y = SCREEN_HEIGHT /2 - paddle_p1.height / 2;
    paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 6);
    paddle_p2.pos.y = SCREEN_HEIGHT / 2 - paddle_p2.height / 2;


     if(keyboardState[SDL_SCANCODE_SPACE]) 
        {
            state = PLAYING;
        }
}

void gameoverState(Paddle &paddle_p1, Paddle &paddle_p2, State &state, Ball &ball, TTF_Font * font) {
    ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
    ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;

    ball.vel.x = 5.f;
    ball.vel.y = 5.f;

    paddle_p1.pos.x = SCREEN_WIDTH / 6;
    paddle_p1.pos.y = SCREEN_HEIGHT /2 - paddle_p1.height / 2;
    paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 6);
    paddle_p2.pos.y = SCREEN_HEIGHT / 2 - paddle_p2.height / 2;

    if(keyboardState[SDL_SCANCODE_SPACE]) 
    {
        paddle_p1.score = 0;
        SDL_DestroyTexture(paddle_p1.scoreText.texture);
        SDL_FreeSurface(paddle_p1.scoreText.surface);
        paddle_p1.scoreText = createText(font, std::to_string(paddle_p1.score), SCREEN_WIDTH / 2 - 20, 10);

        paddle_p2.score = 0;
        SDL_DestroyTexture(paddle_p2.scoreText.texture);
        SDL_FreeSurface(paddle_p2.scoreText.surface);
        paddle_p2.scoreText = createText(font, std::to_string(paddle_p2.score), SCREEN_WIDTH / 2 + 20, 10);
        state = PLAYING;
    }
}

void gameplayState(Ball &ball, Paddle &paddle_p1, Paddle &paddle_p2, State &state, TTF_Font * font) {
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

        // Collision Detection. Only do so if the ball is on the same side of the screen as the paddle.
        if (ball.pos.x < SCREEN_WIDTH / 2) 
        {
            checkCollision(ball, paddle_p1);
        }
        
        if (ball.pos.x > SCREEN_WIDTH / 2) {
            checkCollision(ball, paddle_p2);
        } 
        
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
        // Scoring
        if (ball.pos.x <= 0) {
            paddle_p2.score = paddle_p2.score + 1;
            SDL_DestroyTexture(paddle_p2.scoreText.texture);
            SDL_FreeSurface(paddle_p2.scoreText.surface);
            paddle_p2.scoreText = createText(font, std::to_string(paddle_p2.score), SCREEN_WIDTH / 2 + 20, 10);
            state = SERVE;
        }

        if (ball.pos.x >= SCREEN_WIDTH - ball.width) {
            paddle_p1.score = paddle_p1.score + 1;
            SDL_DestroyTexture(paddle_p1.scoreText.texture);
            SDL_FreeSurface(paddle_p1.scoreText.surface);
            paddle_p1.scoreText = createText(font, std::to_string(paddle_p1.score), SCREEN_WIDTH / 2 - 30, 10);
            state = SERVE;
        }

        if (paddle_p1.score == 20 || paddle_p2.score == 20) {
            state = GAMEOVER;
        }
}

// Main
int main (int argc, char* args[]) 
{
    //SDL_Log("SDL is starting");
    if( !initSDL()) 
    {
        std::cout << "Failed to Initialize!\n";
        closeSDL();
        return 1;
    }

    TTF_Font * font = TTF_OpenFont("assets\\PublicPixel.ttf", 14);
    TTF_Font * smallfont = TTF_OpenFont("assets\\PublicPixel.ttf", 12);
    Text attracttxt = createText(font, "Press Space to Start!", 0, 0);
    Text gameoverText = createText(font, "Game Over!", 0, 0);
    Text playAgainText = createText(smallfont, "Press Space to try again!", 0, 30);

    std::srand(time(nullptr));

    bool quit = false;
    SDL_Event e;

    Ball ball{};

    ball.width = 10;
    ball.height = 10;
    ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
    ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;
    ball.vel.x = 5.f;
    if (std::rand() % 2 == 0) {
        ball.vel.x = 5.f * (float)-1;
    }
    ball.vel.y = 5.f;
    if (std::rand() % 2 == 0) {
        ball.vel.y = 5.f * (float)-1;
    }  

    Paddle paddle_p1{};

    paddle_p1.width = 20;
    paddle_p1.height = 100;
    paddle_p1.pos.x = SCREEN_WIDTH / 6;
    paddle_p1.pos.y = SCREEN_HEIGHT /2 - paddle_p1.height / 2;
    paddle_p1.vel.x = 5.f;
    paddle_p1.vel.y = 5.f;
    paddle_p1.score = 10;
    paddle_p1.scoreText = createText(font, std::to_string(paddle_p1.score), SCREEN_WIDTH / 2 - 20, 10);

    Paddle paddle_p2{};

    paddle_p2.width = 20;
    paddle_p2.height = 100;
    paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 6);
    paddle_p2.pos.y = SCREEN_HEIGHT / 2 - paddle_p2.height / 2;
    paddle_p2.vel.x = 5.f;
    paddle_p2.vel.y = 5.f;
    paddle_p2.score = 10; 
    paddle_p2.scoreText = createText(font, std::to_string(paddle_p2.score), SCREEN_WIDTH / 2 + 10, 10);

    State state = WAITINGTOSTART;
    
    while( !quit )
    {
        switch(state) {
            case WAITINGTOSTART:
                gamestartState(state);
                break;
            case PLAYING:
                gameplayState(ball, paddle_p1, paddle_p2, state, font);
                break;
            case SERVE:
                gameserveState(state, ball, paddle_p1, paddle_p2);
                break;
            case GAMEOVER:
                gameoverState(paddle_p1, paddle_p2, state, ball, font);
                break;
        }

        // Check for Events
        while ( SDL_PollEvent( &e ) != 0) 
        {
            // Quit if we get a quit event 
            if( e.type == SDL_QUIT) 
            {
                quit = true;
            }
        }
        SDL_FRect rectList[] = {ball.rect(), paddle_p1.rect(), paddle_p2.rect()};
        renderScreen(rectList, state, attracttxt, paddle_p1, paddle_p2, gameoverText, playAgainText);
    }
    TTF_CloseFont(font);
    SDL_DestroyTexture(attracttxt.texture);
    SDL_FreeSurface(attracttxt.surface);

    SDL_DestroyTexture(paddle_p1.scoreText.texture);
    SDL_FreeSurface(paddle_p1.scoreText.surface);

    SDL_DestroyTexture(paddle_p2.scoreText.texture);
    SDL_FreeSurface(paddle_p2.scoreText.surface);
    closeSDL();
    return 0;
}