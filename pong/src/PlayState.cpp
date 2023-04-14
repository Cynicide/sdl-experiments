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

    ball.width = 10;
    ball.height = 10;
    ball.pos.x = SCREEN_WIDTH / 2 - ball.width / 2;
    ball.pos.y = SCREEN_HEIGHT /2 - ball.height / 2;
    
    ball.starting_vel = starting_vel;
    ball.current_vel = ball.starting_vel;
    ball.speedup_vel = speedup_vel;
    ball.max_vel = max_vel;

    ball.RandSetBallVelocity();

    paddle_p1.width = 20;
    paddle_p1.height = 100;
    paddle_p1.pos.x = SCREEN_WIDTH / 10;
    paddle_p1.pos.y = SCREEN_HEIGHT /2 - paddle_p1.height / 2;
    paddle_p1.vel.x = 5.f;
    paddle_p1.vel.y = 5.f;
    paddle_p1.score = 0;
    paddle_p1.scoreText = Text(font, std::to_string(paddle_p1.score).c_str(), SCREEN_WIDTH / 2 - 20, 10, gRenderer);

    paddle_p2.width = 20;
    paddle_p2.height = 100;
    paddle_p2.pos.x = SCREEN_WIDTH - (SCREEN_WIDTH / 10);
    paddle_p2.pos.y = SCREEN_HEIGHT / 2 - paddle_p2.height / 2;
    paddle_p2.vel.x = 5.f;
    paddle_p2.vel.y = 5.f;
    paddle_p2.score = 0; 
    paddle_p2.scoreText = Text(font, std::to_string(paddle_p2.score).c_str(), SCREEN_WIDTH / 2 + 10, 10, gRenderer);

    return success;
}

bool PlayState::exit()
{
    paddle_p1.Destroy();
    paddle_p2.Destroy();
    SDL_Log("Exited PlayState\n");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{

}

void PlayState::update(float dt)
{
    if (substate == SERVE ) 
    {
        ball.ResetPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
    
        // Reset the ball velocity
        ball.ResetVel();

        // Prepare for a new serve
        ball.RandSetBallVelocity(); 

        paddle_p1.ResetPos(SCREEN_HEIGHT);
        paddle_p2.ResetPos(SCREEN_HEIGHT);

        if(keyboardState[SDL_SCANCODE_SPACE]) 
        {
            substate = PLAYING;
        }
    }
    else 
    {   
        // Move the Ball
        ball.Move(dt);

        if (ball.pos.y < 0 ) 
        {
            if (sgn(ball.vel.y) != 1) {
                ball.vel.y = ball.vel.y * -1;
                Mix_PlayChannel( -1, gPong, 0 );
            }
        }

        if (ball.pos.y > SCREEN_HEIGHT - ball.height) {
            if (sgn(ball.vel.y) != -1) {
                ball.vel.y = ball.vel.y * -1;
                Mix_PlayChannel( -1, gPong, 0 );
            }
        }

        // Collision Detection. Only do so if the ball is on the same side of the screen as the paddle.
        if (ball.pos.x < SCREEN_WIDTH / 2) 
        {
            bpb = physics.GetSweptBroadphaseBox(ball);
            if (physics.AABBCheck(bpb, paddle_p1)) 	
                {                
                std::cout << "---------------------------------\n";
                ball.SpeedUp();                
                physics.ProcessCollision(ball, paddle_p1);
                Mix_PlayChannel( -1, gPing, 0 );
                bpb.UpdateRect();
                }
        }
        
        if (ball.pos.x > SCREEN_WIDTH / 2) {
            bpb = physics.GetSweptBroadphaseBox(ball);
            if (physics.AABBCheck(bpb, paddle_p2)) 	
                {
                std::cout << "---------------------------------\n";
                ball.SpeedUp();
                physics.ProcessCollision(ball, paddle_p2);
                Mix_PlayChannel( -1, gPing, 0 );
                bpb.UpdateRect();
                }
        } 
        
        // Player Controls
        if(keyboardState[SDL_SCANCODE_A]) 
        {
            paddle_p1.MoveUp(dt);
        }
        if(keyboardState[SDL_SCANCODE_Z]) 
        {
            paddle_p1.MoveDown(SCREEN_HEIGHT, dt);
        }
        if(keyboardState[SDL_SCANCODE_K]) 
        {
            paddle_p2.MoveUp(dt);
        }
        if(keyboardState[SDL_SCANCODE_M]) 
        {
            paddle_p2.MoveDown(SCREEN_HEIGHT, dt);
        }
        paddle_p1.UpdateRect();
        paddle_p2.UpdateRect();
        

        // Scoring - Move this to paddle logic
        if (ball.pos.x <= 0) {
            paddle_p2.score = paddle_p2.score + 1;
            paddle_p2.scoreText.Destroy();
            paddle_p2.scoreText = Text(font, std::to_string(paddle_p2.score).c_str(), SCREEN_WIDTH / 2 + 20, 10, gRenderer);
            substate = SERVE;
        }

        if (ball.pos.x >= SCREEN_WIDTH - ball.width) {
            paddle_p1.score = paddle_p1.score + 1;
            paddle_p1.scoreText.Destroy();
            paddle_p1.scoreText = Text(font, std::to_string(paddle_p1.score).c_str(), SCREEN_WIDTH / 2 - 30, 10, gRenderer);
            substate = SERVE;
        }

        // TODO: Move this.
        if (paddle_p1.score == 10 || paddle_p2.score == 10) 
        {
            {
                setNextState( GameOverState::get() );
            }
        }
    }
}

void PlayState::render()
{
    SDL_RenderDrawLine(gRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    ball.Render();
    paddle_p1.Render();
    paddle_p2.Render();
}

