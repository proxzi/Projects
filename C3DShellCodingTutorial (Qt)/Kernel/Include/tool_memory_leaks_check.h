////////////////////////////////////////////////////////////////////////////////
/// Слежение за утечками
/**
  \file
  \brief  Содержит класс MemoryLeaksVerifiable - базовый для контролируемых классов
*/
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math_define.h>

#if ( defined(STANDARD_C11) && (_MSC_VER > 1800) )
#define ENABLE_MEMORY_LEAKS_CHECK
#endif


namespace c3d // namespace C3D
{

#ifdef ENABLE_MEMORY_LEAKS_CHECK

//------------------------------------------------------------------------------
/** \brief \ru Базовый класс для контролируемых классов.
           \en . \~
  \details \ru На конструкторе объект регистрируется в менеджере утечек, в деструкторе удаляется из списка зарегистрированных.
               Информация о всех объектах, которые остались в регистраторе, будет выведена. \n
           \en . \n \~ 
  \ingroup Base_Tools
*/
// ---
class MATH_CLASS MemoryLeaksVerifiable
{
protected:
  MemoryLeaksVerifiable();
  virtual ~MemoryLeaksVerifiable();
};

#else

class MATH_CLASS MemoryLeaksVerifiable {};

#endif // ENABLE_MEMORY_LEAKS_CHECK

} // namespace C3D



