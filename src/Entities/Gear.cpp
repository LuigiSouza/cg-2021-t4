#include "Gear.h"

#include <iostream>

void Gear::create_gear(void)
{
    float increment = PI_2 / claws * 0.5;
    std::cout << vertices->get_limit() << " ";

    bool is_claw = true;
    for (float tmp = 0; tmp <= PI_2; tmp += increment)
    {
        if (is_claw)
        {
            double size_gear = increment * size_gear_out;
            double div = (size_gear + size_gear) / DIV;
            for (double i = tmp - size_gear; i <= tmp + size_gear; i += div)
            {
                vertices->add(Vector3(sin(i) * radius_claw, cos(i) * radius_claw, 0));
            }
        }
        else
        {
            double size_gear = increment * size_gear_in;
            double div = (size_gear + size_gear) / DIV;
            for (double i = tmp - size_gear; i <= tmp + size_gear; i += div)
            {
                vertices->add(Vector3(sin(i) * radius_out, cos(i) * radius_out, 0));
            }
        }
        is_claw = !is_claw;
    }
    this->num_vertices = vertices->get_size();
    for (int i = 0; i < num_vertices; i++)
    {
        Vector3 other_side = *vertices->get(i);
        other_side.z = thickness;
        vertices->add(Vector3(other_side));
    }
    double div = PI_2 / claws;
    for (double i = 0; i <= PI_2; i += div)
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, 0));
    for (double i = 0; i <= PI_2; i += div)
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, thickness));

    std::cout << vertices->get_limit() << " ";
    std::cout << vertices->get_size() << " ";
}

void Gear::render(void)
{
    Vector3 *prev = vertices->get(0);
    Vector3 *next;
    Vector3 *prev_z;

    // Connect front vertices with with themselves
    for (int i = 1; i < num_vertices; i++)
    {
        next = vertices->get(i);
        CV::line(prev->x, prev->y, next->x, next->y);
        prev = next;
    }
    next = vertices->get(0);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect back vertices with with themselves and with front vertices
    prev = vertices->get(num_vertices);
    for (int i = 1; i < num_vertices; i++)
    {
        next = vertices->get(i + num_vertices);
        CV::line(prev->x, prev->y, next->x, next->y);

        prev = vertices->get(i + num_vertices - 1);
        prev_z = vertices->get(i - 1);
        CV::line(prev->x, prev->y, prev_z->x, prev_z->y);

        prev = next;
    }

    next = vertices->get(num_vertices);
    prev_z = vertices->get(num_vertices - 1);
    CV::line(prev->x, prev->y, prev_z->x, prev_z->y);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect the inner circle
    prev = vertices->get(2 * num_vertices);
    for (int i = 1; i < claws; i++)
    {
        next = vertices->get(i + 2 * num_vertices);
        CV::line(prev->x, prev->y, next->x, next->y);
        prev = next;
    }
    next = vertices->get(2 * num_vertices);
    CV::line(prev->x, prev->y, next->x, next->y);

    prev = vertices->get(2 * num_vertices + claws);
    for (int i = 1; i < claws; i++)
    {
        next = vertices->get(i + 2 * num_vertices + claws);
        CV::line(prev->x, prev->y, next->x, next->y);

        prev = vertices->get(i + 2 * num_vertices + claws - 1);
        prev_z = vertices->get(i + 2 * num_vertices - 1);
        CV::line(prev->x, prev->y, prev_z->x, prev_z->y);

        prev = next;
    }

    next = vertices->get(2 * num_vertices + claws);
    prev_z = vertices->get(2 * num_vertices + claws - 1);
    CV::line(prev->x, prev->y, prev_z->x, prev_z->y);
    CV::line(prev->x, prev->y, next->x, next->y);
}

void Gear::rotate_x(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);

    for (int i = 0; i < vertices->get_size(); i++)
    {
        Vector3 old_pos = Vector3(*vertices->get(i));
        this->vertices->get(i)->x = old_pos.x;
        this->vertices->get(i)->y = old_pos.y * cosseno - old_pos.z * seno;
        this->vertices->get(i)->z = old_pos.y * seno + old_pos.z * cosseno;
    }
}
void Gear::rotate_y(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);

    for (int i = 0; i < this->vertices->get_size(); i++)
    {
        Vector3 old_pos = Vector3(*this->vertices->get(i));
        this->vertices->get(i)->x = old_pos.x * cosseno + old_pos.z * seno;
        this->vertices->get(i)->y = old_pos.y;
        this->vertices->get(i)->z = old_pos.z * cosseno - old_pos.x * seno;
    }
}
void Gear::rotate_z(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);

    for (int i = 0; i < this->vertices->get_size(); i++)
    {
        Vector3 old_pos = Vector3(*this->vertices->get(i));
        this->vertices->get(i)->x = old_pos.x * cosseno - old_pos.y * seno;
        this->vertices->get(i)->y = old_pos.x * seno + old_pos.y * cosseno;
        this->vertices->get(i)->z = old_pos.z;
    }
}
