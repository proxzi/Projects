////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Радиальный размер к поверхности. Расстояние между поверхностями.
         \en Radial dimension of surface. Distance between surfaces. \~
  \details \ru Функции построения окружности или дуги для радиального размера к поверхности.
    Функция вычисления экстремальных расстояний между поверхностями.
           \en Functions of construction of a circle or an arc for radial dimension of surface.
    A function of calculation of extreme distances between surfaces. \~
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __ALG_DIMENSION_H
#define __ALG_DIMENSION_H


#include <templ_s_array.h>
#include <mb_enum.h>
#include <mb_cart_point.h>


class  MATH_CLASS  MbCartPoint3D;
class  MATH_CLASS  MbVector3D;
class  MATH_CLASS  MbPlacement3D;
class  MATH_CLASS  MbAxis3D;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbPlaneCurve;
class  MATH_CLASS  MbSurface;
class              IProgressIndicator;


////////////////////////////////////////////////////////////////////////////////
// 
// \ru Построение окружности или дуги для радиального размера к поверхности, \en Construction of a circle or an arc for radial dimension of surface 
// \ru имеющей круговую параметрическую линию u=const или v=const \en which has a circular parametric line u=const or v=const. 
// \ru Перечень поверхностей, имеющих параметрическую линию u=const или u=const: \en The enumeration of surfaces which have a parametric line u=const or u=const: 
// MbCylinderSurface,      v=const
// MbConeSurface,          v=const
// MbSphereSurface,        u=const
// MbTorusSurface,         u=const
// MbLoftedSurface,        v=const
// MbElevationSurface,     v=const
// MbExtrusionSurface,     v=const
// MbRevolutionSurface,    u=const
// MbEvolutionSurface,     u=const
// MbExactionSurface,      u=const
// 
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
/** \brief \ru Построить окружность или дугу для радиального размера к поверхности.
           \en Construct a circle or an arc for radial dimension of surface. \~
  \details \ru Построение выполняется по заданной параметрической точке поверхности. Поверхность 
    должна иметь круговую параметрическую линию u=const или v=const. Перечень поверхностей,
    имеющих параметрическую линию u=const или v=const:
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const.
           \en Construction is performed by the given parametric point on surface. A surface 
    should have a circular parametric line u=const or v=const. The enumeration of surfaces
    which have a parametric line u=const or v=const.
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const. \~
  \param[in] surface - \ru Исходная поверхность.
                       \en The initial surface. \~
  \param[in] surface_uv - \ru Координаты исходной точки на поверхности.
                          \en Coordinates of the initial point on surface. \~
  \param[out] plane_curve - \ru Требуемая окружность или дуга.
                            \en The required circle or an arc. \~ 
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (void) RadiusDimension3D( const MbSurface     & surface, 
                                    const MbCartPoint   & surface_uv,
                                          MbPlaneCurve *& plane_curve ); 


//------------------------------------------------------------------------------
/** \brief \ru Построить окружность или дугу для радиального размера к поверхности.
           \en Construct a circle or an arc for radial dimension of surface. \~
  \details \ru Построение выполняется по заданной по заданной пространственной точке. Поверхность 
    должна иметь круговую параметрическую линию u=const или v=const. Перечень поверхностей,
    имеющих параметрическую линию u=const или u=const:
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const.
           \en Construction is performed by the given spatial point. A surface 
    should have a circular parametric line u=const or v=const. The enumeration of surfaces
    which have a parametric line u=const or v=const.
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const. \~
  \param[in] surface - \ru Исходная поверхность.
                       \en The initial surface. \~
  \param[in] point - \ru Пространственные координаты исходной точки.
                     \en Space coordinates of the initial point. \~
  \param[out] plane_curve - \ru Требуемая окружность или дуга.
                            \en The required circle or an arc. \~ 
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (void) RadiusDimension3D( const MbSurface     & surface, 
                                    const MbCartPoint3D & point,
                                          MbPlaneCurve *& plane_curve ); 


//------------------------------------------------------------------------------
/** \brief \ru Построить окружность или дугу для радиального размера к поверхности.
           \en Construct a circle or an arc for radial dimension of surface. \~
  \details \ru Построение выполняется по заданному плейсменту. Поверхность должна иметь 
    круговую параметрическую линию u=const или v=const. Перечень поверхностей, имеющих 
    параметрическую линию u=const или u=const:
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const.
           \en Construction is performed by the given placement. A surface should have 
    a circular parametric line u=const or v=const. The enumeration of surfaces with 
    a parametric line u=const or v=const.
    MbCylinderSurface     v=const, \n   MbConeSurface         v=const, \n
    MbSphereSurface       u=const, \n   MbTorusSurface        u=const, \n
    MbLoftedSurface       v=const, \n   MbElevationSurface    v=const, \n
    MbExtrusionSurface    v=const, \n   MbRevolutionSurface   u=const, \n
    MbEvolutionSurface    u=const, \n   MbExactionSurface     u=const. \~
  \param[in] surface - \ru Исходная поверхность.
                       \en The initial surface. \~
  \param[in] place - \ru Исходный плейсмент.
                     \en The initial placement. \~
  \param[out] plane_curve - \ru Требуемая окружность или дуга.
                            \en The required circle or an arc. \~ 
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (void) RadiusDimension3D( const MbSurface     & surface, 
                                    const MbPlacement3D & place,
                                          MbPlaneCurve *& plane_curve ); 


//------------------------------------------------------------------------------
/** \brief \ru Можно ли построить окружность или дугу для радиального размера к поверхности.
           \en Whether a circle or an arc can be constructed for radial dimension of surface. \~
  \details \ru Можно построить, если тип базовой поверхности: st_CylinderSurface или st_ConeSurface,
    или st_SphereSurface, или st_TorusSurface.
           \en It can be constructed if the type of a base surface is st_CylinderSurface or st_ConeSurface,
    or st_SphereSurface, or st_TorusSurface. \~
  \param[in] surface - \ru Исходная поверхность.
                       \en The initial surface. \~
  \return \ru true, если можно построить.
          \en true if it can be constructed. \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) IsPossibleRadiusDimension3D( const MbSurface & surface ); 


//------------------------------------------------------------------------------
/** \brief \ru Результат замера расстояния и угла между поверхностями.
           \en The result of measurement of dimension and angle between surfaces. \~
  \details \ru Результат замера расстояния и угла между поверхностями.
           \en The result of measurement of dimension and angle between surfaces. \~
  \ingroup Algorithms_3D
*/
// ---
enum MbeSurfAxesMeasureRes
{
  // \ru ошибочные результат \en mistaken result 
  samr_SurfSurf_Failed = -3,  ///< \ru Ошибка при работе с поверхностями. \en An error is occurred while working with surfaces. 
  samr_AxisSurf_Failed = -2,  ///< \ru Ошибка при работе с осью и поверхностю. \en An error is occurred while working with axis and surface. 
  samr_AxisAxis_Failed = -1,  ///< \ru Ошибка при работе с осями. \en An error is occurred while working with axes. 
  // \ru пустой результат \en an empty result. 
  samr_Undefined = 0,         ///< \ru Не получилось или не измерялось. \en Failed or didn't measured. 
  // \ru две оси \en two axes 
  samr_AxisAxis_Coaxial,      ///< \ru Оси совпадают. \en Axes are coincident. 
  samr_AxisAxis_Parallel,     ///< \ru Оси параллельны. \en Axes are parallel. 
  samr_AxisAxis_Intersecting, ///< \ru Оси пересекаются. \en Axes are crossed. 
  samr_AxisAxis_Distant,      ///< \ru Оси на расстоянии. \en Axes are located at a distance. 
  // \ru одна ось (какая из осей есть, см. по возвращаемому флагу функции замера) \en one axis (see the returned flag of measurement function to detect which one exactly) 
  samr_AxisSurf_Colinear,     ///< \ru Ось лежит на поверхности. \en The axis lies on the surface. 
  samr_AxisSurf_Parallel,     ///< \ru Ось параллельна поверхности. \en The axis is parallel to the surface. 
  samr_AxisSurf_Intersecting, ///< \ru Ось пересекает поверхность. \en The axis crosses the surface. 
  samr_AxisSurf_Distant,      ///< \ru Ось на расстоянии от поверхности. \en The axis is located at a distance from the surface. 
  // \ru две плоские поверхности \en two planar surfaces 
  samr_SurfSurf_Colinear,     ///< \ru Одна поверхность лежит на другой. \en One surface lies on another one. 
  samr_SurfSurf_Parallel,     ///< \ru Поверхности параллельны. \en Surfaces are parallel. 
  samr_SurfSurf_Intersecting, ///< \ru Поверхности пересекаются. \en Surfaces are intersecting inside domain. 
  // \ru samr_SurfSurf_Distant,      // находятся на расстоянии \en samr_SurfSurf_Distant,      // located at a distance 

};


//------------------------------------------------------------------------------
/** \brief \ru Расстояние между осями поверхностей.
           \en Distance between axes of surfaces. \~
  \details \ru Рассчитывается расстояние между осями поверхностей, имеющих оси вращения,
    или расстояние между поверхностью, имеющей ось, и плоской поверхностью.
           \en Calculate distance between axes of revolution surfaces
    or distance between revolution surface and planar surface. \~
  \param[in] surface1, sameSense1 - \ru Первая поверхность и ее направление.
                                    \en The first surface and its direction. \~
  \param[in] surface2, sameSense2 - \ru Вторая поверхность и ее направление.
                                    \en The second surface and its direction. \~
  \param[out] axis1, exist1 - \ru Ось первой поверхности и флаг ее наличия.
                              \en The axis of the first surface and the flag of its existence. \~
  \param[out] axis2, exist2 - \ru Ось второй поверхности и флаг ее наличия.
                              \en The axis of the second surface and the flag of its existence. \~
  \param[out] p1 - \ru Точка на первой оси или поверхности.
                   \en The point on the first axis or surface. \~
  \param[out] p2 - \ru Точка на второй оси или поверхности.
                   \en The point on the second axis or surface. \~
  \param[out] angle - \ru Угол между осями или осью поверхностью.
                      \en The angle between axes or between an axis and a surface. \~
  \param[out] distance - \ru Минимальное расстояние между осями.
                         \en Minimal distance between axes. \~
  \param[in] angle - \ru Угловая погрешность.
                     \en The angle accuracy. \~
  \return \ru Вариант полученного замера или вариант ошибки.
          \en The variant of the obtained measurement or the variant of error. \~ 
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbeSurfAxesMeasureRes) SurfAxesDistAngle( const MbSurface & surface1, bool sameSense1,
                                                     const MbSurface & surface2, bool sameSense2,
                                                     MbAxis3D & axis1, bool & exist1,
                                                     MbAxis3D & axis2, bool & exist2,
                                                     MbCartPoint3D & p1,
                                                     MbCartPoint3D & p2,
                                                     double & angle,
                                                     double & distance,
                                                     double angleEps = ANGLE_EPSILON );


//------------------------------------------------------------------------------
/** \brief \ru Расстояние между точками на поверхности.
           \en Distance between points on surface. \~
  \details \ru Класс содержит данные о расстоянии между точками и координатами этих точек
    на поверхностях.
           \en The class contains data about the distance between points and their coordinates
    on surfaces. \~
  \ingroup Algorithms_3D
*/
// ---
class MATH_CLASS MbSurfDist {
  friend class MbMinMaxSurfDists;
private:
  double      d;    ///< \ru Расстояние. \en Distance. 
  MbCartPoint uv1;  ///< \ru Параметр на первой поверхности. \en Parameter on the first surface. 
  MbCartPoint uv2;  ///< \ru Параметр на второй поверхности. \en Parameter on the second surface. 
  uint8       sign; ///< \ru Знак расстояния. \en Sign of direction. 

public:
  /// \ru Конструктор. \en Constructor. 
  MbSurfDist() : d( UNDEFINED_DBL ), uv1(), uv2(), sign( 1 ) {}
  /// \ru Конструктор по данным. \en The constructor by data. 
  MbSurfDist( double _d, const MbCartPoint & _uv1, const MbCartPoint & _uv2, bool plus ) { Init( _d, _uv1, _uv2, plus ); }
  /// \ru Конструктор копирования. \en Copy constructor. 
  MbSurfDist( const MbSurfDist & other ) { Init( other ); }
  /// \ru Деструктор. \en The destructor. 
  virtual ~MbSurfDist() {}
public:
        /// \ru Функция копирования. \en Copy function. 
        void          Init( const MbSurfDist & obj ) { d = obj.d; uv1 = obj.uv1; uv2 = obj.uv2; sign = obj.sign; }
        /// \ru Получить расстояние. \en Get distance. 
        double        GetDistance() const { return d;   } 
        /// \ru Получить точку на первой поверхности. \en Get the point on the first surface. 
  const MbCartPoint & GetPointOne() const { return uv1; } 
        /// \ru Получить точку на второй поверхности. \en Get the point on the second surface. 
  const MbCartPoint & GetPointTwo() const { return uv2; } 
        /// \ru Расстояние положительное? \en Is the distance positive? 
        bool          IsPositive() const { return (sign > 0); } 
        /// \ru Расстояние отрицательное? \en Is the distance negative? 
        bool          IsNegative() const { return (sign < 1); } 
        /// \ru Оператор присваивания. \en Assignment operator. 
  const MbSurfDist  & operator = ( const MbSurfDist & other ) { Init( other ); return (*this); }  

private:
        void          Init( double _d, const MbCartPoint & _uv1, const MbCartPoint & _uv2, bool plus );
};


//------------------------------------------------------------------------------
// \ru инициализатор \en Initializer 
// ---
inline void MbSurfDist::Init( double _d, const MbCartPoint & _uv1, const MbCartPoint & _uv2, bool plus )
{
  d = _d; 
  uv1 = _uv1; 
  uv2 = _uv2; 
  sign = plus ? 1 : 0; 
}


//------------------------------------------------------------------------------
/** \brief \ru Расстояния с точками между поверхностями.
           \en Distances between surfaces with points. \~
  \details \ru Расстояния с точками между поверхностями.
           \en Distances between surfaces with points. \~
  \ingroup Algorithms_3D
*/
// ---
class MATH_CLASS MbMinMaxSurfDists {
private :
  SArray<MbSurfDist>  surfDistances;  ///< \ru Расстояние и параметры на поверхностях. \en Distance and parameters on surfaces. 
  mutable double      midDistance;    ///< \ru Среднее расстояние. \en Average distance. 
  mutable double      minDistance;    ///< \ru Минимальное расстояние. \en Minimal distance. 
  mutable double      maxDistance;    ///< \ru Максимальное расстояние. \en Maximal distance. 
  mutable bool        sorted;         ///< \ru Признак сортированности. \en Attribute of being sorted. 

public:
  MbMinMaxSurfDists( size_t nReserve = 0 ); ///< \ru Конструктор. \en Constructor. 
  virtual ~MbMinMaxSurfDists();             ///< \ru Деструктор. \en Destructor. 

public:
  bool      IsEmpty()     const { return (surfDistances.Count() < 1); } ///< \ru Есть ли замеры? \en Are there any measurements? 
  size_t    GetCount()    const { return surfDistances.Count();    }    ///< \ru Количество замеров. \en The number of measurements. 
  ptrdiff_t GetMaxIndex() const { return surfDistances.MaxIndex(); }    ///< \ru Индекс последнего замера. \en Index of the last measurement 
  void      Reserve( size_t nReserve );                                 ///< \ru Зарезервировать память под nReserve элементов. \en Reserve memory for 'nReserve' elements. 
  void      RemoveAll( bool bAdjustMemory );                            ///< \ru Удалить все элементы \en Delete all elements. 
  void      AdjustMemory();                                             ///< \ru Освободить лишнюю память \en Free the unnecessary memory. 

  /// \ru Получить расстояние по индексу. \en Get the distance by the index. 
  bool GetDistance( size_t k, double & d ) const;
  /// \ru Получить расстояние со знаком, по индексу. \en Get the signed distance by the index. 
  bool GetSignedDistance( size_t k, double & d ) const;
  /// \ru Считаем ли вы расстояние отрицательным. \en Whether the distance is negative. 
  bool IsNegativeDistance( size_t k ) const { return ((k < surfDistances.Count()) ? surfDistances[k].IsNegative() : false); }
  /// \ru Получить минимальное расстояние. \en Get minimal distance. 
  bool GetMinDistance( double & d ) const;
  /// \ru Получить максимальное расстояние. \en Get maximal distance. 
  bool GetMaxDistance( double & d ) const;
  /// \ru Получить среднее расстояние. \en Get average distance. 
  bool GetMidDistance( double & d ) const;
  /// \ru Получить расстояние и точки на поверхностях. \en Get distance and points on surface. 
  bool GetSurfDistance( size_t k, double & d, MbCartPoint & uv1, MbCartPoint & uv2 ) const;
  /// \ru Получить расстояние и точки на поверхностях. \en Get distance and points on surface. 
  bool GetSurfDistance( size_t k, double & d, bool & plus, MbCartPoint & uv1, MbCartPoint & uv2 ) const;
  /// \ru Добавить расстояние и точки на поверхностях. \en Add distance and points on surface. 
  bool AddSurfDistance( double distance, bool plus, const MbCartPoint & uv1, const MbCartPoint & uv2, 
                        bool bAddEqual, double eps = LENGTH_EPSILON );
  /// \ru Сортировать по возрастанию расстояния. \en Sort by distance in the ascending order. 
  void Sort();
  /// \ru Убрать объекты с одинаковыми расстояниями. \en Remove objects with similar distances. 
  void RemoveEqualDistances( double eps = LENGTH_EPSILON );

  void operator = ( const MbMinMaxSurfDists & ); ///< \ru Оператор присваивания. \en Assignment operator. 

private:
  MbMinMaxSurfDists( const MbMinMaxSurfDists & );
};


//------------------------------------------------------------------------------
// \ru выдать расстояние \en get the distance 
// ---
inline bool MbMinMaxSurfDists::GetDistance( size_t k, double & d ) const
{
  if ( k < surfDistances.Count() ) {
    d = surfDistances[k].GetDistance();
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
// \ru выдать расстояние со знаком \en get signed distance 
// ---
inline bool MbMinMaxSurfDists::GetSignedDistance( size_t k, double & d ) const
{
  if ( k < surfDistances.Count() ) {
    d = surfDistances[k].GetDistance();
    if ( surfDistances[k].IsNegative() )
      d = -d;
    return true;
  }
  return false;
}


//------------------------------------------------------------------------------
/** \brief \ru Экстремальные расстояния между поверхностями.
           \en Extreme distances between surfaces. \~
  \details \ru Экстремальные расстояния между поверхностями по сетке на первой поверхности,
    причем замеры осуществляются в заданном направлении (если есть вектор)
    или по нормалям к первой поверхности.
           \en Extreme distances between surfaces by mesh on the first surface,
    measurements are performed in a given direction (if the vector is set)
    or by normals of the first surface. \~
  \param[in] surface1 - \ru Первая поверхность.
                        \en The first surface. \~
  \param[in] u1cnt - \ru Количество точек по u (первая поверхность).
                     \en The number of points by u (the first surface) \~
  \param[in] v1cnt - \ru Количество точек по v (первая поверхность).
                     \en The number of points by v (the first surface) \~
  \param[in] dir - \ru Вектор заданного направления (если нет, то по нормали).
                   \en The vector of direction (if not set then by the normal). \~
  \param[in] orient - \ru Направление поиска.
                      \en Direction of search. \~
  \param[in] useEqualDistances - \ru Оставлять равные равные расстояния.
                                 \en Whether to use the equal distances. \~
  \param[in] surface2 - \ru Вторая поверхность.
                        \en The second surface. \~
  \param[in,out] nMin - \ru Кол-во регистрируемых минимумов.
                        \en The number of registrated minimums. \~
  \param[in,out] nMax - \ru Кол-во регистрируемых максимумов.
                        \en The number of registrated maximums. \~
  \param[out] allResults - \ru Все результаты.
                           \en All results. \~
  \param[out] minResults - \ru Результаты-минимумы.
                           \en Results-minimums. \~
  \param[out] maxResults - \ru Результаты-максимумы.
                           \en Results-maximums. \~
  \param[in,out] indicator - \ru Интерфейс-индикатор процесса выполнения.
                             \en Interface-indicator of the execution process. \~
  \return \ru Возвращает результат замера (получен, не получен или же процесс был прерван).
          \en Returns the result of measurement (obtained, not obtained, or the process has been aborted). \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbeProcessState) MinMaxDistances( const MbSurface & surface1,
                                             ptrdiff_t u1cnt,
                                             ptrdiff_t v1cnt,
                                             const MbVector3D * dir,
                                             const MbeSenseValue & orient,
                                             bool useEqualDistances,
                                             const MbSurface & surface2,
                                             ptrdiff_t & nMin,
                                             ptrdiff_t & nMax,
                                             MbMinMaxSurfDists & allResults,
                                             MbMinMaxSurfDists & minResults,
                                             MbMinMaxSurfDists & maxResults,
                                             IProgressIndicator * indicator = NULL );


#endif // __ALG_DIMENSION_H
