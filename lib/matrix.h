///
/// @file matrix.h
/// @brief
///
/// @author LI YIHAI
/// @version 0.2
/// @date 2026-01-19 
///
#ifndef MATRIX_H
#define MATRIX_H


/// includes
#include <vector>
#include "../env/params.h"
#include "datahandler.h"

///
/// @brief Matrix class
///         Matrix class constructed from DataHandler object
///         Data stored in a 1D vector internally
///         Provides necessary Matrix operations (to be implemented)
/// @todo Implement more member functions as needed 
class Matrix {
public:
  
  Matrix() // default constructor
  { 
    #ifdef DEBUG_LOG
    std::cout 
    << "Matrix default constructor called." 
    << std::endl; 
    #endif 
  }; 
  ~Matrix() // destructor
  { 
    #ifdef DEBUG_LOG
    std::cout 
    << "Matrix destructor called." 
    << std::endl; 
    #endif 
  };   

  Matrix(const Matrix&);              // copy constructor
  Matrix& operator=(const Matrix&);   // copy assignment
  Matrix(Matrix&&) noexcept;                 // move constructor
  Matrix& operator=(Matrix&&) noexcept;      // move assignment



  /// Other Constructors
  
  /// @brief Parameterized constructor from dimensions
  /// @param rows Number of rows
  /// @param cols Number of columns
  Matrix(tQR_project::size_type rows, tQR_project::size_type cols) 
    : 
    numR_(rows), numC_(cols), 
    data_(rows * cols, static_cast<tQR_project::elem_type>(0)) 
  {
    #ifdef DEBUG_LOG
    std::cout 
    << "Matrix parameterized constructor called." 
    << std::endl;
    #endif
  }

  /// @brief Parameterized constructor from dimensions and initial value
  /// @param rows Number of rows
  /// @param cols Number of columns
  /// @param value Initial value to fill
  Matrix(tQR_project::size_type rows, tQR_project::size_type cols, tQR_project::elem_type value) 
    : 
    numR_(rows), 
    numC_(cols), 
    data_(rows * cols, value) 
  {
    #ifdef DEBUG_LOG
    std::cout 
    << "Matrix parameterized constructor with value called." 
    << std::endl;
    #endif
  }
  
  ///
  /// @brief Parameterized constructor from DataHandler
  /// @param dh DataHandler object
  ///
  Matrix(const DataHandler& dh) 
  {
    #ifdef DEBUG_LOG
    std::cout << "Matrix parameterized constructor called." << std::endl;
    #endif
    numR_ = dh.GetNumRows();
    numC_ = dh.GetNumCols();
    data_ = std::vector<tQR_project::elem_type>(dh.GetDataPointer(), 
              dh.GetDataPointer() + dh.GetNumElements());
  } 

  /// Other member functions to be implemented as needed

  tQR_project::size_type 
  GetNumElements() 
  const { return data_.size(); }
  
  tQR_project::size_type 
  GetNumRows()     
  const { return numR_; }
  
  tQR_project::size_type 
  GetNumCols()     
  const { return numC_; }

  // << and Show
  
  ///
  /// @brief Print matrix to console
  /// @return tQR_project::Void
  ///
  tQR_project::Void 
  Show() const 
  {
    #ifdef DEBUG_LOG
    std::cout << "Matrix show function called." << std::endl;
    std::cout << "Number of Rows: " << numR_ << std::endl;
    std::cout << "Number of Columns: " << numC_ << std::endl;
    std::cout << "Data: " << std::endl;
    #endif

    for (tQR_project::size_type i = 0; i < numR_; ++i) {
      for (tQR_project::size_type j = 0; j < numC_; ++j) {
        std::cout << data_[i * numC_ + j] << " ";
      }
      std::cout << std::endl;
    }
    return;
  };


  ///
  /// @brief Print matrix to output stream
  /// @param os Output stream
  /// @param mt Matrix to print
  /// @return Output stream
  ///
  friend std::ostream & operator<<(std::ostream &os, const Matrix &mt) {
    os << std::endl;
    for (tQR_project::size_type i = 0; i < mt.numR_; ++i) {
      for (tQR_project::size_type j = 0; j < mt.numC_; ++j) {
        os << mt.data_[i * mt.numC_ + j] << " ";
      }
      os << std::endl;
    }
    os << "(" << mt.numR_ << " x " << mt.numC_ << ")";
    return os;
  }

  // ptr operations
  tQR_project::elem_type* 
  GetDataPointer() 
  noexcept { return data_.data(); }
  
  const tQR_project::elem_type* 
  GetDataPointer() 
  const noexcept { return data_.data(); }  

  tQR_project::elem_type* 
  RowPtr(tQR_project::size_type r) 
  noexcept { return data_.data() + r * numC_; }
  
  const tQR_project::elem_type* 
  RowPtr(tQR_project::size_type r) 
  const noexcept { return data_.data() + r * numC_; }
  
  ///
  /// @brief Refers to the size of the Major Dimension (Row)
  /// @return Leading dimension (Row Major)
  ///
  tQR_project::size_type 
  LdaRowMajor() // Leading Dimension (Row Major)
  const noexcept { return numC_; }


  // elem operations
  tQR_project::elem_type& 
  GetElement(tQR_project::size_type row, tQR_project::size_type col) 
  noexcept { return data_[row * numC_ + col]; }

  const tQR_project::elem_type& 
  GetElement(tQR_project::size_type row, tQR_project::size_type col) 
  const noexcept { return data_[row * numC_ + col]; }



private:
  tQR_project::size_type numR_ {0}, numC_ {0};
  std::vector<tQR_project::elem_type> data_;
}; // end of class Matrix

#endif // MATRIX_H
