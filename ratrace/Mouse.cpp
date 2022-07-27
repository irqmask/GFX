#include <memory>
#include <vector>

#include "Sprite.h"
#include "TileMap.h"

#include "Mouse.h"

const std::vector<Rect<int32_t>> Mouse::FRAMES_UP = {{ 0, 32, 32, 32}};

const std::vector<Rect<int32_t>> Mouse::FRAMES_RIGHT = {{ 32, 32, 32, 32}};

const std::vector<Rect<int32_t>> Mouse::FRAMES_DOWN = {{ 64, 32, 32, 32}};

const std::vector<Rect<int32_t>> Mouse::FRAMES_LEFT = {{ 96, 32, 32, 32}};

static constexpr auto TILESET_FILE = "ratrace.png";

Mouse::Mouse(std::shared_ptr<Engine> engine, std::shared_ptr<TileMap> tm)
    : Sprite()
    , d(DIR_NONE)
    , vx(0.0f)
    , vy(0.0f)
    , engine(engine)
    , tilemap(tm)
{
    std::shared_ptr<FrameSet> fs_up = std::make_shared<FrameSet>();
    fs_up->loadFromImage(TILESET_FILE, FRAMES_UP);
    addFrameSet(0, fs_up);

    std::shared_ptr<FrameSet> fs_right = std::make_shared<FrameSet>();
    fs_right->loadFromImage(TILESET_FILE, FRAMES_RIGHT);
    addFrameSet(1, fs_right);

    std::shared_ptr<FrameSet> fs_down = std::make_shared<FrameSet>();
    fs_down->loadFromImage(TILESET_FILE, FRAMES_DOWN);
    addFrameSet(2, fs_down);

    std::shared_ptr<FrameSet> fs_left = std::make_shared<FrameSet>();
    fs_left->loadFromImage(TILESET_FILE, FRAMES_LEFT);
    addFrameSet(3, fs_left);
}


void Mouse::setDirection(Direction d)
{
    if (d != this->d) {
        this->d = d;
        switch (this->d) {
        case Mouse::DIR_NORTH:
            this->vx = 0.0f; this->vy = -VELOCITY;
            this->setFrameSet(0);
            break;

        case Mouse::DIR_SOUTH:
            this->vx = 0.0f; this->vy = VELOCITY;
            this->setFrameSet(2);
            break;
        case Mouse::DIR_WEST:
            this->vx = -VELOCITY; this->vy = 0.0f;
            this->setFrameSet(3);
            break;

        case Mouse::DIR_EAST:
            this->vx = VELOCITY; this->vy = 0.0f;
            this->setFrameSet(1);
            break;

        default:
            this->vx = 0.0f; this->vy = 0.0f;
            break;
        }
    }
}


Mouse::Direction Mouse::getDirection()
{
    return this->d;
}

bool Mouse::isPosFree(const Vec2d<float> &pos) const
{
    return (tilemap->isPosInMap(pos) && tilemap->getTile(pos) == 0);
}


void Mouse::update(float elapsed)
{
    auto pos = this->getPos(); // TODO
    Vec2d<float> newPos = pos;
    newPos.x += this->vx * elapsed;
    newPos.y += this->vy * elapsed;

    // checking right pos depending on moving direction
    bool free = false;
    switch (this->d) {
    case Mouse::DIR_NORTH:
        // checking upper edge
        free = isPosFree(Vec2d<float>(newPos.x, newPos.y)) &&               // upper left
               isPosFree(Vec2d<float>(newPos.x + MOVE_LIMIT, newPos.y));    // upper right
        break;

    case Mouse::DIR_SOUTH:
        // checking lower edge
        free = isPosFree(Vec2d<float>(newPos.x, newPos.y + MOVE_LIMIT)) &&  // lower left
               isPosFree(Vec2d<float>(newPos.x + MOVE_LIMIT, newPos.y + MOVE_LIMIT)); // lower right
        break;

    case Mouse::DIR_WEST:
        // checking left edge
        free = isPosFree(Vec2d<float>(newPos.x, newPos.y)) &&               // upper left
               isPosFree(Vec2d<float>(newPos.x, newPos.y + MOVE_LIMIT));    // lower left
        break;

    case Mouse::DIR_EAST:
        // checking right edge
        free = isPosFree(Vec2d<float>(newPos.x + MOVE_LIMIT, newPos.y)) &&  // upper right
               isPosFree(Vec2d<float>(newPos.x + MOVE_LIMIT, newPos.y + MOVE_LIMIT)); // lower right
        break;

    default:
        break;
    }

    if (free) {
        setPos(newPos);
    } else {
        setDirection(Mouse::DIR_NONE); // stop
    }
}


void Mouse::draw()
{
    Sprite::draw();

    /*
    engine->setDrawForegroundColor(255, 200, 0, 255);
    int32_t x = this->tilemapPos.x * this->tilemap->getTileWidth();
    int32_t y = this->tilemapPos.y * this->tilemap->getTileHeight();
    engine->drawRect(5 + x, 5 + y, this->tilemap->getTileWidth(), this->tilemap->getTileHeight());

    engine->setDrawForegroundColor(255, 0, 0, 255);
    x = this->nextPos.x * tilemap->getTileWidth();
    y = this->nextPos.y * tilemap->getTileHeight();
    engine->drawRect(6 + x, 6 + y, tilemap->getTileWidth() - 2, tilemap->getTileHeight() - 2);
    */
}


const Vec2d<float> &Mouse::getPos() const
{
    return this->pos;
}


void Mouse::setPos(const Vec2d<float> &pos)
{
    this->pos = pos;
}
