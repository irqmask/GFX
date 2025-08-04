#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


#include "ImageData.h"
#include "Path.h"

class Engine;

class Assets
{
private:
    Assets();
    virtual ~Assets();

public:
    static Assets& get();

    std::shared_ptr<ImageData> image(std::string id);
    void sound(std::string id);

public:
    void preloadImages(std::shared_ptr<Engine> engine);
    void preloadSounds();
private:
    void loadImage(std::shared_ptr<Engine> engine, const std::string& id, const std::string& filename, const std::string& palette, int32_t width, int32_t height);

    struct Color {
        uint8_t r, g, b;
    };

    std::vector<uint8_t> loadRawImageData(const std::string& filename, int32_t width, int32_t height);
    std::vector<Color> loadPaletteData(const std::string& filename);
    std::shared_ptr<ImageData> createRGBImage(std::shared_ptr<Engine> engine, std::vector<uint8_t>& rawImage8, std::vector<Color>& palette, int32_t width, int32_t height);

    Path path;
    std::unordered_map<std::string, std::shared_ptr<ImageData>> images;
};
