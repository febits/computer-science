CC=gcc
CFLAGS=-Wall -Wextra -pedantic -Iinclude -g

BUILD_DIR=build
SRC_DIR=data-structures algorithms

SRC=$(shell find $(SRC_DIR) -name "*.c")
BIN=$(patsubst %.c, $(BUILD_DIR)/%, $(SRC))

LIB_SRC=$(wildcard lib/*.c)
LIB_BIN=$(BUILD_DIR)/utils.o

.PHONY: default always clean
default: always $(LIB_BIN) $(BIN)

$(LIB_BIN): $(LIB_SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)/%: %.c
	$(CC) $(CFLAGS) $(LIB_BIN) $< -o $(BUILD_DIR)/$(notdir $@)

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
