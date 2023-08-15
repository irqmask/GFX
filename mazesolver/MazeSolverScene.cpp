#include "MazeSolverScene.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

// libgame
#include "Path.h"

#include "MazeData.h"

MazeSolverScene::MazeSolverScene(std::shared_ptr<Engine> engine)
    : Scene(engine)
{
    std::cout << __FUNCTION__ << std::endl;
    data = std::dynamic_pointer_cast<MazeData>(getData());
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    //auto image = loadImage(assetPath.plusFilename("tiles_30x30_test.png"));
    tileset = createImage(2 * tileWidth, tileHeight);
    setRenderTarget(tileset);
    // draw free space tile
    setDrawForegroundColor(255, 255, 150, 255);
    drawFilledRect(0, 0, tileWidth, tileHeight);
    // draw wall tile
    setDrawForegroundColor(128, 128, 128, 255);
    drawFilledRect(tileWidth, 0, tileWidth, tileHeight);
    setRenderTarget(nullptr);

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, tileset, tileWidth, tileHeight));
    tilemap->load(data->mazemap, data->tmCols, data->tmRows);
    Rect<int32_t> r(0, 0, getScaledWidth(), getScaledHeight());
    tilemap->setDrawRect(r);
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));

    nodes = new Node[data->tmRows * data->tmCols];
    for (int32_t y=0; y<data->tmRows; y++) {
        for (int32_t x=0; x<data->tmCols; x++) {
            auto node = &nodes[y * data->tmCols + x];
            node->globalGoal = INFINITY;
            node->localGoal = INFINITY;
            node->parent = nullptr;
            node->x = x;
            node->y = y;
            node->visited = false;
            node->neighbors.clear();

            fillNeighbors(x, y);
        }
    }
    currX = data->mapStartPos.x;
    currY = data->mapStartPos.y;
    auto startNode = &nodes[currY * data->tmCols + currX];
    startNode->globalGoal = calcHeuristics(currX, currY);
    startNode->localGoal = 0.0f;
    nodesToTest.push_back(&nodes[currY * data->tmCols + currX]);

    endNode = &nodes[data->mapEndPos.y * data->tmCols + data->mapEndPos.x];
}


MazeSolverScene::~MazeSolverScene()
{
    std::cout << __FUNCTION__ << std::endl;
}


void MazeSolverScene::update(float elapsed)
{
    (void)elapsed;
    auto camPos = tilemap->getCameraPos();
    if (keyIsPressed(Engine::KEY_UP))
        camPos.y -= 0.05f;
    if (keyIsPressed(Engine::KEY_DOWN))
        camPos.y += 0.05f;
    if (keyIsPressed(Engine::KEY_LEFT))
        camPos.x -= 0.05f;
    if (keyIsPressed(Engine::KEY_RIGHT))
        camPos.x += 0.05f;
    tilemap->setCameraPos(camPos);

    doFindPath();
}


void MazeSolverScene::draw()
{
    clearBackground(64, 64, 255, 255);

    tilemap->draw();

    // draw start position
    setDrawForegroundColor(0, 255, 0, 196);
    auto startPos = tilemap->getDrawPos(data->mapStartPos);
    drawFilledRect(startPos.x + 2, startPos.y + 2, tileWidth - 4, tileHeight - 4);

    // draw end position
    setDrawForegroundColor(255, 0, 0, 196);
    auto endPos = tilemap->getDrawPos(data->mapEndPos);
    drawFilledRect(endPos.x + 2, endPos.y + 2, tileWidth - 4, tileHeight - 4);

    // draw current position
    /*setDrawForegroundColor(255, 255, 0, 196);
    auto currPos = tilemap->getDrawPos(Vec2I32(currX, currY));
    drawFilledCircle(currPos.x + tileWidth/2, currPos.y + tileHeight/2, tileWidth/2 - 4);*/

    if (nodesToTest.size() > 0)
        drawPath(nodesToTest.front());
    else if (endNode != nullptr)
        drawPath(endNode);
    setDrawForegroundColor(32, 32, 64, 64);
    drawFilledRect(5, 5, 210, 40);

    setDrawForegroundColor(255, 255, 0, 192);
    font->print(10, 10, "The maze");

    auto camPos = tilemap->getCameraPos();
    std::stringstream str;
    int32_t lx = camPos.x; int32_t rx = fabsf(camPos.x - lx) * 10.0f;
    int32_t ly = camPos.y; int32_t ry = fabsf(camPos.y - ly) * 10.0f;
    str << "cam. pos X" << lx << "." << rx << " | Y" << ly << "." << ry;
    font->print(10, 20, str.str());
}


bool MazeSolverScene::nodeIsObstacle(int32_t x, int32_t y)
{
    if (data == nullptr || data->mazemap == nullptr || x < 0 || y < 0 || x >= data->tmCols || y >= data->tmRows) {
        return false;
    }
    return data->mazemap[y * data->tmCols + x] != 0;
}


bool MazeSolverScene::nodeIsVisited(int32_t x, int32_t y)
{
    if (nodes == nullptr || x < 0 || y < 0 || x >= data->tmCols || y >= data->tmRows) {
        return false;
    }
    return nodes[y * data->tmCols + x].visited;
}


bool MazeSolverScene::compareNodes(const Node *n1, const Node *n2)
{
    return (n1->localGoal < n2->localGoal);
}


void MazeSolverScene::fillNeighbors(int32_t x, int32_t y)
{
    Node *node = &nodes[y * data->tmCols + x];
    if (x > 0 && !nodeIsObstacle(x - 1, y)) {
        auto n = &nodes[y * data->tmCols + (x - 1)];
        node->neighbors.push_back(n);
    }
    if (x < data->tmCols - 1 && !nodeIsObstacle(x + 1, y)) {
        auto n = &nodes[y * data->tmCols + (x + 1)];
        node->neighbors.push_back(n);
    }
    if (y > 0 && !nodeIsObstacle(x, y - 1)) {
        auto n = &nodes[(y - 1) * data->tmCols + x];
        node->neighbors.push_back(n);
    }
    if (y < data->tmRows - 1 && !nodeIsObstacle(x, y + 1)) {
        auto n = &nodes[(y + 1) * data->tmCols + x];
        node->neighbors.push_back(n);
    }
}


float MazeSolverScene::calcHeuristics(int32_t x, int32_t y)
{
    float diffX = x - data->endPos.x;
    float diffY = y - data->endPos.y;
    return sqrtf(diffX * diffX + diffY * diffY);
}


bool MazeSolverScene::doFindPath()
{
    if (nodesToTest.size() == 0)
        return false;

    // fetch next node to test
    auto currNode = nodesToTest.front();

    // for each neighbor
    for (auto nn : currNode->neighbors) {
        if (nn->visited)
            continue;
        // add neighbor to node to test if not visited
        nodesToTest.push_back(nn);

        // if node local < neighbor local + distance to neighbor
        auto nnNewLocal = currNode->localGoal + 1;
        if (currNode->localGoal < nn->localGoal + 1) {
            // update neighbor's parent node, global- and local value
            nn->parent = currNode;
            nn->globalGoal = calcHeuristics(nn->x, nn->y);
            nn->localGoal = nnNewLocal;
        }
    }
    currNode->visited = true;
    nodesToTest.pop_front();

    // sort nodesToTest list, with lowest local value first
    std::sort(nodesToTest.begin(), nodesToTest.end(), compareNodes);
    return true;
}


void MazeSolverScene::drawPath(Node *endNode)
{
    setDrawForegroundColor(32, 32, 32, 255);
    while (endNode->parent != nullptr) {
        Vec2I32 p1(endNode->x, endNode->y);
        Vec2I32 p2(endNode->parent->x, endNode->parent->y);
        auto p1t = tilemap->getDrawPos(p1);
        auto p2t = tilemap->getDrawPos(p2);
        endNode = endNode->parent;
        drawLine(p1t.x + tileWidth / 2, p1t.y + tileHeight / 2, p2t.x + tileWidth / 2, p2t.y + tileHeight / 2);
    }
}
