#include "Sprite.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "Engine.h"
#include "GameExceptions.h"
#include "ImageData.h"


// --- Frame ------------------------------------------------------------------

static int32_t g_frame_counter = 0;

Frame::Frame(std::shared_ptr<ImageData> image)
{
    this->img = image;
    this->index = g_frame_counter++;
}


Frame::~Frame()
{
    this->img.reset();
}


std::shared_ptr<ImageData> Frame::image()
{
    return this->img;
}

// --- FrameSet ---------------------------------------------------------------

void FrameSet::loadFromImage(std::shared_ptr<Engine> engine, std::shared_ptr<ImageData> image, const std::vector<Rect<int32_t>> & frame_rects)
{   
    for (const auto & r : frame_rects) {
        auto frame = std::make_shared<Frame>(engine->copyImage(image, r));
        this->push_back(frame);
    }
}

// --- Sprite -----------------------------------------------------------------

Sprite::Sprite()
    : rect(0, 0, 0, 0)
    , frameTime(0.25)
    , currentFramePos(0)
    , currentFrameSet(0)

{
}


Sprite::~Sprite()
{
}


void Sprite::setDrawPos(int32_t x, int32_t y)
{
    this->rect.pos.x = x;
    this->rect.pos.y = y;
}


void Sprite::setDrawPos(Vec2d<int32_t> v)
{
    this->rect.pos = v;
}


int32_t Sprite::x()
{
    return this->rect.pos.x;
}


int32_t Sprite::y()
{
    return this->rect.pos.y;
}


const Vec2d<int32_t> &Sprite::getDrawPos()
{
    return this->rect.pos;
}


const Rect<int32_t> &Sprite::getDrawRect()
{
    return this->rect;
}


void Sprite::increaseFrame(float elapsed)
{
    this->currentFramePos += elapsed / this->frameTime;
    if (this->currentFramePos >= this->frameSets[this->currentFrameSet]->size()) {
        this->currentFramePos = 0;
    }
}


void Sprite::addFrameSet(uint16_t index, std::shared_ptr<FrameSet> frame_set)
{
    this->frameSets[index] = frame_set;
}


void Sprite::setFramePos(uint16_t pos)
{
    this->currentFramePos = pos;
    if (this->currentFramePos >= this->frameSets[this->currentFrameSet]->size()) {
        this->currentFramePos = 0;
    }
}


void Sprite::setFrameSet(uint16_t set)
{
    this->currentFrameSet = set;
}


std::shared_ptr<Frame> Sprite::currentFrame()
{
    int32_t pos = (int32_t)currentFramePos;
    return this->frameSets[currentFrameSet]->at(pos);
}


void Sprite::update(float elapsed)
{
    (void)elapsed;
}


bool Sprite::isOverlapping(Rect<int32_t> &target)
{
    return this->rect.isOverlapping(target);
}


bool Sprite::isOverlapping(Sprite &target)
{
    return this->rect.isOverlapping(target.getDrawRect());
}
