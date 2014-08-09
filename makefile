# Makefile template for simple single-executable C++ projects with no namespaces
# Written by Boskin Erkocevic
CC := g++

# Source file extension
SOURCE_FILE := .cpp
# Header file extension
HEADER_FILE := .hpp
# Executable extension
EXECUTABLE_FILE := .exe

# Directory where the executable and dlls are stored
BIN := bin
# Directory where external library headers are stored
INC := include
# Directory where external non-standard library objects are stored
LIB := lib
# Directory where compiled objects are stored
OBJ := obj
# Base directory of source code
SRC := src

# Include paths for both libraries and source code
INCLUDES := -I"$(INC)" $(addprefix -I./,$(wildcard $(SRC)/*))
# Library paths
LIBRARIES := -L./$(LIB)
# Generates a list of every object for dependencies
OBJECTS := $(addprefix $(OBJ)/,$(addsuffix .o,$(basename $(notdir $(wildcard $(SRC)/*/*$(SOURCE_FILE))))))

# Compiler flags
CFLAGS = -Wall $(INCLUDES) -c
# Linker flags
LFLAGS = 

# Stem of main executable
MAIN := main
# The executable directory
MAIN_BIN = $(BIN)/$(MAIN)$(EXECUTABLE_FILE)

all : $(MAIN_BIN)

clean :
	@echo Cleaning...
	@rm -f $(OBJ)/*.o

release : all clean

# Rule to link executable
$(MAIN_BIN) : $(OBJECTS)
	@echo Linking $(MAIN)$(EXECUTABLE_FILE)...
	@$(CC) -o $(MAIN_BIN) $(OBJECTS) $(LFLAGS)

# Implicit rule for standard class module
$(OBJ)/%.o : $(SRC)/*/%$(SOURCE_FILE) $(SRC)/*/%$(HEADER_FILE)
	@echo Compiling Module $*...
	@$(CC) -o $(OBJ)/$*.o $< $(CFLAGS)

# Implicit rule for single source file module
$(OBJ)/%.o : $(SRC)/*/%$(SOURCE_FILE)
	@echo Compiling Module $*...
	@$(CC) -o $(OBJ)/$*.o $< $(CFLAGS)
