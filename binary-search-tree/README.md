# Binary Search Trees

In this assignment you'll implement a binary search tree data
structure. The operations you'll implement are:

* **init_node** - create a new bt_node and return a pointer to it
* **insert** and **insert_data** - insert into a correct spot in the tree
* **remove** - remove a node with 0, 1, or 2 nodes from the tree
* **contains** - return true if the tree contains a given value
* **get_node** - return pointer to a node that has the given value
* **size** - return the current number of nodes reachable from the top
* **to_array** - fills an array with the tree's data in sorted order.

## Editing, Compiling and Testing

You only need to edit the `binary_search_tree.cpp` implementation
file, as that is the only file that our official grading system will
use.

Running the python grading script, the unit tests (as a whole and in
parts) is done exactly the same as the linked list assignment, except
now we're using the executable `binary_search_tree_test`.

## Preconditions

### Pointers

In all cases, you can assume that a variable such as `bt_node** top` has
these properties:

* `top` is not null.
* `*top` might be null.

Further, `bt_node* t` might be null. We use `t` represents the top of
a subtree. Remember, every node is the root of a subtree, and any
child link can be used to recursively call the function you're in.

### Values

No restrictions on `int data` are provided - any value is acceptable.

## Postconditions

Any function that modifies the structure of the binary search must
ensure the top pointer is correctly set before returning.

## Invariant

The binary search tree must ensure that by the time the function
returns, it maintains the proper sort order. 

This means it maintains its nodes such that the left subtree only has
values less than the subtree's root; the right subtree only has values
that are greater than or equal to the subtree's root.

**Mnemonic hint:** Left = less.
