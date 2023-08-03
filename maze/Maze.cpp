#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Maze.h"

// --- public members ---------------------------------------------------------

Maze::Maze()
    : Engine("dirt", 640, 480)
    , interval(0.0f)
    , drawIt(false)
{
    std::cout << __FUNCTION__ << std::endl;    
    srand((int)std::time(0));

    rows = this->windowHeight() / CELL_SIZE;
    columns = this->windowWidth() / CELL_SIZE;
    std::cout << "Generating a " << columns << " x " << rows << " maze." << std::endl;
    maze = new uint8_t[rows * columns];
    memset(maze,
           CELL_WALL_TOP | CELL_WALL_RIGHT | CELL_WALL_BOTTOM | CELL_WALL_LEFT,
           rows * columns);
    visit(Vec2I32(0, 0)); // set starting point
}


Maze::~Maze()
{
    std::cout << __FUNCTION__ << std::endl;
    delete maze;
}


void Maze::onEvent(SDL_Event& event)
{
    (void)event;
}


void Maze::update(float elapsed)
{
    interval += elapsed;
    if (interval < 0.1f)
    {
        return;
    }
    interval -= 0.1f;

    std::vector<Vec2I32> neighbors = findUnvisitedNeigbors(places.top());
    if (neighbors.size()) {
        int32_t nextNeighbor = rand() % neighbors.size();
        std::cout << "nextNeighbor " << nextNeighbor << std::endl;
        visit(neighbors[nextNeighbor]);
    }
    else
    {
        while(findUnvisitedNeigbors(places.top()).size() == 0 && places.size() > 0) {
            places.pop();
        }
    }

    drawIt = true;
}


void Maze::draw()
{  
    if (!drawIt)
        return;

    clearBackground(0, 32, 128, 0);

    for (int32_t y = 0; y < rows; y++) {
        for (int32_t x = 0; x < columns; x++) {

            setDrawForegroundColor(255, 255, 255, 255);
            if (isVisited(Vec2I32(x, y)))
                drawFilledRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
//            else
//                drawRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

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

            if (x == places.top().x && y == places.top().y) {
                setDrawForegroundColor(0, 255, 0, 255);
                drawFilledRect(x * CELL_SIZE + 1, y * CELL_SIZE + 1, CELL_SIZE - 2, CELL_SIZE - 2);
            }
        }
    }
}

// --- private members --------------------------------------------------------

std::vector<Vec2I32> Maze::findUnvisitedNeigbors(const Vec2I32 &coord) const
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


int32_t Maze::index(const Vec2I32 &coord) const
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {
        return coord.y * columns + coord.x;
    }
    return -1;
}


bool Maze::isVisited(const Vec2I32 &coord) const
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {
        if ((maze[coord.y * columns + coord.x] & CELL_VISITED) != 0) {
            return true;
        }
    }
    return false;
}


void Maze::tearDownWalls(const Vec2I32 &from, const Vec2I32 &to)
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


void Maze::visit(const Vec2I32 &coord)
{
    if (coord.x >= 0 && coord.x < columns && coord.y >= 0 && coord.y < rows) {

        maze[coord.y * columns + coord.x] |= CELL_VISITED;
        if (places.size()) tearDownWalls(places.top(), coord);
        places.push(coord);
    }
}
