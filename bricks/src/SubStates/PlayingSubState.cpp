#include <PlayingSubState.h>
#include <Sign.h>
#include <Vector2d.h>
#include <sstream>

//BUG: Laser doesn't despawn when hitting invulnerable block sometimes.

PlayingSubState::PlayingSubState(GameContext* gameContext, SubState*& sNextState) :
    gameContext(gameContext),
    sNextState(sNextState),
    normalGameMode(gameContext),
    longGameMode(gameContext, sNextMode),
    slowGameMode(gameContext, sNextMode),
    laserMode(gameContext, sNextMode),
    magneticMode(gameContext, sNextMode)
    {

    }

void PlayingSubState::setDyingSubState(SubState* dyingSubState) {
    this->dyingSubState = dyingSubState;
}

void PlayingSubState::setLevelWinSubState(SubState* levelWinSubState) {
    this->levelWinSubState = levelWinSubState;
}

bool PlayingSubState::enter() {
    longGameMode.setNormalMode(&normalGameMode);
    slowGameMode.setNormalMode(&normalGameMode);
    laserMode.setNormalMode(&normalGameMode);
    magneticMode.setNormalMode(&normalGameMode);

    sCurrentMode = &normalGameMode;
    normalGameMode.enter();
    return true;
}
bool PlayingSubState::exit() {
    if (levelWarp != nullptr) {
        delete levelWarp;
        levelWarp = nullptr;
    }

    gameContext->ClearBalls();
    gameContext->ClearBullets();
    gameContext->ClearPowerups();
    gameContext->paddle.setNormalPaddle();

    return true;

}

//Main loop functions
void PlayingSubState::handleEvent( SDL_Event& e ) {

}
void PlayingSubState::update(double dt) {
    // =================================================
    // ===================   Update  ===================
    // =================================================

    // Update the paddle position
    gameContext->paddle.updatePlaying(dt);

    // Update each ball. If they are stuck to the paddle treat them as if they are being served.
    for (int b = 0; b < 3; ++b) {
        if (gameContext->ballList[b] != nullptr) {
            if (gameContext->ballList[b]->stuckToPaddle == true) {
                gameContext->ballList[b]->updateStuck(dt, gameContext->paddle.paddleRect);
            } else {
                gameContext->ballList[b]->update(dt);
            }

        }
    }

    // Update each powerup
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

    // Update each Bullet.
    for (int p = 0; p < 2; ++p) {
        if (gameContext->bulletList[p] != nullptr) {
            //If they have a status of Dead delete them.
            if (gameContext->bulletList[p]->bulletStatus == Definitions::BulletStatus::BulletDead) {
                delete(gameContext->bulletList[p]);
                gameContext->bulletList[p] = nullptr;
            } else {
                gameContext->bulletList[p]->update(dt);
            }
        }
    }

    // Update Each Brick
    gameContext->levelManager.update(dt, gameContext->paddle.paddleRect);
    
    // If the warp powerup is active update it
    if (levelWarp != nullptr) {
        levelWarp->update(dt);
    }

    // Is the Level Over? Check each brick that can be destroyed to make sure it is.
    bool nextLevel = true;
    for (auto &i : gameContext->levelManager.brickList) {
        if (i.brickStatus != Definitions::BrickStatus::Destroyed && i.brickType != Definitions::BrickType::Indestructable) {
            // If any bricks remain do not advance to the next level.
            nextLevel = false;
            break;
        }
    }

    // Run the game mode update logic
    sCurrentMode->update(dt);

    // Advance to the next level if the conditions are met.
    if (nextLevel == true) {
        sNextState = levelWinSubState;
    }
    
    // =================================================
    // =================== Collision ===================
    // =================================================

    // Collision Warp
    // If we collide with the warp object behave as if the level had been completed.
    if (levelWarp != nullptr) {
        if (physics.AABBCheck(gameContext->paddle.paddleRect, levelWarp->warpRect)) {
            sNextState = levelWinSubState;
        }
    }

    // Collision Powerup
    // Check for Collision with the paddle
    for (int p = 0; p < 5; ++p) {
        if (gameContext->powerupList[p] != nullptr) {
            if (physics.AABBCheck(gameContext->paddle.paddleRect, gameContext->powerupList[p]->powerupRect)) {
                // Fire Powerup Effect
                switch(gameContext->powerupList[p]->powerupType) {
                    case Definitions::PowerUpType::ExtraLife: {
                        gameContext->AddLife();
                        break;
                    }
                    case Definitions::PowerUpType::SlowBall: {
                        sNextMode = &slowGameMode;
                        break;
                    }
                    case Definitions::PowerUpType::TripleBall: {
                        for (int b = 0; b < 3; ++b) {
                            if (gameContext->ballList[b] != nullptr) {
                                gameContext->AddBallsAtLocation(gameContext->ballList[b]->ballRect.x, gameContext->ballList[b]->ballRect.y, gameContext->ballList[b]->getCurrentVel());
                                break;
                            }
                        }
                        break;
                    }
                    case Definitions::PowerUpType::Wide: {
                        sNextMode = &longGameMode;
                        break;
                    }
                    case Definitions::PowerUpType::Laser: {
                        sNextMode = &laserMode;
                        break;
                    }
                    case Definitions::PowerUpType::LevelSkip: {
                        levelWarp = new LevelWarp(&gameContext->spriteManager);
                        break;
                    }
                    case Definitions::PowerUpType::Magnetic: {
                        sNextMode = &magneticMode;
                    break;
                    }
                };

                // Delete the powerup and cleanup.
                delete(gameContext->powerupList[p]);
                gameContext->powerupList[p] = nullptr;
            }
        }
    }

    // Collision for Lasers
    // Top Border
    for (int r = 0; r < 2; ++r) {        
        if (gameContext->bulletList[r] != nullptr) {
            if(gameContext->bulletList[r]->bulletStatus == Definitions::BulletStatus::BulletGood) {

                // If the bullet has left the top of the screen something has gone wrong, delete it.
                if(gameContext->bulletList[r]->bulletRect.y < 0) {
                    delete(gameContext->bulletList[r]);
                    gameContext->bulletList[r] = nullptr;
                }

                // Did we hit the top wall?
                if (physics.AABBCheck(gameContext->bulletList[r]->bulletRect, gameContext->borderT.borderRect)) {
                    gameContext->bulletList[r]->hit();
                    //if we've hit the wall we don't need to check any bricks
                    continue;
                }

                // ToDo: Change to Swept aabb
                // Check each brick                
                for (auto &i : gameContext->levelManager.brickList) {
                    if (i.brickStatus == Definitions::BrickStatus::Good) {
                        // Check if we are inside the brick. 
                        if (physics.AABBCheck(gameContext->bulletList[r]->bulletRect, i.brickRect)) {
                            gameContext->bulletList[r]->hit();
                            i.hit();
                            // Move onto the next bullet as we don't need to check any more bricks
                            break;
                        }
                    }    
                }
            }
        }
    }


    // Collision for the Ball(s)

    // TODO: Add consts for maxballs, max powerups etc
    // TODO: Move slice SpriteSheet
    // Collision - Bottom Border
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

            bpb = physics.GetSweptBroadphaseBox(gameContext->ballList[b]->ballRect, gameContext->ballList[b]->vel.x * dt, gameContext->ballList[b]->vel.y * dt);    

            // Collision - Top Border
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderT.borderRect)) 
            {
                gameContext->ballList[b]->hitTopWall(gameContext->borderT.borderRect);
            }

            // Collision - Side Borders
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderL.borderRect))  
            {
                gameContext->ballList[b]->hitLeftWall(gameContext->borderL.borderRect);
            }
            
            if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->borderR.borderRect))  
            {
                gameContext->ballList[b]->hitRightWall(gameContext->borderR.borderRect);
            }

            // Collision - Paddle
            // Only check for collision if the ball is on the lower half of the screen
            if (gameContext->ballList[b]->ballRect.y > SCREEN_HEIGHT / 2) 
            {
                // If we are already inside the paddle then the paddle may have moved into the ball as the player can move as fast as they can move the mouse
                if (physics.AABBCheck(gameContext->ballList[b]->ballRect, gameContext->paddle.paddleRect)) {             
                    // This is a disgusting hack that moves the ball above the paddle 
                    gameContext->ballList[b]->ballRect.y = gameContext->paddle.paddleRect.y - gameContext->ballList[b]->ballRect.h ;
                } 
                // If we are not inside the paddle then perform a broad phase collision check
                if (physics.AABBCheck(bpb, gameContext->paddle.paddleRect)) 	
                    {                             
                    Vector2d collision;
                    // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
                    physics.SweptAABB(gameContext->ballList[b]->ballRect, gameContext->paddle.paddleRect, gameContext->ballList[b]->vel, collision.x, collision.y);

                    if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                        // Trigger stickiness if we are in magnetic mode
                        if (sCurrentMode == &magneticMode) {
                            gameContext->paddle.hit();
                            gameContext->ballList[b]->hitPaddle(collision, gameContext->paddle.paddleRect);
                            gameContext->ballList[b]->stuckToPaddle = true;
                            
                            // Move the ball of it's off the edge of the paddle, to stop it colliding with the walsl if the players moves to either end of the playfield.
                            if (gameContext->ballList[b]->ballRect.x < gameContext->paddle.paddleRect.x) {
                                gameContext->ballList[b]->ballRect.x = gameContext->paddle.paddleRect.x + 5;
                            }

                            if ((gameContext->ballList[b]->ballRect.x + gameContext->ballList[b]->ballRect.w) > (gameContext->paddle.paddleRect.x + gameContext->paddle.paddleRect.w)) {
                                gameContext->ballList[b]->ballRect.x = (gameContext->paddle.paddleRect.x + gameContext->paddle.paddleRect.w) - gameContext->ballList[b]->ballRect.w - 5;
                            }

                            // Store the offset for when we move the paddle
                            gameContext->ballList[b]->stuckOffset = gameContext->ballList[b]->ballRect.x - gameContext->paddle.paddleRect.x;

                        } else {
                            gameContext->paddle.hit();
                            gameContext->ballList[b]->hitPaddle(collision, gameContext->paddle.paddleRect);
                        }

                    }
                }
            }


            // Collision - Bricks
            float firstCollisionTime = std::numeric_limits<float>::max();
            std::vector<Brick> collisionList = {};
            Vector2d firstCollision;
            Brick* firstHitBrick = nullptr;
            
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

    // Change Game Mode if required

    if( sNextMode != nullptr )
    {
		sCurrentMode->exit();
		sNextMode->enter();

        //Change the current state ID
        sCurrentMode = sNextMode;
        sNextMode = nullptr;
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

        for (int r = 0; r < 2; ++r) {
            if (gameContext->bulletList[r] != nullptr) {
                gameContext->bulletList[r]->render();
            }
        }

        if (levelWarp != nullptr) {
            levelWarp->render();
        }

}