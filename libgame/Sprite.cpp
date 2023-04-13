#include <cassert>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "GameExceptions.h"
#include "Sprite.h"


// --- ImageData --------------------------------------------------------------

static int32_t g_image_counter = 0;

ImageData::ImageData()
    : surface(nullptr)
    , texture(nullptr)
    , w(0)
    , h(0)
{
    renderer = Engine::getRenderer();
    this->index = g_image_counter++;
}


ImageData::ImageData(std::string filename) 
    : ImageData()
{
    loadFromFile(filename);
}


ImageData::ImageData(SDL_Surface *surface, SDL_Texture *texture, int32_t w, int32_t h)
    : ImageData()
{
    this->surface = surface;
    this->texture = texture;
    this->w = w;
    this->h = h;
}


ImageData::~ImageData()
{
    if (this->surface != nullptr) {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}


std::shared_ptr<ImageData> ImageData::createImageFromCutout(const Rect<int32_t> & rect)
{
    SDL_Rect source_rect = { rect.pos.x, rect.pos.y, rect.size.x, rect.size.y };

    SDL_Surface *s = SDL_CreateRGBSurface(0, rect.size.x, rect.size.y,
                                          this->surface->format->BitsPerPixel,
                                          this->surface->format->Rmask, this->surface->format->Gmask,
                                          this->surface->format->Bmask, this->surface->format->Amask);

    SDL_BlitSurface(this->surface, &source_rect, s, nullptr);
    SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);

    std::shared_ptr<ImageData> image_cutout = std::make_shared<ImageData>(s, t, rect.size.x, rect.size.y);

    return image_cutout;
}


void ImageData::draw(int32_t x, int32_t y)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = this->w;
    r.h = this->h;
    SDL_RenderCopy(this->renderer, this->texture, NULL, &r);
}


void ImageData::loadFromFile(std::string filename)
{
    this->surface = IMG_Load(filename.c_str());
    if (this->surface == nullptr) {
        throw ResourceMissing(LOC, "Image file %s not found!", filename.c_str());
    }

    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    int rc = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->w, &this->h);
    if (rc != 0) {
        throw OperationFailed(LOC, "Unable to query texture info: SDL Error %d %s", rc, SDL_GetError());
    }
}

// --- Frame ------------------------------------------------------------------

static int32_t g_frame_counter = 0;

Frame::Frame(std::shared_ptr<ImageData> image)
{
    this->image = image;
    this->index = g_frame_counter++;
}


Frame::~Frame()
{
    this->image.reset();
}


void Frame::draw(int32_t x, int32_t y)
{
    image->draw(x, y);
}

// --- FrameSet ---------------------------------------------------------------

void FrameSet::loadFromImage(std::shared_ptr<ImageData> image, const std::vector<Rect<int32_t>> & frame_rects)
{   
    for (const auto & r : frame_rects) {
        auto frame = std::make_shared<Frame>(image->createImageFromCutout(r));
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


int32_t Sprite::getX()
{
    return this->rect.pos.x;
}


int32_t Sprite::getY()
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


void Sprite::update(float elapsed)
{
    (void)elapsed;
}


void Sprite::draw()
{
    std::shared_ptr<FrameSet> fs = this->frameSets[this->currentFrameSet];
    fs->at((uint16_t)this->currentFramePos)->draw(rect.pos.x, rect.pos.y);
}


bool Sprite::isOverlapping(Rect<int32_t> &target)
{
    return this->rect.isOverlapping(target);
}


bool Sprite::isOverlapping(Sprite &target)
{
    return this->rect.isOverlapping(target.getDrawRect());
}
