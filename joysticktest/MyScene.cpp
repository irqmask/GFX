#include "MyScene.h"

#include <iostream>

#include "Path.h"

MyScene::MyScene(std::shared_ptr<Engine> engine)
    : Scene(engine)
{
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));
    SDL_SetRenderDrawColor(renderer, 0, 0, 64, 255);
    detectJoysticks();
}

MyScene::~MyScene()
{
    std::cout << __FUNCTION__ << std::endl;
    font.reset();
}

void MyScene::detectJoysticks()
{
    openedJoysticks.clear();
    int32_t num_joysticks = SDL_NumJoysticks();
    for (int32_t i=0; i<num_joysticks; i++) {
        std::shared_ptr<Joystick> j = std::make_shared<Joystick>(i);
        openedJoysticks.push_back(j);
    }
}

void MyScene::printJoystickInfo(int32_t x, int32_t y, int32_t joyidx)
{
    engine->setDrawForegroundColor(200, 255, 200, 255);
    engine->drawLine(x, y + 10, x, y + 50);
    font->print(x, y + 10, "joystick " + std::to_string(joyidx));
    font->print(x, y + 20, "  numAxes    " + std::to_string(openedJoysticks.at(joyidx)->numAxes()));
    font->print(x, y + 30, "  numButtons " + std::to_string(openedJoysticks.at(joyidx)->numButtons()));
    font->print(x, y + 40, "  numBalls   " + std::to_string(openedJoysticks.at(joyidx)->numBalls()));
}

void MyScene::drawJoystickStateDigital(int32_t x, int32_t y, int32_t joyidx)
{
    engine->setDrawForegroundColor(255, 200, 200, 255);
    std::shared_ptr<Joystick> j = openedJoysticks.at(joyidx);
    // up
    engine->drawRect(x - 3, y - 15, 6, 10);
    // down
    engine->drawRect(x - 3, y + 5, 6, 10);
    // left
    engine->drawRect(x - 15, y - 3, 10, 6);
    // right
    engine->drawRect(x + 5, y - 3, 10, 6);

    if (j->isUp()) {
        engine->drawFilledRect(x - 2, y - 14, 4, 8);
    }
    if (j->isDown()) {
        engine->drawFilledRect(x - 2, y + 6, 4, 8);
    }
    if (j->isLeft()) {
        engine->drawFilledRect(x - 14, y - 2, 8, 4);
    }
    if (j->isRight()) {
        engine->drawFilledRect(x + 6, y - 2, 8, 4);
    }
}

void MyScene::drawJoystickButtonState(int32_t x, int32_t y, int32_t joyidx)
{
    std::shared_ptr<Joystick> j = openedJoysticks.at(joyidx);
    for (int32_t i=0; i<j->numButtons(); i++) {
        engine->drawCircle(x + i * 12, y, 5);
        if (j->isButton(i)) {
            engine->drawFilledCircle(x + i * 12, y, 4);
        }
    }
}

void MyScene::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_F5:
            detectJoysticks();
            break;

        default:
            break;
        }
    }
}

void MyScene::update(float elapsed)
{
    (void)elapsed;
}

void MyScene::draw()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 64, 255);
    SDL_RenderClear(this->renderer);

    int32_t nj = static_cast<int32_t>(openedJoysticks.size());
    std::string text = "Number of joysticks " + std::to_string(nj);
    font->print(10, 10, text);
    for (int i=0; i<nj; i++) {
        printJoystickInfo(10, 20 + i * 60, i);
        drawJoystickStateDigital(200, 20 + i * 60 + 35, i);
        drawJoystickButtonState(250, 20 + i * 60 + 35, i);
    }

}
