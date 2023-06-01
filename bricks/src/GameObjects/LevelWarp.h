#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>

class LevelWarp {

    public:

        LevelWarp(SpriteManager* spriteManager);
        ~LevelWarp(){};
        void render();
        void update(double dt);    

        SDL_FRect warpRect;

    private:

        SDL_Texture* warpSprite;

        int warpWidth = 0;
        int warpHeight = 0;
        const static int numSprites = 7;
        static const int lastFrame = 6;
        float currentFrame = 0.f;
        SDL_Rect warpSpriteClips[numSprites];

        void sliceSpriteSheet();

};