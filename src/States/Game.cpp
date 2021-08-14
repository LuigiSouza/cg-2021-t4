#include "Game.h"

void Game::render_background(void)
{
    int i;
    float j;
    for (i = *screenHeight, j = 0; i >= 0; i--, j += (255.f / *screenHeight) / 255.f)
    {
        CV::color(j, j * 1.5, 1);
        CV::line(0, i, *screenWidth, i);
    }
}

void Game::render(void)
{
    render_background();
    cannon->render(this->difficult == EnumBotao::Facil);

    CV::color(1, 1, 1);
    char label[50];
    sprintf(label, "Estourados: %.3d / %.3d", poped_balloons, total_balloons);
    CV::text(50, *screenHeight - 30, label);
    sprintf(label, "Dardos restantes: %.3d / %.3d", used_darts, total_darts);
    CV::text(300, *screenHeight - 30, label);

    for (auto it = balloons.begin(); it != balloons.end(); ++it)
        (*it)->render();
}

void Game::update(Mouse mouse)
{
    if (mouse.pushed(0))
        cannon->dragCannon(mouse);
    else if (mouse.released(0))
    {
        bool shoot = cannon->shotDart();
        this->used_darts = shoot ? this->used_darts + 1 : this->used_darts;
    }

    cannon->update(mouse);
    for (auto it = balloons.begin(); it != balloons.end(); ++it)
    {
        bool pop = (*it)->update(cannon->getDartArrow());
        this->poped_balloons = pop ? this->poped_balloons + 1 : this->poped_balloons;
    }

    if (cannon->getState() == CannonState::Stop && (this->used_darts == this->total_darts || this->poped_balloons == this->total_balloons))
        this->change_state = "GameOver";
}

void Game::reset(EnumBotao difficult)
{
    GameState::reset(difficult);
    cannon->reset();
    for (auto it = balloons.begin(); it != balloons.end(); ++it)
        (*it)->reset();
    poped_balloons = 0;
    used_darts = 0;
}

Game::Game(int *_screenWidth, int *_screenHeight)
{
    this->screenWidth = _screenWidth;
    this->screenHeight = _screenHeight;

    this->change_state = this->name_state = "Game";

    this->poped_balloons = this->used_darts = 0;

    this->cannon = new Cannon(200, 350);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            if (balloons_grid[i][j] == 0)
                continue;
            Balloon *balloon = new Balloon(350 + (10 * 2 * Balloon::getSize()) - (j * 2 * Balloon::getSize()), 100 + (10 * 2 * Balloon::getSize()) - (i * 2 * Balloon::getSize()));
            balloon->set_random_color(((i + 1) * 5) * ((j + 2) * 7));
            this->balloons.push_back(balloon);
        }

    this->total_balloons = balloons.size();
}

Game::~Game()
{
    delete cannon;
    for (auto it = balloons.begin(); it != balloons.end(); ++it)
    {
        Balloon *aux = *it;
        balloons.erase(it);
        delete aux;
    }
    balloons.clear();
}
