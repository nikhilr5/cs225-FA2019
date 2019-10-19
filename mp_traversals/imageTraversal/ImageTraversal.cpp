#include <cmath>
#include <iterator>
#include <iostream>
#include <list>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  current = Point(0,0);
}

ImageTraversal:: Iterator::Iterator(ImageTraversal & traversal, Point start) {
  traversal_ = &traversal;
  current = start;

}

/**
 * Iterator increment opreator.
 *
 *going in correct order
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

  current = traversal_->pop();
  Point right(current.x + 1, current.y);
  Point left(current.x - 1, current.y);
  Point below(current.x , current.y - 1);
  Point above(current.x + 1, current.y + 1);
  HSLAPixel & startPixel = traversal_->png_.getPixel(traversal_->start_.x, traversal_->start_.y);

//right
  if(right.x < traversal_->png_.width()) {
    if (traversal_->visited[right.x][right.y] == false) {
      HSLAPixel & pixel = traversal_->png_.getPixel(right.x, right.y);
      double delta = calculateDelta(startPixel, pixel);
      if (delta <= traversal_->tolerance_) {
        traversal_->add(right);
      }
    }
  }

  //below
  if(below.y < traversal_->png_.height()) {
    if (traversal_->visited[current.x][current.y - 1] == false) {
      HSLAPixel & pixel = traversal_->png_.getPixel(current.x, current.y - 1);
      double delta = calculateDelta(startPixel, pixel);
      if (delta <= traversal_->tolerance_) {
        traversal_->add(below);
      }
    }
  }

  //left
  if(left.x > 0) {
    if (traversal_->visited[current.x - 1][current.y] == false) {
      HSLAPixel & pixel = traversal_->png_.getPixel(current.x - 1, current.y);
      double delta = calculateDelta(startPixel, pixel);
      if (delta <= traversal_->tolerance_) {
        traversal_->add(left);
      }
    }
  }

  //above
  if(above.y > 0) {
    if (traversal_->visited[current.x][current.y + 1] == false) {
      HSLAPixel & pixel = traversal_->png_.getPixel(current.x, current.y + 1);
      double delta = calculateDelta(startPixel, pixel);
      if (delta <= traversal_->tolerance_) {
        traversal_->add(above);
      }
    }
  }


  traversal_->visited[current.x][current.y] = true;
  current = traversal_->peek();


  while(!(traversal_->pList.empty())){
    if (traversal_->visited[current.x][current.y] == true) {
      current = traversal_->pop();
      current = traversal_->peek();
    } else { break;}
  }

return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool returnOpp = (this->current == other.current);
  return !returnOpp;
}
