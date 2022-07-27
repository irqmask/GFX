#define SDL_MAIN_HANDLED
#include <memory>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameExceptions.h"

static const std::string g_appName = "ttf2png";
static SDL_Window *g_window = nullptr;
static SDL_Renderer *g_renderer = nullptr;

void init(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw OperationFailed(LOC, "SDL_Init() failed! %s", SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0) {
        throw OperationFailed(LOC, "IMG_Init() failed! %s", IMG_GetError());
    }
    if (TTF_Init() < 0) {
        throw OperationFailed(LOC, "TTF_Init() failed! %s", TTF_GetError());
    }

    g_window = SDL_CreateWindow(g_appName.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                width, height,
                                SDL_WINDOW_SHOWN);
    if (g_window == nullptr) {
        throw OperationFailed(LOC, "SDL_CreateWindow() failed! %s", SDL_GetError());
    }

    g_renderer = SDL_CreateRenderer(g_window, -1, 0);
    if (g_renderer == nullptr) {
        throw OperationFailed(LOC, "SDL_CreateRenderer() failed! %s", SDL_GetError());
    }

    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

}

void deinit()
{
    if (g_window != nullptr) {
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface *createFontSurface(std::string & fontTTFFileName, uint16_t firstChar, uint16_t lastChar, uint16_t fontSize, SDL_Color *color, SDL_Color *bgColor)
{
    const int letterWidth = 9;
    const int letterHeight = fontSize;

    TTF_Font *font = TTF_OpenFont(fontTTFFileName.c_str(), letterHeight);
    if (font == nullptr) {
        throw ResourceMissing(LOC, "Font %s not found! %s", fontTTFFileName.c_str(), TTF_GetError());
    }

    const int imageWidth = 320;
    const int imageHeight = 200;

    uint32_t rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface *surface = SDL_CreateRGBSurface(0, imageWidth, imageHeight, 32, rmask, gmask, bmask, amask);
    uint32_t ubgcolor = SDL_MapRGBA(surface->format, bgColor->r, bgColor->g, bgColor->b, bgColor->a);
    SDL_FillRect(surface, nullptr, ubgcolor);
    int x=0, y=0;
    SDL_Rect glyph_rect = {0, 0, letterWidth, letterHeight};
    for (uint16_t ch=firstChar; ch<=lastChar; ch++) {
        SDL_Surface *glyph_surface = TTF_RenderGlyph_Solid(font, ch, *color);

        SDL_Rect dst_rect = {x, y, letterWidth, letterHeight};
        SDL_BlitSurface(glyph_surface, &glyph_rect, surface, &dst_rect);
        SDL_FreeSurface(glyph_surface);
        glyph_surface = nullptr;

        x += letterWidth;
        if (x > (imageWidth - letterWidth)) {
            x = 0;
            y += letterHeight;
        }
    }

    return surface;
}

int main(void)
{
    int width = 640;
    int height = 480;
    std::string font = "Px437_IBM_VGA_9x16.ttf";
    std::string outFilename = "font.png";
    SDL_Color color = {255, 255, 255, 255};
    SDL_Color bgcolor = {0, 0, 0, 0};

    init(width, height);

    SDL_Surface *fontSurface = createFontSurface(font, 20, 128, 16, &color, &bgcolor);
    if (IMG_SavePNG(fontSurface, outFilename.c_str()) < 0) {
        throw OperationFailed(LOC, "Unable to save font image! %s", IMG_GetError());
    }
    SDL_Texture *fontTx = SDL_CreateTextureFromSurface(g_renderer, fontSurface);
    SDL_FreeSurface(fontSurface);

    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, fontTx, nullptr, nullptr);
    SDL_RenderPresent(g_renderer);
    SDL_Delay(2000);

    SDL_DestroyTexture(fontTx);
    deinit();
    return 0;
}
