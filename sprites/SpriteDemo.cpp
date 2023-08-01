#include "SpriteDemo.h"

#include <iostream>

#include "Engine.h"
#include "Path.h"

SpriteDemo::SpriteDemo(std::shared_ptr<Engine> engine)
    : Scene(engine)
{
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    auto image = engine->loadImage(assetPath.plusFilename("spritexb-4248.png"));
    std::vector<Rect<int32_t>> spriteFrames1 = {{  0,   0, 32, 48},
                                                { 32,   0, 32, 48},
                                                { 64,   0, 32, 48},
                                                { 96,   0, 32, 48}};
    std::vector<Rect<int32_t>> spriteFrames2 = {{  0,  48, 32, 48},
                                                { 32,  48, 32, 48},
                                                { 64,  48, 32, 48},
                                                { 96,  48, 32, 48}};
    std::vector<Rect<int32_t>> spriteFrames3 = {{  0,  96, 32, 48},
                                                { 32,  96, 32, 48},
                                                { 64,  96, 32, 48},
                                                { 96,  96, 32, 48}};
    std::vector<Rect<int32_t>> spriteFrames4 = {{  0, 144, 32, 48},
                                                { 32, 144, 32, 48},
                                                { 64, 144, 32, 48},
                                                { 96, 144, 32, 48}};
    std::shared_ptr<FrameSet> fs1 = std::make_shared<FrameSet>();
    fs1->loadFromImage(engine, image, spriteFrames1);
    std::shared_ptr<FrameSet> fs2 = std::make_shared<FrameSet>();
    fs2->loadFromImage(engine, image, spriteFrames2);
    std::shared_ptr<FrameSet> fs3 = std::make_shared<FrameSet>();
    fs3->loadFromImage(engine, image, spriteFrames3);
    std::shared_ptr<FrameSet> fs4 = std::make_shared<FrameSet>();
    fs4->loadFromImage(engine, image, spriteFrames4);

    this->sprite = std::make_shared<Sprite>();
    this->sprite->addFrameSet(0, fs1);
    this->sprite->addFrameSet(1, fs2);
    this->sprite->addFrameSet(2, fs3);
    this->sprite->addFrameSet(3, fs4);
    this->sprite->setDrawPos(1, 1);
    setDrawForegroundColor(255, 0, 0, 255);
}

SpriteDemo::~SpriteDemo()
{
    std::cout << __FUNCTION__ << std::endl;
    sprite.reset();
}

void SpriteDemo::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_DOWN:
            sprite->setFrameSet(0);
            break;
        case SDLK_UP:
            sprite->setFrameSet(3);
            break;
        case SDLK_LEFT:
            sprite->setFrameSet(1);
            break;
        case SDLK_RIGHT:
            sprite->setFrameSet(2);
            break;
        default:
            break;
        }
    }
}

void SpriteDemo::update(float elapsed)
{
    sprite->increaseFrame(elapsed);
}

void SpriteDemo::draw()
{
    clearBackground(255, 0, 0, 255);
    drawSprite(sprite);
}
