////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Усеченная кривая в двумерном пространстве.
         \en Trimmed curve in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_TRMMED_CURVE_H
#define __CUR_TRMMED_CURVE_H


#include <curve.h>
#include <mb_rect.h>


class             MbRegDuplicate;
class             MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Усеченная кривая в двумерном пространстве.
           \en Trimmed curve in two-dimensional space. \~
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
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbTrimmedCurve : public MbCurve {
// \ru Усечение может быть на продолжении кривой (внесенные изменения помечены как E13865) \en Trimming can be on curve extension (made changes are marked as E13865) 
protected :
  MbCurve * basisCurve; ///< \ru Базовая кривая (не может быть NULL). \en Base curve (can't be NULL). 
  double    trim1;      ///< \ru Параметры начальной точки \en Parameters of start point 
  double    trim2;      ///< \ru Параметры конечной  точки \en Parameters of end point 
  int       sense;      ///< \ru Флаг совпадения направления с направлением базовой кривой (sense==0 не допускается) \en Flag of coincidence of the direction with the direction of the base curve (sense==0 isn't allowed) 
                        ///< \ru Если (sense > 0), то (trim2 > trim1) \en If (sense > 0), then (trim2 > trim1) 
                        ///< \ru Если (sense < 0), то (trim2 < trim1) \en If (sense < 0), then (trim2 < trim1) 
                        ///< \ru Равенство trim1 и trim2 не допускается \en Equality of 'trim1' and 'trim2' isn't allowed 

  mutable MbRect rect;         ///< \ru Габаритный прямоугольник \en Bounding rectangle 
  mutable double metricLength; ///< \ru Метрическая длина усеченной кривой \en Metric length of a trimmed curve 

protected :
  MbTrimmedCurve( const MbTrimmedCurve & initCurve );
  MbTrimmedCurve( MbTrimmedCurve * initCurve ); // \ru Сохранение той же базовой кривой \en Preservation of the same base curve 
public :
  MbTrimmedCurve( const MbCurve & initCurve, double t1, double t2, int initSense, 
                  bool same, double eps = Math::paramEpsilon );
  // \ru Для периодической базовой кривой прии t1==t2 получим периодическую кривую со смещённым началом. \en For a periodic base curve if 't1' is equal to 't2', then obtain periodic curve with shifted beginning. 
public :
  virtual ~MbTrimmedCurve();

public :
  VISITING_CLASS( MbTrimmedCurve ); 

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbePlaneType  IsA() const;  // \ru Тип элемента \en Type of element 
  virtual MbePlaneType  Type() const; // \ru Вернуть тип кривой \en Get type of curve 
  virtual bool        IsSimilar( const MbPlaneItem & ) const; // \ru Являются ли элементы подобными \en Whether the elements are similar 
  virtual bool        SetEqual ( const MbPlaneItem & );       // \ru Сделать элементы равными \en Make the elements equal 
  virtual	bool        IsSame   ( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether curve 'curve' is a duplicate of the current curve. 
  virtual void        Transform( const MbMatrix &, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual void        AddYourGabaritTo( MbRect & ) const; // \ru Добавь свой габарит в прямой прям-к \en Add your own gabarit into the given bounding rectangle 
  virtual bool        IsInRectForDeform( const MbRect & r ) const; // \ru Виден ли объект в заданном прямоугольнике для деформации \en Whether the object is visible in the given rectangle for deformation 
  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for description of a curve domain.
      \{ */
  virtual double      GetTMin()      const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax()      const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool        IsClosed()     const;  // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double      GetPeriod()    const; // \ru Вернуть период \en Get period  
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const; // \ru Проверка вырожденности кривой \en Check for curve degeneracy 
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in a curve domain. 
            Functions PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            if it is out of domain bounds.
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
      \en \name Functions for working inside and outside the curve's domain. 
            Functions _PointOn, _FirstDer, _SecondDer, _ThirdDer,... don't correct parameter
            if it is out of domain bounds. If the parameter is out of domain bounds, an unclosed
            curve is extended by tangent vector at corresponding end point in general case.
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
  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculation of step of approximation 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации с учетом угла отклонения \en Calculation of step of approximation with consideration of angle of deviation 

  /** \} */
  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */

  virtual double      Curvature( double t ) const; // \ru Кривизна усеченной кривой \en Curvature of a trimmed curve 
  virtual bool        HasLength( double & length ) const;
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Estimation of metric length of the curve  
  virtual double      GetMetricLength() const; // \ru Метрическая длина \en The metric length 

  virtual bool        GetMiddlePoint( MbCartPoint & ) const; // \ru Вычислить среднюю точку кривой. \en Calculate mid-point of curve. 

  virtual double      PointProjection( const MbCartPoint & pnt ) const; // \ru Проекция точки на кривую \en Point projection on the curve 

  virtual bool        IsStraight() const;  // \ru Признак прямолинейности кривой \en An attribute of curve straightness. 
  // \ru Положение точки относительно кривой. \en The point position relative to the curve. 
  // \ru Возвращает результат : \en Returning result: 
  // \ru iloc_InItem = 1 - точка находится слева от кривой, \en Iloc_InItem = 1 - point is to the left of the curve, 
  // \ru iloc_OnItem = 0 - точка находится на кривой, \en Iloc_OnItem = 0 - point is on the curve, 
  // \ru iloc_OutOfItem = -1 - точка находится справа от кривой. \en Iloc_OutOfItem = -1 - point is to the right of the curve. 
  virtual MbeItemLocation PointRelative( const MbCartPoint & pnt, double eps = Math::LengthEps ) const;
  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;


  virtual const MbCurve & GetBasisCurve() const; // \ru Вернуть базовую кривую \en Get the base curve 
  virtual       MbCurve & SetBasisCurve();       // \ru Вернуть базовую кривую \en Get the base curve 

  virtual void        Isoclinal( const MbVector & angle, SArray<double> & tFind ) const; // \ru Прямые, проходящие под углом к оси 0X и касательные к кривой \en Lines passing angularly to the 0X axis and tangent to the curve 
  // \ru Выдать характерную точку усеченной кривой если она ближе чем dmax \en Get control point of trimmed curve if it is closer than 'dmax' 
  virtual bool        GetSpecificPoint( const MbCartPoint & from, double & dmax, MbCartPoint & pnt ) const;
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 ); // \ru Удалить часть усеченной кривой между параметрами t1 и t2 \en Delete a part of a trimmed curve between parameters t1 and t2 
  virtual MbeState    TrimmPart ( double t1, double t2, MbCurve *& part2 ); // \ru Оставить часть усеченной кривой между параметрами t1 и t2 \en Keep a part of the trimmed curve between parameters t1 and t2 
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;
  virtual MbCurve *   Offset( double rad ) const;	  // \ru Смещение усеченной кривой \en Shift of a trimmed curve 

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 

          void        ParameterInto( double & t ) const; // \ru Перевод параметра базовой кривой в локальный параметр \en Transformation of the base curve parameter to a local parameter 
          void        ParameterFrom( double & t ) const; // \ru Перевод локального параметра в параметр базовой кривой \en Transformation of a local parameter to the base curve parameter 
          double      GetBasisParameter( double & t ) const; // \ru Установить параметр в область допустимых значений \en Set the parameter into the region of the legal values 
          bool        IsBaseParamOn( double t, double eps = Math::paramEpsilon ) const; // \ru Находится ли параметр базовой кривой в диапазоне усеченной кривой \en Whether the parameter of base curve is in range of a trimmed curve 

          double      GetTrim1() const { return trim1; }
          double      GetTrim2() const { return trim2; }
          int         GetSense() const { return trim2 > trim1 ? 1 : -1; } // \ru Флаг совпадения направления с направлением базовой кривой \en Flag of coincidence of the direction with the direction of base curve 
          void        SetTrim1( double t ) { trim1 = t; InitParam( trim1, trim2, sense ); }
          void        SetTrim2( double t ) { trim2 = t; InitParam( trim1, trim2, sense ); }

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление кривой \en Change direction of a curve 
  virtual bool        GetAxisPoint( MbCartPoint & p ) const; // \ru Точка для построения оси \en Point for the axis construction  
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        GetCentre     ( MbCartPoint & ) const; ///< \ru Вычислить центр кривой. \en Calculate center of curve. 
  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях \en Count of subdivisions for pass in operations  

  // \ru Геометрия подложки тождественна геометрии кривой, отлична параметризация \en Geometry of substrate is identical to geometry of curve, parameterization is different  
  virtual const MbCurve & GetSubstrate() const; // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual       MbCurve & SetSubstrate();       // \ru Выдать подложку или себя \en Get substrate or itself 
  virtual int         SubstrateCurveDirection() const;    // \ru Направление подложки относительно кривой или наоборот \en Direction of substrate relative to the curve or vice versa 
  virtual void        SubstrateToCurve( double & ) const; // \ru Преобразовать параметр подложки в параметр кривой \en Transform a substrate parameter to the curve parameter 
  virtual void        CurveToSubstrate( double & ) const; // \ru Преобразовать параметр кривой в параметр подложки \en Transform a curve parameter to the substrate parameter 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

          void        SetBasisCurve( MbCurve & newCurve );
          void        InitParam( double t1, double t2, int s, double eps = Math::paramEpsilon );
          void        Init( double t1, double t2, int initSense ) {
                        InitParam( t1, t2, initSense );
                        Refresh();
                      }
  const   MbTrimmedCurve & operator = ( const MbTrimmedCurve & source ); // \ru Присвоение параметров усеченной кривой \en Assignment of parameters of trimmed curve 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbTrimmedCurve )
  /** \} */
};

IMPL_PERSISTENT_OPS( MbTrimmedCurve )

//------------------------------------------------------------------------------
// \ru Находится ли параметр базовой кривой в диапазоне \en Whether the parameter of the base curve is in the range 
// \ru Усеченной кривой \en Of the trimmed curve 
// ---
inline bool MbTrimmedCurve::IsBaseParamOn( double t, double eps ) const {
  ParameterInto( t );
  return IsParamOn( t, eps );
}


#endif // __CUR_TRMMED_CURVE_H
