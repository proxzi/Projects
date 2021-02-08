////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Проекционная кривая.
         \en Projection curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_PROJECTION_CURVE_H
#define __CUR_PROJECTION_CURVE_H


#include <templ_s_array.h>
#include <tool_multithreading.h>
#include <curve.h>
#include <mb_rect.h>
#include <mb_vector3d.h>
#include <mb_cart_point3d.h>


class  MATH_CLASS  MbAxis3D;
class  MATH_CLASS  MbMatrix3D;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbSurface;
class              MbRegTransform;
class              MbRegDuplicate;
class              MbCurveIntoNurbsInfo;


//------------------------------------------------------------------------------
/** \brief \ru Проекционная кривая.
           \en Projection curve. \~
  \details \ru Проекционная кривая строится в параметрическом пространстве поверхности
    как проекция пространственной кривой spaceCurve на поверхность surface.
    Если поверхность не плоская, то предполагается, что пространственная кривая лежит на поверхности.
    Двумерная кривая curve содержит начальные приближения для точного вычисления проекционной кривой.
           \en Projection curve is constructed in parametric space of surface
    as projection of spatial curve 'spaceCurve' onto surface 'surface'.
    If surface isn't planar, then it is considered that spatial curve lies on surface.
    Two-dimensional curve 'curve' contains initial approximations for precise calculation of the projection curve. \~
*/ 
// ---
class MATH_CLASS MbProjCurve : public MbCurve {
private :
  MbCurve3D *    spaceCurve;   ///< \ru Пространственная кривая (всегда не NULL). \en Spatial curve (always not NULL). 
  MbSurface *    surface;      ///< \ru Поверхность (всегда не NULL). \en Surface (always not NULL). 
  MbCurve *      curve;        ///< \ru Проекция пространственной кривой на поверхность (служит начальным приближением), всегда не NULL. \en Projection of a spatial curve onto a surface (is used as initial approximation), always not NULL. 
  MbMatrix3D *   into;         ///< \ru Матрица пересчета в систему координат плоскости. Для случая плоской поверхности surface. Вычисляется заново при изменении поверхности. \en A matrix of transformation to the plane coordinate system. In case of planar surface 'surface'. Recalculated at surface change. 
  bool           belong;       ///< \ru Проецируемая кривая лежит на поверхности. \en Projecting curve lies on the surface. 

  mutable MbRect rect;         ///< \ru Габарит проекционной кривой в параметрическом пространстве поверхности. \en Bounding box of projection curve in parametric space of surface. 
  mutable double metricLength; ///< \ru Метрическая длина проекционной кривой. \en Metric length of the projection curve. 
  mutable double tMiddle;      ///< \ru Параметр на кривой, соответствующий метрической середине кривой. \en Parameter on the curve corresponding to the metric middle of the curve. 

  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbProjCurveAuxiliaryData : public AuxiliaryData {
  public:
    double      t0;   ///< \ru Исходный параметр. \en Initial parameter.
    double      t;    ///< \ru Модифицированный параметр. \en Modified parameter.
    bool        ext;  ///< \ru Флаг расчета на продолжении. \en Extension flag.

    MbVector    pcDers[cdt_CountDer]; ///< \ru Точка и производные двумерной кривой. \en Curve point and derivatives.
    MbVector3D  scDers[cdt_CountDer]; ///< \ru Точка и производные трехмерной кривой. \en Space curve point and derivatives.

    MbProjCurveAuxiliaryData();
    MbProjCurveAuxiliaryData( const MbProjCurveAuxiliaryData & );
    virtual ~MbProjCurveAuxiliaryData();

    bool IsChanged( double pmin, double pmax, double p, bool pext ) const
    {
      bool changed = false;
      if ( p != t0 )
        changed = true;
      else if ( ext != pext ) {
        changed = true;
        if ( pmin <= p && p <= pmax )
          changed = false;
      }
      return changed;
    }
    void Init();
    void Init( const MbProjCurveAuxiliaryData & );
    void Move( const MbVector & );
  };
  
  mutable CacheManager<MbProjCurveAuxiliaryData> cache;
  
public :
  /** \brief \ru Конструктор по пространственной кривой, поверхности и двумерной кривой.
             \en Constructor by spatial curve, surface and two-dimensional curve. \~
    \details \ru Конструктор по пространственной кривой, поверхности и двумерной кривой. \n
    Двумерная кривая используется как начальное приближение для расчета проекционной кривой. \n
    В конструкторе используется копия подложки поверхности. \n
             \en Constructor by spatial curve, surface and two-dimensional curve. \n
    Two-dimensional curve is used as initial approximation for calculation of projection curve. \n
    Copy of surface substrate is used in the constructor. \n \~
    \param[in] sCurve - \ru Проецируемая пространственная кривая.
                        \en A projected spatial curve. \~
    \param[in] sameSpaceCurve - \ru Использовать ли оригинал пространственной кривой.
                                \en Use the original of the spatial curve. \~
    \param[in] surface - \ru Поверхность для проецирования пространственной кривой.
                         \en A target surface. \~
    \param[in] pCurve - \ru Параметрическая кривая - начальное приближение для проецирования пространственной кривой.
                        \en A parametric curve - initial approximation for projecting of a spatial curve. \~
    \param[in] samePlaneCurve - \ru Использовать ли оригинал параметрической кривой.
                                \en Use the original of the parametric curve. \~
    \param[in] iReg - \ru Регистратор дублирования.
                      \en Registrar of duplication. \~
  */ 
  MbProjCurve( const MbCurve3D & sCurve, bool sameSpaceCurve,
               const MbSurface & surface, 
               const MbCurve & pCurve, bool samePlaneCurve,
               MbRegDuplicate * iReg = NULL );  

private:
  MbProjCurve( const MbProjCurve &, MbRegDuplicate * ireg );

public :
  virtual ~MbProjCurve();

public :
  VISITING_CLASS( MbProjCurve );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbePlaneType  IsA() const;                   // \ru Тип элемента \en Type of element 
  virtual bool        IsSimilar  ( const MbPlaneItem & ) const;     // \ru Являются ли элементы подобными \en Whether the elements are similar 
  virtual bool        SetEqual ( const MbPlaneItem & );       // \ru Сделать элементы равными \en Make the elements equal 
  virtual bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether curve 'curve' is a duplicate of the current curve. 
  virtual void        Transform( const MbMatrix &, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * ireg = NULL );    // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D & to, MbRegTransform * = NULL );    // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D & axis, double angle, MbRegTransform * = NULL );  // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual void        Move ( const MbVector &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const;  // \ru Сделать копию элемента \en Create a copy of the element 

  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void        AddYourGabaritTo ( MbRect & ) const; // \ru Добавь в прям-к свой габарит \en Add your own bounding rectangle into the given rectangle 
  virtual void        CalculateGabarit ( MbRect & ) const; // \ru Определить габариты кривой. \en Determine bounding box of curve. 
  virtual void        CalculateLocalGabarit( const MbMatrix &, MbRect & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system 
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for description of a curve domain.
      \{ */
  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double      GetTMin () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of the parameter 
  virtual bool        IsClosed() const; // \ru Замкнутость кривой \en A curve closedness 
  virtual double      GetPeriod() const; // \ru Вернуть период \en Get period  

  /** \} */
  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the curve's domain. 
            Functions PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            if it is out of domain bounds.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & p ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector    & v ) const; // \ru Первая производная \en The first derivative 
  virtual void        SecondDer( double & t, MbVector    & v ) const; // \ru Вторая производная \en The second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & v ) const; // \ru Третья производная \en The third derivative 
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
  virtual void       _PointOn  ( double t, MbCartPoint & p ) const;   // \ru Точка на кривой \en Point on the curve 
  virtual void       _FirstDer ( double t, MbVector & v ) const;      // \ru Первая производная \en The first derivative 
  virtual void       _SecondDer( double t, MbVector & v ) const;      // \ru Вторая производная \en The second derivative 
  virtual void       _ThirdDer ( double t, MbVector & v ) const;      // \ru Третья производная \en The third derivative 
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;
  /** \} */

  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */
  virtual double      PointProjection( const MbCartPoint & pnt ) const; // \ru Проекция точки на кривую. \en Point projection on the curve. 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции. \en Projection of a point onto the curve or its extension in the projection region. 

  virtual bool        HasLength( double & ) const; // \ru Метрическая длина кривой. \en Metric length of a curve. 
  virtual double      GetMetricLength()     const; // \ru Метрическая длина кривой. \en Metric length of a curve. 
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой. \en Estimation of metric length of the curve. 
  // \ru Вычислить метрическую длину кривой от параметра t1 до t2. \en Calculate the metric length of unclosed curve from parameter t1 to parameter t2. 
  virtual double      CalculateLength( double t1, double t2 ) const; 

  virtual bool        GetMiddlePoint( MbCartPoint & ) const; // \ru Вычислить среднюю точку кривой. \en Calculate mid-point of curve. 

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменение направления кривой на противоположное \en Change curve direction to the opposite one 

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

  // \ru Удалить часть кривой между параметрами t1 и t2 \en Delete a part of a curve between parameters t1 and t2 
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 );
  // \ru Оставить часть кривой между параметрами t1 и t2 \en Keep a piece of a curve between parameters t1 and t2  
  virtual MbeState    TrimmPart( double t1, double t2, MbCurve *& part2 );

  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации с учетом угла отклонения \en Calculation of step of approximation with consideration of angle of deviation 
  
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;

    const MbCurve3D & GetSpaceCurve() const { return *spaceCurve; }
    const MbSurface & GetSurface   () const { return *surface;    }
    const MbCurve &   GetParamCurve() const { return *curve;      }

          bool        SetSameSurface( const MbSurface & s ); ///< \ru Заменить поверхность на такую же. \en Whether the projecting curve lies on the surface. 

          bool        IsBelong() const { return belong; } ///< \ru Лежит ли проецируемая кривая на поверхности. \en Whether the projecting curve lies on the surface. 

          bool        InvertNormal( MbRegTransform * = NULL ); ///< \ru Инвертировать нормаль, если поверхность - плоскость. \en Invert normal if the surface is a plane. 

          bool        ChangeCarrierBorne( const MbSurface & item, MbSurface & init, const MbMatrix & matr ); ///< \ru Изменение носителя. \en Change a carrier.  

          /// \ru Получить 2d сплайн с данной относительной точностью аппроксимирующий данную кривую. \en Get 2d spline which approximates given curve with a given relative tolerance. 
          MbCurve *   CreateSpline( double relEps, MbRect1D * pRgn = NULL ) const;

          /// \ru Создать кривую путём сращивания части данной кривой с частью другой кривой. \en Create a curve by joining a part of this curve with a part of other curve.
          MbProjCurve * AddCurve( const MbProjCurve &, double accuracy, VERSION version = Math::DefaultMathVersion() ) const;

  virtual void        GetProperties( MbProperties & );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива). \en Whether the curves for union (joining) are similar. 
  /** \} */

private:
          void        CheckPoint ( double & t, bool ext, MbCartPoint & cPoint ) const; // \ru Обнулить данные, вычислить точку \en Set data to zero, calculate point. 
          void        CheckFirst ( double & t, bool ext, MbVector & cFirst  ) const; // \ru Вычислить производную \en Calculate derivative 
          void        CheckSecond( double & t, bool ext, MbVector & cSecond ) const; // \ru Вычислить производную \en Calculate derivative 
          void        CheckThird ( double & t, bool ext, MbVector & cThird  ) const; // \ru Вычислить производную \en Calculate derivative 
          bool        CalculatePoint( const MbCartPoint3D & sPoint, MbCartPoint & cPoint,
                                      MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer, 
                                      MbVector3D & uuDer, MbVector3D & vvDer, MbVector3D & uvDer, MbVector3D * nor ) const; // \ru Вычислить данные для точки. \en Calculate point.
          void        CalculateFirst( bool result, MbCartPoint3D & surfacePoint, MbVector3D & sDeriveU, MbVector3D & sDeriveV, 
                                      MbVector3D & sDeriveUU, MbVector3D & sDeriveVV, MbVector3D & sDeriveUV,  MbVector3D & sNormal,
                                      const MbCartPoint3D & sPoint, const MbCartPoint & cPoint, const MbVector3D & sFirst, MbVector & cFirst ) const; // \ru Вычислить производную \en Calculate derivative 
          void        CalculateSecond( const MbCartPoint3D & surfacePoint, const MbVector3D & sDeriveU, const MbVector3D & sDeriveV, 
                                       const MbVector3D & sDeriveUU, const MbVector3D & sDeriveVV, const MbVector3D & sDeriveUV, const MbVector3D & sNormal, 
                                       const MbCartPoint3D & sPoint, const MbCartPoint & cPoint, const MbVector3D & sFirst, const MbVector & cFirst, 
                                       const MbVector3D & sSecond, MbVector & cSecond ) const; // \ru Вычислить производную \en Calculate derivative 
          void        SetBelong(); // \ru Вычисление параметра belong: лежит ли проецируемая кривая на поверхности \en Calculate 'belong' parameter: whether the projecting curve lies on the surface 
          void        SetInto(); // \ru Инициализировать матрицу пересчета в систему координат плоскости. \en Initialize matrix of transformation to the plane coordinate system.  
          void        PrepareCurveToTrimmed( MbCurve * curvett, double t1, double t2 ) const; // \ru Подготовить двумерную кривую к усечению \en Prepare a two-dimensional curve for trimming 
          
          /** \brief \ru Поменять базовую поверхность на подобную.
                     \en Change base surface to the similar one. \~
            \details \ru Поменять базовую поверхность. Новая поверхность должна быть подобна старой.
                     \en Change the base surface. The new surface has to be similar to the old one. \~
            \param[in] newSurface - \ru Новая поверхность. Захватывается кривой.
                                    \en New surface. Is captured by the curve. \~
            \param[in] matrix     - \ru Матрица преобразования из старой поверхности в новую.
                                    \en Transformation matrix from the old surface to a new one. \~                                           
          */
          void        ChangeSurfaceToSimilar( const MbSurface & newSurface, const MbMatrix & matrix, MbRegTransform * iReg );


  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbProjCurve )
  OBVIOUS_PRIVATE_COPY( MbProjCurve )
};

IMPL_PERSISTENT_OPS( MbProjCurve )

//------------------------------------------------------------------------------
// \ru Изменение носимых элементов \en Change a carrier elements 
// ---
bool ChangeCarrierBorne( const MbSurface & item, MbSurface & init, const MbMatrix & matr, MbCurve & curve );


//------------------------------------------------------------------------------
// \ru Пространственная трансформация проекционных кривых в двумерной кривой \en Spatial transformation of projection curves in two-dimensional curve 
// ---
bool TransformProjCurves( MbCurve & curve, const MbMatrix3D & matr, MbRegTransform * ireg );


//------------------------------------------------------------------------------
// \ru Пространственный сдвиг проекционных кривых в двумерной кривой \en Spatial translation of projection curves in two-dimensional curve 
// ---
bool MoveProjCurves( MbCurve & curve, const MbVector3D & to, MbRegTransform * ireg );


//------------------------------------------------------------------------------
// \ru Вращение проекционных кривых в двумерной кривой \en Rotation of projection curves in two-dimensional curve 
// ---
bool RotateProjCurves( MbCurve & curve, const MbAxis3D & axis3d, double angle, MbRegTransform * ireg );


#endif // __CUR_PROJECTION_CURVE_H
