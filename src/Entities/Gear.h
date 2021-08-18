#ifndef __GEAR_H__
#define __GEAR_H__

#include "../Handles/Algebra.h"
#include "../Handles/Vector3.h"
#include "../Handles/DinamicArray.h"

#include <algorithm>

#include "../gl_canvas2d.h"
#include "Cam.h"

#define GEAR_IN 0.3
#define GEAR_OUT 0.3
#define SIZE_TOOTH 30
#define DIV 4
#define DEFAULT_VALUE 10

class Gear
{
private:
    float posx, posy, posz;

    int tooths;
    float radius_in;
    float radius_out;
    float radius_tooth;

    float size_gear_in;
    float size_gear_out;
    float thickness;

    DinamicArray<Vector3> *vertices;
    DinamicArray<Vector3> *vertices_draw;
    int num_vertices;
    bool is_flat = false;
    bool rendered = false;

public:
    void matrix_view(Cam cam);
    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);
    void create_gear(void);
    void render(void);

    inline Gear(Vector3 _pos, float radius, float crown_size, float tooths_num, float thickness, bool flat);
    inline ~Gear();
};

Gear::Gear(Vector3 _pos, float radius, float crown_size, float tooths_num, float thickness, bool flat)
{
    radius = radius > 0 ? radius : DEFAULT_VALUE;
    thickness = thickness > 0 ? thickness : DEFAULT_VALUE;
    tooths_num = tooths_num > 0 ? tooths_num : DEFAULT_VALUE;
    crown_size = crown_size > 0 ? crown_size : DEFAULT_VALUE;

    this->posx = _pos.x;
    this->posy = _pos.y;
    this->posz = _pos.z;
    this->is_flat = flat;

    this->vertices = new DinamicArray<Vector3>(DIV * tooths_num * 4 + tooths_num);
    this->vertices_draw = new DinamicArray<Vector3>(DIV * tooths_num * 4 + tooths_num);

    this->tooths = tooths_num;
    this->radius_in = radius;
    this->radius_out = radius + crown_size;
    this->thickness = thickness;

    this->radius_tooth = radius_out + SIZE_TOOTH;
    this->size_gear_in = std::min(std::max(0.0, GEAR_IN), 1.0);
    this->size_gear_out = std::min(std::max(0.0, GEAR_OUT), 1.0);
    this->create_gear();
}

Gear::~Gear()
{
    delete vertices;
}

#endif
