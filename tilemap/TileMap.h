#ifndef TILEMAP_H
#define TILEMAP_H

#include <memory>
#include <string>

#include "Sprite.h"

class EngineInterface;

class TileMap
{
public:
    typedef uint32_t tiletype_t;

    ///
    /// \brief TileMap
    /// \param[in] engine       Engine or scene where this TileMap will be used in
    /// \param[in] tileset      Tileset image to load map tiles from
    /// \param[in] tile_width   Tile width in pixels
    /// \param[in] tile_height  Tile Height in pixels
    ///
    TileMap(std::shared_ptr< EngineInterface> engine, std::shared_ptr<ImageData> tileset,
            int32_t tile_width, int32_t tile_height);
    ~TileMap();

    void load(tiletype_t *map, int32_t width, int32_t heigth, int32_t indexOffset=0);
    
    /// set position and size of Tilemap on Screen
    void setDrawRect(const Rect<int32_t> & r);

    tiletype_t getTile(const Vec2d<int32_t> & pos);
    tiletype_t getTile(const Vec2d<float> & pos);
    void setTile(const Vec2d<int32_t> & pos, tiletype_t tile);

    /// draw the tilemap. Position and size defined by setDrawRect()
    void draw();

    /// @return tile width in number of pixels
    int32_t getTileWidth() const;

    /// @return tile height in number of pixels
    int32_t getTileHeight() const;

    /// @returns total map width in number of tiles
    int32_t getWidth() const;

    /// @returns total map height in number of tiles
    int32_t getHeight() const;

    bool isPosInMap(Vec2d<float> pos);

    /// Get draw position from map position
    Vec2d<int32_t> getDrawPos(Vec2d<int32_t> pos) const;

    /// Get draw position from map position
    Vec2d<int32_t> getDrawPos(Vec2d<float> pos) const;

    /// @returns camera position
    Vec2d<float> getCameraPos() const;

    /// set camera position. The camera position defines the top left tile to draw
    /// @param[in]  pos     Camera position
    void setCameraPos(Vec2d<float> pos);

protected:
    /// tile width in pixels
    int32_t tileWidth;
    /// tile height in pixels
    int32_t tileHeight;
    /// total map width in number of tiles
    int32_t width;
    /// total map height in number of tiles
    int32_t height;
    /// displayed rectangle of tilemap on screen
    Rect<int32_t> drawRect;
    /// number of displayed tiles in X direction
    int32_t numDrawTilesX;
    /// number of displayed tiles in X direction
    int32_t numDrawTilesY;

    Vec2d<float> cameraPos;

    std::shared_ptr<FrameSet> frameSet;
    tiletype_t* mapData;
    std::map<int32_t, std::shared_ptr<Frame>> tileLookup;
    std::shared_ptr<EngineInterface> engine;
};

#endif // TILEMAP_H
