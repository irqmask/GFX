#ifndef MYSCENE_H
#define MYSCENE_H

#include <cstdint>
#include <memory>

#include "Scene.h"
#include "BitmapFont.h"
#include "TileMap.h"

class MyScene : public Scene
{
public:
    MyScene(std::shared_ptr<Engine> engine);
    virtual ~MyScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

private:
    static constexpr uint32_t levelWidth = 10;
    static constexpr uint32_t levelHeight = 10;
   
    static TileMap::tiletype_t level0[levelWidth * levelHeight];

    static constexpr int32_t tileWidth  = 30;
    static constexpr int32_t tileHeight = 30;
    std::shared_ptr<TileMap> tilemap;

    int32_t mx, my;
    std::shared_ptr<BitmapFont> font;
};

#endif // MYSCENE_H
