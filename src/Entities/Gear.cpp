#include "Gear.h"

void Gear::create_gear(void)
{
    float increment = PI_2 / claws * 0.5;
    double arc_out = increment * size_gear_out;
    double div_out = (arc_out + arc_out) / DIV;
    double arc_in = increment * size_gear_in;
    double div_in = (arc_in + arc_in) / DIV;

    double distance_claws = Algebra::distance(
        sin(-arc_out) * radius_claw,
        cos(-arc_out) * radius_claw,
        sin(arc_out) * radius_claw,
        cos(arc_out) * radius_claw);
    std::cout << " " << distance_claws << std::endl;

    bool is_claw = true;
    for (float tmp = 0; tmp <= PI_2; tmp += increment)
    {
        if (is_claw)
        {
            if (is_flat)
            {
                vertices->add(Vector3(sin(tmp - arc_out) * radius_claw, cos(tmp - arc_out) * radius_claw, -thickness / 2.0));
                vertices->add(Vector3(sin(tmp + arc_out) * radius_claw, cos(tmp + arc_out) * radius_claw, -thickness / 2.0));
            }
            else
            {
                Vector2 rad_1 = Vector2(sin(tmp - arc_out) * radius_claw, cos(tmp - arc_out) * radius_claw);
                Vector2 rad_2 = Vector2(sin(tmp + arc_out) * radius_claw, cos(tmp + arc_out) * radius_claw);
                Vector2 rad_out_1 = Vector2(sin(tmp - increment + arc_in) * radius_out, cos(tmp - increment + arc_in) * radius_out);
                Vector2 rad_out_2 = Vector2(sin(tmp + increment - arc_in) * radius_out, cos(tmp + increment - arc_in) * radius_out);
                Vector2 vec_1 = rad_out_1 - rad_1;
                Vector2 vec_2 = rad_out_2 - rad_2;
                Vector2 perp_1 = Vector2(-vec_1.y, vec_1.x).normalized() * distance_claws + rad_1;
                Vector2 perp_2 = Vector2(vec_2.y, -vec_2.x).normalized() * distance_claws + rad_2;

                Vector2 *intersect = Algebra::intersect_point(perp_1, rad_1, perp_2, rad_2);
                if (intersect)
                {
                    double distance = Algebra::distance(rad_1.x, rad_1.y, intersect->x, intersect->y);
                    double angle = Algebra::getAngle(rad_2.x, rad_2.y, rad_1.x, rad_1.y, intersect->x, intersect->y);
                    double angle_begin = Algebra::getAngle(intersect->x, intersect->y + 10, rad_1.x, rad_1.y, intersect->x, intersect->y);

                    for (double i = 0; i <= angle; i += angle / 4.0)
                    {
                        vertices->add(Vector3(sin(i - angle_begin) * distance + intersect->x, cos(i - angle_begin) * distance + intersect->y, -thickness / 2.0));
                    }

                    delete intersect;
                }
                else
                {
                    intersect = new Vector2((rad_1.x + rad_2.x) / 2.0, (rad_1.y + rad_2.y) / 2.0);
                    double distance = Algebra::distance(rad_1.x, rad_1.y, intersect->x, intersect->y);
                    double angle = PI;
                    double angle_begin = Algebra::getAngle(intersect->x, intersect->y + 10, rad_1.x, rad_1.y, intersect->x, intersect->y);

                    for (double i = 0; i <= angle; i += angle / 4.0)
                    {
                        vertices->add(Vector3(sin(i - angle_begin) * distance + intersect->x, cos(i - angle_begin) * distance + intersect->y, -thickness / 2.0));
                    }
                }
            }
        }
        else
        {
            for (double i = tmp - arc_in; i <= tmp + arc_in; i += div_in)
            {
                vertices->add(Vector3(sin(i) * radius_out, cos(i) * radius_out, -thickness / 2.0));
            }
        }
        is_claw = !is_claw;
    }
    this->num_vertices = vertices->get_size();
    for (int i = 0; i < num_vertices; i++)
    {
        Vector3 other_side = *vertices->get(i);
        other_side.z = thickness / 2.0;
        vertices->add(Vector3(other_side));
    }
    double div = PI_2 / claws;
    for (double i = 0; i <= PI_2; i += div)
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, -thickness / 2.0));
    for (double i = 0; i <= PI_2; i += div)
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, thickness / 2.0));
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

    // Connect the inner circle vertices with with themselves
    prev = vertices->get(2 * num_vertices);
    for (int i = 1; i < claws; i++)
    {
        next = vertices->get(i + 2 * num_vertices);
        CV::line(prev->x, prev->y, next->x, next->y);
        prev = next;
    }
    next = vertices->get(2 * num_vertices);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect the inner circle vertices with with themselves and with front vertices
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
