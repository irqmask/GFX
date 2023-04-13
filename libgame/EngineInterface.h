/**
 * @file EngineInterface.h
 */
#pragma once

#include <cstdint>
#include <string>

/// Public interface for game engine and scenes.
class EngineInterface
{
public:
    virtual int32_t windowWidth() const = 0;
    virtual int32_t windowHeight() const = 0;
    virtual void setScale(float scaleX, float scaleY) = 0;

    virtual void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    virtual void drawPixel(int32_t x, int32_t y) = 0;
    virtual void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = 0;
    virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) = 0;
    virtual void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) = 0;
    virtual void drawCircle(int32_t x, int32_t y, int32_t r) = 0;
    virtual void drawFilledCircle(int32_t x, int32_t y, int32_t r) = 0;

    virtual float mouseX() = 0;
    virtual float mouseY() = 0;

    virtual void setTitle(std::string title) = 0;   
};
