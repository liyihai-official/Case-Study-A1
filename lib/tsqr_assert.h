///
///
///
///
#ifndef TSQR_ASSERT_H
#define TSQR_ASSERT_H

/// includes
#include <cassert>
#include <iostream>
#include <cstdlib>
#include "../env/params.h"


/// @brief Logging macro for debugging
/// @param msg Message to log
#if DEBUG_LOG
#define LOG(msg) \
  std::cout << "[LOG] " << msg << std::endl;
#else 
  #define LOG(msg) \
  do {} while(0)
#endif



/// @brief Custom assert macro for debugging
/// @param expr Expression to assert
#define TSQR_ASSERT(expr) \
  if (!(expr)) { \
    std::cerr << "Assertion Failed: " #expr \
              << ", file " << __FILE__ \
              << ", line " << __LINE__ \
              << std::endl; \
    assert(expr); \
  }

#endif // TSQR_ASSERT_H