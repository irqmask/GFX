#pragma once

#include "Scene.h"

class DirtScene : public Scene
{
public:
    DirtScene(std::shared_ptr<Engine> renderer);
    virtual ~DirtScene();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;
    
private:  
    bool* data;
    
    int randInt(int s, int e);
    uint8_t randUInt8(uint8_t s, uint8_t e);
    void putBlob(int cx, int cy, int r);
    void putPixel(int x, int y, bool pixel);
    bool advanceAndDrawLines();
};
