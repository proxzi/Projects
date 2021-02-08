////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Скалярная функция параметра.
         \en Scalar function of parameter. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNCTION_H
#define __FUNCTION_H


#include <io_tape.h>
#include <mb_variables.h>
#include <reference_item.h>
#include <vector>


class  MATH_CLASS MbProperties;
class  MATH_CLASS MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Типы скалярных функций.
           \en Types of scalar functions. \~
   \details \ru Скалярные функции можно рассматривать как кривые в одномерном пространстве. \n
            \en Scalar functions may be considered as curves in one-dimensional space. \n \~
   \ingroup Functions
 */
// ---
enum MbeFunctionType {

  ft_Undefined           =   0,  ///< \ru Неизвестный объект. \en Unknown object.

  ft_Function            =   1,  ///< \ru Функция. \en A function. 
  ft_ConstFunction       =   2,  ///< \ru Постоянная функция. \en A constant function. 
  ft_LineFunction        =   3,  ///< \ru Линейная функция. \en A linear function. 
  ft_CubicFunction       =   4,  ///< \ru Кубическая функция Эрмита. \en A cubic Hermite function. 
  ft_CubicSplineFunction =   5,  ///< \ru Кубическая сплайновая функция. \en A cubic spline function. 
  ft_PowerFunction       =   6,  ///< \ru Степенная функция. \en Power function.
  ft_SinusFunction       =   7,  ///< \ru Синусоидальная функция. \en Sinusoidal function.

  ft_CharacterFunction   = 101,  ///< \ru Символьная функция. \en A symbolic function. 
  ft_AnalyticalFunction  = 102,  ///< \ru Символьная функция на модельном выражении. \en A symbolic function in model expression. 

  ft_FreeItem            = 600,  ///< \ru Тип для объектов, созданных пользователем. \en Type for the user-defined objects.

};


//------------------------------------------------------------------------------
/** \brief \ru Скалярная функция параметра.
           \en Scalar function of parameter. \~
  \details \ru Скалярная функция параметра. \n
           \en Scalar function of parameter. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MbFunction : public MbRefItem, public TapeBase {

protected :
  MbFunction();
private:
  MbFunction( const MbFunction & );
public :
  virtual ~MbFunction();
public:
  /** \ru \name Общие функции математического объекта
      \en \name Common functions of mathematical object
      \{ */
  /// \ru Тип элемента. \en A type of element. 
  virtual MbeFunctionType  IsA() const = 0;
  /// \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual MbFunction & Duplicate() const = 0;
  /// \ru Являются ли объекты равными. \en Determine whether objects are equal. 
  virtual bool    IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const = 0;
  /// \ru Являются ли объекты подобными. \en Determine whether objects are similar. 
  virtual bool    IsSimilar( const MbFunction & ) const;
  /// \ru Сделать равным. \en Make equal. 
  virtual bool    SetEqual ( const MbFunction & ) = 0;
  /// \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    GetProperties( MbProperties & ) = 0;
  /// \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    SetProperties( const MbProperties & ) = 0;
  /** \} */
  /** \ru \name Общие функции
      \en \name Common functions
      \{ */
  /// \ru Вернуть максимальное значение параметра. \en Get the maximum value of parameter. 
  virtual double  GetTMax() const = 0;
  /// \ru Вернуть минимальное значение параметра. \en Get the minimum value of parameter. 
  virtual double  GetTMin() const = 0;
  /// \ru Получить замкнутость функции. \en Get the closeness of a function. 
  virtual bool    IsClosed() const = 0;
  /// \ru Установить замкнутость функции. \en Set the closeness of a function. 
  virtual void    SetClosed( bool cl ) = 0;
  /// \ru Периодичность замкнутой кривой. \en Periodicity of a closed curve. 
  virtual bool    IsPeriodic() const;

  /// \ru Значение функции для t. \en The value of function for a given t. 
  virtual double  Value    ( double & t ) const = 0; 
  /// \ru Первая производная по t. \en The first derivative with respect to t. 
  virtual double  FirstDer ( double & t ) const = 0; 
  /// \ru Вторая производная по t. \en The second derivative with respect to t. 
  virtual double  SecondDer( double & t ) const = 0; 
  /// \ru Третья производная по t. \en The third derivative with respect to t. 
  virtual double  ThirdDer ( double & t ) const = 0; 

  /// \ru Значение расширенной функции для t. \en The value of extended function for a given t. 
  virtual double _Value    ( double t ) const; 
  /// \ru Первая производная расширенной функции по t. \en The first derivative of extended function with respect to t. 
  virtual double _FirstDer ( double t ) const; 
  /// \ru Вторая производная расширенной функции по t. \en The second derivative of extended function with respect to t. 
  virtual double _SecondDer( double t ) const; 
  /// \ru Третья производная расширенной функции по t. \en The third derivative of extended function with respect to t. 
  virtual double _ThirdDer ( double t ) const; 

  /** \brief \ru Вычислить значение и производные для заданного параметра.
             \en Calculate value and derivatives of object for given parameter. \~
    \details \ru Значение и производных вычисляются в пределах области определения и на расширенной оси.
             \en Values of point and derivatives are calculated on parameter area and on extended axis. \~
    \param[in]  t   - \ru Параметр.
                      \en Parameter. \~
    \param[in]  ext - \ru В пределах области определения (false), на расширенной оси (true).
                      \en On parameters area (false), on extended axis (true). \~
    \param[out] val - \ru Значение.
                      \en Value. \~
    \param[out] fir - \ru Производная.
                      \en Derivative with respect to t. \~
    \param[out] sec - \ru Вторая производная по t, если не ноль.
                      \en Second derivative with respect to t, if not NULL. \~
    \param[out] thr - \ru Третья производная по t, если не ноль.
                      \en Third derivative with respect to t, if not NULL. \~
    \ingroup Curves_3D
  */
  virtual void    Explore( double & t, bool ext,
                           double & val, double & fir, double * sec, double * thr ) const;

  /// \ru Изменить направление. \en Change direction. 
  virtual void    Inverse( MbRegTransform * iReg = NULL ) = 0; 
  /// \ru Вычислить шаг по прогибу для заданного параметра t. \en Calculate a step by the sag for a given parameter t. 
  virtual double  Step( double t, double sag ) const = 0;
  /// \ru Вычислить шаг по угловому отклонению для заданного параметра t. \en Calculate a step by the angular deviation for a given parameter t. 
  virtual double  DeviationStep( double t, double angle ) const = 0;

  /// \ru Минимальное  значение функции. \en The minimum value of function. 
  virtual double  MinValue( double & t ) const = 0; 
  /// \ru Максимальное значение функции. \en The maximum value of function. 
  virtual double  MaxValue( double & t ) const = 0; 
  /// \ru Среднее значение функции. \en The middle value of function. 
  virtual double  MidValue() const = 0; 
  /// \ru Корректность функции. \en Correctness of function. 
  virtual bool    IsGood  () const = 0; 

  virtual bool    IsConst() const = 0; ///< \ru Является ли функция константной. \en Whether the function is constant. 
  virtual bool    IsLine () const = 0; ///< \ru Является ли функция линейной. \en Whether the function is linear. 

  /// \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const = 0;
  /// \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть: beg == true - соранить начальную половину, beg == false - соранить конечную половину.
  /// \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg ) = 0;
  /// \ru Разбить функцию параметрами: beg == true - соранить начальную половину, beg == false - соранить конечную половину.
  /// \en Function break by the parameters: begs == true - save the initial half, beg == false - save the final half.
  bool            CuttingFunction( SArray<double> & params, bool beginSafe, double eps, RPArray<MbFunction> & cutted );

  /// \ru Наличие полюса функции. \en Existence of a function pole. 
  virtual bool    IsPole( double t ) const; 
  /// \ru Сместить функцию. \en Shift a function. 
  virtual void    SetOffsetFunc( double distOld, double distNew ) = 0; 
  /// \ru Установить область изменения параметра. \en Set the range of parameter. 
  virtual bool    SetLimitParam( double newTMin, double newTMax ); 
  /// \ru Установить значение на конце ( 1 - в начале, 2 - в конце). \en Set the value at the end (1 - at start point, 2 - at end point). 
  virtual void    SetLimitValue( size_t n, double newValue ) = 0; 
  /// \ru Дать значение на конце ( 1 - в начале, 2 - в конце). \en Get the value at the end (1 - at start point, 2 - at end point). 
  virtual double  GetLimitValue( size_t n ) const = 0; 
  /// \ru Установить значение производной на конце ( 1 - в начале, 2 - в конце). \en Set the value of derivative at the end (1 - at start point, 2 - at end point). 
  virtual void    SetLimitDerive( size_t n, double newValue, double dt ); 
  /// \ru Дать значение производной на конце ( 1 - в начале, 2 - в конце). \en Get the value of derivative at the end (1 - at start point, 2 - at end point). 
  virtual double  GetLimitDerive( size_t n ) const; 
  /// \ru Установить значение для параметра t. \en Set the value for the parameter t. 
  virtual bool    InsertValue( double t, double newValue ); 
  /// \ru Получить параметры особого поведения в интервале от t1 до t2 (для cos это Pi*n). \en Get the parameters of special behaviour on the interval from t1 to t2 (for cos it is Pi*n). 
  virtual void    GetCharacteristicParams( std::vector<double> & tSpecific, double t1, double t2 );

  /** \} */
          /// \ru Параметрическая длина. \en The parametric length. 
          double  GetParamLength () const { return GetTMax()-GetTMin(); } 
          /// \ru Находится ли параметр в области определения функции. \en Whether the parameter belongs to the function domain. 
          bool    IsParamOn( double t, double eps ) const { return ( GetTMin()-eps <= t && t <= GetTMax()+eps ); } 
          /// \ru Подготовить к записи регистрируемый объект. \en Prepare for writing the registered object. 
          void    PrepareWrite() { SetRegistrable( (GetUseCount() > 1) ? registrable : noRegistrable ); } 

private:
          void    operator = ( const MbFunction & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS( MbFunction )
};

IMPL_PERSISTENT_OPS( MbFunction )

#endif // __FUNCTION_H
