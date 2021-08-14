/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp

//  Todos os arquivos do projeto devem ser .cpp
//
//  Versao 2.0
//
// *********************************************************************/

// Luigi Perotti Souza - 201910462

/***********************************************************************
 *
 * Funções básicas implementadas:
 *
- Classes em C++ para definição de vetores e transformações geométricas
- Sistema do controle do canhão
- Sistema de movimentação do projétil. De preferência utilize o mouse para isso.
- Colisão do projétil com os alvos (círculos)
- Controle da direção do canhão
- Controle da força de disparo

/------------------------------------------------------------------------
 *
 * Funções extras implementadas:
 *
- Sistemas de GameStates

************************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

#include "gl_canvas2d.h"

#include "Handles/HandleMouse.h"

#include "States/Game.h"
#include "States/Menu.h"
#include "States/GameOver.h"
#include "Handles/Vector2.h"

int screenWidth = 1024, screenHeight = 768;

int GameState::total_darts = 6;
Mouse *mouse_state;

/***********************************************************
*
* Load/Create Functions
*
************************************************************/

void dispose()
{
   exit(0);
}

/***********************************************************
*
* Update Functions
*
************************************************************/

void update()
{
   mouse_state->update();
}

/***********************************************************
*
* Canvas Functions
*
************************************************************/

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
float clock = 0;
void render()
{
   CV::clear(0, 0, 0);

   CV::translate(400, 300);

   int claws = 8;
   int size_in = 40;
   int size_out = 60;
   int size_claw = 60;
   float div = 0.01;
   bool is_claw = true;
   for (float tmp = 0; tmp <= PI_2; tmp += PI_2 / claws / 2)
   {
      Vector2 p_in = Vector2(sin(tmp + clock - div), cos(tmp + clock - div));
      CV::line(p_in.x * size_in, p_in.y * size_in, p_in.x * size_out, p_in.y * size_out);
      if (is_claw)
      {
         float next_tmp = tmp + PI_2 / claws / 2;
         for (float i = tmp; i <= next_tmp; i += div)
            CV::circleFill(sin(i + clock) * size_out, cos(i + clock) * size_out, 1, 4);
      }
      else
      {
         float next_tmp = tmp + PI_2 / claws / 2;
         for (float i = tmp; i <= next_tmp; i += div)
            CV::circleFill(sin(i + clock) * size_in, cos(i + clock) * size_in, 1, 4);
      }
      is_claw = !is_claw;
   }
   clock += 0.01;
   clock = clock <= PI_2 ? clock : 0;
   CV::circleFill(sin(clock) * size_out, cos(clock) * size_out, 4, 4);

   CV::translate(0, 0);

   update();
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   bool fecha = true;
   switch (key)
   {
   case 27: // finaliza programa após clicar duas vezes
      if (fecha)
      {
         dispose();
      }
      break;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   // printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction, x, y);

   mouse_state->setX(x);
   mouse_state->setY(y);

   if (state != -2)
      mouse_state->setPress(button);
}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "More Bloons");

   mouse_state = new Mouse();

   CV::run();
}
