#define SDL_MAIN_HANDLED

#include <memory>
#include <string>

#include "Engine.h"
#include "RatLevel.h"

static const std::string appName = "Rat Race";

int main(void)
{
    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 640, 480));
    engine->setScale(2.0, 2.0);
    auto ratractescene = std::make_shared<RatLevel>(engine);

    engine->enqueueScene(ratractescene);
    engine->runScene();
    
    ratractescene.reset();
    engine.reset();
    return 0;
}
