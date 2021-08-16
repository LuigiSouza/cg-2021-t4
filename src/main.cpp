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

#include "Entities/Gear.h"

#include "Handles/HandleMouse.h"
#include "Handles/Vector2.h"
#include "Handles/Vector3.h"

int screenWidth = 1024, screenHeight = 768;

Mouse *mouse_state;
Gear *engrenagem;

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

float clock = 0;
void update()
{
   mouse_state->update();

   clock += 0.01;
   clock = clock <= PI_2 ? clock : clock - PI_2;
}

/***********************************************************
*
* Canvas Functions
*
************************************************************/

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()

void render()
{
   CV::clear(0, 0, 0);

   CV::translate(400, 300);
   engrenagem->render();
   engrenagem->rotate_x(0.01);
   engrenagem->rotate_y(0.001);
   engrenagem->rotate_z(0.05);

   CV::translate(600, 500);

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
   CV::init(&screenWidth, &screenHeight, "3D Gears");

   engrenagem = new Gear(50, 30, 10, 60);
   mouse_state = new Mouse();

   CV::run();
}
