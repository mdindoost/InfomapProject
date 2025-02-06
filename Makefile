# Export the LD_LIBRARY_PATH so that the runtime linker finds the installed libraries.
export LD_LIBRARY_PATH := $(PWD)/external/install/lib:$(LD_LIBRARY_PATH)

# Compiler and Flags
CXX = g++
CFLAGS = -O3 -w -fPIC -I./external/install/include -I./external/infomap/include -c
LDFLAGS = -L./external/install/lib -Wl,-rpath,$(PWD)/external/install/lib -linfomap_static

# Directories
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = external/install/lib

# Targets
OBJECTS = $(BIN_DIR)/run_infomap.o
EXECUTABLE = $(BIN_DIR)/infomap_test

# Default Target: Build both the object file and test executable
all: $(OBJECTS) $(EXECUTABLE)

# Compile run_infomap.cpp into an object file for Chapel integration
$(BIN_DIR)/run_infomap.o: $(SRC_DIR)/run_infomap.cpp $(SRC_DIR)/run_infomap.h
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CFLAGS) $< -o $@

# Compile infomap_wrapper.cpp into a test executable
$(BIN_DIR)/infomap_test: $(SRC_DIR)/infomap_wrapper.cpp $(BIN_DIR)/run_infomap.o
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Run the test executable
run: all
	@LD_LIBRARY_PATH=$(PWD)/$(LIB_DIR):$$LD_LIBRARY_PATH ./$(BIN_DIR)/infomap_test

# Clean Build Artifacts
clean:
	@echo "Removing objects and executables..."
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/infomap_test *.log src/*~ include/*~ *~ core
