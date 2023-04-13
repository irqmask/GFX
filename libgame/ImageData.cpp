#include "ImageData.h"

#include <cassert>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "GameExceptions.h"


static int32_t g_image_counter = 0;

ImageData::ImageData()
    : surface(nullptr)
    , texture(nullptr)
    , w(0)
    , h(0)
{
    this->index = g_image_counter++;
}


ImageData::ImageData(int32_t w, int32_t h)
    : surface(nullptr)
    , texture(nullptr)
    , w(w)
    , h(w)
{
    this->index = g_image_counter++;
}


ImageData::~ImageData()
{
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}


uint8_t ImageData::bitsPerPixel() const
{
    if (this->surface != nullptr) {
        return this->surface->format->BitsPerPixel;
    }
    return 32;
}
