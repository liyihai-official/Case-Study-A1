///
/// @file matrix.h
/// @brief
///
/// @author LI YIHAI
/// @version 0.1
/// @date 2026-01-19 
///


#ifndef MATRIX_H
#define MATRIX_H


/// includes
#include <vector>
#include "../env/params.h"
#include "datahandler.h"


/// @brief Matrix class
///         Matrix class constructed from DataHandler object
///         Data stored in a 1D vector internally
///         Provides necessary Matrix operations (to be implemented)
///
class Matrix {
public:
  Matrix() { std::cout << "Matrix default constructor called." << std::endl; }; // default constructor

  ///
  /// @brief Parameterized constructor from DataHandler
  /// @param dh DataHandler object
  Matrix(const DataHandler& dh) 
  {
    std::cout << "Matrix parameterized constructor called." << std::endl;
    numR_ = dh.GetNumRows();
    numC_ = dh.GetNumCols();
    data_ = std::vector<tQR_project::elem_type>(dh.GetDataPointer(), 
              dh.GetDataPointer() + dh.GetNumElements());
  } 

  

  ~Matrix() { std::cout << "Matrix destructor called." << std::endl; }; // destructor
  
private:
  tQR_project::size_type numR_ {0}, numC_ {0};
  std::vector<tQR_project::elem_type> data_;
}; // end of class Matrix







#endif // MATRIX_H
