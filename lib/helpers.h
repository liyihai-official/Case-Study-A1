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
} // end of namespace tQR_project




#endif // HELPERS_H