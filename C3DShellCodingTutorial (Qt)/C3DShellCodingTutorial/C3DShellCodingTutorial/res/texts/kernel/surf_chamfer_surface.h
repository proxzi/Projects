////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность-фаска.
         \en Chamfer surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_CHAMFER_SURFACE_H
#define __SURF_CHAMFER_SURFACE_H


#include <surf_smooth_surface.h>


//------------------------------------------------------------------------------
/** \brief \ru Поверхность фаски.
           \en Chamfer surface. \~
  \details \ru Поверхность фаски является линейчатой поверхностью,
    построенной по двут кривым на сопрягаемых поверхностях: curve1 и curve2. 
    Первый параметр поверхности совпадает с параметром кривых curve1 и curve2.
    Второй параметр изменяется от нуля (точки совпадают с curve1) до единицы (точки совпадают с curve2).
    В отличие от других поверхностей функции PointOn и Derive... поверхность фаски не корректирует
    первый параметр при выходе его за пределы области определения.
    Сечение поверхности вдоль её второго параметра будет отрезком прямой.
           \en Chamfer surface is ruled surface
    constructed from two curves on the mating surfaces: curve1 and curve2. 
    The first surface parameter coincides with the parameter of curves curve1 and curve2.
    The second parameter is changed from zero (points coincide with curve1) to unit (points coincide with curve2).
    In contrast to other surfaces functions PointOn and Derive ... chamfer surface does not correct
    the first parameter when it is out of domain bounds.
    Section of surface along its second parameter is a line segment. \~
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbChamferSurface : public MbSmoothSurface {

public:
  /** \brief \ru Конструктор по двум кривым, катетам и типу сопряжения.
             \en Constructor by two curves, cathetuses and type of mate. \~ 
    \details \ru Конструктор по двум кривым, катетам и типу сопряжения.
             \en Constructor by two curves, cathetuses and type of mate. \~ 
    \param[in] curv1 - \ru Опорная кривая на первой поверхности
                       \en Support curve on the first surface \~ 
    \param[in] curv2 - \ru Опорная кривая на второй поверхности
                       \en Support curve on the second surface \~ 
    \param[in] d1 - \ru Катет(или угол в зависимости от типа сопряжения) со знаком для поверхности кривой curv1
                    \en Cathetus(or angle according to the type of mate) with the sign for surface of curve curv1 \~
    \param[in] d2 - \ru Катет(или угол в зависимости от типа сопряжения) со знаком для поверхности кривой curv2
                    \en Cathetus(or angle according to the type of mate) with the sign for surface of curve curv2 \~
    \param[in] fm - \ru Тип сопряжения: 
               st_Chamfer - фаска с заданными катетами
               st_Slant1 - фаска по катету и углу
               st_Slant2 - фаска по углу и катету
                    \en Mate type: 
               st_Chamfer - chamfer with given cathetuses
               st_Slant1 - chamfer by cathetus and angle
               st_Slant2 - chamfer by angle and cathetus \~
  */
  MbChamferSurface( MbSurfaceCurve & curv1, MbSurfaceCurve & curv2, double d1, double d2, MbeSmoothForm fm );
  
  /** \brief \ru Конструктор по двум кривым, катетам и типу сопряжения.
             \en Constructor by two curves, cathetuses and type of mate. \~ 
    \details \ru Конструктор по двум кривым, катетам и типу сопряжения.
             \en Constructor by two curves, cathetuses and type of mate. \~ 
    \param[in] surf1 - \ru Первая поверхность
                       \en The first surface \~
    \param[in] curv1 - \ru Кривая в параметрах первой поверхности
                       \en Curve in parameters of the first surface \~ 
    \param[in] surf2 - \ru Вторая поверхность
                       \en The second surface \~
    \param[in] curv2 - \ru Кривая в параметрах второй поверхности
                       \en Curve in parameters of the second surface \~ 
    \param[in] d1 - \ru Катет(или угол в зависимости от типа сопряжения) со знаком для поверхности кривой curv1
                    \en Cathetus(or angle according to the type of mate) with the sign for surface of curve curv1 \~
    \param[in] d2 - \ru Катет(или угол в зависимости от типа сопряжения) со знаком для поверхности кривой curv2
                    \en Cathetus(or angle according to the type of mate) with the sign for surface of curve curv2 \~
    \param[in] fm - \ru Тип сопряжения: 
               st_Chamfer - фаска с заданными катетами
               st_Slant1 - фаска по катету и углу
               st_Slant2 - фаска по углу и катету
                    \en Mate type: 
               st_Chamfer - chamfer with given cathetuses
               st_Slant1 - chamfer by cathetus and angle
               st_Slant2 - chamfer by angle and cathetus \~
  */
  MbChamferSurface( MbSurface & surf1, MbCurve & curv1,
                    MbSurface & surf2, MbCurve & curv2, double d1, double d2, MbeSmoothForm fm );

protected:
  MbChamferSurface( const MbChamferSurface &, MbRegDuplicate * );
  MbChamferSurface( const MbChamferSurface * ); // \ru Конструктор копирования с теми же опорными поверхностями для CurvesDuplicate(). \en Copy constructor with the same support surfaces for CurvesDuplicate(). 

private:
  MbChamferSurface( const MbChamferSurface & ); // \ru Не реализовано. \en Not implemented. 

public:
  virtual ~MbChamferSurface ();

public:
  VISITING_CLASS( MbChamferSurface );

  /** \ru \name Функции инициализации
      \en \name Initialization functions
      \{ */
  virtual void    Init0( double wmin, double wmax, bool insertPoints = true );
  /** \} */
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Cделать копию элемента. \en Make a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией. \en Whether the object is a copy. 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Cделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );    // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );    // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 

  virtual void    GetProperties( MbProperties &properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties &properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems( RPArray <MbSpaceItem> &s ); // \ru Дать базовые поверхности. \en Get base surfaces. 

  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn и Derive... поверхностей сопряжения не корректируют
            первый параметр при его выходе за пределы определения параметров.
      \en \name Functions for working at domain of surface
            Functions PointOn and Derive...of smooth surfaces don't correct
            the first parameter when it is out of domain bounds.
      \{ */
  virtual void    PointOn  ( double &u, double &v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en The point on the surface. 
  virtual void    DeriveU  ( double &u, double &v, MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void    DeriveV  ( double &u, double &v, MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void    DeriveUU ( double &u, double &v, MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void    DeriveVV ( double &u, double &v, MbVector3D & ) const; // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void    DeriveUV ( double &u, double &v, MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void    DeriveUUU( double &u, double &v, MbVector3D & ) const;
  virtual void    DeriveUUV( double &u, double &v, MbVector3D & ) const;
  virtual void    DeriveUVV( double &u, double &v, MbVector3D & ) const;
  virtual void    DeriveVVV( double &u, double &v, MbVector3D & ) const;
  virtual void    Normal   ( double &u, double &v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void    NormalV  ( double &u, double &v, MbVector3D & ) const;
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct 
            parameters when they are out of rectangular domain bounds.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности. \en The point on the extended surface. 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const;
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const;
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
  /** \} */
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна вдоль v. \en Curvature along v. 

  virtual MbSurface * Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Creation of an offset surface. 
  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru Построить NURBS копию поверхности. \en Construct a NURBS copy of the surface. 

  virtual MbCurve3D * CurveV( double u, MbRect1D *pRrn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 

  virtual bool    GetCylinderAxis( MbAxis3D &axis ) const; // \ru Дать ось вращения для поверхности. \en Get a rotation axis of a surface. 

  virtual void    ChangeCarrier( const MbSpaceItem &item, MbSpaceItem &init ); // \ru Изменение носителя. \en Changing of carrier. 
  virtual bool    ChangeCarrierBorne( const MbSurface & item, MbSurface & init, const MbMatrix & matr ); // \ru Изменение носимых элементов. \en Change carrier elements. 
  virtual double  GetSmoothRadius() const; // \ru Дать радиус. \en Get radius. 
  virtual void    GetDistances( double u, double &d1, double &d2 ) const; // \ru Дать радиусы со знаком. \en Get radii with a sign. 
  virtual double  GetDistance( bool s ) const; // \ru Дать радиус со знаком. \en Get radius with a sign. 
  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской. \en Whether a surface is planar. 
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric domain to the parametric domain of surf. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  
  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons along u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons along v. 
  
  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю. \en If true, then all the derivatives along V are equal to zero. 
  /** \} */
  /** \ru \name Функции поверхности сопряжения
      \en \name Functions of smooth surface
      \{ */
  virtual MbSmoothSurface & CurvesDuplicate() const; // \ru Копия с теми же опорными поверхностями. \en Copy with the same support surfaces. 
  // \ru Объединить поверхности путём включения поверхности init в данную поверхность. \en Unite surface by inclusion of 'init' surface to the given surface. 
  virtual bool    SurfacesCombine( const MbSurfaceIntersectionCurve & edge, 
                                   const MbSurface & init, bool add, MbMatrix & matr,
                                   const MbSurfaceIntersectionCurve * seam ); 
  //virtual void    InsertPointsToCurves( double u ); // \ru Добавить точки в опорные кривые поверхности. \en Add points to support curves of surface. 

  /** \} */
private:
          void    operator = ( const MbChamferSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbChamferSurface )
};

IMPL_PERSISTENT_OPS( MbChamferSurface )

#endif // __SURF_CHAMFER_SURFACE_H
