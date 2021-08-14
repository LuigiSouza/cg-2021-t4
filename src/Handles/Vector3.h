#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

#include <math.h>

class Vector3
{
public:
    float x, y, z;

    Vector3()
    {
        x = y = z = 0;
    };

    Vector3(const float _x, const float _y, const float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    };

    Vector3(const Vector3 &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    };

    void set(const float _x, const float _y, const float _z)
    {
        this->x = _x;
        this->y = _y;
        this->z = _z;
    };

    void set(const Vector3 v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    };

    Vector3 operator+(const Vector3 v)
    {
        Vector3 aux(x + v.x, y + v.y, z + v.z);
        return (aux);
    }

    Vector3 operator-(const Vector3 v)
    {
        Vector3 aux(x - v.x, y - v.y, z - v.z);
        return (aux);
    }

    Vector3 operator*(const float v)
    {
        Vector3 aux(x * v, y * v, z * v);
        return (aux);
    }

    Vector3 operator/(const float s)
    {
        Vector3 aux(x / s, y / s, z / s);
        return (aux);
    }

    float operator*(const Vector3 v)
    {
        float aux = x * v.x + y * v.y + z * v.z;
        return (aux);
    }

    float norma()
    {
        return (float)(sqrt(x * x + y * y + z * z));
    }

    void normalize()
    {
        float norm = (this->norma());
        if (norm == 0)
        {
            this->x = 1;
            this->y = 1;
            this->z = 1;
        }
        else
        {
            this->x /= norm;
            this->y /= norm;
            this->z /= norm;
        }
    }
};

#endif