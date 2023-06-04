#include <LetsGoUIElement.h>
#include <globals.h>

LetsGoUIElement::LetsGoUIElement(SpriteManager* spriteManager, AudioManager* audioManager) {
    this->letsGoSprite = spriteManager->letsGo;
    this->letsGoMusic = audioManager->letsGo;

    spriteManager->getTextureDimensions(letsGoSprite, letsGoWidth, letsGoHeight);

    letsGoRect = {(float)(SCREEN_WIDTH / 2) - (( letsGoWidth / numSprites) / 2), (float)(SCREEN_HEIGHT / 2) - (letsGoHeight / 2), (float)letsGoWidth / numSprites, (float)letsGoHeight  };

    SliceSpriteSheet();
}

void LetsGoUIElement::update(double dt) {
    if (musicStarted == false) {
        musicStarted = true;
        Mix_PlayMusic(letsGoMusic, 0);
    } else {
        if (Mix_PlayingMusic() == 0) {
            musicDone = true;
        }
    }

    currentFrame = currentFrame + (30 * dt);
    if ((int)currentFrame > (float)lastFrame) {
        currentFrame = (float)lastFrame;
        animationDone = true;
    }
}

bool LetsGoUIElement::done() {
    if (animationDone == true && musicDone == true) {
        return true;
    }
    return false;
}

void LetsGoUIElement::render() {
        int frame = (int)currentFrame;
        SDL_Rect solidSprite = {letsGoSpriteClips[frame].x, letsGoSpriteClips[frame].y, letsGoSpriteClips[frame].w, letsGoSpriteClips[frame].h};
        SDL_RenderCopyF(gRenderer, letsGoSprite, &solidSprite, &letsGoRect );
}

void LetsGoUIElement::reset() {
    animationDone = false;
    musicDone = false;
    musicStarted = false;
    currentFrame = 0.f;
}

void LetsGoUIElement::SliceSpriteSheet() {
    for( int i = 0; i <= numSprites - 1; i++ ) {
        letsGoSpriteClips[ i ].x =   i * (letsGoWidth / numSprites);
        letsGoSpriteClips[ i ].y =   0;
        letsGoSpriteClips[ i ].w =  (letsGoWidth / numSprites);
        letsGoSpriteClips[ i ].h = letsGoHeight;
        }
}