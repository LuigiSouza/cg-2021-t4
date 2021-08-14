#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "GameState.h"

/**
 * - GameOver
 * 
 *  Shows gameOver screen to quit game or back to Menu
*/


#include "../Panel/Panel.h"

class GameOver : public GameState
{
private:
    Panel *panel;

public:
    void update(Mouse mouse);
    void render(void);

    EnumBotao getDifficult(void);

    GameOver(float x, float y, float width, float height);
    ~GameOver();
};

#endif
