#ifndef __BALLOON_H__
#define __BALLOON_H__

#include "../Handles/Vector2.h"
#include "../Handles/Algebra.h"
#include "../gl_canvas2d.h"
class Balloon
{
private:
    float balloon_color[11][3] =
        {
            {1, 0, 0},     //Red
            {0, 1, 0},     //Green
            {0, 0, 1},     //Blue
            {1, 0.5, 0},   //Orange
            {0.5, 0, 0},   //Brown
            {0.5, 0.5, 0}, //Olive
            {0, 0.5, 0.5}, //
            {0.5, 0, 0.5}, //
            {0, 1, 1},     //Cyan
            {1, 0, 1},     //Magenta
            {1, 1, 0},     //Yellow
    };

    Vector2 pos;

    static float size;

    float r, g, b;
    bool was_pop;

public:
    Balloon(float _x, float _y);
    ~Balloon();

    void set_random_color(double seed);
    void set_color(int index);
    void set_color(float _r, float _g, float _b);

    static float getSize(void);

    void reset();
    bool update(Vector2 *dart);
    void render(void);
};

#endif
