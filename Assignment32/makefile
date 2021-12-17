# Make variables
CC=gcc
CFLAGS=-g -std=c99 -ansi -Wall -Wextra -pedantic
LIBS=-lm
EXE=Compilers.exe

ODIR=./
_OBJ=Compilers.o MainBuffer.o Buffer.o MainScanner.o Scanner.o MainParser.o Parser.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

DDIR=./
_DEPS=Compilers.h Parser.h Scanner.h Buffer.h
DEPS=$(patsubst %,$(DDIR)/%,$(_DEPS))

# Default build
all: $(EXE)

$(EXE): $(OBJ) 
	$(CC) -o $(EXE) $^ $(LIBS) 

$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

# Remove object files and executable file
clean:
	rm $(EXE) $(ODIR)/*
