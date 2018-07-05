/*

  sorting.cpp

  Please refer to sorting.h for documentation on each function.

   + ------ N O T E: -- Big scary warning! -----------------------------\
   |                                                                    |
   |    We clearly can't use unit testing to ensure that you're         |
   |    actually implementing the correct algorithm. I suppose we could |
   |    write some complicated static analysis checker. But it is       |
   |    easier to just look at it with our eyeballs.                    |
   |                                                                    |
   |    After the assignment is due, we will look at the most recent    |
   |    version of your implementation that got the highest score and   |
   |    make sure you're not doing something sneaky like using a        |
   |    standard library call to sort a vector.                         |
   |                                                                    |
   |    Anyone caught doing this (even though it is kinda funny) will   |
   |    be given 0 points on the assignment.                            |
   |                                                                    |
   `--------------------------------------------------------------------/ 

 */

#include "sorting.h"
#include <iostream>

using namespace std;

// quicksort is the entry point for the quicksort routine. It should
// use the quicksort_partition function. It is also recursive, so you
// will call quicksort from inside the quicksort function.
// 
// data: The input is a vector of integers. You can use this in a very
// similar manner to arrays, but without a lot of the pointer
// brain-damage. Note that the ampersand in front of the parameter
// name indicates this is passed by _reference_, which means whatever
// you do to this vector inside the quicksort function will be visible
// outside as well.
//
// low_idx and high_idx: these are the current indices for the
// quicksort algorithm, and are normal pass-by-value parameters. Both
// of these indices are inclusive: they refer to an addressable
// element of the data vector.
void quicksort(vector<int> &data, int low_idx, int high_idx) {
  if (low_idx < high_idx) {
    int p = quicksort_partition(data, low_idx, high_idx);
    quicksort(data, low_idx, p-1);
    quicksort(data, p+1, high_idx);
  }
}

// quicksort_partition is the helper function for quicksort. Input
// parameters have same semantics as for quicksort.
//
// The pivot index is returned.
int quicksort_partition(vector<int> &data, int low_idx, int high_idx) {
  int pivot = data[high_idx];
  int i = low_idx - 1;

  for (int j = low_idx; j < high_idx; j++) {
    if (data[j] < pivot) {
      i = i + 1;
      int temp = data[j];
      data[j] = data[i];
      data[i] = temp;
    }
  }  
  if (data[high_idx] < data[i+1]) {
    int p_temp = data[high_idx];
    data[high_idx] = data[i+1];
    data[i+1] = p_temp;
  }
  return i+1;
}

// bubblesort is probably the easiest sorting algorithm to conceive
// of. It is unfortunately not all that fast. Here's your chance to
// write really inefficient code! There are no related helper
// functions.
void bubblesort(vector<int> &data) {
  for (int i = 0; i < data.size(); i++) {
    bool swapping = false;
    // need to create another loop so that swapping's boolean value
    // changes until we have iterated through the entire array. Otherwise,
    // the first value comparison we come across that does not swap exits
    // the loop.
    for (int j = 0; j < data.size(); j++) {
      if (data[j] > data[j+1]) {
        int temp = data[j];
        data[j] = data[j+1];
        data[j+1] = temp;
        swapping = true;
      }
    }
    if (swapping == false) {
      break;
    }
  }
}

// mergesort is another classic O(n log n) sorting algorithm. This
// uses the helper function 'merge'.
void mergesort(vector<int> &data) {
  if (data.size() == 1) {
    return;
  }
  int mid = data.size() / 2;
  vector<int> left = vector<int>(data.begin(), data.begin() + mid);
  vector<int> right = vector<int>(data.begin() + mid, data.begin() + data.size());

  mergesort(left);
  mergesort(right);

  data = merge(left, right);

  /* for (int i = 0; i < data.size(); i++) {
    if (data[i] < (data.size()/2)) {
      left.push_back(data[i]);
    } else {
      right.push_back(data[i]);
    }
  } */
     
}

// merge is the helper function for mergesort. It returns a vector
// containing the merged contents of the two input vectors.
vector<int> merge(vector<int> &left, vector<int> &right) {
  vector<int> mergeresult;

  int i = 0;
  int j = 0;

  while(i <= (left.size()-1) && j <= (right.size()-1)) {
    if (left[i] <= right[j]) {
      mergeresult.push_back(left[i]);
      i += 1;
    } else {
      mergeresult.push_back(right[j]);
      j +=1;
    }
  }
  while (i <= left.size()-1) {
    mergeresult.push_back(left[i]);
    i += 1;
  }
  while (j <= right.size()-1) {
    mergeresult.push_back(right[j]);
    j += 1;
  }
  return mergeresult;
}

// mystery_sort is any other sorting function that you choose to
// implement. You may write any additional sorting function you wish,
// and call it 'mystery_sort'.
// 
// See http://en.wikipedia.org/wiki/Sorting_algorithm for a list.
//
// Only rules are: (1) it has to have the following signature, and the
// calling code will expect 'data' to be in non-decreasing order when
// it returns, and (2) you have to write something new---no relying on
// the other functions you've implemented.
//
// Also, write a comment somewhere near the top that explains which
// sorting algorithm you're implementing.
void mystery_sort(vector<int> &data) {
  // TODO
  // Algorithm implemented: INSERTION SORT

  int i = 0;
  int j = 0;
  int key = 0;

  for (i = 0; i < data.size(); i++) {
    key = data[i];
    j = i-1;
    while (j >= 0 && data[j] > key) {
      data[j+1] = data[j];
      j = j-1;
    }
    data[j+1] = key;
  }
}

