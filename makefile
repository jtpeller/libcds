### Utilize G++ and set CFLAGS
CXX			:= g++
CXXFLAGS	:= -pthread -pedantic-errors -Wall -Wextra -Werror -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
INCLUDE		:= -Ilibcds/

# paths
SRC_DIR		:= ./libcds
TESTS_DIR	:= ./tests
BUILD_DIR	:= ./build
OBJ_DIR		:= $(BUILD_DIR)/objs
BIN_DIR		:= $(BUILD_DIR)/bin

# extensions
SRC_EXT		:= .cpp
OBJ_EXT		:= .o
TEST_EXT	:= .test.cpp

# Targets, objs, deps
L_LIST		:= LinkedList
L_OBJ		:= $(OBJ_DIR)/$(L_LIST)$(OBJ_EXT)
L_TARGET	:= $(BIN_DIR)/$(L_LIST).exe

DL_LIST		:= DoublyLinkedList
DL_OBJ		:= $(OBJ_DIR)/$(DL_LIST)$(OBJ_EXT)
DL_TARGET	:= $(BIN_DIR)/$(DL_LIST).exe

SRCS		:= $(addsuffix $(TEST_EXT), $(L_LIST) $(DL_LIST))
OBJS		:= $(SRCS:%.test.cpp=$(OBJ_DIR)/%.o)

### recipes
# note to future self:
# $@ = target
# $< = first prereq
# $^ = all prereqs
# $(@D) = target directory

.PHONY: all build test clean

all: build $(L_TARGET) $(DL_TARGET)

build:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# objects
#$(OBJ_DIR)/%.o: %.test.cpp
#	@mkdir -p $(@D)
#	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

# individual test EXEs
$(L_TARGET): #$(L_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(L_LIST)$(TEST_EXT) -o $(L_TARGET) $^

$(DL_TARGET): #$(DL_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/$(DL_LIST)$(TEST_EXT) -o $(DL_TARGET) $^

# test enables debug info
test: CXXFLAGS += -DDEBUG -g
test: all

# release enables optimization
release: CXXFLAGS += -O2
release: all

info:
	@echo "[*] Directories"
	@echo "[*] BIN dir: ${BIN_DIR}"
	@echo "[*] OBJ dir: ${OBJ_DIR}"
	@echo "[*] SRC dir: ${SRC_DIR}"
	@echo "[*] Files"
	@echo "[*] OBJS:    ${OBJS}"
	@echo "[*] SRCS:    ${SRCS}"

### I clean, you clean, we all clean...
clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

full-clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*
	-@rmdir $(BIN_DIR)
	-@rmdir $(OBJ_DIR)
	-@rmdir $(BUILD_DIR)

