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

## Identifier Types
Sigala's lexer checks if a lexeme is the name of a typedef, namespace, class, enum and template name versus a standard identifier by checking the first character of the lexeme and return based on what that character is.

Should use a lookup table for each type to see if something has been declared as a specific type earlier.  This would be called inside `yacc` or `bison`.  Should this be shared between the lexer and the parser?  Should the parser modify each lexeme?  Insert predefined class names for the standard libraries to avoid collisions.

## Preprocessor Directives
When are preprocessor directives acted upon?  We handle `#include` in our lexer but nothing else.  The `#define` directive would be easy enough.  What about `#if[n]?def`?