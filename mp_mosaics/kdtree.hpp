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
     int curDim = Dim;
     int counter = 0;
     while (counter < curDim) {
       double dimDistance = target[counter] - potential[counter];
       dimDistance = dimDistance * dimDistance;
       totPot = totPot + dimDistance;
       counter++;
     }
     //totPot = sqrt(totPot);

     double totBest = 0.0;
     int counter2  = 0;
     while (counter2 < curDim) {
       double dimDistance = target[counter] - currentBest[counter];
       dimDistance = dimDistance * dimDistance;
       totBest = totBest + dimDistance;
       counter2++;
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
  Point<Dim> temp = query;

  helpFindNearNeigh(root, 0, temp, start);
  return start;
}

//helper
template <int Dim>
void KDTree<Dim>::helpFindNearNeigh(KDTreeNode* current, int dimension, Point<Dim> &query, Point<Dim> &best) const {
  if (current == NULL) {
    return;
  }

  KDTreeNode* next;
  KDTreeNode* other;

  if (smallerDimVal(current->point, query, dimension)) {
    next = current->right;
    other = current->left;
  } else {
    next = current->left;
    other = current->right;
  }

  if (shouldReplace(query, best, current->point)) {
    helpFindNearNeigh(next, (dimension + 1) % Dim, query, best);
  }

  double radius = 0.0;
  double distance;
  for (int i = 0; i < Dim; ++i) {
    radius = radius + ((query[i] - best[i]) * (query[i] - best[i]));
  }

  distance = (current->point[dimension] - query[dimension]) * (current->point[dimension] - query[dimension]);

  if (radius >= distance) {
    helpFindNearNeigh(other, (dimension + 1) % Dim, query, best);
  }
}


template <int Dim>
int KDTree<Dim>:: findPosition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIndex, int dimension) {
  Point<Dim> pivotPoint = newPoints[pivotIndex];
  Point<Dim> temp = newPoints[pivotIndex];
  newPoints[pivotIndex] = newPoints[right];
  newPoints[right] = temp;

  int holder = left;
  for (int i = left; i < right; ++i) {
    Point<Dim> possSmaller = newPoints[i];
    if (smallerDimVal(possSmaller, pivotPoint, dimension)) {
      Point<Dim> temp2 = newPoints[holder];
      newPoints[holder] = possSmaller;
      newPoints[i] = temp2;
      holder++;
    }
  }
  Point<Dim> temp3 = newPoints[holder];
  newPoints[holder] = newPoints[right];
  newPoints[right] = temp3;

  return holder;
}

template <int Dim>
Point<Dim> KDTree<Dim>::find(vector<Point<Dim>>& newPoints, int left, int right, int k, int dimension) {
  if(left == right) {
    return newPoints[right];
  }
  int pivotIndex = (left + right) / 2;
  int spot = findPosition(newPoints, left, right, pivotIndex, dimension);

  if (spot == k) {
    return newPoints[k];
  } else if (spot < k) {
    pivotIndex++;
    return find(newPoints, pivotIndex, right, k, dimension);
  } else {
    pivotIndex--;
    return find(newPoints, left, pivotIndex, k, dimension);
  }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode*  KDTree<Dim>:: makeTree(vector<Point<Dim>>& newPoints, int left, int right, int dimension) {
  if(left > right) return NULL;

  size_t middle = (left + right) / 2;


  Point<Dim> inserter = find(newPoints, left, right, middle, dimension);
  KDTreeNode* subRoot = new KDTreeNode(inserter);
  size++;

  int newDim = (dimension + 1) % Dim;

  subRoot->left = makeTree(newPoints, left, middle - 1, newDim);
  subRoot->right = makeTree(newPoints, middle + 1, right, newDim);


  return subRoot;
}

template <int Dim>
void KDTree<Dim>:: destory(KDTreeNode* subRoot) {
  if (root == NULL) return;

  destory(subRoot->left);
  destory(subRoot->right);
  delete subRoot;
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
