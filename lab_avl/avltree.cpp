/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;

    temp->height = updateHeight(temp);
    t->height = updateHeight(t);

    //since reference
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;

    temp->height = updateHeight(temp);
    t->height = updateHeight(t);

    //since reference
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)

{
//std:: cout << "rebalance" << endl;
  if (subtree == NULL) {
    //NULL
    return;
  }
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (balance == -2) {
      //std:: cout << "balance = -2" << endl;
      int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if (l_balance == -1) {
        rotateRight(subtree);
      } else if(l_balance == 1){
        rotateLeftRight(subtree);
      }
    } else if (balance == 2) {
      //std:: cout << "balance = 2" << endl;
      int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (r_balance == 1) {
        rotateLeft(subtree);
        //std:: cout << "rotate left" << endl;
      } else if (r_balance == -1){
        rotateRightLeft(subtree);
      }
    }
    subtree->height = updateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value) {

    if(subtree == NULL) {
      Node * node = new Node(key, value);
      subtree = node;
    }

     else if (key < subtree->key) {
      insert(subtree->left,key, value);
    }
    else if(key >= subtree->key){
      insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* next = subtree->left;
          while (next->right != NULL) {
              next = next->right;
          }
          swap(subtree, next);
          remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp = NULL;
            if(subtree->left != NULL) {
              temp = subtree->left;
            } else {
              temp = subtree->right;
            }
            delete subtree;
            subtree = temp;
        }
        // your code here

    }
    rebalance(subtree);
}


template <class K, class V>
int AVLTree<K,V>:: updateHeight(Node * subtree) {
  if (!subtree) {
    return -1 ;
  }
  int leftTree = updateHeight(subtree->left);
  int rightTree = updateHeight(subtree->right);


  if (leftTree > rightTree) {
    return 1 + leftTree;
  } else {
    return 1 + rightTree;
  }
}
