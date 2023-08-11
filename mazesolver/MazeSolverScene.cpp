#include "MazeSolverScene.h"

#include <iostream>

#include "Path.h"

MazeSolverScene::MazeSolverScene(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , mx(0)
    , my(0)
{
    std::cout << __FUNCTION__ << std::endl;
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    auto image = engine->loadImage(assetPath.plusFilename("tiles_30x30_test.png"));

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, image, tileWidth, tileHeight));
    //FIXME tilemap->load(level0, levelWidth, levelHeight);
    Rect<int32_t> r(0, 0, 640, 480);
    tilemap->setDrawRect(r);
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));
}


MazeSolverScene::~MazeSolverScene()
{
    std::cout << __FUNCTION__ << std::endl;
}


void MazeSolverScene::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_DOWN:
            break;
        case SDLK_UP:
            break;
        case SDLK_LEFT:
            break;
        case SDLK_RIGHT:
            break;
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


void MazeSolverScene::update(float elapsed)
{
    (void)elapsed;
}


void MazeSolverScene::draw()
{
    clearBackground(32, 32, 192, 255);

    //tilemap->draw();

    setDrawForegroundColor(255, 255, 0, 192);
    drawRect(mx * tileWidth, my * tileHeight, tileWidth, tileHeight);


    font->print(0, 0, "tilemap");
}
