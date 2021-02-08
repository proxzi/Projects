////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность, проходящая через заданное семейство кривых.
         \en Lofted surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_LOFTED_SURFACE_H
#define __SURF_LOFTED_SURFACE_H

#include <surface.h>
#include <curve3d.h>
#include <templ_dptr.h>
#include <tool_multithreading.h>


class MbSurfaceContiguousData;

#define LOFT_NUMB   4 ///< \ru Вспомогательный параметр для поверхности MbLoftedSurface. Используется для определения количества элементов в массивах, где хранится точка и первые три производные в этой точке. \en Auxiliary parameter for MbLoftedSurface surface. Used for determination of count of elements in arrays of points and first three derivatives at this point. 
const VERSION LOFTED_SURFACE_VERSION1 = 0x0F000013L; ///< \ru Корректировка коэффициентов уравнения поверхности. \en Correction of surface equation coefficients.
const VERSION LOFTED_SURFACE_VERSION2 = 0x13000015L; ///< \ru Возможность устанавливать нормали на торцевых сечениях в виде точки. \en Ability to set normals on end sections as a point.


//------------------------------------------------------------------------------
/** \brief \ru Поверхность, проходящая через заданное семейство кривых.
           \en Lofted surface passing through given family of curves. \~ 
  \details \ru Поверхность, проходящая через заданное семейство кривых, построена аналогично сплайну Эрмита MbHermit3D, 
    проходящего через заданное семейство точек. 
    Первый параметр поверхности пропорционален параметрам кривых семейства. 
    Вдоль второго параметра поверхность изменяется по закону сплайна Эрмита MbHermit3D, точками которого служат точки кривых семейства. 
    Производные по второму параметру в точках кривых вычисляются как производные параболы, 
    построенной по трём точкам и значениям параметров в них.
    На каждом участке между двумя соседними кривыми семейства поверхность описывается кубическим полиномом 
    с заданными точками и производными на краях. 
    Поверхность проходит через кривые семейства при значениях параметра из множества vParams.
           \en The surface passing through given family of curves is constructed similar to MbHermit3D Hermite spline 
    passing through given family of points. 
    First parameter of surface is proportional to parameters of curves of family. 
    Along the second parameter the surface changes under the law of MbHermit3D Hermite spline, which points are points of curves of family. 
    Derivatives by second parameter at points of curves are calculated as derivatives of parabola 
    constructed by three points and values of parameters at this points.
    On each region between two neighboring curves of family the surface is described by the cubic polynomial 
    with given points and derivatives at the edges. 
    Surface passes through curves of family for parameter values from vParams set. \~
  \ingroup Surfaces
*/ 
// ---
class MATH_CLASS MbLoftedSurface : public MbSurface {
protected: 
  RPArray<MbCurve3D> uCurves;  ///< \ru Множество кривых семейства. \en Set of curves of family. 
  SArray<double>     vParams;  ///< \ru Множество параметров v для кривых. \en Set of parameters v for curves. 
  SArray<ptrdiff_t>  vLabels;  ///< \ru Множество признаков одинаковых кривых. \en Set of attributes of similar curves. 
  double             umin;     ///< \ru Минимальное значение параметра u. \en Minimal value of parameter u. 
  double             vmin;     ///< \ru Минимальное значение параметра v. \en Minimal value of parameter v. 
  double             umax;     ///< \ru Максимальное значение параметра u. \en Maximal value of parameter u. 
  double             vmax;     ///< \ru Максимальное значение параметра v. \en Maximal value of parameter v. 
  bool               uclosed;  ///< \ru Признак замкнутости по параметру u. \en Attribute of closedness by parameter u. 
  bool               vclosed;  ///< \ru Признак замкнутости по параметру v. \en Attribute of closedness by parameter v. 
  MbVector3D         derive1;  ///< \ru Направление производной в начале незамкнутой поверхности. Если не задано, то нулевой длины. \en The direction of derivative at the beginning of the open surface. If it isn't set, then its length is zero. 
  MbVector3D         derive2;  ///< \ru Направление производной в конце  незамкнутой поверхности. Если не задано, то нулевой длины. \en The direction of derivative at the end of the open surface. If it isn't set, then its length is zero. 
  bool               setNormal1;  ///< \ru Установлена нормаль в начальном сечении. \en The normal is set in initial section.
  bool               setNormal2;  ///< \ru Установлена нормаль в конечном сечении. \en The normal is set in end section.
  VERSION            surfaceVersion;  ///< \ru Версия расчета коэффициентов уравнения поверхности. \en Version of coefficient calculation of surface equation. 

protected:
  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbLoftedSurfaceAuxiliaryData : public AuxiliaryData {
  public:
    DPtr<MbSurfaceContiguousData> data;  ///< \ru Дополнительные данные о поверхности. \en Additional data about a surface. 
    MbLoftedSurfaceAuxiliaryData();
    MbLoftedSurfaceAuxiliaryData( const MbLoftedSurfaceAuxiliaryData & init );
    virtual ~MbLoftedSurfaceAuxiliaryData();
  };
  
  mutable CacheManager<MbLoftedSurfaceAuxiliaryData> cache;

public:
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по массиву профильных кривых, направляющим векторам и замкнутости по v.
               \en Constructor of surface by array of profile curves, guide vectors and closedness by v. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] vc - \ru Замкнутость поверхности по v.
                      \en Surface closedness by v. \~
      \param[in] v1 - \ru Направляющий вектор.
                      \en Guide vector. \~
      \param[in] v2 - \ru Направляющий вектор.
                      \en Guide vector. \~
      \param[in] same - \ru Определяет, надо ли копировать профильные кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                        \en Determines whether to copy profile curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] version - \ru Версия, по умолчанию - последняя.
                           \en Version, last by default. \~
  */
  MbLoftedSurface( const RPArray<MbCurve3D> & initCurves, 
                   bool vc, const MbVector3D & v1, const MbVector3D & v2, bool same,
                   VERSION version = Math::DefaultMathVersion() );
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по массиву профильных кривых, массиву параметров, направляющим векторам и замкнутости по v.
               \en Constructor of surface by array of profile curves, array of parameters, guide vectors and closedness by v. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] initParams - \ru Множество параметров, соответствующих задающим кривым.
                              \en Set of parameters corresponding to driving curves. \~
      \param[in] vc - \ru Замкнутость поверхности по v.
                      \en Surface closedness by v. \~
      \param[in] v1 - \ru Направляющий вектор.
                      \en Guide vector. \~
      \param[in] v2 - \ru Направляющий вектор.
                      \en Guide vector. \~
      \param[in] same - \ru Определяет, надо ли копировать профильные кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                        \en Determines whether to copy profile curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] version - \ru Версия, по умолчанию - последняя.
                           \en Version, last by default. \~
  */
  MbLoftedSurface( const RPArray<MbCurve3D> & initCurves, const SArray<double> & initParams, 
                   bool vc, const MbVector3D & v1, const MbVector3D & v2, bool same,
                   VERSION version = Math::DefaultMathVersion() );
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по массиву профильных кривых, массиву параметров, замкнутости по v и определению нормалей поверхности на концах параметра v.
                   В случае установки нормалей поверхности без задания плоскостей, нормаль определяется по ближайщему сечению.
               \en Constructor of surface by array of profile curves, array of parameters, closedness by v and determining the surface normals at the ends of v.
                   In the case of installing surface normals without specifying planes, the normal is determined by the nearest non point section.\~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] initParams - \ru Множество параметров, соответствующих задающим кривым.
                              \en Set of parameters corresponding to driving curves. \~
      \param[in] vc - \ru Замкнутость поверхности по v.
                      \en Surface closedness by v. \~
      \param[in] setNormal1 - \ru Установить нормаль в начале поверхности.
                              \en Set normal at the start surface. \~
      \param[in] setNormal2 - \ru Установить нормаль в конце поверхности.
                              \en Set normal at the end of surface. \~
      \param[in] same - \ru Определяет, надо ли копировать профильные кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                        \en Determines whether to copy profile curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] version - \ru Версия, по умолчанию - последняя.
                           \en Version, last by default. \~
  */
  MbLoftedSurface( const RPArray<MbCurve3D> & initCurves, const SArray<double> & initParams, bool vc, 
                   bool setNormal1, bool setNormal2, bool same, VERSION version = Math::DefaultMathVersion() );
protected: // \ru Конструкторы для наследников \en Constructors for inheritors 
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по набору профильных кривых.
               \en Constructor of surface by family of profile curves. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] same - \ru Определяет, надо ли копировать профильные кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                        \en Determines whether to copy profile curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] version - \ru Версия, по умолчанию - последняя.
                           \en Version, last by default. \~
  */
  MbLoftedSurface( const RPArray<MbCurve3D> & initCurves, bool same, VERSION version = Math::DefaultMathVersion() );
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по массиву профильных кривых и массиву параметров.
               \en Constructor of surface by array of profile curves and array of parameters. \~
      \param[in] initParams - \ru Множество параметров, соответствующих задающим кривым.
                              \en Set of parameters corresponding to driving curves. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] same - \ru Определяет, надо ли копировать профильные кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                        \en Determines whether to copy profile curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] version - \ru Версия, по умолчанию - последняя.
                           \en Version, last by default. \~
  */
  MbLoftedSurface( const SArray<double> & initParams, const RPArray<MbCurve3D> & initCurves, bool same, VERSION version = Math::DefaultMathVersion() );
  /// \ru Конструктор-копия. \en Copy constructor. 
  MbLoftedSurface( const MbLoftedSurface &, MbRegDuplicate * reg ); 
private:
  MbLoftedSurface( const MbLoftedSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbLoftedSurface();

public:
  VISITING_CLASS( MbLoftedSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbeSpaceType  Type() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты \en Whether the objects are equal 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual void    Refresh();

  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & s ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */

  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetUMin  () const; // \ru Вернуть минимальное значение параметра u \en Return the minimum value of parameter u 
  virtual double  GetVMin  () const; // \ru Вернуть минимальное значение параметра v \en Return the minimum value of parameter v 
  virtual double  GetUMax  () const; // \ru Вернуть максимальное значение параметра u \en Return  the maximum value of parameter u 
  virtual double  GetVMax  () const; // \ru Вернуть максимальное значение параметра v \en Return the maximum value of parameter v 
  virtual bool    IsUClosed() const; // \ru Замкнута ли поверхность по параметру u. \en Whether the surface is closed by parameter u. 
  virtual bool    IsVClosed() const; // \ru Замкнута ли поверхность по параметру v. \en Whether the surface is closed by parameter v. 
  virtual double  GetUPeriod() const; // \ru Период для замкнутой поверхности или 0. \en Period for closed surface or 0. 
  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  // \ru Существует ли полюс на границе параметрической области \en Whether there is pole on boundary of parametric region 
  virtual bool    GetPoleUMin() const;
  virtual bool    GetPoleUMax() const;
  virtual bool    GetPoleVMin() const;
  virtual bool    GetPoleVMax() const;
  virtual bool    IsPole( double u, double v ) const; // \ru Является ли точка особенной \en Whether the point is special 
  /** \} */

  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.\n
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of surfaces correct parameters
            when they are out of bounds of rectangular domain of parameters.\n
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности \en Point on the surface 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по u \en Third derivative with respect to u 
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по v \en Third derivative with respect to v 
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по uv \en Third derivative with respect to uv 
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по uv \en Third derivative with respect to uv 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности \en Point on the extended surface 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const;    // \ru Первая производная по u \en First derivative with respect to u 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const;    // \ru Первая производная по v \en First derivative with respect to v 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const;    // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const;    // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const;    // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const;    // \ru Третья производная по u \en Third derivative with respect to u 
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const;    // \ru Третья производная по v \en Third derivative with respect to v 
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const;    // \ru Третья производная по uv \en Third derivative with respect to uv 
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const;    // \ru Третья производная по uv \en Third derivative with respect to uv 
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  /** \} */

  /** \ru \name Функции движения по поверхности
      \en \name Functions of moving along the surface
      \{ */
  virtual double  StepU         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  virtual double  DeviationStepU( double u, double v, double sag ) const; // \ru Вычисление шага по u при пересечении поверхностей \en Calculation of step by u while intersecting surfaces 
  virtual double  DeviationStepV( double u, double v, double sag ) const; // \ru Вычисление шага по u при пересечении поверхностей \en Calculation of step by u while intersecting surfaces 
  /** \} */
  
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской \en Whether the surface is planar 
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 
  virtual void    CalculateGabarit( MbCube & ) const; // \ru Рассчитать габарит поверхности \en Calculate bounding box of surface 

  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей \en Construct tangent and normal placements of constructive planes 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  virtual bool    GetCylinderAxis( MbAxis3D & axis ) const; // \ru Дать ось вращения для поверхности \en Get a rotation axis of a surface 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности \en NURBS copy of a surface 
  virtual MbSurface *       Offset( double d, bool same ) const;  // \ru Построить смещенную поверхность \en Create a shifted surface 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const \en Spatial copy of 'v = const'-line 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const \en Spatial copy of 'u = const'-line 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u \en Get the count of polygons by u 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v \en Get the count of polygons by v 

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями \en Determine splitting of parametric region of surface by vertical and horizontal lines 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  // \ru Найти ближайшую проекцию точки на поверхность или ее продолжение по заданному начальному приближению. \en Find the neares projection of a point onto the surface. 
  virtual bool    NearPointProjection  ( const MbCartPoint3D & pnt, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; 
  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & pnt, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const; 

  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю \en If true, then all the derivatives by U higher the first one are equal to zero 
  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю \en If true, then all the derivatives by V higher the first one are equal to zero 

  // \ru Проверить параметры и загнать в область определения, если параметр вышел за полюс.
  // Аналог глобальной функции _CheckParams, оптимизированный под использование кэшей.
  // \en Check parameters and move them inside domain if parameter is out of pole.
  // \en Check parameters. Analogue of the global function _CheckParams, optimized for caches usage.
  // \param[in] surface - \ru Поверхность. \en Surface.
  // \param[in] u -       \ru Первый параметр. \en First parameter.
  // \param[in] v -       \ru Второй параметр. \en Second parameter.
  virtual void CheckSurfParams( double & u, double & v ) const;

  /// \ru Получить количество кривых, на которых построена поверхность \en Get count of curves which the surface is constructed by 
          ptrdiff_t CurvesCount() const { return (ptrdiff_t)uCurves.Count(); }

  /** \brief \ru Получить кривую по номеру.
             \en Get curve by an index. \~
      \details \ru Получить кривую по номеру. \n
               \en Get curve by an index. \n \~
      \param[in] ind - \ru Порядковый номер кривой в массиве кривых uCurves.
                       \en Index of curve in uCurves array of curves. \~
      \return \ru Константная кривая.
              \en The constant curve. \~
  */
  const   MbCurve3D * GetCurve( ptrdiff_t ind ) const { return (ind >= 0 && ind < (ptrdiff_t)uCurves.Count()) ? uCurves[ind] : NULL; }
  /** \brief \ru Получить кривую для редактирования по номеру.
             \en Get curve for editing by an index. \~
      \details \ru Получить кривую для редактирования по номеру. \n
               \en Get curve for editing by an index. \n \~
      \param[in] ind - \ru Порядковый номер кривой в массиве кривых uCurves.
                       \en Index of curve in uCurves array of curves. \~
      \return \ru Кривая.
              \en A curve. \~
  */
          MbCurve3D * SetCurve( ptrdiff_t ind )       { return (ind >= 0 && ind < (ptrdiff_t)uCurves.Count()) ? uCurves[ind] : NULL; }
  /** \brief \ru Получить параметр по номеру.
             \en Get parameter by an index. \~
      \details \ru Получить параметр по номеру.\n
               \en Get parameter by an index.\n \~
      \param[in] ind - \ru Порядковый номер параметра в массиве параметров vParams.
                       \en Index of parameter in vParams array of parameters. \~
      \return \ru Значение параметра.
              \en A parameter value. \~
  */
          double  GetParam( ptrdiff_t ind ) const { return (ind >= 0 && ind < (ptrdiff_t)vParams.Count()) ? vParams[ind] : 0.0; }
  /** \brief \ru Заполнить массив параметрами.
             \en Fill an array by parameters. \~
      \details \ru Заполнить массив параметрами. \n
               \en Fill an array by parameters. \n \~
      \param[in,out] params - \ru Множество для заполнения параметрами.
                              \en A set to fill by parameters. \~
  */
          void    GetParams( SArray<double> & params ) const { params = vParams; }
  /** \brief \ru Заполнить массив признаков одинаковых кривых.
             \en Fill array of attributes of similar curves. \~
      \details \ru Заполнить массив признаков одинаковых кривых. \n
               \en Fill array of attributes of similar curves. \n \~
      \param[in,out] labels - \ru Множество для заполнения.
                              \en A set to fill. \~
  */
          void    GetLabels( SArray<ptrdiff_t> & labels ) const { labels = vLabels; }

  /// \ru Направление производной в начале незамкнутой поверхности. Если не задано, то нулевой длины. \en The direction of derivative at the beginning of the open surface. If it isn't set, then its length is zero.
  const MbVector3D & GetDerive1() const { return derive1; }
  ///< \ru Направление производной в конце  незамкнутой поверхности. Если не задано, то нулевой длины. \en The direction of derivative at the end of the open surface. If it isn't set, then its length is zero.
  const MbVector3D & GetDerive2() const { return derive2; }

          bool    IsEqualLabels()          const; ///< \ru Определить, есть ли одинаковые кривые. \en Determine whether there are similar curves.  
  /** \brief \ru Определить, есть ли кривые, одинаковые с кривой под номером ind.
             \en Determine whether there are curves similar to curve with 'ind' index. \~
      \details \ru Определить, есть ли кривые, одинаковые с кривой под номером ind. \n
               \en Determine whether there are curves similar to curve with 'ind' index. \n \~
      \param[in] ind - \ru Номер кривой для сравнения.
                       \en An index of curve for comparison. \~
      \return \ru true - Если в массиве есть кривые, одинаковые с кривой под номером ind.
              \en True - If there are curves similar to curve with 'ind' index in array. \~
  */
          bool    IsEqualLabels( ptrdiff_t ind ) const; 
           

  /** \brief \ru Определить, можно ли создать эквидистантную поверхность.
             \en Determine whether it is possible to create an offset surface. \~
      \details \ru Определить, можно ли создать эквидистантную поверхность.\n
               \en Determine whether it is possible to create an offset surface.\n \~
      \param[in] h - \ru Величина смещения.
                     \en The offset distance. \~
      \param[in] uLimBeg - \ru Нижняя граница по u области, к которой надо построить эквидистантную поверхность.
                           \en Lower bound of region by u which offset surface is necessary to construct to. \~
      \param[in] uLimEnd - \ru Верхняя граница по u области, к которой надо построить эквидистантную поверхность.
                           \en Upper bound of region by u which offset surface is necessary to construct to. \~
      \param[in] vLimBeg - \ru Нижняя граница по v области, к которой надо построить эквидистантную поверхность.
                           \en Lower bound of region by v which offset surface is necessary to construct to. \~
      \param[in] vLimEnd - \ru Верхняя граница по v области, к которой надо построить эквидистантную поверхность.
                           \en Upper bound of region by v which offset surface is necessary to construct to. \~
      \return \ru true - Если в можно создать эквидистантную поверхность.
              \en True - If it is possible to create an offset surface. \~
  */
          bool    IsPossibleCreateThin( double h,
                                        double uLimBeg, double uLimEnd, 
                                        double vLimBeg, double vLimEnd ) const;
  /** \brief \ru Согласовать массивы признаков одинаковости кривых у смежных поверхностей.
             \en Match arrays of attributes of similarity of curves between adjacent surfaces. \~
      \details \ru Согласовать массивы признаков одинаковости кривых у смежных поверхностей. \n
               \en Match arrays of attributes of similarity of curves between adjacent surfaces. \n \~
      \param[in] surf - \ru Смежная поверхность.
                        \en Adjacent surface. \~
      \return \ru true - Если есть изменения в массиве признаков кривых хотя бы одной поверхности.
              \en True - If there are changes in array of attributes of curves of at least one surface. \~
  */
          bool    AgreeLabels( MbLoftedSurface & surf );
  /** \} */

protected: 
          void    CheckParam( double & u, bool ext ) const; // \ru Корректировка параметров. \en Correct parameters. \~
  /** \brief \ru Определение местных координат области поверхности.
             \en Determination of local coordinates of a surface region. \~
      \details \ru Определение местных координат области поверхности. \n
               \en Determination of local coordinates of a surface region. \n \~
      \param[in] v - \ru Координата v на поверхности.
                     \en V coordinate on the surface. \~
      \param[in,out] j1 - \ru Номер ближайшей кривой с параметром, меньшим v.
                          \en Index of nearest curve with parameter less than v. \~
      \param[in,out] j2 - \ru Номер ближайшей кривой с параметром, большим v.
                          \en Index of nearest curve with parameter greater than v. \~
      \param[in,out] y1 - \ru Параметрическое расстояние от точки с координатой v до кривой j1, при условии, что расстояние между кривыми j1 и j2 равно 1.
                          \en Parametric distance from point with v coordinate to j1 curve provided that distance between j1 and j2 curves is equal to 1. \~
      \param[in,out] y2 - \ru Параметрическое расстояние от точки с координатой v до кривой j2, при условии, что расстояние между кривыми j1 и j2 равно 1.
                          \en Parametric distance from point with v coordinate to j2 curve provided that distance between j1 and j2 curves is equal to 1. \~
      \param[in,out] t1 - \ru Значение параметра для кривой j1.
                          \en Value of parameter for j1 curve. \~
      \param[in,out] t2 - \ru Значение параметра для кривой j2.
                          \en Value of parameter for j2 curve. \~
  */
          void    LocalCoordinate( double & v, ptrdiff_t & j1, ptrdiff_t & j2, double & y1, double & y2, double & t1, double & t2 ) const;
  /** \brief \ru Определение массива векторов кривой.
             \en Determination of the array of curve vectors. \~
      \details \ru Определение массива векторов кривой. \n
               \en Determination of the array of curve vectors. \n \~
      \param[in] i - \ru Номер кривой.
                     \en Index of curve. \~
      \param[in] u - \ru Координата u на поверхности.
                     \en U coordinate on the surface. \~
      \param[in] der - \ru Ссылка на массив векторов для хранения вычисленной точки и производных.
                       \en Reference to array of vectors to store calculated point and derivatives. \~
      \param[in] ext - \ru Можно ли продолжить кривую за границы области определения ее параметра.
                       \en Whether it is possible to extend curve out of its parametric domain bounds. \~
  */
          void    CalculateCurve( ptrdiff_t i, double u, MbVector3D & point, bool ext, size_t numb ) const;
          void    CalculateCurve( ptrdiff_t i, double u, MbVector3D & pnt, MbVector3D & fir, MbVector3D * sec, bool ext ) const;
  /** \brief \ru Определение массива векторов параметрa u для точки на поверхности с координатами (u, v).
             \en Determination of array of vectors of u parameter for point on surface with coordinates (u, v). \~
      \details \ru Определение массива векторов параметрa u для точки на поверхности с координатами (u, v). \n
               \en Determination of array of vectors of u parameter for point on surface with coordinates (u, v). \n \~
      \param[in] u - \ru Координата u на поверхности.
                     \en U coordinate on the surface. \~
      \param[in] j1 - \ru Номер ближайшей кривой с параметром, меньшим v.
                      \en Index of nearest curve with parameter less than v. \~
      \param[in] j2 - \ru Номер ближайшей кривой с параметром, большим v.
                      \en Index of nearest curve with parameter greater than v. \~
      \param[in] t1 - \ru Значение параметра для кривой j1.
                      \en Value of parameter for j1 curve. \~
      \param[in] t2 - \ru Значение параметра для кривой j2.
                      \en Value of parameter for j2 curve. \~
      \param[in] ext - \ru Можно ли продолжить поверхность за границы области определения ее параметров.
                       \en Whether it is possible to extend surface out of its parametric domain bounds. \~
  */
          void    CalculateSurface( double & u, ptrdiff_t j1, ptrdiff_t j2, 
                                    double t1, double t2, bool ext, size_t numb,
                                    MbVector3D & point1, MbVector3D & point2, 
                                    MbVector3D & vector1, MbVector3D & vector2, bool correctVectors = true ) const;
          void    CalculateExplore( double & u, ptrdiff_t j1, ptrdiff_t j2, 
                                    double t1, double t2, bool ext, bool boolsecond,
                                    MbVector3D * point1, MbVector3D * point2, 
                                    MbVector3D * vector1, MbVector3D * vector2,
                                    double * tLoft ) const;

  void    ParamPoint ( double y1, double y2, double t1, double t2, double * tLoft ) const;
  void    ParamFirst ( double y1, double y2, double t1, double t2, double * tLoft ) const;
  void    ParamSecond( double y1, double y2, double t1, double t2, double * tLoft ) const;
  void    ParamThird ( double t1, double t2, double * tLoft ) const;

  /** \brief \ru Проверка полюсов на кривых.
             \en Check poles on curves. \~
      \details \ru Определяет, есть ли полюс на границе области определения по длине кривой, определяющей границу.\n
      Результат вычислений можно получить с помощью функций GetPoleUMin, GetPoleUMax, GetPoleVMin, GetPoleVMax.
               \en Determines whether the pole at domain boundary by curve length determining boundary.\n
      Result of calculations can be obtained with help of GetPoleUMin, GetPoleUMax, GetPoleVMin, GetPoleVMax functions. \~ 
  */
          bool    CheckPoles( MbLoftedSurfaceAuxiliaryData * ) const; // \ru Проверка полюсов на кривых \en Check poles on curves 

private:
          void    Init( bool close ); 
          bool    IsSimilarCurves( ptrdiff_t i1, ptrdiff_t i2 ) const; // \ru Определение одинаковых кривых \en Determination of similar curves 
          bool    IsSimilarLabels( ptrdiff_t i1, ptrdiff_t i2 ) const; // \ru Определение одинаковых кривых по меткам. \en Determination of similar curves by labels. 
          void    InitLabels();                                        // \ru Инициализация признаков одинаковых кривых. \en Initialization of attributes of similar curves. 

          void    operator = ( const MbLoftedSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbLoftedSurface )
};

IMPL_PERSISTENT_OPS( MbLoftedSurface )

//------------------------------------------------------------------------------
// \ru Корректировка параметров. \en Correct parameters. \~
// ---
inline void MbLoftedSurface::CheckParam( double & u, bool ext ) const
{
  if ( !ext ) {    
    if ( uclosed ) { // переписана на ::floor(), т.к. подвисала на while
      if ( (u < umin) || (u > umax) ) {
        double pRgn = ( umax - umin );
        u -= ( ::floor((u - umin) / pRgn) * pRgn );
      }
    }
    else if ( u < umin ) {
      u = umin;
    }
    else if ( u > umax ) {
      u = umax;
    }
  }
  else {
    if ( u < umin && GetPoleUMin() ) {
      u = umin;
    }
    else if ( u > umax && GetPoleUMax() ) {
      u = umax;
    }
  }
}


//------------------------------------------------------------------------------
// \ru Определение местных координат области поверхности \en Determination of local coordinates in a surface region 
// ---
inline void MbLoftedSurface::LocalCoordinate( double & v, ptrdiff_t & j1, ptrdiff_t & j2,
                                              double & y1, double & y2, 
                                              double & t1, double & t2 ) const
{
  if ( v < vmin || v > vmax ) { // \ru Параметр вне границ \en Parameter is out of bounds 
    if ( vclosed ) { 
      double tmp = vmax - vmin;
      v -= ::floor((v - vmin) / tmp) * tmp; 
    }
    else {
      if ( v < vmin )
        v = vmin;
      else
        v = vmax;
    }
  }

  j1 = 0;
  j2 = vParams.MaxIndex();

  ptrdiff_t ind, delta = j2; // \ru Диапазон \en A range 

  // \ru Поиск половинным делением \en Search by bisection 
  while ( delta > 1 ) {
    ind = j1 + ( delta / (ptrdiff_t)2 ); // \ru Индекс в середине \en The index in the middle 
    if ( v < vParams[ind] )  // \ru Если v меньше серединного параметра \en If v is less than the middle parameter 
      j2 = ind; // \ru Изменить правую границу \en Change the right bound 
    else 
      j1 = ind; // \ru Изменить левую границу \en Change the left bound 
    delta = j2 - j1; // \ru Диапазон \en A range 
  }

  t1 = vParams[j1];
  t2 = vParams[j2];
  double dt = t2 - t1;
  double antiDt = 1.0;
  if ( dt > NULL_EPSILON ) 
    antiDt /= dt;
  y1 = (t2 - v) * antiDt;
  y2 = (v - t1) * antiDt;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa точки \en Determination of array of degrees of point parameter 
// ---
inline void MbLoftedSurface::ParamPoint( double y1, double y2, double t1, double t2, double * tLoft ) const
{
  double y1pow2 = y1 * y1;
  double y2pow2 = y2 * y2;
  double y1pow3 = y1pow2 * y1;
  double y2pow3 = y2pow2 * y2;
  tLoft[0] = 3.0 * y1pow2 - 2.0 * y1pow3;
  tLoft[1] = 3.0 * y2pow2 - 2.0 * y2pow3;
  tLoft[2] = (y1pow3 - y1pow2) * (t1-t2);
  tLoft[3] = (y2pow3 - y2pow2) * (t2-t1);
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa производной \en Determination of array of degrees of derivative parameter 
// ---
inline void MbLoftedSurface::ParamFirst( double y1, double y2, double t1, double t2, double * tLoft ) const
{
  double y1pow2 = y1 * y1;
  double y2pow2 = y2 * y2;
  double kdt1 = 1.0 / (t1 - t2);
  double kdt2 = -kdt1;
  tLoft[0] = 6.0 * (y1 - y1pow2) * kdt1;
  tLoft[1] = 6.0 * (y2 - y2pow2) * kdt2;
  tLoft[2] = (3.0 * y1pow2 - 2.0 * y1);
  tLoft[3] = (3.0 * y2pow2 - 2.0 * y2);
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa второй производной \en Determination of array of degrees of second derivative parameter 
// ---
inline void MbLoftedSurface::ParamSecond( double y1, double y2, double t1, double t2, double * tLoft ) const {
  double d1 = 1 / (t1-t2);
  double d2 = -d1;
  tLoft[0] = (6 - 12 * y1) * d1 * d1;
  tLoft[1] = (6 - 12 * y2) * d2 * d2;
  tLoft[2] = (6 * y1 - 2) * d1;
  tLoft[3] = (6 * y2 - 2) * d2;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметрa третьей производной \en Determination of array of degrees of third derivative parameter 
// ---
inline void MbLoftedSurface::ParamThird( double t1, double t2, double * tLoft ) const {
  double d1 = 1 / (t1-t2);
  double d2 = -d1;
  double d1pow2 = d1 * d1;
  double d2pow2 = d2 * d2;
  tLoft[0] = -12 * d1pow2 * d1;
  tLoft[1] = -12 * d2pow2 * d2;
  tLoft[2] =   6 * d1pow2;
  tLoft[3] =   6 * d2pow2;
}


//------------------------------------------------------------------------------
/** \brief \ru Наполнить массив v-параметров и весовых центров заданных кривых.
           \en Fill array of v-parameters and weight centers of given curves. \~
  \details \ru Если все профильные кривые плоские, параметры вычисляются функцией CreateElevationParam. 
  Иначе параметр для каждой кривой вычисляется как координата вдоль направляющей проекции центра масс кривой на направляющую.
           \en If all the profile curves are planar, then parameters are calculated by CreateElevationParam function. 
  Otherwise parameter for each curve is calculated as coordinate along guide projection of center of mass of curve to guide. \~
  \param[in] uCurves - \ru Множество профильных кривых.
                       \en Set of profile curves. \~
  \param[in] vcls - \ru Замкнута ли поверхность по параметру v.
                    \en Whether the surface is closed by parameter v. \~
  \param[in,out] vParams - \ru Множество параметров.
                           \en Set of parameters. \~
  \param[in,out] tiePnts - \ru Множество центров масс профильных кривых. Не заполняется, если в функцию передать NULL.
                           \en Set of centers of mass of profile curves. If giving NULL to function, then it isn't filled. \~
  \param[in] version - \ru Версия.
                       \en Version. \~
  \return \ru true - если массив параметров успешно создан.
          \en True - if the array of parameters successfully created. \~ 
  \ingroup Algorithms_3D
*/
// ---
bool CreateLoftedParams( const RPArray<MbCurve3D> &    uCurves, 
                               bool                    vcls,
                               SArray<double> &        vParams,
                               SArray<MbCartPoint3D> * tiePnts,
                               VERSION                 version );


#endif // __SURF_LOFTED_SURFACE_H
