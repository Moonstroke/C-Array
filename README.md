# CODS

## C Opaque Data Structures


[![Build Status](https://travis-ci.org/Moonstroke/CODS.svg?branch=master)
](https://travis-ci.org/Moonstroke/CODS)


![One cod][1]
![Two cods][1]
![Three cods][1]
![Four cods][1]
![Five cods][1]

This repo defines structures for dynamically-allocated arrays.

I needed one for the big project I'm working on, [A Point & Click library in
plain C](https://github.com/Moonstroke/C-SDL-Point-Click), using the SDL v2.




## Usage


These implementations can not contain primitive types, only pointers, including
pointers to primitive types, though.




## Naming convention



### Types

Each type has its unique identifier, spelled in `PascalCase`: the words are
joined together and the first letter of each word is capitalized.

This syntax will be familiar to all developers as it is extremely common; Java
is only one of the many high-level programming languages that have adopted it.


### Functions

Since C does not allow functions to share an identifier, the functions defined
in this project are named in a specific syntax:

    prefix_action

The `prefix` is unambiguously bound to a type (each type has its own prefix),
and the `action` describes the behavior of the function.

Several types share an action, for example an `Array` and a `SortedArray` can
both be `add`ed an item, however the expected behavior is different and
therefore two different functions exist, one for each type.

The prefix generally consists of the initials of the type name; the exact prefix
is given in each type's description below.

This peculiar syntax has been adopted for, as said above, its unambiguity, but
also because it was deemed a good compromise between terseness (names are kept
short, in terms of character length) and clarity (the type the functions is
dedicated to and the action it is designed to perform are immediately exposed).



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

The prefix of the functions dedicated to this type is `a`, so for example the
function that adds an element to an *Array* is called `a_add`.


#### FixedArray

The module **fixedarray** contains a definition for an array of fixed size,
precisely called *FixedArray*. The array contains a number of elements that does
not evolve during the lifetime of the object; the elements in the array may --
and most likely will -- be `NULL` at some time.

In the same manner than for *Array*, the module **fixedarray_funcs** defines
some extra functions for *FixedArray*.

The prefix for the names of the functions related to this type is `fa`.


#### LinkedList

The module **linkedlist** declares a structure of elements that are stored not
necessarily in contiguous blocks on memory; each element contains the
information to find the next element. It is more suited than *Array* for random
data insertion / deletion as those operations are `O(1)`; however element
retrieval is `O(n)`.

There is once again a module of supplementary functions, **linkedlist_funcs**.

The prefix for this type is `ll`.


#### BitArray

The module **bitarray** declares the type `BitArray`, representing a bit array.
A bit array is a specific type of fixed-size array designed to hold boolean
values, or bits, which are either *true* or *false* (or `1` and `0` in terms of
numerical values). The implementation is optimized to represent each element as
a single bit of storage rather than a whole storage unit (usually an octet), the
functions manipulating an instance of this type are designed to extract or
modify each of these bits.

The module **bitarray_funcs** declares extraneous functions for this type.

The prefix for this type is `ba`.


#### SortedArray

The module **sortedarray**, and its associated extension **sortedarray_funcs**,
declare the type `SortedArray` and a set of functions to handle it.
This type of array sorts its elements at the time of inclusion, using a function
given at its creation to discriminate the elements. The profile for the function
is:

    int SortFunction(const data_t*, const data_t*);

The function is expected to return a negative value (that might be lower than
`-1`) when the first argument is inferior to the second, a positive value (maybe
greater than `1`) when the first argument is superior to the second, and exactly
`0` when the two arguments are equivalent.

Searching for an element (when adding or finding it) is implemented with a
binary search algorithm, and so these operations are performed in logarithmic
time (`O(log n)` complexity).

This array will not contain two identical elements at once: the function
`sa_add` will not add the given item and return `-1` if an item equivalent as
per the sort function is already present in the array. The array can therefore
be used as an ordered set with logarithmic-time implementation.

The prefix for this type is `sa`.



### Test modules

The `test.c` file contains a `main()` function that executes the sets of tests
over the module functions, each module having its own set:

The file `test_array.c` contains a set of tests to check the running of the
functions concerning the structure *Array*.

The file `test_fixedarray.c` contains a set of tests for the structure
*FixedArray*.





[1]: https://vignette.wikia.nocookie.net/minecraft/images/a/ab/RawFish.png/revision/latest "Cods!"
