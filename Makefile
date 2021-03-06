## PROJECT SETTINGS ##


# Project name
PROJECT_NAME := CODS


# Project directories
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test


# Documentation
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc


# Installation directory
INST_DIR := /usr/local



## BUILD SETTINGS ##


# Debugging
# y/n
DEBUG := n

# Optimization level at compilation (0 => no optimization)
# 0..3/s
OPTIM_LVL := 2



## VARIABLES ##


# Test executable
TEST_EXEC := test_$(PROJECT_NAME)

# Tests files
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/test_%.o,$(TEST_SRC))
TEST_LOG := test.log

# Project sources and object files
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Library archive
AR_LIB := lib$(PROJECT_NAME).a


# Preprocessor flags
CPPFLAGS := -I$(INC_DIR)
# Compilation flags
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded -O$(OPTIM_LVL)
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif

# The libraries to link against
LDLIBS := -lclog -lCUTE

# Linkage flags
LDFLAGS := -L.



## RULES ##

# All rule names that do not refer to a file
.PHONY: all clean distclean doc test testclean

# The default rule to execute
all: testclean $(AR_LIB)

# Linkage
$(AR_LIB): $(OBJ)
	$(AR) rcs $(AR_LIB) $(OBJ)

# File-wise compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o$@ $(CPPFLAGS) $(CFLAGS)

# Tests compilation
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS)


# Remove compiled files (objects, archives, executables)
clean:
	@rm -rf $(OBJ_DIR) $(AR_LIB) $(TEST_EXEC)

# Reset the project to its initial state
distclean: clean testclean
	@rm -rf $(DOC_DIR) $(TEST_LOG)

# (Re)generate documentation
doc:
	@$(DOC_PRG) $(DOC_CFG)

# Build and launch tests
test: $(TEST_OBJ) $(AR_LIB)
	$(CC) -o$(TEST_EXEC) $^ $(LDLIBS) $(LDFLAGS)
	./$(TEST_EXEC)

# Install the project for system use
install:
	@mkdir -p $(INST_DIR)/include/$(PROJECT_NAME)
	@cp --update --target-directory=$(INST_DIR)/include/$(PROJECT_NAME) $(INC_DIR)/*.h
	@cp --update --target-directory=$(INST_DIR)/lib $(AR_LIB)

# Remove the project from the system
uninstall:
	@rm -rf $(INST_DIR)/include/$(PROJECT_NAME)
	@rm -f $(INST_DIR)/lib/$(AR_LIB)
