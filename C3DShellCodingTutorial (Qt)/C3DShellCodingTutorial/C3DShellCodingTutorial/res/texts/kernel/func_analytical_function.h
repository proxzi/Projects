////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Символьные (пользовательские) функции.
         \en Symbolic (user) functions. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __FUNC_ANLYTICAL_FUNCTION_H
#define __FUNC_ANLYTICAL_FUNCTION_H


#include <templ_sptr.h>
#include <function.h>
#include <mb_enum.h>
#include <tool_cstring.h>
#include <tool_multithreading.h>


class MbMathematicalNode; // \ru Математический узел \en The mathematical node 
class MbListVars;         // \ru Список переменных \en The list of variables 
class MbUserFunc;         // \ru Пользовательская функция \en Th user function 


//------------------------------------------------------------------------------
/** \brief \ru Скалярная функция, заданная символьной строкой.
           \en The symbolic function. \~
  \details \ru Скалярная функция, заданная символьной строкой. \n
           \en The symbolic function. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MdCharacterFunction : public MbFunction, public MbSyncItem {
private :
  const MbMathematicalNode * expression; ///< \ru Выражение функции в виде дерева. \en An expression of a function as tree. 
  const MbListVars *         variables;  ///< \ru Аргументы функции в виде списка. \en Arguments of a function as list 
        c3d::string_t        data;       ///< \ru Выражение функции в виде строки. \en An expression of a function as string. 
        c3d::string_t        argument;   ///< \ru Аргументы функции в виде строки. \en Arguments of a function as string. 
        double               tmin;       ///< \ru Начальный параметр. \en Start parameter. 
        double               tmax;       ///< \ru Конечный параметр. \en End parameter. 
        bool                 sense;      ///< \ru Направление. \en Direction. 

public :
  /// \ru Конструктор. \en Constructor. 
  MdCharacterFunction( const MbMathematicalNode & expression_, const MbListVars & vars, 
                       const c3d::string_t & data_, const c3d::string_t & argument_,
                       double tmin_, double tmax_, bool sense_ );
  virtual ~MdCharacterFunction();

private:
  MdCharacterFunction( const MdCharacterFunction & ); 

public :
  // \ru Общие функции математического объекта \en Common functions of mathematical object 
  virtual MbeFunctionType IsA() const;                   // \ru Тип элемента \en A type of element 
  virtual MbFunction & Duplicate() const;                // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными \en Determine whether objects are equal 
  virtual bool    SetEqual ( const MbFunction & );       // \ru Сделать равным \en Make equal 
  virtual void    GetProperties( MbProperties & );      // \ru Выдать свойства объекта \en Get properties of object 
  virtual void    SetProperties( const MbProperties & );      // \ru Записать свойства объекта \en Set properties of object 

  virtual double  GetTMin      () const;    // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax      () const;    // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed     () const;    // \ru Замкнутость кривой \en A curve closeness 
  virtual void    SetClosed    ( bool cl ); // \ru Замкнутость функции \en A function closeness 

  virtual double  Value        ( double & t ) const; // \ru Значение функции для t \en The value of function for a given t 
  virtual double  FirstDer     ( double & t ) const; // \ru Первая производная по t \en The first derivative with respect to t 
  virtual double  SecondDer    ( double & t ) const; // \ru Вторая производная по t \en The second derivative with respect to t 
  virtual double  ThirdDer     ( double & t ) const; // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значение и производные. \en Calculate value and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           double & val, double & fir, double * sec, double * thr ) const;
                                
  virtual void    Inverse      ( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Step         ( double t, double sag )    const;
  virtual double  DeviationStep( double t, double angle )  const;

  virtual double  MinValue     ( double & t ) const; // \ru Минимальное  значение функции \en The minimum value of function 
  virtual double  MaxValue     ( double & t ) const; // \ru Максимальное значение функции \en The maximum value of function 
  virtual double  MidValue     () const; // \ru Среднее значение функции \en The middle value of function 
  virtual bool    IsGood       () const; // \ru Корректность функции \en Correctness of function 
  virtual bool    IsConst      () const;
  virtual bool    IsLine       () const;

  virtual void    SetOffsetFunc( double distOld, double distNew ); // \ru Сместить функцию \en Shift a function 
  virtual bool    SetLimitParam( double newTMin, double newTMax ); // \ru Установить область изменения параметра \en Set range of parameter 
  virtual void    SetLimitValue( size_t n, double newValue );      // \ru Установить значение на конце ( 1 - в начале, 2 - в конце) \en Set the value at the end (1 - at start point, 2 - at end point) 
  virtual double  GetLimitValue( size_t n ) const;                 // \ru Дать значение на конце ( 1 - в начале, 2 - в конце) \en Get the value at the end (1 - at start point, 2 - at end point) 

  // \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const; 
  // \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть. \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg );

private:  
          void    Translate  ();
          void    CheckParam ( double & t ) const;
private:
          void    operator = ( const MdCharacterFunction & ); // \ru Не реализовано \en Not implemented 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MdCharacterFunction )
};

IMPL_PERSISTENT_OPS( MdCharacterFunction )

//------------------------------------------------------------------------------
/** \brief \ru Скалярная функция, заданная аналитическим выражением.
           \en The analytical function. \~
  \details \ru Скалярная функция, заданная аналитическим выражением. \n
           \en The analytical function. \n \~
  \ingroup Functions
*/
// ---
class MATH_CLASS MdAnalyticalFunction : public MbFunction
{
private:
  MbUserFunc *   expression; // \ru Пользовательская функция. \en The user function. 
  double         tmin;       // \ru Начальный параметр. \en Start parameter. 
  double         tmax;       // \ru Конечный параметр. \en End parameter. 
  bool           sense;      // \ru Направление. \en Direction. 
private:
  struct DerivateData : public AuxiliaryData {
    double tCur;                      // \ru Параметр для которого рассчитаны производные \en. The parameter where the derivatives have been calculated. 
    double derivatives[cdt_CountDer]; // \ru Рассчитанные значения производных. \en The calculated values of derivatives. 

    DerivateData();
    DerivateData( const DerivateData & data );
  };
  mutable CacheManager<DerivateData> cache;

public :
  // \ru Конструктор. \en Constructor. 
  MdAnalyticalFunction( MbUserFunc & ufunc, double tmin_, double tmax_, bool sense_ = true );
public:
  virtual ~MdAnalyticalFunction();

private:
  MdAnalyticalFunction( const MdAnalyticalFunction & ); 

public :
  // \ru Общие функции математического объекта \en Common functions of mathematical object 
  virtual MbeFunctionType IsA() const;                   // \ru Тип элемента \en A type of element 
  virtual MbFunction & Duplicate() const;                // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbFunction & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными \en Determine whether objects are equal 
  virtual bool    SetEqual ( const MbFunction & );       // \ru Сделать равным \en Make equal 
  virtual void    GetProperties( MbProperties & );       // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 

  virtual double  GetTMin       () const;    // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax       () const;    // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed      () const;    // \ru Замкнутость кривой \en A curve closeness 
  virtual void    SetClosed     ( bool cl ); // \ru Замкнутость функции \en A function closeness 

  virtual double  Value         ( double & t ) const; // \ru Значение функции для t \en The value of function for a given t 
  virtual double  FirstDer      ( double & t ) const; // \ru Первая производная по t \en The first derivative with respect to t 
  virtual double  SecondDer     ( double & t ) const; // \ru Вторая производная по t \en The second derivative with respect to t 
  virtual double  ThirdDer      ( double & t ) const; // \ru Третья производная по t \en The third derivative with respect to t 

  virtual void    Inverse       ( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Step          ( double t, double sag )    const;
  virtual double  DeviationStep ( double t, double angle )  const;

  virtual double  MinValue      ( double & t ) const; // \ru Минимальное  значение функции \en The minimum value of function 
  virtual double  MaxValue      ( double & t ) const; // \ru Максимальное значение функции \en The maximum value of function 
  virtual double  MidValue      () const; // \ru Среднее значение функции \en The middle value of function 
  virtual bool    IsGood        () const; // \ru Корректность функции \en Correctness of function 
  virtual bool    IsConst       () const;
  virtual bool    IsLine        () const;

  virtual void    SetOffsetFunc ( double distOld, double distNew ); // \ru Сместить функцию \en Shift a function 
  virtual bool    SetLimitParam ( double newTMin, double newTMax ); // \ru Установить область изменения параметра \en Set range of parameter 
  virtual void    SetLimitValue ( size_t n, double newValue );      // \ru Установить значение на конце ( 1 - в начале, 2 - в конце) \en Set the value at the end (1 - at start point, 2 - at end point) 
  virtual double  GetLimitValue ( size_t n ) const;                 // \ru Дать значение на конце ( 1 - в начале, 2 - в конце) \en Get the value at the end (1 - at start point, 2 - at end point) 

  virtual void    GetCharacteristicParams( std::vector<double> & tVec, double t1, double t2 ) const; // \ru Дать параметры особого поведения(для cos это Pi*n) \en Get parameters of special behavior (for cos it is Pi*n)  

  // \ru Создать функцию из части функции между параметрами t1 и t2 c выбором направления sense. \en Create a function in part of the function between the parameters t1 and t2 choosing the direction. 
  virtual MbFunction * Trimmed( double t1, double t2, int sense ) const; 
  // \ru Разбить функцию точкой с параметром t и вернуть отрезанную часть. \en Function break by the parameter t, and cut off part of the function: begs == true - save the initial half, beg == false - save the final half.
  virtual MbFunction * BreakFunction( double t, bool beg );

  virtual bool IsCos ( double &a, double& b ) const;  ///< \ru Имеет ли функция вид a * cos() + b. \en Function looks like a * cos() + b.


private: 
  /// \ru Производные по параметру: параметр, значение, первая, вторая и третья производные \en Derivatives with respect to the parameter: parameter, value, first, second and third derivatives 
  void    Derivates ( double & t, DerivateData* data ) const;
  void    CheckParam( double & t ) const;
  void    ResetTCalc() const; // \ru Сбросить временные данные \en Reset temporary data 
  void    operator = ( const MdAnalyticalFunction & ); // \ru Не реализовано. \en NOT ALLOWED !!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MdAnalyticalFunction )
};

IMPL_PERSISTENT_OPS( MdAnalyticalFunction )

#endif // __FUNC_ANLYTICAL_FUNCTION_H
