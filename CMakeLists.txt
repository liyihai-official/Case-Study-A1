cmake_minimum_required(VERSION 3.10)
project(CaseStudy_A1_tQR_Factorization VERSION 0.1 LANGUAGES CXX)

set(PROJECT_AUTHOR "LI YIHAI")

# Find Packages
find_package(MPI REQUIRED)
# if (MPI_FOUND)
#   message(STATUS "MPI found")
#   set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
# else()
#   message(FATAL_ERROR "MPI not found")

# C++ Standard Required C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_COMPILER_PATH ${CMAKE_CXX_COMPILER})

set(PROJECT_SOURCES 
  test.cc 
)

# Compile Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# EXECS 
add_executable(TEST test.cc ${PROJECT_SOURCES})

# Link MPI
if(MPI_FOUND)
  target_link_libraries(TEST PRIVATE MPI::MPI_CXX)
endif()

# RELEASE MODE
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(TEST PRIVATE NDEBUG)
endif()