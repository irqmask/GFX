#include "Engine.h"

#include "Scene.h"

// --- public members ---------------------------------------------------------

Scene::Scene(std::shared_ptr<Engine> engine)
    : keepRunning(true)
{
    this->engine = engine;
}


Scene::~Scene()
{
}


int32_t Scene::windowWidth() const
{
    return engine->windowWidth();
}


int32_t Scene::windowHeight() const
{
    return engine->windowHeight();
}


void Scene::setScale(float scaleX, float scaleY)
{
    engine->setScale(scaleX, scaleY);
}


void Scene::clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    engine->clearBackground(r, g, b, a);
}


void Scene::setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    engine->setDrawForegroundColor(r, g, b, a);
}


void Scene::drawPixel(int32_t x, int32_t y)
{
    engine->drawPixel(x, y);
}


void Scene::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    engine->drawLine(x1, y1, x2, y2);
}


void Scene::drawRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    engine->drawRect(x, y, w, h);
}


void Scene::drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    engine->drawFilledRect(x, y, w, h);
}


void Scene::drawCircle(int32_t x, int32_t y, int32_t r)
{
    engine->drawCircle(x, y, r);
}


void Scene::drawFilledCircle(int32_t x, int32_t y, int32_t r)
{
    engine->drawFilledCircle(x, y, r);
}


float Scene::mouseX()
{
    return engine->mouseX();
}


float Scene::mouseY()
{
    return engine->mouseY();
}


void Scene::setTitle(std::string title)
{
    engine->setTitle(title);
}


void Scene::onEvent(SDL_Event &event)
{
    if (event.type == SDL_QUIT) {
        keepRunning = false;
    }
}
