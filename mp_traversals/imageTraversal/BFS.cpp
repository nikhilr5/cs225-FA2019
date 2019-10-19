#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;

  unsigned width = png_.width();
  unsigned height = png_.height();

  visited = new bool*[width];

  for (unsigned i = 0; i < width; ++i) {
    visited[i] = new bool[height];
  }

  for(unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < height; j++) {
      visited[i][j] = false;
    }
  }

  q_Point.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  BFS * a = new BFS(png_, start_, tolerance_);
   ImageTraversal:: Iterator returnRattor(*a, start_);
   return returnRattor;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return ImageTraversal:: Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  q_Point.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  Point returnP = q_Point.front();
  q_Point.pop();
  return returnP;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return q_Point.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  bool check = q_Point.empty();
  return check;
}

//added
PNG* BFS:: getPNG(){
  return &png_;
}

double BFS:: getTolerance() {
  return tolerance_;
}
