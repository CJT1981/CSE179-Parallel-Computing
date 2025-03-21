# Compiler
CC = mpicc
# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11

# Directories
TASK01_DIR = Task01
TASK02_DIR = Task02
TASK03_DIR = Task03

# Source files
TASK01_1_SRC = $(TASK01_DIR)/Task01_1.c
TASK01_2_SRC = $(TASK01_DIR)/Task01_2.c
TASK02_SRC = $(TASK02_DIR)/Task02.c
TASK03_SRC = $(TASK03_DIR)/Task03.c

# Output binaries
TASK01_1_BIN = task01_1
TASK01_2_BIN = task01_2
TASK02_BIN = task02
TASK03_BIN = task03

# Default target
all: $(TASK01_1_BIN) $(TASK01_2_BIN) $(TASK02_BIN) $(TASK03_BIN)

# Compile each task separately
$(TASK01_1_BIN): $(TASK01_1_SRC)
	$(CC) $(CFLAGS) $^ -o $@ -lmpi

$(TASK01_2_BIN): $(TASK01_2_SRC)
	$(CC) $(CFLAGS) $^ -o $@ -lmpi

$(TASK02_BIN): $(TASK02_SRC)
	$(CC) $(CFLAGS) $^ -o $@ -lmpi

$(TASK03_BIN): $(TASK03_SRC)
	$(CC) $(CFLAGS) $^ -o $@ -lmpi

# Clean compiled files
clean:
	rm -f $(TASK01_1_BIN) $(TASK01_2_BIN) $(TASK02_BIN) $(TASK03_BIN)
