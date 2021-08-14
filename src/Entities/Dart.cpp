#include "Dart.h"

Vector2 Dart::getPointP1(Mouse mouse)
{
    float mousex = mouse.getX();
    float mousey = mouse.getY();
    this->force = Algebra::distance(mousex, mousey, p0.x, p0.y);
    float max_mul = -std::min(this->force, max_force);
    return Vector2(((mousex - p0.x) / (this->force)) * max_mul + p0.x, ((mousey - p0.y) / (this->force)) * max_mul + p0.y);
}

Vector2 Dart::getPointP2(void)
{
    float a = -(0.5 * gravity);
    float b = (p1.y - p0.y);
    float c = p0.y;

    double discriminant = b * b - 4 * a * c;
    double time = (-b - sqrt(discriminant)) / (2 * a);

    return Vector2(p0.x + ((p1.x - p0.x) * time), 0);
}

Vector2 Dart::scalePoint(Mouse mouse, float scale)
{
    double sin = ((mouse.getY() - p0.y) / (this->force)) * -1;
    this->sum_t = 0.0125 - (sin * 0.0075);
    return ((p1 - p0) * (Algebra::map(sin, -1, 1, 1, scale))) + p0;
}

void Dart::reset_dart(void)
{
    it_fell = false;
    t = 0;
    pos = p0;
}

void Dart::updatePoints(Mouse mouse)
{
    p1 = getPointP1(mouse);
    p2 = getPointP2();
    p1 = scalePoint(mouse, 6);
}

void Dart::update_dart(void)
{
    if (it_fell)
        return;

    prevPos = pos;
    t += sum_t;
    if (t <= 1)
    {
        pos = Algebra::quadratic_bezier(p0, p1, p2, t);
        it_fell = (prevPos.x < 0 || prevPos.y < 0);

        float dist_porojectile = Algebra::distance(prevPos.x, prevPos.y, pos.x, pos.y);
        float proportion = dart_size / dist_porojectile;
        prevPos = (prevPos - pos) * proportion + pos;

        arrow[0] = pos;
        Vector2 rotate = Algebra::rotate((pos.x - prevPos.x) / 2, (pos.y - prevPos.y) / 2, PI_div_4);
        arrow[1] = prevPos + rotate;
        rotate = Algebra::rotate((pos.x - prevPos.x) / 2, (pos.y - prevPos.y) / 2, -PI_div_4);
        arrow[2] = prevPos + rotate;
    }
    else
    {
        it_fell = true;
    }
}

void Dart::render_reference(void)
{
    CV::circleFill(p0.x, p0.y, 2, SML_CIRCLE_DIV);
    CV::circleFill(p1.x, p1.y, 2, SML_CIRCLE_DIV);
    CV::circleFill(p2.x, p2.y, 2, SML_CIRCLE_DIV);
}

void Dart::render_path(void)
{
    for (double i = 0; i <= 1; i += 0.1)
    {
        Vector2 q0 = Algebra::quadratic_bezier(p0, p1, p2, i);
        CV::circleFill(q0.x, q0.y, 5, SML_CIRCLE_DIV);
    }
    pos = Algebra::quadratic_bezier(p0, p1, p2, t);
}

void Dart::render_dart(void)
{
    CV::line(prevPos.x, prevPos.y, pos.x, pos.y);

    float arrow_x[3] = {
        arrow[0].x,
        arrow[1].x,
        arrow[2].x};
    float arrow_y[3] = {
        arrow[0].y,
        arrow[1].y,
        arrow[2].y};

    CV::polygonFill(arrow_x, arrow_y, 3);
}

bool Dart::hitGround(void)
{
    return it_fell;
}

Vector2 Dart::getPos(void)
{
    return Vector2(pos);
}

Vector2 *Dart::getArrow(void)
{
    return arrow;
}

float Dart::getForce(void)
{
    return std::min(this->force, max_force);
}

Dart::Dart(Vector2 _p0)
{
    p0 = Vector2(_p0);
    it_fell = false;
}

Dart::Dart(float _x, float _y)
{
    p0 = Vector2(_x, _y);
    it_fell = false;
}

Dart::~Dart()
{
    delete arrow;
}

float Dart::max_force = 150.0;
float Dart::gravity = 30.0;
float Dart::dart_size = 30.0;
