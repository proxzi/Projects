﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кривая, вырожденная в точку.
         \en The curve degenerated to a point. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_POINT_CURVE_H
#define __CUR_POINT_CURVE_H

#include <curve.h>


class             MbRegDuplicate;
class             MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Кривая, вырожденная в точку.
           \en The curve degenerated to a point. \~
  \details \ru Кривая, вырожденная в точку, описывается точкой.
    Для согласования с другими кривыми кривая формально может быть замкнутой или разомкнутой и 
    быть заданной на определённой области определения. \n
           \en The curve degenerated to a point is described by point.
    For consistency with other curves the curve can be closed or open formally and 
    be given on the specific domain. \n \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbPointCurve : public MbCurve {
protected:
  MbCartPoint point;  ///< \ru Точка. \en A point. 
  bool        closed; ///< \ru Признак замкнутости \en A closedness attribute 
  double      tmin;   ///< \ru Начальное значение параметра. \en Initial value of parameter. 
  double      tmax;   ///< \ru Конечное  значение параметра. \en Final value of parameter. 

public :
  MbPointCurve( const MbCartPoint &p, double t1, double t2, bool cl );
  MbPointCurve( const MbCartPoint &p, bool cl );
  MbPointCurve( bool cl );
protected:
  MbPointCurve( const MbPointCurve & );
public :
  virtual ~MbPointCurve();

public :
  VISITING_CLASS( MbPointCurve ); 

  /** \ru \name Функции кривой, вырожденной в точку.
      \en \name Functions of curve degenerated to a point.
      \{ */
          void        Init( const MbCartPoint &p, double t1, double t2, bool cl );
          void        Init( double t1, double t2, bool cl );
          void        Init( const MbCartPoint &p );
          void        SetTMin  ( double t ) { tmin = t; }
          void        SetTMax  ( double t ) { tmax = t; }
          void        SetClosed( bool cl  ) { closed = cl; }

  /** \} */
  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of geometric object.
      \{ */

  virtual MbePlaneType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual bool        SetEqual( const MbPlaneItem & );       // \ru Сделать элементы равными \en Make equal elements 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const;
  virtual void        Move     ( const MbVector &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL );
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual void        Transform( const MbMatrix &, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL );
  virtual void        AddYourGabaritTo ( MbRect & ) const;    // \ru Добавь свой габарит в прямой прям-к \en Add bounding box into a straight box 
  virtual void        CalculateLocalGabarit( const MbMatrix & into, MbRect & local ) const; // \ru Добавь в прям-к свой габарит с учетом матрицы \en Add bounding box into a box with consideration of the matrix 
  virtual double      DistanceToPoint( const MbCartPoint & to ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual	bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether the 'curve' curve is duplicate of current curve. 
  virtual bool        IsVisibleInRect( const MbRect & r, bool exact = false ) const; // \ru Виден ли объект в заданном прямоугольнике \en Whether the object is visible in the given rectangle 
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for curve domain description.
      \{ */
  virtual double      GetTMin () const; // \ru Вернуть минимальное  значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool        IsClosed() const; // \ru Проверка замкнутости \en Check for closedness 
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the curve's domain. 
            Functions PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            when it is out of domain bounds.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & p ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector    & v ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & v ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & v ) const; // \ru Третья производная \en Third derivative 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения кривой. 
            Функции _PointOn, _FirstDer, _SecondDer, _ThirdDer,... не корректируют параметр
            при выходе за пределы области определения. При выходе за область определения незамкнутая
            кривая, в общем случае, продолжается по касательной, которую она имеет на соответствующем конце.
      \en \name Functions for working inside and outside the curve's domain. 
            Functions _PointOn, _FirstDer, _SecondDer, _ThirdDer,... do not correct parameter
            when it is out of domain bounds. When parameter is out of domain bounds, an unclosed
            curve is extended by tangent vector at corresponding end point in general case. 
      \{ */
  virtual void       _PointOn  ( double  t, MbCartPoint & p ) const;  // \ru Точка на кривой или на её продолжении \en Point on the curve or on its extension 
  virtual void       _FirstDer ( double  t, MbVector    & v ) const;
  virtual void       _SecondDer( double  t, MbVector    & v ) const;
  virtual void       _ThirdDer ( double  t, MbVector    & v ) const;
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;
  /** \} */

  /** \ru \name Функции движения по кривой
      \en \name Function of moving by curve 
    \{ */  
  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of approximation step with consideration of curvature radius 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации по угловой толерантности \en Calculation of approximation step by angular tolerance 
  /** \} */

  /** \ru \name Общие функции кривой
      \en \name Common function of curve
      \{ */
  virtual double      Curvature( double t ) const; // \ru Кривизна усеченной кривой \en Curvature of a trimmed curve 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление кривой \en Change direction of a curve 
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const; // \ru Проверка вырожденности \en Check for degeneracy 
  virtual bool        HasLength( double & length ) const;

  virtual MbCurve *   Offset( double rad ) const; // \ru Смещение отрезка \en Shift of a line segment 
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 

  // \ru Удалить часть усеченной кривой между параметрами t1 и t2 \en Delete a part of a truncated curve between parameters t1 and t2 
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 );
  // \ru Оставить часть усеченной кривой между параметрами t1 и t2 \en Keep a part of the trimmed curve between parameters t1 and t2 
  virtual MbeState    TrimmPart(  double t1, double t2, MbCurve *& part2 );
  virtual bool        IsStraight() const;                 // \ru Является ли линия прямолинейной \en Whether the line is straight 

  // \ru Положение точки относительно кривой. \en The point position relative to the curve. 
  // \ru Возвращает результат : \en Returning result: 
  // \ru iloc_OutOfItem = -1 - точка находится вне кривой, \en Iloc_OutOfItem = -1 - point is outside of the curve, 
  // \ru iloc_OnItem = 0 - точка находится на кривой. \en Iloc_OnItem = 0 - point is located on the curve, 
  virtual MbeItemLocation PointRelative( const MbCartPoint & pnt, double eps = Math::LengthEps ) const;
  virtual double      PointProjection( const MbCartPoint & pnt ) const;  // \ru Проекция точки на отрезок \en Point projection on the line segment 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции \en Point projection on the curve or its extension in the projection search area 
  virtual void        IntersectHorizontal( double y, SArray<double> & cross ) const; // \ru Пересечение с горизонтальной прямой \en Intersection with the horizontal line 
  virtual void        IntersectVertical  ( double x, SArray<double> & cross ) const; // \ru Пересечение с вертикальной прямой \en Intersection with the vertical line 

  virtual double      GetMetricLength() const;  // \ru Метрическая длина \en The metric length 
  virtual bool        GetMiddlePoint ( MbCartPoint & ) const; // \ru Выдать среднюю точку отрезка \en Calculate a middle point on a line segment 
  virtual bool        GetCentre      ( MbCartPoint & ) const; // \ru Выдать центр отрезка \en Get the center of a line segment 
  virtual bool        GetWeightCentre( MbCartPoint & ) const; // \ru Выдать центр тяжести кривой \en Get the center of gravity of the curve 
  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях \en The number of partitions for passage in the operations  

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  const   MbCartPoint & GetPoint() const { return point; }
          MbCartPoint & SetPoint() { return point; }

  /** \} */

private:
          void        CheckParameter( double & t ) const;
          void        operator = ( const MbPointCurve & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbPointCurve )
}; // MbPointCurve

IMPL_PERSISTENT_OPS( MbPointCurve )

#endif // __CUR_POINT_CURVE_H
