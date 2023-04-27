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
    spdlog::info("Entered PlayState");
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

    ballCoord = Text(font, "BX: " + std::to_string(ball.ballRect.x) +
                           " BY: " + std::to_string(ball.ballRect.y) +
                           " BW: " + std::to_string(ball.ballRect.w) +
                           " BH: " + std::to_string(ball.ballRect.h), 10, 10, gRenderer);

    bpbCoord = Text(font, "BPX: 0 BPY: 0 BPW: 0 BPH: 0", 10, 50, gRenderer);

    ballVel = Text(font, "VX: " + std::to_string(ball.vel.x) +
                        " VY: " + std::to_string(ball.vel.y), 10, 90, gRenderer);
    subState = SERVING;

    return success;
}

bool PlayState::exit()
{
    spdlog::info("Exited PlayState\n");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{

}

void PlayState::update(double dt)
{
    switch(subState) 
    {
    case SERVING: 
    {
        ball.reset();
        paddle.update(dt);
        ball.update(dt, paddle.paddleRect);
        int mx, my;
        Uint32 mouseState = SDL_GetMouseState(&mx, &my);
        if (mouseState == SDL_BUTTON(1)) 
        {
            //ball.randomizeXDirection();
            subState = PLAYING;
        }
        break;
    }
    case PLAYING:
    {

        // Update Everything
        paddle.update(dt);
        ball.update(dt); 
        bpb = physics.GetSweptBroadphaseBox(ball.ballRect, ball.vel.x, ball.vel.y);    
        
        ballCoord = Text(font, "BX: " + std::to_string(ball.ballRect.x) +
                            " BY: " + std::to_string(ball.ballRect.y) +
                            " BW: " + std::to_string(ball.ballRect.w) +
                            " BH: " + std::to_string(ball.ballRect.h), 10, 10, gRenderer);

        bpbCoord = Text(font, "BPX: " + std::to_string(bpb.x) +
                            " BPY: " + std::to_string(bpb.y) +
                            " BPW: " + std::to_string(bpb.w) +
                            " BPH: " + std::to_string(bpb.h), 10, 50, gRenderer);

        ballVel = Text(font, "VX: " + std::to_string(ball.vel.x) +
                            " VY: " + std::to_string(ball.vel.y), 10, 90, gRenderer);


        // Check for Collision

        if (physics.AABBCheck(ball.ballRect, lightning.bBorder)) 
        {
            subState = SERVING;
            break;
        }

        if (physics.AABBCheck(ball.ballRect, border.tBorder)) 
        {
            spdlog::info("########### Vertical Wall to Paddle Collision ###########");
            ball.flipY();
        }

        if (physics.AABBCheck(ball.ballRect, border.rBorder) || physics.AABBCheck(ball.ballRect, border.lBorder))  
        {
            spdlog::info("########### Horizontal Wall to Paddle Collision ###########");
            ball.flipX();
        }

        if (sgn(ball.vel.y) == 1) 
        {
            if (physics.AABBCheck(bpb, paddle.paddleRect)) 	
            {                             
            spdlog::info("########### BPB to Paddle Collision ###########");
            spdlog::info("BPB: " + std::to_string(bpb.x) + " : " + std::to_string(bpb.y) + " : " + std::to_string(bpb.w) + " : " + std::to_string(bpb.h));
            spdlog::info("Brick: " + std::to_string(paddle.paddleRect.x) + " : " + std::to_string(paddle.paddleRect.y) + " : " + std::to_string(paddle.paddleRect.w) + " : " + std::to_string(paddle.paddleRect.h));  
            physics.ProcessCollision(ball.ballRect, paddle.paddleRect, ball.vel, dt);
            }
        }

        for (auto &i : brickManager.brickList) 
        {
            if (physics.AABBCheck(bpb, i.brickRect))
            {                             
            spdlog::info("########### BPB to Brick Collision ###########");
            spdlog::info("BPB: " + std::to_string(bpb.x) + " : " + std::to_string(bpb.y) + " : " + std::to_string(bpb.w) + " : " + std::to_string(bpb.h));
            spdlog::info("Brick: " + std::to_string(i.brickRect.x) + " : " + std::to_string(i.brickRect.y) + " : " + std::to_string(i.brickRect.w) + " : " + std::to_string(i.brickRect.h));                      
            physics.ProcessCollision(ball.ballRect, i.brickRect, ball.vel, dt);
            gPause = true;
            break;
            }
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
    RenderLoop += 1;
    background.render();
    lightning.render();
    border.render();
    paddle.render();
    brickManager.render();

    ballCoord.Render();
    bpbCoord.Render();
    ballVel.Render();

    ball.render();
    SDL_SetRenderDrawColor(gRenderer, 0,255,255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRectF(gRenderer, &bpb);


}