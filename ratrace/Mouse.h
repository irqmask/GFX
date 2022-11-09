#pragma once

#include <memory>
#include <vector>

#include "Sprite.h"
#include "TileMap.h"

class Engine;
class TileMap;

class Mouse : public Sprite
{
public:
    enum Direction
    {
        DIR_NONE,
        DIR_NORTH,
        DIR_EAST,
        DIR_SOUTH,
        DIR_WEST
    };

    Mouse(std::shared_ptr<Engine> engine, std::shared_ptr<ImageData> tileset, std::shared_ptr<TileMap> tm);

    virtual void update(float elapsed);
    virtual void draw();

    const Vec2d<float> & getPos() const;
    void setPos(const Vec2d<float> & pos);

    void setDirection(Direction d);
    Direction getDirection();

    bool isPosFree(const Vec2d<float> & pos) const;

protected:
    static constexpr float VELOCITY = 3.0f;
    static constexpr float MOVE_LIMIT = 0.95f;

    Direction d;
    Vec2d<float> pos;
    float vx, vy;

    std::shared_ptr<Engine> engine;
    std::shared_ptr<TileMap> tilemap;

private:
    static const std::vector<Rect<int32_t>> FRAMES_UP;
    static const std::vector<Rect<int32_t>> FRAMES_RIGHT;
    static const std::vector<Rect<int32_t>> FRAMES_DOWN;
    static const std::vector<Rect<int32_t>> FRAMES_LEFT;
};
