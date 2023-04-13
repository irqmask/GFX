#pragma once

#include <memory>
#include <SDL.h>

#include "EngineInterface.h"

class Engine;

/// Use a scene to implement difference, well, scenes, in your application.
/// For example, a game starts with an intro scene, followed by the actual level and then an outro scene.
/// The SceneManager will automatically play-back all scenes in the implemented order.
/// A Scene inherits the EngineInterface so that Engine based application can easily be turned into Scene
/// based applications.
class Scene : public EngineInterface
{
public:
    Scene(std::shared_ptr<Engine> engine);
    virtual ~Scene();

    virtual int32_t windowWidth() const override;
    virtual int32_t windowHeight() const override;
    virtual void setScale(float scaleX, float scaleY) override;

    virtual std::shared_ptr<ImageData> loadImage(const std::string& filename) const override;
    virtual std::shared_ptr<ImageData> copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const override;

    virtual void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    virtual void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    virtual void drawPixel(int32_t x, int32_t y) override;
    virtual void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
    virtual void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    virtual void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    virtual void drawCircle(int32_t x, int32_t y, int32_t r) override;
    virtual void drawFilledCircle(int32_t x, int32_t y, int32_t r) override;
    virtual void drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image) override;
    virtual void drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame) override;
    virtual void drawSprite(std::shared_ptr<Sprite> sprite) override;

    virtual float mouseX() override;
    virtual float mouseY() override;

    virtual void setTitle(std::string title) override;

    bool isRunning() { return keepRunning; }
    void endScene() { keepRunning = false; }

    virtual void onEvent(SDL_Event& event);

    virtual void update(float elapsed) = 0;
    virtual void draw() = 0;

private:
    std::shared_ptr<Engine> engine;
    SDL_Renderer* renderer;

    bool keepRunning;
};
