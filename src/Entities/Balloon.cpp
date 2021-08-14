#include "Balloon.h"

bool Balloon::update(Vector2 *dart)
{
    for (int i = 0; i < 3; i++)
    {
        if (!was_pop && Algebra::distance(dart[i].x, dart[i].y, pos.x, pos.y) <= this->size)
        {
            was_pop = true;
            return true;
        }
    }
    return false;
}

void Balloon::render(void)
{
    if (was_pop)
        return;

    CV::color(this->r, this->g, this->b);
    CV::circleFill(pos.x, pos.y, this->size, BIG_CIRCLE_DIV);
    CV::color(0, 0, 0);
}

void Balloon::set_color(float _r, float _g, float _b)
{
    this->r = _r;
    this->g = _g;
    this->b = _b;
}

void Balloon::set_color(int index)
{
    float *rgb = this->balloon_color[index];
    this->r = rgb[0];
    this->g = rgb[1];
    this->b = rgb[2];
}

void Balloon::set_random_color(double seed)
{
    srand(seed);
    int r = rand() % 11;
    this->set_color(r);
}

Balloon::Balloon(float _x, float _y)
{
    this->pos = Vector2(_x, _y);
    was_pop = false;
    this->r = 1.0;
    this->g = 0.0;
    this->b = 1.0;
}

void Balloon::reset()
{
    was_pop = false;
}

Balloon::~Balloon()
{
}

float Balloon::getSize(void)
{
    return size;
}

float Balloon::size = 22.5;
