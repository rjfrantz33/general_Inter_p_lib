
# Summary 

To build and compile this project using CMake, follow these steps:

Navigate to the build directory: cd build

Run CMake to configure the project: cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 

Compile the project: make or make all

This will configure and compile the project, generating the necessary binaries and test executables.

You will then executable files, as defined in the CMakeLists.txt:

to see them, run:

$ find . -executable -type f

