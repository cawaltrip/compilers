#######################################
# Compiler Options ####################
#######################################
#CPP=/opt/local/bin/g++-mp-4.4
CPP=g++
CPPFLAGS=-c -g -std=gnu++98

#FLEX=/opt/local/bin/flex++
FLEX=flex
#######################################
# Filename configurations #############
#######################################
BIN=120++
CC_SOURCES=120++.cc
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
	$(CPP) -o 120++ 120++.o lex.yy.o

.c.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@

120++.cc: clex.h

clex.h: lex.yy.cc

lex.yy.cc: clex.l cgram.tab.h
	$(FLEX) $<

# Remove created files
clean:
	-rm -f *.o
	-rm -f *.a
	-rf -f $(BIN)
	-rf -f $(OBJECTS)
	-rf -f lex.yy.c clex.h