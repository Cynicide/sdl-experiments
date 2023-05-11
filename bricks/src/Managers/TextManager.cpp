#include <TextManager.h>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ranges.h"

TextManager::TextManager() {
    spdlog::info("Creating Font Manager");
    loadFonts();
}

void TextManager::loadFonts() {
    publicPixel12 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 12);
    publicPixel24 = TTF_OpenFont("assets\\fonts\\PublicPixel.ttf", 24);
}