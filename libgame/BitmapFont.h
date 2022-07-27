#pragma once

#include <vector>
#include "Engine.h"

class BitmapFont
{
public:
    BitmapFont(std::string fontFile, uint16_t glyphWidth, uint16_t glyphHeight, uint16_t firstChar, uint16_t lastChar);
    virtual ~BitmapFont();

    void print(int32_t x, int32_t y, std::string s);

private:
    uint16_t glyphWidth;
    uint16_t glyphHeight;
    uint16_t firstChar;
    uint16_t lastChar;
    
    SDL_Texture *fontImage;
    std::vector<SDL_Rect> glyphs;
};
