////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Включатель модулей ядра.
         \en Kernel modules enabler \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef _TOOL_ENABLER_H_
#define _TOOL_ENABLER_H_

#include <math_define.h>


//------------------------------------------------------------------------------
/** \brief \ru Включить модули ядра.
           \en Enable kernel modules. \~ 
  \details \ru Включить соответствующие модули ядра.
           \en Enable the corresponding kernel modules. \~
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (void) EnableMathModules( const char * name, int nameLength, const char * key, int keyLength );


//------------------------------------------------------------------------------
/** \brief \ru Проверить ключ активации на валидность.
           \en Verify key. \~ 
  \details \ru Проверить ключ активации на валидность.
           \en Verify key. \~
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) VerifyLicenseKey( const char * name, const char * key, const char * pub_key );


//------------------------------------------------------------------------------
/** \brief \ru Проверить контроллер защиты моделировщика.
           \en Check the controller of the Modeler. \~ 
  \details \ru Проверить контроллер защиты моделировщика.
           \en Check the controller of the Modeler. \~ 
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) IsMathModelerEnable();


//------------------------------------------------------------------------------
/** \brief \ru Проверить контроллер защиты конвертеров.
           \en Check the controller of the Converter. \~ 
  \details \ru Проверить контроллер защиты конвертеров.
           \en Check the controller of the Converter. \~ 
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) IsMathConverterEnable();


//------------------------------------------------------------------------------
/** \brief \ru Проверить контроллер защиты решателя.
           \en Check the controller of the Solver. \~ 
  \details \ru Проверить контроллер защиты решателя.
           \en Check the controller of the Solver. \~ 
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) IsMathSolverEnable();


//------------------------------------------------------------------------------
/** \brief \ru Проверить контроллер защиты визуализатора.
           \en Check the controller of the Vision. \~ 
  \details \ru Проверить контроллер защиты визуализатора.
           \en Check the controller of the Vision. \~ 
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) IsMathVisionEnable();


//------------------------------------------------------------------------------
/** \brief \ru Проверить контроллер защиты преобразователя сеток в BRep.
           \en Check the controller of the BShaper. \~ 
  \details \ru Проверить контроллер защиты преобразователя сеток в BRep.
           \en Check the controller of the BShaper. \~ 
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (bool) IsMathBShaperEnable();


//------------------------------------------------------------------------------
/** \brief \ru Отпустить контролера работы модулей ядра.
           \en Free the controller of the kernel modules work. \~ 
  \details \ru Отпустить контролера работы модулей ядра.
           \en Free the controller of the kernel modules work. \~
  \ingroup Base_Tools
*/
// ---
MATH_FUNC (void) FreeMathModulesChecker();


#endif // _TOOL_ENABLER_H_
