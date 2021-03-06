#ifndef __GEAR_H__
#define __GEAR_H__

#include "../Handles/Algebra.h"
#include "../Handles/Vector3.h"
#include "../Handles/DinamicArray.h"

#include <algorithm>

#include "../gl_canvas2d.h"
#include "Cam.h"

#define DIV_IN 4
#define DIV_TOOTH 4
#define DEFAULT_VALUE 10

// Gear class
class Gear
{
private:
    float posx, posy, posz;

    int tooths;
    float radius_tooth;
    float thickness;

    // Radius from center to inside circle
    float radius_in;
    // Radius from center to outside circle
    float radius_out;

    float size_tooth;
    // Size from inside circle to outside circle
    float crown_size;

    // Distance from one tooth to another
    float size_gear_in;
    float size_gear_out;

    // Vertices relative to (0,0,0)
    DinamicArray<Vector3> *vertices;
    DinamicArray<Vector3> *vertices_draw;
    // Number of vertices of one side of gear excluding inside circle
    int num_vertices;

    // Flag to check if it will render based on (0,0,0) coordinates or pre drawn coordinates
    bool rendered = false;
    bool is_flat = false;

public:
    // Convert world coordinates to view coordinates
    void matrix_view(Cam cam);
    // Recreate gear when changes occur
    void create_gear(void);

    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);

    void set_radius(float _rad);
    void set_tooths(int _num);
    void set_type(bool flat);
    void set_size_tooth(float size);
    void set_thickness(float thick);
    void set_crown_size(float size);

    void set_in_gap(float gap);
    void set_out_gap(float gap);

    void render(void);

    inline Gear(Vector3 _pos, float radius, float _crown_size, float tooths_num, float _size_tooth, float thickness, bool flat, float in_gap, float out_gap);
    inline ~Gear();
};

Gear::Gear(Vector3 _pos, float radius, float _crown_size, float tooths_num, float _size_tooth, float thickness, bool flat, float in_gap, float out_gap)
{
    radius = radius > DEFAULT_VALUE ? radius : DEFAULT_VALUE;
    thickness = thickness > DEFAULT_VALUE ? thickness : DEFAULT_VALUE;
    tooths_num = tooths_num > DEFAULT_VALUE ? tooths_num : DEFAULT_VALUE;
    _crown_size = _crown_size > DEFAULT_VALUE ? _crown_size : DEFAULT_VALUE;
    _size_tooth = _size_tooth > DEFAULT_VALUE ? _size_tooth : DEFAULT_VALUE;

    this->posx = _pos.x;
    this->posy = _pos.y;
    this->posz = _pos.z;
    this->is_flat = flat;

    this->vertices = new DinamicArray<Vector3>(DIV_IN * tooths_num * DIV_TOOTH + tooths_num);
    this->vertices_draw = new DinamicArray<Vector3>(DIV_IN * tooths_num * DIV_TOOTH + tooths_num);

    this->tooths = tooths_num;
    this->radius_in = radius;
    this->size_tooth = _size_tooth;
    this->crown_size = _crown_size;
    this->radius_out = radius + _crown_size;
    this->thickness = thickness;

    this->radius_tooth = radius_out + size_tooth;
    this->size_gear_in = std::min(std::max(0.1, (double)in_gap), 0.9);
    this->size_gear_out = std::min(std::max(0.1, (double)out_gap), 0.9);
    this->create_gear();
}

Gear::~Gear()
{
    delete vertices;
    delete vertices_draw;
}

#endif
