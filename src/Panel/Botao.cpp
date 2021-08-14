#include "Botao.h"

Botao::Botao(float _x, float _y, float _larg, float _alt, EnumBotao function, int rgb)
{
   altura = _alt;
   largura = _larg;
   x = _x;
   y = _y;
   this->function = function;
   set_color(rgb);
   set_function(function);
}

Botao::~Botao()
{
}

void Botao::render()
{
   CV::color(r, g, b);
   CV::rectFill(x, y, x + largura, y + altura);
   CV::color(0, 0, 0);
   CV::text(x + 5, y + altura / 2, label); //escreve o label do botao mais ou menos ao centro.
}

bool Botao::isInside(Mouse mouse_state)
{
   if (mouse_state.getX() >= x && mouse_state.getX() <= (x + largura) && mouse_state.getY() >= y && mouse_state.getY() <= (y + altura))
   {
      return true;
   }
   return false;
}

void Botao::set_function(EnumBotao function)
{
   switch (function)
   {
   case EnumBotao::Jogar:
      sprintf(label, "Jogar");
      this->function = function;
      break;
   case EnumBotao::Facil:
      sprintf(label, "Facil");
      this->function = function;
      break;
   case EnumBotao::Dificil:
      sprintf(label, "Dificil");
      this->function = function;
      break;
   case EnumBotao::Menu:
      sprintf(label, "Menu");
      this->function = function;
      break;
   case EnumBotao::Sair:
      sprintf(label, "Sair");
      this->function = function;
      break;
   default:
      std::cout << std::endl
                << "Opcao Invalida..." << std::endl;
      exit(0);
      break;
   }
}
