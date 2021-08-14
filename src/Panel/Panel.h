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

public:
   Panel(float x, float y, float width, float height);
   ~Panel();

   void addButton(float _x, float _y, float _larg, float _alt, EnumBotao, int rgb);

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

#endif
