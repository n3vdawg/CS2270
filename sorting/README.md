# Sorting

The functions all have a similar signature. Here's the declaration for
`quicksort`:

```cpp
void quicksort(vector<int> &data, int low_idx, int high_idx);
```

The header file signatures call for `vector` objects to contain data,
and it uses the `&` modifier to the parameters to make them _reference
parameters_. These are explained in turn:

Vector
---------

`vector` is a standard C++ class. A `vector` is essentially an
intelligent list data structure, with methods that let you append,
insert, remove, push, pop, and query its data at valid indices.

Consider: `vector<int> data;` This means `data` is a `vector`
that contains `int` elements. This additional syntax is necessary,
because otherwise the compiler doesn't know what kind of elements will
be in the data structure.

Hints with vectors:

```cpp
vector<int> data; // declares an empty vector that holds ints, named data
data.push_back(4); // append 4 to end of data. now contains [ 4 ]
data.push_back(6); // append 6 to end of data. now contains [ 4, 6 ]
data.push_back(2); // append 2 to end of data. now contains [ 4, 6, 2 ]

int n = data.size(); // can address data[0] through data[n-1], but not data[n]

// make a sub-vector using data[0] through data[mid-1], but not data[mid]. 
vector<int> left = vector<int>(data.begin(), data.begin() + mid);
```

[Reference documentation for `vector`](http://www.cplusplus.com/reference/vector/vector/?kw=vector).



Pass By Reference
---------

The parameter `data` is passed by _reference_. This means that
whatever changes you make to the variable inside the function will be
visible in the calling context.

Say there are functions:

	void vegas(int val) {
		val = 1234;
	}
	
	void change_me(int& val) {
		val = 1234;
	}

... and we do the following:

	int x = 4;
	int y = 5;
	vegas(x);
	change_me(y);
	cout << x << " " << y << endl;
	
It prints `4 1234`. Whatever happens in `vegas` stays in
vegas. Whatever happens in `change_me` is persistent outside.

## Pass by reference, longer code example

```cpp
// This is a complete code example that demonstrates various forms of
// function parameters.
//
// 1. pointers: pass a copy of the address of a variable to a
// function. input pointer is copied to a separate stack variable that
// is available for use in the function. dereferencing that pointer
// gives direct access to the original memory.
//
// 2. value: pass a copy of the value of a variable to a
// function. nothing that function can do can modify that variable's
// value in the calling context.  unless it is a pointer.
//
// 3. reference: use the exact memory from the calling context in the
// function. this essentially just gives a new name to the same
// memory. any modifications to that memory will persist after the
// function exits.
//
// 4. constant reference: same as plain old reference, except the
// compiler will trigger an error if it can determine that you are
// modifying the parameter.
//
// This program outputs something like the following:
//
// main A:    val:  1, address: 0x7fff513f457c
// pointer:   val:  0x7fff513f457c, *val: 1, address: 0x7fff513f4528
// main B:    val:  2, address: 0x7fff513f457c
// reference: val:  2, address: 0x7fff513f457c
// main C:    val:  3, address: 0x7fff513f457c
// value:     val:  3, address: 0x7fff513f452c
// main D:    val:  3, address: 0x7fff513f457c
//
// Notice that of all the memory addresses printed out, there are only
// two; the one ending in 7c is the memory address of `val` at the top
// of `main`, the one ending in 28 is the address of a pointer, and
// that pointer's value is the 7c address that everything else refers
// to.

#include <iostream>

using namespace std;

void point(int* val);
void value(int val);
void ref(int& val);
void vegas(const int& val);

int main() {
  int val = 1;
  cout << "main A:    val:  " << val << ", address: " << &val << endl;  
  point(&val);
  cout << "main B:    val:  " << val << ", address: " << &val << endl;    
  ref(val);
  cout << "main C:    val:  " << val << ", address: " << &val << endl;
  value(val);
  cout << "main D:    val:  " << val << ", address: " << &val << endl;
}

void point(int* val) {
  cout << "pointer:   val:  " << val << ", *val: " << *val << ", address: " << &val << endl;
  *val = 2;
}

void ref(int& val) {
  cout << "reference: val:  " << val << ", address: " << &val << endl;
  val = 3;
}

void value(int val) {
  cout << "value:     val:  " << val << ", address: " << &val << endl;
  val = 4;
}

void vegas(const int& val) {
  cout << "const:     val:  " << val << ", address: " << &val << endl;
  // val = 5; // will not compile because val is const, so it is commented out
}
```

## Vectors, passed by reference

Passing vectors by reference works exactly the same way:

    void change_vec(vector<int>& stuff) {
        stuff.push_back(99);
    }
    
    ...
    
    vector<int> foo;
    change_vec(foo);
    cout << foo.size() << endl; // 1
    cout << foo[0] << endl; // 99

For more on this C++ feature see
[introduction to parameter passing modes](http://pages.cs.wisc.edu/~hasti/cs368/CppTutorial/NOTES/PARAMS.html).

This is also informative: https://www.ibm.com/support/knowledgecenter/SS4QVT_8.5.1/com.ibm.xlcpp111.aix.doc/language_ref/cplr233.html
