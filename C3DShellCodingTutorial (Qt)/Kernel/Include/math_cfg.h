////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Определение системы и платформы.
         \en System and platform definition. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MATH_CFG_H
#define __MATH_CFG_H

#if defined( WIN32 ) && !defined ( _WIN32 )
  #define _WIN32
#endif

#if defined( _WIN32 ) && !defined ( WIN32 )
  #define WIN32
#endif

#ifdef _WIN32
  #ifndef C3D_WINDOWS
    #define C3D_WINDOWS
  #endif
#elif defined(__FreeBSD__)
  #ifndef C3D_FreeBSD
    #define C3D_FreeBSD
  #endif
#elif defined(__APPLE__) && defined(__MACH__)
  #ifndef C3D_MacOS
    #define C3D_MacOS
  #endif
#elif defined(__gnu_linux__) || defined(__linux__)
  #ifndef C3D_LINUX
    #define C3D_LINUX
  #endif
#endif

#if !defined ( C3D_WINDOWS )  //_MSC_VER
  // Only for LINUX
  #if (defined(__x86_64__) || defined(__64BIT__) || defined(__arm64__) || (__WORDSIZE == 64))
    #define PLATFORM_64
  #else
    #define PLATFORM_32
  #endif

// \ru для совместимости с компиляцией интерфейсов объявленных в конвертерах \en to be compatible with the compilation of interfaces which are declared in converters
  #ifndef  __stdcall
    #define  __stdcall
  #endif //  __stdcall

#else // C3D_WINDOWS

// Only for WINDOWS
  #if (defined(_WIN64) || defined(WIN64))
    #define PLATFORM_64
  #else
    #define PLATFORM_32
  #endif

#endif //C3D_WINDOWS   


#endif // __MATH_CFG_H

