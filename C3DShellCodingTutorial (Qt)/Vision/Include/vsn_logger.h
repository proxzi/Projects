////////////////////////////////////////////////////////////////////////////////
/**
\file Внимание. Интерфейс не устоявшийся
  \brief \ru Инструмент логирования
           Использование:
           vsnDebug("Текст для отладки");
           vsnCritical("Еще один текст для отладки");

           Вывод в output:
           debug: D:\Development\VisionWork\Examples\Qt\01_Background\background.cpp(177) : Текст для отладки
           critical: D:\Development\VisionWork\Examples\Qt\01_Background\background.cpp(178) : Еще один текст для отладки
         \en Logging tools \~

*/
////////////////////////////////////////////////////////////////////////////////
#include <vsn_global.h>

#ifndef __MB_LOGGER_H
#define __MB_LOGGER_H

#include <tool_cstring.h>
#include <string>

VSN_BEGIN_NAMESPACE

enum ELevel
{
    el_notset = -1,
    el_trace,
    el_debug,
    el_info,
    el_warning,
    el_error,
    el_critical,
};

//------------------------------------------------------------------------------
/** \brief \ru Расширенный инструмент логирования.
           \en NO TRANSLATION. \~
    \ingroup Vision_Tools
*/
// ---
class VSN_CLASS ExLogger
{
public:
    ExLogger(const char* file, int line);
public:
    // трассировка
    void Trace(const std::string& msg);
    // отладка
    void Debug(const std::string& msg);
    // информация
    void Info(const std::string& msg);
    // предупреждение
    void Warning(const std::string& msg);
    // ошибка
    void Error(const std::string& msg);
    // критическая ошибка
    void Critical(const std::string& msg);
public:
    // установка порога записи
    void SetLevel(ELevel level);
    // общая функция логирования
    void Log(ELevel level, const std::string& msg);
private:
    std::string m_file;
    int m_line;
};

#define vsnTrace      VSN::ExLogger(__FILE__, __LINE__).Trace
#define vsnDebug      VSN::ExLogger(__FILE__, __LINE__).Debug
#define vsnInfo       VSN::ExLogger(__FILE__, __LINE__).Info
#define vsnWarning    VSN::ExLogger(__FILE__, __LINE__).Warning
#define vsnError      VSN::ExLogger(__FILE__, __LINE__).Error
#define vsnCritical   VSN::ExLogger(__FILE__, __LINE__).Critical

VSN_END_NAMESPACE

#endif // __MB_LOGGER_H
