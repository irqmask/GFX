#include <iostream>

#include "MyScene.h"

uint32_t MyScene::level0[MyScene::levelWidth * MyScene::levelHeight] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    0, 22, 22, 22, 10, 10, 11, 11, 12,  0,
    0,  9,  1,  1,  1, 10, 11, 11, 20,  0,
    0,  0,  1,  21,  1,  0,  1,  0,  1,  0,
    0,  0,  1,  1,  1,  1,  0,  1,  0,  1,
    0,  0,  1,  1,  1,  0,  1,  0,  1,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

MyScene::MyScene(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , mx(0)
    , my(0)
{
    std::cout << __FUNCTION__ << std::endl;
    //tilemap = std::shared_ptr<TileMap>(new TileMap(std::string("tiles_30x30_test.png"), tileWidth, tileHeight));
    tilemap = std::shared_ptr<TileMap>(new TileMap(std::string("/home/christian/Dokumente/Kinder/Frederik/zitronensuche.png"), tileWidth, tileHeight));
    tilemap->load(level0, levelWidth, levelHeight);
    Rect<int32_t> r(0, 0, 640, 480);
    tilemap->setDrawRect(r);
    font = std::shared_ptr<BitmapFont>(new BitmapFont(std::string("font.png"), 9, 16, 20, 128));
}

MyScene::~MyScene()
{
    std::cout << __FUNCTION__ << std::endl;
}

void MyScene::onEvent(SDL_Event& event)
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
    mousepos.x = engine->mouseX / tileWidth;
    mousepos.y = engine->mouseY / tileHeight;

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int tt = tilemap->getTile(mousepos);
        if (event.button.button == SDL_BUTTON_LEFT)
            tt++;
        if (event.button.button == SDL_BUTTON_RIGHT)
            tt--;
        tilemap->setTile(mousepos, tt);
    }
}

void MyScene::update(float elapsed)
{
    (void)elapsed;
}

void MyScene::draw()
{
    SDL_SetRenderDrawColor(this->renderer, 32, 32, 192, 255);
    SDL_RenderClear(this->renderer);

    tilemap->draw();

    engine->setDrawForegroundColor(255, 255, 0, 192);
    engine->drawRect(mx * tileWidth, my * tileHeight, tileWidth, tileHeight);

    font->print(0, 0, "Hallo Welt!");
}
