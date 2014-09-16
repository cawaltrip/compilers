#######################################
# Compiler Options ####################
#######################################
#CPP=/opt/local/bin/g++-mp-4.4
CPP=g++
CPPFLAGS=-c -g -std=gnu++98 -x c++ -Wall
LDFLAGS=

#FLEX=/opt/local/bin/flex++
#FLEX++
FLEX=flex

RM=-rm -f
#######################################
# Filename configurations #############
#######################################
BIN=120++
CC_SOURCES=120++.cc token.cc
C_SOURCES=lex.yy.c
OBJECTS=$(CC_SOURCES:.cc=.o) $(C_SOURCES:.c=.o)

# Grammar File
GRAMMAR_FILE=cgram.tab.h
FLEX_FILE=clex.l

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
	$(FLEX) $<

# Remove created files
clean:
	$(RM) *.o *.a lex.yy.c clex.h lex.yy.h $(BIN) $(OBJECTS)