# C / Array
## A dynamic array implementation in C

This repo defines a structure for a dynamic array.

I needed one for the big project I'm working on, [A Point & Click library in plain C]
(https://github.com/Moonstroke/C-SDL-Point-Click), using the SDL version 2.

This implementation can not contain primitive types, only pointers, including
pointers to primitive types, though.

The module *array.h* contains the interface for the structure, defined opaquely
in *array.c*; the module *array_funcs.h* defines several additional functions
manipulating the structure.

The *test.c* module contains the `main()` function, that executes a set of tests
over the Array functions.

