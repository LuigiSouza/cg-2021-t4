#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

/**
 * - GameState:
 * 
 * Interface to stores Manu, Game and GameOver states  
*/

#include <string>
#include <list>

#include "../gl_canvas2d.h"
#include "../Handles/HandleMouse.h"

#include "../Panel/Botao.h"

class GameState
{
protected:
    // Name of state and Name of next state
    std::string name_state;
    std::string change_state;
    // Sotre Points
    int used_darts, poped_balloons, total_balloons;

    EnumBotao difficult;

public:
    virtual ~GameState() {}

    static int total_darts;

    // Update functions
    virtual void render(void) = 0;
    virtual void update(Mouse mouse) = 0;
    // Reset next state to original state
    virtual void reset(EnumBotao difficult)
    {
        this->difficult = difficult;
        this->change_state = name_state;
    }

    EnumBotao getDifficult(void)
    {
        return this->difficult;
    }

    std::string get_changeState(void)
    {
        return change_state;
    }

    std::list<int> getPoints(void)
    {
        return {used_darts, poped_balloons, total_balloons};
    }
    // Set points to show in game over state
    void setPoints(std::list<int> points)
    {
        auto l_front = points.begin();

        used_darts = *l_front;
        std::advance(l_front, 1);
        poped_balloons = *l_front;
        std::advance(l_front, 1);
        total_balloons = *l_front;
    }
};

#endif
