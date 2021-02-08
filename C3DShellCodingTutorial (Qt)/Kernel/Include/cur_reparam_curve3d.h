////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Репараметризованная кривая в трехмерном пространстве.
         \en Reparametrized curve in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_REPARAM_CURVE3D_H
#define __CUR_REPARAM_CURVE3D_H


#include <curve3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Репараметризованная кривая в трехмерном пространстве.
           \en Reparametrized curve in three-dimensional space. \~
  \details \ru Репараметризованная кривая служит для согласования областей определения кривых. \n
    Геометрически репараметризованная кривая полностью совпадает с базовой кривой basisCurve.
    Репараметризованная кривая имеет другую область определения и, как следствие, другую длину своих производных.
    Параметры базовой кривой и репараметризованной кривой связаны равенствами: \n
    Для линейной репараметризации b * (t - tmin) = t_basisCurve - tmin_basisCurve, где t - параметр репараметризованной кривой.
    Для квадратичной репараметризации t_basisCurve = a * t * t + b * t + c,  где t - параметр репараметризованной кривой.
    При квадратичной репараметризации можно выбирать не только новый диапазон параметров, но и величину первой производной в начале кривой.
    Базовой кривой для репараметризованной кривой не может служить другая репараметризованная кривая.
    В подобной ситуации выполняется переход к первичной базовой кривой.
           \en Reparametrized curve is used for matching domains of curves. \n
    Geometrically reparametrized curve completely coincides with base curve 'basisCurve'.
    Reparametrized curve has another definition domain and as a result another length of its derivatives.
    Parameters of base curve and reparametrized curve are related by the equality: \n
    For linear reparametrization b * (t - tmin) = t_basisCurve - tmin_basisCurve, where 't' - parameter of reparametrized curve.
    For quadratic reparametrization t_basisCurve = a * t * t + b * t + c, where 't' - parameter of reparametrized curve.
    When the quadratic reparametrization is used it is possible to define the first derivative value at the beginning of the curve.
    Another reparametrized curve can't be the base curve for a reparametrized curve.
    In this situation it changes to the initial base curve. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbReparamCurve3D : public MbCurve3D {
  enum MbeReparamType {
    rt_Linear,   ///< \ru Линейная репараметризация. \en Linear reparametrization.
    rt_Quadratic ///< \ru Квадратичная репараметризация. \en Quadratic reparametrization. 
  };

protected:
  MbCurve3D *    basisCurve;  ///< \ru Базовая кривая. \en The base curve.
  MbeReparamType reparamType; ///< \ru Способ репараметризации. \en Way of repatametrization.
  double         tmin;        ///< \ru Начальный параметр. \en Start parameter. 
  double         tmax;        ///< \ru Конечный  параметр. \en End parameter.
  double         a;           ///< \ru Коэффициент при квадратичном члене репараметризующего многочлена. \en The coefficient of the quadratic term of the reparametrizing polynomial.
  double         b;           ///< \ru Коэффициент при линейном члене репараметризующего многочлена. \en The coefficient of the linear term of the reparametrizing polynomial.
  double         c;           ///< \ru Свободный коэффициент репараметризующего многочлена. \en The free coefficient of the reparametrizing polynomial.

protected:
  MbReparamCurve3D( const MbReparamCurve3D &, MbRegDuplicate * );
private :
  MbReparamCurve3D( const MbReparamCurve3D & ); // \ru Не реализовано. \en Not implemented. 
public :
  MbReparamCurve3D( const MbCurve3D &, double t1, double t2 );
  MbReparamCurve3D( const MbCurve3D &, double t1, double t2, double begFirstDerValue );

  virtual ~MbReparamCurve3D();

public :
  VISITING_CLASS( MbReparamCurve3D );
  
          void        Init( double t1, double t2 );
          void        Init( double t1, double t2, double begFirstDerValue );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA()              const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией \en Whether the object is a copy 
  virtual bool        SetEqual ( const MbSpaceItem & );       // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual bool        IsSpaceSame( const MbSpaceItem & item, double eps = METRIC_REGION ) const; // \ru Являются ли объекты идентичными в пространстве \en Whether the objects are equal in space 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double      GetTMin()  const;
  virtual double      GetTMax()  const;
  virtual bool        IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double      GetPeriod() const; // \ru Вернуть период \en Get period  
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector3D & ) const;  // \ru Первая производная \en The first derivative 
  virtual void        SecondDer( double & t, MbVector3D & ) const;  // \ru Вторая производная \en The second derivative 
  virtual void        ThirdDer ( double & t, MbVector3D & ) const;  // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void        Normal   ( double & t, MbVector3D & ) const;// \ru Вектор главной нормали \en Vector of the principal normal 
  // \ru Функции кривой для работы вне области определения параметрической кривой \en Functions of curve for working outside the domain of parametric curve 
  virtual void       _PointOn  ( double t,  MbCartPoint3D & ) const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void       _FirstDer ( double t,  MbVector3D & ) const;    // \ru Первая производная \en The first derivative 
  virtual void       _SecondDer( double t,  MbVector3D & ) const;    // \ru Вторая производная \en The second derivative 
  virtual void       _ThirdDer ( double t,  MbVector3D & ) const;    // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void       _Normal   ( double t,  MbVector3D & ) const;// \ru Вектор главной нормали \en Vector of the principal normal 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 
  
  virtual const MbCurve3D & GetBasisCurve() const;
  virtual       MbCurve3D & SetBasisCurve();
  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Create a trimmed curve 

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 

  virtual double      GetMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      CalculateMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      CalculateLength( double t1, double t2 ) const;
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                     VERSION version = Math::DefaultMathVersion() ) const; 
  virtual double      GetLengthEvaluation() const;

  virtual void        CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system 
  virtual bool        IsDegenerate( double eps = METRIC_PRECISION ) const; // \ru Проверка вырожденности кривой \en Check for curve degeneracy 
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Являются ли стыки контура\кривой гладкими? \en Whether the joints of a contour\curve are smooth. 
  virtual double      Curvature    ( double  ) const; // \ru Кривизна кривой \en Curvature of the curve 
                      
  virtual double      Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double      MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  virtual void        CalculatePolygon( const MbStepData & stepData, MbPolygon3D &polygon ) const; // \ru pассчитать полигон \en Calculate a polygon 
  virtual void        CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой \en Calculate the bounding box of a curve 
  virtual void        GetCentre( MbCartPoint3D & ) const; // \ru Посчитать центр кривой \en Calculate the center of a curve 
  virtual void        GetWeightCentre( MbCartPoint3D & ) const; // \ru Посчитать центр тяжести кривой \en Calculate the gravity center of the curve 

  virtual void        GetPointsByEvenLengthDelta( size_t n, std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curve equally spaced by the arc length 

  // \ru Ближайшая проекция точки на кривую \en The nearest projection of a point onto the curve 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const;
  // \ru Определение точек касания изоклины \en Determination of tangent points of isocline 
  virtual void        GetIsoclinal( const MbVector3D & nor, SArray<double> & tIso ) const;
  /// \ru Найти все особые точки функции кривизны кривой.
  /// \en Find all the special points of the curvature function of the curve.
  virtual void    GetCurvatureSpecialPoints( std::vector<c3d::DoublePair> & points ) const;

  // \ru Прохождение кривой через точку \en Passing of curve through a point 
  //virtual bool        GoThroughPoint( double t, MbCartPoint3D & p0 );
  // \ru Касание кривой через точку с заданной производной \en Tangent of curve through point with the given derivative 
  //virtual bool        GoThroughPointWithDerive( double t, MbCartPoint3D & p0, MbVector3D & v0 );

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of a curve 

  virtual size_t      GetCount()   const;
  virtual void        ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Change a carrier 
  virtual bool        IsPlanar  () const; // \ru Является ли кривая плоской \en Whether the curve is planar 
  virtual bool        IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой \en Get axis of curve 

          void        ParameterInto( double & ) const; // \ru Перевод параметра базовой кривой в локальный параметр \en Transformation of the base curve parameter to a local parameter 
          void        ParameterFrom( double & ) const; // \ru Перевод локального параметра в параметр базовой кривой \en Transformation of a local parameter to the base curve parameter 

          void        SetBasisCurve( MbCurve3D & );      // \ru Заменить плоскую кривую \en Replace the planar curve 
          double      Tmin() const { return tmin; }      // \ru Начальный параметр \en Start parameter 
          double      Tmax() const { return tmax; }      // \ru Конечный  параметр \en End parameter 
          double      Dt()   const { return b;   }      // \ru Производная параметра кривой basisCurve по параметру \en Derivative of parameter of 'basisCurve' curve by parameter 
          void        SetTmin( double t );
          void        SetTmax( double t );
          void        SetDt  ( double d );

  // \ru !!! геометрия подложки тождественна геометрии кривой, отлична параметризация !!! \en !!! geometry of substrate is identical to geometry of curve, parameterization is different !!! 
  virtual const MbCurve3D & GetSubstrate() const; // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual       MbCurve3D & SetSubstrate();       // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual int         SubstrateCurveDirection() const;    // \ru Направление подложки относительно кривой или наоборот \en Direction of substrate relative to the curve or vice versa 
  virtual void        SubstrateToCurve( double & ) const; // \ru Преобразовать параметр подложки в параметр кривой \en Transform a substrate parameter to the curve parameter 
  virtual void        CurveToSubstrate( double & ) const; // \ru Преобразовать параметр кривой в параметр подложки \en Transform a curve parameter to the substrate parameter 
  // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if the curve is planar 
  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Get the planar curve and placement if the spatial curve is planar (call DeleteItem for two-dimensional curve after using) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы) \en Get a surface curve if a spatial curve is on a surface (call DeleteItem for arguments after using ) 
  virtual bool        GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;

  /// \ru Является ли объект смещением \en Whether the object is a shift 
  virtual bool        IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  virtual bool        IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

          bool        IsLinear() const { return (reparamType == rt_Linear); } // \ru Является ли репараметризация линейной? \en Is the re-parametrization linear?

private:
          void        operator = ( const MbReparamCurve3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbReparamCurve3D )
}; // MbReparamCurve3D

IMPL_PERSISTENT_OPS( MbReparamCurve3D )

//------------------------------------------------------------------------------
/// \ru Перевод параметра базовой кривой в новый параметр. \en Transformation of the base curve parameter to a new parameter. 
// ---
inline void MbReparamCurve3D::ParameterInto( double & t ) const {
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
/// \ru Перевод нового параметра в параметр базовой кривой. \en Transformation of a new parameter to the base curve parameter. 
// ---
inline void MbReparamCurve3D::ParameterFrom( double & t ) const {
  if ( reparamType == rt_Linear )
    t = b * t + c;
  else
    t = a * t * t + b * t + c;
}


#endif // __CUR_REPARAM_CURVE3D_H
