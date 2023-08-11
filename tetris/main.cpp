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

    std::shared_ptr<SpriteDemo> spritescene = std::make_shared<SpriteDemo>(engine);

    engine->enqueueScene(spritescene);
    engine->runScene();

    spritescene.reset();
    engine.reset();
    return 0;
}
