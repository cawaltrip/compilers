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
C_SOURCES=lex.yy.c cgram.tab.c
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

lex.yy.c: clex.l cgram.tab.h
	$(LEX) $<

cgram.tab.o: cgram.tab.c
	$(CPP) $(CPPFLAGS) -DYYDEBUG cgram.tab.c

cgram.tab.c cgram.tab.h: cgram.y
	$(YACC) -dtv cgram.y

# Remove created files
clean:
	$(RM) *.o *.a
	$(RM) cgram.tab.c cgram.tab.h 
	$(RM) lex.yy.c clex.h lex.yy.h
	$(RM) $(BIN) $(OBJECTS)
