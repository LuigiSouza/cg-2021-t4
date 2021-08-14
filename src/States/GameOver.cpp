#include "GameOver.h"

void GameOver::render(void)
{
    panel->render();

    char label[50];

    CV::color(0, 0, 0);
    sprintf(label, "Baloes Estourados: %.2d / %.2d", poped_balloons, total_balloons);
    CV::text(panel->getCoord_x() + 8, panel->getCoord_y() + panel->getHeight() - 20, label);
    sprintf(label, "Dardos Utilizados: %.2d / %.2d", used_darts, total_darts);
    CV::text(panel->getCoord_x() + 8, panel->getCoord_y() + panel->getHeight() - 40, label);
}

void GameOver::update(Mouse mouse)
{
    if (mouse.pushed(0))
    {
        Botao *button = panel->buttonClicked(mouse);
        if (!button)
            return;
        switch (button->get_function())
        {
        case EnumBotao::Menu:
            this->change_state = "Menu";
            break;
        case EnumBotao::Sair:
            this->change_state = "Sair";
            break;
        default:
            break;
        }
    }
}

GameOver::GameOver(float x, float y, float width, float height)
{
    this->change_state = this->name_state = "GameOver";
    this->used_darts = this->poped_balloons = this->total_balloons = 0;

    panel = new Panel(x, y, width, height);
    panel->addButton(width / 3, 200, 80, 50, EnumBotao::Menu, 3);
    panel->addButton(width / 3, 100, 80, 50, EnumBotao::Sair, 5);

    difficult = EnumBotao::Facil;
}

GameOver::~GameOver()
{
    delete panel;
}
