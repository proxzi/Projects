////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность выдавливания.
         \en Extrusion surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_EXTRUSION_SURFACE_H
#define __SURF_EXTRUSION_SURFACE_H


#include <surf_swept_surface.h>


class  MATH_CLASS MbLine3D;
class  MATH_CLASS MbOffsetSurface;


//------------------------------------------------------------------------------
/** \brief \ru Поверхность выдавливания.
           \en Extrusion surface. \~
  \details \ru Поверхность выдавливания является кинематической поверхностью с прямолинейной образующей. 
 	  Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = curve(u) + (direction distance v). \n
    Первый параметр поверхности совпадает с параметром образующей кривой.
           \en Extrusion surface is swept surface with rectilinear generating curve. 
 	  Radius-vector of surface is described by the vector function \n
    r(u,v) = curve(u) + (direction distance v). \n
    First parameter of surface coincides with parameter of generating curve. \~ 
  \ingroup Surfaces
*/ 
// ---
class MATH_CLASS MbExtrusionSurface : public MbSweptSurface {
protected:
  MbVector3D direction; ///< \ru Направление выдавливания, единичный вектор. \en Direction of extrusion, vector of unit length. 
  double     distance;  ///< \ru Длина выдавливания. \en Length of extrusion. 

public:
  /** \brief \ru Конструктор по образующей и направлению выдавливания.
             \en Constructor by generating curve and direction of extrusion. \~
    \details \ru Конструктор по образующей и направлению выдавливания.
             \en Constructor by generating curve and direction of extrusion. \~
    \param[in] curve - \ru Образующая поверхности выдавливания
                       \en Generating curve of extrusion surface \~
    \param[in] vector - \ru Направление выдавливания
                        \en Direction of extrusion \~
    \param[in] same - \ru Использование оригинала кривой, а не ее копии
                      \en Usage of original of curve, not a copy \~
  */
  MbExtrusionSurface ( const MbCurve3D & curve, const MbVector3D & vector, bool same );
  
  /** \brief \ru Конструктор по прямой, точке и образующей.
             \en Constructor by line, point and generating curve. \~
    \details \ru Конструктор по прямой, точке и образующей.\n
      Используется только в конвертерах.
             \en Constructor by line, point and generating curve.\n
      Used only in converters. \~
  */
  MbExtrusionSurface( const MbLine3D &, const MbCartPoint3D &, MbCurve3D &, bool same );

public:
  virtual ~MbExtrusionSurface();

protected:
  MbExtrusionSurface( const MbExtrusionSurface &, MbRegDuplicate * );

private:
  MbExtrusionSurface( const MbExtrusionSurface & ); // \ru Не реализовано. \en Not implemented. 

public:
  VISITING_CLASS( MbExtrusionSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );          // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.\n 
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of surfaces correct parameters
            when they are out of bounds of rectangular domain of parameters.\n 
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en The point on the surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const;
  virtual void    NormalV  ( double & u, double & v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности. \en The point on the extended surface. 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const;
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
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
  virtual double  StepU         ( double u, double v, double sag ) const; // \ru Вычисление шага по u по заданной стрелке прогиба. \en Calculation of the parameter step in u direction by the sag. 
  virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага по v по заданной стрелке прогиба. \en Calculation of the parameter step in v direction by the sag. 
  virtual double  DeviationStepU( double u, double v, double angle ) const; // \ru Вычисление шага по u по заданному углу отклонения. \en Calculation of the parameter step in u direction by the deviation angle. 
  virtual double  DeviationStepV( double u, double v, double angle ) const; // \ru Вычисление шага по v по заданному углу отклонения. \en Calculation of the parameter step in v direction by the deviation angle. 
  virtual double  MetricStepU   ( double u, double v, double length ) const; // \ru Вычисление шага по u по заданной длине. \en Calculation of the parameter step in u direction by the given length. 
  virtual double  MetricStepV   ( double u, double v, double length ) const; // \ru Вычисление шага по v по заданной длине. \en Calculation of the parameter step in v direction by the given length. 
  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  /** \} */
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна линии по u. \en Curvature of line by u. 
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна линии v. \en Curvature of v-line. 

  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской. \en Whether the surface is planar. 
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя. \en Changing of carrier. 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Create an offset surface. 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en Spatial copy of 'v = const'-line. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 

  virtual ThreeStates Salient() const; // \ru Выпуклая ли поверхность. \en Whether a surface is convex. 

  // \ru Проекция точки на поверхность. \en The point projection onto the surface. 
  virtual bool    NearPointProjection  ( const MbCartPoint3D & p, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection onto the surface. 
  // \ru Пересечение с кривой. \en Intersection with curve. 
  virtual void    CurveIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                     bool ext0, bool ext, bool touchInclude = false ) const;

  virtual void    CalculateGabarit( MbCube & ) const; // \ru Выдать габарит. \en Get the bounding box. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  virtual bool    GetCylinderAxis( MbAxis3D & axis ) const; // \ru Дать ось вращения для поверхности. \en Get a rotation axis of a surface. 
  virtual bool    GetCenterLines( std::vector<MbCurve3D *> & clCurves ) const; // \ru Дать осевые (центральные) линии для поверхности. \en Get center lines of a surface.
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  
  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const; // \ru Является ли поверхность скруглением. \en Whether the surface is fillet. 
  virtual MbeParamDir GetFilletDirection() const; // \ru Направление поверхности скругления. \en Direction of fillet surface. 

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;  

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v.    
  virtual void    SetLimit( double u1, double v1, double u2, double v2 ); 
  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю. \en If true, then all the derivatives by U higher the first one are equal to zero. 
  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю. \en If true, then all the derivatives by V higher the first one are equal to zero.    
  /** \} */
  /** \ru \name Функции поверхности выдавливания.
      \en \name Functions of extrusion surface.
      \{ */
    /// \ru Направление выдавливания. \en A direction of extrusion. 
    const MbVector3D & GetDirection() const { return direction; } 
          /// \ru Длина выдаливания. \en A length of extrusion.  
          double  GetDistance () const { return distance;  } 
          /// \ru Изменить направление выдавливания на противоположное. \en Change direction of extrusion to opposite. 
          void    InvertDirection() { direction.Invert(); SetDirtyGabarit(); } 

          /** \brief \ru Создание эквидистантной поверхности.
                     \en Create an offset surface. \~
            \details \ru Создание поверхности типа st_OffsetSurface, совпадающей с данной поверхностью.\n
              Если образующая кривая является эквидистантной кривой на плоскости, 
              то, используя ее базовую кривую в качестве образующей, создается поверхность
              выдавливания и по ней эквидистантная поверхность.\n
              Поверхность строится в случае, если направление выдавливания
              перпендикулярно плоскости образующей кривой.\n
              Используется только в конвертерах.
                     \en Create surface of st_OffsetSurface type coinciding with current surface.\n
              If generating curve is offset curve on plane, 
              then using its base curve as generating curve the extrusion surface
              and offset surface by it are created.\n
              Surface is created if direction of extrusion
              is perpendicular to plane of generating curve.\n
              Used only in converters. \~
          */
          MbOffsetSurface * GetSurfaceFromPlaneCurveOffset() const;
  /** \} */

private:
          // \ru Пересечение с прямолинейной кривой. \en Intersection with rectilinear curve. 
          bool    StraightIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, bool ext0, bool ext ) const;
          void    operator = ( const MbExtrusionSurface & ); // \ru Не реализовано. \en Not implemented. 
protected:
  inline  void    CheckParam( double &u, double &v ) const; // \ru Проверить параметры. \en Check parameters. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbExtrusionSurface )
};

IMPL_PERSISTENT_OPS( MbExtrusionSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры. \en Check parameters. 
// ---
inline void MbExtrusionSurface::CheckParam( double & u, double & v ) const
{
  if ( u < umin ) {
    if ( uclosed ) {
      double uRgn = ( umax - umin );
      u -= ( ::floor((u - umin) / uRgn) * uRgn );
    }
    else
      u = umin;
  }

  if ( u > umax ) {
    if ( uclosed ) {
      double uRgn = ( umax - umin );
      u -= ( ::floor((u - umin) / uRgn) * uRgn );
    }
    else
      u = umax;
  }

  if ( v < vmin )
    v = vmin;
  if ( v > vmax )
    v = vmax;
}


#endif // __SURF_EXTRUSION_SURFACE_H
