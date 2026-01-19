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
  Matrix(const Matrix&);            // copy constructor
  Matrix& operator=(const Matrix&); // copy assignment
  Matrix(Matrix&&) noexcept;                 // move constructor
  Matrix& operator=(Matrix&&) noexcept;      // move assignment
  ~Matrix() { std::cout << "Matrix destructor called." << std::endl; }; // destructor

  /// Other Constructors
  
  /// @brief Parameterized constructor from dimensions
  /// @param rows Number of rows
  /// @param cols Number of columns
  Matrix(tQR_project::size_type rows, tQR_project::size_type cols) 
    : numR_(rows), numC_(cols), data_(rows * cols, static_cast<tQR_project::elem_type>(0)) 
  {
    std::cout << "Matrix parameterized constructor called." << std::endl;
  }

  /// @brief Parameterized constructor from dimensions and initial value
  /// @param rows Number of rows
  /// @param cols Number of columns
  /// @param value Initial value to fill
  Matrix(tQR_project::size_type rows, tQR_project::size_type cols, tQR_project::elem_type value) 
    : numR_(rows), numC_(cols), data_(rows * cols, value) 
  {
    std::cout << "Matrix parameterized constructor with value called." << std::endl;
  }
  
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

  /// Other member functions to be implemented as needed
  
  // << and Show
  tQR_project::Void Show() const 
  {
    std::cout << "Matrix show function called." << std::endl;
    std::cout << "Number of Rows: " << numR_ << std::endl;
    std::cout << "Number of Columns: " << numC_ << std::endl;
    std::cout << "Data: " << std::endl;
    for (tQR_project::size_type i = 0; i < numR_; ++i) {
      for (tQR_project::size_type j = 0; j < numC_; ++j) {
        std::cout << data_[i * numC_ + j] << " ";
      }
      std::cout << std::endl;
    }
    return;
  };

  friend std::ostream & operator<<(std::ostream &os, const Matrix &mt) {
    os << "Matrix: " << mt.numR_ << " x " << mt.numC_ << std::endl;
    for (tQR_project::size_type i = 0; i < mt.numR_; ++i) {
      for (tQR_project::size_type j = 0; j < mt.numC_; ++j) {
        os << mt.data_[i * mt.numC_ + j] << " ";
      }
      os << std::endl;
    }
    return os;
  }

  // ptr
  tQR_project::elem_type* GetDataPointer() noexcept { return data_.data(); }
  const tQR_project::elem_type* GetDataPointer() const noexcept { return data_.data(); }  

  // elem
  tQR_project::elem_type& GetElement(tQR_project::size_type row, tQR_project::size_type col) noexcept 
  { return data_[row * numC_ + col]; }
  const tQR_project::elem_type& GetElement(tQR_project::size_type row, tQR_project::size_type col) const noexcept 
  { return data_[row * numC_ + col]; }


private:
  tQR_project::size_type numR_ {0}, numC_ {0};
  std::vector<tQR_project::elem_type> data_;
}; // end of class Matrix

#endif // MATRIX_H
