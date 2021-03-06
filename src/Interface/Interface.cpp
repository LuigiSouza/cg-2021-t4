#include "Interface.h"

void Interface::render(void)
{
    gear->render();

    panel->render();
}

void Interface::update(void)
{
    this->handle_mouse();

    angle_z += rotate_speed;
    angle_z = angle_z > PI_2 ? angle_z - PI_2 : angle_z;
    gear->rotate_z(angle_z);

    if (mouse->getCtrl())
        gear->rotate_x(angle_x);
    else
        gear->rotate_y(-angle_y);

    gear->matrix_view(*cam);
}

void Interface::handle_mouse(void)
{
    Botao *button = panel->buttonClicked(*mouse);
    if (mouse->isDown(0))
    {
        if (!button)
        {
            if (mouse->getCtrl())
                angle_x += mouse->moveY() / 100.0;
            else
                angle_y += mouse->moveX() / 100.0;
        }
    }
    if (mouse->pushed(0))
    {
        if (button)
        {
            switch (button->get_function())
            {
            case EnumBotao::minRadius:
                if (radius > DEFAULT_VALUE)
                {
                    radius -= 2;
                    gear->set_radius(radius);
                }
                break;
            case EnumBotao::maxRadius:
                if (radius < 80)
                {
                    radius += 2;
                    gear->set_radius(radius);
                }
                break;
            case EnumBotao::minTooth:
                if (tooths_num > 5)
                {
                    gear->set_tooths(--tooths_num);
                }
                break;
            case EnumBotao::maxTooth:
                if (tooths_num < 20)
                {
                    gear->set_tooths(++tooths_num);
                }
                break;
            case EnumBotao::minSizeTooth:
                if (size_tooth > DEFAULT_VALUE)
                {
                    size_tooth -= 5;
                    gear->set_size_tooth(size_tooth);
                }
                break;
            case EnumBotao::maxSizeTooth:
                if (size_tooth < 40)
                {
                    size_tooth += 5;
                    gear->set_size_tooth(size_tooth);
                }
                break;
            case EnumBotao::minThick:
                if (thickness > DEFAULT_VALUE)
                {
                    thickness -= 2;
                    gear->set_thickness(thickness);
                }
                break;
            case EnumBotao::maxThick:
                if (thickness < 80)
                {
                    thickness += 2;
                    gear->set_thickness(thickness);
                }
                break;
            case EnumBotao::minCrownSize:
                if (crown_size > DEFAULT_VALUE)
                {
                    crown_size -= 2;
                    gear->set_crown_size(crown_size);
                }
                break;
            case EnumBotao::maxCrownSize:
                if (crown_size < 80)
                {
                    crown_size += 2;
                    gear->set_crown_size(crown_size);
                }
                break;
            case EnumBotao::minSpeed:
                if (rotate_speed > -0.1)
                {
                    rotate_speed -= 0.005;
                }
                break;
            case EnumBotao::maxSpeed:
                if (rotate_speed < 0.1)
                {
                    rotate_speed += 0.005;
                }
                break;
            case EnumBotao::camStyle:
                cam->set_ortho(!cam->get_ortho());
                if (cam->get_ortho())
                    button->set_function(EnumBotao::camStyle, "ORTHOGRAPHIC");
                else
                    button->set_function(EnumBotao::camStyle, "PERSPECTIVE");
                break;
            case EnumBotao::toothType:
                is_flat = !is_flat;
                gear->set_type(is_flat);
                if (is_flat)
                    button->set_function(EnumBotao::toothType, "FLAT TOOTH");
                else
                    button->set_function(EnumBotao::toothType, "ROUND TOOTH");
                break;
            case EnumBotao::minInGap:
                in_gap -= 0.05;
                in_gap = std::min(std::max(0.1, (double)in_gap), 0.9);
                gear->set_in_gap(in_gap);
                break;
            case EnumBotao::maxInGap:
                in_gap += 0.05;
                in_gap = std::min(std::max(0.1, (double)in_gap), 0.9);
                gear->set_in_gap(in_gap);
                break;
            case EnumBotao::minOutGap:
                out_gap -= 0.05;
                out_gap = std::min(std::max(0.1, (double)out_gap), 0.9);
                gear->set_out_gap(out_gap);
                break;
            case EnumBotao::maxOutGap:
                out_gap += 0.05;
                out_gap = std::min(std::max(0.1, (double)out_gap), 0.9);
                gear->set_out_gap(out_gap);
                break;
            default:
                return;
                break;
            }
        }
        gear->create_gear();
    }
}

bool Interface::keyboard(int key)
{
    // std::cout << "key: " << key << std::endl;

    switch (key)
    {
    case 97: // a
        if (direction_x > -0.2)
        {
            direction_x -= 0.005;
            cam->set_direction_x(direction_x);
        }
        break;
    case 100: // d
        if (direction_x < 0.2)
        {
            direction_x += 0.005;
            cam->set_direction_x(direction_x);
        }
        break;
    case 101: // e
        break;
    case 102: // f
        if (direction_y > -0.2)
        {
            direction_y -= 0.005;
            cam->set_direction_y(direction_y);
        }
        break;
    case 113: // q
        break;
    case 114: // r
        if (direction_y < 0.2)
        {
            direction_y += 0.005;
            cam->set_direction_y(direction_y);
        }
        break;
    case 115: // s
        if (cam_z > 0)
        {
            cam_z -= 10;
            cam->set_center_z(cam_z);
        }
        break;
    case 119: // w
        if (cam_z < 50)
        {
            cam_z += 10;
            cam->set_center_z(cam_z);
        }
        break;
    case 120: // x
        break;
    case 122: // z
        break;
    case 214: // ctrl
        mouse->setCtrl(!mouse->getCtrl());
        break;
    case 27: // finaliza programa ap??s clicar duas vezes
        return true;
        break;
    }
    return false;
}
