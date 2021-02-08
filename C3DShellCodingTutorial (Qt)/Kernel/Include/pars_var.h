////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Переменная.
         \en Variable. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VAR_H
#define __VAR_H

#include <math_define.h>
//#include <string>
#include <tool_cstring.h>
#include <reference_item.h>


//------------------------------------------------------------------------------
/** \brief \ru Переменная.
           \en Variable. \~
  \details \ru Переменная. \n
           \en Variable. \n \~
  \ingroup Parser
*/
// ---
class MATH_CLASS MbVar : public MbRefItem {
private:
  const c3d::string_t _name;  ///< \ru Имя переменной. \en A name of variable. 
  double              _value; ///< \ru Значение переменной. \en A value of variable. 

public:
  /// \ru Конструктор. \en Constructor. 
  MbVar( const c3d::string_t & name ); 
  /// \ru Деструктор. \en Destructor. 
  virtual ~MbVar();             

public:   
          /// \ru Получить имя переменной. \en Get variable name. 
    const c3d::string_t & Name () const;              
          /// \ru Значение переменной. \en A value of variable. 
          double          Value() const;              
          /// \ru Присвоить значение переменной. \en Assign a value to a variable. 
          void            Assignment( double value ); 

OBVIOUS_PRIVATE_COPY( MbVar )
};


#endif  // __VAR_H