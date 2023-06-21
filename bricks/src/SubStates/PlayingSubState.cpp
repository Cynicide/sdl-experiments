#include <PlayingSubState.h>
#include <Sign.h>
#include <Vector2d.h>
#include <sstream>
#include "spdlog/spdlog.h"

//BUG: Laser doesn't despawn when hitting invulnerable block sometimes.
PlayingSubState::PlayingSubState(GameContext* gameContext, SubState*& sNextState) :
    gameContext(gameContext),
    sNextState(sNextState),
    normalGameMode(gameContext),
    longGameMode(gameContext, sNextMode),
    slowGameMode(gameContext, sNextMode),
    laserMode(gameContext, sNextMode),
    magneticMode(gameContext, sNextMode)
    {}

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
    gameContext->ballList.clear();
    gameContext->bulletList.clear();
    gameContext->powerupList.clear();
    gameContext->levelManager.destroyLevelWarp();
    gameContext->paddle.setNormalPaddle();
    return true;

}

//Main loop functions
void PlayingSubState::handleEvent( SDL_Event& e ) {

}
void PlayingSubState::update(double dt) {
    auto logger = spdlog::get("fileLogger");

    // =================================================
    // ===================   Update  ===================
    // =================================================

    // Update the paddle position
    gameContext->paddle.updatePlaying(dt);

    // Update each ball
    gameContext->ballList.update(dt, gameContext->paddle.paddleRect);

    // Update each powerup
    gameContext->powerupList.update(dt);

    // Update each Bullet.
    gameContext->bulletList.update(dt);

    // Update Each Brick, Turret and Level Warp
    gameContext->levelManager.update(dt, gameContext->paddle.paddleRect);

    // Is the Level Over? 
    bool nextLevel = gameContext->levelManager.isLevelComplete();

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
    if (gameContext->levelManager.warpIsActive()) {
        if (physics.AABBCheck(gameContext->paddle.paddleRect, gameContext->levelManager.getWarpCollisionRect())) {
            sNextState = levelWinSubState;
        }
    }

    // Collision Powerup
    // Check for Collision with the paddle
    for (int p = 0; p < gameContext->powerupList.MAXPOWERUPS; ++p) {
        if (gameContext->powerupList.get(p) != nullptr) {
            if (physics.AABBCheck(gameContext->paddle.paddleRect, gameContext->powerupList.get(p)->powerupRect)) {
                // Fire Powerup Effect
                switch(gameContext->powerupList.get(p)->powerupType) {
                    case Definitions::PowerUpType::ExtraLife: {
                        gameContext->addLife();
                        break;
                    }
                    case Definitions::PowerUpType::SlowBall: {
                        sNextMode = &slowGameMode;
                        break;
                    }
                    case Definitions::PowerUpType::TripleBall: {
                        // This loops through and find an active ball to spawn the rest from
                        for (int b = 0; b < gameContext->ballList.MAXBALLS; ++b) {
                            if (gameContext->ballList.get(b) != nullptr) {
                                gameContext->ballList.fillAtLocation(gameContext->ballList.get(b)->ballRect.x, gameContext->ballList.get(b)->ballRect.y, gameContext->ballList.get(b)->getCurrentVel());
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
                        gameContext->levelManager.createLevelWarp();
                        break;
                    }
                    case Definitions::PowerUpType::Magnetic: {
                        sNextMode = &magneticMode;
                    break;
                    }
                };
                gameContext->powerupList.remove(p);
            }
        }
    }

    // Collision for Lasers
    // Top Border
    for (int r = 0; r < gameContext->bulletList.MAXBULLETS; ++r) {        
        if (gameContext->bulletList.get(r) != nullptr) {
            if(gameContext->bulletList.get(r)->bulletStatus == Definitions::BulletStatus::BulletGood) {
                
                auto& bulletRect = gameContext->bulletList.get(r)->bulletRect;

                // If the bullet has left the top of the screen something has gone wrong, delete it.
                if(bulletRect.y < 0) {
                    gameContext->bulletList.remove(r);
                }

                // Did we hit the top wall?
                if (physics.AABBCheck(bulletRect, gameContext->borderT.borderRect)) {
                    gameContext->bulletList.get(r)->hit();
                    //if we've hit the wall we don't need to check any bricks
                    continue;
                }

                // ToDo: Change to Swept aabb
                // Check each brick                
                for (auto brick : gameContext->levelManager.brickList) {
                    if (brick->isGood()) {
                        // Check if we are inside the brick. 
                        if (physics.AABBCheck(bulletRect, brick->brickRect)) {
                            gameContext->bulletList.get(r)->hit();
                            brick->hit();
                            // Move onto the next bullet as we don't need to check any more bricks
                            break;
                        }
                    }    
                }

                // ToDo: Change to Swept aabb
                // Check each turret                
                for (auto turret : gameContext->levelManager.turretList) {
                    if (turret->isGood()) {
                        // Check if we are inside the turret. 
                        if (physics.AABBCheck(bulletRect, turret->turretRect)) {
                            gameContext->bulletList.get(r)->hit();
                            turret->hitTurret();
                            // Move onto the next turret as we don't need to check any more bricks
                            break;
                        }
                    }    
                }
            }
        }
    }

    // Collision for the Turret Bullets

    for (auto turret : gameContext->levelManager.turretList) {
        if (turret->turretBullet != nullptr) {
            if (physics.AABBCheck(turret->turretBullet->turretBulletRect, gameContext->paddle.paddleRect)) {
                sNextState = dyingSubState;
            }
        }
    }

    // Collision for the Ball(s)

    // Check the Ball List for balls. If there are none this will remain true and kill the player
    bool killPlayer = true;

    for (int b = 0; b < gameContext->ballList.MAXBALLS; ++b) {
        if (gameContext->ballList.get(b) != nullptr) {

            killPlayer = false;

            // Create some references for readability as we will use these objects often
            auto& ballRect = gameContext->ballList.get(b)->ballRect;
            auto& paddleRect = gameContext->paddle.paddleRect;
            auto& ballVel = gameContext->ballList.get(b)->vel;

            bpb = physics.GetSweptBroadphaseBox(ballRect, ballVel.x * dt, ballVel.y * dt);    

            // Collision Bottom Border
            if (physics.AABBCheck(ballRect, gameContext->lightning.bBorder)) {
                gameContext->ballList.remove(b);
                break;
            }

            // Collision - Top Border
            if (physics.AABBCheck(ballRect, gameContext->borderT.borderRect)) {
                gameContext->ballList.get(b)->hitTopWall(gameContext->borderT.borderRect);
            }

            // Collision - Side Borders
            if (physics.AABBCheck(ballRect, gameContext->borderL.borderRect)) {
                gameContext->ballList.get(b)->hitLeftWall(gameContext->borderL.borderRect);
            }
            
            if (physics.AABBCheck(ballRect, gameContext->borderR.borderRect)) {
                gameContext->ballList.get(b)->hitRightWall(gameContext->borderR.borderRect);
            }

            // Collision - Paddle

            // Only check for collision if the ball is on the lower half of the screen
            if (ballRect.y > SCREEN_HEIGHT / 2) {
                // Check to see if we are already inside the paddle. As the paddle and the ball can move, we may need to move the ball above the paddle 
                if (physics.AABBCheck(ballRect, paddleRect)) {             
                    
                    gameContext->ballList.get(b)->moveAbovePaddle(paddleRect);
                } 
                // If we are not inside the paddle then perform a broad phase collision check
                if (physics.AABBCheck(bpb, paddleRect)) 	
                    {                             
                    Vector2d collision;
                    // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
                    physics.SweptAABB(ballRect, paddleRect, ballVel, collision.x, collision.y);

                    if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                        // Trigger stickiness if we are in magnetic mode
                        if (sCurrentMode == &magneticMode) {
                            gameContext->paddle.hit();
                            gameContext->ballList.get(b)->hitPaddle(collision, paddleRect);
                            gameContext->ballList.get(b)->stuckToPaddle = true;
                            
                            // Move the ball of it's off the edge of the paddle, to stop it colliding with the wall if the players moves to either end of the playfield.
                            if (ballRect.x < paddleRect.x) {
                                ballRect.x = paddleRect.x + 5;
                            }

                            if ((ballRect.x + ballRect.w) > (paddleRect.x + paddleRect.w)) {
                                ballRect.x = (paddleRect.x + paddleRect.w) - ballRect.w - 5;
                            }

                            // Store the offset for when we move the paddle
                            gameContext->ballList.get(b)->stuckOffset = ballRect.x - paddleRect.x;

                        } else {
                            gameContext->paddle.hit();
                            gameContext->ballList.get(b)->hitPaddle(collision, paddleRect);
                        }
                    }
                }
            }

            // Collision - Bricks and Turrets
            float firstCollisionTime = std::numeric_limits<float>::max();
            float firstTurretCollisionTime = std::numeric_limits<float>::max();

            Vector2d firstCollision;
            
            std::shared_ptr<Brick> firstHitBrick;
            std::shared_ptr<Turret> firstHitTurret;

            for (auto turret : gameContext->levelManager.turretList) {
                if (turret->isGood()) {
                    if (physics.AABBCheck(ballRect, turret->collisionRect)) {
                        // If we are already inside the turret something went wrong with the last update. Attempt to revert it.
                        gameContext->ballList.get(b)->revertUpdate(dt);                       
                    }

                    if (physics.AABBCheck(bpb, turret->collisionRect)) {

                        Vector2d collision;
                        double collisiontime;

                        // Perform a Swept AABB check against the ball and the brick and get the collision time                
                        collisiontime = physics.SweptAABB(ballRect, turret->collisionRect, ballVel, collision.x, collision.y);

                        if (collisiontime < firstTurretCollisionTime && (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f)) {
                            firstTurretCollisionTime = collisiontime;
                            firstCollision = collision;
                            firstHitTurret = turret;
                        }
                    }
                }
            }

            // Check each brick for collision
            for (auto brick : gameContext->levelManager.brickList)  {
                // Make sure the brick is not already destroyed
                if (brick->isGood()) {
                    // Then if we are already inside a brick we need to move out as Swept AABB will not work.
                    if (physics.AABBCheck(ballRect, brick->brickRect)) {
                        gameContext->ballList.get(b)->revertUpdate(dt);
                    }

                    // Then do a check against the Broad Phase Bounding Box
                    if (physics.AABBCheck(bpb, brick->brickRect)){                            

                        Vector2d collision;
                        double collisiontime;
                        
                        // Perform a Swept AABB check against the ball and the brick and get the collision time                
                        collisiontime = physics.SweptAABB(ballRect, brick->brickRect, ballVel, collision.x, collision.y);


                        // If the collision time is shorter than the last collision time we reported point to it                       
                        if (collisiontime < firstCollisionTime && (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f)) {
                            firstCollisionTime = collisiontime;
                            firstCollision = collision;
                            firstHitBrick = brick;
                        }
                    }
                }
            }

            if (firstHitTurret != nullptr) {
                firstHitTurret->hitTurret();
            }

            if (firstHitBrick != nullptr) {
                // Some bricks might be Tough or Invulnerable. These should not spawn powerups when hit
                // so make sure the brick has progressed to Exploding before doing so
                if (firstHitBrick->hit() == Definitions::BrickStatus::BrickExploding) {
                    gameContext->powerupList.add(firstHitBrick->brickRect.x, firstHitBrick->brickRect.y, firstHitBrick->brickRect.w);
                }
            }

            if (firstHitBrick != nullptr || firstHitTurret != nullptr) {
               gameContext->ballList.get(b)->hitBrick(firstCollision); 
            }
        }
    }

    // If the previous for loop didn't change killPlayer
    if (killPlayer == true) {
        sNextState = dyingSubState;
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
        gameContext->ballList.render();

        gameContext->powerupList.render();
        gameContext->bulletList.render();
}