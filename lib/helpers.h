#ifndef HELPERS_H
#define HELPERS_H

#include "../env/params.h"
#include "datahandler.h"
#include "matrix.h"
#include <unistd.h>
#include <iomanip>

namespace tQR_project {

  void sleeper(tQR_project::size_type seconds) {
    std::cout << "====================================================";
    sleep(seconds);
    std::cout << std::endl;
  }
  // std::ostream & operator<<(std::ostream &os, const DataHandler &dh) {
  //   os << "DataHandler: " << dh.GetNumRows() << " x " << dh.GetNumCols() 
  //      << ", Total elements: " << dh.GetNumElements() << std::endl;
  //   for (tQR_project::size_type i = 0; i < dh.GetNumRows(); ++i) {
  //     for (tQR_project::size_type j = 0; j < dh.GetNumCols(); ++j) {
  //       os << dh.GetElement(i, j) << " ";
  //     }
  //     os << std::endl;
  //   }
  //   return os;
  // }

} // end of namespace tQR_project




#endif // HELPERS_H