#######################################
# Compiler Options ####################
#######################################
CPP=clang++
CPPFLAGS=-c -g -std=c++11 -x c++ -Wno-deprecated-register -I /usr/local/include
#CPPFLAGS=-c -g -std=gnu++98 -x c++ -I /usr/local/include
LDFLAGS=
LEX=flex
YACC=/usr/local/Cellar/bison/3.0.2/bin/bison
#YACC=bison
RM=-rm -f
#######################################
# Filename configurations #############
#######################################
BIN=120++
CC_SOURCES=120++.cc token.cc treenode.cc hashmap.cc
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
	$(YACC) -dtv -Wall 120gram.y

# Remove created files
clean:
	$(RM) *.o *.a
	$(RM) 120gram.tab.c 120gram.tab.h 
	$(RM) lex.yy.c clex.h lex.yy.h
	$(RM) $(BIN) $(OBJECTS)
