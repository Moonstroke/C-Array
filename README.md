# CODS

## C Opaque Data Structures


[![Build Status](https://travis-ci.org/Moonstroke/CODS.svg?branch=master)
](https://travis-ci.org/Moonstroke/CODS)


![One cod](https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!")
![Two cods](https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!")
![Three cods](https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!")
![Four cods](https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!")
![Five cods](https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!")


This repo defines structures for dynamically-allocated arrays.

I needed one for the big project I'm working on, [A Point & Click library in
plain C](https://github.com/Moonstroke/C-SDL-Point-Click), using the SDL v2.




## Usage

These implementations can not contain primitive types, only pointers, including
pointers to primitive types, though.




## Modules


### `cods.h`

The file `cods.h` is shared by the other modules. It defines common data and
is included by all the other files.

It can also serve as the project's main interface (hence the name): if it is
`#include`d directly, all the project's headers are also included.


### Type modules

#### Array

The module **array** contains the interface for the *Array* structure; this type
represents a typical dynamically resizable array to hold a variable number of
elements in a safe way. One element in the array may be `NULL`, though in this
case one should consider using the *FixedArray* type which is better
designed for this specific case.

The module **array_funcs** defines some additional functions (more or less
useful) to manipulate the structure.


#### FixedArray

The module **fixedarray** contains a definition for an array of fixed size,
precisely called *FixedArray*. The array contains a number of elements that does
not evolve during the lifetime of the object; the elements in the array may --
and most likely will -- be `NULL` at some time.

In the same manner than for *Array*, the module **fixedarray_funcs** defines
some extra functions for *FixedArray*.


#### LinkedList

The module **linkedlist** declares a structure of elements that are stored not
necessarily in contiguous blocks on memory; each element contains the
information to find the next element. It is more suited than *Array* for random
data insertion / deletion as those operations are `O(1)`; however element
retrieval is `O(n)`.

There is once again a module of supplementary functions, **linkedlist_funcs**.


#### BitArray

The module **bitarray** declares the type `BitArray`, representing a bit array.
A bit array is a specific type of fixed-size array designed to hold boolean
values, or bits, which are either *true* or *false* (or `1` and `0` in terms of
numerical values). The implementation is optimized to represent each element as
a single bit of storage rather than a whole storage unit (usually an octet), the
functions manipulating an instance of this type are designed to extract or
modify each of these bits.

The module **bitarray_funcs** declares extraneous functions for this type.



### Test modules

The `test.c` file contains a `main()` function that executes the sets of tests
over the module functions, each module having its own set:

The file `test_array.c` contains a set of tests to check the running of the
functions concerning the structure *Array*.

The file `test_fixedarray.c` contains a set of tests for the structure
*FixedArray*.
