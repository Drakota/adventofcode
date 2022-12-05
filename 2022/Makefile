MAKEFLAGS += --silent
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -std=gnu11 -ggdb

BUILD_DIR := build
SOURCE := $(wildcard d*/*.c)
INPUT := $(wildcard d*/input/*.txt)
EXECUTABLES := $(patsubst %.c, $(BUILD_DIR)/%, $(SOURCE))
INPUT_HEADERS := $(patsubst %.txt, %.h, $(INPUT))
COMMON := $(wildcard common/*)

all: $(EXECUTABLES)

$(INPUT_HEADERS): $(INPUT)
	@printf "[*] Generating input header %s\n" $@
	xxd -i $(subst h,txt,$@) > $@

$(BUILD_DIR)/%.o: %.c $(COMMON) $(INPUT_HEADERS)
	@printf "[*] Building %s\n" $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	@printf "[*] Linking %s\n" $@
	@$(CC) $(CFLAGS) $< -o $@ $(COMMON)

clean:
	@printf "[*] Cleaning up build directory & input headers\n"
	@rm -rf $(subst 2022,,$(BUILD_DIR))
	@rm -rf $(INPUT_HEADERS)
