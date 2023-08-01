#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Dirt.h"

// --- public members ---------------------------------------------------------

Dirt::Dirt()
    : Engine("dirt", 320, 240)
{
    std::cout << __FUNCTION__ << std::endl;
    this->data = (bool*)calloc((size_t)(windowWidth() * windowHeight()), sizeof(bool));
    srand((int)std::time(0));
}


Dirt::~Dirt()
{
    std::cout << __FUNCTION__ << std::endl;
    if (this->data != nullptr) {
        free(this->data);
        this->data = nullptr;
    }
}

void Dirt::onEvent(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            putBlob(event.button.x, event.button.y, randInt(15, 30));
        }
    }
}

void Dirt::update(float elapsed)
{
    (void)elapsed;
}

void Dirt::draw()
{
    bool particles_moved;
    
    clearBackground(255,220,0,0);
    
    particles_moved = advanceAndDrawLines();
    if (!particles_moved) {
        putBlob(randInt(30, windowWidth() - 30),
                randInt(30, 100),
                randInt(15, 30));
    }
}

// --- private members --------------------------------------------------------

uint8_t Dirt::randUInt8(uint8_t s, uint8_t e)
{
    double val;

    assert(e > s);

    val = rand();
    val *= (e - s);
    val /= RAND_MAX;
    val = val + s + 0.5;
    return (uint8_t)(val);
}

int Dirt::randInt(int s, int e)
{
    double val;
    
    val = rand();
    val *= (e-s);
    val /= RAND_MAX;
    val = val + s + 0.5;
    return (int)(val);
}

void Dirt::putBlob(int cx, int cy, int r)
{
    int32_t xx, yy;

    int32_t w = windowWidth();
    int32_t h = windowHeight();
    
    std::cout << "putBlob " << cx << " " << cy << " " << r << std::endl;
    for (int x=-r/2; x<r/2; x++) {
        for (int y=-r/2; y<r/2; y++) {
            if (x*x + y*y < r*r/4) {
               xx = x + cx; yy = cy + y;
               if (xx >= 0 && xx < w && yy >= 0 && yy < h) {
                   int offset = yy*w + xx;
                   data[offset] = !data[offset];
               }
            }
        }
    }
}

void Dirt::putPixel(int x, int y, bool pixel)
{
    if (pixel)
        setDrawForegroundColor(x / 2 % 255, 0, 240, 255);
    else
        setDrawForegroundColor(255, 240, 0, 255);

    drawPixel(x, y);
}

bool Dirt::advanceAndDrawLines()
{    
    bool particles_moved = false;
    
    int32_t w = windowWidth();
    int32_t h = windowHeight();

    if (h < 2) return false;
    
    for (int y = h - 1; y > 0; y--) {      
        bool* current_line = &this->data[y*w];
        // line above
        bool* above_line = &this->data[(y-1)*w];
        for (int x = 0; x < w; x++) {
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
    int32_t w = windowWidth();
    int32_t h = windowHeight();

    if (x>=0 && x<w && y>=0 && y<h) {
        int offset = y*w + x;
        this->data[offset] = existing;
    }
}*/
