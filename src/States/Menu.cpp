#include "Menu.h"

void Menu::render(void)
{
    panel->render();
}

void Menu::update(Mouse mouse)
{
    if (mouse.pushed(0))
    {
        Botao *button = panel->buttonClicked(mouse);
        if (!button)
            return;
        switch (button->get_function())
        {
        case EnumBotao::Jogar:
            this->change_state = "Game";
            break;
        case EnumBotao::Facil:
            button->set_function(EnumBotao::Dificil);
            this->difficult = EnumBotao::Dificil;
            break;
        case EnumBotao::Dificil:
            button->set_function(EnumBotao::Facil);
            this->difficult = EnumBotao::Facil;
            break;
        case EnumBotao::Sair:
            this->change_state = "Sair";
            break;
        default:
            break;
        }
    }
}

Menu::Menu(float x, float y, float width, float height)
{
    this->change_state = this->name_state = "Menu";

    this->poped_balloons = this->total_balloons = this->used_darts = 0;

    panel = new Panel(x, y, width, height);
    panel->addButton(width / 3, height - 100, 80, 50, EnumBotao::Jogar, 3);
    panel->addButton(width / 3, height - 200, 80, 50, EnumBotao::Facil, 13);
    panel->addButton(width / 3, height - 300, 80, 50, EnumBotao::Sair, 2);

    difficult = EnumBotao::Facil;
}

Menu::~Menu()
{
    delete panel;
}
