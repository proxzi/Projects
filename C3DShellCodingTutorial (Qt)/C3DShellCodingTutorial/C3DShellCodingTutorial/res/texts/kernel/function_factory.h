////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Создание скалярных функций.
         \en Creation of scalar functions. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNCTION_FACTORY_H
#define __FUNCTION_FACTORY_H


#include <tool_cstring.h>
#include <templ_s_array.h>
#include <math_define.h>
#include <mb_operation_result.h>


class  MATH_CLASS MbFunction;
class  MATH_CLASS MbListVars;
class  MATH_CLASS MbMathematicalNode;


//------------------------------------------------------------------------------
/** \brief \ru Фабрика функций.
           \en Factory of functions. \~
  \details \ru Фабрика функций. \n
           \en Factory of functions. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MbFunctionFactory {
private:
  mutable MbResultType status; ///< \ru Результат создания. \en The result of creation. 

public :
  /// \ru Конструктор. \en Constructor. 
  MbFunctionFactory(); 
  virtual ~MbFunctionFactory();

public:
  MbResultType Status() const; ///< \ru Получить статус создания. \en Get the state of creation. 

public:
  /// \ru Создать символьную функцию. \en Create a symbolic function. 
  MbFunction * CreateAnalyticalFunction ( const c3d::string_t & data,  MbListVars & vars, 
                                          const MbMathematicalNode & root, 
                                          const c3d::string_t & argument,
                                          double tmin, double tmax )  const;
  /// \ru Создать символьную функцию. \en Create a symbolic function. 
  MbFunction * CreateAnalyticalFunction ( const c3d::string_t & data,
                                          const c3d::string_t & argument,
                                          double tmin, double tmax )  const;
  /// \ru Создать постоянную функцию. \en Create a constant function. 
  MbFunction * CreateConstFunction      ( double value )                                        const;
  /// \ru Создать линейную функцию. \en Create a linear function. 
  MbFunction * CreateLineFunction       ( double v1, double v2, double t1, double t2 )          const;
  /// \ru Создать кубическую функцию. \en Create a cubic function. 
  MbFunction * CreateCubicFunction      ( const SArray<double> & values, bool closed )          const;
  /// \ru Создать кубическую функцию. \en Create a cubic function. 
  MbFunction * CreateCubicFunction      ( const SArray<double> & values, 
                                          const SArray<double> & params, bool closed )          const;
  /// \ru Создать кубическую функцию. \en Create a cubic function. 
  MbFunction * CreateCubicFunction      ( const SArray<double> & values,
                                          const SArray<double> & firsts,
                                          const SArray<double> & params, bool closed )          const;
  /*
  MbFunction * CreateCubicSplineFunction( const SArray<double> & values, bool closed )          const;
  MbFunction * CreateCubicSplineFunction( const SArray<double> & values, 
                                          const SArray<double> & params, bool closed )          const;
  */

OBVIOUS_PRIVATE_COPY( MbFunctionFactory )
};


//------------------------------------------------------------------------------
// \ru Найти в строке переменные \en Find variables in string 
// ---
const MbMathematicalNode * GetVarListForAnalyticalFunc( const c3d::string_t & data, MbListVars & vars );


#endif // __FUNCTION_FACTORY_H
