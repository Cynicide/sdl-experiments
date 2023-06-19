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

    gameContext->ballList.clear();
    gameContext->bulletList.clear();
    gameContext->powerupList.clear();
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

    // Update Each Brick
    gameContext->levelManager.update(dt, gameContext->paddle.paddleRect);
    
    // If the warp powerup is active update it
    if (levelWarp != nullptr) {
        levelWarp->update(dt);
    }

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
    if (levelWarp != nullptr) {
        if (physics.AABBCheck(gameContext->paddle.paddleRect, levelWarp->warpPortalCollisionRect)) {
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
                        levelWarp = new LevelWarp(&gameContext->spriteManager);
                        break;
                    }
                    case Definitions::PowerUpType::Magnetic: {
                        sNextMode = &magneticMode;
                    break;
                    }
                };

                // Delete the powerup and cleanup.
                //delete(gameContext->powerupList[p]);
                //gameContext->powerupList[p] = nullptr;
                gameContext->powerupList.remove(p);
            }
        }
    }

    // Collision for Lasers
    // Top Border
    for (int r = 0; r < gameContext->bulletList.MAXBULLETS; ++r) {        
        if (gameContext->bulletList.get(r) != nullptr) {
            if(gameContext->bulletList.get(r)->bulletStatus == Definitions::BulletStatus::BulletGood) {

                // If the bullet has left the top of the screen something has gone wrong, delete it.
                if(gameContext->bulletList.get(r)->bulletRect.y < 0) {
                    gameContext->bulletList.remove(r);
                }

                // Did we hit the top wall?
                if (physics.AABBCheck(gameContext->bulletList.get(r)->bulletRect, gameContext->borderT.borderRect)) {
                    gameContext->bulletList.get(r)->hit();
                    //if we've hit the wall we don't need to check any bricks
                    continue;
                }

                // Check each brick                
                for (auto brick : gameContext->levelManager.brickList) {
                    if (brick->isGood()) {
                        // Check if we are inside the brick. 
                        if (physics.AABBCheck(gameContext->bulletList.get(r)->bulletRect, brick->brickRect)) {
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
                        if (physics.AABBCheck(gameContext->bulletList.get(r)->bulletRect, turret->turretRect)) {
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

    // TODO: Move slice SpriteSheet
    // Collision - Bottom Border
    for (int b = 0; b < gameContext->ballList.MAXBALLS; ++b) {
        if (gameContext->ballList.get(b) != nullptr) {
            if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, gameContext->lightning.bBorder)) {
                gameContext->ballList.remove(b);
            }
        }
    }

    // Kill the player if there are no more balls.
    // ToDo: Move this up to the previous loop. Why are there so many Ball Loops?
    bool killPlayer = true;
    for (int b = 0; b < gameContext->ballList.MAXBALLS; ++b) {
        if (gameContext->ballList.get(b) != nullptr) {
                killPlayer = false;
        }
    }

    if (killPlayer == true) {
        sNextState = dyingSubState;
    }

    for (int b = 0; b < gameContext->ballList.MAXBALLS; ++b) {
        if (gameContext->ballList.get(b) != nullptr) {

            bpb = physics.GetSweptBroadphaseBox(gameContext->ballList.get(b)->ballRect, gameContext->ballList.get(b)->vel.x * dt, gameContext->ballList.get(b)->vel.y * dt);    

            // Collision - Top Border
            if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, gameContext->borderT.borderRect)) 
            {
                gameContext->ballList.get(b)->hitTopWall(gameContext->borderT.borderRect);
            }

            // Collision - Side Borders
            if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, gameContext->borderL.borderRect))  
            {
                gameContext->ballList.get(b)->hitLeftWall(gameContext->borderL.borderRect);
            }
            
            if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, gameContext->borderR.borderRect))  
            {
                gameContext->ballList.get(b)->hitRightWall(gameContext->borderR.borderRect);
            }

            // Collision - Paddle
            // Only check for collision if the ball is on the lower half of the screen
            if (gameContext->ballList.get(b)->ballRect.y > SCREEN_HEIGHT / 2) 
            {
                // If we are already inside the paddle then the paddle may have moved into the ball as the player can move as fast as they can move the mouse
                if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, gameContext->paddle.paddleRect)) {             
                    // This is a disgusting hack that moves the ball above the paddle 
                    gameContext->ballList.get(b)->ballRect.y = gameContext->paddle.paddleRect.y - gameContext->ballList.get(b)->ballRect.h ;
                } 
                // If we are not inside the paddle then perform a broad phase collision check
                if (physics.AABBCheck(bpb, gameContext->paddle.paddleRect)) 	
                    {                             
                    Vector2d collision;
                    // If the broad phase check is true then make a swept aabb check and adjust the movement of the ball
                    physics.SweptAABB(gameContext->ballList.get(b)->ballRect, gameContext->paddle.paddleRect, gameContext->ballList.get(b)->vel, collision.x, collision.y);

                    if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                        // Trigger stickiness if we are in magnetic mode
                        if (sCurrentMode == &magneticMode) {
                            gameContext->paddle.hit();
                            gameContext->ballList.get(b)->hitPaddle(collision, gameContext->paddle.paddleRect);
                            gameContext->ballList.get(b)->stuckToPaddle = true;
                            
                            // Move the ball of it's off the edge of the paddle, to stop it colliding with the wall if the players moves to either end of the playfield.
                            if (gameContext->ballList.get(b)->ballRect.x < gameContext->paddle.paddleRect.x) {
                                gameContext->ballList.get(b)->ballRect.x = gameContext->paddle.paddleRect.x + 5;
                            }

                            if ((gameContext->ballList.get(b)->ballRect.x + gameContext->ballList.get(b)->ballRect.w) > (gameContext->paddle.paddleRect.x + gameContext->paddle.paddleRect.w)) {
                                gameContext->ballList.get(b)->ballRect.x = (gameContext->paddle.paddleRect.x + gameContext->paddle.paddleRect.w) - gameContext->ballList.get(b)->ballRect.w - 5;
                            }

                            // Store the offset for when we move the paddle
                            gameContext->ballList.get(b)->stuckOffset = gameContext->ballList.get(b)->ballRect.x - gameContext->paddle.paddleRect.x;

                        } else {
                            gameContext->paddle.hit();
                            gameContext->ballList.get(b)->hitPaddle(collision, gameContext->paddle.paddleRect);
                        }

                    }
                }
            }

            // Collision - Bricks and Turrets
            float firstCollisionTime = std::numeric_limits<float>::max();
            float firstTurretCollisionTime = std::numeric_limits<float>::max();

            std::vector<std::shared_ptr<Brick>> collisionList;

            Vector2d firstCollision;
            
            std::shared_ptr<Brick> firstHitBrick;
            std::shared_ptr<Turret> firstHitTurret;

            for (auto turret : gameContext->levelManager.turretList) {
                if (turret->isGood()) {
                    if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, turret->collisionRect)) {
                        gameContext->ballList.get(b)->ballRect.x = gameContext->ballList.get(b)->ballRect.x - (gameContext->ballList.get(b)->vel.x * dt);
                        gameContext->ballList.get(b)->ballRect.y = gameContext->ballList.get(b)->ballRect.y - (gameContext->ballList.get(b)->vel.y * dt);                         
                    }

                    if (physics.AABBCheck(bpb, turret->collisionRect)) {

                        Vector2d collision;
                        double collisiontime;

                        // Perform a Swept AABB check against the ball and the brick and get the collision time                
                        collisiontime = physics.SweptAABB(gameContext->ballList.get(b)->ballRect, turret->collisionRect, gameContext->ballList.get(b)->vel, collision.x, collision.y);

                        if (collisiontime < firstTurretCollisionTime && (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f)) {
                            firstTurretCollisionTime = collisiontime;
                            firstCollision = collision;
                            firstHitTurret = turret;
                        }
                    }
                }
            }

            // Check each brick for collision
            for (auto brick : gameContext->levelManager.brickList) 
            {
                // First Make sure the brick is not destroyed
                if (brick->isGood()) {
                    // Then if we are already inside a brick we need to move out as swept aabb will not work.
                    if (physics.AABBCheck(gameContext->ballList.get(b)->ballRect, brick->brickRect)) {
                        gameContext->ballList.get(b)->ballRect.x = gameContext->ballList.get(b)->ballRect.x - (gameContext->ballList.get(b)->vel.x * dt);
                        gameContext->ballList.get(b)->ballRect.y = gameContext->ballList.get(b)->ballRect.y - (gameContext->ballList.get(b)->vel.y * dt); 
                    }

                    // Then do a check against the Broad Phase Bounding Box
                    if (physics.AABBCheck(bpb, brick->brickRect)){                            

                        Vector2d collision;
                        double collisiontime;

                        // Add this to a collection so we can report on multiple collisions per check
                        collisionList.push_back(brick);
                        
                        // Perform a Swept AABB check against the ball and the brick and get the collision time                
                        collisiontime = physics.SweptAABB(gameContext->ballList.get(b)->ballRect, brick->brickRect, gameContext->ballList.get(b)->vel, collision.x, collision.y);

                        // Do we even still need this?
                        // Ensure there are no other bricks blocking the collision
                        if (abs(collision.x) > 0.0001f || abs(collision.y) > 0.0001f) {
                            std::stringstream ssBrAddr;
                            ssBrAddr << static_cast<void*>(&brick);
                            
                            std::string brAddr;
                            brAddr = ssBrAddr.str();
                            logger->info("Brick: " + brAddr + " -- CollisionTime: " + std::to_string(collisiontime));
                        }
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
                
                // ToDo: Look at replacing this with a pointer to the brick
                // Temp Variable to hold the status 
                Definitions::BrickStatus brickStatus = Definitions::BrickStatus::BrickGood;

                brickStatus = firstHitBrick->hit();
                //gameContext->ballList[b]->hitBrick(firstCollision);

                if (brickStatus == Definitions::BrickStatus::BrickExploding) {
                    // try and spawn a powerup
                    gameContext->powerupList.add(firstHitBrick->brickRect.x, firstHitBrick->brickRect.y, firstHitBrick->brickRect.w);
                }
            }

            if (firstHitBrick != nullptr || firstHitTurret != nullptr) {
               gameContext->ballList.get(b)->hitBrick(firstCollision); 
            }

            if (collisionList.size() > 1) {
                logger->info("@@@@@@@@@@@@@@@@@@@@@@ COLLISION POSSIBLE FOR MORE THAN ONE BLOCK (" + std::to_string(collisionList.size()) + ")");
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
        gameContext->ballList.render();

        gameContext->powerupList.render();
        gameContext->bulletList.render();

        if (levelWarp != nullptr) {
            levelWarp->render();
        }

}