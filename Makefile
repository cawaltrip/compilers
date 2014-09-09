#######################################
# Compiler Options ####################
#######################################
#CPP=/opt/local/bin/g++-mp-4.4
CPP=g++
CPPFLAGS=-c -g

#######################################
# Filename configurations #############
#######################################
BIN=120++
SOURCES=120++.cc lex.yy.cc
OBJECTS=$(SOURCES:.cc=.o)



# Grammar File
GRAMMAR_FILE=$(addsuffix gram.tab.h,$(BASE_NAME))

# Flex file
FLEX_FILE=$(addsuffix .l,$(BASE_NAME))

# Scanner files (created by flex)
BASE_SCANNER=$(addsuffix .yy,$(BASE_NAME))
SCANNER_FILE=$(addsuffix .cpp,$(BASE_SCANNER))
SCANNER_OBJECT=$(addsuffix .o,$(BASE_SCANNER))

#######################################
# Make rules ##########################
#######################################

all: $(BIN)

$(BIN): 120++.o lex.yy.o
	$(CPP) -o 120++ 120++.o lex.yy.o

120++.o: 120++.c
	$(CPP) $(CPPFLAGS) 120++.c

lex.yy.o: lex.yy.cc
	$(CPP) $(CPPFLAGS) lex.yy.cc

lex.yy.cc: 120++.l cgram.tab.h
	flex 120++.l

# Remove created files
clean:
	-rm -f *.o
	-rm -f *.a
	-rf -f $(BIN)
	-rf -f $(OBJECTS)
	-rf -f lex.yy.c clex.h