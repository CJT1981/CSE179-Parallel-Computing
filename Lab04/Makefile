CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99 -lpthread

# Define tasks
TASKS = Task01 Task02

# Default target (compile all tasks)
all: $(TASKS)

# Compile Task01 (montecarlo)
Task01: Task01/montecarlo.c
	$(CC) $(CFLAGS) Task01/montecarlo.c -o Task01/montecarlo

# Compile Task02 (bankAccount)
Task02: Task02/bankAccount.c Task02/bankAccount.h
	$(CC) $(CFLAGS) Task02/bankAccount.c -o Task02/bankAccount

# Clean all compiled files
clean:
	rm -f Task01/montecarlo Task02/bankAccount
