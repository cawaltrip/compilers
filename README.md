UIdaho CS445 - Compilers
==========================

I'm not updating this project anymore and it is both incomplete and very very rough.  The majority of the semantic analysis and the beginnings of the type checking were done under the time crunch of the semester ending and being incredibly far behind.  The point up to completing the parse tree isn't too bad though!  If I had a bunch of free time, I'd love to continue to work on this or a compiler for another language, but I don't foresee that happening for quite awhile.

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
