/*

  linked_list.cpp

 */

// AUTHOR: Tyler
// WHAT: CSCI 2270 Assignment 1
// COLLABORATORS: Cody H.

#include "linked_list.h"

using namespace std;

// create a new node structure that points to NULL and holds the
// provided integer. return a pointer to that new node.
node* init_node(int data) {
  node* ret = new node;
  // data element inside the ret node
  ret->data = data;
  // don't know what the next element is, so return null
  ret->next = NULL;
  return ret;
}

// create a space-separated string representing the contents of the
// list, in the same order they are found beginning from the head of
// the list. return that string object.  For example, this might
// return "" (the empty string) if the list is empty, or it might
// return "1 7 3" or "1 7 3 " (note the space at the end, you can have
// that there and it is OK).
string report(node* head) {
  string message = "";

  node* cursor = head;

  while (cursor != NULL) {
    // *cursor would give two inputs into to_string
    message += to_string(cursor->data) + " ";
    cursor = cursor->next;
  }
  
  return message;
}

// insert an integer into the list pointed to by top. the resulting
// list is one element longer, and the newly appended node has the
// given data value. consider using the 'append' function to help.
void append_data(node** top, int data) {
  append(top, init_node(data));
}

// this is the same as append_data, except we're adding a node, rather
// than a value. 
void append(node** top, node* new_node) {
  if (*top == NULL) {
    *top = new_node;
  } else {
    node* cursor = *top;
    while (cursor->next != NULL) {
      cursor = cursor->next;
    }
    // adds a new node onto the end. Basically cursor points to the new node which doesn't exist and adds that new_node there
    cursor->next = new_node;
  }
}

// similar to append_data. insert a new node that contains the given
// data value, such that the new node occupies the offset
// indicated. Any nodes that were already in the list at that offset
// and beyond are shifted down by one. For example if the list
// contains 23, 74, 93, and we insert 42 at index 1, the resulting
// list should be 23, 42, 74, 93.
void insert_data(node** top, int offset, int data) {
  insert(top, offset, init_node(data));
}

// this is the same as insert_data, except we're inserting a node,
// rather than a value.
void insert(node** top, int offset, node* new_node) {
  int i = 0;

  if (offset == 0) {
    // next attribute of new_node is pointing towards where top points
    // *top is the address that top points to. We want new_node to point at that same address
    // allows the new_node to hook onto the linked list chain at the beginning
    new_node->next = *top;
    // now the top node needs to point at the new_node
    // so we do below
    *top = new_node;
    return;
  } else {
    // initialize cursor
    node* cursor = *top;
    // iterate through list and insert new node
    while (i < (offset - 1)) {
      cursor = cursor->next;
      i = i + 1;
    }
    node* before = cursor;
    node* after = cursor->next;
    // before's pointer is now pointing to new node
    before->next = new_node;
    new_node->next = after;
  }
  return;
}

// remove the node indicated by the given offset. For example if our
// list contains 23, 74, 93, and we remove offset 1, the resulting
// list should then contain 23, 93.
void remove(node** top, int offset) {
  int i = 0;

  if (offset == 0) {
    // can't delete top but we need to delete the node top points to. 
    // have the pointer point at the same node as top since, it's our first one,
    node* j = *top;
    *top = j->next;
    delete j;
    return;
  } else {
    // need to start node at head
    node* cursor = *top;
    while(i < (offset-1)) {
      cursor = cursor->next;
      i = i + 1;
    }
    node* before_del = cursor;
    node* deleter = cursor->next;
    node* after_del = deleter->next;
    before_del->next = after_del;
    delete deleter; 
  }
  return;
}

// report the number of nodes in the linked list pointed to by head.
int size(node* head) {
  if (head == NULL) {
    return 0;
  }
  
  int i = 0;
  node* cursor = head;
  while(cursor != NULL) {
    i = i + 1;
    cursor = cursor->next;
  }
  return i;
}

// return true if the linked list pointed to by head contains a node
// with the specified value.
bool contains(node* head, int data) {
  bool ins = false;
  if (head == NULL) {
    return ins;
  }
  node* cursor = head;
  while(cursor != NULL) {
    if (cursor->data == data) {
      ins = true;
    }
    cursor = cursor->next;
  }
  return ins;
}
