////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Синус функция.
         \en Sinus function. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNC_SINUS_FUNCTION_H
#define __FUNC_SINUS_FUNCTION_H


#include <function.h>


//------------------------------------------------------------------------------
/** \brief \ru Синус функция.
           \en Sinus function. \~
  \details \ru Синус функция  f(t) = origin + amplitude* sin((t - shift) / frequency). \n
           \en Sinus function f(t) = origin + amplitude* sin((t - shift) / frequency). \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MbSinusFunction : public MbFunction {
public :
  double origin;    ///< \ru Начальное значение. \en Start value.  
  double amplitude; ///< \ru Амплитуда. \en Amplitude. 
  double shift;     ///< \ru Сдвиг параметра. \en Parameter shift. 
  double frequency; ///< \ru Циклическая частота. \en Frequency. 
  double tmin;      ///< \ru Начало области определения. \en Beginning of domain. 
  double tmax;      ///< \ru Конец области определения. \en Ending of domain. 

public :
  ///< \ru Конструктор по значениям и параметрам. \en Constructor by values and parameters. 
  MbSinusFunction( double orig, double ampl, double shif, double freq, double t1, double t2 );
private:
  MbSinusFunction( const MbSinusFunction & );
public :
  virtual ~MbSinusFunction();
public:
          void    Init( double orig, double ampl, double shif, double freq, double t1, double t2 ); ///< \ru Инициализация по значениям и параметрам. \en Initialization by values and parameters. 
public:
  // \ru Общие функции математического объекта \en Common functions of mathematical object 
  virtual MbeFunctionType  IsA() const;                  // \ru Тип элемента \en A type of element 
  virtual MbFunction & Duplicate() const;                // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными \en Determine whether objects are equal 
  virtual bool    SetEqual ( const MbFunction & );       // \ru Сделать равным \en Make equal 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 

  virtual double  GetTMax()    const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double  GetTMin()    const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool    IsClosed()   const; // \ru Замкнутость кривой \en A curve closeness 
  virtual void    SetClosed( bool cl ); // \ru Замкнутость функции \en A function closeness 

  virtual double  Value     ( double & t ) const; // \ru Значение функции для t \en The value of function for a given t 
  virtual double  FirstDer  ( double & t ) const; // \ru Первая производная по t \en The first derivative with respect to t 
  virtual double  SecondDer ( double & t ) const; // \ru Вторая производная по t \en The second derivative with respect to t 
  virtual double  ThirdDer  ( double & t ) const; // \ru Третья производная по t \en The third derivative with respect to t 

  virtual double _Value     ( double t ) const; // \ru Значение функции для t \en The value of function for a given t 
  virtual double _FirstDer  ( double t ) const; // \ru Первая производная по t \en The first derivative with respect to t 
  virtual double _SecondDer ( double t ) const; // \ru Вторая производная по t \en The second derivative with respect to t 
  virtual double _ThirdDer  ( double t ) const; // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значение и производные. \en Calculate value and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           double & val, double & fir, double * sec, double * thr ) const;

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Step( double t, double sag ) const;
  virtual double  DeviationStep( double t, double angle ) const;

  virtual double  MinValue  ( double & t ) const; // \ru Минимальное  значение функции \en The minimum value of function 
  virtual double  MaxValue  ( double & t ) const; // \ru Максимальное значение функции \en The maximum value of function 
  virtual double  MidValue  () const; // \ru Среднее значение функции \en The middle value of function 
  virtual bool    IsGood    () const; // \ru Корректность функции \en Correctness of function 

  virtual bool    IsConst() const;
  virtual bool    IsLine () const;

  // \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const; 
  // \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть. \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg );

  virtual void    SetOffsetFunc( double distOld, double distNew ); // \ru Сместить функцию \en Shift a function 
          bool    SetLimit( double newTMin, double newTMax ); // \ru Установить область изменения параметра \en Set range of parameter 
  virtual void    SetLimitValue( size_t n, double newValue ); // \ru Установить значение на конце ( 1 - в начале, 2 - в конце) \en Set the value at the end (1 - at beginning, 2 - at ending) 
  virtual double  GetLimitValue( size_t n ) const; // \ru Дать значение на конце ( 1 - в начале, 2 - в конце) \en Get the value at the end (1 - at beginning, 2 - at ending) 

private:
          void    operator = ( const MbSinusFunction & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSinusFunction )
};


IMPL_PERSISTENT_OPS( MbSinusFunction )


#endif // __FUNC_SINUS_FUNCTION_H
