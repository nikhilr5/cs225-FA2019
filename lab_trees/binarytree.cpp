/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;


    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
  mirror(root);
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) {
  if (subRoot == NULL) {
    return;
  }
  mirror(subRoot->left);
  mirror(subRoot->right);
  Node * temp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = temp;



}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */

 //every element after in either equal to or greater than the prev one
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    InorderTraversal<int>  a(root);
    int previousElem;
    for (TreeTraversal<int>:: Iterator i = a.begin(); i != a.end(); ++i) {
      if ((*i)->elem >= previousElem) {
        previousElem = (*i)->elem;
      } else {return false;}
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  std::vector<T> vector;
  // Node* tmp;
   isOrderedRecursive(root, vector);
   for (unsigned i = 0; i < vector.size() - 1; ++i) {
     // tmp = queue.front();
     // queue.pop();
     if (vector[i] >= vector[i + 1]) {
       return false;
     }
   }
   return true;
}

//helper
template <typename T>
void BinaryTree<T>::isOrderedRecursive(Node *subRoot, std::vector<T>& treeVector) const{
  if (subRoot == NULL) {
    return;
  }
  isOrderedRecursive(subRoot->left, treeVector);
  treeVector.push_back(subRoot->elem);
  isOrderedRecursive(subRoot->right, treeVector);
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    std:: vector<T> temp;
    getPaths(paths, temp, root);
    return;
}

//helper
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& path,
  std::vector<T>  singlePath, Node * subRoot) const {
    if (subRoot == NULL) return;

    singlePath.push_back(subRoot->elem);
    if (!subRoot->right && !subRoot->left) {
      path.push_back(singlePath);
      //go up one node for next path
      singlePath.pop_back();
    }
    getPaths(path, singlePath, subRoot->left);
    getPaths(path, singlePath, subRoot->right);
}



/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int zed = 0;
    return sumDistances(root, zed);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* subRoot, int currentDistance) const {
  if (subRoot == NULL) return 0;
  int returnDistance = currentDistance + sumDistances(subRoot->left, currentDistance + 1)
    + sumDistances(subRoot->left, currentDistance + 1);


  return returnDistance;
}
