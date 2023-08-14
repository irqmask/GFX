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


std::shared_ptr<SceneData> Scene::getData() const
{
    return engine->getSceneData();
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


int32_t Scene::getScaledWidth() const
{
    return engine->getScaledWidth();
}


int32_t Scene::getScaledHeight() const
{
    return engine->getScaledHeight();
}


void Scene::setRenderTarget(std::shared_ptr<ImageData> image) const
{
    engine->setRenderTarget(image);
}


std::shared_ptr<ImageData> Scene::createImage(int32_t width, int32_t height) const
{
    return engine->createImage(width, height);
}


std::shared_ptr<ImageData> Scene::loadImage(const std::string& filename) const
{
    return engine->loadImage(filename);
}


std::shared_ptr<ImageData> Scene::copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const
{
    return engine->copyImage(srcImage, cutout);
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


void Scene::drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image)
{
    engine->drawImage(x, y, image);
}


void Scene::drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame)
{
    engine->drawFrame(x, y, frame);
}


void Scene::drawSprite(std::shared_ptr<Sprite> sprite)
{
    engine->drawSprite(sprite);
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
        engine->quit();
    }
}
