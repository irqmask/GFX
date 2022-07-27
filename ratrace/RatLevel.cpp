#include <iomanip>
#include <iostream>
#include <sstream>

#include "BitmapFont.h"
#include "Cheese.h"
#include "EnemyMouse.h"
#include "Mouse.h"

#include "RatLevel.h"

TileMap::tiletype_t RatLevel::level1[] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 1, 0, 1, 0, 1, 1, 0, 1, 0,
      0, 1, 0, 1, 1, 0, 1, 0, 1, 0,
      0, 1, 0, 1, 1, 0, 1, 0, 1, 0,
      0, 1, 0, 1, 1, 0, 1, 0, 1, 0,
      0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
      0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

RatLevel::RatLevel(std::shared_ptr<Engine> engine)
    : Scene(engine)
{
    std::cout << __FUNCTION__ << std::endl;
    
    font = std::shared_ptr<BitmapFont>(new BitmapFont(std::string("font.png"), 9, 16, 20, 128));

    tilemap = std::shared_ptr<TileMap>(new TileMap(std::string("ratrace.png"), TILE_W, TILE_H));
    tilemap->load(level1, LEVEL_W, LEVEL_H);
    Rect<int32_t> mapviewrect;
    mapviewrect.pos.x = 5;
    mapviewrect.pos.y = 5;
    mapviewrect.size.x = engine->getWindowWidth() * 0.75;
    mapviewrect.size.y = engine->getWindowHeight() * 0.9;
    tilemap->setDrawRect(mapviewrect);

    mouse = std::make_shared<Mouse>(engine, tilemap);

}


RatLevel::~RatLevel()
{
    std::cout << __FUNCTION__ << std::endl;
}


void RatLevel::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_DOWN:
            mouse->setDirection(Mouse::DIR_SOUTH);
            break;
        case SDLK_UP:
            mouse->setDirection(Mouse::DIR_NORTH);
            break;
        case SDLK_LEFT:
            mouse->setDirection(Mouse::DIR_WEST);
            break;
        case SDLK_RIGHT:
            mouse->setDirection(Mouse::DIR_EAST);
            break;
        default:
            break;
        }
    }

}


void RatLevel::update(float elapsed)
{
    mouse->update(elapsed);

    for (auto emouse : enemyMiceList) {
        emouse->ai();
        emouse->update();

        if (mouse->isOverlapping(*emouse)) {
            enemyHit(emouse); // eeek
        }
    }

    for (const auto & cheese : cheeseList) {
        if (mouse->isOverlapping(*cheese)) {
            eatCheese(cheese);
        }
    }


    /* TODO if (cheeseList.size() == 0) {
        // level end
        levelEnd();
    } */

    Vec2d<float> camPos = mouse->getPos();
    camPos.x -= 3.0f;
    camPos.y -= 3.0f;
    tilemap->setCameraPos(camPos);

    mouse->setDrawPos(tilemap->getDrawPos(mouse->getPos()));

}


void RatLevel::draw()
{
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 0, 255);
    SDL_RenderClear(this->renderer);

    tilemap->draw();
    font->print(0, 0, "Hallo Welt!");

    for (auto cheese : cheeseList) {
        cheese->draw();
    }


    mouse->draw();

    for (auto emouse : enemyMiceList) {
        emouse->draw();
    }


    // debug output
    engine->setDrawForegroundColor(127, 127, 127, 127);
    engine->drawFilledRect(5, 5, 250, 50);
    Vec2d<float> pos = mouse->getPos();
    std::stringstream postext;
    postext << "X = " << std::setprecision(4) << pos.x << " Y = " << pos.y;
    font->print(10, 10, postext.str());
    std::stringstream tilepostext;
    /*auto tp = mouse->getTilemapPos();
    tilepostext << "tileX = " << std::setprecision(3) << tp.x << " tileY = " << tp.y;
    font->print(10, 20, tilepostext.str());*/



}


void RatLevel::enemyHit(std::shared_ptr<EnemyMouse> e)
{
    // TODO implement
}


void RatLevel::eatCheese(std::shared_ptr<Cheese> c)
{
    // TODO implement
}


void RatLevel::levelEnd()
{
    keepRunning = false;
    // TODO implement
}
