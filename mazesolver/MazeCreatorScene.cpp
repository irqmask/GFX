#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "MazeCreatorScene.h"

// --- public members ---------------------------------------------------------

MazeCreatorScene::MazeCreatorScene(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , interval(0.0f)
    , drawIt(false)
    , finished(false)
{
    std::cout << __FUNCTION__ << std::endl;    
    srand((int)std::time(0));

    rows = this->getScaledHeight() / CELL_SIZE;
    columns = this->getScaledWidth() / CELL_SIZE;
    std::cout << "Generating a " << columns << " x " << rows << " maze." << std::endl;
    maze = new uint8_t[rows * columns];
    memset(maze,
           CELL_WALL_TOP | CELL_WALL_RIGHT | CELL_WALL_BOTTOM | CELL_WALL_LEFT,
           rows * columns);
    startPos = Vec2I32(rand() % columns, rand() % rows);
    endPos = Vec2I32(-1, -1);
    visit(startPos); // set starting point
}


MazeCreatorScene::~MazeCreatorScene()
{
    std::cout << __FUNCTION__ << std::endl;
    delete maze;
}


void MazeCreatorScene::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);
    if (event.key.state == SDL_RELEASED && event.key.keysym.scancode == SDL_SCANCODE_F5)
        restart();
}


void MazeCreatorScene::update(float elapsed)
{
    interval += elapsed;

    if (finished) {
        if (interval > 1.0f) {
            this->endScene();
        }
    }
    else {
        if (interval < 0.05f) {
            return;
        }
        interval -= 0.05f;
    }

    if (places.size() > 0) {
        std::vector<Vec2I32> neighbors = findUnvisitedNeigbors(places.top());
        if (neighbors.size()) {
            int32_t nextNeighbor = rand() % neighbors.size();
            visit(neighbors[nextNeighbor]);
        }
        else {
            while(places.size() > 0 && findUnvisitedNeigbors(places.top()).size() == 0) {
                places.pop();
            }
        }
    }
    else {
        finished = true;
    }
    drawIt = true;
}


void MazeCreatorScene::draw()
{  
    if (!drawIt)
        return;

    clearBackground(32, 64, 128, 0);

    for (int32_t y = 0; y < rows; y++) {
        for (int32_t x = 0; x < columns; x++) {

            setDrawForegroundColor(255, 255, 255, 255);
            if (isVisited(Vec2I32(x, y)))
                drawFilledRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

            setDrawForegroundColor(0, 0, 0, 255);
            uint8_t walls = maze[y * columns + x];
            if (walls & CELL_WALL_TOP)
                drawLine(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
            if (walls & CELL_WALL_RIGHT)
                drawLine((x + 1) * CELL_SIZE - 1, y * CELL_SIZE, (x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
            if (walls & CELL_WALL_BOTTOM)
                drawLine(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1, (x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
            if (walls & CELL_WALL_LEFT)
                drawLine(x * CELL_SIZE, y * CELL_SIZE, x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);

            if (places.size() > 0) {
                if (x == places.top().x && y == places.top().y) {
                    setDrawForegroundColor(255, 255, 0, 255);
                    drawFilledRect(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2);
                }
            }
        }
    }
    // draw start position
    setDrawForegroundColor(0, 255, 0, 255);
    drawFilledRect(startPos.x * CELL_SIZE + 1, startPos.y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2);

    // draw end position
    if (finished) {
        setDrawForegroundColor(255, 0, 0, 255);
        drawFilledRect(endPos.x * CELL_SIZE + 1, endPos.y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2);
    }
}

// --- private members --------------------------------------------------------

std::vector<Vec2I32> MazeCreatorScene::findUnvisitedNeigbors(const Vec2I32 &coord) const
{
    Vec2I32 n;
    std::vector<Vec2I32> v;

    n = Vec2I32(coord.x, coord.y - 1);
    if (n.x >= 0 && n.x < columns && n.y >= 0 && n.y < rows) {
        if (!isVisited(n)) {
            v.push_back(n);
        }
    }

    n = Vec2I32(coord.x + 1, coord.y);
    if (n.x >= 0 && n.x < columns && n.y >= 0 && n.y < rows) {
        if (!isVisited(n)) {
            v.push_back(n);
        }
    }

    n = Vec2I32(coord.x, coord.y + 1);
    if (n.x >= 0 && n.x < columns && n.y >= 0 && n.y < rows) {
        if (!isVisited(n)) {
            v.push_back(n);
        }
    }

    n = Vec2I32(coord.x - 1, coord.y);
    if (n.x >= 0 && n.x < columns && n.y >= 0 && n.y < rows) {
        if (!isVisited(n)) {
            v.push_back(n);
        }
    }

    return v;
}


int32_t MazeCreatorScene::index(const Vec2I32 &coord) const
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {
        return coord.y * columns + coord.x;
    }
    return -1;
}


bool MazeCreatorScene::isVisited(const Vec2I32 &coord) const
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {
        if ((maze[coord.y * columns + coord.x] & CELL_VISITED) != 0) {
            return true;
        }
    }
    return false;
}


void MazeCreatorScene::tearDownWalls(const Vec2I32 &from, const Vec2I32 &to)
{
    Vec2I32 diff(to.x - from.x, to.y - from.y); //) = to - from;

    // going up
    if (diff.x == 0 && diff.y == -1) {
        maze[index(from)] &= ~CELL_WALL_TOP;
        maze[index(to)] &= ~CELL_WALL_BOTTOM;
    }

    // going right
    if (diff.x == 1 && diff.y == 0) {
        maze[index(from)] &= ~CELL_WALL_RIGHT;
        maze[index(to)] &= ~CELL_WALL_LEFT;
    }

    // going down
    if (diff.x == 0 && diff.y == 1) {
        maze[index(from)] &= ~CELL_WALL_BOTTOM;
        maze[index(to)] &= ~CELL_WALL_TOP;
    }

    // going left
    if (diff.x == -1 && diff.y == 0) {
        maze[index(from)] &= ~CELL_WALL_LEFT;
        maze[index(to)] &= ~CELL_WALL_RIGHT;
    }
}


void MazeCreatorScene::visit(const Vec2I32 &coord)
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {

        maze[coord.y * columns + coord.x] |= CELL_VISITED;
        if (places.size()) tearDownWalls(places.top(), coord);
        places.push(coord);
        endPos = coord;
    }
}


void MazeCreatorScene::restart()
{
    memset(maze,
           CELL_WALL_TOP | CELL_WALL_RIGHT | CELL_WALL_BOTTOM | CELL_WALL_LEFT,
           rows * columns);
    while (places.size()) {
        places.pop();
    }
    startPos = Vec2I32(rand() % columns, rand() % rows);
    endPos = Vec2I32(-1, -1);
    visit(startPos); // set starting point
}
