#define SDL_MAIN_HANDLED

#include <string>

#include "Engine.h"
#include "Dirt.h"

static const std::string appName = "dirt";

int main(void)
{
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(appName, 500, 200);
    
    std::shared_ptr<DirtScene> dirtscene = std::make_shared<DirtScene>(engine);
    
    engine->setNextScene(dirtscene);
    engine->run();
    
    dirtscene.reset();   
    engine.reset();
    return 0;
}
