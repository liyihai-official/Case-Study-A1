///
/// @file tsqr_assert.h
/// @brief tsqr custom assert macros and handlers
///         tsqr LOG macro for debugging
///
/// @author LI YIHAI
/// @version 0.1
/// @date 2026-01-21
///
#ifndef TSQR_ASSERT_H
#define TSQR_ASSERT_H

/// includes
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "../env/params.h"

/// 
/// -------------------------------------------------------------
/// Logging
/// -------------------------------------------------------------
///
/// @brief Custom Logging information handler
/// 

/// @brief Logging macro for debugging
/// @param msg Message to log
#if DEBUG_LOG
#define LOG(msg) \
  std::cout << "[LOG] " << msg << std::endl;
#else 
  #define LOG(msg) \
  do {} while(0)
#endif



/// 
/// -------------------------------------------------------------
/// Assertions
/// -------------------------------------------------------------
///
/// @brief Custom assert failure handler
/// 

namespace tsqr {
namespace details {

/// @brief Custom assert failure handler
/// @param expr_str Expression string that failed
/// @param file File name where assertion failed
/// @param line Line number where assertion failed
/// @param msg_ptr Message pointer to additional information
/// @return 
[[noreturn]] 
inline 
tsqr::Void 
tsqr_assert_fail(
  const tsqr::Char* expr_str,
  const tsqr::Char* file,
  tsqr::Int line,
  const tsqr::Char* msg_ptr = nullptr) 
  noexcept 
{
  std::cerr << "Assertion Failed: " << expr_str
            << ", file " << file
            << ", line " << line
            << std::endl;

  if (msg_ptr && msg_ptr[0] != '\0') {
    std::cerr << ", message: " << msg_ptr << std::endl;
  }
  std::abort();
}

} // end of namespace details
} // end of namespace tsqr




/// @brief Custom assert macro for debugging
/// @param expr Expression to assert
#define TSQR_ASSERT(expr)                         \
  do {                                            \
    const tsqr::Bool _tsqr_ok = static_cast<tsqr::Bool>(expr); \
    if (!_tsqr_ok) {                              \
      ::tsqr::details::tsqr_assert_fail(          \
        #expr, __FILE__, __LINE__, nullptr);      \
    }                                             \
  } while (0)

/// @brief Custom assert macro with message for debugging
/// @param expr Expression to assert
/// @param msg Message to display on failure
#define TSQR_ASSERT_MSG(expr, msg)                \
  do {                                            \
    const tsqr::Bool _tsqr_ok = static_cast<tsqr::Bool>(expr); \
    if (!_tsqr_ok) {                              \
      ::tsqr::details::tsqr_assert_fail(          \
        #expr, __FILE__, __LINE__, (msg));        \
    }                                             \
  } while (0)  



#endif // TSQR_ASSERT_H