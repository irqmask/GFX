/**
 * @file EngineInterface.h
 */
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Rect.h"

class ImageData;
class Frame;
class Sprite;

/// Public interface for game engine and scenes.
class EngineInterface
{
public:
    virtual int32_t windowWidth() const = 0;
    virtual int32_t windowHeight() const = 0;
    virtual void setScale(float scaleX, float scaleY) = 0;

    virtual std::shared_ptr<ImageData> loadImage(const std::string& filename) const = 0;
    virtual std::shared_ptr<ImageData> copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const = 0;

    virtual void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void drawPixel(int32_t x, int32_t y) = 0;
    virtual void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = 0;
    virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) = 0;
    virtual void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) = 0;
    virtual void drawCircle(int32_t x, int32_t y, int32_t r) = 0;
    virtual void drawFilledCircle(int32_t x, int32_t y, int32_t r) = 0;
    virtual void drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image) = 0;
    virtual void drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame) = 0;
    virtual void drawSprite(std::shared_ptr<Sprite> sprite) = 0;

    virtual float mouseX() = 0;
    virtual float mouseY() = 0;

    virtual void setTitle(std::string title) = 0;   
};
