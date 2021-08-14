
#include "Algebra.h"

Vector2 Algebra::perpendicular(Vector2 vec1, Vector2 vec2, float px, float py)
{
   float k = ((vec2.y - vec1.y) * (px - vec1.x) - (vec2.x - vec1.x) * (py - vec1.y)) / ((vec2.y - vec1.y) * (vec2.y - vec1.y) + (vec2.x - vec1.x) * (vec2.x - vec1.x) * 1.0);

   return Vector2(px - k * (vec2.y - vec1.y) * 1.0,
                  py + k * (vec2.x - vec1.x) * 1.0);
}

Vector2 Algebra::rotate(float x, float y, float angle)
{
   return Vector2(x * cos(angle) - y * sin(angle),
                  x * sin(angle) + y * cos(angle));
}

float Algebra::getAngle(float x1, float y1, float base_x, float base_y)
{
   float vectorB_x = x1 - base_x;
   float vectorB_y = y1 - base_y;

   float vec_atan = atan2(vectorB_y, vectorB_x);
   return vec_atan;
}

/*
    * PNPOLY - Point Inclusion in Polygon Test
    * W. Randolph Franklin (WRF)
    * From: https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
   */
bool Algebra::isInside(float x, float y, int n, float vx[], float vy[])
{
   bool c = false;
   for (int i = 0, j = n - 1; i < n; j = i++)
   {
      if ((((vy[i] <= y) && (y < vy[j])) ||
           ((vy[j] <= y) && (y < vy[i]))) &&
          (x < (vx[j] - vx[i]) * (y - vy[i]) / (vy[j] - vy[i]) + vx[i]))
         c = !c;
   }
   return c;
}

float Algebra::distance(float x1, float y1, float x2, float y2)
{
   return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

float Algebra::map(float n, float start1, float stop1, float start2, float stop2)
{
   return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

Vector2 Algebra::quadratic_bezier(Vector2 p0, Vector2 p1, Vector2 p2, double t)
{
   return p0 * ((1 - t) * (1 - t)) + p1 * (2 * (1 - t) * t) + p2 * t * t;
}
