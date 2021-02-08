////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Контур на плоскости.
         \en Contour on plane. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CONTOUR_ON_PLANE_H
#define __CUR_CONTOUR_ON_PLANE_H


#include <cur_contour_on_surface.h>


class  MATH_CLASS MbPlane;
class  MATH_CLASS MbAxis3D;


//------------------------------------------------------------------------------
/** \brief \ru Контур на плоскости.
           \en Contour on plane. \~
  \details \ru Контур на плоскости представляет собой трёхмерную составную кривую,
    полученную движением вдоль двумерного контура MbContour,
    расположенного в пространстве параметров некоторой плоскости MbPlane. \n
    Контур на плоскости используется: 
    для описания области определения параметров поверхности,
    для описания плоского эскиза в операции.
           \en Contour on the plane a is three-dimensional composite curve,
    obtained by the motion along the two-dimensional contour MbContour,
    located in the parameters space of a plane MbPlane. \n
    Contour on the plane is used: 
    for description of surface domain,
    for description of planar sketch in the operation. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbContourOnPlane : public MbContourOnSurface {

public :
  /// \ru Конструктор по плоскости, контуру и флагу использования оригинала контура. \en Constructor by plane, contour and flag of using original contour. 
  MbContourOnPlane( const MbPlane &, const MbContour &, bool same );
  /// \ru Конструктор по плоскости и направлению обхода поверхности. \en Constructor by plane and traverse direction of surface. 
  MbContourOnPlane( const MbPlane &, int sense );
  /// \ru Конструктор по плоскости. \en Constructor by plane. 
  MbContourOnPlane( const MbPlane & );

protected:
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbContourOnPlane( const MbContourOnPlane &, MbRegDuplicate * );
  /// \ru Конструктор копирования контура с той же поверхностью для CurvesDuplicate(). \en Constructor to copy contour with the same surface for CurvesDuplicate(). 
  explicit MbContourOnPlane( const MbContourOnPlane * );
private:
  MbContourOnPlane( const MbContourOnPlane & ); // \ru Не реализовано !!! \en Not implemented !!! 

public :
  virtual ~MbContourOnPlane();

public :
  VISITING_CLASS( MbContourOnPlane );

  // \ru Общие функции математического объекта. \en The common functions of the mathematical object. 

  virtual MbeSpaceType  IsA() const; // \ru Дать тип элемента. \en Get a type of the element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual MbContourOnSurface & CurvesDuplicate() const; // \ru Сделать копию со старой подложкой. \en Make a copy with old substrate. 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Определить, является ли копией данного объекта? \en Determine whether the object is copy of a given object. 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 

  // \ru Общие функции кривой. \en Common functions of curve. 

  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Вычислить точку на кривой. \en Calculate point on the curve. 
  virtual void    FirstDer ( double & t, MbVector3D & )    const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void    SecondDer( double & t, MbVector3D & )    const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void    ThirdDer ( double & t, MbVector3D & )    const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Функции для работы внутри и вне области определения кривой. \en Functions for working inside and outside of the curve domain. \~
  virtual void   _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Вычислить точку на расширенной кривой. \en Calculate point on the extended curve. 
  virtual void   _FirstDer ( double t, MbVector3D & )     const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void   _SecondDer( double t, MbVector3D & )     const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void   _ThirdDer ( double t, MbVector3D & )     const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
    // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual double  Curvature    ( double t )             const; // \ru Вычислить кривизну кривой. \en Calculate the curve curvature. 
  virtual double  Step         ( double t, double sag ) const; // \ru Вычислить шаг аппроксимации. \en Calculate the approximation step. 
  virtual double  DeviationStep( double t, double sag ) const; // \ru Вычислить шаг аппроксимации. \en Calculate the approximation step. 

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создать усеченную кривую. \en Create the trimmed curve. 

  virtual double  GetMetricLength() const; // \ru Вычислить метрическую длину кривой. \en Calculate the metric length of curve. 
  virtual double  GetLengthEvaluation() const; // \ru Оценить метрическую длину кривой. \en Evaluate the metric length of curve. 
  virtual double  CalculateMetricLength() const; // \ru Вычислить метрическую длину кривой. \en Calculate the metric length of curve. 
  
  virtual bool    ChangeSurface( MbSurface & newsurf ); // \ru Заменить поверхность контура. \en Replace the surface of contour. 
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменить носителя. \en Change the carrier. 
  virtual bool    IsPlanar() const; // \ru Является ли кривая плоской? \en Whether the curve is planar? 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую). \en Get planar curve and placement if the space curve is planar (after the using call DeleteItem for two-dimensional curves) 
  virtual bool    GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place3d, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Заполнить плейсмент, если кривая плоская. \en Fill the placement if curve is planar. 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool    GetCircleAxis( MbAxis3D & ) const; // \ru Дать ось кривой. \en Get the curve axis. 
  virtual void    GetCentre( MbCartPoint3D & wc ) const; // \ru Дать центр тяжести. \en Get the center of gravity. 
  virtual void    GetWeightCentre( MbCartPoint3D & wc ) const; // \ru Дать центр тяжести. \en Get the center of gravity. 
  virtual void    CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой. \en Calculate the bounding box of curve. 

  virtual bool    IsStraight() const; // \ru Определить, является ли линия прямолинейной? \en Wetermine whether the line is straight. 

  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D *pRgn = NULL,
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of curve. 

  virtual void    GetPointsByEvenLengthDelta( size_t n, std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги. \en Get n points of curve with equal intervals along the length of the arc. 

          /// \ru Получить локальную систему координат плоскости. \en Get the local coordinate system of a plane. 
    const MbPlacement3D    & GetPlacement() const;
          /// \ru Получить плоскость. \en Get the plane. 
    const MbPlane &          GetPlane() const { return (const MbPlane &)GetSurface(); }

          /// \ru Сделать правой локальную систему координат плоскости. \en Make the local coordinate system of plane right. 
          void    SetRightPlacement();
          /// \ru Адаптировать локальную систему координат плоскости. \en Adapt the local coordinate system of a plane. 
          void    AdaptToPlace( const MbPlacement3D & );
          /// \ru Заменить локальную систему координат плоскости. \en Replace the local coordinate system of a plane. 
          void    SetPlacement( const MbPlacement3D & );
          /// \ru Инвертировать нормаль плоскости. \en Invert the normal of plane. 
          void    InvertNormal( MbRegTransform * ireg = NULL );

private:
          void    operator = ( const MbContourOnPlane & ); // \ru Не реализовано !!! \en Not implemented !!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbContourOnPlane )
};

IMPL_PERSISTENT_OPS( MbContourOnPlane )

#endif // __CUR_CONTOUR_ON_PLANE_H
