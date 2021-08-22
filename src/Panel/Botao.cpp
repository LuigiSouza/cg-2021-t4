#include "Botao.h"

void Botao::render()
{
   CV::color(r, g, b);
   if (!is_fil)
      CV::rect(x, y, x + largura, y + altura);
   else if (function != EnumBotao::Text)
      CV::rectFill(x, y, x + largura, y + altura);
   CV::color(text_r, text_g, text_b);
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

void Botao::set_function(EnumBotao function, const char *_label)
{
   switch (function)
   {
   case EnumBotao::Text:
   case EnumBotao::Other:
   case EnumBotao::minRadius:
   case EnumBotao::maxRadius:
   case EnumBotao::minTooth:
   case EnumBotao::maxTooth:
   case EnumBotao::minSizeTooth:
   case EnumBotao::maxSizeTooth:
   case EnumBotao::minThick:
   case EnumBotao::maxThick:
   case EnumBotao::minCrownSize:
   case EnumBotao::maxCrownSize:
   case EnumBotao::minSpeed:
   case EnumBotao::maxSpeed:
   case EnumBotao::camStyle:
   case EnumBotao::toothType:
   case EnumBotao::minInGap:
   case EnumBotao::maxInGap:
   case EnumBotao::minOutGap:
   case EnumBotao::maxOutGap:
      sprintf(label, _label);
      this->function = function;
      break;
   default:
      std::cout << std::endl
                << "Opcao Invalida..." << std::endl;
      exit(0);
      break;
   }
}
