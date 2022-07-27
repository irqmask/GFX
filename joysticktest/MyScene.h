#pragma once

#include <memory>

#include "BitmapFont.h"
#include "GameExceptions.h"
#include "Scene.h"

class Joystick {
public:
    Joystick(int32_t idx)
        : i(-1)
        , j(nullptr)
    {
        j = SDL_JoystickOpen(idx);
        if (j == nullptr) throw ResourceMissing(LOC, "Joystick with index %d not opened!", idx);
        i = idx;
    }

    ~Joystick()
    {
        if (j != nullptr) {
            SDL_JoystickClose(j);
        }
    }

    void update()
    {
        SDL_JoystickUpdate();
    }

    int32_t numAxes()
    {
        return SDL_JoystickNumAxes(j);
    }

    int32_t numButtons()
    {
        return SDL_JoystickNumButtons(j);
    }

    int32_t numBalls()
    {
        return SDL_JoystickNumBalls(j);
    }

    bool isUp()
    {
        return SDL_JoystickGetAxis(j, 1) < MIN_UP;
    }

    bool isDown()
    {
        return SDL_JoystickGetAxis(j, 1) > MIN_DOWN;
    }

    bool isLeft()
    {
        return SDL_JoystickGetAxis(j, 0) < MIN_LEFT;
    }

    bool isRight()
    {
        return SDL_JoystickGetAxis(j, 0) > MIN_RIGHT;
    }

    bool isButton(int32_t btn)
    {
        return SDL_JoystickGetButton(j, btn) == 1;
    }

private:
    int32_t i;
    SDL_Joystick* j;
    std::string name;

    static constexpr int32_t MIN_UP = -20;
    static constexpr int32_t MIN_DOWN = 20;
    static constexpr int32_t MIN_LEFT = -20;
    static constexpr int32_t MIN_RIGHT = 20;

};

class MyScene : public Scene
{
public:
    MyScene(std::shared_ptr<Engine> engine);
    virtual ~MyScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

    void detectJoysticks();
    void printJoystickInfo(int32_t x, int32_t y, int32_t joyidx);
    void drawJoystickStateDigital(int32_t x, int32_t y, int32_t joyidx);
    void drawJoystickButtonState(int32_t x, int32_t y, int32_t joyidx);

private:
    std::shared_ptr<BitmapFont> font;
    std::vector<std::shared_ptr<Joystick>> openedJoysticks;
};
