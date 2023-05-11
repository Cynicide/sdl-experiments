#include <StartState.h>
#include <SpriteManager.h>
#include <TextManager.h>

StartState::StartState(PlayState* playState, SpriteManager* spriteManager, TextManager* textManager) 
: borderL(PLAYFIELD_STARTX, false, spriteManager->techBorder),
  borderR(PLAYFIELD_STARTX + PLAYFIELD_WIDTH - borderWidthV, true, spriteManager->techBorder),
  background(spriteManager->stars)
 {
    this->playState = playState;
    this->spriteManager = spriteManager;
    this->textManager = textManager;
}

bool StartState::enter()
{
    //Loading success flag
    bool success = true;
    spdlog::info("Entered StartState.");

    logoSprite = spriteManager->logo;

    int logoWidth;
    int logoHeight;

    bool bQuery = SDL_QueryTexture(logoSprite, NULL, NULL, &logoWidth, &logoHeight);
    if (bQuery == 1) {
        spdlog::error("Issue querying Logo Texture: ");
        spdlog::error(SDL_GetError());
    }

    logoRect = {(SCREEN_WIDTH / 2 - logoWidth / 2), (SCREEN_HEIGHT / 4) - (logoHeight / 2), logoWidth, logoHeight };

    font = textManager->publicPixel24;

    spaceToStart = Text(font, "Press Space to play!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gRenderer);
    spaceToStart.center(SCREEN_WIDTH, SCREEN_HEIGHT);
    spaceToStart.moveBottomQuarter(SCREEN_HEIGHT);

    qToQuit = Text(font, "Press q at any time to quit.", 0, 0, gRenderer);
    qToQuit.moveBottomLeft(SCREEN_WIDTH, SCREEN_HEIGHT, &PLAYFIELD_STARTX);
    qToQuit.padLeft(30);

    clickToLaunch = Text(font, "Click the left mouse to serve the ball.", 0, 0, gRenderer);
    clickToLaunch.offsetAboveVertically(qToQuit.getYLocation(), qToQuit.getXLocation());

    instructions = Text(font, "INSTRUCTIONS:", 0, 0, gRenderer);
    instructions.offsetAboveVertically(clickToLaunch.getYLocation(), clickToLaunch.getXLocation());

    return success;
}

bool StartState::exit()
{
    spdlog::info("Exited StartState");
    spaceToStart.destroy();
    qToQuit.destroy();
    clickToLaunch.destroy();
    instructions.destroy();
    return true;
}

void StartState::handleEvent( SDL_Event& e )
{
    //If the user pressed space move onto play state
    if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_SPACE ) )
    {
        setNextState(playState);
    }
}

void StartState::update(double dt)
{
    background.update(dt);
}

void StartState::render()
{
    background.render();
    borderL.render();
    borderR.render();
    SDL_RenderCopy(gRenderer, logoSprite, NULL, &logoRect );
    spaceToStart.render();
    qToQuit.render();
    clickToLaunch.render();
    instructions.render();
}