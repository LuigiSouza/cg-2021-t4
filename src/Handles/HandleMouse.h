
#ifndef ___MOUSE__H___
#define ___MOUSE__H___

class Mouse
{
private:
    float pos_x;
    float pos_y;

    bool prev_button[3];
    bool button[3];

    float prev_pos_x;
    float prev_pos_y;

    bool ctrl = false;

public:
    Mouse(void);
    ~Mouse(void);

    // get states
    bool isDown(int index);
    bool pushed(int index);
    bool released(int index);
    // update functions
    void setPress(int index);
    void update(void);
    // setters
    void setX(float x);
    void setY(float y);
    // getters
    float getX(void);
    float getY(void);
    float getPrevX(void);
    float getPrevY(void);
    // get move from ouse
    float moveX(void);
    float moveY(void);

    void setCtrl(bool ctrl);
    bool getCtrl(void);
};

#endif
