#######################################
# Compiler Options ####################
#######################################
CPP=g++
CPPFLAGS=-c -g -std=gnu++0x -x c++
LDFLAGS=
LEX=flex
YACC=bison
RM=-rm -f
#######################################
# Filename configurations #############
#######################################
BIN=120++
CC_SOURCES=120++.cc token.cc
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
	$(CPP) $(CPPFLAGS) -DYYDEBUG 120gram.tab.c

120gram.tab.c 120gram.tab.h: 120gram.y
	$(YACC) -dtv 120gram.y

# Remove created files
clean:
	$(RM) *.o *.a
	$(RM) 120gram.tab.c 120gram.tab.h 
	$(RM) lex.yy.c clex.h lex.yy.h
	$(RM) $(BIN) $(OBJECTS)
