CXX = g++
CXXFLAGS = -std=c++14 -Wall -fopenmp -I./include -I./extern/infomap/src
LDFLAGS = -fopenmp

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
WRAPPER_SRC = $(SRC_DIR)/infomap_wrapper.cpp
TEST_SRC = $(TEST_DIR)/test_infomap.cpp

# Object files
WRAPPER_OBJ = $(OBJ_DIR)/infomap_wrapper.o
TEST_OBJ = $(OBJ_DIR)/test_infomap.o

# Executables
TEST_EXEC = $(BUILD_DIR)/test_infomap

# Find all Infomap object files recursively (excluding main.o)
INFOMAP_OBJS = $(shell find extern/infomap/build/Infomap -name "*.o" ! -name "main.o")

# Default target
all: infomap $(TEST_EXEC)

# Create build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile Infomap library
.PHONY: infomap
infomap:
	cd extern/infomap && $(MAKE)

# Print object files (for debugging)
print-objects:
	@echo "Infomap objects: $(INFOMAP_OBJS)"

# Compile wrapper
$(WRAPPER_OBJ): $(WRAPPER_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test
$(TEST_OBJ): $(TEST_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link test executable
$(TEST_EXEC): $(WRAPPER_OBJ) $(TEST_OBJ) | $(BUILD_DIR)
	$(CXX) $(WRAPPER_OBJ) $(TEST_OBJ) $(INFOMAP_OBJS) -o $@ $(LDFLAGS)

# Run the program
.PHONY: run
run: all
	./$(TEST_EXEC)

# Build and run (shorthand)
.PHONY: test
test: run

# Clean
clean:
	rm -rf $(BUILD_DIR)
	cd extern/infomap && make clean

.PHONY: all clean print-objects run test