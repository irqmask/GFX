#define SDL_MAIN_HANDLED

#include <string>

#include "Dirt.h"


int main(void)
{
    auto dirt = std::make_shared<Dirt>();
    
    dirt->run();
    dirt.reset();
    return 0;
}
