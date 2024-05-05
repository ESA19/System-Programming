# Makefile for building the 'odev' program

# Compiler and linker configuration
CC = gcc
CFLAGS = -g -I/home/esa/Desktop/system_programming_project/include
LDFLAGS = /home/esa/Desktop/system_programming_project/lib/libfdr.a

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# Source and object files
SRC = $(SRC_DIR)/odev.c
OBJ = $(OBJ_DIR)/odev.o

# Target executable
TARGET = odev

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Running the program
run:
	./$(TARGET) giris.dat

# Cleaning up
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all run clean
