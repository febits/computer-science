CC=gcc
CFLAGS=-Wall -Wextra -pedantic -Iinclude -g

BUILD_DIR=build
SRC_DIR=data-structures algorithms

SRC=$(shell find $(SRC_DIR) -name "*.c")
BIN=$(patsubst %.c, $(BUILD_DIR)/%, $(SRC))

.PHONY: default always clean
default: always $(BIN)

$(BUILD_DIR)/%: %.c
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$(notdir $@)

always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
