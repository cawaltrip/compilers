/*
 * globals.hh
 * UIdaho CS-445 120++ Compiler
 * Global variables for 120++ compiler
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GLOBALS_HH_
#define _GLOBALS_HH_

/* Global writable flags */
static bool PRINT_PARSE_TREES = false;

/* Custom exit status codes */
static const unsigned short EXIT_LEXICAL_ERROR = 1;
static const unsigned short EXIT_SYNTAX_ERROR = 2;
static const unsigned short EXIT_SEMANTIC_ERROR = 3;
static const unsigned short EXIT_UNSUPPORTED = 4;

#endif /* _GLOBALS_HH_ */