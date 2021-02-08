////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность на ограничивающем контуре.
         \en The surface on the bounding contour. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_GREGORY_SURFACE_H
#define __SURF_GREGORY_SURFACE_H


#include <surface.h>
#include <curve3d.h>
#include <math_define.h>
#include <templ_dptr.h>


class MATH_CLASS  MbContour3D;
class MbTriWorkingData;


//------------------------------------------------------------------------------
/** \brief \ru Поверхность на ограничивающем контуре.
           \en The surface on the bounding contour. \~
  \details \ru Поверхность, построенная на замкнутом контуре.
    Поверхность определяется замкнутым контуром из n, n>1, пространственных кривых и состоит из n патчей,
    G1-гладко стыкующихся между собой. Каждый патч является модификацией четырехугольной поверхности Грегори.
    В вершинах патча нарушается равенство смешанных производных.
           \en The surface defined by closed contour.
    The surface is defined by closed contour of n, n>1, spacial curves and consists of n patches connected in such
    a way to satisfy G1-continuity. Every patch is the modification of quadrilateral Gregory surface.
    At the vertex of patch the equality of mixed derivatives is not fulfilled. \~
  \ingroup Surfaces
*/ 
// ---
class MATH_CLASS MbGregorySurface : public MbSurface {
  class MbGregoryWorkingData;
private:
  size_t sn;                     ///< \ru Количество сторон многоугольника. \en The sides count of polygon.
  RPArray<MbCurve3D> contour;    ///< \ru Границы многоугольника. \en The polygon boundaries.
  SArray<MbeMatingType> conjug;  ///< \ru Тип сопряжения вдоль границы. \en Conjugation type along the curve.
  RPArray<MbCurve3D> radial;     ///< \ru Кривые от заданной точки до сторон многоугольника. \en Curves from given point to polygon sides.
  DPtr<MbGregoryWorkingData> gd; ///< \ru Расчетные данные поверхности. \en Surface computational data. 

public:
  /** \brief \ru Конструктор поверхности.
             \en Constructor of surface. \~
  \details \ru Конструктор поверхности на ограничивающем контуре.
           \en Constructor of surface on the bounding contour. \~
      \param[in] initContour - \ru Контур.
                               \en The contour. \~
  */
  MbGregorySurface( const MbContour3D & initContour, const SArray<MbeMatingType> * conj = NULL );
protected:
  /// \ru Конструктор-копия. \en Copy constructor. 
  MbGregorySurface( const MbGregorySurface &, MbRegDuplicate * ); 
public:
  virtual ~MbGregorySurface();

public:
  VISITING_CLASS( MbGregorySurface );
  
  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Make a copy of element. 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией. \en Whether the object is a copy. 
  virtual bool    SetEqual( const MbSpaceItem & init );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const;  // \ru Являются ли объекты подобными. \en Whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL );         // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix 
  virtual void    Move( const MbVector3D &to, MbRegTransform * = NULL );                 // \ru Сдвиг. \en Translation 
  virtual void    Rotate( const MbAxis3D &axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis 
  virtual void    Refresh(); // \ru Сбросить все временные данные. \en Flush all the temporary data. 

  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems   ( RPArray<MbSpaceItem>   & ); // \ru Дать базовые объекты. \en Get the base objects. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */

  /** \ru \name Функции описания области определения поверхности.
      \en \name Functions for surface domain description.
      \{ */
  virtual double  GetUMin() const;
  virtual double  GetVMin() const;
  virtual double  GetUMax() const;
  virtual double  GetVMax() const;

  virtual bool    IsUClosed() const;  // \ru Замкнута ли гладко поверхность по параметру u без учета граничного контура. \en Whether the surface is smoothly closed by parameter u without regard to the boundary contour. 
  virtual bool    IsVClosed() const;  // \ru Замкнута ли гладко поверхность по параметру v без учета граничного контура. \en Whether the surface is smoothly closed by parameter v without regard to the boundary contour. 
  virtual bool    IsUTouch() const;  // \ru Замкнута ли фактически поверхность по параметру u независимо от гладкости. \en Whether the surface is actually closed by parameter u regardless of the smoothness. 
  virtual bool    IsVTouch() const;  // \ru Замкнута ли фактически поверхность по параметру v независимо от гладкости. \en Whether the surface is actually closed by parameter v regardless of the smoothness. 
  virtual bool    IsUPeriodic() const;  // \ru Замкнута ли гладко поверхность по параметру u. \en Whether the surface is smoothly closed by parameter u. 
  virtual bool    IsVPeriodic() const;  // \ru Замкнута ли гладко поверхность по параметру v. \en Whether the surface is smoothly closed by parameter v. 
  virtual double  GetUPeriod() const; // \ru Вернуть период для замкнутой поверхности или 0. \en Return period for closed surface or 0. 
  virtual double  GetVPeriod() const; // \ru Вернуть период для замкнутой поверхности или 0. \en Return period for closed surface or 0. 

  virtual size_t  GetUCount() const;
  // \ru Существует ли полюс на границе параметрической области. \en Whether there is pole on boundary of parametric region. 
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
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & p ) const; // \ru Точка на поверхности \en Point on the surface 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & p ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & p ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & p ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & p ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & p ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void    Normal   ( double & u, double & v, MbVector3D & p ) const; // \ru Нормаль \en Normal 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & p ) const; // \ru Точка на поверхности \en Point on the surface 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & p ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & p ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & p ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & p ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & p ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUUV( double u, double v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUVV( double u, double v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveVVV( double u, double v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _Normal   ( double u, double v, MbVector3D & p ) const; // \ru Нормаль \en Normal 
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  /** \} */

  /** \ru \name Функции движения по поверхности.
      \en \name Functions of moving along the surface.
      \{ */
  virtual double  StepU         ( double u, double v, double sag ) const; // \ru Вычисление шага параметра u по по величине прогиба. \en Calculation of parameter u step by the value of sag.  
  //virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага параметра v по по величине прогиба. \en Calculation of parameter v step by the value of sag. 
  virtual double  DeviationStepU( double u, double v, double ang ) const; // \ru Вычисление шага параметра u по углу отклонения нормали \en Calculation of parameter u step by the angle of deviation of normal 
  //virtual double  DeviationStepV( double u, double v, double ang ) const; // \ru Вычисление шага параметра v по углу отклонения нормали \en Calculation of parameter v step by the angle of deviation of normal 
  /** \} */

    /** \ru \name Общие функции поверхности.
      \en \name Common functions of surface.
      \{ */
  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v.
  /** \} */

private:
          // \ru Проверить параметры и в случае выхода за пределы загнать в область определения.
          // \en Check parameters and if it is out of limits, then move it to domain.
          void    CheckParams( double & u, double & v ) const;
          // \ru Проверить параметры и в случае захода за полюс или выходе за период загнать в область определения.
          // \en Check parameters and if it is out of pole or it is out of period, then drive it to the domain region. 
          void    CheckParamsEx( double & u, double & v ) const;

          // \ru Определить местные координаты области поверхности. \en Determine local coordinates of surface region. 
          void    LocalCoordinate( double u, double v, double & ul, double & vl, size_t & i, MbTriWorkingData * pd ) const;
          // \ru Вычислить вспомогательные векторы производных в узлах кривых. \en Calculate auxiliary vectors of derivatives at nodes of curves. 
          void    CalculateVertex( const size_t & i, MbTriWorkingData * pd ) const;
          // \ru Вычислить вспомогательные вектора производных вдоль кривых патча. \en Calculate auxiliary vectors of derivatives along curves of patch. 
          void    CalculateAlong0( const double & ul, const double & vl, const size_t & patch, MbTriWorkingData * pd ) const;
          void    CalculateAlong1( const double & ul, const size_t & patch, MbTriWorkingData * pd ) const;
          void    CalculateAlong2( const double & vl, const size_t & patch, MbTriWorkingData * pd ) const;
          // \ru Производные в локальных координатах. \en Derivatives in the local coordinates.
          void    DerU  ( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
          void    DerV  ( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
          void    DerUU ( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
          void    DerVV ( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
          void    DerUV ( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Вторая производная по uv. \en Second derivative with respect to uv. 
          void    DerUUU( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Третья производная. \en Third derivative.
          void    DerUUV( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Третья производная. \en Third derivative. 
          void    DerUVV( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Третья производная. \en Third derivative. 
          void    DerVVV( const double & ul, const double & vl, MbTriWorkingData * pd, MbVector3D & vect ) const; // \ru Третья производная. \en Third derivative.
          // \ru Вычислить нормаль. \en Normal calculation.
          void    ExactNormal( double u, double v, const MbVector3D & derU, const MbVector3D & derV, MbVector3D & norm ) const;


DECLARE_PERSISTENT_CLASS_NEW_DEL( MbGregorySurface )
OBVIOUS_PRIVATE_COPY( MbGregorySurface )
}; // MbGregorySurface

IMPL_PERSISTENT_OPS( MbGregorySurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры и в случае выхода за пределы загнать в область определения. \en Check parameters and if it is out of limits, then move it to domain.
// ---
inline void MbGregorySurface::CheckParams( double & u, double & v ) const
{
  if ( (u  > -EXTENT_EPSILON && u < 0.0) || (u >= static_cast<double>(sn) && u < static_cast<double>(sn) + EXTENT_EPSILON) )
    u = 0.0;
  else if ( (u < 0.0) || (u >= static_cast<double>(sn)) )
    u -= ::floor( u / static_cast<double>(sn) ) * static_cast<double>(sn);
  if ( v < 0.0 )
    v = 0.0;
  else if ( v > 1.0 )
    v = 1.0;
}


//------------------------------------------------------------------------------
// \ru Проверить параметры и в случае захода за полюс или выходе за период загнать в область определения. \en Check parameters and if it is out of pole or it is out of period, then drive it to the domain region. 
// ---
inline void MbGregorySurface::CheckParamsEx( double & u, double & v ) const
{
  if ( (u  > -EXTENT_EPSILON && u < 0.0) || (u >= static_cast<double>(sn) && u < static_cast<double>(sn) + EXTENT_EPSILON) )
    u = 0.0;
  else if ( (u < 0.0) || (u >= static_cast<double>(sn)) )
    u -= ::floor( u / static_cast<double>(sn) ) * static_cast<double>(sn);
  if ( v < 0.0 )
    v = 0.0;
}

#endif // __SURF_GREGORY_SURFACE_H
