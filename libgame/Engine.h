#pragma once

#include <memory>
#include <string>

#include <SDL.h>

#include "EngineInterface.h"
#include "Scene.h"

class Engine : public EngineInterface
{
public:
    Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight);
    virtual ~Engine();

    static constexpr float PI = 3.14159265358979323846f;

    float elapsed;
    float fps;

    float msX;
    float msY;

    static SDL_Renderer* getRenderer();
    int32_t windowWidth() const  override;
    int32_t windowHeight() const override;
    void setScale(float scaleX, float scaleY) override;

    void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void drawPixel(int32_t x, int32_t y) override;
    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
    void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawCircle(int32_t x, int32_t y, int32_t r) override;
    void drawFilledCircle(int32_t x, int32_t y, int32_t r) override;

    float mouseX() override;
    float mouseY() override;

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
