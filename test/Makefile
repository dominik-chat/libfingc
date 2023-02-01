#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

PRJ = libfingc
TEST_LIB = $(PRJ)_test

BUILD_DIR = build
SRC_DIR = src

SRC = $(shell find src/ -type f -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS = \
	-std=gnu99 \
	-O2 \
	-Wall \
	-Wextra \
	-c \

CC = gcc
COPY = objcopy

all: prepare $(OBJ) link end

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e "\e[32mCompiling C object: $<\e[0m"
	@$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@

prepare:
	@echo -e "\e[33m\e[1mBuilding $(PRJ) test module\e[0m"
	@mkdir -p $(BUILD_DIR)
	@readelf -sW libfingc.a | awk '$$4 == "FUNC"' | awk '{print $$8}' | while read -r line; do echo "$$line test_$$line"; done > $(BUILD_DIR)/symbols.txt
	@$(COPY) --redefine-syms=$(BUILD_DIR)/symbols.txt $(PRJ).a $(BUILD_DIR)/$(TEST_LIB).a

link:
	@echo -e "\e[35mLinking tester\e[0m"
	@gcc $(OBJ) $(BUILD_DIR)/$(TEST_LIB).a -o $(BUILD_DIR)/$(PRJ)_test

clean:
	@rm -rf $(BUILD_DIR)

end:
	@echo -e "\e[33m\e[1mModule $(PRJ) built successfully\e[0m"

run:
	@clear
	@./$(BUILD_DIR)/$(PRJ)_test