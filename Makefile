#
# Makefile
# UIdaho CS-445 120++ Compiler
# Compilation options for 120++ compiler on GNU/Linux operating system.
# 
# Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#######################################
# Compiler Options ####################
#######################################
CPP=g++
CPPFLAGS=-c -g -std=c++98 -x c++
LDFLAGS=
LEX=flex
YACC=bison
RM=-rm -f

#######################################
# Operating System Specific Options ###
#######################################
# Modified from StackOverflow answer:
# http://stackoverflow.com/a/12099167/2592570
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	CPPFLAGS += -Wno-deprecated-register -I /usr/local/include
	YACC=/usr/local/Cellar/bison/3.0.2/bin/bison
endif

#######################################
# Filename configurations #############
#######################################
BIN=120++
BIN_NAME=120
CC_SOURCES=120++.cc token.cc treenode.cc typename.cc symtable.cc semantic.cc
C_SOURCES=lex.yy.c 120gram.tab.c
OBJECTS=$(CC_SOURCES:.cc=.o) $(C_SOURCES:.c=.o)
#######################################
# Make rules ##########################
#######################################

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CPP) -lboost_program_options $(LDFLAGS) $^ -o $(BIN_NAME)

.c.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@

120++.cc: clex.h

clex.h: lex.yy.c

lex.yy.c: clex.l 120gram.tab.h
	$(LEX) $<

120gram.tab.o: 120gram.tab.c
	$(CPP) $(CPPFLAGS) 120gram.tab.c

120gram.tab.c 120gram.tab.h: 120gram.y
	$(YACC) -d -Wall 120gram.y

# Semantic Testing
semantic:
	$(MAKE) clean
	$(MAKE) all
	./$(BIN) stubs/*

# Remove created files
clean:
	$(RM) *.o *.a
	$(RM) *.tab.c *.tab.h *gram.output
	$(RM) lex.yy.c clex.h lex.yy.h
	$(RM) $(BIN_NAME)
