#include "AssetView.h"

#include <iostream>

#include "Path.h"

#include "Assets.h"

AssetView::AssetView(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , mx(0)
    , my(0)
{
    std::cout << __FUNCTION__ << std::endl;
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    auto image = engine->loadImage(assetPath.plusFilename("tiles_30x30_test.png"));

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, image, tileWidth, tileHeight));
    //tilemap->load(level0, levelWidth, levelHeight, -1);
    //Rect<int32_t> r(0, 0, 640, 480);
    //tilemap->setDrawRect(r);
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));

    Assets::get().preloadImages(engine);
}


AssetView::~AssetView()
{
    std::cout << __FUNCTION__ << std::endl;
}


void AssetView::onEvent(SDL_Event& event)
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
}


void AssetView::update(float elapsed)
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


void AssetView::draw()
{
    clearBackground(32, 32, 192, 255);

    //tilemap->draw();

    setDrawForegroundColor(255, 255, 0, 192);
    //drawRect(mx * tileWidth, my * tileHeight, tileWidth, tileHeight);
    auto image = Assets::get().image("ScnInventory");
    drawImage(0, 0, image);

    font->print(0, 0, "asset view");
}
