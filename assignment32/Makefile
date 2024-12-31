# Make variables
CC=gcc
CFLAGS=-g -ansi -pedantic -Wall -Wextra -Wextra
LDFLAGS=-lm
BIN=ash

OBJ=compilers.o main_buffer.o buffer.o main_scanner.o scanner.o main_parser.o parser.o

# Default build
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

# Remove object files and executable file
clean:
	rm $(BIN) *.o
