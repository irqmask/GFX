#include "Assets.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Engine.h"
#include "GameExceptions.h"
#include "ImageData.h"
#include "Path.h"

Assets::Assets()
    : path("./assets")
{
}


Assets::~Assets()
{
}


Assets& Assets::get()
{
    static Assets assets;
    return assets;
}


std::shared_ptr<ImageData> Assets::image(std::string id)
{
    if (images.find(id) == images.end())
        throw ResourceMissing(LOC, "Image with id '%s' not found!", id.c_str());
    return images[id];
}


void Assets::preloadImages(std::shared_ptr<Engine> engine)
{
    loadImage(engine, "ScnInventory", "MSTOCK-0.DAT", "MSTPAL-0.DAT", 320, 200);
}


void Assets::loadImage(std::shared_ptr<Engine> engine, const std::string &id, const std::string &filename, const std::string &palFilename, int32_t width, int32_t height)
{
    auto rawImage = loadRawImageData(filename, width, height);
    auto palette = loadPaletteData(palFilename);
    auto image = createRGBImage(engine, rawImage, palette, width, height);

    this->images.emplace(id, image);
}


std::vector<uint8_t> Assets::loadRawImageData(const std::string &filename, int32_t width, int32_t height)
{
    std::vector<uint8_t> pixelData;
    std::ifstream file(path.plusFilename(filename), std::ios::binary);

    if (!file) {
        throw ResourceMissing(LOC, "Failed to open image data file %s", filename.c_str());
    }

    pixelData.resize(width * height);
    file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

    return pixelData;
}


std::vector<Assets::Color> Assets::loadPaletteData(const std::string &filename)
{
    std::vector<Color> palette;
    std::ifstream file(path.plusFilename(filename), std::ios::binary);

    if (!file) {
        throw ResourceMissing(LOC, "Failed to open palette file %s", filename);
    }

    Color color;
    while (file.read(reinterpret_cast<char*>(&color), sizeof(Color))) {
        color.r *= 4;
        color.g *= 4;
        color.b *= 4;

        palette.push_back(color);
    }

    return palette;
}


std::shared_ptr<ImageData> Assets::createRGBImage(std::shared_ptr<Engine> engine, std::vector<uint8_t> &rawImage8, std::vector<Color> &palette, int32_t width, int32_t height)
{
    auto image = engine->createImage(width, height);
    engine->setRenderTarget(image);

    size_t pix = 0;
    for (int32_t y=0; y<height; y++) {
        for (int32_t x=0; x<width; x++) {
            uint8_t index = rawImage8[pix];
            if (index < palette.size()) {
                engine->setDrawForegroundColor(palette[index].r, palette[index].g, palette[index].b, 255);
                engine->drawPixel(x, y);
            }

            pix++;
        }
    }

    engine->setRenderTarget(nullptr);
    return image;
}
