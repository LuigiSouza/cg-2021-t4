#ifndef __FRAMES_H__
#define __FRAMES_H__

#include <stdio.h>
#include <time.h>

#define UPDATE_RATE 20

class Frames
{
    clock_t t1, t2;
    float fps, fps_old;
    int cont_frames;

    float x, y;
    char label[20];

public:
    Frames(float _x, float _y)
    {
        this->x = _x;
        this->y = _y;
        this->fps_old = 20;
        this->cont_frames = 0;
    }

    float get_fps()
    {
        return fps;
    }

    void render()
    {
        CV::translate(0, 0);
        CV::color(1, 1, 1);

        t2 = clock();
        double dt = (double)(t2 - t1);
        cont_frames++;

        if (dt > UPDATE_RATE)
        {
            t1 = t2;
            fps = cont_frames / (dt / CLOCKS_PER_SEC);
            cont_frames = 0;
            fps_old = fps;
            sprintf(label, "FPS: %d", int(fps));
        }
        else
        {
            sprintf(label, "FPS: %d", int(fps_old));
        }
        CV::text(x, y, label);
    }
};

#endif
