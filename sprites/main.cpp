#define SDL_MAIN_HANDLED

#include <memory>

#include "Engine.h"
#include "MyScene.h"
#include "Sprite.h"

static const std::string appName = "sprites";

int main(void)
{
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 320, 200);

    std::shared_ptr<MyScene> spritescene = std::make_shared<MyScene>(engine);

    engine->setNextScene(spritescene);
    engine->run();

    spritescene.reset();
    engine.reset();
    return 0;
}
