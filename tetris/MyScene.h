#pragma once

#include <memory>

#include "BitmapFont.h"
#include "Scene.h"
#include "Sprite.h"

typedef std::vector<Vec2d<int32_t>> Tetromino;
typedef std::vector<Tetromino> TetrominoSprite;

class SpriteDemo : public Scene
{
public:
    SpriteDemo(std::shared_ptr<Engine> engine);
    virtual ~SpriteDemo();

    virtual void onEvent(SDL_Event& event) override;
    virtual void update(float elapsed) override;
    virtual void draw() override;

    static constexpr int32_t BLOCK_WIDTH = 25;
    static constexpr int32_t BLOCK_HEIGHT = 25;
    static constexpr int32_t FIELD_WIDTH = 10;
    static constexpr int32_t FIELD_HEIGHT = 20;
    static constexpr int32_t FIELD_OFFSET_X = 10;
    static constexpr int32_t FIELD_OFFSET_Y = 10;

    static constexpr int32_t PREVIEW_BOX_OFFSET_X = 2 * FIELD_OFFSET_X + BLOCK_WIDTH * FIELD_WIDTH;
    static constexpr int32_t PREVIEW_BOX_OFFSET_Y = FIELD_OFFSET_Y;
    static constexpr int32_t PREVIEW_BOX_WIDTH = 5 * BLOCK_WIDTH;
    static constexpr int32_t PREVIEW_BOX_HEIGHT = 3 * BLOCK_HEIGHT;

    static constexpr int32_t SCORE_BOX_OFFSET_X = PREVIEW_BOX_OFFSET_X;
    static constexpr int32_t SCORE_BOX_OFFSET_Y = PREVIEW_BOX_OFFSET_Y + PREVIEW_BOX_HEIGHT + FIELD_OFFSET_Y;
    static constexpr int32_t SCORE_BOX_WIDTH = PREVIEW_BOX_WIDTH;
    static constexpr int32_t SCORE_BOX_HEIGHT = 90;

    static constexpr int32_t START_X = FIELD_WIDTH / 2 - 1;
    static constexpr int32_t START_Y = -5;
    static constexpr float AUTO_DROP_TIME = 0.4f;
    static constexpr float MANUAL_DROP_TIME = 0.05f;
    static constexpr float REMOVE_TIME = 0.2f;

    static constexpr int32_t SCORE_SIMPLE_MULTIPLIER = 10;
    static constexpr int32_t SCORE_DOUBLE_MULTIPLIER = 25;
    static constexpr int32_t SCORE_QUAD_MULTIPLIER = 50;



    // Tetrominos (left and bottom aligned, turned clockwise)
    // I
    const TetrominoSprite TetrominoI = {{{0, 3}, {1, 3}, {2, 3}, {3, 3}},
                                        {{0, 0}, {0, 1}, {0, 2}, {0, 3}}};
    // J
    const TetrominoSprite TetrominoJ = {{{0, 2}, {0, 3}, {1, 3}, {2, 3}},
                                        {{0, 1}, {1, 1}, {0, 2}, {0, 3}},
                                        {{0, 2}, {1, 2}, {2, 2}, {2, 3}},
                                        {{1, 1}, {1, 2}, {0, 3}, {1, 3}}};
    // L
    const TetrominoSprite TetrominoL = {{{2, 2}, {0, 3}, {1, 3}, {2, 3}},
                                        {{0, 1}, {0, 2}, {0, 3}, {1, 3}},
                                        {{0, 2}, {1, 2}, {2, 2}, {0, 3}},
                                        {{0, 1}, {1, 1}, {1, 2}, {1, 3}}};
    // O
    const TetrominoSprite TetrominoO = {{{0, 2}, {1, 2}, {0, 3}, {1, 3}}};
    // S
    const TetrominoSprite TetrominoS = {{{1, 2}, {2, 2}, {0, 3}, {1, 3}},
                                        {{0, 1}, {0, 2}, {1, 2}, {1, 3}}};
    // T
    const TetrominoSprite TetrominoT = {{{1, 2}, {0, 3}, {1, 3}, {2, 3}},
                                        {{0, 1}, {0, 2}, {1, 2}, {0, 3}},
                                        {{0, 2}, {1, 2}, {2, 2}, {1, 3}},
                                        {{1, 1}, {0, 2}, {1, 2}, {1, 3}}};
    // Z
    const TetrominoSprite TetrominoZ = {{{0, 2}, {1, 2}, {1, 3}, {2, 3}},
                                        {{1, 1}, {0, 2}, {1, 2}, {0, 3}}};

    const std::vector<TetrominoSprite> tetrominos = {TetrominoI, TetrominoJ, TetrominoL, TetrominoO, TetrominoS, TetrominoT, TetrominoZ};

private:
    void newTetromino();
    bool tetrominoHitsGround();
    void tetrominoToField();
    int32_t tetrominoWidth();
    int32_t checkRows();
    void removeRows();

    int32_t calcScore(int32_t removedRows);

    void drawBox(int32_t x, int32_t y, int32_t w, int32_t h);
    void drawField();
    void drawTetromino(int32_t x, int32_t y, int32_t fx, int32_t fy, const Tetromino &t);
    void drawFullRows();

    std::shared_ptr<ImageData> background;
    std::shared_ptr<BitmapFont> font;
    int8_t field[FIELD_WIDTH][FIELD_HEIGHT];

    int32_t currX;
    int32_t currY;
    int32_t nextTetromino;
    int32_t currTetrominoIdx;
    int32_t currTetrominoDir;
    float elapsedSum;
    float dropTime;
    bool gameover;
    bool removingRows;
    std::vector<int32_t> fullRows;

    int32_t score;
    int32_t highscore;
};
