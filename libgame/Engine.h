#pragma once

#include <memory>
#include <string>

#include <SDL.h>

#include "Scene.h"

class Engine
{
public:
    Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight);
    virtual ~Engine();

    static constexpr float PI = 3.14159265358979323846f;

    float elapsed;
    float fps;

    float mouseX;
    float mouseY;

    static SDL_Renderer* getRenderer();
    int32_t getWindowWidth();
    int32_t getWindowHeight();
    void setScale(float scaleX, float scaleY);

    void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
    void drawRect(int32_t x, int32_t y, int32_t w, int32_t h);
    void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h);
    void drawCircle(int32_t x, int32_t y, int32_t r);
    void drawFilledCircle(int32_t x, int32_t y, int32_t r);

    void run();
    void setNextScene(std::shared_ptr<Scene> scene);

    void setTitle(std::string title);
    
private:
    std::string title;
    int32_t w;
    int32_t h;
    float scaleX;
    float scaleY;
    SDL_Window *window;
    std::shared_ptr<Scene> current_scene;
    std::shared_ptr<Scene> next_scene;
    
    void initializeGFX();
    void deinitialzeGFX();    
};
