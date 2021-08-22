#include "Panel.h"

void Panel::addButton(float _x, float _y, float _larg, float _alt, bool fill, EnumBotao function, int rgb, int rgb_text, const char *label)
{
   _x += coord_x;
   _y += coord_y;
   buttons.push_front(new Botao(_x, _y, _larg, _alt, fill, function, rgb, rgb_text, label));
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
   if (is_fill)
      CV::rectFill(coord_x, coord_y, coord_x + width, coord_y + height);
   else
      CV::rect(coord_x, coord_y, coord_x + width, coord_y + height);
   CV::rect(coord_x, coord_y, coord_x + width, coord_y + height);

   for (auto it = buttons.begin(); it != buttons.end(); ++it)
   {
      (*it)->render();
   }
}
