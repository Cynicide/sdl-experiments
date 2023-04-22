#include <PlayState.h>

PlayState PlayState::sPlayState;

PlayState::PlayState() {

}

PlayState* PlayState::get()
{
    //Get static instance
    return &sPlayState;
}

bool PlayState::enter()
{
    SDL_Log("Entered PlayState\n");
    //Loading success flag
    bool success = true;
 
   // Set Up Game
    background = Background(); 
    border = Border();

    lightning = Lightning();

    paddle = Paddle();
    ball = Ball();

    brickManager = BrickManager();

    brickManager.LoadLevel();
    brickManager.CreateLevel();

    subState = SERVING;

    return success;
}

bool PlayState::exit()
{

    SDL_Log("Exited PlayState\n");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{

}

void PlayState::update(double dt)
{
    switch(subState) {
        case SERVING: {
            paddle.update(dt);
            ball.update(dt, paddle.paddleRect);
            int mx, my;
            Uint32 mouseState = SDL_GetMouseState(&mx, &my);
            if (mouseState == SDL_BUTTON(1)) {
                //ball.randomizeXDirection();
                subState = PLAYING;
            }
            break;
        }
        case PLAYING:
        {
            paddle.update(dt);
            ball.update(dt);
            if (physics.AABBCheck(ball.ballRect, border.tBorder) || physics.AABBCheck(ball.ballRect, lightning.bBorder)) {
                ball.flipY();
            }

            if (physics.AABBCheck(ball.ballRect, border.rBorder) || physics.AABBCheck(ball.ballRect, border.lBorder))  {
                ball.flipX();
            }           
            break;
        }

        case DYING:
            {
                break;
            }
        case GAMEOVER:
            {
                break;
            }
    }
}

void PlayState::render()
{
    background.render();
    lightning.render();
    border.render();
    paddle.render();
    
    brickManager.render();
    
    ball.render();

}