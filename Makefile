#######################################
# Compiler Options ####################
#######################################
CPP=clang++
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
CC_SOURCES=120++.cc token.cc treenode.cc typename.cc symtable.cc
CC_SOURCES+=semantic.cc
C_SOURCES=lex.yy.c 120gram.tab.c
OBJECTS=$(CC_SOURCES:.cc=.o) $(C_SOURCES:.c=.o)
#######################################
# Make rules ##########################
#######################################

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CPP) $(LDFLAGS) $^ -o $@

.c.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@

120++.cc: clex.h

clex.h: lex.yy.c

lex.yy.c: clex.l 120gram.tab.h
	$(LEX) $<

120gram.tab.o: 120gram.tab.c
	$(CPP) $(CPPFLAGS) 120gram.tab.c

120gram.tab.c 120gram.tab.h: 120gram.y
	$(YACC) -dt -Wall 120gram.y

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
	$(RM) $(BIN)
