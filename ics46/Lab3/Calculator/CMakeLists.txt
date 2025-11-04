cmake_minimum_required(VERSION 3.10)

# Project name
project(Calculator_cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the main executable
file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp) # Exclude main.cpp for tests
add_executable(Calculator ${SRC_FILES} src/main.cpp) # Add main.cpp only for the main executable

# Google Test setup
# Download and add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add the test executable
file(GLOB TEST_FILES CONFIGURE_DEPENDS gtest/*.cpp)
add_executable(CalculatorTests ${TEST_FILES} ${SRC_FILES}) # Exclude main.cpp

# Link Google Test libraries to the test executable
target_link_libraries(CalculatorTests gtest gtest_main)

# Enable testing
enable_testing()

# Add a test for the Google Test executable
add_test(NAME CalculatorTests COMMAND CalculatorTests)