#include <Text.h>

Text::Text() {

}

Text::Text(TTF_Font * font, const char * text, int x_loc, int y_loc, SDL_Renderer* gRenderer) {
    SDL_Color color = { 255, 255, 255 };
    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    
    bool bQuery = SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }
    
    textRect = {x_loc, y_loc, textW, textH};
}

void Text::Destroy() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Text::Render() {
    SDL_RenderCopy(gRenderer, texture, NULL, &textRect);
}

void Text::SetPos(int x, int y) {
    textRect.x = x;
    textRect.y = y;
}
