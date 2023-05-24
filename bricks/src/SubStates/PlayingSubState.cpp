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

        for (int b = 0; b < 3; ++b) {
            if (gameContext->ballList[b] != nullptr) {
                gameContext->ballList[b]->update(dt);
            }
        }

        // Update each powerup position if they are not null
        for (int p = 0; p < 5; ++p) {
            if (gameContext->powerupList[p] != nullptr) {
                gameContext->powerupList[p]->update(dt);
                // If they have fallen off the bottom of the screen delete them.
                if (gameContext->powerupList[p]->powerupRect.y > SCREEN_HEIGHT) {
                   delete(gameContext->powerupList[p]);
                   gameContext->powerupList[p] = nullptr; 
                }
            }
        }

    gameContext->levelManager.update(dt);

    // Is the Level Over?
    bool nextLevel = true;
    for (auto &i : gameContext->levelManager.brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed && i.brickType != Definitions::BrickType::Indestructable) {
            nextLevel = false;
            break;
        }
    }

    if (nextLevel == true) {
        sNextState = levelWinSubState;
    }
    

    // =================================================
    // =================== Collision ===================
    // =================================================

    // Collision Powerup

    // Check for Collision with the paddle
    for (int p = 0; p < 5; ++p) {
        if (gameContext->powerupList[p] != nullptr) {
            if (physics.AABBCheck(gameContext->paddle.paddleRect, gameContext->powerupList[p]->powerupRect)) {
                // If we collide spawn 3 balls (Temp)
                for (int b = 0; b < 3; ++b) {
                    if (gameContext->ballList[b] != nullptr) {
                        gameContext->AddBallAtLocation(gameContext->ballList[b]->ballRect.x, gameContext->ballList[b]->ballRect.y);
                        break;
                    }
                }
                // Delete the powerup and cleanup.
                delete(gameContext->powerupList[p]);
                gameContext->powerupList[p] = nullptr;
            }
        }
    }

    // Collision for the Ball(s)

    // Collision - Bottom Border
    // AABB Check Ball Rect versus Lightning Rect

    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->lightning.bBorder)) {
                delete(gameContext->ballList[b]);
                gameContext->ballList[b] = nullptr;
            }
        }
    }

    // Kill the player if there are no more balls.
    bool killPlayer = true;
    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
                killPlayer = false;
        }
    }

    if (killPlayer == true) {
        sNextState = dyingSubState;
    }

    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
            // Update the Broad Phase Box for the Ball
            bpb = physics.GetSweptBroadphaseBox(gameContext->ballList[b]->ballRect, gameContext->ballList[b]->vel.x * dt, gameContext->ballList[b]->vel.y * dt);    

            // Collision - Top Border
            // AABB Check Ball Rect versus Border Rect
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderT.borderRect)) 
            {
                spdlog::debug("########### Horizontal Wall to Paddle Collision ###########");
                gameContext->ballList[b]->hitTopWall(gameContext->borderT.borderRect);
            }

            // Collision - Side Borders
            // AABB Check Ball Rect versus Side Border Rects
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderL.borderRect))  
            {
                spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
                gameContext->ballList[b]->hitLeftWall(gameContext->borderL.borderRect);
            }
            
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderR.borderRect))  
            {
                spdlog::debug("########### Vertical Wall to Paddle Collision ###########");
                gameContext->ballList[b]->hitRightWall(gameContext->borderR.borderRect);
            }

            // Collision - Paddle
            
            // If the ball is on the bottom half of the screen check for collision
            if (gameContext->ballList[b]->ballRect.y > SCREEN_HEIGHT / 2) 
            {
                // If we are already inside the paddle then the paddle may have moved into the ball as the player can move
                // it as fast as they can move the mouse
                if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->paddle.paddleRect)) {
                    bool colliding = true;
                    
                    // This is a disgusting hack that moves the ball above the paddle and sets the Y velocity
                    // I have discovered I do not like programming physics or collision detection.
                    gameContext->ballList[b]->ballRect.y = gameContext->paddle.paddleRect.y - gameContext->ballList[b]->ballRect.h ;
                    if (sgn(gameContext->ballList[b]->vel.y) == 1) {
                        gameContext->ballList[b]->vel.y = gameContext->ballList[b]->vel.y * -1;
                    }

                    while (colliding) {
                        // If we find ourselves still colliding with the paddle we're going to update the balls location until we're not
                        gameContext->ballList[b]->update(dt);
                        if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->paddle.paddleRect) == false) {
                            colliding = false;
                        }
                    }
                } 
                // If we are not inside the paddle then perform a broad phase collision check
                if (physics.AABBCheck(bpb, gameContext->paddle.paddleRect)) 	
                    {                             
                    Vector2d collision;
                    //double collisiontime; 

                    // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
                    physics.SweptAABB(gameContext->ballList[b]->ballRect, gameContext->paddle.paddleRect, gameContext->ballList[b]->vel, collision.x, collision.y);

                    if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                        gameContext->paddle.hit();
                        gameContext->ballList[b]->hitPaddle(collision, gameContext->paddle.paddleRect);
                    }
                }
            }


            // Collision - Bricks
            float firstCollisionTime = std::numeric_limits<float>::max();
            std::vector<Brick> collisionList = {};
            Vector2d firstCollision;
            Brick *firstHitBrick = nullptr;
            
            // Check each brick for collision
            for (auto &i : gameContext->levelManager.brickList) 
            {
                // First Make sure the brick is not destroyed
                if (i.brickStatus == Definitions::BrickStatus::Good) {
                    // Then if we are already inside a brick we need to move out as swept aabb will not work.
                    if (physics.AABBCheck(gameContext->ballList[b]->ballRect, i.brickRect)) {
                        gameContext->ballList[b]->ballRect.x = gameContext->ballList[b]->ballRect.x - (gameContext->ballList[b]->vel.x * dt);
                        gameContext->ballList[b]->ballRect.y = gameContext->ballList[b]->ballRect.y - (gameContext->ballList[b]->vel.y * dt); 
                    }

                    // Then do a check against the Broad Phase Bounding Box
                    if (physics.AABBCheck(bpb, i.brickRect)){                             

                    Vector2d collision;
                    double collisiontime;

                    // Add this to a collection so we can report on multiple collisions per check
                    collisionList.push_back(i);
                    
                    // Perform a Swept AABB check against the ball and the brick and get the collision time                
                    collisiontime = physics.SweptAABB(gameContext->ballList[b]->ballRect, i.brickRect, gameContext->ballList[b]->vel, collision.x, collision.y);

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
                
                // Temp Variable to hold the status 
                Definitions::BrickStatus brickStatus = Definitions::BrickStatus::Good;

                brickStatus = firstHitBrick->hit();
                gameContext->ballList[b]->hitBrick(firstCollision);

                if (brickStatus == Definitions::BrickStatus::Exploding) {
                    // try and spawn a powerup
                    gameContext->AddPowerUp(firstHitBrick->brickRect.x, firstHitBrick->brickRect.y, firstHitBrick->brickRect.w);
                }
            }

            if (collisionList.size() > 1) {
                spdlog::info("@@@@@@@@@@@@@@@@@@@@@@ COLLISION POSSIBLE FOR MORE THAN ONE BLOCK (" + std::to_string(collisionList.size()) + ")");
            }
        }
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
        gameContext->lifeCounter.render(gameContext->lives);
        gameContext->paddle.renderPlaying();
        gameContext->levelManager.render();
        for (int b = 0; b < 3; ++b) {
            if (gameContext->ballList[b] != nullptr) {
                gameContext->ballList[b]->render();
            }
        }

        for (int p = 0; p < 5; ++p) {
            if (gameContext->powerupList[p] != nullptr) {
                gameContext->powerupList[p]->render();
            }
        }
}