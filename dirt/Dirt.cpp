#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Dirt.h"

// --- public members ---------------------------------------------------------

DirtScene::DirtScene(std::shared_ptr<Engine> engine) : Scene(engine)
{
    std::cout << __FUNCTION__ << std::endl;
    this->data = (bool*)calloc((size_t)(this->w * this->h), sizeof(bool));
    srand((int)std::time(0));
}


DirtScene::~DirtScene()
{
    std::cout << __FUNCTION__ << std::endl;
    if (this->data != nullptr) {
        free(this->data);
        this->data = nullptr;
    }
}

void DirtScene::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            putBlob(event.button.x, event.button.y, randInt(15, 30));
        }
    }
}

void DirtScene::update(float elapsed)
{
}

void DirtScene::draw()
{
    bool particles_moved;
    
    SDL_SetRenderDrawColor(this->renderer, 255,220,0,0);
    SDL_RenderClear(this->renderer);
    
    
    particles_moved = advanceAndDrawLines();
    if (!particles_moved) {
        putBlob(randInt(30, this->w-30),
                randInt(30, 100),
                randInt(15, 30));
    }
}

// --- private members --------------------------------------------------------

uint8_t DirtScene::randUInt8(uint8_t s, uint8_t e)
{
    double val;

    assert(e > s);

    val = rand();
    val *= (e - s);
    val /= RAND_MAX;
    val = val + s + 0.5;
    return (uint8_t)(val);
}

int DirtScene::randInt(int s, int e)
{
    double val;
    
    val = rand();
    val *= (e-s);
    val /= RAND_MAX;
    val = val + s + 0.5;
    return (int)(val);
}

void DirtScene::putBlob(int cx, int cy, int r)
{
    int xx, yy;
    
    std::cout << "putBlob " << cx << " " << cy << " " << r << std::endl;
    for (int x=-r/2; x<r/2; x++) {
        for (int y=-r/2; y<r/2; y++) {
            if (x*x + y*y < r*r/4) {
               xx = x + cx; yy = cy + y;
               if (xx >= 0 && xx < this->w && yy >= 0 && yy < this->h) {
                   int offset = yy*this->w + xx;
                   data[offset] = !data[offset];
               }
            }
        }
    }
}

void DirtScene::putPixel(int x, int y, bool pixel)
{
    if (pixel)
        SDL_SetRenderDrawColor(renderer, x/2 % 255, 0, 240, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 240, 0, 255);
    
    SDL_RenderDrawPoint(this->renderer, x, y);
}

bool DirtScene::advanceAndDrawLines()
{    
    bool particles_moved = false;
    
    if (this->h < 2) return false;
    
    for (int y = this->h - 1; y > 0; y--) {      
        bool* current_line = &this->data[y*this->w];
        // line above
        bool* above_line = &this->data[(y-1)*this->w];
        for (int x = 0; x < this->w; x++) {
            if (!current_line[x] && above_line[x]) {
                current_line[x] = true;
                above_line[x] = false;
                particles_moved = true;
            }
            putPixel(x, y, current_line[x]);           
        }
    }
    return particles_moved;
}

/*void CDirtScene::putParticle(int x, int y, bool existing)
{
    if (x>=0 && x<this->w && y>=0 && y<this->h) {
        int offset = y*this->w + x;
        this->data[offset] = existing;
    }
}*/
