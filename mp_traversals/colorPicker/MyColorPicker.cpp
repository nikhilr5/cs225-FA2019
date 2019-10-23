#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  unsigned hueNum = 7 * x + ((4 * x) * y);
  double hue = hueNum % 250;

  HSLAPixel pixel(hue, .7, .25);
  return pixel;
}
