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
    float projection = 300;
    bool ortho;

public:
    Vector3 get_pos(void);
    Vector3 get_head(void);
    Vector3 get_direction(void);
    Vector3 get_normal(void);

    float get_projection(void);

    void set_center(Vector3 _c);
    void set_center_x(float _x);
    void set_center_y(float _y);
    void set_center_z(float _z);

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
