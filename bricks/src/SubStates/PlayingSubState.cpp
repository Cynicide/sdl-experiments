#include <PlayingSubState.h>
#include <Sign.h>
#include <Vector2d.h>
#include <sstream>

PlayingSubState::PlayingSubState(GameContext* gameContext, SubState*& sNextState) :
    gameContext(gameContext),
    sNextState(sNextState) {
}

void PlayingSubState::setDyingSubState(SubState* dyingSubState) {
    this->dyingSubState = dyingSubState;
}

void PlayingSubState::setLevelWinSubState(SubState* levelWinSubState) {
    this->levelWinSubState = levelWinSubState;
}

bool PlayingSubState::enter() {
    return true;

}
bool PlayingSubState::exit() {

    return true;

}

//Main loop functions
void PlayingSubState::handleEvent( SDL_Event& e ) {

}
void PlayingSubState::update(double dt) {
    // =================================================
    // ===================   Update  ===================
    // =================================================

    gameContext->paddle.updatePlaying(dt);
    gameContext->ball.update(dt);
    gameContext->brickManager.update(dt);

    // Is the Level Over?
    bool nextLevel = true;
    for (auto &i : gameContext->brickManager.brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed && i.brickType != Definitions::BrickType::Indestructable) {
            nextLevel = false;
            continue;
        }
    }

    if (nextLevel == true) {
        sNextState = levelWinSubState;
    }
    

    // =================================================
    // =================== Collision ===================
    // =================================================

    // Update the Braod Phase Box for the Ball
    bpb = physics.GetSweptBroadphaseBox(gameContext->ball.ballRect, gameContext->ball.vel.x * dt, gameContext->ball.vel.y * dt);    
    
    // Collision - Bottom Border
    // AABB Check Ball Rect versus Lightning Rect
    if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->lightning.bBorder)) 
    {
        gameContext->ball.hitLightning();
        sNextState = dyingSubState;
    }

    // Collision - Top Border
    // AABB Check Ball Rect versus Border Rect
    if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->borderT.borderRect)) 
    {
        spdlog::debug("########### Horizontal Wall to Paddle Collision ###########");
        gameContext->ball.hitTopWall(gameContext->borderT.borderRect);
    }

    // Collision - Side Borders
    // AABB Check Ball Rect versus Side Border Rects
    if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->borderL.borderRect))  
    {
        spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
        gameContext->ball.hitLeftWall(gameContext->borderL.borderRect);
    }
    
    if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->borderR.borderRect))  
    {
        spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
        gameContext->ball.hitRightWall(gameContext->borderR.borderRect);
    }

    // Collision - Paddle
    
    // If the ball is on the bottom half of the screen check for collision
    if (gameContext->ball.ballRect.y > SCREEN_HEIGHT / 2) 
    {
        // If we are already inside the paddle then the paddle may have moved into the ball as the player can move
        // it as fast as they can move the mouse
        if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->paddle.paddleRect)) {
            bool colliding = true;
            
            // This is a disgusting hack that moves the ball above the paddle and sets the Y velocity
            // I have discovered I do not like programming physics or collision detection.
            gameContext->ball.ballRect.y = gameContext->paddle.paddleRect.y - gameContext->ball.ballRect.h ;
            if (sgn(gameContext->ball.vel.y) == 1) {
                gameContext->ball.vel.y = gameContext->ball.vel.y * -1;
            }

            while (colliding) {
                // If we find ourselves still colliding with the paddle we're going to update the balls location until we're not
                gameContext->ball.update(dt);
                if (physics.AABBCheck(gameContext->ball.ballRect, gameContext->paddle.paddleRect) == false) {
                    colliding = false;
                }
            }
        } 
        // If we are not inside the paddle then perform a broad phase collision check
        if (physics.AABBCheck(bpb, gameContext->paddle.paddleRect)) 	
            {                             
            Vector2d collision;
            double collisiontime; 

            // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
            collisiontime = physics.SweptAABB(gameContext->ball.ballRect, gameContext->paddle.paddleRect, gameContext->ball.vel, collision.x, collision.y);

            if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                gameContext->paddle.hit();
                gameContext->ball.hitPaddle(collision, gameContext->paddle.paddleRect);
            }
        }
    }


    // Collision - Bricks
    float firstCollisionTime = std::numeric_limits<float>::max();
    std::vector<Brick> collisionList = {};
    Vector2d firstCollision;
    Brick *firstHitBrick = nullptr;
    
    // Check each brick for collision
    for (auto &i : gameContext->brickManager.brickList) 
    {
        // First Make sure the brick is not destroyed
        if (i.brickStatus == Definitions::BrickStatus::Good) {
            // Then if we are already inside a brick we need to move out as swept aabb will not work.
            if (physics.AABBCheck(gameContext->ball.ballRect, i.brickRect)) {
                gameContext->ball.ballRect.x = gameContext->ball.ballRect.x - (gameContext->ball.vel.x * dt);
                gameContext->ball.ballRect.y = gameContext->ball.ballRect.y - (gameContext->ball.vel.y * dt); 
            }

            // Then do a check against the Broad Phase Bounding Box
            if (physics.AABBCheck(bpb, i.brickRect)){                             

            Vector2d collision;
            double collisiontime;

            // Add this to a collection so we can report on multiple collisions per check
            collisionList.push_back(i);
            
            // Perform a Swept AABB check against the ball and the brick and get the collision time                
            collisiontime = physics.SweptAABB(gameContext->ball.ballRect, i.brickRect, gameContext->ball.vel, collision.x, collision.y);

            // Ensure there are no other bricks blocking the collision
            if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                std::stringstream ssBrAddr;
                ssBrAddr << static_cast<void*>(&i);
                
                std::string brAddr;
                brAddr = ssBrAddr.str();
                spdlog::info("Brick: " + brAddr + " -- CollisionTime: " + std::to_string(collisiontime));
            }


            // If the collision time is shorter than the last collision time we reported point to it
            
            if (collisiontime < firstCollisionTime && (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f)) {
                firstCollisionTime = collisiontime;
                firstCollision = collision;
                firstHitBrick = &i;
            }
            }
            // Lastly if we find ourselves inside a brick. Stop everything.
            //if (physics.AABBCheck(ball.ballRect, i.brickRect)) {
            //    subState = Definitions::SubState::BRICKDEBUG;
            //    spdlog::info("------------- Ball Inside Brick -------------");
            //    spdlog::info("Ball:  X1: " + std::to_string(ball.ballRect.x) + ", Y1: " + std::to_string(ball.ballRect.y) + ", X2: " + std::to_string(ball.ballRect.x + ball.ballRect.w) + " Y2: " + std::to_string(ball.ballRect.y + ball.ballRect.h));
            //    spdlog::info("Brick: X1: " + std::to_string(i.brickRect.x) + ", Y1: " + std::to_string(i.brickRect.y) + ", X2: " + std::to_string(i.brickRect.x + i.brickRect.w) + " Y2: " + std::to_string(i.brickRect.y + i.brickRect.h));
            //}
        }
    }

    if (firstHitBrick != nullptr) {
        firstHitBrick->hit();
        gameContext->ball.hitBrick(firstCollision);
    }

    if (collisionList.size() > 1) {
        spdlog::info("@@@@@@@@@@@@@@@@@@@@@@ COLLISION POSSIBLE FOR MORE THAN ONE BLOCK (" + std::to_string(collisionList.size()) + ")");
    }
}
void PlayingSubState::render() {
        gameContext->tiledBackground.render();
        gameContext->lightning.render();

        gameContext->borderL.render();
        gameContext->borderR.render();
        gameContext->borderT.render();
        gameContext->borderTL.render();
        gameContext->borderTR.render();
        gameContext->paddle.renderPlaying();
        gameContext->brickManager.render();
        gameContext->ball.render();

        //SDL_SetRenderDrawColor(gRenderer, 0,255,255, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawRectF(gRenderer, &bpb);
}