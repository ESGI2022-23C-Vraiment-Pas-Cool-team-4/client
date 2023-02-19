BUILD_DIR = build
SRC_DIRS = src
# INCLUDES = includes


SRCS = $(shell find $(SRC_DIRS) -name '*.c') main.c
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -mwindows

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = exec

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)

# The final build step.
$(BUILD_DIR)/$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDES) -o $@

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: run
run:
	make && ./build/$(OBJ_NAME)