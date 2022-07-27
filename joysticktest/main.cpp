#define SDL_MAIN_HANDLED

#include <memory>

#include "Engine.h"
#include "MyScene.h"

static const std::string appName = "joysticktest";

int main(void)
{
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 800, 600);
    engine->setScale(2.0f, 2.0f);

    std::shared_ptr<MyScene> joystickscene = std::make_shared<MyScene>(engine);

    engine->setNextScene(joystickscene);
    engine->run();

    joystickscene.reset();
    engine.reset();
    return 0;
}
