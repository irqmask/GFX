#include <thread>

#include <SDL_image.h>

#include "Engine.h"
#include "GameExceptions.h"

// --- public members ---------------------------------------------------------

SDL_Renderer* g_renderer = nullptr;

Engine::Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight)
    : elapsed(0.0)
    , fps(0.0)
    , mouseX(-1.0)
    , mouseY(-1.0)
    , title(windowTitle)
    , w(windowWidth)
    , h(windowHeight)
    , scaleX(1.0)
    , scaleY(1.0)
    , window(nullptr)
    , current_scene(nullptr)
    , next_scene(nullptr)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    initializeGFX();
}


Engine::~Engine()
{
    deinitialzeGFX();
}


SDL_Renderer* Engine::getRenderer()
{
    return g_renderer;
}


int32_t Engine::getWindowWidth()
{
    return this->w;
}


int32_t Engine::getWindowHeight()
{
    return this->h;
}


void Engine::setScale(float scaleX, float scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    SDL_RenderSetScale(g_renderer, this->scaleX, this->scaleY);
}


void Engine::setNextScene(std::shared_ptr<Scene> scene)
{
    this->next_scene = scene;   
}


void Engine::run()
{
    while (this->next_scene != nullptr) {
        // TODO remove? std::cout << "Engine entering next scene" << std::endl;
        
        this->current_scene = this->next_scene;
        this->next_scene = nullptr;
        
        bool running = false;
        uint32_t ticks = 0, last_ticks = SDL_GetTicks();
        float one_second = 0.0;
        int frames = 0;
        do {
            ticks = SDL_GetTicks();
            this->elapsed = (ticks - last_ticks) / 1000.0f;

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_MOUSEMOTION) {
                    this->mouseX = (float)event.motion.x / this->scaleX;
                    this->mouseY = (float)event.motion.y / this->scaleY;
                }
                this->current_scene->onEvent(event);
            }
            this->current_scene->update(this->elapsed);
            this->current_scene->draw();

            SDL_RenderPresent(g_renderer);

            running = this->current_scene->isRunning();

            frames++;
            one_second += this->elapsed;
            if (one_second >= 1.0) {
                this->fps = frames / one_second;
                one_second = 0.0; 
                frames = 0;
                setTitle(title + " " + std::to_string(fps) + " fps");
            }
            last_ticks = ticks;
            std::this_thread::yield();
        } while (running);
    }
}


void Engine::setTitle(std::string title)
{
    SDL_SetWindowTitle(this->window, title.c_str());
}


void Engine::setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(g_renderer, r, g, b, a);
}


void Engine::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    SDL_RenderDrawLine(g_renderer, x1, y1, x2, y2);
}


void Engine::drawRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderDrawRect(g_renderer, &r);
}


void Engine::drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderFillRect(g_renderer, &r);
}


void Engine::drawCircle(int32_t x, int32_t y, int32_t r)
{
    float fy;
    float fx;

    float o = 0.0f;
    do {
        fx = sinf(o) * r;
        fy = - cosf(o) * r;
        SDL_RenderDrawPointF(g_renderer, fx + x, fy + y);
        SDL_RenderDrawPointF(g_renderer, -fx + x, fy + y);
        o += 0.2f;
    } while (o < PI);
}


void Engine::drawFilledCircle(int32_t x, int32_t y, int32_t r)
{
    int32_t rr = r*r;
    for (int32_t dy = -r; dy < r; dy++)
        for (int32_t dx = -r; dx < r; dx++)
            if (dx*dx + dy*dy <= rr)
                SDL_RenderDrawPoint(g_renderer, dx + x, dy + y);
}

// --- private members --------------------------------------------------------

void Engine::initializeGFX()
{
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    this->window = SDL_CreateWindow(title.c_str(),
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    this->w, this->h,
                                    SDL_WINDOW_SHOWN);
	if (this->window == nullptr) {
		throw OperationFailed(LOC, "SDL_CreateWindow() failed! %s", SDL_GetError());
	}
    
    g_renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (g_renderer == nullptr) {
		throw OperationFailed(LOC, "SDL_CreateRenderer() failed! %s", SDL_GetError());
	}
        
    SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
}


void Engine::deinitialzeGFX()
{
    //Clean up
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}
