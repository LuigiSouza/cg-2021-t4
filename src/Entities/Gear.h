#ifndef __GEAR_H__
#define __GEAR_H__

#include "../Handles/Vector3.h"
#include "../Handles/DinamicArray.h"

#include <algorithm>

#include "../gl_canvas2d.h"

#define GEAR_IN 0.2
#define GEAR_OUT 0.2
#define SIZE_CLAW 30
#define DIV 1

class Gear
{
private:
    int claws;
    float radius_in;
    float radius_out;
    float radius_claw;

    float size_gear_in;
    float size_gear_out;
    float thickness;

    DinamicArray<Vector3> *vertices;
    int num_vertices;

public:
    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);
    void create_gear(void);
    void render(void);

    inline Gear(float radius, float crown_size, float claws_num, float thickness);
    inline ~Gear();
};

Gear::Gear(float radius, float crown_size, float claws_num, float thickness)
{
    this->vertices = new DinamicArray<Vector3>(DIV * claws_num * 4 + claws_num);
    this->claws = claws_num;
    this->radius_in = radius;
    this->radius_out = radius + crown_size;
    this->thickness = thickness;
    this->radius_claw = radius_out + SIZE_CLAW;
    this->size_gear_in = std::min(std::max(0.0, GEAR_IN), 1.0);
    this->size_gear_out = std::min(std::max(0.0, GEAR_OUT), 1.0);
    this->create_gear();
}

Gear::~Gear()
{
    delete vertices;
}

#endif
