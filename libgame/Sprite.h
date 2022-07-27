#pragma once

#include <map>
#include <memory>
#include <vector>

#include "Engine.h"
#include "Rect.h"


class ImageData
{
public:
    ImageData(std::string filename);
    ImageData(SDL_Surface *surface, SDL_Texture *texture, int32_t w, int32_t h);
    ~ImageData();

    int32_t getW() { return this->w; }
    int32_t getH() { return this->h; }

    std::shared_ptr<ImageData> createImageFromCutout(const Rect<int32_t> & rect);
    void draw(int32_t x, int32_t y);

private:
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    uint32_t pixelformat;
    int32_t w;
    int32_t h;
    int32_t index;

    ImageData();
    void loadFromFile(std::string file_path);
};

/// Frames are needed for animation of Sprites.
/// One frame represents one picture of a movement.
/// Frames are organized in FrameSets.
class Frame
{
public:
    Frame(std::shared_ptr<ImageData> image);
    ~Frame();

    void draw(int32_t x, int32_t y);

private:
    int32_t index;
    std::shared_ptr<ImageData> image;
};


/// Contains one or multiple Frames of a particular movement. 
/// A sprite usually has more than one FrameSet. E.g. a sprite has a frameset for
/// walking left, walking right, jumping left, jumping right etc.
class FrameSet : public std::vector<std::shared_ptr<Frame>>
{
public:
    void loadFromImage(std::string file_path, const std::vector<Rect<int32_t>> & frameRects);
};

/// A Sprite is the display of an actor in the game, e.g. player or enemy.
/// The Sprite capsules all data needed to display the actor.
class Sprite
{
public:
    /// ctor
    Sprite();
    /// dtor
    virtual ~Sprite();
    
    /// Set position of the sprite
    /// @param[in]  x   X-position
    /// @param[in]  y   Y-position
    void setDrawPos(int32_t x, int32_t y);
    /// Set position of the sprite
    /// @param[in]  v   2D vector
    void setDrawPos(Vec2d<int32_t> v);

    /// @returns current X-position of the sprite
    int32_t getX();
    /// @returns current Y-position of the sprite
    int32_t getY();

    const Vec2d<int32_t>& getDrawPos();
    const Rect<int32_t>& getDrawRect();

    void increaseFrame(float elapsed);

    void addFrameSet(uint16_t index, const std::shared_ptr<FrameSet> frame_set);
    void setFramePos(uint16_t pos);
    void setFrameSet(uint16_t set);

    virtual void update(float elapsed);
    virtual void draw();

    /// Calculate overlap between target and this sprite.
    /// @param[in]  target  Target rectangle to check
    /// @returns overlapped rectangle. Rectangle's size is zero when no overlap occurrs.
    bool isOverlapping(Rect<int32_t> & target);

    /// Calculate overlap between target and this sprite.
    /// @param[in]  target  Target sprite to check
    /// @returns overlapped rectangle. Rectangle's size is zero when no overlap occurrs.
    bool isOverlapping(Sprite & target);


protected:    
    std::map<uint16_t, std::shared_ptr<FrameSet>> frameSets;
    
private:
    /// draw position and size
    Rect<int32_t> rect;

    float frameTime;

    /// current displayed framme.
    float currentFramePos;
    /// current displayed FrameSet.
    uint16_t currentFrameSet;
};
