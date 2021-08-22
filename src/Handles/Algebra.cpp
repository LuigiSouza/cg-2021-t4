
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

float Algebra::getAngle(float x1, float y1, float x2, float y2, float base_x, float base_y)
{
   float vectorA_x = x1 - base_x;
   float vectorA_y = y1 - base_y;
   float vectorB_x = x2 - base_x;
   float vectorB_y = y2 - base_y;

   float dot_product = vectorA_x * vectorB_x + vectorA_y * vectorB_y * 1.0;
   float croos_product = vectorA_x * vectorB_y - vectorA_y * vectorB_x * 1.0;
   float angle = atan2(fabs(croos_product), dot_product);

   return croos_product < 0 ? 6.28318530717 - angle : angle;
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

float Algebra::distance(Vector2 v1, Vector2 v2)
{
   return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) * 1.0);
}

float Algebra::distance(Vector3 v1, Vector3 v2)
{
   return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2) * 1.0);
}

float Algebra::map(float n, float start1, float stop1, float start2, float stop2)
{
   return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

Vector2 Algebra::quadratic_bezier(Vector2 p0, Vector2 p1, Vector2 p2, double t)
{
   return p0 * ((1 - t) * (1 - t)) + p1 * (2 * (1 - t) * t) + p2 * t * t;
}

/*
    *  Based on an algorithm in Andre LeMothe's "Tricks of the Windows Game Programming Gurus"
   */
Vector2 *Algebra::intersect_point(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3)
{
   Vector2 s1 = p1 - p0;
   Vector2 s2 = p3 - p2;

   double s = (-s1.y * ((p0 - p2).x) + s1.x * ((p0 - p2).y)) / (-s2.x * s1.y + s1.x * s2.y);
   double t = (s2.x * ((p0 - p2).y) - s2.y * ((p0 - p2).x)) / (-s2.x * s1.y + s1.x * s2.y);

   // Collision detected
   if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
   {
      return new Vector2((p0.x + t * s1.x), (p0.y + (t * s1.y)));
   }

   return nullptr; // No collision
}
