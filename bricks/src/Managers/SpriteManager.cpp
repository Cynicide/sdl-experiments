#include <SpriteManager.h>
#include "spdlog/spdlog.h"
#include <SDL2/SDL_image.h>

SpriteManager::SpriteManager() {
    auto logger = spdlog::get("fileLogger");
    logger->info("Creating Sprite Manager");
    loadSprites();
}

bool SpriteManager::getTextureDimensions(SDL_Texture * texture, int &width, int &height) {
    auto logger = spdlog::get("fileLogger");
        bool bQuery = SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        if (bQuery == 1) {
            logger->error("Error querying sprite.");
            logger->error( SDL_GetError());
            return false;
    } 
    return true;
}

SpriteManager::~SpriteManager() {
    auto logger = spdlog::get("fileLogger");
    logger->info("Destroying Textures");
    // ToDo: Properly de-allocate textures
    /*SDL_DestroyTexture(stars);
    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(paddle);
    SDL_DestroyTexture(ball);
    SDL_DestroyTexture(lightning);
    SDL_DestroyTexture(brickRed);
    SDL_DestroyTexture(brickBlue);
    SDL_DestroyTexture(brickYellow);
    SDL_DestroyTexture(brickTough);
    SDL_DestroyTexture(brickIndestructable);
    SDL_DestroyTexture(brickGreen);
    SDL_DestroyTexture(brickPurple);
    SDL_DestroyTexture(brickOrange);
    SDL_DestroyTexture(shipExplosion);
    SDL_DestroyTexture(techBorder);
    SDL_DestroyTexture(techCorner);
    SDL_DestroyTexture(techTopBorder);*/
}

SDL_Surface* SpriteManager::loadSurface( std::string path) {
    auto logger = spdlog::get("fileLogger");
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        logger->error( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    return loadedSurface;
}

SDL_Texture* SpriteManager::loadAlphaTexture(std::string path) {
    auto logger = spdlog::get("fileLogger");
    SDL_Surface* surface = loadSurface(path);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    bool bQuery = SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    if (bQuery == 1) {
        logger->info("Error setting Texture Blend Mode: ");
        logger->info(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return texture;
    
}

SDL_Texture* SpriteManager::loadTexture(std::string path) {
    SDL_Surface* surface = loadSurface(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void SpriteManager::loadSprites() {
    
    // Misc
    stars = loadAlphaTexture("assets\\images\\stars.png");
    logo = loadAlphaTexture("assets\\images\\logo.png");
    background = loadAlphaTexture("assets\\images\\background.png");
    letsGoTop = loadAlphaTexture("assets\\images\\lets-go-top.png");
    letsGoBottom = loadAlphaTexture("assets\\images\\lets-go-bottom.png");
    levelCompleteTop = loadAlphaTexture("assets\\images\\level-complete-top.png");
    levelCompleteBottom = loadAlphaTexture("assets\\images\\level-complete-bottom.png");
    gameOverTop = loadAlphaTexture("assets\\images\\game-over-top.png");
    gameOverBottom = loadAlphaTexture("assets\\images\\game-over-bottom.png");

    // Ship
    paddle = loadAlphaTexture("assets\\images\\paddle.png");
    shipExplosion = loadAlphaTexture("assets\\images\\explosion-sheet.png");
    laserPaddle = loadAlphaTexture("assets\\images\\paddle-lasermode.png");
    longPaddle = loadAlphaTexture("assets\\images\\paddle-long.png");
    turret = loadAlphaTexture("assets\\images\\turret-gun-sheet.png");
    turretBase = loadAlphaTexture("assets\\images\\turret-base.png");
    turretBullet = loadAlphaTexture("assets\\images\\turret-bullet-sheet.png");
    turretExplosion = loadAlphaTexture("assets\\images\\turret-explosion-sheet.png");

    // Ball
    ball = loadAlphaTexture("assets\\images\\ball.png");
    bullet = loadAlphaTexture("assets\\images\\laser-shot-sheet.png");

    //Bricks
    brickRed = loadAlphaTexture("assets\\images\\brick-red-sheet.png");
    brickBlue = loadAlphaTexture("assets\\images\\brick-blue-sheet.png");
    brickYellow = loadAlphaTexture("assets\\images\\brick-yellow-sheet.png");
    brickGreen = loadAlphaTexture("assets\\images\\brick-green-sheet.png");
    brickPurple = loadAlphaTexture("assets\\images\\brick-purple-sheet.png");
    brickOrange = loadAlphaTexture("assets\\images\\brick-orange-sheet.png");
    brickTough = loadAlphaTexture("assets\\images\\brick-tough-sheet.png");
    brickIndestructable = loadAlphaTexture("assets\\images\\brick-indestructable-sheet.png");

    //Borders
    techBorder = loadAlphaTexture("assets\\images\\border-sides.png");
    techCorner = loadAlphaTexture("assets\\images\\border-corner.png");
    techTopBorder = loadAlphaTexture("assets\\images\\border-top.png");
    lightning = loadAlphaTexture("assets\\images\\lightning.png");

    // Life Counter
    lifeCounter = loadAlphaTexture("assets\\images\\life-counter.png");
    lifeIcon = loadAlphaTexture("assets\\images\\life-icon.png");
    
    // Powerups
    capsuleLaser = loadAlphaTexture("assets\\images\\capsule-laser-sheet.png");
    capsuleExtraLife = loadAlphaTexture("assets\\images\\capsule-1up-sheet.png");
    capsuleSlow = loadAlphaTexture("assets\\images\\capsule-slow-sheet.png");
    capsuleTriple = loadAlphaTexture("assets\\images\\capsule-triple-sheet.png");
    capsuleWide = loadAlphaTexture("assets\\images\\capsule-wide-sheet.png");
    capsuleJump = loadAlphaTexture("assets\\images\\capsule-jump-sheet.png");
    capsuleMagnetic = loadAlphaTexture("assets\\images\\capsule-magnetic-sheet.png");

    // Level Warp
    levelWarpPortal = loadAlphaTexture("assets\\images\\level-skip-portal-sheet.png");
    levelWarpArrow = loadAlphaTexture("assets\\images\\level-skip-arrow.png");
}