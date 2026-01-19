cmake_minimum_required(VERSION 3.10)
project(CaseStudy_A1_tQR_Factorization VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关键：先指定 BLAS 供应商，再 find_package(BLAS)
set(BLA_VENDOR OpenBLAS)

# 如果你用的是 Homebrew，建议把前缀加入搜索路径（可选但很推荐）
list(APPEND CMAKE_PREFIX_PATH
  "/opt/homebrew/opt/openblas"
  "/opt/homebrew/opt/lapack"
)

find_package(MPI REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

add_executable(TEST test.cc)
add_executable(MAIN main.cc)

# 编译选项不要全局拼 CMAKE_CXX_FLAGS，改用 target 级别
target_compile_options(TEST PRIVATE -O3)
target_compile_options(MAIN PRIVATE -O3)

# 1) 解决 lapacke.h：显式找 header
find_path(LAPACKE_INCLUDE_DIR
  NAMES lapacke.h
  PATHS
    "/opt/homebrew/opt/lapack/include"
    "/opt/homebrew/include"
)

# 2) 解决 liblapacke：显式找库
find_library(LAPACKE_LIBRARY
  NAMES lapacke
  PATHS
    "/opt/homebrew/opt/lapack/lib"
    "/opt/homebrew/lib"
)

if (NOT LAPACKE_INCLUDE_DIR)
  message(FATAL_ERROR "Cannot find lapacke.h. Try: brew install lapack")
endif()

if (NOT LAPACKE_LIBRARY)
  message(FATAL_ERROR "Cannot find liblapacke. Try: brew install lapack")
endif()

target_include_directories(TEST PRIVATE
  ${LAPACKE_INCLUDE_DIR}
)

target_include_directories(MAIN PRIVATE
  ${LAPACKE_INCLUDE_DIR}
)

target_link_libraries(TEST PRIVATE
  MPI::MPI_CXX
  ${LAPACKE_LIBRARY}     # 先 lapacke（你 include 了 lapacke.h，通常需要）
  ${LAPACK_LIBRARIES}    # 再 LAPACK
  ${BLAS_LIBRARIES}      # 最后 BLAS(OpenBLAS)
)

target_link_libraries(MAIN PRIVATE
  MPI::MPI_CXX
  ${LAPACKE_LIBRARY}     # 先 lapacke（你 include 了 lapacke.h，通常需要）
  ${LAPACK_LIBRARIES}    # 再 LAPACK
  ${BLAS_LIBRARIES}      # 最后 BLAS(OpenBLAS)
)