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
- Modelagem de engrenagem tipo spur gear
- Animação (rotação)
- Visualização ortográfica e perspectiva (sob vários ângulos) em wireframe
- Parametrização do número de dentes e raios

/------------------------------------------------------------------------
 *
 * Funções extras implementadas:
 *
- Engrenagem tipo spur gear com lado plano e curvo
- Edição livre de todos os parâmetros utilizados na engrenagem
- Interface para edição da engrenagem
- Rotação em diferentes ângulos com o mouse
- Sistema de FPS

************************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>

#include "gl_canvas2d.h"

#include "Entities/Cam.h"
#include "Handles/HandleMouse.h"

#include "Interface/Interface.h"
#include "Interface/Frames.h"

int screenWidth = 1024, screenHeight = 768;

Mouse *mouse_state;
Interface *interface;

// Fps variables
Frames *fps;

/***********************************************************
*
* Load/Create Functions
*
************************************************************/

void dispose()
{
   delete interface;
   delete mouse_state;
   delete fps;
   exit(0);
}

/***********************************************************
*
* Update Functions
*
************************************************************/

void update()
{
   interface->update();
   mouse_state->update();
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

   update();

   interface->render();

   fps->render();
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key)
{
   if (interface->keyboard(key))
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
   fps = new Frames(10, screenHeight - 20);

   CV::run();
}
