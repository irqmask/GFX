#define SDL_MAIN_HANDLED

#include <string>

#include "Engine.h"

#include "MazeData.h"
#include "MazeCreatorScene.h"
#include "MazeSolverScene.h"

static const std::string appName = "mazesolver";

int main(void)
{
    std::shared_ptr<Engine> engine = std::unique_ptr<Engine>(new Engine(appName, 640, 480));
    engine->setScale(2.0, 2.0);
    auto mazedata = std::make_shared<MazeData>();
    engine->setSceneData(mazedata);

    auto creatorscene = std::make_shared<MazeCreatorScene>(engine);
    engine->enqueueScene(creatorscene);
    engine->runScene();

    auto solverscene = std::make_shared<MazeSolverScene>(engine);
    engine->enqueueScene(solverscene);
    engine->runScene();

    creatorscene.reset();
    engine.reset();
    return 0;
}
