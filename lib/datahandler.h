///
/// @file datahandler.h
/// @brief Datahandler class declaration
///
/// @author LI YIHAI
/// @version 0.1
/// @date 2026-01-19 
///

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

/// includes
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>

#include "../env/params.h"


///
/// @brief Datahandler
///         Loading data from file.
///         Assignment requirement: Support vector and matrix data
///         Data stored in a 1D vector internally   
///
class DataHandler {
public:
  DataHandler() {  std::cout << "DataHandler default constructor called." << std::endl; }; // default empty constructor
  DataHandler(const DataHandler&);            // copy constructor
  DataHandler& operator=(const DataHandler&); // copy assignment
  DataHandler(DataHandler&&) noexcept;                 // move constructor
  DataHandler& operator=(DataHandler&&) noexcept;      // move assignment

  ~DataHandler() { std::cout << "DataHandler destructor called." << std::endl; }; // destructor

  // Constructor: Load data from file 
  DataHandler(const tQR_project::String& filename) 
  {
    std::cout << "DataHandler parameterized constructor called." << std::endl;
    std::ifstream infile(filename);
    if (!infile) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return;
    }

    tQR_project::elem_type value;
    while (infile >> value) {
      data_.push_back(value);
    }
    infile.close();

    num_elem_ = data_.size();

    // DEBUG TEST
    // For demonstration, assume a fixed number of columns
    numC_ = 1; 
    numR_ = (num_elem_ + numC_ - 1) / numC_; // Ceiling division
  }

  /// @brief Reshape data into matrix form
  /// @param rows Number of rows
  /// @param cols Number of columns
  tQR_project::Void Reshape(tQR_project::size_type rows, tQR_project::size_type cols) 
  {
    if (rows * cols != num_elem_) {
      std::cerr << "Reshape error: total elements do not match." << std::endl;
      return;
    } 
    numR_ = rows;
    numC_ = cols;
    return;
  };


  /// @brief Split a head portion of data as a new DataHandler object
  /// @param count Number of elements to split
  /// @return New DataHandler object containing the split data
  DataHandler Split_head(tQR_project::size_type count) 
  {
    DataHandler new_handler;
    if (count > num_elem_) {
      count = num_elem_;
    }
    new_handler.data_.assign(data_.begin(), data_.begin() + count);
    new_handler.num_elem_ = count;
    new_handler.numC_ = numC_;
    new_handler.numR_ = (count + numC_ - 1) / numC_; // Ceiling division
    data_.erase(data_.begin(), data_.begin() + count);
    num_elem_ -= count;
    numR_ = (num_elem_ + numC_ - 1) / numC_; // Update number of rows
    return new_handler;
  };


  /// @brief Split a tail portion of data as a new DataHandler object
  /// @param count Number of elements to split
  /// @return New DataHandler object containing the split data
  DataHandler Split_tail(tQR_project::size_type count)
  {
    DataHandler new_handler;
    if (count > num_elem_) {
      count = num_elem_;
    }
    new_handler.data_.assign(data_.end() - count, data_.end());
    new_handler.num_elem_ = count;
    new_handler.numC_ = numC_;
    new_handler.numR_ = (count + numC_ - 1) / numC_; // Ceiling division
    data_.erase(data_.end() - count, data_.end());
    num_elem_ -= count;
    numR_ = (num_elem_ + numC_ - 1) / numC_; // Update number of rows
    return new_handler;
  };

  tQR_project::Void Fill(tQR_project::elem_type value) 
  {
    std::fill(data_.begin(), data_.end(), value);
    return;
  };

  tQR_project::Void Fill_Zero()
  {
    Fill(static_cast<tQR_project::elem_type>(0));
    return;
  }

  tQR_project::Void Show() 
  {
    std::cout << "DataHandler show function called." << std::endl;
    std::cout << "Number of elements: " << num_elem_ << std::endl;
    std::cout << "Number of Rows: " << numR_ << std::endl;
    std::cout << "Number of Columns: " << numC_ << std::endl;
    std::cout << "Data: " << std::endl;
    for (tQR_project::size_type i = 0; i < num_elem_; ++i) {
      std::cout << data_[i] << " ";
      if ((i + 1) % numC_ == 0) {
        std::cout << std::endl;
      }
    }
    return;
  };


  tQR_project::size_type GetNumElements() const { return num_elem_; }
  tQR_project::size_type GetNumRows()     const { return numR_; }
  tQR_project::size_type GetNumCols()     const { return numC_; }


  tQR_project::elem_type* GetDataPointer() noexcept { return data_.data(); }
  const tQR_project::elem_type* GetDataPointer() const noexcept { return data_.data(); }


private:
  std::vector<tQR_project::elem_type> data_;
  tQR_project::size_type num_elem_ {0}, numR_ {0}, numC_ {0};
}; // end of class DataHandler









/// @brief Copy constructor
/// @param other 
inline
DataHandler::DataHandler(const DataHandler& other)
  : data_(other.data_),
    num_elem_(other.num_elem_),
    numR_(other.numR_),
    numC_(other.numC_) 
{
}

/// @brief Copy assignment operator
/// @param other 
/// @return Reference to this object
inline
DataHandler& DataHandler::operator=(const DataHandler& other) {
  if (this != &other) {
    data_ = other.data_;
    num_elem_ = other.num_elem_;
    numR_ = other.numR_;
    numC_ = other.numC_;
  }
  return *this;
}

/// @brief Move constructor
/// @param other 
inline
DataHandler::DataHandler(DataHandler&& other) noexcept
  : data_(std::move(other.data_)),
    num_elem_(other.num_elem_),
    numR_(other.numR_),
    numC_(other.numC_) 
{
  other.num_elem_ = 0;
  other.numR_ = 0;
  other.numC_ = 0;
}

/// @brief Move assignment operator
/// @param other 
/// @return Reference to this object
inline
DataHandler& DataHandler::operator=(DataHandler&& other) noexcept {
  if (this != &other) {
    data_ = std::move(other.data_);
    num_elem_ = other.num_elem_;
    numR_ = other.numR_;
    numC_ = other.numC_;

    other.num_elem_ = 0;
    other.numR_ = 0;
    other.numC_ = 0;
  }
  return *this;
}


#endif // DATAHANDLER_H