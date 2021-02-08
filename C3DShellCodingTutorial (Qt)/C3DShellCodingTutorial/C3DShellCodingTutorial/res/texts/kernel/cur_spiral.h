////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Спираль.
         \en Spiral. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_SPIRAL_H
#define __CUR_SPIRAL_H


#include <mb_placement3d.h>
#include <mb_cube.h>
#include <curve3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Спираль.
           \en Spiral. \~
  \details \ru Родительский класс спиралей: MbConeSpiral, MbCrookedSpiral, MbCurveSpiral. \n
           \en Parent class for spirals: MbConeSpiral, MbCrookedSpiral, MbCurveSpiral. \n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbSpiral: public MbCurve3D {
protected:
  MbPlacement3D   position; ///< \ru Локальная система координат (положение центра). \en Local coordinate system (location of center). 
  double          step;     ///< \ru Шаг спирали. \en A pitch of spiral. 
  double          tmin;     ///< \ru Минимальное значение  параметра спирали. \en Minimal value of parameter of spiral. 
  double          tmax;     ///< \ru Максимальное значение параметра спирали. \en Maximal value of parameter of spiral. 

  /** \brief \ru Метрическая длина кривой. 
             \en Metric length of a curve. \~
      \details \ru Метрическая длина кривой расчитывается только при запросе длины объекта. Метрическая длина кривой в конструкторе кривой и после модификации кривой принимает отрицательное значение.
               \en Metric length of a curve is calculated only at the request. Metric length of a curve is undefined (negative) after object constructor and after object modifications. \n \~
  */
  mutable double  metricLength; 
  /** \brief \ru Габаритный куб кривой. 
             \en Bounding box of a curve. \~
      \details \ru Габаритный куб кривой расчитывается только при запросе габарита объекта. Габаритный куб в конструкторе кривой и после модификации кривой принимает неопределенное значение.
               \en Bounding box of a curve is calculated only at the request. Bounding box of a curve is undefined after object constructor and after object modifications. \n \~
  */
  mutable MbCube  cube;

protected:
  MbSpiral() : position(), step( 1.0 ), tmin( 0.0 ), tmax( M_PI2 ), metricLength( -1.0 ), cube() {}
  MbSpiral( const MbPlacement3D & pl ) : position( pl ), step( 0.0 ), tmin( 0.0 ), tmax( 0.0 ), metricLength( -1.0 ), cube() {}
  MbSpiral( const MbPlacement3D & pl, double height, double st );  // \ru По высоте и шагу \en By height and pitch 
  MbSpiral( const MbPlacement3D & pl, double s, double t1, double t2 );
  MbSpiral( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, double st, bool left = false );
  MbSpiral( const MbSpiral & init );
public :
  virtual ~MbSpiral();

public :
  VISITING_CLASS( MbSpiral );

          void    Init( const MbSpiral & init );
          void    Init( const MbPlacement3D & place );
          void    Init( double height, double st ); // \ru Установить высоту и шаг \en Set height and pitch 
          void    Init( const MbPlacement3D & place, double height, double st );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA()  const = 0; // \ru Тип элемента \en Type of element 
  virtual MbeSpaceType  Type() const;     // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const = 0;                   // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual( const MbSpaceItem & init );   // \ru Сделать равным \en Make equal 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL );     // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move( const MbVector3D & to, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual void    AddYourGabaritTo( MbCube & ) const; // \ru Добавь свой габарит в куб \en Add your own bounding box into the cube 
  virtual void    PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void    GetProperties( MbProperties & properties ) = 0;  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & properties ) = 0;  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual void    Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMin() const;  // \ru Вернуть минимальное значение параметра \en Get the minimum value of the parameter 
  virtual double  GetTMax() const;  // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const = 0; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double & t, MbVector3D & ) const = 0;    // \ru Первая производная \en The first derivative 
  virtual void    SecondDer( double & t, MbVector3D & ) const = 0;    // \ru Вторая производная \en The second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & ) const = 0;    // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const = 0;

  virtual void    Inverse( MbRegTransform * iReg = NULL ) = 0; // \ru Изменить направление \en Change direction 

  virtual double  GetMetricLength() const;      // \ru Выдать метрическую длину ограниченной кривой \en Get metric length of bounded curve 
  virtual double  GetLengthEvaluation() const;  // \ru Оценка метрической длины кривой \en Estimation of metric length of the curve 

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

  virtual double  Curvature( double t ) const;          // \ru Кривизна \en Curvature 
  virtual double  Step( double t, double sag ) const;   // \ru Вычисление шага аппроксимации \en Calculation of step of approximation 
  virtual double  DeviationStep( double t, double angle ) const;

  virtual size_t  GetCount() const;
          double  GetSpiralPeriod() const; // \ru Вернуть период \en Get period 

  // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if the curve is planar 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

  /// \ru Является ли объект смещением \en Whether the object is a shift 
  virtual bool    IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  virtual void    GetCentre( MbCartPoint3D & c ) const; // \ru Выдать центр \en Get center  

  // \ru Функции спирали \en Functions of spiral 

  virtual void    SetStep( double s ) = 0;                // \ru Изменить шаг \en Change step 
  virtual double  GetSpiralRadius ( double t ) const = 0; // \ru Выдать физический радиус спирали \en Get physical radius of spiral 
  inline  void    CheckParam( double & t ) const;
          void    GetDirection ( MbVector3D & v ) const { v = position.GetAxisZ();  }
          bool    GetAxis( MbAxis3D & axis ) const; // \ru Дать ось спирали \en Get axis of spiral 
          double  GetStep() const { return step;  } // \ru Выдать шаг \en Get step 
          double  GetSpiralStep() const; // \ru Выдать физический шаг спирали \en Get physical pitch of spiral 
          double  GetAngle() const { return tmax-tmin; } // \ru Выдать полный угол спирали \en Get full angle of spiral 
          void    SetTMin( double t ) { tmin = t; Refresh(); } // \ru Изменить граничный угол \en Change boundary angle 
          void    SetTMax( double t ) { tmax = t; Refresh(); } // \ru Изменить граничный угол \en Change boundary angle 
          void    SetLimit( double t1, double t2 )  { tmin = std_min( t1, t2 ); tmax = std_max( t1, t2 ); Refresh(); }

  const   MbPlacement3D & GetPlacement() const { return position; }
          bool    IsPositionNormal() const { return ( !position.IsAffine() ); }

private:
          void    operator = ( const MbSpiral & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS( MbSpiral )
};

IMPL_PERSISTENT_OPS( MbSpiral )

//------------------------------------------------------------------------------
// \ru Проверка параметра кривой \en Check parameter of curve 
//---
inline void MbSpiral::CheckParam( double & t ) const
{
  if ( t < tmin )
    t = tmin;
  if ( t > tmax )
    t = tmax;
}


//------------------------------------------------------------------------------
// \ru Выдать физический шаг спирали \en Get physical pitch of spiral 
//---
inline double MbSpiral::GetSpiralStep() const
{
  if ( position.IsNormal() )
    return step;
  else if ( position.IsOrthogonal() ) {
    return (step * position.GetAxisZ().Length());
  }
  return 0.0;
}


#endif // __CUR_SPIRAL_H
