#pragma once

#include <cstdint>
#include <memory>

#include "Rect.h"

struct SDL_Surface;
struct SDL_Texture;

/// Container for images
class ImageData
{
public:
    ImageData(int32_t w, int32_t h);
    ~ImageData();

    int32_t width() const { return this->w; }
    int32_t height() const { return this->h; }
    uint8_t bitsPerPixel() const;

protected:
    SDL_Surface* surface;
    SDL_Texture* texture;
    friend class Engine; // aren't you ? ;-)

private:
    int32_t w;
    int32_t h;
    int32_t index;

    ImageData();
    ImageData(const ImageData&) = delete;
    ImageData& operator= (const ImageData&) = delete;
};
