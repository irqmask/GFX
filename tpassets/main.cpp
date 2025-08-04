#define SDL_MAIN_HANDLED

#include <iostream>
#include <memory>
#include <string>

#include "Engine.h"
#include "GameExceptions.h"

#include "AssetView.h"

static const std::string appName = "Theme Park Assets";

int main(void)
{
    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 640, 480));
    engine->setScale(2.0, 2.0);
    try {
        auto scene = std::make_shared<AssetView>(engine);

        engine->enqueueScene(scene);
        engine->runScene();
    }
    catch (const GameException &e) {
        std::cerr << "Exception occurred: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
