# Compilation parameters
# y/n, debugging
DEBUG := n
# 0/s/1/2/3/n, optimisation level at compilation (n => no optimisation)
OPTIM_LVL := 2


# Directories
INC_DIR := inc
SRC_DIR := src
OBJ_DIR := obj

# Executables
TEST_EXEC := test_arrays


# Tests files
TEST_SRC := $(wildcard $(SRC_DIR)/test*.c)
TEST_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Common files
SRC := $(filter-out $(TEST_SRC), $(wildcard $(SRC_DIR)/*.c))
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Library archive
LIB := libarrays.a


# Documentation
DOC_PRG := doxygen
DOC_CFG := Doxyfile
DOC_DIR := doc


# Installation directory
INST_DIR := /usr/local

# Compilation flags
CC := gcc
CFLAGS := -std=c11 -pedantic -Wall -Wextra -Wpadded
ifeq ($(DEBUG), y)
	CFLAGS += -g
endif
ifneq ($(OPTIM_LVL), n)
	CFLAGS += -O$(OPTIM_LVL)
endif
LDLIBS := -llog
LDFLAGS := -I$(INC_DIR)



.PHONY: all clean distclean doc test testclean

all: testclean $(LIB)

$(LIB): $(OBJ)
	$(AR) rcs $(LIB) $(OBJ_DIR)/*.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o$@ $(LDFLAGS) $(CFLAGS)


clean:
	rm -rf $(OBJ_DIR)

distclean: clean docclean testclean
	rm -rf $(LIB)

doc:
	$(DOC_PRG) $(DOC_CFG)

docclean:
	rm -rf $(DOC_DIR)

test: $(TEST_OBJ) $(OBJ)
	$(CC) -o$(TEST_EXEC) $^ $(LDLIBS)
	./$(TEST_EXEC)

testclean:
	rm -rf $(TEST_OBJ) $(TEST_EXEC)

install: all
	cp --update --target-directory=$(INST_DIR)/include $(INC_DIR)/*
	cp --update --target-directory=$(INST_DIR)/lib $(LIB)

uninstall:
	rm -f $(patsubst $(INC_DIR)/%,$(INST_DIR)/include/%,$(wildcard $(INC_DIR)/*))
	rm -f $(INST_DIR)/lib/$(LIB)
