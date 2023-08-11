#pragma once

#include <stack>
#include <vector>

#include "Scene.h"

class MazeCreatorScene : public Scene
{
public:
    MazeCreatorScene(std::shared_ptr<Engine> engine);
    virtual ~MazeCreatorScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;
    
private:  
    enum {
        CELL_WALL_TOP       = 0x01,
        CELL_WALL_RIGHT     = 0x02,
        CELL_WALL_BOTTOM    = 0x04,
        CELL_WALL_LEFT      = 0x08,
        CELL_VISITED        = 0x10
    };

    static constexpr int32_t CELL_SIZE = 20;

    float interval;
    bool drawIt, finished;
    int32_t rows, columns;
    Vec2I32 startPos, endPos;
    std::stack<Vec2I32> places;
    uint8_t *maze;

    int32_t index(const Vec2I32 &coord) const;
    bool isVisited(const Vec2I32 &coord) const;
    void visit(const Vec2I32 &coord);
    void tearDownWalls(const Vec2I32 &from, const Vec2I32 &to);
    std::vector<Vec2I32> findUnvisitedNeigbors(const Vec2I32 &coord) const;
    void restart();
};
