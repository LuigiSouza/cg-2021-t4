#ifndef __ALGEBRA_H__
#define __ALGEBRA_H__

#include <cmath>
#include <iostream>

#include "Vector2.h"

// Auxiliar class to make calculus between points
class Algebra
{
public:
   // Get perpendicular points given a segment
   // between vec1 and vec2 and point (px, py)
   static Vector2 perpendicular(Vector2 vec1, Vector2 vec2, float px, float py);

   // Returns the rotate point giving (x, y)
   // and angle in radians
   static Vector2 rotate(float x, float y, float angle);

   // Get angle between (x1, y1) and x axys,
   // base_x and base _y is used to normalize values to (0, 0)
   static float getAngle(float x1, float y1, float base_x, float base_y);

   // Returns distance between two given points
   static float distance(float x1, float y1, float x2, float y2);

   /*
    * PNPOLY - Point Inclusion in Polygon Test
    * W. Randolph Franklin (WRF)
    * From: https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
   */
   static bool isInside(float x, float y, int n, float vx[], float vy[]);

   // Scale the value n from start1 to stop1 to a range between start2 and stop2
   static float map(float n, float start1, float stop1, float start2, float stop2);

   // Returns point q0 with quadratic bezier given three points and t
   static Vector2 quadratic_bezier(Vector2 p0, Vector2 p1, Vector2 p2, double t);
};

#endif
