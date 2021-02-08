////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Сервис для обработки ошибок.
         \en Error-handling services. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TOOL_ERR_HANDLING_H
#define __TOOL_ERR_HANDLING_H

#include <math_define.h>


//------------------------------------------------------------------------------
/**
  \brief   \ru Определение режима обработки исключений.
           \en Definition of mode for exception handling. \~
  \details \ru Определяет, пробрасывать ли исключение дальше после его обработки. По умолчанию исключения подавляются. \n
           \en Defines, whether to throw exception further after its processing. By default, exceptions are suppressed. \~
  \ingroup Base_Tools
*/
//---
class MATH_CLASS ExceptionMode
{
  static bool sExptEnabled;
public:
  // \ru  Установить режим обработки исключений: true, чтобы пробрасывать исключения дальше; false, чтобы подавлять исключения.
  //      Возвращает предыдущий режим.
  // \en  Set mode for exception handling: true - to throw exceptions further; false - to suppress exceptions.
  //      Return the previous mode.
  static bool Enable( bool enabled = true );

  // \ru Получить текущий режим обработки исключений (true - пробрасывать исключение дальше; false - нет).
  // \en Get current exception handling mode (true - to throw exception further; false - to not throw).
  static bool IsEnabled();
};

//------------------------------------------------------------------------------
/**
  \brief \ru Меняет режим обработки исключений в области видимости.
         \en Alter mode for exception handling in a scope. \~
  \ingroup Base_Tools
*/
//---
class MATH_CLASS ScopedExceptionMode
{
  bool m_oldMode;
public:
  ScopedExceptionMode( bool mode = true ) { m_oldMode = ExceptionMode::Enable( mode ); }
  ~ScopedExceptionMode() { ExceptionMode::Enable( m_oldMode ); }
};


//------------------------------------------------------------------------------
/**
  \brief \ru Бросить указанное исключение, если режим позволяет.
         \en Throw the specified exception if allowed by the exception mode. \~
  \ingroup Base_Tools
*/
//---
#define C3D_CONTROLED_THROW_EX(expt) if( ExceptionMode::IsEnabled() ) throw expt;

//------------------------------------------------------------------------------
/**
  \brief \ru Бросить исключение, если режим позволяет.
         \en Throw exception if allowed by the mode for exception handling. \~
  \ingroup Base_Tools
*/
//---
#define C3D_CONTROLED_THROW if( ExceptionMode::IsEnabled() ) throw;

#endif // __TOOL_ERR_HANDLING_H
