#include "Engine.h"

#include "Scene.h"

// --- public members ---------------------------------------------------------

Scene::Scene(std::shared_ptr<Engine> engine)
    : keepRunning(true)
{
    this->engine = engine;
    this->renderer = this->engine->getRenderer();
    this->w = this->engine->getWindowWidth();
    this->h = this->engine->getWindowHeight();
}


Scene::~Scene()
{
}


void Scene::onEvent(SDL_Event &event)
{
    if (event.type == SDL_QUIT) {
        keepRunning = false;
    }
}
