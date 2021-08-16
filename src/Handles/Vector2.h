#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath>

class Vector2
{
public:
    float x, y;

    Vector2()
    {
        x = y = 0;
    }

    Vector2(const float _x, const float _y)
    {
        x = _x;
        y = _y;
    }

    Vector2(const Vector2 &vec)
    {
        x = vec.x;
        y = vec.y;
    }

    void set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void set(Vector2 vec)
    {
        x = vec.x;
        y = vec.y;
    }

    void normalize()
    {
        float norm = (float)sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            x = 1;
            y = 1;
            return;
        }
        x /= norm;
        y /= norm;
    }

    Vector2 normalized()
    {
        float norm = (float)sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            return Vector2(1, 1);
        }
        return Vector2(x / norm, y / norm);
    }

    Vector2 operator-(const Vector2 &v)
    {
        Vector2 aux(x - v.x, y - v.y);
        return (aux);
    }

    Vector2 operator+(const Vector2 &v)
    {
        Vector2 aux(x + v.x, y + v.y);
        return (aux);
    }

    Vector2 operator*(const Vector2 &v)
    {
        Vector2 aux(x * v.x, y * v.y);
        return (aux);
    }

    Vector2 operator/(const Vector2 &v)
    {
        Vector2 aux(x / v.x, y / v.y);
        return (aux);
    }

    Vector2 operator*(const double mul)
    {
        Vector2 aux(x * mul, y * mul);
        return (aux);
    }

    Vector2 operator/(const double div)
    {
        Vector2 aux(x / div, y / div);
        return (aux);
    }

    //Adicionem os demais overloads de operadores aqui.
};

#endif
