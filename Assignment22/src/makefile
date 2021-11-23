# Make variables
CC=gcc
CFLAGS=-ansi -Wall -Wextra -pedantic -g -std=c99
LIBS=-lm
EXE=ProjectAsh

ODIR=../obj
_OBJ=Compilers.o MainBuffer.o Buffer.o MainScanner.o Scanner.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

DDIR=../deps
_DEPS=Compilers.h Scanner.h Buffer.h
DEPS=$(patsubst %,$(DDIR)/%,$(_DEPS))

# Default build
all: $(EXE)

$(EXE): $(OBJ) 
	$(CC) -o $(EXE) $^ $(LIBS) $(CFLAGS)

$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

# Remove object files and executable file
clean:
	rm $(EXE) $(ODIR)/*
