# Make variables
CC=gcc
CFLAGS=-g -ansi -pedantic -Wall -Wextra -Wextra
LDFLAGS=-lm
BIN=Ash

OBJ=Compilers.o MainBuffer.o Buffer.o MainScanner.o Scanner.o MainParser.o Parser.o

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
