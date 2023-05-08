#include <PlayState.h>
#include <TextManager.h>

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
    background = TiledBackground(SpriteManager::get()->background); 

    borderL = BorderVertical(PLAYFIELD_STARTX, 0, borderWidthV, SCREEN_HEIGHT, false);
    borderR = BorderVertical(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthV, 0, borderWidthV, SCREEN_HEIGHT, true);
    borderT = BorderHorizontal(PLAYFIELD_STARTX, 0, PLAYFIELD_WIDTH, borderHeightH, false);
    borderTL = BorderCorner(PLAYFIELD_STARTX, 0, borderWidthC, borderHeightC, false);
    borderTR = BorderCorner(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthC, 0, borderWidthC, borderHeightC, true);    

    font = TextManager::get()->publicPixel12;

    lightning = Lightning();

    paddle = Paddle();
    ball = Ball();

    brickManager = BrickManager();

    brickManager.LoadLevel();
    brickManager.CreateLevel();

    ballCoord = Text(font, "BX: " + std::to_string(ball.ballRect.x) +
                           " BY: " + std::to_string(ball.ballRect.y) +
                           " BW: " + std::to_string(ball.ballRect.w) +
                           " BH: " + std::to_string(ball.ballRect.h), 30, 20, gRenderer);

    bpbCoord = Text(font, "BPX: 0 BPY: 0 BPW: 0 BPH: 0", 30, 60, gRenderer);

    ballVel = Text(font, "VX: " + std::to_string(ball.vel.x) +
                        " VY: " + std::to_string(ball.vel.y), 30, 100, gRenderer);
    subState = Definitions::SubState::SERVING;

    return success;
}

bool PlayState::exit()
{
    ballCoord.destroy();
    bpbCoord.destroy();
    ballVel.destroy();
    spdlog::info("Exited PlayState");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{
    switch(subState) {

        case Definitions::SubState::SERVING: {
            break;
        }
        case Definitions::SubState::PLAYING: {
            break;
        }
        case Definitions::SubState::DYING: {
            if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
            {
                paddle.reset();
                subState = Definitions::SubState::SERVING;
            }
            break;
        }
        case Definitions::SubState::GAMEOVER: {
            break;
        }
    }
}

void PlayState::update(double dt)
{
    switch(subState) 
    {
    case Definitions::SubState::SERVING: 
    {
        ball.reset();
        paddle.update(dt);
        ball.update(dt, paddle.paddleRect);
        int mx, my;
        Uint32 mouseState = SDL_GetMouseState(&mx, &my);
        if (mouseState == SDL_BUTTON(1)) 
        {
            ball.randomizeXDirection();
            subState = Definitions::SubState::PLAYING;
        }
        break;
    }
    case Definitions::SubState::PLAYING:
    {
        // =================================================
        // ===================   Update  ===================
        // =================================================

        paddle.update(dt);
        ball.update(dt); 

        // =================================================
        // =================== Collision ===================
        // =================================================

        // Update the Braod Phase Box for the Ball
        bpb = physics.GetSweptBroadphaseBox(ball.ballRect, ball.vel.x, ball.vel.y);    
        
        // DEBUG: Coordinates on Screen        
        ballCoord.destroy();
        ballCoord = Text(font, "BX: " + std::to_string(ball.ballRect.x) +
                            " BY: " + std::to_string(ball.ballRect.y) +
                            " BW: " + std::to_string(ball.ballRect.w) +
                            " BH: " + std::to_string(ball.ballRect.h), 30, 20, gRenderer);

        bpbCoord.destroy();
        bpbCoord = Text(font, "BPX: " + std::to_string(bpb.x) +
                            " BPY: " + std::to_string(bpb.y) +
                            " BPW: " + std::to_string(bpb.w) +
                            " BPH: " + std::to_string(bpb.h), 30, 60, gRenderer);

        ballVel.destroy();
        ballVel = Text(font, "VX: " + std::to_string(ball.vel.x) +
                            " VY: " + std::to_string(ball.vel.y), 30, 100, gRenderer);
        
        // Collision - Bottom Border
        // AABB Check Ball Rect versus Lightning Rect
        if (physics.AABBCheck(ball.ballRect, lightning.bBorder)) 
        {
            //ball.hitLightning();
            subState = Definitions::SubState::DYING;
        }


        // Collision - Top Border
        // AABB Check Ball Rect versus Border Rect
        if (physics.AABBCheck(ball.ballRect, borderT.borderRect)) 
        {
            spdlog::debug("########### Horizontal Wall to Paddle Collision ###########");
            ball.hitTopWall(borderT.borderRect);
        }

        // Collision - Side Borders
        // AABB Check Ball Rect versus Side Border Rects
        if (physics.AABBCheck(ball.ballRect, borderL.borderRect))  
        {
            spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
            ball.hitLeftWall(borderL.borderRect);
        }
        
        if (physics.AABBCheck(ball.ballRect, borderR.borderRect))  
        {
            spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
            ball.hitRightWall(borderR.borderRect);
        }

        // Collision - Paddle
        
        // If the ball is on the bottom half of the screen check for collision
        if (ball.ballRect.y > SCREEN_HEIGHT / 2) 
        {
            // If we are already inside the paddle then the paddle may have moved into the ball as the player can move
            // it as fast as they can move the mouse
            if (physics.AABBCheck(ball.ballRect, paddle.paddleRect)) {
                bool colliding = true;
                
                // This is a disgusting hack that moves the ball above the paddle and sets the Y velocity
                // I have discovered I do not like programming physics or collision detection.
                ball.ballRect.y = paddle.paddleRect.y - ball.ballRect.h ;
                if (sgn(ball.vel.y) == 1) {
                    ball.vel.y = ball.vel.y * -1;
                }

                while (colliding) {
                    // If we find ourselves still colliding with the paddle we're going to update the balls location until we're not
                    ball.update(dt);
                    if (physics.AABBCheck(ball.ballRect, paddle.paddleRect) == false) {
                        colliding = false;
                    }
                }
            } 
            // If we are not inside the paddle then perform a broad phase collision check
            if (physics.AABBCheck(bpb, paddle.paddleRect)) 	
                {                             
                Vector2d collision;
                float collisiontime; 

                spdlog::debug("########### BPB to Paddle Collision ###########");
                spdlog::debug("BPB: " + std::to_string(bpb.x) + " : " + std::to_string(bpb.y) + " : " + std::to_string(bpb.w) + " : " + std::to_string(bpb.h));
                spdlog::debug("Brick: " + std::to_string(paddle.paddleRect.x) + " : " + std::to_string(paddle.paddleRect.y) + " : " + std::to_string(paddle.paddleRect.w) + " : " + std::to_string(paddle.paddleRect.h));  

                // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
                collisiontime = physics.SweptAABB(ball.ballRect, paddle.paddleRect, ball.vel, collision.x, collision.y);

                if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                    paddle.hit();
                    ball.hitPaddle(collision, paddle.paddleRect);
                }
            }
        }


        // Collision - Bricks
        std::vector<Brick> collisionList = {};

        for (auto &i : brickManager.brickList) 
        {
            if (i.brickStatus == Definitions::BrickStatus::Good) {

                if (physics.AABBCheck(bpb, i.brickRect))
                {                             
                Vector2d collision;
                float collisiontime;

                collisionList.push_back(i);
                
                spdlog::debug("########### BPB to Brick Collision ###########");
                spdlog::debug("BPB: " + std::to_string(bpb.x) + " : " + std::to_string(bpb.y) + " : " + std::to_string(bpb.w) + " : " + std::to_string(bpb.h));
                spdlog::debug("Brick: " + std::to_string(i.brickRect.x) + " : " + std::to_string(i.brickRect.y) + " : " + std::to_string(i.brickRect.w) + " : " + std::to_string(i.brickRect.h));                      
                
                collisiontime = physics.SweptAABB(ball.ballRect, i.brickRect, ball.vel, collision.x, collision.y);
    
                if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                    i.hit();
                    ball.hitBrick(collision);
                    }
                }
            }
        }

        if (collisionList.size() > 1) {
            spdlog::info("@@@@@@@@@@@@@@@@@@@@@@ COLLISION POSSIBLE FOR MORE THAN ONE BLOCK (" + std::to_string(collisionList.size()) + ")");
        }

        break;
    }

    case Definitions::SubState::DYING:
    {
        break;
    }
    case Definitions::SubState::GAMEOVER:
    {
        break;
    }
    }
}

void PlayState::render()
{
    background.render();
    lightning.render();

    borderL.render();
    borderR.render();
    borderT.render();
    borderTL.render();
    borderTR.render();

    paddle.render(subState);
    brickManager.render();

    /*ballCoord.render();
    bpbCoord.render();
    ballVel.render();*/

    ball.render();
    //SDL_SetRenderDrawColor(gRenderer, 0,255,255, SDL_ALPHA_OPAQUE);
    //SDL_RenderDrawRectF(gRenderer, &bpb);


}