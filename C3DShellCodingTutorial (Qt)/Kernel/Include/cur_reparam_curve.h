////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Репараметризованная кривая в двумерном пространстве.
         \en Reparametrized curve in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_REPARAM_CURVE_H
#define __CUR_REPARAM_CURVE_H


#include <curve.h>


class MbRegDuplicate;
class MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Репараметризованная кривая в двумерном пространстве.
           \en Reparametrized curve in two-dimensional space. \~
  \details \ru Репараметризованная кривая служит для согласования областей определения кривых. \n
    Геометрически репараметризованная кривая полностью совпадает с базовой кривой basisCurve.
    Репараметризованная кривая имеет другую область определения и, как следствие, другую длину своих производных.
    Параметры базовой кривой и репараметризованной кривой связаны равенством: \n
    dt (t - tmin) = t_basisCurve - tmin_basisCurve, где t - параметр репараметризованной кривой.
    Базовой кривой для репараметризованной кривой не может служить другая репараметризованная кривая.
    В подобной ситуации выполняется переход к первичной базовой кривой.
           \en Reparametrized curve is used for matching domains of curves. \n
    Geometrically reparametrized curve completely coincides with base curve 'basisCurve'.
    Reparametrized curve has another definition domain and as a result another length of its derivatives.
    Parameters of base curve and reparametrized curve are related by the equality: \n
    dt (t - tmin) = t_basisCurve - tmin_basisCurve, where 't' - parameter of reparametrized curve.
    Another reparametrized curve can't be the base curve for a reparametrized curve.
    In this situation it changes to the initial base curve. \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbReparamCurve : public MbCurve {
  enum MbeReparamType {
    rt_Linear,   ///< \ru Линейная репараметризация. \en Linear reparametrization.
    rt_Quadratic ///< \ru Квадратичная репараметризация. \en Quadratic reparametrization. 
  };

protected :
  MbCurve *      basisCurve;  ///< \ru Базовая кривая. \en The base curve.
  MbeReparamType reparamType; ///< \ru Способ репараметризации. \en Way of repatametrization.
  double         tmin;        ///< \ru Начальный параметр. \en Start parameter. 
  double         tmax;        ///< \ru Конечный  параметр. \en End parameter.
  double         a;           ///< \ru Коэффициент при квадратичном члене репараметризующего многочлена. \en The coefficient of the quadratic term of the reparametrizing polynomial.
  double         b;           ///< \ru Коэффициент при линейном члене репараметризующего многочлена. \en The coefficient of the linear term of the reparametrizing polynomial.
  double         c;           ///< \ru Свободный коэффициент репараметризующего многочлена. \en The free coefficient of the reparametrizing polynomial.

public :
  MbReparamCurve( const MbCurve &, double t1, double t2 );
  MbReparamCurve( const MbCurve &, const double t1, const double t2, const double begFirstDerValue );
protected:
  MbReparamCurve( const MbReparamCurve & );
public :
  virtual ~MbReparamCurve();

public :
  VISITING_CLASS( MbReparamCurve ); 

          void        Init( double t1, double t2 );
          void        Init( double t1, double t2, double begFirstDerValue );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbePlaneType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual bool        IsSimilar ( const MbPlaneItem & ) const; // \ru Являются ли элементы подобными \en Whether the elements are similar 
  virtual bool        SetEqual( const MbPlaneItem & );       // \ru Сделать элементы равными \en Make the elements equal 
  virtual void        Transform( const MbMatrix & matr, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector & to, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual	bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual MbCurve *   Offset( double rad ) const;	// \ru Смещение усеченной кривой \en Shift of a trimmed curve 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const;
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;
  virtual	MbContour * NurbsContour() const; // \ru Построить контур \en Create a contour 
  virtual void        AddYourGabaritTo( MbRect & r ) const; // \ru Добавь свой габарит в прямой прям-к \en Add your own gabarit into the given bounding rectangle 
  virtual void        CalculateGabarit( MbRect & r ) const; // \ru Определить габариты кривой \en Determine the bounding box of a curve 
  virtual bool        IsVisibleInRect( const MbRect & r, bool exact = false ) const; // \ru Виден ли объект в заданном прямоугольнике \en Whether the object is visible in the given rectangle 
  using      MbCurve::IsVisibleInRect;   
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for description of a curve domain.
      \{ */
  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double      GetTMin () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of the parameter 
  virtual bool        IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double      GetPeriod() const; // \ru Вернуть период \en Get period  
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
            Исключение составляет MbLine (прямая).
      \en \name Functions for working in the curve's domain. 
            Functions PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            if it is out of domain bounds.
            Except MbLine (line).
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & p  ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector    & fd ) const; // \ru Первая производная \en The first derivative 
  virtual void        SecondDer( double & t, MbVector    & sd ) const; // \ru Вторая производная \en The second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & td ) const; // \ru Третья производная \en The third derivative 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения кривой. 
            Функции _PointOn, _FirstDer, _SecondDer, _ThirdDer,... не корректируют параметр
            при выходе за пределы области определения. При выходе за область определения незамкнутая
            кривая, в общем случае, продолжается по касательной, которую она имеет на соответствующем конце.
            Исключение составляют дуги эллипса и окружности - они продолжаются в соответствии со своими уравнениями.
      \en \name Functions for working inside and outside the curve's domain. 
            Functions _PointOn, _FirstDer, _SecondDer, _ThirdDer,... don't correct parameter
            if it is out of domain bounds. If the parameter is out of domain bounds, an unclosed
            curve is extended by tangent vector at corresponding end point in general case.
            Except arcs of an ellipse or a circle - they are extended according to their equations.
      \{ */
  virtual void       _PointOn  ( double t, MbCartPoint & p ) const;
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
      \en \name Functions of moving along the curve
    \{ */
  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  virtual double      DeviationStep( double t, double _atol ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  /** \} */

  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменение направления кривой на противоположное \en Change curve direction to the opposite one 
  virtual double      DistanceToPoint( const MbCartPoint & toP ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual bool        DistanceToPointIfLess( const MbCartPoint & toP, double & d ) const; // \ru Расстояние до точки, если оно меньше d \en Distance to a point if it is less than 'd' 
  virtual MbeState    Deformation( const MbRect &, const MbMatrix & );  // \ru Деформация \en Deformation 
  // \ru Удалить часть кривой между параметрами t1 и t2 \en Delete a part of a curve between parameters t1 and t2 
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 );
  // \ru Оставить часть кривой между параметрами t1 и t2 \en Keep a piece of a curve between parameters t1 and t2  
  virtual MbeState    TrimmPart( double t1, double t2, MbCurve *& part2 );

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 

  virtual bool        IsBounded()    const; // \ru Признак ограниченной кривой \en Attribute of a bounded curve 
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const; // \ru Проверка вырожденности кривой \en Check for curve degeneracy 
  virtual bool        IsStraight()   const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Являются ли стыки контура\кривой гладкими? \en Whether the joints of a contour\curve are smooth. 
  virtual bool        IsCompleteInRect( const MbRect & r ) const; // \ru Виден ли объект полностью в в заданном прямоугольнике \en Whether the object is completely visible in the given rectangle 
  virtual double      CalculateMetricLength() const; // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual bool        HasLength( double & length ) const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      GetMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Estimation of metric length of the curve  
  virtual double      Curvature      ( double t ) const; // \ru Кривизна кривой \en Curvature of the curve 

  virtual double      CalculateLength( double t1, double t2 ) const;
  // \ru Положение точки относительно кривой. \en The point position relative to the curve. 
  // \ru Возвращает результат : \en Returning result: 
  // \ru iloc_InItem = 1 - точка находится слева от кривой, \en Iloc_InItem = 1 - point is to the left of the curve, 
  // \ru iloc_OnItem = 0 - точка находится на кривой, \en Iloc_OnItem = 0 - point is on the curve, 
  // \ru iloc_OutOfItem = -1 - точка находится справа от кривой. \en Iloc_OutOfItem = -1 - point is to the right of the curve. 
  virtual MbeItemLocation PointRelative( const MbCartPoint & pnt, double eps = Math::LengthEps ) const;
  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual double      PointProjection( const MbCartPoint & ) const; // \ru Проекция точки на кривую \en Point projection on the curve 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции \en Projection of a point onto the curve or its extension in the projection region 
  // \ru Вычисление всех перпендикуляров к кривой из данной точки \en Calculation of all the perpendiculars to the curve from a given point 
  virtual void        PerpendicularPoint( const MbCartPoint & pnt, SArray<double> & tFind ) const;
  virtual bool        SmallestPerpendicular( const MbCartPoint & pnt, double & tProj ) const; // \ru Нахождение ближайшего перпендикуляра к кривой из данной точки \en Calculation of the closest perpendicular to the curve from the given point 
  virtual void        TangentPoint( const MbCartPoint & pnt, SArray<double> & tFind ) const; // \ru Вычисление всех касательных к кривой из данной точки \en Calculation of all the tangents to the curve from a given point 
  virtual void        IntersectHorizontal( double y, SArray<double> & ) const; // \ru Пересечение кривой с горизонтальной прямой \en Intersection of a curve with a horizontal line 
  virtual void        IntersectVertical  ( double x, SArray<double> & ) const; // \ru Пересечение с вертикальной прямой \en Intersection with a vertical line 
  virtual void        SelfIntersect( SArray<MbCrossPoint> &, double metricEps = Math::LengthEps ) const; // \ru Самопересечение произвольной кривой \en Self-intersection of an arbitrary curve 

  // \ru Определение особых точек офсетной кривой \en Determination of special points of an offset curve 
  virtual void        OffsetCuspPoint( SArray<double> & tCusps, double dist ) const;
  virtual bool        GetMiddlePoint( MbCartPoint & ) const; // \ru Выдать среднюю точку кривой \en Get mid-point of a curve 
  virtual bool        GoThroughPoint( MbCartPoint & p0 );
  // \ru Вычисление минимальной длины кривой между двумя точками на ней \en Calculate the minimal curve length between two points on it 
  virtual double      LengthBetween2Points( MbCartPoint & p1, MbCartPoint & p2, MbCartPoint * pc = NULL ) const;
  virtual bool        GetSpecificPoint( const MbCartPoint & from, double & dmax, MbCartPoint & pnt ) const; // \ru Выдать характерную точку кривой если она ближе чем dmax \en Get control point of curve if it is closer than 'dmax' 
  virtual bool        GetWeightCentre( MbCartPoint & c ) const; // \ru Выдать центр тяжести кривой \en Get the center of gravity of the curve 
  virtual bool        GetCentre( MbCartPoint & c ) const; // \ru Выдать центр кривой \en Get center of curve 
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const; // \ru Сдвинуть параметр t на расстояние len по направлению \en Translate parameter 't' by distance 'len' along the direction 
  virtual bool        GetAxisPoint( MbCartPoint & p ) const; // \ru Точка для построения оси \en Point for the axis construction 
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 
  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях \en Count of subdivisions for pass in operations  
  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;


  virtual void        GetPointsByEvenLengthDelta( size_t n,  std::vector<MbCartPoint> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curve equally spaced by the arc length 

          void        ParameterInto( double & ) const; // \ru Перевод параметра базовой кривой в локальный параметр \en Transformation of the base curve parameter to a local parameter 
          void        ParameterFrom( double & ) const; // \ru Перевод локального параметра в параметр базовой кривой \en Transformation of a local parameter to the base curve parameter 
          double      EpsilonInto( double eps ) const; // \ru Перевод точности параметра базовой кривой в точность локального параметра \en Transformation of the base curve parameter tolerance to a local parameter tolerance 
          double      EpsilonFrom( double eps ) const; // \ru Перевод точности локального параметра в точность параметра базовой кривой \en Transformation of a local parameter tolerance to the base curve parameter tolerance 

  virtual const MbCurve & GetBasisCurve() const;
  virtual       MbCurve & SetBasisCurve();

          void        SetBasisCurve( MbCurve & );      // \ru Заменить плоскую кривую \en Replace the planar curve 
          double      Tmin() const { return tmin; }      // \ru Начальный параметр \en Start parameter 
          double      Tmax() const { return tmax; }      // \ru Конечный  параметр \en End parameter 
          double      Dt()   const { return b;   }      // \ru Производная параметра кривой basisCurve по параметру \en Derivative of parameter of 'basisCurve' curve by parameter 
          void        SetTmin( double t );
          void        SetTmax( double t );
          void        SetDt  ( double d );

          MbeReparamType GetReparamType() const { return reparamType; } // \ru Тип параметризации. \en Parameterization type.

  // \ru !!! геометрия подложки тождественна геометрии кривой, отлична параметризация !!! \en !!! geometry of substrate is identical to geometry of curve, parameterization is different !!! 
  virtual const MbCurve & GetSubstrate() const; // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual       MbCurve & SetSubstrate();       // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual int         SubstrateCurveDirection() const;    // \ru Направление подложки относительно кривой или наоборот \en Direction of substrate relative to the curve or vice versa 
  virtual void        SubstrateToCurve( double & ) const; // \ru Преобразовать параметр подложки в параметр кривой \en Transform a substrate parameter to the curve parameter 
  virtual void        CurveToSubstrate( double & ) const; // \ru Преобразовать параметр кривой в параметр подложки \en Transform a curve parameter to the substrate parameter 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

          bool        IsLinear() const { return (reparamType == rt_Linear); } // \ru Является ли репараметризация линейной? \en Is the re-parametrization linear?

  /** \} */

private:
          void        operator = ( const MbReparamCurve & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbReparamCurve )
}; // MbReparamCurve

IMPL_PERSISTENT_OPS( MbReparamCurve )

//------------------------------------------------------------------------------
// \ru Перевод параметра базовой кривой в новый параметр \en Transformation of the base curve parameter to a new parameter 
// ---
inline void MbReparamCurve::ParameterInto( double & t ) const {
  if ( reparamType == rt_Linear )
    t = ( t - c ) / b;
  else {
    C3D_ASSERT( ::fabs(a) > NULL_EPSILON );
    const double discriminant = b * b + 4.0 * a * (t - c);
    if ( discriminant > EXTENT_EQUAL )
      t = 0.5 * ( ::sqrt(discriminant) - b ) / a;
    else
      t = -0.5 * b / a;
  }
}


//------------------------------------------------------------------------------
// \ru Перевод нового параметра в параметр базовой кривой \en Transformation of a new parameter to the base curve parameter 
// ---
inline void MbReparamCurve::ParameterFrom( double & t ) const {
  if ( reparamType == rt_Linear )
    t = b * t + c;
  else
    t = a * t * t + b * t + c;
}


//------------------------------------------------------------------------------
// \ru Перевод точности параметра базовой кривой в точность локального параметра \en Transformation of the base curve parameter tolerance to a local parameter tolerance 
// ---
inline double MbReparamCurve::EpsilonInto( double eps ) const {
  double res = 0.0;

  if ( reparamType == rt_Linear ) {
    if ( ::fabs(b) > Math::paramEpsilon )
      res = eps / b;
  }
  else {
    const double bmin = 2.0 * a * tmin + b;
    const double bmax = 2.0 * a * tmax + b;
    const double div = std_max( bmin, bmax );
    if ( ::fabs(div) > Math::paramEpsilon )
      res = eps / div;
  }

  return res;
}


//------------------------------------------------------------------------------
// \ru Перевод точности локального параметра в точность параметра базовой кривой \en Transformation of a local parameter tolerance to the base curve parameter tolerance 
// ---
inline double MbReparamCurve::EpsilonFrom( double eps ) const {
  double res = 0.0;

  if ( reparamType == rt_Linear )
    return eps * b;
  else {
    const double bmin = 2.0 * a * tmin + b;
    const double bmax = 2.0 * a * tmax + b;
    const double mul = std_min( bmin, bmax );
    res = eps * mul;
  }

  return res;
}


#endif // __CUR_REPARAM_CURVE_H
