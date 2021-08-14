#ifndef __MENU_H__
#define __MENU_H__

#include "GameState.h"

/**
 * - Menu
 * 
 * Main Menu, can start game, set difficult and quit canvas
*/

#include "../Panel/Panel.h"

class Menu : public GameState
{
private:
    Panel *panel;

public:
    void update(Mouse mouse);
    void render(void);

    EnumBotao getDifficult(void);

    Menu(float x, float y, float width, float height);
    ~Menu();
};

#endif
