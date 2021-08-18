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

    this->cam = new Cam(Vector3(-200, -100, 0), Vector3(0, 0, 1), 0.0, true);
    this->gear = new Gear(Vector3(-200, -100, 800), 50, 30, 10, 60, false);

    this->panel = new Panel(*screenWidth - 300, 0, 300, *screenHeight, true);
    panel->color(0.5, 0.5, 0.5);
    this->panel->addButton(100, *screenHeight - 150, 50, 50, true, EnumBotao::Text, 0, 0, "EDIT GEAR");
    this->panel->addButton(50, *screenHeight - 210, 100, 50, false, EnumBotao::Other, 0, 0, "-RADIUS");
    this->panel->addButton(160, *screenHeight - 210, 100, 50, false, EnumBotao::Other, 0, 0, "+RADIUS");
    this->panel->addButton(50, *screenHeight - 270, 100, 50, false, EnumBotao::Other, 0, 0, "-TOOTH_N");
    this->panel->addButton(160, *screenHeight - 270, 100, 50, false, EnumBotao::Other, 0, 0, "+TOOTH_N");
    this->panel->addButton(50, *screenHeight - 330, 100, 50, false, EnumBotao::Other, 0, 0, "-TOOTH_S");
    this->panel->addButton(160, *screenHeight - 330, 100, 50, false, EnumBotao::Other, 0, 0, "+TOOTH_S");
    this->panel->addButton(50, *screenHeight - 390, 100, 50, false, EnumBotao::Other, 0, 0, "-THICK");
    this->panel->addButton(160, *screenHeight - 390, 100, 50, false, EnumBotao::Other, 0, 0, "+THICK");
    this->panel->addButton(50, *screenHeight - 450, 100, 50, false, EnumBotao::Other, 0, 0, "-CROW_S");
    this->panel->addButton(160, *screenHeight - 450, 100, 50, false, EnumBotao::Other, 0, 0, "+CROW_S");
    this->panel->addButton(50, *screenHeight - 510, 100, 50, false, EnumBotao::Other, 0, 0, "-SPEED");
    this->panel->addButton(160, *screenHeight - 510, 100, 50, false, EnumBotao::Other, 0, 0, "+SPEED");
    this->panel->addButton(50, *screenHeight - 600, 210, 50, false, EnumBotao::Other, 0, 0, "FLAT TOOTH");
    this->panel->addButton(50, *screenHeight - 660, 210, 50, false, EnumBotao::Other, 0, 0, "UPDATE");
}

Interface::~Interface()
{
    delete cam;
    delete mouse;
    delete gear;
    delete panel;
}

#endif
