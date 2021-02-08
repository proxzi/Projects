////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Отрезок прямой в трёхмерном пространстве.
         \en Line segment in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_LINE_SEGMENT3D_H
#define __CUR_LINE_SEGMENT3D_H


#include <curve3d.h>


class  MATH_CLASS MbLineSegment;
class  MATH_CLASS MbLine3D;


//------------------------------------------------------------------------------
/** \brief \ru Отрезок прямой в трёхмерном пространстве.
           \en Line segment in three-dimensional space. \~
  \details \ru Отрезок прямой описывается начальной точкой point1 и конечной точкой point2.\n
    Область определения параметра отрезка располагается в пределах от нуля до единицы. 
    Начальной точке отрезка point1 соответствует параметр tmin=0, конечной точке отрезка point2 соответствует параметр tmax=1.\n
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией\n
    r(t) = ((1 - t) point1) + (t point2).\n
           \en Line segment is described by the start point "point1" and the end point "point2". \n
    Domain of a line segment is the range [0, 1]. 
    The start point of line segment corresponds to parameter tmin=0, the end point of line segment corresponds to parameter tmax=1.\n
    Radius-vector of the curve in the method PointOn(double&t,MbCartPoint3D&r) is described by the vector function\n
    r(t) = ((1 - t) point1) + (t point2).\n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbLineSegment3D : public MbCurve3D {
private :
  MbCartPoint3D point1; ///< \ru Начальная точка. \en Start point. 
  MbCartPoint3D point2; ///< \ru Конечная  точка. \en End point. 

public :
  MbLineSegment3D() : MbCurve3D(), point1(), point2() {}
  explicit MbLineSegment3D( const MbCartPoint3D & p1, const MbCartPoint3D & p2 );
  explicit MbLineSegment3D( const MbCartPoint3D & p, const MbVector3D & v );
  explicit MbLineSegment3D( const MbCartPoint3D & p, const MbVector3D & v, double t );
  MbLineSegment3D( const MbLine3D & initLine, double t1, double t2 );
  MbLineSegment3D( const MbLineSegment &, const MbPlacement3D & plane );
protected:
  MbLineSegment3D( const MbLineSegment3D & );
public :
  virtual ~MbLineSegment3D();

public :
  VISITING_CLASS( MbLineSegment3D );

          // \ru Установить параметры отрезка. \en Set the parameters of line segment.
          void    Init( const MbLineSegment3D & );
          void    Init( const MbCartPoint3D & p1, const MbCartPoint3D & p2 );
          void    Init( const MbCartPoint3D & p0, const MbVector3D & v0 );
          void    Init( const MbPlacement3D &,   const MbLineSegment & );
          void    Init( double t1, double t2 );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual ( const MbSpaceItem & );           // \ru Сделать равным \en Make equal 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMin()  const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax()  const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double & t, MbVector3D & )    const; // \ru Первая производная \en First derivative 
  virtual void    SecondDer( double & t, MbVector3D & )    const; // \ru Вторая производная \en Second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & )    const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Функции кривой для работы вне области определения параметрической кривой \en Functions of curve for working outside the domain of parametric curve 
  virtual void   _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void   _FirstDer ( double t, MbVector3D & )     const; // \ru Первая производная \en First derivative 
  virtual void   _SecondDer( double t, MbVector3D & )     const; // \ru Вторая производная \en Second derivative 
  virtual void   _ThirdDer ( double t, MbVector3D & )     const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить Nurbs-копию кривой \en Construct NURBS copy of the curve 
  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const;

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  CalculateMetricLength() const;           // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double  GetLengthEvaluation() const;
  virtual double  CalculateLength( double t1, double t2 ) const;

  virtual void    CalculateGabarit     ( MbCube & ) const;          // \ru Выдать габарит кривой \en Get the bounding box of curve 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  virtual void    GetCentre      ( MbCartPoint3D & wc ) const; // \ru Посчитать центр кривой \en Calculate a center of curve 
  virtual void    GetWeightCentre( MbCartPoint3D & wc ) const; // \ru Посчитать центр тяжести кривой \en Calculate the gravity center of the curve 
  virtual double  Curvature( double t ) const;               // \ru Кривизна усеченной кривой \en Curvature of a trimmed curve 
  virtual bool    NearPointProjection  ( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Ближайшая проекция точки на кривую \en The nearest point projection to the curve 

  virtual double  Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double  DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double  MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of curve. 
  virtual MbCurve * GetMapPsp( const MbMatrix3D &, double zNear, MbRect1D * pRgn = NULL ) const; // \ru Дать перспективную плоскую проекцию кривой. \en Get a planar geometric projection of curve. 

  virtual bool    IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual size_t  GetCount  () const;
  virtual bool    IsPlanar  () const; // \ru Является ли кривая плоской \en Whether a curve is planar 
  virtual bool    DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                 VERSION version = Math::DefaultMathVersion() ) const; // \ru Сдвинуть параметр t на расстояние len по направлению \en Shift the parameter t by the distance 'len' in the direction 
  virtual void    CalculatePolygon( const MbStepData & stepData, MbPolygon3D & polygon ) const; // \ru Рассчитать полигон \en Calculate a polygon 
  virtual void    GetPointsByEvenLengthDelta( size_t n,  std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curves equally spaced by the arc length 
  virtual bool    IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves are similar for merge (joining) 

    const MbCartPoint3D & GetPoint1() const { return point1; }
    const MbCartPoint3D & GetPoint2() const { return point2; }
          MbCartPoint3D & SetPoint1()       { return point1; }
          MbCartPoint3D & SetPoint2()       { return point2; }
          void    GetPoint1( MbCartPoint3D & p ) const { p = point1; }
          void    GetPoint2( MbCartPoint3D & p ) const { p = point2; }
          void    SetPoint1( const MbCartPoint3D & p ) { point1 = p; }
          void    SetPoint2( const MbCartPoint3D & p ) { point2 = p; }
          void    SetLimitPoint( ptrdiff_t number, const MbCartPoint3D &pnt ); // \ru Заменить точку отрезка \en Replace the point of a line segment 

  /// \ru Является ли объект смещением \en Whether the object is a shift 
  virtual bool    IsShift ( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;

private:
          void    operator = ( const MbLineSegment3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbLineSegment3D )
};

IMPL_PERSISTENT_OPS( MbLineSegment3D )

#endif // __CUR_LINE_SEGMENT3D_H
