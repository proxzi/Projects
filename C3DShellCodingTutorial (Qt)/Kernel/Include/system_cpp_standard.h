////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Макросы стандартов C и C++.
         \en C\C++ standards. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEM_CPP_STANDARD_H
#define __SYSTEM_CPP_STANDARD_H

#include <cstddef>
#include <math_cfg.h>

// С11
#if (defined(_MSC_VER) && (_MSC_VER > 1600)) || (defined(__INTEL_C) ) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || (defined(__BORLANDC__)) // BORLAND version?
#define STANDARD_C11
#endif
// C11 with thread_local support
#if (defined(_MSC_VER) && (_MSC_VER >= 1900)) || (defined(__INTEL_C) ) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || (defined(__BORLANDC__)) // BORLAND version?
#define STANDARD_C11_THREAD
#endif

// С++11
#if defined(__cplusplus) && (__cplusplus >= 201103L) // С++11 (fully supported)
#define STANDARD_CPP11
#define STANDARD_C11_THREAD
#endif

// GCC version (https://sourceforge.net/p/predef/wiki/Compilers/)
#if !defined(C3D_WINDOWS)  // _MSC_VER
  #if defined(__GNUC__)
    #if defined(__GNUC_MINOR__)
      #if defined(__GNUC_PATCHLEVEL__)
        #define C3D_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
      #else
        #define C3D_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
      #endif
    #else
      #define #define C3D_GCC_VERSION (__GNUC__ * 10000)
    #endif
  #else
    #define C3D_GCC_VERSION 0
  #endif
#else  // C3D_WINDOWS
  #define C3D_GCC_VERSION 0
#endif  // C3D_WINDOWS

#if defined(__clang__)  // Clang compiler
  #define C3D_CLANG_COMPILER
#endif  // Clang compiler

// GNU glibc version.
#if defined(C3D_LINUX)  // Linux
  #include <features.h>
  #if defined(__GLIBC__) && defined(__GLIBC_MINOR__)
    #define C3D_GLIBC_VERSION (__GLIBC__ * 1000 + __GLIBC_MINOR__)
  #else
    #define C3D_GLIBC_VERSION 0
  #endif
#else
  #define C3D_GLIBC_VERSION 0
#endif

#if ( defined(STANDARD_C11) || defined(STANDARD_CPP11) )
#define STANDARD_CPP11_RVALUE_REFERENCES
#endif


#endif // __SYSTEM_CPP_STANDARD_H
