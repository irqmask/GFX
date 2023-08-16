#pragma once

#include <cstdint>
#include <memory>
#include <deque>

// libgame
#include "BitmapFont.h"
#include "Scene.h"
#include "TileMap.h"

class MazeData;

class MazeSolverScene : public Scene
{
public:
    MazeSolverScene(std::shared_ptr<Engine> engine);
    virtual ~MazeSolverScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

private:
    struct Node
    {
        bool visited;
        int32_t x, y;
        float localGoal;
        float globalGoal;
        std::vector<Node*> neighbors;
        Node *parent;
    };

    std::shared_ptr<MazeData> data;

    static constexpr int32_t tileWidth  = 9;
    static constexpr int32_t tileHeight = 9;

    Node *nodes;
    int32_t currX, currY;
    std::deque<Node*> nodesToTest;
    Node *endNode;

    std::shared_ptr<TileMap> tilemap;
    std::shared_ptr<ImageData> tileset;
    std::shared_ptr<BitmapFont> font;

    bool nodeIsObstacle(int32_t x, int32_t y);
    bool nodeIsVisited(int32_t x, int32_t y);
    static bool compareNodes(const Node *n1, const Node *n2);
    void fillNeighbors(int32_t x, int32_t y);
    float calcHeuristics(int32_t x, int32_t y);

    void startFindPath(Vec2I32 start, Vec2I32 end);

    /// @returns true, if it needs to be executed again.
    bool doFindPath();

    void drawPath(Node *endNode);
};
