UIdaho CS445 - Compilers
==========================

# General TODO
 *  Wrapper for fopen and memory allocations?
 *  More error checking?

# HW1
Lexical Analysis assignment using `flex`.

# HW2
Parsing assignment using `bison`.

## Notes
 *  In the assignment notes, the tree struct has a `struct tree *kids[9]`.  Use `struct tree **kids;` instead.

# HW3
Type checking the parse trees

## Notes
 *  Type checking for functions will need to know that a default constructor or an self-defined empty constructors are valid.
 *  At end of file, run through and delete the tree that was created.
 *  Allow, but ignore const.