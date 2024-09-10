cmake_minimum_required(VERSION 3.10)
project(general_inter_p_lib)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
    -Wcast-align
    -Wpedantic
    -Wcast-qual
    -Wconversion
    -Wnon-virtual-dtor
    -Wmissing-include-dirs
    -Wdisabled-optimization
    -Winit-self
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wparentheses
    -Wredundant-decls
    -Wunused
    -Wmisleading-indentation
    -Wduplicated-branches
    -Wnull-dereference
    -Wformat=2
    -Wimplicit-fallthrough
    -Wshadow
    -Wsign-promo
    -Wstrict-aliasing
    -Wall
    -Wextra

    # -Wctor-dtor-privacy
    # -Wdouble-promotion
    -Werror # uncomment to treat warnings as errors
)

# Add the source files for the library
add_library(general_inter_p_lib src/shared_memory.cpp)

# Add the source files for the test executable
add_executable(general_inter_p_lib_test
    test/shared_memory_test.cpp
    test/image_test.cpp
    src/shared_memory.cpp
    src/shared_memory.h
    src/image.h
)

add_executable(general_inter_p_lib_run
    src/output.cpp
)

# Add this before the `FetchContent_MakeAvailable` call
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest ${CMAKE_BINARY_DIR}/googletest)

# the include(fetchcontent) is not needed anymore as
# the gtest is now cloned in the project directory
# using cd /home/s0001480/Documents/Cpp_src/general_Inter_p_lib
# general_Inter_p_lib$ git clone https://github.com/google/googletest.git

# Add the gtest library
# include(FetchContent)
# FetchContent_Declare(
# googletest
# URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
# DOWNLOAD_EXTRACT_TIMESTAMP true
# )
# FetchContent_MakeAvailable(googletest)

# Link the gtest library and the lib_inter_p_com to the test executable
target_link_libraries(general_inter_p_lib_test PRIVATE gtest gtest_main general_inter_p_lib rt)

# Include directories for headers
target_include_directories(general_inter_p_lib_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add a custom target for formatting
find_program(CLANG_FORMAT "clang-format")

if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${ALL_CXX_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running clang-format"
        VERBATIM
    )
else()
    message(WARNING "clang-format not found. Formatting target will not be available.")
endif()