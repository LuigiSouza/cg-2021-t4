#ifndef __DART_H__
#define __DART_H__

#include "../Handles/HandleMouse.h"
#include "../Handles/Vector2.h"
#include "../Handles/Algebra.h"

#include "../gl_canvas2d.h"

/**
 * - Dart
 * 
 * Class to handle dart shot by cannon
*/

class Dart
{
private:
    // Stores positions of arrow to hit balloons
    Vector2 prevPos, pos;
    Vector2 p0, p1, p2;

    Vector2 arrow[3];

    // Variables to show where is going to hit and how fast the dart is going to update
    float force = 1.0;
    float t = 0.0;
    float sum_t = 0.005;
    // Checks if darts is in the screen
    bool it_fell;
    // Static variables to stores fisics arguments
    static float max_force;
    static float gravity;
    static float dart_size;

    // Scale p1 to make a wider curve
    Vector2 scalePoint(Mouse mouse, float scale);
    // Gets p1 and p2 to make bezier curve
    Vector2 getPointP1(Mouse mouse);
    Vector2 getPointP2(void);

public:
    Dart(Vector2 _p0);
    Dart(float _x, float _y);
    ~Dart();

    void reset_dart(void);

    void updatePoints(Mouse mouse);
    void update_dart(void);

    // render p1 and p2
    void render_reference(void);
    // render bezier curve
    void render_path(void);
    void render_dart(void);

    bool hitGround(void);
    Vector2 getPos(void);
    Vector2 *getArrow(void);
    float getForce(void);
};

#endif
