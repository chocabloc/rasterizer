# Source and Object files
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)

# Compiler options
CC = gcc
LD = gcc
CFLAGS = -std=gnu2x -Ofast -flto -march=native -Wall
LDFLAGS = -lm -lSDL2 -flto

# Output binary
OUT = ./3demo

# Rules
.phony = clean run
$(OUT): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $(OUT)
$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
run: $(OUT)
	$(OUT)
clean:
	rm -f $(OBJ)
