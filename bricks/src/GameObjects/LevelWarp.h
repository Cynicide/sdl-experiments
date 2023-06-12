#pragma once

#include <SDL2/SDL.h>
#include <SpriteManager.h>

class LevelWarp {

    public:

        LevelWarp(SpriteManager* spriteManager);
        ~LevelWarp(){};
        void render();
        void update(double dt);    

        SDL_FRect warpPortalRect;
        SDL_FRect warpPortalCollisionRect;
        SDL_FRect warpArrowRect;

    private:

        SDL_Texture* warpPortalSprite;
        int warpPortalWidth = 0;
        int warpPortalHeight = 0;
        const static int numSprites = 7;
        static const int lastFrame = 6;
        float currentPortalFrame = 0.f;
        SDL_Rect warpPortalSpriteClips[numSprites];


        SDL_Texture* warpArrowSprite;
        int warpArrowWidth = 0;
        int warpArrowHeight = 0;
        bool arrowBlink = true;
        int arrowBlinkTimer = 20;
        float currentArrowBlinkTimer = 0.f;

        //Since the portal appears in the wall we need to offset the collision slightly so the player can hit it.
        int xCollisionOffset = 5; 

        void sliceSpriteSheet();

};