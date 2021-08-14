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

int screenWidth = 1024, screenHeight = 768;

int GameState::total_darts = 6;

Mouse *mouse_state;

// Game State Manager
std::map<std::string, GameState *> gsm;
std::string current_state;

/***********************************************************
*
* Load/Create Functions
*
************************************************************/

void dispose()
{
   delete mouse_state;
   delete gsm["Game"];
   delete gsm["Menu"];
   delete gsm["GameOver"];
   gsm.clear();
   exit(0);
}

/***********************************************************
*
* Update Functions
*
************************************************************/

void update()
{
   gsm[current_state]->update(*mouse_state);
   if (gsm[current_state]->get_changeState() != current_state)
   {
      EnumBotao difficult = gsm[current_state]->getDifficult();
      std::list<int> points = gsm[current_state]->getPoints();

      current_state = gsm[current_state]->get_changeState();
      if (!gsm[current_state])
         dispose();
      if (current_state == "GameOver")
         gsm[current_state]->setPoints(points);

      gsm[current_state]->reset(difficult);
   }
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

   gsm[current_state]->render();

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
   gsm["Game"] = new Game(&screenWidth, &screenHeight);
   gsm["Menu"] = new Menu(screenWidth / 3, 200, screenWidth / 4, 400);
   gsm["GameOver"] = new GameOver(screenWidth / 3, 200, screenWidth / 4 + 20, 400);
   current_state = "Menu";

   CV::run();
}
