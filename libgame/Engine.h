#pragma once

#include <memory>
#include <string>
#include <deque>

#include <SDL.h>

#include "EngineInterface.h"
#include "Scene.h"

class Engine : public EngineInterface
{
public:
    Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight);
    virtual ~Engine();

    static constexpr float PI = 3.14159265358979323846f;
    static constexpr float DESIRED_FPS = 200.0f;

    float elapsed;
    float fps;

    float msX;
    float msY;

    static SDL_Renderer* getRenderer(); //FIXME remove need to have public access to SDL renderer
    int32_t windowWidth() const  override;
    int32_t windowHeight() const override;
    void setScale(float scaleX, float scaleY) override;
    int32_t getScaledWidth() const override;
    int32_t getScaledHeight() const override;

    void setRenderTarget(std::shared_ptr<ImageData> image) const override;

    std::shared_ptr<ImageData> createImage(int32_t width, int32_t height) const override;
    std::shared_ptr<ImageData> loadImage(const std::string &filename) const override;
    std::shared_ptr<ImageData> copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const override;

    void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void drawPixel(int32_t x, int32_t y) override;
    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
    void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawCircle(int32_t x, int32_t y, int32_t r) override;
    void drawFilledCircle(int32_t x, int32_t y, int32_t r) override;
    void drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image) override;
    void drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame) override;
    void drawSprite(std::shared_ptr<Sprite> sprite) override;

    float mouseX() override;
    float mouseY() override;

    void setTitle(std::string title) override;

    void run();
    void runScene();
    void enqueueScene(std::shared_ptr<Scene> scene);
    void setSceneData(std::shared_ptr<SceneData> data);
    std::shared_ptr<SceneData> getSceneData() const;
    void quit();

    virtual void onEvent(SDL_Event& event);

    virtual void update(float elapsed);
    virtual void draw();


private:
    std::string title;
    int32_t w;
    int32_t h;
    float scaleX;
    float scaleY;
    int32_t scaledWidth;
    int32_t scaledHeight;
    float ticks_per_frame = 1000.0f / DESIRED_FPS;
    SDL_Window *window;
    SDL_Renderer* renderer;
    std::deque<std::shared_ptr<Scene>> sceneStack;
    std::shared_ptr<SceneData> sceneData;
    std::shared_ptr<Scene> currentScene;
    bool keepRunning;

    void initializeGFX();
    void deinitialzeGFX();    
};
