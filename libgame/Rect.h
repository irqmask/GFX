#pragma once

#include <cstdint>

template <class T>
class Vec2d
{
public:
    Vec2d() : x(static_cast<T>(0)), y(static_cast<T>(0)) {};
    Vec2d(T x, T y) : x(x), y(y) {};
    T x;
    T y;

    Vec2d<T>& operator+=(const Vec2d<T>& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vec2d<T>& operator-=(const Vec2d<T>& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vec2d<T>& operator*=(float val) {
        this->x *= val;
        this->y *= val;
        return *this;
    }
};

typedef Vec2d<int32_t> Vec2I32;
typedef Vec2d<float> Vec2Flt;

template <class T>
class Rect
{
public:
    Rect()
    {
    };

    Rect(T x, T y, T w, T h)
        : pos(x, y)
        , size(w, h)
    {
    };

    virtual ~Rect()
    {
    };

    Vec2d<T> pos;
    Vec2d<T> size;

    bool inRect(const Vec2d<T> & p)
    {
        return (p.x >= this->pos.x && p.y >= this->pos.y && p.x < (this->pos.x + this->size.x) && p.y < (this->pos.y + this->size.y));
    }

    bool isOverlapping(const Rect<T> & r)
    {
        return (r.pos.x < this->pos.x + this->size.x && r.pos.x + r.size.x < this->pos.x &&
                r.pos.y < this->pos.y + this->size.y && r.pos.y + r.size.y < this->pos.y);
    }
};
