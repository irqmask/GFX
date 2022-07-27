
#include <SDL.h>
#include <SDL_image.h>

#include "GameExceptions.h"
#include "BitmapFont.h"

extern SDL_Renderer* g_renderer;

BitmapFont::BitmapFont(std::string fontFile, uint16_t glyphWidth, uint16_t glyphHeight, uint16_t firstChar, uint16_t lastChar)
    : glyphWidth(glyphWidth)
    , glyphHeight(glyphHeight)
    , firstChar(firstChar)
    , lastChar(lastChar)
    , fontImage(nullptr)
{
    SDL_Surface *font_surface = IMG_Load(fontFile.c_str());
    if (font_surface == nullptr) {
        throw ResourceMissing(LOC, "Failed loading font image %s! %s", fontFile.c_str(), IMG_GetError());
    }
    SDL_Rect r = {0, 0, glyphWidth, glyphHeight};

    for (uint16_t ch = firstChar; ch < lastChar; ch++) {
        glyphs.push_back(r);
        r.x += glyphWidth;
        if (r.x > (font_surface->w - glyphWidth)) {
            r.x = 0;
            r.y += glyphHeight;
            if (r.y > font_surface->h) {
                throw OperationFailed(LOC, "Font image too small for glyph width %d, height %d, image width, %d height %d, first char %d, last %d!",
                                      glyphWidth, glyphHeight,
                                      font_surface->w, font_surface->h,
                                      firstChar, lastChar);
            }
        }
    }
    glyphs.push_back(r);

    fontImage = SDL_CreateTextureFromSurface(g_renderer, font_surface);
    if (fontImage == nullptr) {
        throw OperationFailed(LOC, "Unable to create texture for font %s", fontFile.c_str());
    }
}


BitmapFont::~BitmapFont()
{
    SDL_DestroyTexture(fontImage);
}


void BitmapFont::print(int32_t x, int32_t y, std::string s)
{
    for (char &c : s) {
        if (c < firstChar || c > lastChar) continue;

        uint16_t idx = c;
        idx -= firstChar;
        SDL_Rect &src = glyphs.at(idx);
        SDL_Rect dst = {x, y, glyphWidth, glyphHeight};
        SDL_RenderCopy(g_renderer, fontImage, &src, &dst);
        x += glyphWidth;
    }
}
