UIdaho CS445 - Compilers
==========================

# HW1
Lexical Analysis assignment using `flex`.

## TODO:
 *  String literals
 *  Character constants
 *  Regular expressions
 *  Pretty printing
 *  Wrapper for fopen and memory allocations
 *  Switch entirely to C?
 *  More error checking?

# HW2
Parsing assignment using `bison`.

## Notes
 *  Reduce/reduce conflicts is `bison`'s way of saying that it thinks that your grammar may be ambiquous.
 *  In the assignment notes, the tree struct has a `struct tree *kids[9]`.  Use `struct tree **kids;` instead.
 *  Print the tree using pre-order traversal.
## Recommendations
 *  Highly recommended to first get the parser to spit out whether or not the parse was successful.  Only after that should the tree be created.
