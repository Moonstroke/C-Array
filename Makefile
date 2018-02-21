## BUILD SETTINGS##


# Debugging
# y/n
DEBUG := n

# Optimization level at compilation (0 => no optimization)
# 0..3/s
OPTIM_LVL := 2



## VARIABLES ##


# Project directories
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj

# Executables
TEST_EXEC := test_arrays

# Tests files
TEST_SRC := $(wildcard $(SRC_DIR)/test*.c)
TEST_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Sources and object files
SRC := $(filter-out $(TEST_SRC), $(wildcard $(SRC_DIR)/*.c))
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Library archive
LIB := libarrays.a


# Installation directory
INST_DIR := /usr/local


# Documentation
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc


# The compiler
CC := gcc

# Compilation flags
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded -O$(OPTIM_LVL) -I$(INC_DIR)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif

# The libraries to link against
LDLIBS := -llog

# Linkage flags
LDFLAGS := -L.




## RULES ##

# All rule names that do not refer to a file
.PHONY: all clean distclean doc test testclean

# The default rule to execute
all: testclean $(LIB)

# Linkage
$(LIB): $(OBJ)
	$(AR) rcs $(LIB) $(OBJ_DIR)/*.o

# File-wise compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o$@ $(CFLAGS)


# Remove compiled files
clean:
	@rm -rf $(OBJ_DIR)

# Reset the project to its initial state
distclean: clean docclean testclean
	@rm -rf $(LIB)

# (Re)generate documentation
doc:
	@$(DOC_PRG) $(DOC_CFG)

# Remove documentation
docclean:
	@rm -rf $(DOC_DIR)

# Build and launch tests
test: $(TEST_OBJ) $(LIB)
	$(CC) -o$(TEST_EXEC) $^ $(LDLIBS) $(LDFLAGS)
	./$(TEST_EXEC)

# Remove test build files
testclean:
	@rm -rf $(TEST_OBJ) $(TEST_EXEC)

# Install the project for system use
install:
	@cp --update --target-directory=$(INST_DIR)/include $(INC_DIR)/*
	@cp --update --target-directory=$(INST_DIR)/lib $(LIB)

# Remove the project from the system
uninstall:
	@rm -f $(patsubst $(INC_DIR)/%,$(INST_DIR)/include/%,$(wildcard $(INC_DIR)/*))
	@rm -f $(INST_DIR)/lib/$(LIB)

# Install the project dependencies
get-deps:
	@./install_deps.sh
