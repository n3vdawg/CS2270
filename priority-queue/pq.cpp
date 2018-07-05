//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Your Name: Tyler Nevell


#include <string>
#include <iostream>
#include <vector>
#include "pq.h"

using namespace std;

pq* init_priority_queue() {
  // initialize pointer to new pq node
  pq* queue = new pq;
  // initialize data and next 
  queue->priority = -1;
  queue->next = NULL;
  queue->str = "";
  return queue;
}

// insert adds the given text to the queue, using the specified
// priority. If there is a tie, the given string should be placed at
// the back of the group that it ties with, so all other strings with
// this priority will be removed first.
void insert(pq* &queue, string text, float priority) {
  //BASE CASE
  /*if (queue == NULL) {
    queue->priority = priority;
    queue->str = text;
    queue->next = NULL;
    return; 
  }*/

  // initialize new node to have inputted properties
  
  pq* cursor = queue;
  
  // need to iterate through queue with a cursor
  // when we find a larger priority value, we need to put our ins_node
  // into the spot before our cursor. 
  int i = 0;
  pq* ins_node = new pq;      
  pq* prev_node = cursor;
  while (i < 1) {
    if (priority > cursor->priority) {
      if (cursor->next == NULL) {
        ins_node->priority = priority;
        ins_node->str = text;
        ins_node->next = NULL;
        // have cursor point to ins_node
        cursor->next = ins_node;
        return;
      }
      prev_node = cursor;
      cursor = cursor->next;
    }
    
    else if (priority <= cursor->priority) {
      // have ins_node point to cursor
      ins_node->priority = priority;
      ins_node->str = text;
      ins_node->next = cursor;
      prev_node->next = ins_node;
      return;
    }

  }
}

// remove will access the highest priority element in the queue,
// remove it from the queue, and return it. if the queue is empty it
// should return the empty string.
string remove(pq* &queue) {
  if (queue == NULL) {
    return "";
  }
  int i = 0;
  pq* cursor = queue;
  pq* prev_cur = cursor;
  // iterate through list
  while(i < 1) {
    // if our cursor->next is NULL, we've reached the end of our list
    // and we need to remove it and return it
    if (cursor->next == NULL) {
      prev_cur->next = NULL;
      return cursor->str;
    }
    // allows us to point to the node before cursor and then move on to the 
    // next node so we can keep track of what node needs to stop pointing
    // to our removed node
    prev_cur = cursor;
    cursor = cursor->next;
  }
}

// peek will access the highest priority element in the queue and
// return it without modifying the queue. if the queue is empty it
// should return the empty string.
string peek(pq* &queue) {
  if (queue == NULL) {
    return "";
  }

  // create while loop to iterate through whole list
  int i = 0;
  //initialize cursor
  pq* cursor = queue;
  while (i < 1) {
    if (cursor->next == NULL) {
      return cursor->str;
    }
    // move onto next node
    cursor = cursor->next;
  }
}
