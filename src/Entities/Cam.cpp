#include "Cam.h"

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

void Cam::set_angle(float _angle)
{
    this->angle = _angle;
    Vector3 aux = direction.normalized();
    int i = aux.x < 0 ? -1 : 1;
    Vector3 a = Vector3(-aux.y * i, aux.x * i, 0);
    if (aux.x == 0 && aux.y == 0)
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
