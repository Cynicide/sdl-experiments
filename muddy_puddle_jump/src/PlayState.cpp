#include <PlayState.h>

PlayState PlayState::sPlayState;

PlayState::PlayState() {

}

PlayState* PlayState::get()
{
    //Get static instance
    return &sPlayState;
}

bool PlayState::enter()
{
    SDL_Log("Entered PlayState\n");
    //Loading success flag
    bool success = true;
    
    peppaYmax = 0;
    peppaYmin = 0;
    peppaYvelUp = 400;
    peppaYvelDown = 600;
    peppaJumpheight = 100;
    numOfJumps = 0;
    numOfJumpsMax = 3;
    score = 0;
    countdown = 60;
    timeLeft = 1.0f;

    scoreText.Destroy();
    scoreText = Text(font, ("Score: " + std::to_string(score)).c_str(), 20, 20, gRenderer);

    timeText.Destroy();
    timeText = Text(font, std::to_string(countdown).c_str(), SCREEN_WIDTH / 2, 20, gRenderer);

    backgroundTexture = ImageLib::get()->loadTexture("assets\\images\\background1080.png");
    peppaTexture = ImageLib::get()->loadTexture("assets\\images\\peppaboots-200px-sheet.png");
    puddleTexture = ImageLib::get()->loadTexture("assets\\images\\puddle.png");;
    
    SliceSpriteSheet();

    substate = PREPARING;

   // Set Up Game
    return success;
}

bool PlayState::exit()
{
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(peppaTexture);
    SDL_DestroyTexture(puddleTexture);
    SDL_Log("Exited PlayState\n");
    return true;
}

void PlayState::handleEvent( SDL_Event& e )
{

}

void PlayState::update(float dt)
{
    RunCountDown(dt);

    if (substate == PREPARING) {

        int puddle_textureWidth, puddle_textureHeight;

        SDL_QueryTexture(puddleTexture, NULL, NULL, &puddle_textureWidth, &puddle_textureHeight);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> locationx(50, 1700);
        std::uniform_int_distribution<int> locationy(600, 1000);

        puddle_offset.x = locationx(gen);
        puddle_offset.y = locationy(gen);
        puddle_offset.w = puddle_textureWidth;
        puddle_offset.h = puddle_textureHeight;

        substate = PLAYING;
    }

    if (substate == PLAYING) {


        int x, y;
        Uint32 mouseState = SDL_GetMouseState(&x, &y);

        peppa_offset.x = x;
        peppa_offset.y = y;
        peppa_offset.w = gSpriteClips[0].w;
        peppa_offset.h = gSpriteClips[0].h;

        // If Colliding with Puddle then change to animation state
        if (AABBCheck(peppa_offset, puddle_offset)) {
            jumpTimer = 0.0f;
            peppa_offset.x = puddle_offset.x - ((gSpriteClips[1].w - puddle_offset.w) /2);
            peppa_offset.y = (puddle_offset.y + puddle_offset.h) - gSpriteClips[1].h;
            peppa_offset.w = gSpriteClips[1].w;
            peppa_offset.h = gSpriteClips[1].h;
            peppaYmax = peppa_offset.y;
            peppaYmin = peppa_offset.y - peppaJumpheight;
            substate = JUMPING;
            
            bool is_playing = Mix_Playing(2);

            if (is_playing) {
                // Don't do anything
            } 
            else 
            {
                Mix_PlayChannel(2, puddles, 0);
            }
        }
    } 

    if (substate == JUMPING) {


        if (jumpdirection == UP) {
            peppa_offset.y = peppa_offset.y - (peppaYvelUp * dt);

            if ((peppa_offset.y < peppaYmin)) {
                jumpdirection = DOWN;
            }
        }

        if (jumpdirection == DOWN) {
            peppa_offset.y = peppa_offset.y + (peppaYvelDown * dt);

            if ((peppa_offset.y > peppaYmax)) {
                jumpdirection = UP;
                numOfJumps = numOfJumps + 1;
            }
        }

        if (numOfJumps > numOfJumpsMax) {
            scoreText.Destroy();
            score = score + 1;
            scoreText = Text(font, ("Score: " + std::to_string(score)).c_str(), 20, 20, gRenderer);
            numOfJumps = 0;
            substate = PREPARING;
        }

    }
}

void PlayState::render()
{
    SDL_RenderCopyF(gRenderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopyF(gRenderer, puddleTexture, NULL, &puddle_offset);

    if (substate == JUMPING) {

        if (jumpdirection == UP) {
            SDL_RenderCopyF(gRenderer, peppaTexture, &gSpriteClips[2], &peppa_offset);
        } 
        else 
        {
            SDL_RenderCopyF(gRenderer, peppaTexture, &gSpriteClips[1], &peppa_offset);
        }
    }

    if (substate == PLAYING) {

        SDL_RenderCopyF(gRenderer, peppaTexture, &gSpriteClips[0], &peppa_offset);
    }

    scoreText.Render();
    timeText.Render();
}

bool PlayState::AABBCheck(SDL_FRect rPeppa, SDL_FRect rPuddle) 
{ 
  return !(rPeppa.x + rPeppa.w < rPuddle.x || rPeppa.x > rPuddle.x + rPuddle.w || rPeppa.y + rPeppa.h < rPuddle.y || rPeppa.y > rPuddle.y + rPuddle.h); 
}

void PlayState::SliceSpriteSheet() {
    //Set sprite clips
    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  200;
    gSpriteClips[ 0 ].h = 200;

    gSpriteClips[ 1 ].x =  200;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  200;
    gSpriteClips[ 1 ].h = 200;
    
    gSpriteClips[ 2 ].x = 400;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  200;
    gSpriteClips[ 2 ].h = 200;
}

void PlayState::RunCountDown(float dt) {
    timeLeft -= dt;

    if (timeLeft <= 0.0f) {
        countdown--;
    if (countdown <= 0) 
        {
        setNextState( GameOverState::get(score) );
        }
        else 
        {
        timeText.Destroy();
        timeText = Text(font, std::to_string(countdown).c_str(), SCREEN_WIDTH / 2, 20, gRenderer);
        timeLeft = 1.0f; // reset the timer to 1 second
        }
    }
}