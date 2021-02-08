////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Подключение математических функций в LINUX и WINDOWS, а также для компилятора Intel.
         \en Connection of mathematical functions in LINUX and WINDOWS, and for Intel compiler. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MATHX_H
#define __MATHX_H

#include <math_cfg.h>

#if !defined ( C3D_WINDOWS )  //_MSC_VER

  // Only for LINUX 
  #if defined ( __INTEL_COMPILER ) 
    // Only INTEL COMPILER for LINUX
    #include <mathimf.h>
    #define _CMATH_
  #else // __INTEL_COMPILER
    // Other COMPILER for LINUX
    #include <math.h>
  #endif //__INTEL_COMPILER
  #include <stdint.h>
  #include <cstddef>

  #define _hypot hypot

  #ifndef __SIZEOF_WCHAR_T__ 
    #define __SIZEOF_WCHAR_T__  4
  #endif
   
  #define  DEPRECATE_DECLARE

#else // C3D_WINDOWS

  // Only for WINDOWS
  #ifndef __SIZEOF_WCHAR_T__ 
    #define __SIZEOF_WCHAR_T__  2
  #endif

  #if defined ( __INTEL_COMPILER ) 
    // Only INTEL COMPILER for WINDOWS 
    #include <mathimf.h>

    #define _hypot hypot
    #define _CMATH_
  #else // __INTEL_COMPILER
    // Only MS COMPILER for WINDOWS  
    #ifndef _USE_MATH_DEFINES 
      #define _USE_MATH_DEFINES  // \ru для подключения #define математических констант из math.h \en for connection #define of mathematical constants from math.h 
    #endif
    #include <math.h>

//-----------------------------------------------------------------------------
namespace c3d {
    # define _HYPOT_EPSILON   1.0E-20
    template <class T>
    T _hypot(T x, T y)
    {
       // Normalize x and y, so that both are positive and x >= y:
       x = fabs(x);
       y = fabs(y);

       if ( y > x ) {
         if(y * _HYPOT_EPSILON >= x)
            return y;

         T rat = x / y;
         return y * sqrt(1 + rat*rat);
       }
       else {
         if(x * _HYPOT_EPSILON >= y)
            return x;

         T rat = y / x;
         return x * sqrt(1 + rat*rat);
       }
    } // template <class T> T _hypot(T x, T y)
}
//-----------------------------------------------------------------------------
    #define _hypot c3d::_hypot

  #endif //__INTEL_COMPILER

#define DEPRECATE_DECLARE __declspec( deprecated( "This item is deprecated!" ) )

#endif //C3D_WINDOWS   


#endif // __MATHX_H
