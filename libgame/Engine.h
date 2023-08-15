#pragma once

#include <memory>
#include <string>
#include <deque>

#include <SDL.h>

#include "EngineInterface.h"
#include "Scene.h"


class Engine : public EngineInterface
{
public:
    enum KeyCode
    {
        // must be kept in same order and values as SDL2 key scancodes which match USB scancode
        KEY_A = 4,
        KEY_B = 5,
        KEY_C = 6,
        KEY_D = 7,
        KEY_E = 8,
        KEY_F = 9,
        KEY_G = 10,
        KEY_H = 11,
        KEY_I = 12,
        KEY_J = 13,
        KEY_K = 14,
        KEY_L = 15,
        KEY_M = 16,
        KEY_N = 17,
        KEY_O = 18,
        KEY_P = 19,
        KEY_Q = 20,
        KEY_R = 21,
        KEY_S = 22,
        KEY_T = 23,
        KEY_U = 24,
        KEY_V = 25,
        KEY_W = 26,
        KEY_X = 27,
        KEY_Y = 28,
        KEY_Z = 29,

        KEY_1 = 30,
        KEY_2 = 31,
        KEY_3 = 32,
        KEY_4 = 33,
        KEY_5 = 34,
        KEY_6 = 35,
        KEY_7 = 36,
        KEY_8 = 37,
        KEY_9 = 38,
        KEY_0 = 39,

        KEY_RETURN = 40,
        KEY_ESCAPE = 41,
        KEY_BACKSPACE = 42,
        KEY_TAB = 43,
        KEY_SPACE = 44,

        KEY_MINUS = 45,
        KEY_EQUALS = 46,
        KEY_LEFTBRACKET = 47,
        KEY_RIGHTBRACKET = 48,
        KEY_BACKSLASH = 49,
        KEY_NONUSHASH = 50,
        KEY_SEMICOLON = 51,
        KEY_APOSTROPHE = 52,
        KEY_GRAVE = 53,
        KEY_COMMA = 54,
        KEY_PERIOD = 55,
        KEY_SLASH = 56,

        KEY_CAPSLOCK = 57,

        KEY_F1 = 58,
        KEY_F2 = 59,
        KEY_F3 = 60,
        KEY_F4 = 61,
        KEY_F5 = 62,
        KEY_F6 = 63,
        KEY_F7 = 64,
        KEY_F8 = 65,
        KEY_F9 = 66,
        KEY_F10 = 67,
        KEY_F11 = 68,
        KEY_F12 = 69,

        KEY_PRINTSCREEN = 70,
        KEY_SCROLLLOCK = 71,
        KEY_PAUSE = 72,
        KEY_INSERT = 73,
        KEY_HOME = 74,
        KEY_PAGEUP = 75,
        KEY_DELETE = 76,
        KEY_END = 77,
        KEY_PAGEDOWN = 78,
        KEY_RIGHT = 79,
        KEY_LEFT = 80,
        KEY_DOWN = 81,
        KEY_UP = 82,

        KEY_NUMLOCKCLEAR = 83,
        KEY_KP_DIVIDE = 84,
        KEY_KP_MULTIPLY = 85,
        KEY_KP_MINUS = 86,
        KEY_KP_PLUS = 87,
        KEY_KP_ENTER = 88,
        KEY_KP_1 = 89,
        KEY_KP_2 = 90,
        KEY_KP_3 = 91,
        KEY_KP_4 = 92,
        KEY_KP_5 = 93,
        KEY_KP_6 = 94,
        KEY_KP_7 = 95,
        KEY_KP_8 = 96,
        KEY_KP_9 = 97,
        KEY_KP_0 = 98,
        KEY_KP_PERIOD = 99,

        KEY_NONUSBACKSLASH = 100,
        KEY_LAST // not a key, just a mark for the end of the list
    };

    Engine(std::string windowTitle, int32_t windowWidth, int32_t windowHeight);
    virtual ~Engine();

    static constexpr float PI = 3.14159265358979323846f;
    static constexpr float DESIRED_FPS = 200.0f;

    float elapsed;
    float fps;

    float msX;
    float msY;
    bool keyPressed[KEY_LAST];
    static SDL_Renderer* getRenderer(); //FIXME remove need to have public access to SDL renderer
    int32_t windowWidth() const  override;
    int32_t windowHeight() const override;
    void setScale(float scaleX, float scaleY) override;
    int32_t getScaledWidth() const override;
    int32_t getScaledHeight() const override;

    void setRenderTarget(std::shared_ptr<ImageData> image) const override;

    std::shared_ptr<ImageData> createImage(int32_t width, int32_t height) const override;
    std::shared_ptr<ImageData> loadImage(const std::string &filename) const override;
    std::shared_ptr<ImageData> copyImage(std::shared_ptr<ImageData> srcImage, const Rect<int32_t>& cutout) const override;

    void clearBackground(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void setDrawForegroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void drawPixel(int32_t x, int32_t y) override;
    void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
    void drawRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawFilledRect(int32_t x, int32_t y, int32_t w, int32_t h) override;
    void drawCircle(int32_t x, int32_t y, int32_t r) override;
    void drawFilledCircle(int32_t x, int32_t y, int32_t r) override;
    void drawImage(int32_t x, int32_t y, std::shared_ptr<ImageData> image) override;
    void drawFrame(int32_t x, int32_t y, std::shared_ptr<Frame> frame) override;
    void drawSprite(std::shared_ptr<Sprite> sprite) override;

    bool keyIsPressed(int32_t key) const override;
    float mouseX() const override;
    float mouseY() const override;

    void setTitle(std::string title) override;

    void run();
    void runScene();
    void enqueueScene(std::shared_ptr<Scene> scene);
    void setSceneData(std::shared_ptr<SceneData> data);
    std::shared_ptr<SceneData> getSceneData() const;
    void quit();

    /// The onEvent() is called in a loop until all events since last call have bee processed
    /// Unless the other two functions update() and draw() which will be called only one per
    /// main-loop.
    virtual void onEvent(SDL_Event& event);

    virtual void update(float elapsed);
    virtual void draw();


private:
    std::string title;
    int32_t w;
    int32_t h;
    float scaleX;
    float scaleY;
    int32_t scaledWidth;
    int32_t scaledHeight;
    float ticks_per_frame = 1000.0f / DESIRED_FPS;
    SDL_Window *window;
    SDL_Renderer* renderer;
    std::deque<std::shared_ptr<Scene>> sceneStack;
    std::shared_ptr<SceneData> sceneData;
    std::shared_ptr<Scene> currentScene;
    bool keepRunning;

    void initializeGFX();
    void deinitialzeGFX();
    void processKeyEvents(SDL_Event& event);
    void processMouseEvents(SDL_Event& event);
};
