// 
// pq_struct.h
// 
// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
//
// You will turn in this file and pq.cpp.
//
// Your Name:

#include <string>
#include <iostream>
#include <vector>

#ifndef pq_struct_h
#define pq_struct_h

using namespace std;

struct pq {
    pq* next;
    float priority;
    string str;
};

#endif
