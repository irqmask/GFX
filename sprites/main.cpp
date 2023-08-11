#define SDL_MAIN_HANDLED

#include <memory>

#include "Engine.h"

#include "SpriteDemo.h"

static const std::string appName = "sprites";

int main(void)
{
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 320, 200);

    auto spritescene = std::make_shared<SpriteDemo>(engine);

    engine->enqueueScene(spritescene);
    engine->runScene();

    spritescene.reset();
    engine.reset();
    return 0;
}
