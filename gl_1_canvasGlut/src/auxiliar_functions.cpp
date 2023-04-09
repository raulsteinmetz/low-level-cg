#include "auxiliar_functions.h"
#include "math.h"

int calc_position(float percent, int w_h, int screen_width, int screen_height) {
   if (w_h == 0) {
      return int(percent * screen_width / 100.0);
   }
   return int(percent * screen_height / 100.0);
}

int distance(int x0, int y0, int x1, int y1) {
   return int(sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}
