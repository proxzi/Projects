////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кубическая функция Эрмита.
         \en Cubic Hermite function. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNC_CUBIC_FUNCTION_H
#define __FUNC_CUBIC_FUNCTION_H


#include <function.h>
#include <templ_s_array.h>


#define FUNC_NUMB   4 ///< \ru Количество элементов расчетного массива кубической функции Эрмита. \en The number of elements of calculation array of a cubic Hermite function. 


//------------------------------------------------------------------------------
/** \brief \ru Кубическая функция Эрмита.
           \en Cubic Hermite function. \~
  \details \ru Кубическая функция Эрмита. \n
           \en Cubic Hermite function. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MbCubicFunction : public MbFunction {
protected:
  SArray<double> valueList;  ///< \ru Характерные точки. \en The control points. 
  SArray<double> firstList;  ///< \ru Производные в контрольных точках. \en The derivatives in control points. 
  SArray<double> tList;      ///< \ru Значения параметров на кривой, которую моделирует кубический сплайн. \en The values of parameters on a curve which is modeled by a cubic spline. 
  bool           closed;     ///< \ru Признак замкнутости кривой. \en An attribute of curve closedness. 
  ptrdiff_t      uppIndex;   ///< \ru Количество интервалов (число точек - 1). \en The number of intervals (a number of points - 1). 

public :
  /// \ru Конструктор по точкам и признаку замкнутости. \en Constructor by points and an attribute of closedness. 
  MbCubicFunction( const SArray<double> & values, bool cls );
  /// \ru Конструктор по точкам, параметрам и признаку замкнутости. \en Constructor by points, parameters and an attribute of closedness. 
  MbCubicFunction( const SArray<double> & values, const SArray<double> & params, bool cls );
  /// \ru Конструктор по точкам, производным, параметрам и признаку замкнутости. \en Constructor by points, derivatives, parameters and an attribute of closedness. 
  MbCubicFunction( const SArray<double> & values, const SArray<double> & firsts, const SArray<double> & params, bool cls );
  /// \ru Конструктор по двум точкам. \en Constructor by two points. 
  MbCubicFunction( double value1, double value2 );
  /// \ru Конструктор по двум точкам. \en Constructor by two points. 
  MbCubicFunction( double value1, double derive1, double t1, double value2, double derive2, double t2 );
private:
  MbCubicFunction( const MbCubicFunction & );
public :
  virtual ~MbCubicFunction();

public:
  /// \ru Инициализация по точкам, параметрам и признаку замкнутости. \en Initialization by points, parameters and an attribute of closedness. 
          void    Init( const SArray<double> & values,   
                        const SArray<double> & params, bool cls );
public:
  // \ru Общие функции математического объекта \en Common functions of mathematical object 
  virtual MbeFunctionType  IsA  () const;               // \ru Тип элемента \en A type of element 
  virtual MbFunction & Duplicate() const;               // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool   IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными \en Determine whether objects are equal 
  virtual bool   SetEqual ( const MbFunction & );       // \ru Сделать равным \en Make equal 
  virtual void   GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void   SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 

  virtual double  GetTMax  () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double  GetTMin  () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool    IsClosed () const; // \ru Замкнутость кривой \en A curve closedness 
  virtual void    SetClosed( bool cl ); // \ru Замкнутость функции \en A function closedness 

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
  virtual void    SetLimitDerive( size_t n, double newValue, double dt ); // \ru Установить значение на конце ( 1 - в начале, 2 - в конце) \en Set the value at the end (1 - at start point, 2 - at end point) 
  virtual double  GetLimitDerive( size_t n ) const; // \ru Дать значение на конце ( 1 - в начале, 2 - в конце) \en Get the value at the end (1 - at start point, 2 - at end point) 
  virtual bool    InsertValue( double t, double newValue ); // \ru Установить значение для параметра t. \en Set the value for the pdrdmeter t. 

  // \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const; 
  // \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть. \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg );
          MbFunction * Break( double t1, double t2 ) const; ///< \ru Выделить часть функции. \en Select a part of a function. 
          // \ru В указанной точке t установить заданное поведение, изменив функцию на интервале, не превышающем tDelta. \en Set a given behavior at point t by modifying the function of an interval not exceeding tDelta.
          void    SetFunctionValue( double t, const double & val, double tDelta, const double & der, double eps );

          size_t  GetValuesCount() const; // \ru Выдать количество опорных точек \en Get the number of control points 
          double  GetParam( size_t index ) const; // \ru Дать значение параметра точки по номеру \en Get the value of point parameter by its number  
          double  GetValue( size_t index ) const; // \ru Дать значение точки по номеру \en Get the value of point by its number  

private:
          bool    CalculateDerivatives(); // \ru Расчет производных. \en Calculation of derivatives 
  inline  bool    LocalCoordinate( double & t, ptrdiff_t & j1, ptrdiff_t & j2,
                                   double & y1, double & y2, double & t1, double & t2 ) const; 
          ptrdiff_t GetIndex ( double t ) const; 
          void    ParamPoint ( double y1, double y2, double t1, double t2, double * tLoft ) const; 
          void    ParamFirst ( double y1, double y2, double t1, double t2, double * tLoft ) const; 
          void    ParamSecond( double y1, double y2, double t1, double t2, double * tLoft ) const; 
          void    ParamThird ( double t1, double t2, double * tLoft ) const; 
          bool    SetCorrection( size_t ind, double tDelta ); // \ru Скорректировать функцию по индексу. \en Function correction by index.
          void    CalculateValues( size_t i1, size_t i2 ); // \ru Скорректировать функцию на интервале i1-i2. \en Function correction on the interval i1-i2.


private:
          void    operator = ( const MbCubicFunction & );   // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCubicFunction )
};

IMPL_PERSISTENT_OPS( MbCubicFunction )

//------------------------------------------------------------------------------
// \ru Определение местных координат области поверхности \en Definition of local coordinates in a surface region 
// ---
inline bool MbCubicFunction::LocalCoordinate( double & t, ptrdiff_t & j1, ptrdiff_t & j2,
                                              double & y1, double & y2, 
                                              double & t1, double & t2 ) const
{
  bool result = true;
  ptrdiff_t listInd = tList.MaxIndex();
  double tmin = tList[0];
  double tmax = tList[listInd];
  if ( t < tmin ) {
    if ( closed ) {
      double tmp = tmax - tmin;
      t -= ::floor((t - tmin) / tmp) * tmp; 
    }
    else {
      t = tmin;
      result = false;
    }
  }
  else
  if ( t > tmax ) {
    if ( closed ) {
      double tmp = tmax - tmin;
      t -= ::floor((t - tmin) / tmp) * tmp; 
    }
    else {
      t = tmax;
      result = false;
    }
  }

  j1 = 0;
  j2 = listInd;

  ptrdiff_t ind, delta = j2; // \ru Диапазон \en A range 

  // \ru Поиск половинным делением \en Search by bisection 
  while ( delta > 1 ) {
    ind = j1 + ( delta / (ptrdiff_t)2 ); // \ru Индекс в середине \en The index in the middle 
    if ( t < tList[ind] )  // \ru Если v меньше серединного параметра \en If v is less than the middle parameter 
      j2 = ind; // \ru Изменить правую границу \en Change the right bound 
    else 
      j1 = ind; // \ru Изменить левую границу \en Change the left bound 
    delta = j2 - j1; // \ru Диапазон \en A range 
  }
  
  t1 = tList[j1];
  t2 = tList[j2];
  y1 = (t-t2) / (t1-t2);
  y2 = (t-t1) / (t2-t1);

  return result;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa точки \en Definition of array of degrees of point parameter 
// ---
inline void MbCubicFunction::ParamPoint( double y1, double y2, double t1, double t2, double * tLoft ) const {
  tLoft[0] = 3*y1*y1 - 2*y1*y1*y1;
  tLoft[1] = 3*y2*y2 - 2*y2*y2*y2;
  tLoft[2] = (y1*y1*y1 - y1*y1) * (t1-t2);
  tLoft[3] = (y2*y2*y2 - y2*y2) * (t2-t1);
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa производной \en Definition of array of degrees of derivative parameter 
// ---
inline void MbCubicFunction::ParamFirst( double y1, double y2, double t1, double t2, double * tLoft ) const {
  tLoft[0] = (6*y1 - 6*y1*y1) / (t1-t2);
  tLoft[1] = (6*y2 - 6*y2*y2) / (t2-t1);
  tLoft[2] = (3*y1*y1 - 2*y1);
  tLoft[3] = (3*y2*y2 - 2*y2);
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa второй производной \en Definition of array of degrees of second derivative parameter 
// ---
inline void MbCubicFunction::ParamSecond( double y1, double y2, double t1, double t2, double * tLoft ) const {
  double d1 = 1 / (t1-t2);
  double d2 = -d1;
  tLoft[0] = (6 - 12*y1) * d1*d1;
  tLoft[1] = (6 - 12*y2) * d2*d2;
  tLoft[2] = (6*y1 - 2) * d1;
  tLoft[3] = (6*y2 - 2) * d2;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa третьей производной \en Definition of array of degrees of third derivative parameter 
// ---
inline void MbCubicFunction::ParamThird( double t1, double t2, double * tLoft ) const {
  double d1 = 1 / (t1-t2);
  double d2 = -d1;
  tLoft[0] = -12*d1*d1*d1;
  tLoft[1] = -12*d2*d2*d2;
  tLoft[2] =   6*d1*d1;
  tLoft[3] =   6*d2*d2;
}


#endif // __FUNC_CUBIC_FUNCTION_H
