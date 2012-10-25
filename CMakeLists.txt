# We start by saying what version of cmake we're using.
cmake_minimum_required(VERSION 2.8)

# This sets the name of the project.
project(Assignment4)

# We can manually set compiler flags via cmake's set command.  
# -Wall enables all compiler warnings. You should get in the habit of
# using it.
# -g enables debugger symbols.
# -std=c++0x enables C++11.
set(CMAKE_CXX_FLAGS "-g -Wall")

# We use this line to specify the location of the compiler's output.
# PROJECT_SOURCE_DIR is a cmake variable that specifies the current
# directory.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# we use include_directories to tell cmake where our source folders
# are.
include_directories(
  ${PROJECT_SOURCE_DIR}
)

# These commands add Google test. The add_subdirectory command is a
# bit like an "include" for building your project. It causes cmake to
# recursively work on creating build files for the specified
# subdirectory.
#add_subdirectory(${PROJECT_SOURCE_DIR}/gtest-1.6.0)
#include_directories(${PROJECT_SOURCE_DIR}/gtest-1.6.0/include)

# The add_executable command takes an executable name and a list of
# source files. In this case the source files will be compiled into a
# binary named tests
add_executable(project4.out 
  adt4_test.cpp
  job.cpp
  jobQueue.cpp
)

# The target_link_libraries takes a binary name and a library
#target_link_libraries(out gtest_main)
