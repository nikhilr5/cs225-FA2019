#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
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

  pQueue.push(start);

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  DFS * a = new DFS(png_, start_, tolerance_);
  ImageTraversal:: Iterator returnRattor(*a, start_);
  return returnRattor;

}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  pQueue.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  Point returnP = pQueue.front();
  //remove from queue
  pQueue.pop();

  return returnP;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  return pQueue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  bool check = pQueue.empty();
  return check;
}

//added methods

PNG* DFS:: getPNG(){
  return &png_;
}

double DFS:: getTolerance() {
  return tolerance_;
}
