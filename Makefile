#
# Copyright 2023 Dominik Chat
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

PRJ = libfingc

BUILD_DIR = build
OUTPUT_DIR = out
SRC_DIR = src
INC_DIR = include

SRC = $(shell find src/ -type f -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CFLAGS = \
	-std=gnu99 \
	-ffreestanding \
	-nostdlib \
	-O2 \
	-Wall \
	-Wextra \
	-c \

ARFLAGS = crs

CC = gcc
AR = ar

all: prepare $(OBJ) $(PRJ).a end

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e "\e[32mCompiling C object: $<\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I./$(INC_DIR) $< -o $@

%.a: $(OBJ)
	@echo -e "\e[35mCreating static library: $@\e[0m"
	@$(AR) $(ARFLAGS) $(BUILD_DIR)/$@ $(OBJ)

prepare:
	@echo -e "\e[33m\e[1mBuilding $(PRJ) module\e[0m"

end:
	@mkdir -p $(OUTPUT_DIR)
	@cp $(BUILD_DIR)/$(PRJ).a $(OUTPUT_DIR)/$(PRJ).a
	@cp -r include $(OUTPUT_DIR)/include
	@echo -e "\e[33m\e[1mModule $(PRJ) built successfully\e[0m"

clean:
	@rm -rf $(BUILD_DIR) $(OUTPUT_DIR)