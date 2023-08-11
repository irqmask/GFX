#define SDL_MAIN_HANDLED

#include <string>

#include "Engine.h"
#include "MazeCreatorScene.h"
#include "MazeSolverScene.h"

static const std::string appName = "mazesolver";

int main(void)
{
    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 540, 480));
    engine->setScale(2.0, 2.0);
    auto creatorscene = std::make_shared<MazeCreatorScene>(engine);
    auto solverscene = std::make_shared<MazeSolverScene>(engine);
    engine->enqueueScene(creatorscene);
    engine->enqueueScene(solverscene);
    engine->runScene();

    creatorscene.reset();
    engine.reset();
    return 0;
}
