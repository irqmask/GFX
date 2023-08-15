#pragma once

#include "Scene.h"
#include "TileMap.h"

class MazeData : public SceneData
{
public:
    MazeData()
        : SceneData()
        , maze(nullptr)
        , mazemap(nullptr)
    {};
    Vec2I32 startPos;
    Vec2I32 endPos;
    Vec2I32 mapStartPos;
    Vec2I32 mapEndPos;
    uint8_t *maze;
    int32_t tmRows;
    int32_t tmCols;
    TileMap::tiletype_t *mazemap;
};
