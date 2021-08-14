#ifndef __GAME_H__
#define __GAME_H__

#include "GameState.h"

/**
 * - Game
 * 
 * Main class, responsible to render cannon, balloons, dart and show points
*/

#include "../Entities/Cannon.h"
#include "../Entities/Balloon.h"
#include <list>

class Game : public GameState
{
private:
    Cannon *cannon;
    std::list<Balloon *> balloons;

    int *screenWidth, *screenHeight;

    bool balloons_grid[10][10] = {
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
    };

    void render_background(void);

public:
    void update(Mouse mouse);
    void render(void);

    void reset(EnumBotao difficult);

    Game(int *_screenWidth, int *_screenHeight);
    ~Game();
};

#endif
