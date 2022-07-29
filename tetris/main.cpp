#define SDL_MAIN_HANDLED

#include <ctime>
#include <memory>

#include "Engine.h"
#include "MyScene.h"
#include "Sprite.h"

static const std::string appName = "tetris";

int main(void)
{
    time_t t;
    srand((unsigned) time(&t));

    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 480, 640);

    std::shared_ptr<MyScene> spritescene = std::make_shared<MyScene>(engine);

    engine->setNextScene(spritescene);
    engine->run();

    spritescene.reset();
    engine.reset();
    return 0;
}
