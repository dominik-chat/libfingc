#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

PRJ = libfingc
TEST_LIB = $(PRJ)_test

BUILD_DIR = build
INPUT_DIR = input
SRC_DIR = src
INC_DIR = include

SRC = $(shell find src/ -type f -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADERS = $(shell find $(INPUT_DIR)/$(INC_DIR) -type f -name '*.h')
MOD_HEADERS = $(HEADERS:$(INPUT_DIR)/%.h=$(BUILD_DIR)/%_test.h)

CFLAGS = \
	-std=c11 \
	-O2 \
	-Wall \
	-Wextra \
	-c

CC = gcc
COPY = objcopy

all: prepare $(MOD_HEADERS) $(OBJ) link end

$(BUILD_DIR)/$(INC_DIR)/%_test.h: $(INPUT_DIR)/$(INC_DIR)/%.h
	@echo -e "\e[34m\e[1mPreparing test headers\e[0m"
	@ctags -o - --extras=r --kinds-C++=h --language-force=C++ $< | awk '{ print "#include \"" $$1 "\""}' > $@
	@ctags --language-force=C -x --_xformat="%t test_%N %S;"  --kinds-C=p $< | sed -e 's/typename://g' >> $@
	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e "\e[32mCompiling C object: $<\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./$(BUILD_DIR)/$(INC_DIR) $< -o $@

prepare:
	@echo -e "\e[33m\e[1mBuilding $(PRJ) test module\e[0m"
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(INC_DIR)
	@readelf -sW $(INPUT_DIR)/$(PRJ).a | awk '$$4 == "FUNC"' | awk '{print $$8}' | while read -r line; do echo "$$line test_$$line"; done > $(BUILD_DIR)/symbols.txt
	@$(COPY) --redefine-syms=$(BUILD_DIR)/symbols.txt $(INPUT_DIR)/$(PRJ).a $(BUILD_DIR)/$(TEST_LIB).a

link:
	@echo -e "\e[35mLinking tester\e[0m"
	@$(CC) $(OBJ) $(BUILD_DIR)/$(TEST_LIB).a -o $(BUILD_DIR)/$(PRJ)_test

clean:
	@rm -rf $(BUILD_DIR)

end:
	@echo -e "\e[33m\e[1mModule $(PRJ) built successfully\e[0m"

run:
	@clear
	@./$(BUILD_DIR)/$(PRJ)_test