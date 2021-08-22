#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "../Entities/Gear.h"
#include "../Entities/Cam.h"

#include "../Handles/HandleMouse.h"
#include "../Handles/Algebra.h"
#include "../Handles/Vector2.h"
#include "../Handles/Vector3.h"

#include "../Panel/Botao.h"
#include "../Panel/Panel.h"

class Interface
{
private:
    int *screenWidth, *screenHeight;

    Mouse *mouse;
    Cam *cam;
    Gear *gear;
    Panel *panel;

    float radius = 50;
    float tooths_num = 10;
    float size_tooth = 30;
    float thickness = 60;
    float crown_size = 30;

    float in_gap = 0.3;
    float out_gap = 0.3;

    float angle_x = 0;
    float angle_y = 0;
    float angle_z = 0;

    float rotate_speed = 0.01;

    bool is_ortho = false;
    bool is_flat = true;

    float cam_angle = 0.0;
    float cam_x = 0;
    float cam_y = 0;
    float cam_z = 0;

    float direction_x = 0;
    float direction_y = 0;
    float direction_z = 10;

    void handle_mouse(void);

public:
    void update(void);
    void render(void);
    bool keyboard(int key);

    inline Interface(int *scr_w, int *scr_h, Mouse *_mouse);
    inline ~Interface();
};

Interface::Interface(int *scr_w, int *scr_h, Mouse *_mouse)
{
    this->screenWidth = scr_w;
    this->screenHeight = scr_h;
    this->mouse = _mouse;

    this->cam = new Cam(Vector3(cam_x, cam_y, cam_z), Vector3(direction_x, direction_y, direction_z), cam_angle, is_ortho);
    this->gear = new Gear(Vector3(375, 375, 200), radius, crown_size, tooths_num, size_tooth, thickness, is_flat, in_gap, out_gap);

    this->panel = new Panel(*screenWidth - 300, 0, 300, *screenHeight, true);
    panel->color(0.5, 0.5, 0.5);
    this->panel->addButton(100, *screenHeight - 100, 50, 50, true, EnumBotao::Text, 0, 0, "EDIT GEAR");
    this->panel->addButton(50, *screenHeight - 150, 100, 50, false, EnumBotao::minRadius, 0, 0, "-RADIUS");
    this->panel->addButton(160, *screenHeight - 150, 100, 50, false, EnumBotao::maxRadius, 0, 0, "+RADIUS");
    this->panel->addButton(50, *screenHeight - 210, 100, 50, false, EnumBotao::minTooth, 0, 0, "-TOOTH_N");
    this->panel->addButton(160, *screenHeight - 210, 100, 50, false, EnumBotao::maxTooth, 0, 0, "+TOOTH_N");
    this->panel->addButton(50, *screenHeight - 270, 100, 50, false, EnumBotao::minSizeTooth, 0, 0, "-TOOTH_S");
    this->panel->addButton(160, *screenHeight - 270, 100, 50, false, EnumBotao::maxSizeTooth, 0, 0, "+TOOTH_S");
    this->panel->addButton(50, *screenHeight - 330, 100, 50, false, EnumBotao::minThick, 0, 0, "-THICK");
    this->panel->addButton(160, *screenHeight - 330, 100, 50, false, EnumBotao::maxThick, 0, 0, "+THICK");
    this->panel->addButton(50, *screenHeight - 390, 100, 50, false, EnumBotao::minCrownSize, 0, 0, "-CROW_S");
    this->panel->addButton(160, *screenHeight - 390, 100, 50, false, EnumBotao::maxCrownSize, 0, 0, "+CROW_S");
    this->panel->addButton(50, *screenHeight - 450, 100, 50, false, EnumBotao::minSpeed, 0, 0, "-SPEED");
    this->panel->addButton(160, *screenHeight - 450, 100, 50, false, EnumBotao::maxSpeed, 0, 0, "+SPEED");
    this->panel->addButton(50, *screenHeight - 510, 100, 50, false, EnumBotao::minInGap, 0, 0, "-I_GAP");
    this->panel->addButton(160, *screenHeight - 510, 100, 50, false, EnumBotao::maxInGap, 0, 0, "+I_GAP");
    this->panel->addButton(50, *screenHeight - 570, 100, 50, false, EnumBotao::minOutGap, 0, 0, "-O_GAP");
    this->panel->addButton(160, *screenHeight - 570, 100, 50, false, EnumBotao::maxOutGap, 0, 0, "+O_GAP");
    this->panel->addButton(50, *screenHeight - 630, 210, 50, false, EnumBotao::camStyle, 0, 0, "PERSPECTIVE");
    this->panel->addButton(50, *screenHeight - 690, 210, 50, false, EnumBotao::toothType, 0, 0, "FLAT TOOTH");
}

Interface::~Interface()
{
    delete cam;
    delete mouse;
    delete gear;
    delete panel;
}

#endif
