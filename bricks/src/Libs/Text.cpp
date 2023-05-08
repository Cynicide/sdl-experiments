#include <Text.h>

Text::Text() {

}

Text::Text(TTF_Font * font, std::string text, float x_loc, float y_loc, SDL_Renderer* gRenderer) {
    SDL_Color color = { 255, 255, 255 };
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    
    bool bQuery = SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    if (bQuery == 1) {
        SDL_Log( SDL_GetError());
    }
    
    textRect = {x_loc, y_loc, (float)textW, (float)textH};
}

void Text::destroy() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Text::render() {
    SDL_RenderCopyF(gRenderer, texture, NULL, &textRect);
}

void Text::setPos(int x, int y) {
    textRect.x = x;
    textRect.y = y;
}

void Text::padLeft( int padding) {
    textRect.x = textRect.x + padding;
}

void Text::centerHorizontally(int screen_width) {
    textRect.x = (screen_width / 2) - (textRect.w / 2);
}

void Text::centerVetically(int screen_height) {
    textRect.y = (screen_height / 2) - (textRect.h / 2);
}

void Text::center(int screen_width, int screen_height) {
    centerHorizontally(screen_width);
    centerVetically(screen_height);
}

void Text::moveTopQuarter(int screen_height) {
    textRect.y = (screen_height / 4) - (textRect.h / 2);
}
void Text::moveBottomQuarter(int screen_height){
    textRect.y = ((float)screen_height * 0.75f) - (textRect.h / 2);
}

void Text::moveBottomLeft(int screen_width, int screen_height, int* playfield_start_x) {
    if (playfield_start_x == nullptr) {
        textRect.y = ((float)screen_height - verticalOffset) - (textRect.h);
        textRect.x = horizontalOffset;
    } else {
        spdlog::info("Text Bottom Left Playfield");
        textRect.y = ((float)screen_height - verticalOffset) - (textRect.h);
        textRect.x = static_cast<float>(*playfield_start_x) + horizontalOffset;
    }

}

void Text::offsetAboveVertically(int offsetObjectY, int offsetObjectX) {
    textRect.y = (float)offsetObjectY - verticalOffset - textRect.h;
    textRect.x = (float)offsetObjectX;
}

int Text::getXLocation() {
    return (int)textRect.x;
}

int Text::getYLocation() {
    return (int)textRect.y;
}

void Text::setVerticalOffset(int offset) {
    verticalOffset = offset;
}

void Text::setHorizontalOffset( int offset) {
    horizontalOffset = offset;
}