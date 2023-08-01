#define SDL_MAIN_HANDLED

#include <iostream>
#include <memory>
#include <string>

#include "Engine.h"
#include "MyScene.h"
#include "Path.h"

static const std::string appName = "tilemap";

int main(void)
{
    std::cout << "executable path " << Path::fromCurrentExecutable().toString() << std::endl;

    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 640, 480));
    engine->setScale(2.0, 2.0);
    std::shared_ptr<SpriteDemo> spritescene = std::make_shared<SpriteDemo>(engine);

    engine->setNextScene(spritescene);
    engine->runScene();
    
    spritescene.reset();
    engine.reset();
    return 0;
}
