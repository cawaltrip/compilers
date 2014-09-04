#######################################
# Compiler Options ####################
#######################################
CPP=g++
CPPFLAGS=-c -g -v

#######################################
# Filename configurations #############
#######################################
BASE_NAME=120++
CPP_OBJECT=$(addsuffix .o,$(BASE_NAME))
CPP_FILE=$(addsuffix .cpp,$(BASE_NAME))

# Grammar File
GRAMMAR_FILE=$(addsuffix .tab.h,$(BASE_NAME))

# Flex file
FLEX_FILE=$(addsuffix .l,$(BASE_NAME))

# Scanner files (created by flex)
BASE_SCANNER=$(addsuffix .yy,$(BASE_NAME))
SCANNER_FILE=$(addsuffix .cpp,$(BASE_SCANNER))
SCANNER_OBJECT=$(addsuffix .o,$(BASE_SCANNER))

#######################################
# Make rules ##########################
#######################################

# Primary makefile
all: 
	run_flex
	compile_flex
	120++.o
	120++

# Remove created files
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f $(SCANNER_FILE) $(SCANNER_OBJECT)

120++: $(CPP_OBJECT) $(SCANNER_OBJECT)
	$(CPP) -o $(BASE_NAME) $(CPP_OBJECT) $(SCANNER_OBJECT)

120++.o: 120++.cpp
	$(CPP) $(CPPFLAGS) $(CPP_FILE)

compile_flex: $(SCANNER_OBJECT)
	$(CPP) $(CPPFLAGS) $(SCANNER_FILE)

run_flex: $(FLEX_FILE) $(GRAMMAR_FILE)
	flex $(FLEX_FILE) --outfile=$(SCANNER_FILE)

## phase 2: ignore for now

#c: main.o cgram.tab.o lex.yy.o
#	cc -o c main.o cgram.tab.o lex.yy.o

#cgram.tab.o: cgram.tab.c
#	cc -c -DYYDEBUG cgram.tab.c

#cgram.tab.c: cgram.y
#	bison -d -v cgram.y

#cgram.tab.h: cgram.tab.c
