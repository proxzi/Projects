////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Логирование информации.
         \en Information logging. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __TOOL_LOG_H
#define __TOOL_LOG_H

#include <io_define.h>
#include <tool_cstring.h>
#include <math_define.h>

//------------------------------------------------------------------------------
// \ru Потокобезопасные интерфейсы для ведение журнала сообщений и записи его в файл.
//     Для каждого потока ведется отдельный лог, который записывается в отдельный файл.
//     Доступны в дебаге.
// \en Thread-safe interfaces for logging messages and writing the log to the file.
//     Keep a separate log for each thread which is saved to a separate file.
//     Available in debug configuration.
//
/* \ru Пример использования. \en Usage sample. 
 int k = 0;
 START_LOGGING;                      // \ru Начинаем логирование. \en Start logging.
 LOG_MSG( _T("Samplelog") );         // \ru Добавляем указанную строку в лог. \en Put a specified string to the log.
 ...
 // \ru Форматируем строку лога (оператор << Logger::Endl добавляет ее в лог). \en Format a log line (operator << Logger::Endl puts it to the log).
 Logger::Get() << _T("Value ") << k << Logger::Endl;
 ...
 WRITE_LOG_FILE( _T("sample.log") ); // \ru Записываем лог в файл. \en Write the log to the file.
 END_LOGGING;                        // \ru Заканчиваем логирование. \en Stop logging.
*/
// ---
#ifdef C3D_DEBUG

//------------------------------------------------------------------------------
// \ru Класс позволяет форматировать строку для лога и добавлять ее в лог.
// \en Class allows to format a line to the log and put it to the log.
// ---
class MATH_CLASS Logger
{
public:
  // \ru Получить логгер. \en Get the logger.
  static Logger& Get();

  // \ru Следующие методы позволяют форматировать строку для лога. Работают с текущей строкой лога.
  // \en Next methods allow to format a line to the log. Work with the current line of the log.

  // \ru Добавить строку в текущую строку лога. \en Add a string to the current line of the log.
  virtual Logger& operator << ( const TCHAR * ) = 0;
  // \ru Добавить integer в текущую строку лога. \en Add integer to the current line of the log.
  virtual Logger& operator << ( const int & ) = 0;
#if defined(PLATFORM_64) // \ru x32 совпадение типов ptrdiff_t и int \en x32 coincidence of ptrdiff_t and int types
  // \ru Добавить ptrdiff_t в текущую строку лога. \en Add ptrdiff_t to the current line of the log.
  virtual Logger& operator << ( const ptrdiff_t & ) = 0;
#endif
  // \ru Добавить size_t в текущую строку лога. \en Add size_t to the current line of the log.
  virtual Logger& operator << ( const size_t & ) = 0;
  // \ru Добавить double в текущую строку лога. \en Add double to the current line of the log.
  virtual Logger& operator << ( const double & ) = 0;
  // \ru Завершить форматирование текущей строки и добавить ее в лог. Следующий вызов оператора << создаст новую текущую строку.
  // \en Finish formatting of the current line and add it to the log. Next call to the operator << will create new current line.
  virtual Logger& operator << ( Logger& (*man)( Logger& ) ) = 0;

  // \ru Манипулятор-признак завершения форматирования текущей строки лога.
  // \en Manipulator-indicator of finishing formatting of the current line of the log.
  static Logger& Endl( Logger& );
};

// \ru Начать или закончить логирование. \en Start or stop logging.
MATH_FUNC(void) SetLogging( bool allow );

// \ru Записать лог в файл. Лог для каждого потока записывается в отдельный файл.
// \en Write the log to the file. Log of each thread writes to a separate file.
MATH_FUNC(void) WriteLog( const TCHAR *fileName );

// \ru Записать указанную строку в лог. \en Write a specified string to the log.
MATH_FUNC(void) LogMessage( const c3d::string_t &msg );

// \ru Макросы для операций логирования. \en Logging macros.

// \ru Начать логирование. \en Start logging.
#define START_LOGGING SetLogging( true );
// \ru Закончить логирование. \en Stop logging.
#define END_LOGGING SetLogging( false );
// \ru Положить форматированную строку в лог. \en Put a formatted string to the log.
#define LOG_MSG(msg) LogMessage( msg );
// \ru Записать лог в файл. Лог для каждого потока записывается в отдельный файл.
// \en Write the log to the file. Log of each thread writes to a separate file.
#define WRITE_LOG_FILE(fileName) WriteLog( fileName );

#else
inline void CALL_DECLARATION SetLogging( bool ){}
inline void CALL_DECLARATION WriteLog( const TCHAR * ){}
inline void CALL_DECLARATION LogMessage( const c3d::string_t & ){}

#define START_LOGGING
#define END_LOGGING
#define LOG_MSG(msg)
#define WRITE_LOG_FILE(fileName)

#endif


namespace c3d //namespace c3d
{

//------------------------------------------------------------------------------
/** \brief \ru Включить контроль утечек памяти.
           \en Enable memory leakage control. \~ 
  \details \ru Включить контроль утечек памяти.
           \en Enable memory leakage control. \~
  \ingroup Base_Tools
*/
// ---
MATH_FUNC(void) EnableMemoryLeakDump();

} //namespace c3d


#endif // __TOOL_LOG_H
