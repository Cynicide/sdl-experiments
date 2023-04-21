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

void PlayState::update(float dt)
{
   paddle.update(dt);
   ball.update(dt);
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