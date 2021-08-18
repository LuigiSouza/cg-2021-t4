#include "Interface.h"

void Interface::render(void)
{
    panel->render();
}

void Interface::update(void) {}

bool Interface::keyboard(int key)
{
    switch (key)
    {
    case 27: // finaliza programa após clicar duas vezes
        return true;
        break;
    }
    return false;
}
