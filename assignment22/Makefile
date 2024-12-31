# Make variables
CC=gcc
CFLAGS=-ansi -Wall -Wextra -pedantic -g -std=c99
LIBS=-lm
EXE=project_ash

ODIR=obj
_OBJ=compilers.o mainBuffer.o buffer.o mainScanner.o scanner.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

DDIR=include
_DEPS=compilers.h scanner.h buffer.h
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
