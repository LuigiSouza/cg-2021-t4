#include "Gear.h"

void Gear::set_radius(float _rad)
{
    this->radius_in = _rad;
    this->radius_out = radius_in + crown_size;
    this->radius_tooth = radius_out + size_tooth;
}
void Gear::set_tooths(int _num)
{
    this->tooths = _num;
}
void Gear::set_size_tooth(float size)
{
    this->size_tooth = size;
    this->radius_tooth = radius_out + size_tooth;
}
void Gear::set_thickness(float thick)
{
    this->thickness = thick;
}
void Gear::set_crown_size(float size)
{
    this->crown_size = size;
    this->radius_out = radius_in + crown_size;
    this->radius_tooth = radius_out + size_tooth;
}
void Gear::set_type(bool flat)
{
    this->is_flat = flat;
}
void Gear::set_in_gap(float gap)
{
    this->size_gear_in = gap;
}
void Gear::set_out_gap(float gap)
{
    this->size_gear_out = gap;
}

void Gear::matrix_view(Cam cam)
{
    Vector3 c = cam.get_pos();
    Vector3 h = cam.get_head();
    Vector3 d = cam.get_direction();
    Vector3 n = cam.get_normal();
    float projection = cam.get_projection();
    DinamicArray<Vector3> *render_by = rendered ? this->vertices : this->vertices_draw;
    rendered = false;

    for (int i = 0; i < render_by->get_size(); i++)
    {
        Vector3 *pnt_render = vertices_draw->get(i);
        Vector3 pnt = *render_by->get(i);
        pnt.z += posz;
        pnt_render->x = pnt.x * n.x + pnt.y * n.y + pnt.z * n.z - (n.x * c.x + n.y * c.y + n.z * c.z);
        pnt_render->y = pnt.x * h.x + pnt.y * h.y + pnt.z * h.z - (h.x * c.x + h.y * c.y + h.z * c.z);
        pnt_render->z = pnt.x * d.x + pnt.y * d.y + pnt.z * d.z - (d.x * c.x + d.y * c.y + d.z * c.z);
        if (!cam.get_ortho())
        {
            pnt_render->x = pnt_render->x * ((projection / pnt_render->z));
            pnt_render->y = pnt_render->y * ((projection / pnt_render->z));
        }
    }
}

void Gear::create_gear(void)
{
    vertices->clear();
    vertices_draw->clear();

    float error = 0.0001;

    float increment = PI_2 / tooths * 0.5;
    double arc_out = increment * size_gear_out;
    double arc_in = increment * size_gear_in;
    double div_in = (arc_in + arc_in) / (double)DIV_IN;

    double distance_tooths = Algebra::distance(
        sin(-arc_out) * radius_tooth,
        cos(-arc_out) * radius_tooth,
        sin(arc_out) * radius_tooth,
        cos(arc_out) * radius_tooth);

    bool is_tooth = true;
    for (double tmp = 0; tmp < PI_2 - error; tmp += increment)
    {
        if (is_tooth)
        {
            if (is_flat)
            {
                vertices->add(Vector3(sin(tmp - arc_out) * radius_tooth, cos(tmp - arc_out) * radius_tooth, -thickness / 2.0));
                vertices->add(Vector3(sin(tmp + arc_out) * radius_tooth, cos(tmp + arc_out) * radius_tooth, -thickness / 2.0));
            }
            else
            {
                Vector2 rad_1 = Vector2(sin(tmp - arc_out) * radius_tooth, cos(tmp - arc_out) * radius_tooth);
                Vector2 rad_2 = Vector2(sin(tmp + arc_out) * radius_tooth, cos(tmp + arc_out) * radius_tooth);
                Vector2 rad_out_1 = Vector2(sin(tmp - increment + arc_in) * radius_out, cos(tmp - increment + arc_in) * radius_out);
                Vector2 rad_out_2 = Vector2(sin(tmp + increment - arc_in) * radius_out, cos(tmp + increment - arc_in) * radius_out);
                Vector2 vec_1 = rad_out_1 - rad_1;
                Vector2 vec_2 = rad_out_2 - rad_2;
                Vector2 perp_1 = Vector2(-vec_1.y, vec_1.x).normalized() * distance_tooths + rad_1;
                Vector2 perp_2 = Vector2(vec_2.y, -vec_2.x).normalized() * distance_tooths + rad_2;

                Vector2 *intersect = Algebra::intersect_point(perp_1, rad_1, perp_2, rad_2);
                if (intersect)
                {
                    double distance = Algebra::distance(rad_1, *intersect);
                    double angle = Algebra::getAngle(rad_2.x, rad_2.y, rad_1.x, rad_1.y, intersect->x, intersect->y);
                    double angle_begin = Algebra::getAngle(intersect->x, intersect->y + 10, rad_1.x, rad_1.y, intersect->x, intersect->y);

                    for (double i = 0; i <= angle; i += angle / DIV_TOOTH)
                    {
                        vertices->add(Vector3(sin(i - angle_begin) * distance + intersect->x, cos(i - angle_begin) * distance + intersect->y, -thickness / 2.0));
                    }

                    delete intersect;
                }
                else
                {
                    intersect = new Vector2((rad_1.x + rad_2.x) / 2.0, (rad_1.y + rad_2.y) / 2.0);
                    double distance = Algebra::distance(rad_1, *intersect);
                    double angle = PI;
                    double angle_begin = Algebra::getAngle(intersect->x, intersect->y + 10, rad_1.x, rad_1.y, intersect->x, intersect->y);

                    for (double i = 0; i <= angle; i += angle / DIV_TOOTH)
                    {
                        vertices->add(Vector3(sin(i - angle_begin) * distance + intersect->x, cos(i - angle_begin) * distance + intersect->y, -thickness / 2.0));
                    }
                }
            }
        }
        else
        {
            for (double i = tmp - arc_in; i <= tmp + arc_in + error; i += div_in)
            {
                vertices->add(Vector3(sin(i) * radius_out, cos(i) * radius_out, -thickness / 2.0));
            }
        }
        is_tooth = !is_tooth;
    }
    this->num_vertices = vertices->get_size();
    for (int i = 0; i < num_vertices; i++)
    {
        Vector3 other_side = *vertices->get(i);
        other_side.z = thickness / 2.0;
        vertices->add(Vector3(other_side));
    }
    double div = PI_2 / tooths;
    for (double i = 0; i < PI_2 - error; i += div)
    {
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, -thickness / 2.0));
    }
    for (double i = 0; i < PI_2 - error; i += div)
    {
        vertices->add(Vector3(sin(i) * radius_in, cos(i) * radius_in, thickness / 2.0));
    }
    for (int i = 0; i < vertices->get_size(); i++)
        vertices_draw->add(*vertices->get(i));
}

void Gear::render(void)
{
    CV::color(1, 1, 1);
    CV::translate(posx, posy);

    Vector3 *prev = vertices_draw->get(0);
    Vector3 *next;
    Vector3 *prev_z;

    // Connect front vertices with with themselves
    for (int i = 1; i < num_vertices; i++)
    {
        next = vertices_draw->get(i);
        CV::line(prev->x, prev->y, next->x, next->y);
        prev = next;
    }
    next = vertices_draw->get(0);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect back vertices with with themselves and with front vertices
    prev = vertices_draw->get(num_vertices);
    for (int i = 1; i < num_vertices; i++)
    {
        next = vertices_draw->get(i + num_vertices);
        CV::line(prev->x, prev->y, next->x, next->y);

        prev = vertices_draw->get(i + num_vertices - 1);
        prev_z = vertices_draw->get(i - 1);
        CV::line(prev->x, prev->y, prev_z->x, prev_z->y);

        prev = next;
    }

    next = vertices_draw->get(num_vertices);
    prev_z = vertices_draw->get(num_vertices - 1);
    CV::line(prev->x, prev->y, prev_z->x, prev_z->y);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect the inner circle vertices with with themselves
    prev = vertices_draw->get(2 * num_vertices);
    for (int i = 1; i < tooths; i++)
    {
        next = vertices_draw->get(i + 2 * num_vertices);
        CV::line(prev->x, prev->y, next->x, next->y);
        prev = next;
    }
    next = vertices_draw->get(2 * num_vertices);
    CV::line(prev->x, prev->y, next->x, next->y);

    // Connect the inner circle vertices with with themselves and with front vertices
    prev = vertices_draw->get(2 * num_vertices + tooths);
    for (int i = 1; i < tooths; i++)
    {
        next = vertices_draw->get(i + 2 * num_vertices + tooths);
        CV::line(prev->x, prev->y, next->x, next->y);

        prev = vertices_draw->get(i + 2 * num_vertices + tooths - 1);
        prev_z = vertices_draw->get(i + 2 * num_vertices - 1);
        CV::line(prev->x, prev->y, prev_z->x, prev_z->y);

        prev = next;
    }

    next = vertices_draw->get(2 * num_vertices + tooths);
    prev_z = vertices_draw->get(2 * num_vertices + tooths - 1);
    CV::line(prev->x, prev->y, prev_z->x, prev_z->y);
    CV::line(prev->x, prev->y, next->x, next->y);

    rendered = true;
    CV::translate(0, 0);
}

void Gear::rotate_x(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);
    DinamicArray<Vector3> *rotate_by = rendered ? this->vertices : this->vertices_draw;
    rendered = false;

    for (int i = 0; i < rotate_by->get_size(); i++)
    {
        Vector3 old_pos = *rotate_by->get(i);
        this->vertices_draw->get(i)->x = old_pos.x;
        this->vertices_draw->get(i)->y = old_pos.y * cosseno - old_pos.z * seno;
        this->vertices_draw->get(i)->z = old_pos.y * seno + old_pos.z * cosseno;
    }
}
void Gear::rotate_y(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);
    DinamicArray<Vector3> *rotate_by = rendered ? this->vertices : this->vertices_draw;
    rendered = false;

    for (int i = 0; i < rotate_by->get_size(); i++)
    {
        Vector3 old_pos = *rotate_by->get(i);
        this->vertices_draw->get(i)->x = old_pos.x * cosseno + old_pos.z * seno;
        this->vertices_draw->get(i)->y = old_pos.y;
        this->vertices_draw->get(i)->z = old_pos.z * cosseno - old_pos.x * seno;
    }
}
void Gear::rotate_z(float angle)
{
    float cosseno = cos(angle);
    float seno = sin(angle);
    DinamicArray<Vector3> *rotate_by = rendered ? this->vertices : this->vertices_draw;
    rendered = false;

    for (int i = 0; i < rotate_by->get_size(); i++)
    {
        Vector3 old_pos = *rotate_by->get(i);
        this->vertices_draw->get(i)->x = old_pos.x * cosseno - old_pos.y * seno;
        this->vertices_draw->get(i)->y = old_pos.x * seno + old_pos.y * cosseno;
        this->vertices_draw->get(i)->z = old_pos.z;
    }
}
