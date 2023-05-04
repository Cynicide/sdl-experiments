#include <TextManager.h>

TextManager TextManager::sTextManager;

TextManager::TextManager() {

}

TextManager* TextManager::get()
{
    //Get static instance
    return &sTextManager;
}

void TextManager::loadFonts() {
    publicPixel12 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 12);
}