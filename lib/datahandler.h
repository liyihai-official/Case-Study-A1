#if !defined(DATAHANDLER_H)

#define DATAHANDLER_H
#include <vector>
#include <fstream>
#include <iostream>
#include "../env/params.h"

class DataHandler {
public:
  DataHandler() { 
    std::cout << "DataHandler default constructor called." << std::endl; 
  };
  
  ~DataHandler() { 
    std::cout << "DataHandler destructor called." << std::endl; 
  };

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

private:
  std::vector<tQR_project::elem_type> data_;
  tQR_project::size_type num_elem_ {0}, numR_ {0}, numC_ {0};
};


#endif // DATAHANDLER_H