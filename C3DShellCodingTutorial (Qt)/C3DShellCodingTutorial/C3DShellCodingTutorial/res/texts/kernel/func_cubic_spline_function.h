////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кубический сплайн функция.
         \en Cubic spline function. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNC_CUBIC_SPLINE_FUNCTION_H
#define __FUNC_CUBIC_SPLINE_FUNCTION_H


#include <function.h>
#include <templ_s_array.h>


//------------------------------------------------------------------------------
/** \brief \ru Кубический сплайн функция.
           \en Cubic spline function. \~
  \details \ru Кубический сплайн функция. \n
           \en Cubic spline function. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MbCubicSplineFunction : public MbFunction {
protected:
  SArray<double> valueList;  ///< \ru Характерные точки. \en The control points. 
  SArray<double> secondList; ///< \ru Вторые производные в контрольных точках. \en Second derivatives in control points. 
  SArray<double> tList;      ///< \ru Значение параметров на кривой, которую моделирует кубический сплайн. \en The values of parameters on a curve which is modeled by a cubic spline. 
  bool           closed;     ///< \ru Признак замкнутости кривой. \en An attribute of curve closeness. 
  ptrdiff_t      uppIndex;   ///< \ru Количество интервалов (число точек - 1). \en The number of intervals (a number of points - 1). 

public :
  /// \ru Конструктор по точкам и признаку замкнутости. \en Constructor by points and an attribute of closeness. 
  MbCubicSplineFunction( const SArray<double> & values, bool cls );
  /// \ru Конструктор по точкам, параметрам и признаку замкнутости. \en Constructor by points, parameters and an attribute of closeness. 
  MbCubicSplineFunction( const SArray<double> & values, const SArray<double> & params, bool cls );
private:
  MbCubicSplineFunction( const MbCubicSplineFunction & );
public :
  virtual ~MbCubicSplineFunction();

public:
  /// \ru Инициализация по точкам, параметрам и признаку замкнутости. \en Initialization by points, parameters and an attribute of closeness. 
          void    Init( const SArray<double> & values,   // \ru Инициализация переменных \en Initialization of variables 
                        const SArray<double> & params, bool cls );
public:
  // \ru Общие функции математического объекта \en Common functions of mathematical object 
  virtual MbeFunctionType  IsA      () const;                // \ru Тип элемента \en A type of element 
  virtual MbFunction & Duplicate() const;                // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными \en Determine whether objects are equal 
  virtual bool    SetEqual ( const MbFunction & );       // \ru Сделать равным \en Make equal 
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of object 

  virtual double  GetTMax  () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double  GetTMin  () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool    IsClosed () const; // \ru Замкнутость кривой \en A curve closeness 
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

  virtual void    SetOffsetFunc( double distOld, double distNew ); // \ru Сместить функцию \en Shift a function 
  virtual bool    SetLimitParam( double newTMin, double newTMax ); // \ru Установить область изменения параметра \en Set range of parameter 
  virtual void    SetLimitValue( size_t n, double newValue ); // \ru Установить значение на конце ( 1 - в начале, 2 - в конце) \en Set the value at the end (1 - at start point, 2 - at end point) 
  virtual double  GetLimitValue( size_t n ) const; // \ru Дать значение на конце ( 1 - в начале, 2 - в конце) \en Get the value at the end (1 - at start point, 2 - at end point) 
  virtual bool    InsertValue( double t, double newValue ); // \ru Установить значение для параметра t. \en Set the value for the pdrdmeter t. 

  // \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const; 
  // \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть. \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg );
          MbFunction * Break( double t1, double t2 ) const; ///< \ru Выделить часть функции. \en Select a part of a function. 

private:
          double    Value   ( double t, size_t num ) const;  // \ru Точка на кривой \en The point on the curve 
          double    FirstDer( double t, size_t num ) const;  // \ru Первая производная \en First derivative 
          ptrdiff_t GetIndex( double t ) const; 
          bool      CalcSecondDerives (); // \ru Расчет вторых производных \en Calculation of second derivatives 
          bool      CalcClosedSpline  (); // \ru Расчет вторых производных в узлах для замкнутой кривой \en Calculation of second derivatives in nodes of closed curve 
          bool      CalcUnClosedSpline(); // \ru Расчет вторых производных в узлах для разомкнутой кривой \en Calculation of second derivatives in nodes of unclosed curve 
          bool      DefineIntervalPar( double & t, size_t & num ) const; // \ru Определение принадлежности интервалу параметров \en Check belonging to interval of parameters 
private:
          void    operator = ( const MbCubicSplineFunction & );   // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCubicSplineFunction )
};

IMPL_PERSISTENT_OPS( MbCubicSplineFunction )

#endif // __FUNC_CUBIC_SPLINE_FUNCTION_H
