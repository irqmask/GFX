#include "TileMap.h"

#include "EngineInterface.h"
#include "ImageData.h"
#include "Sprite.h"

TileMap::TileMap(std::shared_ptr<EngineInterface> engine, std::shared_ptr<ImageData> tileset,
                 int32_t tile_width, int32_t tile_height)
    : tileWidth(tile_width)
    , tileHeight(tile_height)
    , width(0)
    , height(0)
    , mapData(nullptr)
    , engine(engine)
{
    frameSet = std::make_shared<FrameSet>();

    int tiles_in_row = tileset->height() / tile_height;
    int tiles_in_column = tileset->width() / tile_width;

    // load map tile graphics
    for (int row = 0; row < tiles_in_row; row++) {
        for (int column = 0; column < tiles_in_column; column++) {
            Rect<int32_t> r(column * tile_height, row * tile_width, tile_height, tile_width);
            auto f = std::make_shared<Frame>(engine->copyImage(tileset, r));
            frameSet->push_back(f);
        }
    }

    // create default tile lookup map
    for (int32_t i = 0; i < static_cast<int32_t>(frameSet->size()); i++) {
        tileLookup[i] = frameSet->at(i);
    }
}


TileMap::~TileMap()
{
}


void TileMap::load(uint32_t *map, int32_t width, int32_t heigth, int32_t indexOffset)
{
    this->width = width;
    this->height = heigth;
    this->mapData = map;
    if (indexOffset) {
        for (size_t idx=0; idx<width*height; idx++) {
            mapData[idx] += indexOffset;
        }
    }
}


void TileMap::setDrawRect(const Rect<int32_t> &r)
{
    this->drawRect = r;
    this->numDrawTilesX = r.size.x / this->tileWidth;
    this->numDrawTilesY = r.size.y / this->tileHeight;
    // we need to draw one more if drawrect size is not a true multiple of tile size
    if (r.size.x % this->tileWidth > 0)
        this->numDrawTilesX++;
    if (r.size.y % this->tileHeight > 0)
        this->numDrawTilesY++;
    // draw one more to avoid flickering at the sides
    this->numDrawTilesX++;
    this->numDrawTilesY++;
}


TileMap::tiletype_t TileMap::getTile(const Vec2d<int32_t> & pos)
{
    if (pos.x < 0 || pos.x >= this->width || pos.y < 0 || pos.y >= this->height)
        return 0;

    return this->mapData[pos.y * this->width + pos.x];
}


TileMap::tiletype_t TileMap::getTile(const Vec2d<float> &pos)
{
    Vec2d<int32_t> vi;
    vi.x = static_cast<int32_t>(pos.x);
    vi.y = static_cast<int32_t>(pos.y);
    return getTile(vi);
}


void TileMap::setTile(const Vec2d<int32_t> & pos, TileMap::tiletype_t tile)
{
    if (pos.x < 0 || pos.x >= this->width || pos.y < 0 || pos.y >= this->height)
        return;

    this->mapData[pos.y * this->width + pos.x] = tile;
}


void TileMap::draw()
{
    int32_t camX, camY;

    camX = static_cast<int32_t>(cameraPos.x);
    camY = static_cast<int32_t>(cameraPos.y);

    int32_t rx = ((float)(cameraPos.x - camX) * (float)this->tileWidth);
    int32_t ry = ((float)(cameraPos.y - camY) * (float)this->tileHeight);

    for (int32_t x = 0; x < numDrawTilesX; x++) {
        for (int32_t y = 0; y < numDrawTilesY; y++) {
            int32_t tx = x + camX;
            int32_t ty = y + camY;
            if (tx >= 0 && ty >= 0 && tx < this->width && ty < this->height) {
                tiletype_t tile = this->mapData[ty * this->width + tx];
                std::shared_ptr<Frame> frame = tileLookup[tile];
                if (frame != nullptr)
                    engine->drawFrame(x * tileWidth - rx, y * tileHeight - ry, frame);
            }
        }
    }
}


int32_t TileMap::getTileWidth() const
{
    return tileWidth;
}


int32_t TileMap::getTileHeight() const
{
    return tileHeight;
}


int32_t TileMap::getWidth() const
{
    return width;
}


int32_t TileMap::getHeight() const
{
    return height;
}


bool TileMap::isPosInMap(Vec2d<float> pos)
{
    return (pos.x >= 0.0f && pos.y >= 0.0f && pos.x < this->width && pos.y < this->height);
}


Vec2d<int32_t> TileMap::getDrawPos(Vec2d<int32_t> pos) const
{
    float posX = pos.x;
    float posY = pos.y;

    posX -= cameraPos.x;
    posY -= cameraPos.y;

    posX *= this->tileWidth;
    posY *= this->tileHeight;

    posX += this->drawRect.pos.x;
    posY += this->drawRect.pos.y;
    posX += 0.5f;
    posY += 0.5f;
    Vec2d<int32_t> vi;
    vi.x = static_cast<int32_t>(posX);
    vi.y = static_cast<int32_t>(posY);
    return vi;
}


Vec2d<int32_t> TileMap::getDrawPos(Vec2d<float> pos) const
{
    pos.x -= cameraPos.x;
    pos.y -= cameraPos.y;

    pos.x *= this->tileWidth;
    pos.y *= this->tileHeight;

    pos.x += this->drawRect.pos.x;
    pos.y += this->drawRect.pos.y;
    pos.x += 0.5f;
    pos.y += 0.5f;
    Vec2d<int32_t> vi;
    vi.x = static_cast<int32_t>(pos.x);
    vi.y = static_cast<int32_t>(pos.y);
    return vi;
}


Vec2d<float> TileMap::getCameraPos() const
{
    return cameraPos;
}

void TileMap::setCameraPos(Vec2d<float> pos)
{
    cameraPos = pos;
}
