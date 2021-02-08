////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Усеченная кривая в трехмерном пространстве.
         \en Trimmed curve in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_TRMMED_CURVE3D_H
#define __CUR_TRMMED_CURVE3D_H


#include <curve3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Усеченная кривая в трехмерном пространстве.
           \en Trimmed curve in three-dimensional space. \~
  \details \ru Усеченная кривая описывает участок базовой кривой basisCurve, 
    который начинается в точке с параметром trim1 и оканчивается в точке с параметром trim2. \n
    Описываемый участок может иметь направление, совпадающее с направлением базовой кривой (sense == +1),
    а также может иметь направление, противоположное направлению базовой кривой (sense == -1).
    Для замкнутых периодических кривых описываемый участок может содержать внутри начальную точку базовой кривой. 
    Базовой кривой для усеченной кривой не может служить другая усеченная кривая.
    В подобной ситуации выполняется переход к первичной базовой кривой.
           \en Trimmed curve describes a piece of base curve 'basisCurve' 
    which starts at point with 'trim1' parameter and ends at point with 'trim2' parameter. \n
    Described piece can have the direction coinciding with the direction of a base curve (sense == +1),
    and also can have the direction opposite to the direction of a base curve (sense == -1).
    For closed periodic curves the described piece can contain the start point of base curve inside. 
    Another trimmed curve can't be the base curve for a trimmed curve.
    In this situation it changes to the initial base curve. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbTrimmedCurve3D : public MbCurve3D {
private :
  MbCurve3D *     basisCurve;   ///< \ru Базовая кривая. \en The base curve. 
  double          trim1;        ///< \ru Параметр начальной точки базовой кривой. \en Parameter of the start point of the base curve. 
  double          trim2;        ///< \ru Параметр конечной  точки базовой кривой. \en Parameter of the end point of base curve. 
  int             sense;        ///< \ru Флаг совпадения направления с направлением базовой кривой. \en Flag of coincidence of the direction with the direction of base curve. 
private:
  mutable double  metricLength; ///< \ru Метрическая длина кривой. \en Metric length of a curve. 

public :
  MbTrimmedCurve3D( const MbCurve3D & initCurve, double t1, double t2, int initSense, bool same );
  MbTrimmedCurve3D( const MbCurve3D & initCurve, const MbCartPoint3D & p0, const MbCartPoint3D & p1 );
protected :
  MbTrimmedCurve3D( const MbTrimmedCurve3D &, MbRegDuplicate * );
private :
  MbTrimmedCurve3D( const MbTrimmedCurve3D & ); // \ru Не реализовано. \en Not implemented. 
public :
  virtual ~MbTrimmedCurve3D();

public : 
  VISITING_CLASS( MbTrimmedCurve3D );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 
  
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией \en Whether the object is a copy 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );    // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );    // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual void    Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void    PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMin()  const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax()  const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double  GetPeriod() const; // \ru Вернуть период \en Get period  
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void    PointOn  ( double &t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double &t, MbVector3D & ) const;     // \ru Первая производная \en The first derivative 
  virtual void    SecondDer( double &t, MbVector3D & ) const;     // \ru Вторая производная \en The second derivative 
  virtual void    ThirdDer ( double &t, MbVector3D & ) const;     // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void    Normal   ( double &t, MbVector3D & ) const;   // \ru Вектор главной нормали \en Vector of the principal normal 
  // \ru Функции кривой для работы вне области определения параметрической кривой \en Functions of curve for working outside the domain of parametric curve 
  virtual void   _PointOn  ( double t,  MbCartPoint3D & ) const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void   _FirstDer ( double t,  MbVector3D & ) const;    // \ru Первая производная \en The first derivative 
  virtual void   _SecondDer( double t,  MbVector3D & ) const;    // \ru Вторая производная \en The second derivative 
  virtual void   _ThirdDer ( double t,  MbVector3D & ) const;    // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void   _Normal   ( double t,  MbVector3D & ) const;   // \ru Вектор главной нормали \en Vector of the principal normal 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 

  virtual const MbCurve3D & GetBasisCurve() const;
  virtual       MbCurve3D & SetBasisCurve();
  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Create a trimmed curve 

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Curvature    ( double  )                const; // \ru Кривизна усеченной кривой \en Curvature of a trimmed curve 
  virtual double  Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double  DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double  MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  virtual bool    IsDegenerate( double eps = METRIC_PRECISION ) const; // \ru Проверка вырожденности кривой \en Check for curve degeneracy 
  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of a curve 
  virtual size_t  GetCount() const;
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Change a carrier 
  virtual bool    IsPlanar  () const; // \ru Является ли кривая плоской \en Whether the curve is planar 
  virtual bool    IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool    GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой \en Get axis of curve 
  virtual void    GetCentre( MbCartPoint3D &wc ) const; // \ru Посчитать центр кривой \en Calculate the center of a curve 

  virtual double  GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Estimation of metric length of the curve  
  virtual double  GetMetricLength() const; // \ru Метрическая длина \en Metric length 

          void    SetBasisCurve( MbCurve3D & );      // \ru Заменить плоскую кривую \en Replace the planar curve 
          void    InitParam( double t1, double t2, int initSense );
          double  GetTrim1() const { return trim1; }
          double  GetTrim2() const { return trim2; }
          int     GetSense() const { return sense; } // \ru Флаг совпадения направления с направлением базовой кривой \en Flag of coincidence of the direction with the direction of base curve 

          void    ParameterInto( double &t ) const; // \ru Перевод параметра базовой кривой в параметр усеченной кривой \en Transformation of parameter of base curve to a parameter of trimmed curve 
          void    ParameterFrom( double &t ) const; // \ru Перевод локального параметра в параметр базовой кривой \en Transformation of a local parameter to the base curve parameter 
          double  GetBasisParameter( double &t ) const; // \ru Установить параметр в область допустимых значений \en Set the parameter into the region of the legal values 

          bool    IsBaseParamOn( double t ) const; // \ru Находится ли параметр базовой кривой в диапазоне усеченной кривой \en Whether the parameter of base curve is in range of a trimmed curve 

  // \ru Ближайшая проекция точки на кривую. \en The nearest projection of a point onto the curve. 
  virtual bool    NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Ближайшая проекция точки на кривую \en The nearest projection of a point onto the curve 
  /// \ru Найти все особые точки функции кривизны кривой. 
  /// \en Find all the special points of the curvature function of the curve.
  virtual void    GetCurvatureSpecialPoints( std::vector<c3d::DoublePair> & points ) const;

  // \ru Геометрия базовой кривой тождественна геометрии кривой, отлична параметризация. \en Geometry of base curve is identical to geometry of curve, parameterization is different. 
  virtual const MbCurve3D & GetSubstrate() const; // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual       MbCurve3D & SetSubstrate();       // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual int     SubstrateCurveDirection() const;    // \ru Направление подложки относительно кривой или наоборот \en Direction of substrate relative to the curve or vice versa 
  virtual void    SubstrateToCurve( double & ) const; // \ru Преобразовать параметр подложки в параметр кривой \en Transform a substrate parameter to the curve parameter 
  virtual void    CurveToSubstrate( double & ) const; // \ru Преобразовать параметр кривой в параметр подложки \en Transform a curve parameter to the substrate parameter 

  // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if the curve is planar 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Get the planar curve and placement if the spatial curve is planar (call DeleteItem for two-dimensional curve after using) 
  virtual bool    GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы) \en Get a surface curve if a spatial curve is on a surface (call DeleteItem for arguments after using ) 
  virtual bool    GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;

  /// \ru Является ли объект смещением \en Whether the object is a shift 
  virtual bool    IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 

private:
          void    operator = ( const MbTrimmedCurve3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbTrimmedCurve3D )
};

IMPL_PERSISTENT_OPS( MbTrimmedCurve3D )

//------------------------------------------------------------------------------
// \ru Находится ли параметр базовой кривой в диапазоне усеченной кривой \en Whether the parameter of base curve is in range of a trimmed curve 
// ---
inline bool MbTrimmedCurve3D::IsBaseParamOn( double t ) const {
  ParameterInto( t );
  return IsParamOn( t, PARAM_REGION );
}


#endif // __CUR_TRMMED_CURVE3D_H
