////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Линейчатая поверхность.
         \en Ruled surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_RULED_SURFACE_H
#define __SURF_RULED_SURFACE_H


#include <surf_swept_surface.h>
#include <math_define.h>


class  MATH_CLASS MbMatrix;
class  MATH_CLASS MbConeSurface;
class  MATH_CLASS MbExtrusionSurface;


//------------------------------------------------------------------------------
/** \brief \ru Линейчатая поверхность.
           \en Ruled surface. \~
  \details \ru Линейчатая поверхность построена по двум кривым путём соединения их соответствующих точек отрезками прямой. 
 	  Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = (1 - v) curve(u) + v sline(w(u)). \n
    Первый параметр поверхности совпадает с параметром кривой curve. 
    Параметр w кривой sline пропорционален первому параметру поверхности. 
    Вдоль второго параметра поверхность прямолинейна.
           \en A ruled surface is constructed on two curves by connection of its corresponding points by linear segments. 
 	  Radius-vector of surface is described by the vector function \n
    r(u,v) = (1 - v) curve(u) + v sline(w(u)). \n
    First parameter of surface coincides with parameter of 'curve' curve. 
    Parameter w of 'sline' curve is proportional to first parameter of surface. 
    Surface is linear along the second parameter. \~ 
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbRuledSurface : public MbSweptSurface {
public:

  /** \brief \ru Типы линейчатой поверхности.
             \en Types of ruled surface. \~
  */
  enum RuledSurfaceType {
    rld_Unset = 0, ///< \ru Тип поверхности не установлен. \en Surface type isn't set. 
    rld_Planar,    ///< \ru Геометрия плоскости. \en Planar. 
    rld_Line,      ///< \ru Образующие кривые прямолинейны. \en Generating curves are straight lines. 
    rld_Cone,      ///< \ru Геометрия конической поверхности. \en Conical surface. 
    rld_PoleMin,   ///< \ru Кривая curve вырождена в точку. \en 'curve' curve is degenerated to a point. 
    rld_PoleMax,   ///< \ru Кривая sline вырождена в точку. \en 'sline' curve is degenerated to a point. 
    rld_Offset,    ///< \ru Геометрия поверхности выдавливания с уклоном. \en Extrusion surface with taper. 
    rld_Swept,     ///< \ru Геометрия поверхности выдавливания. \en Extrusion surface. 
    rld_Arbitrary, ///< \ru Произвольная линейчатая поверхность. \en Arbitrary ruled surface. 
  };

private:
  RuledSurfaceType type;          ///< \ru Тип линейчатой поверхности. \en Type of ruled surface. 
  MbCurve3D *      sline;         ///< \ru Вторая образующая кривая (первой является curve). \en The second generating curve ('curve' is first one). 
  double           tmin;          ///< \ru Начальный параметр sline. \en Start parameter of 'sline'. 
  double           dt;            ///< \ru Производная параметра кривой sline по параметру u (dt * (u - umin) = t_sline - tmin_sline). \en Derivative of parameter of 'sline' curve by u parameter (dt * (u - umin) = t_sline - tmin_sline). 
  bool             poleMin;       ///< \ru Полюс при umin. \en Pole at umin. 
  bool             poleMax;       ///< \ru Полюс при umax. \en Pole at umax. 
  double           uMinNormDelta; // \ru Отступ при наличии касательного полюса umin. \en Indent in the presence of umin tangent pole. 
  double           uMaxNormDelta; // \ru Отступ при наличии касательного полюса umax. \en Indent in the presence of umax tangent pole. 
  double           uminExt;       // \ru Минимальное разрешенное значение по u. \en Minimal allowed value by u. 
  double           umaxExt;       // \ru Максимальное разрешенное значение по u. \en Maximal allowed value by u. 
  double           vminExt;       // \ru Минимальное разрешенное значение по v. \en Minimal allowed value by v. 
  double           vmaxExt;       // \ru Максимальное разрешенное значение по u. \en Maximal allowed value by v. 

public:

  /** \brief \ru Конструктор по двум кривым.
             \en Constructor by two curves. \~
    \details \ru Конструктор по двум кривым.
             \en Constructor by two curves. \~
    \param[in] c1 - \ru Первая образующая кривая
                    \en First generating curve \~
    \param[in] c2 - \ru Вторая образующая кривая.
                    \en Second generating curve. \~
    \param[in] same - \ru Признак использования оригинала образующих кривых, а не их копий.
                      \en Attribute of usage of original of generating curves, not a copies. \~
  */
  MbRuledSurface( const MbCurve3D & c1, const MbCurve3D & c2, bool same );
  
  /** \brief \ru Конструктор по двум кривым и параметрам по V.
             \en Constructor by two curves and parameters by V. \~
    \details \ru Конструктор по двум кривым и параметрам по V.\n
      Используется только в конвертерах.
             \en Constructor by two curves and parameters by V.\n
      Used only in converters. \~
    \param[in] vin - \ru Минимальный параметр по V
                     \en Minimal parameter by V \~
    \param[in] vax - \ru Максимальный параметр по V
                     \en Maximal parameter by V \~
    \param[in] c1 - \ru Первая образующая кривая
                    \en First generating curve \~
    \param[in] c2 - \ru Вторая образующая кривая
                    \en Second generating curve \~        
  */
  // \ru Используется только в конверторах для эллипса и цилиндра в orthosur \en Used only in converters for ellipse and cylinder in 'orthosur' 
  MbRuledSurface( double vin, double vax, const MbCurve3D & c1, const MbCurve3D & c2 ); 

protected:
  MbRuledSurface( const MbRuledSurface &, MbRegDuplicate * );
public:
  virtual ~MbRuledSurface ();

public:
  VISITING_CLASS( MbRuledSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  
  virtual void    GetProperties( MbProperties &properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties &properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems ( RPArray <MbSpaceItem> & ); // \ru Дать базовые объекты. \en Get the base objects. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual void    Refresh(); // \ru Сбросить все временные данные. \en Reset all temporary data. 

  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetUPeriod() const; // \ru Вернуть период. \en Return period. 
  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.   
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of surfaces correct parameters
            when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en The point on the surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const;
  virtual void    Normal   ( double & u, double & v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void    NormalU  ( double & u, double & v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
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
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void   _NormalU  ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalUU ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalUV ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalVV ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
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

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v. 

  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя. \en Changing of carrier. 

  // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection onto the surface.
  virtual bool    NearPointProjection( const MbCartPoint3D & p, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const;

  // \ru Пересечение с кривой. \en Intersection with curve. 
  virtual void    CurveIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                     bool ext0, bool ext, bool touchInclude = false ) const;

  virtual void    CalculateGabarit( MbCube & ) const; // \ru Выдать габарит. \en Get the bounding box. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к.. \en Calculate bounding box relative to the local coordinate system. 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const;
  virtual MbSurface *       Offset( double d, bool same ) const;  // \ru Построить смещенную поверхность. \en Create a shifted surface. 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en Spatial copy of 'v = const'-line. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 
  virtual MbCurve3D * CurveUV( const MbLineSegment &, bool bApprox = true ) const; // \ru Пространственная копия линии по параметрической линии. \en Spatial copy of line by parametric line. 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  virtual bool    GetCylinderAxis( MbAxis3D &axis ) const; // \ru Дать ось вращения для поверхности \en Get a rotation axis of a surface 
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Подобные ли поверхности для объединения (слива). Специальный случай. Для внутреннего использования. \en Whether the surfaces are similar to merge. Special case. For internal use only. 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;

  // \ru Существует ли полюс на границе параметрической области сплайновой кривой. \en Whether there is pole on boundary of parametric region of spline curve. 
  virtual bool    GetPoleUMin() const;
  virtual bool    GetPoleUMax() const;
  virtual bool    GetPoleVMin() const;
  virtual bool    GetPoleVMax() const;
  virtual bool    IsPole( double u, double v ) const; // \ru Является ли точка особенной. \en Whether the point is special. 
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю. \en If true, then all the derivatives by U higher the first one are equal to zero. 
  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю. \en If true, then all the derivatives by V higher the first one are equal to zero. 
  /** \} */
  /** \ru \name Функции движения по поверхности
      \en \name Functions of moving along the surface
      \{ */
  /// \ru Дать вторую образующую кривую. \en Get second generating curve. 
  const   MbCurve3D & GetSline() const { return *sline; } 
  /// \ru Дать вторую образующую кривую для изменения. \en Get second generating curve for changing. 
          MbCurve3D & SetSline()       { return *sline; } 

  /// \ru Тип линейчатой поверхности. \en Type of ruled surface.    
  inline  RuledSurfaceType  GetType() const { C3D_ASSERT( type != rld_Unset ); return type; } 
  /// \ru Обновить тип линейчатой поверхности. \en Update type of ruled surface.
  inline  void              UpdateType();
  /** \} */

  inline  double  SlineParameterFrom( const double & u ) const;
  inline  double  SlineParameterInto( const double & t ) const;

private:  
  inline  void    CheckParam( double & u, double & v ) const; // \ru Проверить параметры. \en Check parameters. 
  inline  void    CheckPoleParam( double & u, double & v ) const; 

          void              InitNormDeltaU(); // \ru Посчитать величины отступа от uMin и uMax при подсчете нормали \en Calculate indent values from uMin and uMax in calculation of normal 
          void              InitTabooUV();    // \ru Вычислить ограничения по u и v \en Calculate constraints by u and v 
          // \ru Пересечение с прямолинейной кривой \en Intersection with rectilinear curve 
          bool              StraightIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                                  bool ext0, bool ext ) const;
          RuledSurfaceType  CheckType();
          MbConeSurface *   GetConeSurface() const;
          bool              IsPlane() const; // \ru НЕ ИСПОЛЬЗОВАТЬ СНАРУЖИ !!! \en NOT USE OUTSIDE !!! 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbRuledSurface )
OBVIOUS_PRIVATE_COPY( MbRuledSurface )
};

IMPL_PERSISTENT_OPS( MbRuledSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры \en Check parameters 
// ---
inline void MbRuledSurface::CheckParam( double & u, double & v ) const
{
  if (u < umin) {
    if ( uclosed ) {
      double pRgn = ( umax - umin );
      u -= ( ::floor((u - umin) / pRgn) * pRgn );      
    }
    else
      u = umin;
  }
  else if ( u > umax) {
    if ( uclosed ) {
      double pRgn = ( umax - umin );
      u -= ( ::floor((u - umin) / pRgn) * pRgn );      
    }
    else
      u = umax;
  }
  if ( v < vmin )
    v = vmin;
  else if ( v > vmax )
    v = vmax;
}


//------------------------------------------------------------------------------
// \ru Корректировка параметров \en Correct parameters 
// ---
inline void MbRuledSurface::CheckPoleParam( double & u, double & v ) const
{
  if ( (type == rld_PoleMin) && (v < vmin) )
    v = vmin;
  else if ( v < vminExt )
    v = vminExt;

  if ( (type == rld_PoleMax) && (v > vmax) )
    v = vmax;
  else if ( v > vmaxExt )
    v = vmaxExt;

  if ( u < umin ) {
    if ( poleMin )
      u = umin;
    else if ( u < uminExt )
      u = uminExt;
  }
  if ( u > umax ) {
    if ( poleMax )
      u = umax;
    else if ( u > umaxExt )
      u = umaxExt;
  }
}


//------------------------------------------------------------------------------
// \ru Обновить тип линейчатой поверхности. \en Update type of ruled surface.
// ---
inline void MbRuledSurface::UpdateType()
{
  type = rld_Unset;
  CheckType();
}


//------------------------------------------------------------------------------
// \ru Перевод параметра curve в параметр sline \en Convert 'curve' parameter to 'sline' parameter 
// ---
inline double MbRuledSurface::SlineParameterFrom( const double & u ) const {
  return tmin + (u - umin) * dt;
}


//------------------------------------------------------------------------------
// \ru Перевод параметра sline в параметр curve \en Convert 'sline' parameter to 'curve' parameter 
// ---
inline double MbRuledSurface::SlineParameterInto( const double & t ) const {
  double du = (::fabs(dt) > EXTENT_EQUAL) ? 1.0 / dt : 1.0;
  return umin + (t - tmin) * du;
}


//------------------------------------------------------------------------------
// \ru Являются ли поверхости геометрически одинаковыми \en Whether surfaces are similar 
// ---
bool IsSameRuledExtrusion( const MbRuledSurface & ruled, const MbExtrusionSurface & extrusion,
                           MbMatrix * matr );


#endif // __SURF_RULED_SURFACE_H
