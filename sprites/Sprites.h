#pragma once

#include <memory>

#include "Scene.h"
#include "Sprite.h"

class MyScene : public Scene
{
public:
    MyScene(std::shared_ptr<Engine> engine);
    virtual ~MyScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

private:
    std::shared_ptr<Sprite> sprite;
};
