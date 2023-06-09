#include <StartState.h>
#include "spdlog/spdlog.h"

StartState::StartState(GameContext* gameContext, PlayState* playState) :
    gameContext(gameContext),
    playState(playState)
 {
    titleTrack = gameContext->audioManager.titleTrack;
 }

bool StartState::enter()
{
    auto logger = spdlog::get("fileLogger");
    //Loading success flag
    bool success = true;
    logger->info("Entered StartState.");

    font = gameContext->publicPixel24;

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

    Mix_PlayMusic(titleTrack, -1);

    return success;
}

bool StartState::exit()
{
    auto logger = spdlog::get("fileLogger");
    logger->info("Exited StartState");
    spaceToStart.destroy();
    qToQuit.destroy();
    clickToLaunch.destroy();
    instructions.destroy();
    Mix_HaltMusic();
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
    gameContext->scrollingBackground.update(dt);
    gameContext->logoSprite.update(dt);
}

void StartState::render()
{
    gameContext->scrollingBackground.render();
    gameContext->borderL.render();
    gameContext->borderR.render();
    //SDL_RenderCopy(gRenderer, gameContext->logoSprite, NULL, &logoRect );
    spaceToStart.render();
    qToQuit.render();
    clickToLaunch.render();
    instructions.render();
    gameContext->logoSprite.render();
}