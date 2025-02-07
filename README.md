# Infomap Wrapper Project

A C++ wrapper for the Infomap community detection algorithm.

## Getting Started

### Prerequisites
- C++ compiler with C++14 support
- OpenMP support
- Git

### Clone and Build

1. Clone the repository with its submodules:
```bash
# Clone the main repository
git clone https://github.com/mdindoost/InfomapProject.git
cd InfomapProject
'''

# Initialize and update the Infomap submodule
git submodule init
git submodule update

Build the project:

make clean
make

Run the test program:

./build/test_infomap
Project Structure

src/ - Source files
include/ - Header files
test/ - Test files
extern/ - External dependencies (Infomap)

Usage
The main interface is provided through the run_Infomap function:
cppCopyInfomapResult result = run_Infomap(src, dst, num_nodes, params);
Where:

src: Vector of source nodes
dst: Vector of destination nodes
num_nodes: Total number of nodes
params: InfomapParams structure with configuration options

Development Guide
Making Changes

Make your changes in the relevant files
Build and test:

make clean
make
./build/test_infomap
Committing Changes

Check status of changes:

git status

Add modified files:

git add <modified_files>

Commit changes:

git commit -m "Descriptive message about your changes"

Push to remote repository:

git push origin main
Updating Infomap Submodule
To update the Infomap submodule to its latest version:
cd extern/infomap
git pull origin master
cd ../..
git add extern/infomap
git commit -m "Update Infomap submodule"
git push origin main
Contributing

Create a new branch for your feature:

git checkout -b feature-name

Make your changes and commit them
Push the branch:

git push origin feature-name

Create a Pull Request on GitHub

License
This project is licensed under the MIT License - see the LICENSE file for details.
Acknowledgments

Infomap - The core community detection algorithm
