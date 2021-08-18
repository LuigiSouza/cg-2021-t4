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
#include "Entities/Cam.h"
#include "States/Interface.h"

#include "Handles/HandleMouse.h"
#include "Handles/Algebra.h"
#include "Handles/Vector2.h"
#include "Handles/Vector3.h"

int screenWidth = 1024, screenHeight = 768;

Mouse *mouse_state;
Interface *interface;

/***********************************************************
*
* Load/Create Functions
*
************************************************************/

void dispose()
{
   delete interface;
   delete mouse_state;
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
   interface->update();
}

/***********************************************************
*
* Canvas Functions
*
************************************************************/

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis
//globais que podem ser setadas pelo metodo keyboard()
float clockx = 0;
float clocky = 0;
float clockz = 0;
float posz = 0;
void render()
{
   CV::clear(0, 0, 0);

   interface->render();

   // // cam->set_center(Vector3(0, mouse_state->getX(), 0));
   // if (mouse_state->isDown(0))
   // {
   //    clockx += 0.01;
   //    clockx = clockx <= PI_2 ? clockx : clockx - PI_2;
   // }
   // if (mouse_state->isDown(1))
   // {
   //    clocky += 0.01;
   //    clocky = clocky <= PI_2 ? clocky : clocky - PI_2;
   // }
   // if (mouse_state->isDown(2))
   // {
   //    clockz += 0.01;
   //    clockz = clockz <= PI_2 ? clockz : clockz - PI_2;
   // }
   // engrenagem->rotate_z(clockz);
   // engrenagem->rotate_x(clockx);
   // engrenagem->rotate_y(clocky);
   // // engrenagem->rotate_z(Algebra::map(mouse_state->getX(), 0, screenHeight, 0, PI));
   // // engrenagem->rotate_x(Algebra::map(mouse_state->getY(), 0, screenHeight, 0, PI));
   // // engrenagem->rotate_z(Algebra::map(mouse_state->getX(), 0, screenWidth, 0, PI_div_4));
   // engrenagem->matrix_view(*cam);
   // engrenagem->render();
   // engrenagem->rotate_x(0.01);

   update();
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   bool exit = interface->keyboard(key);

   if (exit)
      dispose();
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

   mouse_state = new Mouse();
   interface = new Interface(&screenWidth, &screenHeight, mouse_state);

   CV::run();
}
