////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность, проходящая через заданное семейство кривых, с направляющей.
         \en Lofted surface with guide curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_ELEVATION_SURFACE_H
#define __SURF_ELEVATION_SURFACE_H

#include <surf_lofted_surface.h>
#include <surf_spine.h>


class  MATH_CLASS  MbContourOnPlane;

const VERSION ELEVATION_SURFACE_VERSION  = 0x0B000000L; ///< \ru Версия активации поверхности по сечениям с направляющей. \en Start using version.
const VERSION ELEVATION_SURFACE_VERSION1 = 0x0F001003L; ///< \ru Расчёт точки на поверхности аналогично Lofted-поверхности. \en Calculation of points on the surface is similar to Lofted surface.


//------------------------------------------------------------------------------
/** \brief \ru Поверхность, проходящая через заданное семейство кривых, с направляющей.
           \en Lofted surface with guide curve. \~
  \details \ru Поверхность, построенная на совокупности сечений и направляющей кривой.
    Поверхность является аналогом поверхности MbLoftedSurface, построенной по набору сечений, 
    но отличающаяся от нее наличием направляющей кривой, задающей форму перехода от одного сечения к другому.
    Первый параметр поверхности изменяется вдоль сечений. 
    Второй параметр поверхности изменяется вдоль направляющей кривой.
           \en Surface constructed by set of sections and guide curve.
    The surface is analog of MbLoftedSurface surface constructed on a set of sections, 
    but differs from it by existence of the guide curve which is determining a form of transition from one section to another.
    The first parameter of the surface is changed along sections. 
    The second parameter of the surface is changed along guide curve. \~ 
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbElevationSurface : public MbLoftedSurface {
private:
  MbCurve3D *      spine;       ///< \ru Направляющая кривая (не NULL). \en Guide curve (not NULL). 
  RPArray<MbSpine> mSpines;     ///< \ru Множество указателей на направляющие кривые (на основе spine). \en Set of pointers to guide curves (based on 'spine').
  bool             isSimToEvol; ///< \ru Способ расчёта точек на поверхности. \en Way of calculating of points on the surface.

public:
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по набору задающих кривых и направляющей кривой.
               \en Constructor of lofted with guide curve surface by the set of driving curves and guide curve. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] sameCurves - \ru Определяет, надо ли копировать задающие кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                              \en Determines whether to copy driving curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] initSpine - \ru Направляющая кривая.
                             \en The spine (guide) curve. \~
      \param[in] sameSpine - \ru Определяет, надо ли копировать направляющую кривую: true - использовать полученную кривую без копирования, false - использовать копию.
                             \en Determines whether to copy guide curve: true - use obtained curve without copying, false - use copy. \~
      \param[in] simToEvol - \ru Определяет способ расчёта точек на поверхности: true - аналогично кинематической поверхности, false - поверхности по сечениям.
                             \en Determines how to calculate points on the surface: true - similarly to evolution surface, false - lofted surface. \~
      \param[in] version - \ru Версия модели. По умолчанию текущая версия математики.
                           \en Version of model. Current version of mathematics by default. \~
  */
  MbElevationSurface( const RPArray<MbCurve3D> & initCurves, bool sameCurves,
                      const MbCurve3D          & initSpine,  bool sameSpine,
                      bool simToEvol = true,
                      VERSION version = Math::DefaultMathVersion() );
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
      \details \ru Конструктор поверхности по набору задающих кривых, массиву параметров для них и направляющей кривой.
               \en Constructor of lofted with guide curve surface by the set of driving curves, array of parameters for driving curves and guide curve. \~
      \param[in] initVParams - \ru Множество параметров для задающих кривых.
                               \en Set of parameters for driving curves. \~
      \param[in] initCurves - \ru Множество задающих кривых.
                              \en Set of driving curves. \~
      \param[in] sameCurves - \ru Определяет, надо ли копировать задающие кривые: true - использовать полученные кривые без копирования, false - использовать копии.
                              \en Determines whether to copy driving curves: true - use obtained curves without copying, false - use copies. \~
      \param[in] initSpine - \ru Направляющая кривая.
                             \en The spine (guide) curve. \~
      \param[in] sameSpine - \ru Определяет, надо ли копировать направляющую кривую: true - использовать полученную кривую без копирования, false - использовать копию.
                             \en Determines whether to copy guide curve: true - use obtained curve without copying, false - use copy. \~
      \param[in] simToEvol - \ru Определяет способ расчёта точек на поверхности: true - аналогично кинематической поверхности, false - поверхности по сечениям.
                             \en Determines how to calculate points on the surface: true - similarly to evolution surface, false - lofted surface. \~
      \param[in] version - \ru Версия модели. По умолчанию текущая версия математики.
                           \en Version of model. Current version of mathematics by default. \~
  */
  MbElevationSurface( const SArray<double>     & initVParams,
                      const RPArray<MbCurve3D> & initCurves, bool sameCurves,
                      const MbCurve3D          & initSpine,  bool sameSpine, 
                      bool simToEvol = true,
                      VERSION version = Math::DefaultMathVersion() ); // \ru Конструктор с заданными параметрами для сечений \en Constructor with specified parameters for sections 
protected:
  MbElevationSurface( const MbElevationSurface &, MbRegDuplicate * reg ); ///< \ru Конструктор копирования. \en Copy-constructor. 
private:
  MbElevationSurface( const MbElevationSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbElevationSurface();

public:
  VISITING_CLASS( MbElevationSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты \en Whether the objects are equal 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual void    Refresh  ();

  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems  ( RPArray<MbSpaceItem> & s ); ///< \ru Дать базовые объекты. \en Get the base objects. 
  /** \} */

  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual size_t  GetVCount() const;
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
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на поверхности \en Point on the surface 
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
  virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of step of approximation with consideration of curvature radius 
  virtual double  DeviationStepV( double u, double v, double sag ) const; // \ru Вычисление шага по u при пересечении поверхностей \en Calculation of step by u while intersecting surfaces 
  /** \} */
  
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности \en NURBS copy of a surface 
  virtual MbSurface *       Offset( double d, bool same ) const;  // \ru Построить смещенную поверхность \en Create a shifted surface 

  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const \en Spatial copy of 'u = const'-line 

  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 
  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей \en Construct tangent and normal placements of constructive planes 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;

  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v \en Get the count of polygons by v 

  /// \ru Вернуть направляющую кривую. \en Return spine (guide) curve.  
  const MbCurve3D & GetSpineCurve() const { C3D_ASSERT( spine != NULL ); return *spine; }

  /// \ru Вернуть направляющую кривую. \en Return spine (guide) curve.  
  bool IsSimilarToEvolution() const { return isSimToEvol; }
  
private:
          void    Init( VERSION version ); // \ru Инициализация данных \en Data initialization 
          void    SpineInit();
          void    ProfilePoint( ptrdiff_t i, double v, bool pole, // \ru Полюс. \en Pole. 
                                const MbCartPoint3D & sPoint,
                                const MbVector3D & point,
                                MbVector3D & derives0 ) const; 
          void    ProfileExplore( ptrdiff_t i, double v, bool pole, // \ru Полюс. \en Pole. 
                                  const MbCartPoint3D & sPoint,
                                  const MbVector3D & sFirst, 
                                  const MbVector3D * sSecond, 
                                  const MbVector3D * points,
                                  MbVector3D * derives0,
                                  MbVector3D * derives1,
                                  MbVector3D * derives2 ) const;
          void    ProfileSurface( ptrdiff_t i, double v, bool pole, // \ru Полюс. \en Pole. 
                                  uint uDeg, uint vDeg, 
                                  const MbCartPoint3D & spinePoint,
                                  const MbVector3D & spineFirst, 
                                  const MbVector3D & spineSecond, 
                                  const MbVector3D & spineThird,
                                  const MbVector3D * points,
                                  MbVector3D * derives0,
                                  MbVector3D * derives1,
                                  MbVector3D * derives2,
                                  MbVector3D * derives3 ) const; // \ru Определение массива производных для i-го сечения \en Determination of array of derivatives for i-th section  
          void    CalculatePoint( double & u, double & v, bool ext, MbCartPoint3D & point ) const;
          void    CalculateExplore( double & u, double & v, bool ext,
                                    MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                                    MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer ) const;
          void    CalculateSurface( double & u, double & v, bool ext, uint uDeg, uint vDeg, 
                                    MbVector3D & der ) const;
          void    CalculateLikeLofted( double & u, double & v, bool ext, 
                                       size_t uDer, size_t vDer, MbCartPoint3D & point ) const;
          void    ExploreLikeLofted( double & u, double & v, bool ext,
                                     MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                                     MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer ) const;
  inline  void    CheckParam( double & u, double & v, bool ext ) const; 
          void    CheckParam( double & u, bool ext ) const;

          void    operator = ( const MbElevationSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbElevationSurface )
};

IMPL_PERSISTENT_OPS( MbElevationSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры. \en Check parameters. 
// ---
inline void MbElevationSurface::CheckParam( double & u, double & v, bool ext ) const 
{
  if ( !ext ) { // \ru Внутри параметрического прямоугольника. \en Inside of the region of parameters.
    if ( (u < umin) || (u > umax) ) {
      if ( uclosed ) {
        double uRgn = umax - umin;
        u -= ::floor((u - umin) / uRgn) * uRgn;
      }
      else {
        if ( u < umin ) 
          u = umin;
        else
          u = umax;
      }
    }

    if ( (v < vmin) || (v > vmax) ) {
      if ( vclosed ) {
        double vRgn = vmax - vmin;
        v -= ( ::floor((v - vmin) / vRgn) * vRgn );
      }
      else {
        if ( v < vmin ) 
          v = vmin;
        else
          v = vmax;
      }
    }
  }
  else { // \ru Вне параметрического прямоугольника. \en Outside of the region of parameters.
    if ( u < umin && GetPoleUMin() ) {
      u = umin;
    }
    else if ( u > umax && GetPoleUMax() ) {
      u = umax;
    }
    if ( v < vmin && GetPoleVMin() ) {
      v = vmin;
    }
    else if ( v > vmax && GetPoleVMax() ) {
      v = vmax;
    }
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Cоздать параметр для заданной кривой
           \en Create parameter for specified curve \~
  \details \ru Кривая-профиль должна быть плоской. Если направляющая пересекается с плоскостью профиля,
  в качестве параметра принимается координата вдоль направляющей точки пересечения ее с плоскостью профиля, 
  ближайшей к центру масс профильной кривой. \n
  Если направляющая не пересекается с плоскостью профиля, в качестве параметра используется координата на направляющей
  проекции центра масс профильной кривой на направляющую.
           \en Profile curve should be planar. If guide curve intersects with plane of profile,
  then as parameter is used the coordinate along guide curve of intersection point of it with plane of profile 
  which is nearest to center of mass of profile curve. \n
  If guide curve not intersects with plane of profile, then as parameter is used the coordinate on guide curve
  of projection of center of mass of profile curve onto guide curve. \~
  \param[in] crvThis - \ru Профильная кривая.
                       \en The profile curve. \~
  \param[in] spine - \ru Направляющая.
                     \en The spine (guide) curve. \~
  \param[in,out] wcThis - \ru Центр масс профильной кривой.
                          \en Center of mass of profile curve. \~
  \param[in,out] ct - \ru Искомый параметр.
                      \en Required parameter. \~
  \param[in,out] tau - \ru Производная направляющей в точке с координатой ct. Если в функцию передать NULL, производная не вычисляется.
                       \en Derivative of guide curve at point with 'ct' coordinate. If giving NULL to function, then derivative isn't calculated. \~
  \return \ru true - если направляющая пересекается с плоскостью профиля, false - если не пересекается.
          \en True - if guide curve intersects with plane of profile, false - if not intersects. \~ 
  \ingroup Algorithms_3D
*/
// ---
bool CreateElevationParam( const MbCurve3D & crvThis, const MbCurve3D & spine,
                           MbCartPoint3D & wcThis, double & ct, MbVector3D * tau );


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
  \param[in] spine - \ru Направляющая.
                     \en The spine (guide) curve. \~
  \param[in,out] vParams - \ru Множество параметров.
                           \en Set of parameters. \~
  \param[in,out] tiePnts - \ru Множество центров масс профильных кривых. Не заполняется, если в функцию передать NULL.
                           \en Set of centers of mass of profile curves. If giving NULL to function, then it isn't filled. \~
  \return \ru true - если массив параметров успешно создан.
          \en True - if the array of parameters successfully created. \~ 
  \ingroup Algorithms_3D
*/
// ---
bool CreateElevationParams( RPArray<MbCurve3D> & uCurves, bool vcls, const MbCurve3D & spine,
                            SArray<double> & vParams, SArray<MbCartPoint3D> * tiePnts );


#endif // __SURF_ELEVATION_SURFACE_H
