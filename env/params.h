///
/// @file params.h
/// @brief This file contains key parameters for the project.
///         Vector size is N x 1
///         Matrix size is M x N
///         Datatype of elements is float64 aka double
/// @author LI YIHAI
/// @version 0.1
/// @date 2026-01-19 
///
#ifndef PARAMS_H_LI
#define PARAMS_H_LI

/// includes 
#include <cstdint>  // C Standard Integer types
#include <string>   // 'std::string' type
#include <iostream> // Necessary IO streams

///
/// MATC: Matrix Col size
/// MATR: Matrix Row size
/// 
#undef MATC
#undef MATR

#define MATC 1000  // Matrix Col size
#define MATR 10000 // Matrix Row 


///
/// Datatype of elements
///
namespace tQR_project
{
  // Type Aliases
  using Byte  = uint8_t;
  using Word  = uint16_t;
  using Dword = uint32_t;
  using Qword = uint64_t;

  // Types
  using Int = int;
  using UnsignedInt = unsigned int;
  using Float       = float;
  using Double      = double;
  using Char        = char;
  using Bool        = bool;
  using String      = std::string;
  using Void        = void;

  // Define types
  typedef Dword   size_type;
  typedef Double  elem_type;
} // end of namespace tQR_project


#endif // end of define PARAMS_H_LI