#define SDL_MAIN_HANDLED

#include <memory>

#include "JoystickTest.h"

int main(void)
{
    auto joysticktest = std::make_shared<JoystickTest>();
    joysticktest->setScale(2.0f, 2.0f);

    joysticktest->run();

    joysticktest.reset();
    return 0;
}
