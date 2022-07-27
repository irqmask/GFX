#define SDL_MAIN_HANDLED

#include <memory>
#include <string>

#include "Engine.h"
#include "MyScene.h"

static const std::string appName = "tilemap";

int main(void)
{
    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 640, 480));
    engine->setScale(2.0, 2.0);
    std::shared_ptr<MyScene> spritescene = std::make_shared<MyScene>(engine);

    engine->setNextScene(spritescene);
    engine->run();
    
    spritescene.reset();
    engine.reset();
    return 0;
}
