/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
     head_ = NULL;
     tail_ = NULL;
     length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode * tmp;
  //ListNode * current;
  //current = head_;
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  head_ = NULL;
  tail_ = NULL;
  tmp = NULL;

}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ > 0) {
    //null is now new Node1
    head_->prev = newNode;
    //newNode points to old head1
    newNode->next = head_;
    //making newNode head of list
    head_ = newNode;
    //newNode prev is null since new head
    newNode->prev = NULL;

  } else {
    head_ = newNode;
    tail_ = newNode;
    newNode->prev = NULL;
  }
  length_++;
  }

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
ListNode * newNode = new ListNode(ndata);
if (length_ > 0) {
  tail_->next = newNode;
  newNode->prev = tail_;
  newNode->next = NULL;
  tail_ = newNode;
} else {
  tail_ = newNode;
  head_ = newNode;
  newNode->next = NULL;

}
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  if ( splitPoint < 0) return start;
  if (splitPoint >= length_) return NULL;
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  int holdLength = length_;
  for (int i = 0; i < splitPoint; i++) {

    curr = curr->next;

  }
  curr->prev->next = NULL;
  curr->prev = NULL;
  //head_ = curr;

// start = curr;
// delete curr;
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>

void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_;
  ListNode * hold;
  int spot = 1;
  while (curr != tail_) {
    hold = curr->next;
    if(spot % 2 == 0) {
      //previous node pts to next node
      curr->prev->next = curr->next;
      //next node pts to previous node
      curr->next->prev = curr->prev;
      tail_->next = curr;
      curr->prev = tail_;
      curr->next = NULL;
      tail_ = curr;
    }
    spot++;
    //next node which we held b4 if statement
    curr = hold;
  }

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {

  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  }
  /// @todo Graded in MP3.2
  ListNode* prev = startPoint->prev;
  ListNode* curr = startPoint;
  ListNode* temp = curr;
  ListNode* front = startPoint;
  ListNode* back = endPoint;
  ListNode* endNext = endPoint->next;

  // curr->next = endNext;
  // curr->prev = temp;
  // curr = temp;

//int test = 0;

  while(curr != endPoint) {
    //holds next node
    temp = curr->prev;
    ListNode* temp2 = curr->next;
    //sets current pointing to prev
    curr->prev = curr->next;
    //sets prev to next node

    curr->next = temp;
    // std::cout << "226" << std::endl;
    curr = temp2;
  }
  //sets startPoint to old last node
  startPoint->next = endNext;
  endPoint->next = endPoint->prev;
  endPoint->prev = prev;

  if (startPoint->next != NULL) {
    startPoint->next->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
  if (endPoint->prev != NULL) {
    endPoint->prev->next = endPoint;
    // std::cout << "241" << std::endl;
  } else {

    head_ = endPoint;
  }

  startPoint = back;
  endPoint = front;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  if (length_ == 0) return;

  ListNode* temp1 = head_;
  ListNode* temp2 = head_;
  int sections = length_ / n;
  int counter = 1;
  for (int i = 0; i < sections; i++) {
    counter = 1;
    while (counter < n) {
        //move on to next one to create n tuple
      temp1 = temp1->next;
        //increase counter
      counter++;
    }
    //call reverse
    reverse(temp2, temp1);
    // reset temps
    temp2 = temp1->next;
    temp1 = temp1->next;
    }
    // for the extra if any left over
    while(temp1 != NULL && temp1 != tail_) {
      // std::cout << "times" << std::endl;
      temp1 = temp1->next;
    }
    //reverse for the extra nodes if any
    reverse(temp2,temp1);

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself+
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == NULL) return second;
  if (second == NULL) return first;

  ListNode * temp1 = first;
  ListNode * temp2 = second;
  ListNode * curr;
  ListNode * returnNode;


  if (temp1->data < temp2->data) {
    returnNode = temp1;
    temp1 = temp1->next;
  } else {
    returnNode = temp2;
    temp2 = temp2->next;
  }


  curr = returnNode;

while ( temp1 != NULL && temp2 != NULL) {

  //which ever data is less gets added to list
  if (temp1->data < temp2->data) {
    curr->next = temp1;
    temp1->prev = curr;
    temp1 = temp1->next;
  } else {
    curr->next = temp2;
    temp2->prev = curr;
    temp2 = temp2->next;
  }
  curr = curr->next;
}

//if one of the lists is empty
  if(temp1 == NULL && temp2 != NULL) {
    curr->next = temp2;
    temp2->prev = curr;
  }

  if(temp1 != NULL && temp2 == NULL) {
    curr->next = temp1;
    temp1->prev = curr;
  }
return returnNode;

}



/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (start == NULL) return NULL;
  if (start->next == NULL || chainLength < 2) {
    return start;
  }
  int newChainLength = chainLength/2;

  ListNode * center = split(start,newChainLength);
  return merge(mergesort(start, newChainLength), mergesort(center, chainLength - newChainLength));

}
