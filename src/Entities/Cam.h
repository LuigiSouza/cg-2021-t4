#ifndef __CAM_H__
#define __CAM_H__

#include "../Handles/Vector3.h"

class Cam
{
private:
    Vector3 center;
    Vector3 direction;
    Vector3 head;
    Vector3 normal;

    float angle;
    float projection = 600;
    bool ortho;

public:
    bool get_ortho(void) { return ortho; }
    void set_ortho(bool i) { this->ortho = i; }

    Vector3 get_pos(void);
    Vector3 get_head(void);
    Vector3 get_direction(void);
    Vector3 get_normal(void);

    float get_projection(void);

    void set_center(Vector3 _c);
    void set_center_x(float _x);
    void set_center_y(float _y);
    void set_center_z(float _z);

    void set_direction(Vector3 _c);
    void set_direction_x(float _x);
    void set_direction_y(float _y);
    void set_direction_z(float _z);

    void set_angle(float _angle);

    inline Cam(Vector3 _c, Vector3 _d, float _angle, bool _ortho);
    inline ~Cam();
};

Cam::Cam(Vector3 _c, Vector3 _d, float _angle, bool _ortho)
{
    this->center = _c;
    this->direction = _d.normalized();
    this->set_angle(_angle);
    this->ortho = _ortho;
}

Cam::~Cam()
{
}

#endif
