////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кривая на поверхности.
         \en Curve on surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_SURFACE_CURVE_H
#define __CUR_SURFACE_CURVE_H


#include <templ_three_states.h>
#include <curve3d.h>
#include <mb_cube.h>
#include <plane_item.h>
#include <tool_multithreading.h>


class  MATH_CLASS MbRect;
class  MATH_CLASS MbPlacement3D;
class  MATH_CLASS MbCurve;
class  MATH_CLASS MbSurface;
class  MATH_CLASS MbSurfaceIntersectionCurve;
class             MbCurveIntoNurbsInfo;


//------------------------------------------------------------------------------
/** \brief \ru Кривая на поверхности.
           \en Curve on surface. \~
  \details \ru Кривая на поверхности строится путём введения зависимости параметров поверхности u и v 
    от некоторого общего для них параметра t: u=u(t), v=v(t). \n 
    Параметры поверхности u и v являются координатами двумерной точки в пространстве параметров поверхности. 
	  Кривая на поверхности описывается поверхностью surface и двумерной кривой в пространстве параметров curve. 
    Поверхностью surface может быть любая поверхность, кроме MbCurveBoundedSurface. \n 
    Для заданного параметра t кривой curve вычисляется двумерная точка w=[u v] области параметров поверхности, 
    далее для параметров u и v поверхностью surface вычисляется точка кривой на поверхности. 
    Параметры u и v поверхности могут выходить за пределы её области определения. \n 
    Кривая на поверхности может быть периодической, 
    если периодической является двумерная кривая curve или 
    если кривая curve имеет совпадающие производные на краях и крайние точки кривой 
    смещены на соответствующий период периодической по первому или второму параметру поверхности surface.
           \en Curve on surface is constructed by introduction of dependence of u and v surface parameters 
    from some parameter t common for them: u=u(t), v=v(t). \n 
    u and v surface parameters are coordinates of two-dimensional point in space of surface parameters. 
	  Curve on surface is described by 'surface' surface and two-dimensional curve 'curve' in space of parameters. 
    Any surface except MbCurveBoundedSurface can be surface 'surface'. \n 
    two-dimensional point w=[u v] of region of surface parameters is calculated for a given parameter t of curve 'curve', 
    further, a point of curve on surface is calculated for u and v parameters of 'surface' surface. 
    u and v surface parameters can exceed the bounds of its domain. \n 
    Curve on surface can be periodic, 
    if two-dimensional curve 'curve' is periodic or 
    if curve 'curve' has coinciding derivatives at the end points and the curve end points 
    is shifted by corresponding period of 'surface' surface which is periodic by first or second parameter. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbSurfaceCurve : public MbCurve3D {
protected :
  MbCurve           * curve;    ///< \ru Плоская кривая в uv-пространстве (всегда не NULL). \en Planar curve in uv-space (always not NULL). 
  MbSurface         * surface;  ///< \ru Указатель на поверхность         (всегда не NULL). \en Pointer to the surface (always not NULL). 
  bool                closed;   ///< \ru Флаг замкнутости поверхностной кривой. \en An attribute of closedness of surface of curve. 

  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
      \details \ru Вспомогательные данные служат для ускорения работы объекта.
               \en Auxiliary data are used for fast calculations. \n \~
  */
  mutable MbCube      cube;             ///< \ru Габаритный куб. \en Bounding box. 
  mutable double      metricLength;     ///< \ru Метрическая длина кривой. \en Metric length of a curve. \~
  mutable double      lengthEvaluation; ///< \ru Оценочная длина кривой. \en Estimated length of a curve. 
  mutable double      curveRadius;      ///< \ru Радиус кривой, если она является дугой окружности в пространстве. \en The radius of the curve, if the curve is a spatial arc. 
  mutable ThreeStates isStraight;       ///< \ru Флаг прямолинейности. \en A straightness flag. 

  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbSurfaceCurveAuxiliaryData : public AuxiliaryData {
  public:
    double        t;    ///< \ru Модифицированный параметр. \en Modified parameter.

    MbVector      pDers[cdt_CountDer]; ///< \ru Точка и производные двумерной кривой. \en Curve point and derivatives.
    MbVector3D    sDers[sdt_CountDer]; ///< \ru Точка и производные поверхности. \en Surface point and derivatives.
    MbVector3D    sNorm;               ///< \ru Нормаль поверхности. \en Surface normal.

    MbSurfaceCurveAuxiliaryData();
    MbSurfaceCurveAuxiliaryData( const MbSurfaceCurveAuxiliaryData & );
    virtual ~MbSurfaceCurveAuxiliaryData();

    void Init();
    void Init( const MbSurfaceCurveAuxiliaryData & );
    void Move( const MbVector3D & );
  };
  
  mutable CacheManager<MbSurfaceCurveAuxiliaryData> cache;

public :
  /// \ru Конструктор кривой на поверхности. \en Constructor of curve on surface. 
  MbSurfaceCurve( const MbSurface &, const MbCurve &, bool same, MbRegDuplicate * iReg = NULL ); 
  /// \ru Конструктор отрезка прямой на поверхности. \en Constructor of a line segment on surface. 
  MbSurfaceCurve( const MbSurface &, const MbCartPoint & p0, const MbCartPoint & p1, MbePlaneType type = pt_Curve );
  /// \ru Конструктор граничной кривой поверхности. \en Constructor of boundary curve of surface. 
  MbSurfaceCurve( const MbSurface &, ptrdiff_t pnt1, ptrdiff_t pnt2, MbePlaneType type = pt_Curve );
protected:
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSurfaceCurve( const MbSurfaceCurve &, MbRegDuplicate * );
  /// \ru Конструктор копирования кривой с той же поверхностью для CurvesDuplicate(). \en Copy-constructor of a curve with the same surface for CurvesDuplicate(). 
  explicit MbSurfaceCurve( const MbSurfaceCurve * );
private:
  MbSurfaceCurve( const MbSurfaceCurve & ); // \ru Не реализовано!!! \en Not implemented!!! 

public :
  virtual ~MbSurfaceCurve();

public:
  /// \ru Реализация функции, инициирующей посещение объекта. \en Implementation of a function initializing a visit of an object. 
  VISITING_CLASS( MbSurfaceCurve );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbeSpaceType IsA() const;  // \ru Дать тип элемента. \en Get element type. 
  virtual MbeSpaceType Type() const; // \ru Дать тип элемента. \en Get element type. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  /// \ru Копия кривой с той же поверхностью. \en Copy of curve with the same surface. 
          MbSurfaceCurve & CurvesDuplicate() const;
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Определить, являются ли объекты одинаковыми. \en Determine whether objects are equal. 
  virtual bool        SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
  virtual bool        IsSimilar( const MbSpaceItem & ) const; // \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 
  virtual void        AddYourGabaritTo( MbCube & r ) const; // \ru Добавить свой габарит в куб. \en Add your own bounding box into a cube. 
  virtual void        Refresh(); // \ru Сбросить все временные данные. \en Reset all temporary data. 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void        GetBasisItems( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты. \en Get the basis objects. 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /** \} */
  /** \ru \name Общие функции кривой.
      \en \name Common functions of curve.
      \{ */

  virtual double      GetTMin() const;   // \ru Вернуть минимальное значение параметра. \en Get the minimum value of parameter. 
  virtual double      GetTMax() const;   // \ru Вернуть максимальное значение параметра. \en Get the maximum value of parameter. 
  virtual bool        IsClosed() const;  // \ru Проверить замкнутость кривой. \en Check for curve closedness. 
  virtual double      GetPeriod() const; // \ru Вернуть период периодической кривой. \en Get period of a periodic curve. 

  // \ru Функции для работы в области определения. \en Functions for working in the definition domain. 
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Вычислить точку на кривой. \en Calculate a point on the curve. 
  virtual void        FirstDer ( double & t, MbVector3D & )    const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void        SecondDer( double & t, MbVector3D & )    const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void        ThirdDer ( double & t, MbVector3D & )    const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Функции для работы вне области определения. \en Functions for working outside of definition domain. 
  virtual void       _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Вычислить точку на расширенной кривой. \en Calculate a point on the extended curve. 
  virtual void       _FirstDer ( double t, MbVector3D & )     const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void       _SecondDer( double t, MbVector3D & )     const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void       _ThirdDer ( double t, MbVector3D & )     const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore  ( double & t, bool ext,
                                 MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  // \ru Установить параметры NURBS. \en Set parameters of NURBS. 
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создать усеченную кривую. \en Create a trimmed curve 

  // \ru Вычислить ближайшую проекцию точки на кривую. \en Calculate the nearest projection of a point onto the curve. 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const;
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление. \en Change the direction. 

  virtual double      Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double      MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL,
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of a curve. 
          /// \ru Вычислить плоскую проекцию кривой в частных случаях. \en Calculate planar projection of a curve in special cases. 
          MbCurve *   GetParticularMap( const MbMatrix3D & into, MbRect1D * pRgn,
                                        VERSION version ) const;

  virtual bool        IsStraight() const; // \ru Определить, является ли линия прямолинейной. \en Determine whether the line is straight. 
  virtual void        ChangeCarrier     ( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменить носитель. \en Change the carrier. 
  virtual bool        ChangeCarrierBorne( const MbSpaceItem &, MbSpaceItem &, const MbMatrix & matr ); // \ru Изменить носимые элементы. \en Change a carrier elements. 
  virtual bool        IsPlanar() const; // \ru Определить, является ли кривая плоской. Прямолинейные кривые являются плоскими, но без определённой ЛСК. \en Determine whether the curve is planar. Straight lines is planar but without certain placement.
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Определить, являются ли стыки контура\кривой гладкими. \en Determine whether the joints of contour\curve are smooth. 
  virtual void        CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой. \en Calculate bounding box of a curve. 
  virtual double      GetMetricLength() const; // \ru Вычислить метрическую длину кривой. \en Calculate the metric length of a curve. 
  virtual double      GetLengthEvaluation() const; // \ru Оценить метрическую длину кривой. \en Estimate the metric length of a curve. 
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой. \en Get the curve axis. 
  virtual void        GetCentre      ( MbCartPoint3D &  c ) const; // \ru Выдать центр кривой. \en Get center of curve. 
  virtual void        GetWeightCentre( MbCartPoint3D & wc ) const; // \ru Выдать центр тяжести кривой. \en Get center of mass of curve. 

  // \ru Вычислить ближайшую точку кривой к плейсменту. \en Calculate the curve point nearest to a placement. 
  virtual double      DistanceToPlace( const MbPlacement3D & place, double & t0, double & angle ) const;
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую). \en Get the planar curve and placement if the spatial curve is planar (call DeleteItem for two-dimensional curve after using ). 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place3d, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы). \en Get a surface curve if a spatial curve is on a surface (call DeleteItem for arguments after use). 
  virtual bool        GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Заполнить плейсмент, если кривая плоская. \en Fill the placement if the curve is planar. 
  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

  /// \ru Дать тип кривой. \en Get type of curve. 
  virtual MbeCurveBuildType GetBuildType() const;
  /** \brief \ru Вставить точку по параметру.
             \en Insert point by parameter. \~
    \details \ru Вставить точку по желаемому параметру и выдать фактический параметр. \n
             \en Insert point by desirable parameter and get the actual parameter. \n \~ 
    \param[in] t - \ru Параметр на кривой, куда надо вставить точку.
                   \en Parameter on the curve where it is necessary to insert a point. \~
    \return \ru Возвращает true, если произошла вставка точки.
            \en Returns true if a point was inserted. \~
  */
  virtual bool        InsertPoint( double & t );

  /// \ru Определить, является ли объект смещением. \en Determine whether the object is a translation. 
  virtual bool        IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  /// \ru Определить, подобные ли кривые для объединения (слива). \en Determine whether the curves for union (joining) are similar. 
  virtual bool        IsSimilarToCurve( const MbCurve3D & other, double precision = METRIC_PRECISION ) const;
  virtual void        GetPointsByEvenLengthDelta( size_t n, std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги. \en Get n points of a curve with equally spaced by the arc length. 

  // \ru Определить количество разбиений для прохода в операциях. \en Define the number of splittings for one passage in operations. 
  virtual size_t      GetCount() const;

  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

  /** \} */

  /// \ru Определить, является ли кривая curve копией этой кривой. \en Determine whether the 'curve' curve is a duplicate of the current curve. 
          bool        IsSameCurvePoints( const MbSurfaceCurve * scurve, double accuracy, bool sameSense ) const;
  /// \ru Вычислить нормаль к поверхности. \en Calculate surface normal. 
          void        SurfaceNormal( double & t, MbVector3D & ) const;
  /// \ru Получить параметры поверхности по параметру на кривой. \en Get surface parameters by a parameter on the curve. 
          void        SurfaceParams( double & t, double & u, double & v, bool ext = false ) const;
  /// \ru Вычислить параметрический габарит кривой. \en Calculate parametric bounding box of the curve. 
          void        CalculateUVLimits( MbRect & uvRect ) const;
  /// \ru Вычислить U-пары от V. \en Calculate U-pairs from V. 
          void        GetUPairs( double v, SArray<double> & u, SArray<double> & t ) const;
  /// \ru Вычислить V-пары от U. \en Calculate V-pairs from U. 
          void        GetVPairs( double u, SArray<double> & v, SArray<double> & t ) const;

  /// \ru Построить участок пространственной копии кривой. \en Construct a piece of a spatial curve copy. 
          MbCurve3D * MakeCurve( double t1, double t2 ) const;
  /// \ru Построить пространственную копию кривой. \en Construct a spatial curve copy. 
          MbCurve3D * MakeCurve() const;
  /// \ru Построить точную пространственную копию кривой. \en Construct the exact spatial curve copy. 
          MbCurve3D * CreateCurve() const;
  /// \ru Создать пространственную кривую по линии u, v. \en Create a spatial curve by u, v lines. 
          MbCurve3D * CreateUV() const;

  /// \ru Вычислить левый перпендикуляр к кривой в плоскости поверхности. \en Calculate the left perpendicular to a curve at level of surface. 
          void        Transversal( double & t, MbVector3D & f ) const;

  /// \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
          bool        IsCurveEqual ( const MbSpaceItem & ) const;
  /// \ru Сделать равной кривую. \en Make curve equal. 
          bool        SetCurveEqual( const MbSpaceItem & );

  /// \ru Дать кривую. \en Get curve. 
  const   MbCurve &   GetCurve()   const { return *curve; }
  /// \ru Дать поверхность. \en Get surface. 
  const   MbSurface & GetSurface() const { return *surface; }
  /// \ru Дать кривую. \en Get curve. 
          MbCurve &   SetCurve()
          {
            metricLength = -1.0;
            cache.Reset( true );
            return *curve;
          }
  /// \ru Дать поверхность. \en Get surface. 
          MbSurface & SetSurface()
          {
            metricLength = -1.0;
            cache.Reset( true );
            return *surface;
          }

  /// \ru Заменить кривую. \en Replace curve. 
          bool        ChangeCurve  ( const MbCurve & );
  /// \ru Заменить поверхность. \en Replace surface. 
          bool        ChangeSurface( const MbSurface & );
  /// \ru Заменить кривую и поверхность. \en Replace curve and surface. 
          bool        ChangeSurfaceCurve( const MbSurfaceCurve & );
                    
  /// \ru Установить область изменения параметра. \en Set range of parameter.
          bool        SetLimitParam( double newTMin, double newTMax );

  /// \ru Получить текущую точку на кривой по параметру. \en Get current point on a curve by a parameter. 
  virtual bool        GetCurvePoint( double & t, MbCartPoint & cPoint ) const;

protected:
          void        CheckParam ( double & t, bool ext ) const; // \ru Проверить и изменить при необходимости параметр. \en Check and correct parameter. 
          void        CalculatePoint ( double & t, bool ext, MbCartPoint3D & ) const; // \ru Вычислить точку на расширенной кривой. \en Calculate a point on the extended curve. 
          void        CalculateFirst ( double & t, bool ext, MbVector3D & )    const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
          void        CalculateSecond( double & t, bool ext, MbVector3D & )    const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
          void        CalculateThird ( double & t, bool ext, MbVector3D & )    const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  /// \ru Попытаться создать пространственную кривую по проекционной кривой. \en Try to create a spatial curve from a projection curve. 
          MbCurve3D * TryProjection() const;
  /// \ru Вычислить точку двумерной и пространственной кривой. \en Calculate a point on two-dimensional curve and on the curve. 
          void        Explorer( double & t, bool ext, MbCartPoint & cPnt, MbCartPoint3D & pnt ) const; 
          void        Explorer( double & t, bool ext, 
                                MbCartPoint & cPnt, MbVector & cFir, MbVector & cSec, MbVector * cThird,
                                MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer, 
                                MbVector3D & uuDer, MbVector3D & vvDer, MbVector3D & uvDer, MbVector3D & nor ) const; 

  /** \brief \ru Проверить и установить замкнутость кривой.
             \en Check and set the curve closedness. \~
    \details \ru Проверить и установить признак замкнутости кривой. \n 
      Вызывать после самостоятельного изменения двумерной кривой.
             \en Check and set attribute of curve closedness. \n 
      To be called after independent changing of two-dimensional curve. \~
  */
          void        CheckClosed();

  /** \brief \ru Удалить кэши.
             \en Delete caches. \~
    \details \ru Удалить кэши. \n 
             \en Delete caches. \n 
  */
          void        CacheReset();

private:
          // \ru Объявить оператор приравнивания по ссылке, \en Declare operator of assignment by reference 
          // \ru чтобы не был вызван по умолчанию оператор приравнивания по значению \en To prevent default calling of the assignment operator by value 
          void        operator = ( const MbSurfaceCurve & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSurfaceCurve )

  friend class MbSurfaceIntersectionCurve;
};

IMPL_PERSISTENT_OPS( MbSurfaceCurve )

#endif // __CUR_SURFACE_CURVE_H
