/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  if (curDim < 0 || curDim >= Dim) {
    return false;
  }

  bool returnBool;
  if (first[curDim] == second[curDim]) {
    returnBool = first < second;
  } else {
  returnBool = first[curDim] < second[curDim];
 }
  return returnBool;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{

     double totPot = 0.0;
     for (int i = 0; i < Dim; i++) {
       double dimDistance = target[i] - potential[i];
       dimDistance = dimDistance * dimDistance;
       totPot = totPot + dimDistance;
     }
     //totPot = sqrt(totPot);

     double totBest = 0.0;
     for (int i = 0; i < Dim; i++) {
       double dimDistance = target[i] - currentBest[i];
       dimDistance = dimDistance * dimDistance;
       totBest = totBest + dimDistance;
     }
     //totBest = sqrt(totBest);

     if (totPot == totBest) {
       return potential < currentBest;
     } else if (totPot < totBest) {
       return true;
     }
     return false;


}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{

  if (newPoints.empty()) {
    root = NULL;
    size = 0;
  } else {
    vector<Point<Dim>> points = newPoints;
    size = 0;
    root = makeTree(points, 0, points.size() - 1, 0);
  }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  copy(root, other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  destory(root);
  copy(root, rhs->root);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  destory(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  Point<Dim> start = root->point;
  //since query cosnt
  Point<Dim> temp = query;

  helpFindNearNeigh(root, 0, temp, start);

  //start becomes the best matching neighbor
  return start;
}

//helper
template <int Dim>
void KDTree<Dim>::helpFindNearNeigh(KDTreeNode* current, int dimension, Point<Dim> &query, Point<Dim> &best) const {

  if (current == NULL) {
    return;
  }

  KDTreeNode* nextNode;
  KDTreeNode* possNode;

  if (smallerDimVal(query, current->point, dimension)) {
    //since value at point's dimension is greater than query move to left of sorted kd tree
    nextNode = current->left;
    possNode = current->right;
  } else {
    nextNode = current->right;
    possNode = current->left;
  }

  //goes to bottom of tree first
  helpFindNearNeigh(nextNode, (dimension + 1) % Dim, query, best);

  //checks if current point is closer to query than the current best
  if (shouldReplace(query, best, current->point)) {
    //replaces if so
    best = current->point;
  }

  double area = 0.0;
  double curPDistance = 0.0;
  for (int i = 0; i < Dim; ++i) {
    //creates area of current best to query
    area = area + ((query[i] - best[i]) * (query[i] - best[i]));
  }

  //gets the distance of the current point to query
  curPDistance = (current->point[dimension] - query[dimension]) * (current->point[dimension] - query[dimension]);

  //if distance is inside that area
  if (curPDistance <= area) {
    //go down the other part of the tree that hasn't been visited to look at potential options
    helpFindNearNeigh(possNode, (dimension + 1) % Dim, query, best);
  }
}


//returns position of pivot in vector
//sorts elements into ones less than pivot and greater than (less than group < pivot < greaterthan group)
template <int Dim>
int KDTree<Dim>:: findPosition(vector<Point<Dim>>& newPoints, int left, int right, size_t rotPoint, int dimension) {
  Point<Dim> rotPointVal = newPoints[rotPoint];

  //sets pivot to end
  swap(newPoints[rotPoint], newPoints[right]);
  // Point<Dim> temp = newPoints[pivotIndex];
  // newPoints[pivotIndex] = newPoints[right];
  // newPoints[right] = temp;

  int holder = left;

  for (int i = left; i < right; ++i) {
    if (smallerDimVal(newPoints[i], rotPointVal, dimension)) {
      //group ones greater than pivot
      swap(newPoints[holder], newPoints[i]);
      holder++;
    }
  }
  swap(newPoints[right], newPoints[holder]);

  return holder;
}



template <int Dim>
Point<Dim> KDTree<Dim>::find(vector<Point<Dim>>& newPoints, int left, int right, size_t k, int dimension) {
  //return the kth smallest value in vector
  if(left == right) {
    return newPoints[right];
  }
  //start at center
  size_t rotPoint = findPosition(newPoints, left, right, (left + right) / 2, dimension);
  //rotPoint how large the element is compared to others in the vector
  if (rotPoint == k) {

    return newPoints[k];
  } else if (k < rotPoint) {
    //move down vec
    rotPoint--;
    return find(newPoints, left, rotPoint, k, dimension);
  } else {
    //move up
    rotPoint++;
    return find(newPoints, rotPoint, right, k, dimension);
  }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode*  KDTree<Dim>:: makeTree(vector<Point<Dim>>& newPoints, int left, int right, int dimension) {
  if(left > right) return NULL;

  // top of root must be the value in btw
  size_t middle = (left + right) / 2;


  Point<Dim> inserter = find(newPoints, left, right, middle, dimension);
  KDTreeNode* subRoot = new KDTreeNode(inserter);
  size++;

  //raps dim around so no out of bound
  int newDim = (dimension + 1) % Dim;

  subRoot->left = makeTree(newPoints, left, middle - 1, newDim);
  subRoot->right = makeTree(newPoints, middle + 1, right, newDim);


  return subRoot;
}

template <int Dim>
void KDTree<Dim>:: destory(KDTreeNode*& subRoot) {
  if (subRoot == NULL) return;

  destory(subRoot->left);
  destory(subRoot->right);
  delete subRoot;
  subRoot = NULL;
}

template <int Dim>
void KDTree<Dim>:: copy(KDTreeNode*& curr, KDTreeNode *& other) {
  if (other == NULL) {
    return;
  }

  curr = new KDTreeNode(other->point);
  copy(curr->left, other->left);
  copy(curr->right, other->right);
}
