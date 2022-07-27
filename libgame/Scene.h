#pragma once

#include <memory>
#include <SDL.h>

class Engine;

class Scene
{
public:
    Scene(std::shared_ptr<Engine> engine);
    virtual ~Scene();

    int32_t getW() { return w; }
    int32_t getH() { return h; }

    bool isRunning() { return keepRunning; }

    virtual void onEvent(SDL_Event& event);

    virtual void update(float elapsed) = 0;
    virtual void draw() = 0;

protected:
    std::shared_ptr<Engine> engine;
    SDL_Renderer* renderer;
    int32_t w;
    int32_t h;

    bool keepRunning;
};
