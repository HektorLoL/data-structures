# this code was taken by the tutorial:
#	https://makefiletutorial.com/#makefile-cookbook

# the name of the result/executable
TARGET_EXEC := ./main

# where all the object files (.o) will be
BUILD_DIR := ./build
# the src directories (plural because it may have other directories inside of it)
SRC_DIRS := ./src

# all .c files included in the src directories
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# all objects (.o) files need to compile the main executable
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# DEBUG
#   you could also put these flags in the make command,
#   like: `sudo make CFLAGS='-Wall -g'`
CFLAGS := -Wall -g

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@) # -p option for ignoring existing files
	$(CC) $(INC_FLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)%