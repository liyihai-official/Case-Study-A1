/// 
/// 
/// @file main.cc
/// @brief Main program for Tall Skinny QR Factorization, 
///         for solving Ax=b linear equations.
///
/// @author LI YIHAI
/// @version 0.1
/// @date 2026-01-19 
///
///


/// includes libs + env
#include "env/params.h"
#include "lib/helpers.h"
#include "lib/datahandler.h"
#include "lib/matrix.h"

/// includes LAPACK + C-BLAS
#include <lapacke.h>
#include <cblas.h>


int main ()
{
  std::cout << "Sequential program is running. " << std::endl;
  std::cout << "Vector size V: " << tsqr::size_type(MATC) << std::endl;
  std::cout << "Matrix size MATR x MATC: " << tsqr::size_type(MATR) 
            << " x " << tsqr::size_type(MATC) << std::endl
            << std::endl;            
  // tsqr::sleeper(1);          
  
  tsqr::String fn {"../data/test.txt"};
  DataHandler dh {fn};
  std::cout << "Data loaded from file: " << fn << std::endl;
  // tsqr::sleeper(1);

  DataHandler dh_b = dh.Split_head(MATR);
  dh.Reshape(MATR, MATC);

  Matrix mt_A(dh);
  Matrix mt_b(dh_b);
  Matrix mt_tau(1, MATC, 0);
  
  // tsqr::sleeper(1);

  {
    LAPACKE_dgeqrf(LAPACK_ROW_MAJOR, 
      static_cast<tsqr::Int>(dh.GetNumRows()), 
      static_cast<tsqr::Int>(dh.GetNumCols()), 
      mt_A.GetDataPointer(),      // Placeholder for data pointer
      static_cast<tsqr::Int>(dh.GetNumCols()), 
      mt_tau.GetDataPointer()     // Placeholder for tau pointer
    );

    LAPACKE_dormqr(LAPACK_ROW_MAJOR, 'L', 'T', 
      static_cast<tsqr::Int>(dh_b.GetNumRows()), 
      static_cast<tsqr::Int>(1), 
      static_cast<tsqr::Int>(dh.GetNumCols()), 
      mt_A.GetDataPointer(),
      static_cast<tsqr::Int>(dh.GetNumCols()),
      mt_tau.GetDataPointer(),
      mt_b.GetDataPointer(),
      static_cast<tsqr::Int>(1)
    );
  }  
  // tsqr::sleeper(1);


  /// Get Result of 'x'
  Matrix R(MATC, MATC, 0);
  for (int i = 0; i < MATC; ++i) {
    for (int j = i; j < MATC; ++j) {
      R.GetElement(i,j) = mt_A.GetElement(i,j);
    }
  }

  Matrix x(MATC, 1, 0);
  for (int i = 0; i < MATC; ++i) x.GetElement(i,0) = mt_b.GetElement(i,0);

  tsqr::Int info = LAPACKE_dtrtrs(
    LAPACK_ROW_MAJOR,
    'U',   // upper triangular
    'N',   // No transpose
    'N',   // Non-unit diagonal
    MATC,  // Column of Matrix
    1,     // nrhs
    R.GetDataPointer(),
    MATC,  // lda = n in row-major for n×n
    x.GetDataPointer(),
    1      // ldb = nrhs in row-major
  );
  if (info != 0) { /* handle */ }  



  return 0;
}