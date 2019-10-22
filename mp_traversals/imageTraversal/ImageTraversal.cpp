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
  traversal_ = NULL;
  isEmpty = true;
}

ImageTraversal:: Iterator::Iterator(ImageTraversal & traversal, Point start, PNG png, double tolerance, bool ** visited) {
  traversal_ = &traversal;
  start_ = start;
  isEmpty = false;
  current = traversal_->peek();
  png_ = png;
  visited_ = visited;
  tolerance_ = tolerance;

}

/**
 * Iterator increment opreator.
 *
 *going in correct order
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  //std:: cout<< "(" << current.x <<" , " <<current.y << ")" << std:: endl << std::endl;
  Point tempCur = traversal_->pop();
  traversal_->setVisited(current.x, current.y);


  Point right(tempCur.x + 1, tempCur.y);
  Point left(tempCur.x - 1, tempCur.y);
  // 0,0 is upper left
  Point below(tempCur.x , tempCur.y + 1);
  Point above(tempCur.x, tempCur.y - 1);
  HSLAPixel & startPixel = png_.getPixel(start_.x, start_.y);

//right
  if(right.x < png_.width()) {
    //std:: cout << "gettting in right" <<  std::endl;
      HSLAPixel & pixel = png_.getPixel(right.x, right.y);
      double delta = calculateDelta(startPixel, pixel);
      //std:: cout << "delta: " <<  delta << " tolerance : " << tolerance_ << std::endl;
      if (delta < tolerance_) {
        //std:: cout << "tolerance right" <<  std::endl;
        traversal_->add(right);
      }

  }

  //below
  if(below.y < png_.height()) {
    //std:: cout << "gettting in below" <<  std::endl;
      HSLAPixel & pixel = png_.getPixel(below.x, below.y);
      double delta = calculateDelta(startPixel, pixel);
      //std:: cout << "delta: " <<  delta << " tolerance : " << tolerance_ << std::endl;
      if (delta < tolerance_) {
        //std:: cout << "tolerance below" <<  std::endl;
        traversal_->add(below);
      }

  }

  //left
  if(left.x < png_.width()) {
    //std:: cout << "gettting in left" <<  std::endl;
      HSLAPixel & pixel = png_.getPixel(left.x, left.y);
      double delta = calculateDelta(startPixel, pixel);
      //std:: cout << "delta: " <<  delta << " tolerance : " << tolerance_ << std::endl;
      if (delta < tolerance_) {
        //std:: cout << "tolerance left" <<  std::endl;
        traversal_->add(left);
      }

  }

  //above
  if(above.y < png_.height()) {
    //std:: cout << "gettting in above" <<  std::endl;
      HSLAPixel & pixel = png_.getPixel(above.x, above.y);
      double delta = calculateDelta(startPixel, pixel);
      //std:: cout << "delta: " <<  delta << " tolerance : " << tolerance_ << std::endl;
      if (delta < tolerance_) {
        //std:: cout << "tolerance above" <<  std::endl;
        traversal_->add(above);
      }

  }

  while(!(traversal_->empty()) && (traversal_->getVisited(traversal_->peek().x, traversal_->peek().y))){
    //std:: cout << "front: " << traversal_->peek()
    traversal_->pop();

  }
  if (traversal_->empty()) {
    isEmpty = true;
    return *this;
  } else {
    current = traversal_->peek();
    //start_ = current;
    return *this;
}
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool returnOpp = isEmpty && other.isEmpty;
  return !returnOpp;
}
