// btree.cpp

// Tyler's B-TREE INVARIANTS:
/* 
  1. Every node has at most m slots for children
  2. Every internal node has at least ceil(m/2) children
  3. The root node has at least two children if it is not also a leaf
  4. A non-leaf node that currently has k keys must have k+1 children
  5. All leaves appear in the same level
  6. The keys within a node must be sorted in ascending order
  
  Additional HW Invariants
  
  7. A node's is_leaf property is true for leaves, false otherwise
  8. Keys are unique; inserting duplicates will silently fail
   */

// NOTE TO READERS: Remove and part of Insert are incomplete at this time and will be revisited in the near future



#include <iostream>
#include "btree.h"

using namespace std;

// insert adds the given key into a b-tree rooted at 'root'.  If the
// key is already contained in the btree this should do nothing.
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or remove)
// -- the btree pointed to by 'root' is valid.
void insert(btree*& root, int key) {
  // call find() func to determine what node our key needs to be inserted into
  btree* ins_node = find(root, key);
  // Scenario 1: The key we insert already exists
  // Use FOR loop to iterate through entire node to examine 
  // whether key already exists
  for (int i = 0; i < ins_node->num_keys; i++) {
    // if key at index i is same as input key, return
    if (ins_node->keys[i] == key) {
      return;
    }
  }
  // scenario 
  
  // The node we insert into is a leaf
  // check IF ins_node is a leaf
  if (ins_node->is_leaf == true) {
    
    // The node is not full
    // check ins_node->num_keys property
    // IF ins_node->num_keys is < BTREE_ORDER - 1 (max number of keys)
    if (ins_node->num_keys < BTREE_ORDER - 1) {

      // set i = to num_keys so we can iterate down through each index
      int i = ins_node->num_keys - 1;
      cout << ins_node->num_keys << endl;
      // IF our key is greater than the last element, insert into i+1 index
      cout << ins_node->keys[i] << endl;
      if (key > ins_node->keys[i]) {
        ins_node->keys[i+1] = key;
        ins_node->num_keys += 1;
        return;
      } 
      
      else {
        // iterate down through our list using a WHILE loop until our i reaches
        // reaches the last index and while our key is still larger than the key
        // found at index i        
        int i = ins_node->num_keys - 1;
        while (i >= 0 && key < ins_node->keys[i]) {
          // copy key found at index i into index i+1
          
          ins_node->keys[i+1] = ins_node->keys[i];
          // decrement i by 1
          i -= 1;
        }  
        // once we've reached our index, insert key into index after that location,
        // since we'll be at the value where our key is > than index elt
        ins_node->keys[i+1] = key;
        ins_node->num_keys += 1;
        return;      
      }
    }

    // IF ins_node is a full node, we must split
    // move median up 
    // split rest into two nodes
    if (ins_node->num_keys == BTREE_ORDER - 1) {
      cout << "full node" << endl;
      // allocate mem for new btree node
      btree* temp = new btree;
      temp->num_keys = 0;
      temp->is_leaf = true;
      for (int i=0; i <= BTREE_ORDER; i++) {
        temp->children[i] = NULL;
      }
      int j = 0;
      // iterate down through our list using a WHILE loop until our i reaches
      // reaches the last index and while our key is still larger than the key
      // found at index i        
      int idx = ins_node->num_keys - 1;
      cout << key << endl;
      while (idx >= 0 && key < ins_node->keys[idx]) {
        // copy key found at index i into index i+1
        ins_node->keys[idx+1] = ins_node->keys[idx];
        // decrement i by 1
        cout << ins_node->keys[idx+1] <<"fart" << endl;
        idx -= 1;
      }
      ins_node->keys[idx+1] = key;
      ins_node->num_keys += 1;
      /*for (int k = 0; k < ins_node->num_keys; k++) {
        cout << ins_node->keys[k]<< "burp" << endl;
      }*/
      // insert keys from +1 of our median into temp node 
      for (int i = (BTREE_ORDER/2)+1; i < ins_node->num_keys; i++) {
        // start at j=0, temp[0] = ins_node[3] 
        temp->keys[j] = ins_node->keys[i];
        cout << temp->keys[j] << "foo" << endl;
        // iterate to next key; temp->keys[j+1]
        j += 1;
      }
      temp->num_keys = j;
      int med_key = ins_node->keys[(BTREE_ORDER/2)];
      // for root
      ins_node->num_keys = j;
      idx = root->num_keys - 1;
      cout << med_key << endl;
      
      // check if our key being moved up is < 
      if (med_key < root->keys[idx]) {  
        while (med_key < root->keys[idx]) {
          // copy key found at index i into index i+1
          root->keys[idx+1] = root->keys[idx];
          root->children[idx+2] = root->children[idx+1];
          // decrement i by 1
          cout << root->keys[idx+1] <<"fart" << endl;
          cout << root->keys[idx] << "idx" << endl;
          cout << idx << endl;
          idx -= 1;
        }
        root->keys[idx+1] = med_key;
        root->num_keys += 1;
        root->children[idx + 2] = temp;
        for (int k = 0; k < root->num_keys; k++) {
        cout << root->keys[k]<< "burp" << endl;
        }
        cout << idx << endl;
      }
      
    }  
  }
}

// remove deletes the given key from a b-tree rooted at 'root'. If the
// key is not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void remove(btree*& root, int key) {
  btree* re_node = find(root, key);

  // our node is a leaf
  // Iterate through node with a for loop to check if key exists
  // within our node
  if (re_node->is_leaf == true) {  
    for (int i = 0; i < re_node->num_keys; i++) {
      // check if current index contains key
      if (key == re_node->keys[i]) {
        // move all keys after idx-th position one place backward
        for (int j = i + 1; j < re_node->num_keys; ++j) {
          re_node->keys[j-1] = re_node->keys[j];
        }
        // decrement count of keys
        re_node->num_keys -= 1;
        return;
      }
    }
  }
  // 
}

/*
void split_node(btree*& root, int j) {
  // z is a newly created node
  btree* z;
  // y is root's jth child
  btree* y = root->children[j];

  z->is_leaf = y->is_leaf;

  int t = (y->num_keys + 1;

  z->
}*/


// find locates the node that either: (a) currently contains this key,
// or (b) the node that would contain it if we were to try to insert
// it.  Note that this always returns a non-null node.
btree* find(btree*& root, int key) {
  // initiate counter
  int i = 0;
  // initiate cursor
  btree* cursor = root;
  // find smallest index such that our find key < key[i] in our current node
  // iterate through current node with i while key > keys[i] and i is <= size of node
  // if find key is not in our node, i = num_keys (number of keys in our node/node size)
  while (i < cursor->num_keys && key > cursor->keys[i]) {
    i++;
  }
  // IF we are still within our array of keys in our current node
  // && IF we have discovered the key, return pointer to key's node
  if (i < cursor->num_keys && key == cursor->keys[i]) {
    return cursor;
  }
  // ELSE, IF cursor is a leaf, and we've iterated through all our keys
  // there must not be a duplicate of our find key.
  // return the node
  else if (cursor->is_leaf == true) {
    return cursor;
  }
  // IF cursor is not a leaf, and we need to recursively call find()
  // to search the next appropriate child node
  // if the key < current keys[i], go down link to children[i]
  // and recursively search for our key (our link to the node with keys < our key[i])
  if (key < cursor->keys[i]) {    
    // return cursor and key recursively
    // both cursor and key have been initiallized
    // do not bother defining them with btree*& and int
    return find(cursor->children[i], key);
  } 
  // ELSE, the key is > keys[i-1] (i-1 because i = node size + 1 and we are at the last link) and we travel
  // down link to children[i] and recursively search this child node for our key
  else if (key > cursor->keys[i-1]) {
    return find(cursor->children[i], key);
  }
}

// count_nodes returns the number of nodes referenced by this
// btree. If this node is NULL, count_nodes returns zero; if it is a
// root, it returns 1; otherwise it returns 1 plus however many nodes
// are accessable via any valid child links.
int count_nodes(btree*& root) {
  // if our b-tree contains literally nothing, return 0
  if (root == NULL) {
    return 0;
  }
  int counter = 0;
  // if our current node is a leaf, return 1
  if (root->is_leaf == true) {
    return 1;
  }
  // if we aren't at a leaf, we know that we have children nodes
  // So we add +1 for every time we explore down that path to a child node
  // because we KNOW a node exists down that way.
  counter += 1;
  // iterate through each of our child nodes and their children as well.
  // and recursively call count_nodes until we reach leaves, go up, then down,
  // rinse and repeat.
  // work from the bottom up, and count +1 for everytime we have a node.
  // keys = # of children - 1, so we have num_keys + 1 of children nodes
  for (int i = 0; i < (root->num_keys + 1); i++) {
    // return 1 + the func count_nodes
    // everytime we recursively call this function, 1 will be added to the total count
    counter += count_nodes(root->children[i]); 
  }
  return counter;
}

// count_keys returns the total number of keys stored in this
// btree. If the root node is null it returns zero; otherwise it
// returns the number of keys in the root plus however many keys are
// contained in valid child links.
int count_keys(btree*& root) {
  // if b-tree is empty, just freaking return 0
  if (root == NULL) {
    return 0;
  }
  // initiate a counter
  int counter = 0;
  // check if we are currently at a leaf and return num_keys found in current node
  if (root->is_leaf == true) {
    return root->num_keys;
  }
  // if we aren't at a leaf count the num_keys at current node anyways
  counter += root->num_keys;
  // we need to iterate through every child node and count each's keys respectively
  // and recursively call upon the children of each key in our node
  for (int i = 0; i < (root->num_keys + 1); i++) {
    // call our count_keys func to return the amount of keys found in the children
    // of our children. (like counting keys found in each subtree)
    // add these into our counter
    counter += count_keys(root->children[i]);
  }
  // our counter has received num_keys of every node
  // return counter
  return counter;
}

