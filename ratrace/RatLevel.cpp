#include "RatLevel.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "BitmapFont.h"
#include "Path.h"
#include "ImageData.h"

#include "Cheese.h"
#include "EnemyMouse.h"
#include "Mouse.h"

TileMap::tiletype_t RatLevel::level1[] =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
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
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");

    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));
    auto image = engine->loadImage(assetPath.plusFilename("ratrace.png"));

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, image, TILE_W, TILE_H));
    tilemap->load(level1, LEVEL_W, LEVEL_H);
    Rect<int32_t> mapviewrect;
    mapviewrect.pos.x = 5;
    mapviewrect.pos.y = 5;
    mapviewrect.size.x = static_cast<int32_t>(static_cast<float>(windowWidth()) * 0.75f);
    mapviewrect.size.y = static_cast<int32_t>(static_cast<float>(windowHeight()) * 0.9f);
    tilemap->setDrawRect(mapviewrect);

    mouse = std::make_shared<Mouse>(engine, image, tilemap);
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
    clearBackground(255, 255, 0, 255);

    tilemap->draw();

    for (auto cheese : cheeseList) {
        drawSprite(cheese);
    }

    drawSprite(mouse);

    for (auto emouse : enemyMiceList) {
        drawSprite(emouse);
    }

    // debug output
    setDrawForegroundColor(127, 127, 127, 127);
    drawFilledRect(5, 5, 250, 50);
    Vec2d<float> pos = mouse->getPos();
    std::stringstream postext;
    postext << "X = " << std::setprecision(4) << pos.x << " Y = " << pos.y;
    font->print(10, 10, postext.str());
    std::stringstream tilepostext;
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
    endScene();
    // TODO implement
}
