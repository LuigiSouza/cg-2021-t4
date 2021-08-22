#ifndef __PANEL_H__
#define __PANEL_H__

#include "Botao.h"
#include <list>

class Panel
{
private:
   /* data */
   float coord_x;
   float coord_y;
   float width;
   float height;

   std::list<Botao *> buttons;

   int color_control;

   float r, g, b;
   bool is_fill;

public:
   inline Panel(float x, float y, float width, float height, bool _fill);
   inline ~Panel();

   void addButton(float _x, float _y, float _larg, float _alt, bool fill, EnumBotao, int rgb, int rgb_text, const char *label);

   bool insidePanel(Mouse mouse);
   Botao *buttonClicked(Mouse mouse);

   void render();
   void color(float r, float g, float b)
   {
      this->r = r;
      this->g = g;
      this->b = b;
   }

   float getCoord_x(void)
   {
      return coord_x;
   }

   float getCoord_y(void)
   {
      return coord_y;
   }

   float getWidth(void)
   {
      return width;
   }

   float getHeight(void)
   {
      return height;
   }
};

Panel::Panel(float x, float y, float width, float height, bool _fill)
{
   coord_x = x;
   coord_y = y;
   this->width = width;
   this->height = height;
   this->is_fill = _fill;
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

#endif
