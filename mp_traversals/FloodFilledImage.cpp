#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  png_ = png;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  //adds each to respected vectors
  vTraversal.push_back(&traversal);
  vColorPicker.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker//HSLAPixel newPixel
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  PNG temp = png_;
   int count = 0;

  for (unsigned i = 0; i < vTraversal.size(); i++) {
    animation.addFrame(temp);

    for (const Point & p : *vTraversal[i]) {
      HSLAPixel & cur = temp.getPixel(p.x, p.y);
      cur = vColorPicker[i]->getColor(p.x,p.y);
      count++;
      if (count % frameInterval == 0) {
        animation.addFrame(temp);

      }

      //Point  p = *it;
      //HSLAPixel newPixel = newCol->getColor(p.x, p.y);
      //
      //oldPixel = newP;
      //count++;
    }
    animation.addFrame(temp);
  }

  return animation;
}

//ImageTraversal::Iterator it = newTrav->begin(); it != newTrav->end(); ++it
