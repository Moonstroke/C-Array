# C / Arrays


## Dynamic array types implemented in C

This repo defines structures for dynamically-allocated arrays.

I needed one for the big project I'm working on, [A Point & Click library in plain C]
(https://github.com/Moonstroke/C-SDL-Point-Click), using the SDL version 2.


## Usage


These implementations can not contain primitive types, only pointers, including
pointers to primitive types, though.



## Modules


### Type modules


#### Array

The module **array** contains the interface for the *Array* structure; this type
represents a typical dynamically resizable array to hold a variable number of
elements in a safe way. One element in the array may be `NULL`, though in this
case one should consider using the *FixedArray* type which is better
designed for this specific case.

The module **array_funcs** defines some additional functions (more or less
useful) to manipulate the structure.


### Test modules

The `test.c` file contains a `main()` function that executes the sets of tests
over the module functions, each module having its own set:

The file `test_array.c` contains a set of tests to check the running of the
functions concerning the structure *Array*.
