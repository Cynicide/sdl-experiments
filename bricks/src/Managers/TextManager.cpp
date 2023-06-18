#include <TextManager.h>
#include "spdlog/spdlog.h"

TextManager::TextManager() {
    auto logger = spdlog::get("fileLogger");
    logger->info("Creating Font Manager");
    loadFonts();
}

void TextManager::loadFonts() {
    publicPixel12 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 12);
    publicPixel24 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 24);
}