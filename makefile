# All declarations I need for flags, source, and object files

# Variables to limit confusion between certain calls
SRC_DIR = src
OBJ_DIR = obj

# Include directories and Compiler variable
LDFLAGS = -Iinclude #This flag tells the compiler to look into include dir
CC = gcc #Specifies the compiler we want 

# Getting Source files 
src = $(wildcard $(SRC_DIR)/*.c)
# Getting Object files and make sure they go into the obj folder
obj = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(src))

# Checking to see if the obj directory exists
$(shell mkdir -p $(OBJ_DIR))

# Creating a target executable
printfunc: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

# Creating a rule to compile .c files into .o files and place those
# .o files into the obj folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(LDFLAGS)

# Creating a clean up command called "clean" using .PHONY
.PHONY: clean
clean:
	rm -f $(obj) printfunc