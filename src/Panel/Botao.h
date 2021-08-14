#ifndef __BOTAO_H__
#define __BOTAO_H__

#include "../gl_canvas2d.h"
#include "../Handles/HandleMouse.h"
#include "../Handles/Vector2.h"

#include "EnumBotao.h"

#include <string>
#include <iostream>

class Botao
{
private:
  float altura, largura, x, y;
  char label[100];

  float r, g, b;

  int elems;

  EnumBotao function;

public:
  Botao(float _x, float _y, float _larg, float _alt, EnumBotao function, int rgb);
  ~Botao();

  void render();

  bool isInside(Mouse mouse_state);

  float *get_rgb()
  {
    float *ret = new float[3];
    ret[0] = r;
    ret[1] = g;
    ret[2] = b;

    return ret;
  }
  // Sets functions of button
  EnumBotao get_function()
  {
    return this->function;
  }
  // Sets functions of button
  void set_function(EnumBotao function);

  void set_color(float r, float g, float b)
  {
    this->r = r;
    this->g = g;
    this->b = b;
  }

  void set_color(int i)
  {
    float *rgb = CV::get_color(i);
    this->r = rgb[0];
    this->g = rgb[1];
    this->b = rgb[2];
  }
};

#endif
