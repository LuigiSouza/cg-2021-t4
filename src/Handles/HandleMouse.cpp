
#include "HandleMouse.h"

#include <iostream>

void Mouse::update(void)
{
   for (int i = 0; i < 3; i++)
   {
      this->prev_button[i] = this->button[i];
   }

   this->prev_pos_x = this->pos_x;
   this->prev_pos_y = this->pos_y;
}

void Mouse::setPress(int index)
{
   this->prev_button[index] = this->button[index];
   this->button[index] = !this->button[index];
}

bool Mouse::isDown(int index)
{
   return this->button[index];
}

bool Mouse::pushed(int index)
{
   return this->button[index] && !this->prev_button[index];
}

bool Mouse::released(int index)
{
   return !this->button[index] && this->prev_button[index];
}

void Mouse::setX(float x)
{
   this->prev_pos_x = this->pos_x;
   this->pos_x = x;
}
void Mouse::setY(float y)
{
   this->prev_pos_y = this->pos_y;
   this->pos_y = y;
}
float Mouse::getX(void) { return this->pos_x; }
float Mouse::getY(void) { return this->pos_y; }
float Mouse::getPrevX(void) { return this->prev_pos_x; }
float Mouse::getPrevY(void) { return this->prev_pos_y; }
float Mouse::moveX(void) { return this->pos_x - this->prev_pos_x; }
float Mouse::moveY(void) { return this->pos_y - this->prev_pos_y; }

void Mouse::setCtrl(bool ctrl) { this->ctrl = ctrl; }
bool Mouse::getCtrl(void) { return this->ctrl; }
