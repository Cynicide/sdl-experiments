#pragma once
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL.h>
#include <SpriteManager.h>
#include <AudioManager.h>

class VerticalSplitTextUI {
    public:
        VerticalSplitTextUI(SpriteManager* spriteManager, SDL_Texture* topTexture, SDL_Texture* bottomTexture, Mix_Music * music);
        ~VerticalSplitTextUI(){};
        SDL_FRect topRect;
        SDL_FRect bottomRect;

        void update(double dt);
        void render();
        void reset();
        bool done();

    private:
        Mix_Music* music;
        SDL_Texture* topSprite;
        SDL_Texture* bottomSprite;

        // Both Sprites are the same Dimensions
        int spriteHeight = 0;
        int spriteWidth = 0;
        int uiSpeed = 600;
        
        bool animationDone = false;
        bool musicDone = false;
        bool musicStarted = false;
};