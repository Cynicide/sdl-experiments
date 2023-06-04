#pragma once
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <AudioManager.h>

class LetsGoUIElement {
    public:
        LetsGoUIElement(SpriteManager* spriteManager, AudioManager* audioManager);
        ~LetsGoUIElement(){};
        SDL_FRect letsGoRect;

        void update(double dt);
        void render();
        void reset();
        bool done();

    private:
        Mix_Music* letsGoMusic;
        SDL_Texture* letsGoSprite;
        static const int numSprites = 9;
        static const int lastFrame = 8;
        SDL_Rect letsGoSpriteClips[numSprites];
        float currentFrame = 0.f;
        int letsGoHeight = 0;
        int letsGoWidth = 0;
        void SliceSpriteSheet();

        bool animationDone = false;
        bool musicDone = false;
        bool musicStarted = false;
};