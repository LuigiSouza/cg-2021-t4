#include "Cam.h"
#include <iostream>

void Cam::set_center(Vector3 _c)
{
    this->center = _c;
}

void Cam::set_center_x(float _x)
{
    this->center.x = _x;
}
void Cam::set_center_y(float _y)
{
    this->center.y = _y;
}
void Cam::set_center_z(float _z)
{
    this->center.z = _z;
}

void Cam::set_direction(Vector3 _c)
{
    this->direction = _c;
    set_angle(angle);
}

void Cam::set_direction_x(float _x)
{
    this->direction.x = _x;
    set_direction(direction);
}
void Cam::set_direction_y(float _y)
{
    this->direction.y = _y;
    set_direction(direction);
}
void Cam::set_direction_z(float _z)
{
    this->direction.z = _z;
    set_direction(direction);
}

void Cam::set_angle(float _angle)
{
    this->angle = _angle;
    Vector3 aux = direction.normalized();
    Vector3 a = Vector3(0, aux.z, -aux.y);
    if (aux.z == 0 && aux.y == 0)
        a.y = 1;
    Vector3 w = a ^ direction;
    Vector3 r = (a * (cos(_angle) / a.norma()) + w * (sin(_angle) / w.norma())) * a.norma();
    this->head = r.normalized();
    this->normal = head ^ direction;
}

float Cam::get_projection(void)
{
    return this->projection;
}

Vector3 Cam::get_pos(void)
{
    return Vector3(this->center);
}

Vector3 Cam::get_head(void)
{
    return Vector3(this->head);
}

Vector3 Cam::get_direction(void)
{
    return Vector3(this->direction);
}

Vector3 Cam::get_normal(void)
{
    return Vector3(this->normal);
}
