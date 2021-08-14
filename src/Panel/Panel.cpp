#include "Panel.h"

Panel::Panel(float x, float y, float width, float height)
{
   coord_x = x;
   coord_y = y;
   this->width = width;
   this->height = height;
   r = g = b = 1;
}

Panel::~Panel()
{
   for (auto it = buttons.begin(); it != buttons.end(); ++it)
   {
      Botao *aux = *it;
      buttons.erase(it);
      delete aux;
   }
   buttons.clear();
}

void Panel::addButton(float _x, float _y, float _larg, float _alt, EnumBotao function, int rgb)
{
   _x += coord_x;
   _y += coord_y;
   buttons.push_front(new Botao(_x, _y, _larg, _alt, function, rgb));
}

bool Panel::insidePanel(Mouse mouse)
{
   return (mouse.getX() >= coord_x && mouse.getX() <= coord_x + width &&
           mouse.getY() >= coord_y && mouse.getY() <= coord_y + height);
}

Botao *Panel::buttonClicked(Mouse mouse)
{
   Botao *ret;
   for (auto it = buttons.begin(); it != buttons.end(); ++it)
   {
      if ((*it)->isInside(mouse))
      {
         ret = (*it);
         return ret;
      }
   }
   return nullptr;
}

void Panel::render()
{
   CV::color(r, g, b);
   CV::rectFill(coord_x, coord_y, coord_x + width, coord_y + height);
   CV::rect(coord_x, coord_y, coord_x + width, coord_y + height);

   for (auto it = buttons.begin(); it != buttons.end(); ++it)
   {
      (*it)->render();
   }
}
