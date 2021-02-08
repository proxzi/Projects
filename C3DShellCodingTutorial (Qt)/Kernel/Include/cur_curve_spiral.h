////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Спираль переменного радиуса, именяющегося в соответствии с образующей кривой.
         \en Spiral with a variable radius which changes according to the generating curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUC_CURVE_SPIRAL_H
#define __CUC_CURVE_SPIRAL_H


#include <cur_spiral.h>


//------------------------------------------------------------------------------
/** \brief \ru Спираль переменного радиуса.
           \en Spiral with a variable radius. \~
  \details \ru Спираль переменного радиуса, именяющегося в соответствии с образующей кривой curve. \n
    Образующая кривая является двумерной и располагается в плоскости ZX локальной системы координат спирали.
    Радиус спирали равен второй координате точки образующей кривой.
    Ось спирали направлена вдоль оси Z локальной системы координат. \n
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией: \n
    r(t) = position.origin + (position.axisZ step t / 2pi) + (position.axisX radius cos(t)) + (position.axisY radius sin(t)),
    где radius = curve(w).y;
           \en Spiral with a variable radius which are changed according to the generating curve "curve". \n
    Generating curve is two-dimensional and located in the ZX plane of the local coordinate system.
    A spiral radius is equal to the second point coordinate of generating curve.
    A spiral axis is directed along the Z-axis of the local coordinate system. \n
    The radius-vector of curve in the method PointOn(double&t,MbCartPoint3D&r) is described by a vector function: \n
    r(t) = position.origin + (position.axisZ step t / 2pi) + (position.axisX radius cos(t)) + (position.axisY radius sin(t)),
    where radius = curve(w).y; \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbCurveSpiral : public MbSpiral {
protected:
  MbCurve * curve;      ///< \ru Кривая, задающая закон изменения радиуса. \en Curve which determines the rule of radius changing. 
  double    wMin;       ///< \ru Минимальное значение  параметра кривой curve. \en Minimal parameter value of curve "curve". 
  double    wMax;       ///< \ru Максимальное значение параметра кривой curve. \en Maximal parameter value of curve "curve". 
  bool      curveSense; ///< \ru Совпадение направления оси спирали с направлением кривой curve. \en The coincidence of the direction of the spiral axis with the direction of the curve "curve". 

public:
  MbCurveSpiral( const MbPlacement3D & pl, double rad, double s, double t1, double t2 ); // \ru Цилиндрическая спираль \en Cylindrical spiral 
  MbCurveSpiral( const MbPlacement3D & pos, MbCurve & lawCurve, double s, bool same );   // \ru Спираль с образующей кривой \en Spiral with a generating curve 

protected:
  MbCurveSpiral( const MbCurveSpiral & init );

public :
  virtual ~MbCurveSpiral();

public:
  VISITING_CLASS( MbCurveSpiral );

          void    Init( const MbCurveSpiral & init );
          void    Init( const MbPlacement3D & place );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual( const MbSpaceItem & init );   // \ru Сделать равным \en Make equal 

  virtual void    GetProperties( MbProperties & );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems( RPArray<MbSpaceItem> & );

  // \ru Общие функции кривой \en Common functions of curve 

  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn  ( double & t, MbCartPoint3D & pnt ) const ; // \ru Точка на кривой \en Point on curve 
  virtual void    FirstDer ( double & t, MbVector3D & fd ) const; // \ru Первая производная \en First derivative 
  virtual void    SecondDer( double & t, MbVector3D & sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & td ) const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Функции для работы внутри и вне области определения кривой. \en Functions for working inside and outside of the curve domain. \~
  virtual void   _PointOn  ( double t,  MbCartPoint3D & pnt ) const ; // \ru Точка на кривой \en Point on curve 
  virtual void   _FirstDer ( double t,  MbVector3D & fd ) const; // \ru Первая производная \en First derivative 
  virtual void   _SecondDer( double t,  MbVector3D & sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void   _ThirdDer ( double t,  MbVector3D & td ) const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 

  // \ru Функции спирали \en Functions of spiral 

  virtual void    SetStep( double s );                // \ru Изменить шаг \en Change step 
  virtual double  GetSpiralRadius ( double t ) const; // \ru Выдать физический радиус спирали \en Get physical radius of spiral 

protected:
          void    Init( bool setLimits );
          double  GetRadiusValue( double t, double & r0, MbVector & derive ) const; // \ru Выдать радиус спирали \en Get the spiral radius 
          void    GetRadiusDerivative( MbVector & derive, double & r1 ) const;  // \ru Выдать первую производную радиуса \en Get the first derivative of the radius 
          void    GetRadiusDerivatives( double wPar, MbVector & derive, double & r1, double & r2, double & r3 ) const; // \ru Выдать первую, вторую и третью производные радиуса \en Get the first, second and third derivatives of the radius 

private:
          void    operator = ( const MbCurveSpiral & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCurveSpiral )
}; // MbCurveSpiral

IMPL_PERSISTENT_OPS( MbCurveSpiral )

#endif // __CUC_CURVE_SPIRAL_H
