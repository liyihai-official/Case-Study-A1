cmake_minimum_required(VERSION 3.10)
project(CaseStudy_A1_tQR_Factorization VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------
# 1) Debug MODES: AUTO / ON / OFF
# -------------------------------------
set(DEBUG_LOG_MODE "AUTO" CACHE STRING "debug log: AUTO|ON|OFF")
set_property(CACHE DEBUG_LOG_MODE PROPERTY STRINGS AUTO ON OFF)

add_library(tqr_build_options INTERFACE)
add_library(tqr::build_options ALIAS tqr_build_options)

# target_compile_definitions(tqr_build_options INTERFACE
#   DEBUG_LOG=$<IF:$<STREQUAL:${DEBUG_LOG_MODE},ON>,1,
#              $<IF:$<STREQUAL:${DEBUG_LOG_MODE},OFF>,0,
#                   $<IF:$<CONFIG:Debug>,1,0>>>
# )
target_compile_definitions(tqr_build_options INTERFACE
  "DEBUG_LOG=$<IF:$<STREQUAL:${DEBUG_LOG_MODE},ON>,1,$<IF:$<STREQUAL:${DEBUG_LOG_MODE},OFF>,0,$<IF:$<CONFIG:Debug>,1,0>>>"
)


# -------------------------------------
# 2) BLAS/LAPACK/MPI
# -------------------------------------
set(BLA_VENDOR OpenBLAS)
list(APPEND CMAKE_PREFIX_PATH
  "/opt/homebrew/opt/openblas"
  "/opt/homebrew/opt/lapack"
)

find_package(MPI REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

find_path(LAPACKE_INCLUDE_DIR
  NAMES lapacke.h
  PATHS "/opt/homebrew/opt/lapack/include" "/opt/homebrew/include"
)
find_library(LAPACKE_LIBRARY
  NAMES lapacke
  PATHS "/opt/homebrew/opt/lapack/lib" "/opt/homebrew/lib"
)

if (NOT LAPACKE_INCLUDE_DIR)
  message(FATAL_ERROR "Cannot find lapacke.h. Try: brew install lapack")
endif()
if (NOT LAPACKE_LIBRARY)
  message(FATAL_ERROR "Cannot find liblapacke. Try: brew install lapack")
endif()

# -------------------------------------
# 3) Header-only library (INTERFACE)
# -------------------------------------
add_library(tqr INTERFACE)
add_library(tqr::tqr ALIAS tqr)

target_include_directories(tqr
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${LAPACKE_INCLUDE_DIR}
)

target_link_libraries(tqr
  INTERFACE
    tqr::build_options
    MPI::MPI_CXX
    ${LAPACKE_LIBRARY}
    ${LAPACK_LIBRARIES}
    ${BLAS_LIBRARIES}
)


# -------------------------------------
# 4) Executables
# -------------------------------------
add_executable(TEST test.cc)
add_executable(MAIN main.cc)

target_link_libraries(TEST PRIVATE tqr::tqr)
target_link_libraries(MAIN PRIVATE tqr::tqr)

target_compile_options(TEST PRIVATE -O3)
target_compile_options(MAIN PRIVATE -O3)
