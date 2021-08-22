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
  float text_r, text_g, text_b;

  int elems;
  bool is_fil;

  EnumBotao function;

public:
  inline Botao(float _x, float _y, float _larg, float _alt, bool fill, EnumBotao function, int rgb, int rgb_text, const char *label);
  inline ~Botao();

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
  void set_function(EnumBotao function, const char *label);

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
    delete rgb;
  }

  void set_color_text(int i)
  {
    float *rgb = CV::get_color(i);
    this->text_r = rgb[0];
    this->text_g = rgb[1];
    this->text_b = rgb[2];
    delete rgb;
  }
};

Botao::Botao(float _x, float _y, float _larg, float _alt, bool fill, EnumBotao function, int rgb, int rgb_text, const char *_label)
{
  altura = _alt;
  largura = _larg;
  x = _x;
  y = _y;
  this->is_fil = fill;
  this->function = function;
  set_color(rgb);
  set_color_text(rgb_text);
  set_function(function, _label);
}

Botao::~Botao()
{
}

#endif
