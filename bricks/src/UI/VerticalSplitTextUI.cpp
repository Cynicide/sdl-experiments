#include <VerticalSplitTextUI.h>
#include <globals.h>

VerticalSplitTextUI::VerticalSplitTextUI(SpriteManager* spriteManager, SDL_Texture* topTexture, SDL_Texture* bottomTexture, Mix_Music * music) {
    this->music = music;
    this->topSprite = topTexture;
    this->bottomSprite = bottomTexture;

    spriteManager->getTextureDimensions(topSprite, spriteWidth, spriteHeight);

    topRect = {(float)(SCREEN_WIDTH / 2) - ( spriteWidth / 2), (float)0 - spriteHeight, (float)spriteWidth, (float)spriteHeight};
    bottomRect = {(float)(SCREEN_WIDTH / 2) - ( spriteWidth / 2), (float)SCREEN_HEIGHT, (float)spriteWidth, (float)spriteHeight};

}

void VerticalSplitTextUI::update(double dt) {
    if (musicStarted == false) {
        musicStarted = true;
        Mix_PlayMusic(music, 0);
    } else {
        if (Mix_PlayingMusic() == 0) {
            musicDone = true;
        }
    }

    if (topRect.y < ((SCREEN_HEIGHT / 2) - spriteHeight)) {
        topRect.y = topRect.y + (uiSpeed * dt);
    }

    if (bottomRect.y > SCREEN_HEIGHT / 2) {
        bottomRect.y = bottomRect.y - (uiSpeed * dt);
    }

    if (topRect.y > ((SCREEN_HEIGHT / 2) - spriteHeight) && bottomRect.y < SCREEN_HEIGHT) {
        animationDone = true;
    }
}

bool VerticalSplitTextUI::done() {
    if (animationDone == true && musicDone == true) {
        return true;
    }
    return false;
}

void VerticalSplitTextUI::render() {
        SDL_RenderCopyF(gRenderer, topSprite, NULL, &topRect );
        SDL_RenderCopyF(gRenderer, bottomSprite, NULL, &bottomRect );
}

void VerticalSplitTextUI::reset() {
    animationDone = false;
    musicDone = false;
    musicStarted = false;
    topRect = {(float)(SCREEN_WIDTH / 2) - ( spriteWidth / 2), (float)0 - spriteHeight, (float)spriteWidth, (float)spriteHeight};
    bottomRect = {(float)(SCREEN_WIDTH / 2) - ( spriteWidth / 2), (float)(SCREEN_HEIGHT + spriteHeight), (float)spriteWidth, (float)spriteHeight};
}