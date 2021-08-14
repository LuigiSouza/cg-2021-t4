#include "Cannon.h"

Cannon::Cannon(float _x, float _y) : dart(_x, _y)
{
    this->pos = Vector2(_x, _y);
    this->direction[0] = pos;
    this->direction[1] = Vector2(pos.x - minimum_force / 2.0, pos.y + minimum_force);
    this->direction[2] = Vector2(pos.x + minimum_force / 2.0, pos.y + minimum_force);
    this->state = CannonState::Stop;
    this->r = 1;
    this->g = 0.5;
    this->r = 0;
}

Cannon::~Cannon()
{
}

void Cannon::updateCannon(Mouse mouse)
{
    float mousex = mouse.getX();
    float mousey = mouse.getY();
    float force = Algebra::distance(mousex, mousey, pos.x, pos.y);
    float max_mul = -minimum_force;
    float pointx = ((mousex - pos.x) / (force)) * max_mul + pos.x;
    float pointy = ((mousey - pos.y) / (force)) * max_mul + pos.y;

    Vector2 rotate = Algebra::rotate((pointx - pos.x) / 2, (pointy - pos.y) / 2, PI_div_2);
    rotate.set(rotate.x + pointx, rotate.y + pointy);
    direction[1] = rotate;

    rotate = Algebra::rotate((pointx - pos.x) / 2, (pointy - pos.y) / 2, -PI_div_2);
    rotate.set(rotate.x + pointx, rotate.y + pointy);
    direction[2] = rotate;
}

void Cannon::update(Mouse mouse)
{
    if (dart.hitGround())
    {
        state = CannonState::Stop;
        dart.reset_dart();
    }
    if (state == CannonState::Drag)
    {
        dart.updatePoints(mouse);
        updateCannon(mouse);
    }
    if (state == CannonState::Shoot)
        dart.update_dart();
}

void Cannon::reset(void)
{
    this->direction[0] = pos;
    this->direction[1].set(pos.x - minimum_force / 2.0, pos.y + minimum_force);
    this->direction[2].set(pos.x + minimum_force / 2.0, pos.y + minimum_force);
    this->state = CannonState::Stop;
}

void Cannon::render_force(void)
{
    Vector2 force = (direction[1] + direction[2]) / 2.0;
    float dist = Algebra::distance(force.x, force.y, direction[0].x, direction[0].y);
    force = (force - direction[0]) * -1;
    force = (force / dist) * dart.getForce();

    Vector2 arm1 = Algebra::rotate(force.x, force.y, PI_div_2);
    Vector2 arm2 = Algebra::rotate(force.x, force.y, -PI_div_2);
    force = force + direction[0];
    arm1.normalize();
    arm2.normalize();
    arm1 = arm1 * this->size + force;
    arm2 = arm2 * this->size + force;

    CV::line(force.x, force.y, direction[0].x, direction[0].y);
    CV::line(arm1.x, arm1.y, arm2.x, arm2.y);
}

void Cannon::render(bool show_path)
{
    CV::color(1, 1, 1);
    if (show_path && state == CannonState::Drag)
        dart.render_path();
    if (state == CannonState::Shoot)
        dart.render_dart();

    CV::color(r, g, b);
    CV::circleFill(pos.x, pos.y, size, SML_CIRCLE_DIV);
    float cannon_x[3] = {
        direction[0].x,
        direction[1].x,
        direction[2].x};
    float cannon_y[3] = {
        direction[0].y,
        direction[1].y,
        direction[2].y};
    CV::polygonFill(cannon_x, cannon_y, 3);

    if (state == CannonState::Drag)
        render_force();

    CV::color(0, 0, 0);
}

CannonState Cannon::getState(void)
{
    return this->state;
}

Vector2 Cannon::getDartPos(void)
{
    return dart.getPos();
}

Vector2 *Cannon::getDartArrow(void)
{
    return dart.getArrow();
}

bool Cannon::shotDart(void)
{
    if (state != CannonState::Drag)
        return false;
    if (this->dart.getForce() < this->minimum_force)
    {
        state = CannonState::Stop;
        return false;
    }
    dart.reset_dart();
    state = CannonState::Shoot;
    return true;
}

void Cannon::dragCannon(Mouse mouse)
{
    if (state != CannonState::Shoot && Algebra::distance(mouse.getX(), mouse.getY(), pos.x, pos.y) < size)
    {
        state = CannonState::Drag;
    }
}

float Cannon::size = 15.0;
float Cannon::minimum_force = 30.0;
