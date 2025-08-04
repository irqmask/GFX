#include "MyScene.h"

#include <iostream>

#include "Path.h"

uint32_t TilemapDemo::level0[TilemapDemo::levelWidth * TilemapDemo::levelHeight] = {
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 2, 3, 3, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 2, 23, 11, 11, 21, 3, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 21, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 11, 21, 3, 3, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 21, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 18, 7, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 18, 7, 11, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 18, 7, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 11, 11, 21, 4, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 18, 7, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 10, 11, 11, 11, 11, 11, 11, 11, 12, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 18, 7, 11, 11, 11, 11, 11, 5, 20, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 18, 6, 7, 11, 11, 5, 20, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 18, 6, 6, 20, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14
};


TilemapDemo::TilemapDemo(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , mx(0)
    , my(0)
{
    std::cout << __FUNCTION__ << std::endl;
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    auto image = engine->loadImage(assetPath.plusFilename("tiles_30x30_test.png"));

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, image, tileWidth, tileHeight));
    tilemap->load(level0, levelWidth, levelHeight, -1);
    Rect<int32_t> r(0, 0, 640, 480);
    tilemap->setDrawRect(r);
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));
}


TilemapDemo::~TilemapDemo()
{
    std::cout << __FUNCTION__ << std::endl;
}


void TilemapDemo::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN && event.key.repeat == false) {
        switch (event.key.keysym.sym) {
        default:
            break;
        }
    }

    if (event.type == SDL_KEYUP && event.key.repeat == false) {
        switch (event.key.keysym.sym) {
        default:
            break;
        }
    }

    // convert to map coordinates
    Vec2d<int32_t> mousepos;
    mousepos.x = static_cast<int32_t>(mouseX() / static_cast<float>(tileWidth));
    mousepos.y = static_cast<int32_t>(mouseY() / static_cast<float>(tileHeight));

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int tt = tilemap->getTile(mousepos);
        if (event.button.button == SDL_BUTTON_LEFT)
            tt++;
        if (event.button.button == SDL_BUTTON_RIGHT)
            tt--;
        tilemap->setTile(mousepos, tt);
    }
}


void TilemapDemo::update(float elapsed)
{
    const uint8_t *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_LEFT]) {
        camV.x = -cameraSpeed;
    }
    else if (keystates[SDL_SCANCODE_RIGHT]) {
        camV.x = cameraSpeed;
    }
    else
        camV.x = 0.0f;

    if (keystates[SDL_SCANCODE_UP]) {
        camV.y = -cameraSpeed;
    }
    else if (keystates[SDL_SCANCODE_DOWN]) {
        camV.y = cameraSpeed;
    }
    else
        camV.y = 0.0f;

    camV *= elapsed;
    camPos += camV;
    tilemap->setCameraPos(camPos);
}


void TilemapDemo::draw()
{
    clearBackground(32, 32, 192, 255);

    tilemap->draw();

    setDrawForegroundColor(255, 255, 0, 192);
    drawRect(mx * tileWidth, my * tileHeight, tileWidth, tileHeight);


    font->print(0, 0, "tilemap");
}
