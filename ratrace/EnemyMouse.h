#pragma once

#include "Mouse.h"

class EnemyMouse : public Mouse
{
public:
    EnemyMouse(std::shared_ptr<Engine> engine, std::shared_ptr<ImageData> tileset, std::shared_ptr<TileMap> tm);

    void ai();
    void update();
};

