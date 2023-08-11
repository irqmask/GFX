#include "Engine.h"

#include <thread>

#include <SDL_image.h>

#include "GameExceptions.h"
#include "ImageData.h"
#include "Sprite.h"

// --- public members ---------------------------------------------------------

SDL_Renderer* g_renderer = nullptr;

Engine::Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight)
    : elapsed(0.0)
    , fps(0.0)
    , msX(-1.0)
    , msY(-1.0)
    , title(windowTitle)
    , w(windowWidth)
    , h(windowHeight)
    , window(nullptr)
    , renderer(nullptr)
    , currentScene(nullptr)
    , keepRunning(true)
{
    setScale(1.0f, 1.0f);
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


int32_t Engine::windowWidth() const
{
    return this->w;
}


int32_t Engine::windowHeight() const
{
    return this->h;
}


void Engine::setScale(float scaleX, float scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaledWidth = this->w / this->scaleX;
    this->scaledHeight = this->h / this->scaleY;
    SDL_RenderSetScale(renderer, this->scaleX, this->scaleY);
}


int32_t Engine::getScaledWidth() const
{
    return this->scaledWidth;
}


int32_t Engine::getScaledHeight() const
{
    return this->scaledHeight;
}


void Engine::setTitle(std::string title)
{
    SDL_SetWindowTitle(this->window, title.c_str());
}


std::shared_ptr<ImageData> Engine::loadImage(const std::string& filename) const
{
    SDL_Surface *s = IMG_Load(filename.c_str());
    if (s == nullptr) {
        throw ResourceMissing(LOC, "Image file %s not found!", filename.c_str());
    }

    SDL_Texture *t = SDL_CreateTextureFromSurface(this->renderer, s);

    int w = 0, h = 0;
    int rc = SDL_QueryTexture(t, nullptr, nullptr, &w, &h);
    if (rc != 0) {
        throw OperationFailed(LOC, "Unable to query texture info: SDL Error %d %s", rc, SDL_GetError());
    }
    auto image = std::make_shared<ImageData>(w, h);
    image->surface = s;
    image->texture = t;
    return image;
}


std::shared_ptr<ImageData> Engine::copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const
{
    SDL_Rect source_rect = { cutout.pos.x, cutout.pos.y, cutout.size.x, cutout.size.y };

    SDL_Surface* s = SDL_CreateRGBSurface(0, cutout.size.x, cutout.size.y,
                                          srcImage->surface->format->BitsPerPixel,
                                          srcImage->surface->format->Rmask,
                                          srcImage->surface->format->Gmask,
                                          srcImage->surface->format->Bmask,
                                          srcImage->surface->format->Amask);

    SDL_BlitSurface(srcImage->surface, &source_rect, s, nullptr);
    SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);

    std::shared_ptr<ImageData> image_cutout = std::make_shared<ImageData>(cutout.size.x, cutout.size.y);
    image_cutout->surface = s;
    image_cutout->texture = t;

    return image_cutout;
}


void Engine::clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}


void Engine::setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}


void Engine::drawPixel(int32_t x, int32_t y)
{
    SDL_RenderDrawPoint(renderer, x, y);
}


void Engine::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


void Engine::drawRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderDrawRect(renderer, &r);
}


void Engine::drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    SDL_RenderFillRect(renderer, &r);
}


void Engine::drawCircle(int32_t x, int32_t y, int32_t r)
{
    float fy;
    float fx;

    float o = 0.0f;
    do {
        fx = sinf(o) * r;
        fy = - cosf(o) * r;
        SDL_RenderDrawPointF(renderer, fx + x, fy + y);
        SDL_RenderDrawPointF(renderer, -fx + x, fy + y);
        o += 0.2f;
    } while (o < PI);
}


void Engine::drawFilledCircle(int32_t x, int32_t y, int32_t r)
{
    int32_t rr = r*r;
    for (int32_t dy = -r; dy < r; dy++)
        for (int32_t dx = -r; dx < r; dx++)
            if (dx*dx + dy*dy <= rr)
                SDL_RenderDrawPoint(renderer, dx + x, dy + y);
}


void Engine::drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = image->width();
    r.h = image->height();
    SDL_RenderCopy(renderer, image->texture, NULL, &r);
}


void Engine::drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame)
{
    drawImage(x, y, frame->image());
}


void Engine::drawSprite(std::shared_ptr<Sprite> sprite)
{
    drawFrame(sprite->x(), sprite->y(), sprite->currentFrame());
}


float Engine::mouseX()
{
    return msX;
}


float Engine::mouseY()
{
    return msY;
}


void Engine::enqueueScene(std::shared_ptr<Scene> scene)
{
    this->sceneStack.push_back(scene);
}


void Engine::quit()
{
    this->keepRunning = false;
}

void Engine::onEvent(SDL_Event& event)
{
    (void)event;
}


void Engine::update(float elapsed)
{
    (void)elapsed;
}


void Engine::draw()
{
}


void Engine::run()
{
    bool running = true;
    uint32_t ticks = 0, last_ticks = SDL_GetTicks();
    float one_second = 0.0;
    int frames = 0;
    do {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEMOTION) {
                this->msX = (float)event.motion.x / this->scaleX;
                this->msY = (float)event.motion.y / this->scaleY;
            }
            this->onEvent(event);
        }
        this->update(this->elapsed);
        this->draw();

        SDL_RenderPresent(renderer);

        frames++;

        // free unnecessary CPU time
        ticks = SDL_GetTicks();
        uint32_t elapsed_ticks = ticks - last_ticks;
        if (elapsed_ticks < ticks_per_frame) {
            SDL_Delay((uint32_t)ticks_per_frame - elapsed_ticks);
        }
        else {
            SDL_Delay(0);
        }

        // calculate elapsed again, after sleeping
        ticks = SDL_GetTicks();
        this->elapsed = (ticks - last_ticks) / 1000.0f;
        last_ticks = ticks;

        one_second += this->elapsed;
        if (one_second >= 1.0) {
            this->fps = frames / one_second;
            one_second = 0.0;
            frames = 0;
            setTitle(title + " " + std::to_string(fps) + " fps");
        }
    } while (running);
}


void Engine::runScene()
{
    while (this->sceneStack.size() > 0 && keepRunning) {
        // TODO remove? std::cout << "Engine entering next scene" << std::endl;

        this->currentScene = this->sceneStack.front();
        this->sceneStack.pop_front();

        bool running = false;
        uint32_t ticks = 0, last_ticks = SDL_GetTicks();
        float one_second = 0.0;
        int frames = 0;
        do {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_MOUSEMOTION) {
                    this->msX = (float)event.motion.x / this->scaleX;
                    this->msY = (float)event.motion.y / this->scaleY;
                }
                this->currentScene->onEvent(event);
            }
            this->currentScene->update(this->elapsed);
            this->currentScene->draw();

            SDL_RenderPresent(renderer);

            running = this->currentScene->isRunning();

            frames++;

            // free unnecessary CPU time
            ticks = SDL_GetTicks();
            uint32_t elapsed_ticks = ticks - last_ticks;
            if (elapsed_ticks < ticks_per_frame) {
                SDL_Delay((uint32_t)ticks_per_frame - elapsed_ticks);
            }
            else {
                SDL_Delay(0);
            }

            // calculate elapsed again, after sleeping
            ticks = SDL_GetTicks();
            this->elapsed = (ticks - last_ticks) / 1000.0f;
            last_ticks = ticks;

            one_second += this->elapsed;
            if (one_second >= 1.0) {
                this->fps = frames / one_second;
                one_second = 0.0;
                frames = 0;
                setTitle(title + " " + std::to_string(fps) + " fps");
            }
        } while (running);
    }
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
    
    renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (renderer == nullptr) {
		throw OperationFailed(LOC, "SDL_CreateRenderer() failed! %s", SDL_GetError());
	}
    g_renderer = renderer; //FIXME remove static pointer to renderer
        
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
