#define SDL_MAIN_HANDLED

#include <ctime>
#include <memory>

#include "Engine.h"
#include "MyScene.h"

static const std::string appName = "tetris";

int main(void)
{
    time_t t;
    srand((unsigned) time(&t));

    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 480, 640);

    auto tetrisscene = std::make_shared<Tetris>(engine);

    engine->enqueueScene(tetrisscene);
    engine->runScene();

    tetrisscene.reset();
    engine.reset();
    return 0;
}
