#pragma once

#include <cstdint>
#include <memory>

#include "Scene.h"
#include "TileMap.h"

class BitmapFont;
class Cheese;
class EnemyMouse;
class Mouse;

class RatLevel : public Scene
{
public:
    RatLevel(std::shared_ptr<Engine> engine);
    virtual ~RatLevel();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

    void enemyHit(std::shared_ptr<EnemyMouse> e);
    void eatCheese(std::shared_ptr<Cheese> c);
    void levelEnd();

private:
    static constexpr uint32_t LEVEL_W = 10;
    static constexpr uint32_t LEVEL_H = 10;
    static constexpr int32_t  TILE_W = 32; // pixel
    static constexpr int32_t  TILE_H = 32; // pixel

    static TileMap::tiletype_t level1[LEVEL_W * LEVEL_H];
   
    std::shared_ptr<BitmapFont> font;

    std::shared_ptr<Mouse> mouse;
    std::shared_ptr<TileMap> tilemap;
    std::vector<std::shared_ptr<EnemyMouse>> enemyMiceList;
    std::vector<std::shared_ptr<Cheese>> cheeseList;
};
