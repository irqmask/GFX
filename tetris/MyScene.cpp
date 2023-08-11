#include "MyScene.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "Path.h"

Tetris::Tetris(std::shared_ptr<Engine> engine)
    : Scene(engine)
    , currX(START_X)
    , currY(START_Y)
    , currTetrominoIdx(0)
    , currTetrominoDir(0)
    , elapsedSum(0.0f)
    , dropTime(AUTO_DROP_TIME)
    , gameover(false)
    , removingRows(false)
    , score(0)
    , highscore(0)
{
    Path assetPath = Path::fromCurrentExecutable().plusPath("assets");
    background = engine->loadImage(assetPath.plusFilename("background.png"));
    font = std::shared_ptr<BitmapFont>(new BitmapFont(assetPath.plusFilename("font.png"), 9, 16, 20, 128));

    for (int32_t y = 0; y < FIELD_HEIGHT; y++) {
        for (int32_t x = 0; x < FIELD_WIDTH; x++) {
            field[x][y] = 0;
        }
    }
    nextTetromino = rand() % tetrominos.size();
    newTetromino();
}


Tetris::~Tetris()
{
    std::cout << __FUNCTION__ << std::endl;
}


void Tetris::onEvent(SDL_Event& event)
{
    Scene::onEvent(event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_DOWN:
            dropTime = MANUAL_DROP_TIME;
            break;
        case SDLK_UP:
            currTetrominoDir++;
            currTetrominoDir %= tetrominos[currTetrominoIdx].size();
            if (currX + tetrominoWidth() >= FIELD_WIDTH) {
                currX = FIELD_WIDTH - tetrominoWidth();
            }
            break;
        case SDLK_LEFT:
            if (currX > 0) currX--;
            break;
        case SDLK_RIGHT:
            if (currX < (FIELD_WIDTH - tetrominoWidth())) currX++;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_DOWN:
            dropTime = AUTO_DROP_TIME;
            break;
        default:
            break;
        }
    }
}


void Tetris::update(float elapsed)
{
    if (!gameover) {
        // drop tetrominos
        if (removingRows) {
            elapsedSum += elapsed;
            if (elapsedSum > REMOVE_TIME) {
                elapsedSum = 0.0f;
                removeRows();
            }
        }
        else {
            elapsedSum += elapsed;
            if (elapsedSum > dropTime) {
                elapsedSum = 0.0f;
                if (tetrominoHitsGround()) {
                    if (currY < 0) {
                        gameover = true;
                    }
                    tetrominoToField();

                    int32_t rows = checkRows();
                    if (rows > 0) {
                        removingRows = true;
                        score += calcScore(rows);
                        if (score > highscore) {
                            highscore = score;
                        }
                    }

                    newTetromino();
                }
                currY++;
            }
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}


void Tetris::draw()
{
    clearBackground(0, 0, 0, 255);

    drawImage(0, 0, background);
    drawField();

    // draw next
    drawTetromino(PREVIEW_BOX_OFFSET_X + BLOCK_WIDTH / 2,
                  PREVIEW_BOX_OFFSET_Y + BLOCK_HEIGHT / 2,
                  0, -2,
                  tetrominos[nextTetromino][0]);

    // draw score
    font->print(SCORE_BOX_OFFSET_X + 10, SCORE_BOX_OFFSET_Y + 10, "Score:");
    std::string scoreString = std::to_string(score);
    font->print(SCORE_BOX_OFFSET_X + 10, SCORE_BOX_OFFSET_Y + 30, scoreString);
    font->print(SCORE_BOX_OFFSET_X + 10, SCORE_BOX_OFFSET_Y + 50, "Highscore:");
    std::string highscoreString = std::to_string(highscore);
    font->print(SCORE_BOX_OFFSET_X + 10, SCORE_BOX_OFFSET_Y + 70, highscoreString);

    // draw current
    drawTetromino(FIELD_OFFSET_X, FIELD_OFFSET_Y, currX, currY, tetrominos[currTetrominoIdx][currTetrominoDir]);

    if (removingRows) drawFullRows();
    /*
    for (auto &tall: tetrominos) {
        y = 0;
        for (auto &t: tall) {
            drawTetromino(x, y, t);
            y += 5;
        }
        x += 5;
    }*/
}


void Tetris::newTetromino()
{
    currX = START_X;
    currY = START_Y;
    currTetrominoIdx = nextTetromino;
    nextTetromino = rand() % tetrominos.size();
    currTetrominoDir = rand() % tetrominos[currTetrominoIdx].size();
}


bool Tetris::tetrominoHitsGround()
{
    const Tetromino & t = tetrominos[currTetrominoIdx][currTetrominoDir];
    for (auto b: t) {
        int32_t x = currX + b.x;
        int32_t y = currY + b.y + 1;

        if (x < 0 || y < 0 || x >= FIELD_WIDTH)
            continue;

        if (y >= FIELD_HEIGHT)
            return true;

        if (field[x][y] != 0)
            return true;
    }
    return false;
}


void Tetris::tetrominoToField()
{
    const Tetromino & t = tetrominos[currTetrominoIdx][currTetrominoDir];
    for (auto b: t) {
        int32_t fieldX = currX + b.x;
        int32_t fieldY = currY + b.y;
        if (fieldX < 0 || fieldY < 0) continue;
        field[fieldX][fieldY] = currTetrominoIdx + 1;
    }
}


int32_t Tetris::tetrominoWidth()
{
    int maxX = 0;
    const Tetromino & t = tetrominos[currTetrominoIdx][currTetrominoDir];
    for (auto b: t) {
        if (b.x > maxX) maxX = b.x;
    }
    return maxX + 1;
}


int32_t Tetris::checkRows()
{
    for (int32_t y = 0; y < FIELD_HEIGHT; y++) {
        bool full = true;
        for (int32_t x = 0; x < FIELD_WIDTH; x++) {
            if (field[x][y] == 0) full = false;
        }
        if (full) fullRows.push_back(y);
    }
    // found full row
    removingRows = (fullRows.size() > 0);
    return static_cast<int32_t>(fullRows.size());
}


void Tetris::removeRows()
{
    if (fullRows.size() > 0) {
        int32_t yy = fullRows.front();
        fullRows.erase(fullRows.begin());

        for (int32_t y = yy; y > 0; y--) {
            for (int32_t x = 0; x<FIELD_WIDTH; x++) {
                field[x][y] = field[x][y-1];
            }
        }

        for (int32_t x = 0; x<FIELD_WIDTH; x++) {
            field[x][0] = 0;
        }
    }
    else {
        removingRows = false;
    }
}


int32_t Tetris::calcScore(int32_t removedRows)
{
    if (removedRows >= 4) return removedRows * SCORE_QUAD_MULTIPLIER;
    if (removedRows >= 2) return removedRows * SCORE_DOUBLE_MULTIPLIER;
    return removedRows * SCORE_SIMPLE_MULTIPLIER;
}


void Tetris::drawBox(int32_t x, int32_t y, int32_t w, int32_t h)
{
    setDrawForegroundColor(255, 255, 192, 255);
    drawRect(x - 1, y - 1, w + 2, h + 2);
    setDrawForegroundColor(32, 32, 32, 96);
    drawFilledRect(x, y, w, h);
}


void Tetris::drawField()
{
    // draw preview box
    drawBox(PREVIEW_BOX_OFFSET_X, PREVIEW_BOX_OFFSET_Y, PREVIEW_BOX_WIDTH, PREVIEW_BOX_HEIGHT);

    // draw score box
    drawBox(SCORE_BOX_OFFSET_X, SCORE_BOX_OFFSET_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT);


    // draw field
    drawBox(FIELD_OFFSET_X, FIELD_OFFSET_Y, BLOCK_WIDTH * FIELD_WIDTH, BLOCK_HEIGHT * FIELD_HEIGHT);


    setDrawForegroundColor(255, 255, 192, 128);
    for (int32_t y = 0; y < FIELD_HEIGHT; y++) {
        for (int32_t x = 0; x < FIELD_WIDTH; x++) {
            if (field[x][y] != 0) {
                drawFilledRect(FIELD_OFFSET_X + x * BLOCK_WIDTH,
                               FIELD_OFFSET_Y + y * BLOCK_HEIGHT,
                               BLOCK_WIDTH,
                               BLOCK_HEIGHT);
            }
        }
    }
}


void Tetris::drawFullRows()
{
    setDrawForegroundColor(10, 20, 128, 128);

    for (int32_t y : fullRows) {
        drawFilledRect(FIELD_OFFSET_X, FIELD_OFFSET_Y + y * BLOCK_HEIGHT, FIELD_WIDTH * BLOCK_WIDTH, BLOCK_HEIGHT);
    }
}


void Tetris::drawTetromino(int32_t x, int32_t y, int32_t fx, int32_t fy, const Tetromino &t)
{
    setDrawForegroundColor(192, 192, 192, 255);

    for (auto b: t)
    {
        int32_t fieldX = fx + b.x;
        int32_t fieldY = fy + b.y;
        if (fieldX < 0 || fieldY < 0) continue;

        drawRect(x + fieldX * BLOCK_WIDTH,
                 y + fieldY * BLOCK_HEIGHT,
                 BLOCK_WIDTH,
                 BLOCK_HEIGHT);
    }
}
