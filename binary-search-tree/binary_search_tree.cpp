//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//

#include "binary_search_tree.h"

// init_node initializes a new bt_node from the heap using the given
// data, and two NULL children, and returns a pointer to it.
bt_node* init_node(int data) {
  bt_node* t = new bt_node;

  t->data = data;

  t->left = NULL;
  t->right = NULL;
  return t; 
}

// insert places the new_node in a proper location in the tree
// indicated by top, while obeying the invariant. On return, *top
// points to the root of the tree.
void insert(bt_node** top, bt_node* new_node) {
  
  
  if (new_node == NULL) {
    return;
  }
  // create a temp node to compare value to root of bt
  bt_node* root = *top;
  if (new_node->data < root->data) {
    if (root->left == NULL) {
      root->left = new_node;
      return;
    } else {
      // insert requires double pointer and root is only single, use & to go up one level
      return insert(&root->left, new_node);
    }
  }
  if (new_node->data > root->data) {
    if (root->right == NULL) {
      root->right = new_node;
      return;
    } else {
      return insert(&root->right, new_node);
    }
  }
}

// insert_data creates a new node with the given data value and
// inserts it similarly to insert().
void insert_data(bt_node** top, int data) {
  insert(top, init_node(data));
}

// remove removes a node from the tree whose data value matches the
// input. On return, *top points to the root of the tree. If no node
// in the tree contains the given data, this function has no effect.
void remove(bt_node** top, int data) {
  if (top == NULL) {
    return;
  }

  bt_node* cursor = *top;
  bool righto = false;
  bool lefto = false;
  bool not_found = true;

  // check if our root is node to remove
  if (cursor->data == data){
    bt_node* removal_node = cursor;
    // if there is a child to left, we find predecessor (left once, right until end)
    if (cursor->left != NULL){
      bt_node* tempcursor = cursor;
      cursor = cursor->left;
      
      //does a node to the right exist?
      if (cursor->right){
        righto = true;
      }

      // iterate through nodes to find root's predecessor
      while (cursor->right != NULL) {
        tempcursor = cursor;
        cursor = cursor->right;
      }
      // remove any right nodes
      if (righto) {
        // removal_node has left and right data, so only assign cursor's new data to it
        removal_node->data = cursor->data;
        // node we took data out of and assigned to our root needs to be deleted by referencing from 
        // the previos nodes location. We know it's to the right, so we point that way and set it to NULL
        tempcursor->right = NULL;
        return;
      
      } else {
        removal_node->data = cursor->data;
        tempcursor->data = tempcursor->left->data;
        tempcursor->left = NULL;
        return;
      }

    // if there is no left child, we need to find successor (right once, left until end)
    } else {
      bt_node* tempcursor = cursor;
      cursor = cursor->right;

      if (cursor->left){
        lefto = true;
      }

      while (cursor->left != NULL) {
        tempcursor = cursor;
        cursor = cursor->right;
      }

      if (lefto) {
        removal_node->data = cursor->data;
        tempcursor->left = NULL;
        return;
      } else {
        removal_node->data = cursor->data;
        tempcursor->data = tempcursor->right->data;
        tempcursor->right = NULL;
        return;
      }

    }
  
  }
  // a leaf or inner node needs to be removed
  
  // to iterate through the tree and find our node, need to user a tempcursor
  bt_node* tempcursor = cursor; 
  while (not_found) {
    // do we need to go left?
    if (data < cursor->data) {
      // while loop iterates until we find cursor that equals data
      if (cursor->data == data) {
        not_found = false; //exit loop
      } else {
        tempcursor = cursor;
        cursor = cursor->left;
      }
    } else { // we look right since it is larger
      if (cursor->data == data) {
        not_found = false;
      } else {
        tempcursor = cursor;
        cursor = cursor->right;
      }
    }
  } 
  // both our tempcursor and cursor (respectively will be at and before the node we need to remove
  bt_node* removal_node = cursor;

  // check if removal_node is a leaf. If not, continue past
  if (removal_node->right == NULL && removal_node->left == NULL) {
    if (removal_node->data < tempcursor->data) {
      tempcursor->left = NULL;
      return;
    } else {
      tempcursor->right = NULL;
      return;
    }
  }

  if (cursor->left != NULL){
      bt_node* tempcursor = cursor;
      cursor = cursor->left;
      
      //does a node to the right exist?
      if (cursor->right){
        righto = true;
      }

      // iterate through nodes to find root's predecessor
      while (cursor->right != NULL) {
        tempcursor = cursor;
        cursor = cursor->right;
      }
      // remove any right nodes
      if (righto) {
        // removal_node has left and right data, so only assign cursor's new data to it
        removal_node->data = cursor->data;
        // node we took data out of and assigned to our root needs to be deleted by referencing from 
        // the previos nodes location. We know it's to the right, so we point that way and set it to NULL
        tempcursor->right = NULL;
        return;
      
      } else {
        removal_node->data = cursor->data;
        tempcursor->data = tempcursor->left->data;
        tempcursor->left = NULL;
        return;
      }

    // if there is no left child, we need to find successor (right once, left until end)
    } else {
      bt_node* tempcursor = cursor;
      cursor = cursor->right;

      if (cursor->left){
        lefto = true;
      }

      while (cursor->left != NULL) {
        tempcursor = cursor;
        cursor = cursor->right;
      }

      if (lefto) {
        removal_node->data = cursor->data;
        tempcursor->left = NULL;
        return;
      } else {
        removal_node->data = cursor->data;
        tempcursor->data = tempcursor->right->data;
        tempcursor->right = NULL;
        return;
      }

    }
  
}

// contains returns true if any node in the subtree pointed to by t
// contains the given data value, false otherwise.
bool contains(bt_node* t, int data) {  
  if (t == NULL) {
    return false;
  }

  if (t->data == data) {
    return true;
  }
  if (data < t->data) {
    return contains(t->left, data);
  }
  
  if (data > t->data) {
    return contains(t->right, data);
  }
  return NULL;
}

// get_node searches through the subtree pointed to by t for a node that
// contains the given data value. If such a node is found, a pointer
// to it is returned. Otherwise this function returns NULL.
bt_node* get_node(bt_node* t, int data) {
  // 2. are we in a cant continue stage
  if (t == NULL) {
    return NULL;
  }

  // 1. do we have the answer?
  if (t->data == data) {
    return t;
  }

  // 3. can we subdivide and recurse more?
  if (data < t->data) {
    // look left
    return get_node(t->left, data);
  } else {
    // look right
    return get_node(t->right, data);
  }
}

// size returns the number of nodes in the subtree pointed to by t. If
// the tree is empty (t is NULL), it returns zero.
int size(bt_node* t) {
  if (t == NULL) {
    return 0;
  } else {
    return size(t->left) + size(t->right) + 1;
  }
}

// to_array fills an integer array to reflect the contents of the
// subtree pointed to by t. The filled array will be the same as the
// subtree's size (found with the size() function), and the order of
// the array elements are the same that is found during an inorder
// traversal of the subtree.
//
// Note: the array is created and sized before this function is
// called. You will have at least size(top) elements available, so you
// may safely index [0..size(t)-1].
void to_array(bt_node* t, int arr[]) {
  if(t == NULL){
    return;
  }

  to_array(t->left, arr);
  arr[t->data] = t->data;
  to_array(t->right, arr);
  return;
}
