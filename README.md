# InfomapProject

This project integrates the Infomap clustering algorithm via a custom C/C++ wrapper, allowing it to be called from Chapel.

## Directory Structure

- **external/infomap/**: Contains the Infomap source code (as a Git submodule).
- **external/install/**: The installation directory for Infomap (headers and static library).
- **src/**: Contains the wrapper code:
  - **run_infomap.h** and **run_infomap.cpp**: The wrapper functions for Infomap.
  - **infomap_wrapper.cpp**: A simple test program that calls the Infomap wrapper.
- **bin/**: The output directory for object files and executables.
- **Makefile**: Build script to compile and link the project.

## Building and Testing

1. Build and run the test executable:
   ```bash
   make clean
   make run
