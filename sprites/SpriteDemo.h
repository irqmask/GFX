#pragma once

#include <memory>

#include "Scene.h"
#include "Sprite.h"

class SpriteDemo : public Scene
{
public:
    SpriteDemo(std::shared_ptr<Engine> engine);
    virtual ~SpriteDemo();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

private:
    std::shared_ptr<Sprite> sprite;
    std::shared_ptr<ImageData> imgFrameSet;
};
