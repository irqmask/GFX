#define SDL_MAIN_HANDLED

#include <string>

#include "Maze.h"


int main(void)
{
    auto maze = std::make_shared<Maze>();
    
    maze->run();
    maze.reset();
    return 0;
}
