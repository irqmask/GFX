#include "MyScene.h"

#include <array>
#include <iostream>
#include <sstream>

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


const std::string level1Str =
    "........................"
    "...ss............ssss..."
    "...ssss..........ssss..."
    "....ssssss.......ssss..."
    ".....sssss.............."
    "....sss................."
    "....sssssss.......ss...."
    ".....ssssss.......ss...."
    "........ssssssss........"
    ".......ssssssssss......."
    ".......ssssssssss......."
    "........ssssssssss......"
    "........sssssssss......."
    "......ssss...sss........"
    ".....ssss..............."
    ".....ssss....sss........"
    ".....ssss...ssss........"
    "....ssss...ssss........."
    "....ssssssssss.........."
    ".....sssssssss.........."
    "........sssssss........."
    "........sssssss........."
    "........sssssss........."
    "........................";


uint32_t TilemapDemo::level1[TilemapDemo::levelWidth * TilemapDemo::levelHeight];

enum {
    CENTRAL,
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST,
    ICENTRAL,
    INORTH,
    INORTHEAST,
    IEAST,
    ISOUTHEAST,
    ISOUTH,
    ISOUTHWEST,
    IWEST,
    INORTHWEST
};

std::array<TileMap::tiletype_t,18> sand_water_tiles = { 10, 2, 3, 11, 19, 18, 17, 9, 1, 13, 5, 6, 14, 22, 21, 20, 12, 4 };
//std::array<TileMap::tiletype_t,9> water_sand_tiles = { 13, 5, 6, 14, 22, 21, 20, 12, 4 };

// sand-water tiles
// NW=1  N=2  NE=3
//  W=9  M=10  E=11
// SW=17 S=18 SE=19
TileMap::tiletype_t TilemapDemo::evalTileType(const std::string &str, char pri, char sec, int32_t x, int32_t y, const std::array<TileMap::tiletype_t,18> &tiletypes)
{
    auto getChar = [&](const std::string &str, int32_t x, int32_t y) {
        char chr = 255;
        if (x >= 0 && y >= 0 && x < levelWidth && y < levelHeight)
            chr = str[y * levelWidth + x];
        return chr;
    };

    if (getChar(str, x-1, y) == sec && getChar(str, x, y-1) == sec && getChar(str, x+1, y) == pri && getChar(str, x, y+1) == pri) {
        return tiletypes[NORTHWEST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x, y-1) == sec && getChar(str, x+1, y) == pri && getChar(str, x+1, y+1) == pri) {
        return tiletypes[NORTH];
    }
    else if (getChar(str, x+1, y) == sec && getChar(str, x, y-1) == sec && getChar(str, x-1, y) == pri && getChar(str, x, y+1) == pri) {
        return tiletypes[NORTHEAST];
    }
    else if (getChar(str, x-1, y) == sec && getChar(str, x, y+1) == sec && getChar(str, x+1, y) == pri && getChar(str, x, y-1) == pri) {
        return tiletypes[SOUTHWEST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x, y+1) == sec && getChar(str, x+1, y) == pri && getChar(str, x, y-1) == pri) {
        return tiletypes[SOUTH];
    }
    else if (getChar(str, x, y+1) == sec && getChar(str, x+1, y) == sec && getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri) {
        return tiletypes[SOUTHEAST];
    }
    else if (getChar(str, x-1, y) == sec && getChar(str, x+1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x, y+1) == pri) {
        return tiletypes[WEST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x+1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x, y+1) == pri &&
             getChar(str, x-1, y-1) == pri && getChar(str, x+1, y-1) == pri && getChar(str, x+1, y+1) == pri && getChar(str, x-1, y+1) == pri) {
        return tiletypes[CENTRAL];
    }
    else if (getChar(str, x+1, y) == sec && getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x, y+1) == pri) {
        return tiletypes[EAST];
    }



    else if (getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x+1, y) == pri && getChar(str, x, y+1) == pri && getChar(str, x+1, y+1) == sec) {
        return tiletypes[INORTHWEST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x+1, y) == pri && getChar(str, x, y+1) == pri && getChar(str, x-1, y+1) == sec) {
        return tiletypes[INORTHEAST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x+1, y) == pri && getChar(str, x, y+1) == pri && getChar(str, x+1, y-1) == sec) {
        return tiletypes[ISOUTHWEST];
    }
    else if (getChar(str, x-1, y) == pri && getChar(str, x, y-1) == pri && getChar(str, x+1, y) == pri && getChar(str, x, y+1) == pri && getChar(str, x-1, y-1) == sec) {
        return tiletypes[ISOUTHEAST];
    }
    else {
        return 0;
    }
}



void TilemapDemo::mapFromString(TileMap::tiletype_t map[], const std::string &str)
{
    auto xy2idx = [&](int32_t x, int32_t y){ return y * levelWidth + x; };

    for (int32_t y=0; y < levelHeight; y++) {
        for (int32_t x=0; x < levelWidth; x++) {
            switch (str[xy2idx(x, y)]) {
            case '.':
                map[xy2idx(x, y)] = 0;
                break;
            case 's':
                map[xy2idx(x, y)] = evalTileType(str, 's', '.', x, y, sand_water_tiles);
                break;
            default:
                map[xy2idx(x, y)] = 8;
                break;
            }

        }
    }
}


TilemapDemo::TilemapDemo(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , mx(0)
    , my(0)
{
    std::cout << __FUNCTION__ << std::endl;
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    auto image = engine->loadImage(assetPath.plusFilename("tiles_30x30_test.png"));

    mapFromString(level1, level1Str);

    tilemap = std::shared_ptr<TileMap>(new TileMap(engine, image, tileWidth, tileHeight));
    tilemap->load(level0, levelWidth, levelHeight, -1);
    //tilemap->load(level1, levelWidth, levelHeight);
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

    std::stringstream ss;
    ss << "camPos x: " << camPos.x << " y: " << camPos.y;

    font->print(0, 0, "tilemap");
    //font->print(0, 16, ss.str());
}
