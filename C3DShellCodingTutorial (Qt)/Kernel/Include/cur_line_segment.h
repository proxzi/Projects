////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Отрезок прямой в двумерном пространстве.
         \en Line segment in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_LINE_SEGMENT_H
#define __CUR_LINE_SEGMENT_H


#include <cur_line.h>
#include <mb_rect1d.h>


class  MATH_CLASS MbLine;
class             DiskreteLengthData;


//------------------------------------------------------------------------------
/** \brief \ru Отрезок прямой в двумерном пространстве.
           \en Line segment in two-dimensional space. \~
  \details \ru Отрезок прямой описывается начальной точкой point1 и конечной точкой point2.\n
  	Область определения параметра отрезка располагается в пределах от нуля до единицы. 
    Начальной точке отрезка point1 соответствует параметр tmin=0, конечной точке отрезка point2 соответствует параметр tmax=1.\n
	  Радиус-вектор отрезка описывается векторной функцией\n
    r(t) = ((1 - t) point1) + (t point2).\n
           \en Line segment is described by the start point "point1" and the end point "point2". \n
  	Domain of a line segment is the range [0, 1]. 
    The start point of line segment corresponds to parameter tmin=0, the end point of line segment corresponds to parameter tmax=1.\n
	  Radius-vector of line segment is described by the vector function \n
    r(t) = ((1 - t) point1) + (t point2).\n \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbLineSegment : public MbCurve {
private :
  MbCartPoint point1; ///< \ru Начальная точка. \en Start point. 
  MbCartPoint point2; ///< \ru Конечная  точка. \en End point. 

public :
  MbLineSegment();
  MbLineSegment( double u1, double v1, double u2, double v2 ) : MbCurve(), point1( u1, v1 ), point2( u2, v2 ) {}
  MbLineSegment( const MbCartPoint &p1, const MbCartPoint &p2 );
  MbLineSegment( const MbCartPoint &p,  const MbVector &dir, double t1, double t2 );
  MbLineSegment( const MbCartPoint &initP, double x1, double x2 );
  MbLineSegment( const MbLine & line, double t1, double t2, int sense );
  MbLineSegment( const MbLineSegment & lseg, double t1, double t2 );
  MbLineSegment( double t1, double t2, double s, bool bTIsX );
//protected:
  MbLineSegment( const MbLineSegment & );
public :
  virtual ~MbLineSegment();

public :
  VISITING_CLASS( MbLineSegment ); 

   /** \ru \name Функции инициализации отрезка.
       \en \name Line segment initialization functions.
      \{ */
          // \ru Установить параметры отрезка \en Set the parameters of line segment 
          void        Init( const MbLineSegment & );
          void        Init( const MbCartPoint &p1, const MbCartPoint &p2 );
          void        Init( const MbCartPoint &pnt, double x1, double x2 );
          void        Init( double t1, double t2 );
          void        Init1( const MbCartPoint &p1, const MbCartPoint &p2, double &len, double &angle );
          void        Init2( const MbCartPoint &p1, MbCartPoint &p2, const double &len, double &angle );
          void        Init3( const MbCartPoint &p1, MbCartPoint &p2, double &len, const double &angle,
                             const DiskreteLengthData * diskrData = NULL );
          void        Init4( MbCartPoint &p1, const MbCartPoint &p2, const double &len, double &angle );
          void        Init5( MbCartPoint &p1, const MbCartPoint &p2, double &len, const double &angle,
                             const DiskreteLengthData * diskrData = NULL );
          void        Init6( const MbCartPoint &p1, MbCartPoint &p2, const double &len, const double &angle );
          void        Init7( MbCartPoint &p1, const MbCartPoint &p2, const double &len, const double &angle );
          void        Init8( MbCartPoint &p1, MbCartPoint &p2, double &len, double &angle,
                             const DiskreteLengthData & diskrData, bool correctP1 );
          void        Init9( const MbCartPoint & p1, MbCartPoint & p2, double & len, double & angle,
                             const DiskreteLengthData & diskrData, bool keepX );

  /** \} */
  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbePlaneType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual bool        IsSame ( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether the 'curve' curve is duplicate of current curve. 
  virtual bool        SetEqual( const MbPlaneItem & );     // \ru Сделать элементы равными \en Make equal elements 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual void        Transform( const MbMatrix &, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL );  // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual void        AddYourGabaritTo ( MbRect & ) const;    // \ru Добавь свой габарит в прямой прям-к \en Add bounding box into a straight box 
  virtual void        CalculateGabarit ( MbRect & ) const;              // \ru Определить габариты кривой \en Determine the bounding box of the curve 
  virtual void        CalculateLocalGabarit( const MbMatrix & into, MbRect & local ) const ; // \ru Добавь в прям-к свой габарит с учетом матрицы \en Add bounding box into a box with consideration of the matrix 
  virtual double      DistanceToPoint( const MbCartPoint & to ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual bool        IsVisibleInRect( const MbRect & r, bool exact = false ) const; // \ru Виден ли объект в заданном прямоугольнике \en Whether the object is visible in the given rectangle 
  using      MbCurve::IsVisibleInRect;      
  virtual bool        IsCompleteInRect( const MbRect & r ) const;  // \ru Виден ли объект полностью в в заданном прямоугольнике \en Whether the object is entirely visible in the given rectangle 
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for curve domain description.
      \{ */
  virtual double      GetTMin ()     const; // \ru Вернуть минимальное  значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax ()     const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool        IsClosed()     const; // \ru Проверка замкнутости \en Check for closedness 
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const; // \ru Проверка вырожденности \en Check for degeneracy 
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the curve's domain. 
            Functions: PointOn, FirstDer, SecondDer, ThirdDer,... correct the parameter
            when it is outside domain.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & p  ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector    & fd ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & td ) const; // \ru Третья производная \en Third derivative 
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
  virtual void       _PointOn  ( double t, MbCartPoint & p ) const;  // \ru Точка на кривой или на её продолжении \en Point on the curve or on its extension 
  virtual void       _FirstDer ( double t, MbVector    & v ) const;
  virtual void       _SecondDer( double t, MbVector    & v ) const;
  virtual void       _ThirdDer ( double t, MbVector    & v ) const;
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
      \en \name Common function of curve.
      \{ */
  virtual double      Curvature( double t ) const; // \ru Кривизна усеченной кривой \en Curvature of a trimmed curve 
  virtual void        Inverse( MbRegTransform * iReg = NULL );  // \ru Изменить направление кривой \en Change direction of a curve 

  virtual MbCurve *   Offset( double rad ) const; // \ru Смещение отрезка \en Shift of a line segment 
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить Nurbs-копию кривой \en Construct NURBS copy of the curve 

  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 ); // \ru Удалить часть усеченной кривой между параметрами t1 и t2 \en Delete a part of a trimmed curve between parameters t1 and t2 
  virtual MbeState    TrimmPart( double t1, double t2, MbCurve *& part2 );  // \ru Оставить часть усеченной кривой между параметрами t1 и t2 \en Keep a part of the trimmed curve between parameters t1 and t2 
  // \ru Выдать характерную точку усеченной кривой если она ближе чем dmax \en Get characteristic point of trimmed curve if it is closer than dmax 
  virtual bool        GetSpecificPoint( const MbCartPoint & from, double & dmax, MbCartPoint & pnt ) const;
  virtual MbeState    Deformation( const MbRect &, const MbMatrix & );  // \ru Деформация \en Deformation 
  virtual bool        IsInRectForDeform( const MbRect & r ) const;      // \ru Виден ли объект в заданном прямоугольнике для деформации \en Whether the object is visible in the specified rectangle for the deformation 

  virtual bool        IsStraight() const;                 // \ru Является ли линия прямолинейной \en Whether the line is straight 

  // \ru Положение точки относительно кривой. \en The point position relative to the curve. 
  // \ru iloc_InItem = 1 - точка находится слева по направлению, \en Iloc_InItem = 1 - the point is on the left, 
  // \ru iloc_OnItem = 0 - точка находится по направлению, \en Iloc_OnItem = 0 - the point is on the direction, 
  // \ru iloc_OutOfItem = -1 - точка находится справа по направлению. \en Iloc_OutOfItem = -1 - the point is on the right. 
  virtual MbeItemLocation PointRelative( const MbCartPoint & pnt, double eps = Math::LengthEps ) const;
  virtual double      PointProjection( const MbCartPoint & pnt ) const;  // \ru Проекция точки на отрезок \en Point projection on the line segment 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции \en Point projection on the curve or its extension in the projection search area 
  virtual void        PerpendicularPoint( const MbCartPoint & pnt, SArray<double> & tFind ) const; // \ru Вычисление всех перпендикуляров к кривой из данной точки \en Calculation of all perpendiculars to the curve from a given point 
  virtual void        IntersectHorizontal( double y, SArray<double> & cross ) const; // \ru Пересечение с горизонтальной прямой \en Intersection with the horizontal line 
  virtual void        IntersectVertical  ( double x, SArray<double> & cross ) const; // \ru Пересечение с вертикальной прямой \en Intersection with the vertical line 

  virtual bool        HasLength( double & length ) const;
  virtual double      GetMetricLength() const;  // \ru Метрическая длина \en The metric length 
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Evaluation of the metric length of the curve  
  // \ru Вычисление минимальной длины кривой между двумя точками на ней \en Calculation of minimal length of a curve between two points on it 
  virtual double      LengthBetween2Points( MbCartPoint & p1, MbCartPoint & p2, MbCartPoint * pc = NULL ) const;

  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const;
  virtual double      CalculateLength( double t1, double t2 ) const; // \ru Посчитать метрическую длину отрезка от параметра t1 до t2 с заданной точностью \en Coclculate the metric length of the line segment from parameter 't1' to 't2' with the given tolerance 
  virtual bool        GetMiddlePoint ( MbCartPoint & ) const; // \ru Выдать среднюю точку отрезка \en Get the middle point on a line segment 
  virtual bool        GetCentre      ( MbCartPoint & ) const; // \ru Выдать центр отрезка \en Get the center of a line segment 
  virtual bool        GetWeightCentre( MbCartPoint & ) const; // \ru Выдать центр тяжести кривой \en Get the center of gravity of the curve 
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves are similar for merge (joining) 
  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях \en The number of partitions for passage in the operations  
  virtual void        GetPointsByEvenLengthDelta( size_t n,  std::vector<MbCartPoint> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curves equally spaced by the arc length 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

          void        ThroughPoint( double t, const MbCartPoint & pnt ); // \ru Пройти через точку при данном параметре \en Pass through the point in the given parameter 
          void        InsertPoint( double t,  const MbCartPoint & pnt ); // \ru Вставить точку \en Insert a point 
          double      GetAngle() const; // \ru Выдать значение угла наклона отрезка \en Get the value of an angle inclination of a line segment 
          MbDirection GetDirection() const; // \ru Выдать вектор наклона отрезка \en Get the vector of a line segment inclination 
          bool        IsParallel( const MbLineSegment & seg, double eps = Math::AngleEps ) const; // \ru Проверка параллельности двух прямых \en Check for parallelism of two lines 
    const MbCartPoint & GetPoint1() const { return point1; }
    const MbCartPoint & GetPoint2() const { return point2; }
          MbCartPoint & SetPoint1()       { return point1; }
          MbCartPoint & SetPoint2()       { return point2; }
          void        GetPoint1( MbCartPoint & p ) const { p = point1; }
          void        GetPoint2( MbCartPoint & p ) const { p = point2; }
          void        SetPoint1( const MbCartPoint & p ) { point1 = p; }
          void        SetPoint2( const MbCartPoint & p ) { point2 = p; }
          void        SetLimitPoint( ptrdiff_t number, const MbCartPoint & pnt ); // \ru Заменить точку отрезка \en Replace the point of a line segment 
          void        CheckParameter( double & t ) const; // \ru Проверка и коррекция параметра \en Check and correction of parameter 

          // \ru Работа с базовой прямой \en Work with the base line 
          MbCartPoint Origin() const { MbCartPoint p( point1 ); return p; }
          MbVector    Derive() const { MbVector v( point1, point2 ); return v; }
          MbDirection Direction() const { MbDirection v( point1, point2 ); return v; }
          bool        Extend( const MbCartPoint & point ); // \ru Удлинить отрезок до проекции точки point \en Extend line segment to projection of point "point" 
          double      PointProjectionOnBaseLine( const MbCartPoint & pnt ) const; // \ru Проекция на прямую \en Projection on the line 
          double      PointProjectionOnBaseLine( const MbCartPoint & pnt, MbCartPoint & proj ) const; // \ru Проекция на прямую \en Projection on the line 
          double      DistanceToPointOnBaseLine( const MbCartPoint & pnt ) const; // \ru Расстояние от точки до проекции на прямую \en Distance from a point to a projection on the line 
          bool        IsHorizontal( double eps = Math::paramEpsilon ) const { return ::fabs(point1.y - point2.y) < eps; } // \ru Проверка горизонтальности \en Check for horizontality 
          bool        IsVertical  ( double eps = Math::paramEpsilon ) const { return ::fabs(point1.x - point2.x) < eps; } // \ru Проверка вертикальности \en Check for verticality 

//private:
  const   MbLineSegment & operator = ( const MbLineSegment & ); // \ru Реализовано \en Implemented 

  /** \} */

          void        ReadAsLineSeg( reader & in ); // \ru Чтение. 
          void        WriteAsLineSeg( writer & out ) const; // \ru Запись. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbLineSegment )
}; // MbLineSegment

IMPL_PERSISTENT_OPS( MbLineSegment )

//------------------------------------------------------------------------------
// \ru Инициализировать по отрезку \en Initialize by a line segment 
// ---
inline void MbLineSegment::Init( const MbLineSegment & ls ) {
  point1 = ls.point1;
  point2 = ls.point2;
}

//------------------------------------------------------------------------------
// \ru Пересчитать параметры отрезка \en Recalculate the parameters of the line segment 
// ---
inline void MbLineSegment::Init( const MbCartPoint & p1, const MbCartPoint & p2 ) {
  point1 = p1;
  point2 = p2;
}

//------------------------------------------------------------------------------
// \ru Инициализация горизонтального отрезка для штриховки \en Initialization of a horizontal segment for hatching 
// ---
inline void MbLineSegment::Init( const MbCartPoint & pnt, double x1, double x2 ) {
  point1 = pnt;
  point2 = pnt;
  point1.x += x1;
  point2.x += x2;
}

//------------------------------------------------------------------------------
// \ru Заменить точку отрезка \en Replace the point of a line segment 
// ---
inline void MbLineSegment::SetLimitPoint( ptrdiff_t number, const MbCartPoint & pnt )
{
  if ( number == 1 )  // \ru Меняем 1-ую точку \en Change the first point 
    point1 = pnt;
  else
    point2 = pnt;
}

//------------------------------------------------------------------------------
// \ru Выдать значение угла наклона отрезка \en Get the value of an angle inclination of a line segment 
// ---
inline double MbLineSegment::GetAngle() const {
  MbDirection d0( point1, point2 );
  return d0.DirectionAngle();
}

//------------------------------------------------------------------------------
// \ru Выдать вектор наклона отрезка \en Get the vector of a line segment inclination 
// ---
inline MbDirection MbLineSegment::GetDirection() const {
  MbDirection d0( point1, point2 );
  return d0;
}

//------------------------------------------------------------------------------
// \ru Проверка параллельности двух прямых \en Check for parallelism of two lines 
// ---
inline bool MbLineSegment::IsParallel( const MbLineSegment & seg, double eps ) const {
  MbDirection d0( point1, point2 );
  MbDirection d1( seg.point1, seg.point2 );
  return ( ::fabs( d0.ay * d1.ax - d0.ax * d1.ay ) < eps );
}

//------------------------------------------------------------------------------
// \ru Проверка и коррекция параметра \en Check and correction of parameter 
// ---
inline void MbLineSegment::CheckParameter( double & t ) const {
  if ( t < 0 ) t = 0;
  if ( t > 1 ) t = 1;
}

//------------------------------------------------------------------------------
// \ru Инициализация по другому отрезку \en Initialization by another segment 
// ---
inline const MbLineSegment & MbLineSegment::operator = ( const MbLineSegment & other ) {
  point1 = other.point1;
  point2 = other.point2;

  return *this;
}


#endif // __CUR_LINE_SEGMENT_H
