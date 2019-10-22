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
  unsigned hueNum = 2 * x + ((3 * x) * y);
  double hue = hueNum % 250;

  HSLAPixel pixel(hue, .7, .25);
  return pixel;
}
