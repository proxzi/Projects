////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Спиральная поверхность.
         \en Spiral surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_SPIRAL_SURFACE_H
#define __SURF_SPIRAL_SURFACE_H


#include <surf_swept_surface.h>
#include <mb_placement3d.h>
#include <mb_matrix3d.h>


class  MATH_CLASS  MbConeSpiral;


//------------------------------------------------------------------------------
/** \brief \ru Спиральная поверхность.
           \en Spiral surface. \~
  \details \ru Спиральная поверхность получена путем движения образующей кривой curve по цилиндрической спирали.
    Спиральная поверхность является частным случаем кинематической поверхности.
    Ось спирали направлена вдоль оси Z локальной системы координат. 
    Второй параметр поверхности отсчитывается от оси position.axisX локальной системы координат. 
 	  Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = position.origin + (M(v) (curve(u) - origin)), \n
    где M(v) - матрица вращения. \n
    Первый параметр поверхности совпадает с параметром образующей кривой. 
    Второй параметр поверхности совпадает с углом поворота точки спирали вокруг её оси.
           \en A spiral surface is obtained by moving of a generating curve along a cylindrical spiral.
    Spiral surface is a special case of sweep surface.
    A spiral axis is directed along the Z-axis of the local coordinate system. 
    The second parameter of a surface is measured from the axis "position.axisX" of the local coordinate system. 
 	  Radius-vector of the surface is described by the vector function \n
    r(u,v) = position.origin + (M(v) (curve(u) - origin)), \n
    where M(v) is rotation matrix. \n
    The first surface parameter coincides with the parameter of generatrix. 
    The second surface parameter coincides with rotation angle of a spiral point around its axis. \~ 
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbSpiralSurface : public MbSweptSurface {
private:
  MbPlacement3D  position; ///< \ru Местная система координат (position.axisZ - ось спирали). \en Local coordinate system ('position.axisZ' is axis of spiral). 
  double         radius;   ///< \ru Радиус спирали. \en A spiral radius. 
  double         step;     ///< \ru Шаг спирали. \en A pitch of spiral. 
  MbCartPoint3D  origin;   ///< \ru Центр тяжести образующей. \en Center of gravity of generatrix. 
  MbMatrix3D     into;     ///< \ru Матрица преобразования в систему position. \en Matrix of transformation to the system 'position'. 
  MbMatrix3D     from;     ///< \ru Матрица преобразования из системы position. \en Matrix of transformation from the system 'position'. 
  double         stepd2pi; ///< \ru Шаг приходящийся на период. \en A step corresponding to period. 
                               
public:

  /** \brief \ru Конструктор по образующей, локальной системе координат, радиусу спирали, шагу спирали.
             \en Constructor by generatrix, local coordinate system, spiral radius and spiral pitch. \~
    \details \ru Конструктор по образующей, локальной системе координат, радиусу спирали, шагу спирали.
             \en Constructor by generatrix, local coordinate system, spiral radius and spiral pitch. \~
    \param[in] c - \ru Образующая
                   \en Generatrix \~
    \param[in] pos - \ru Локальная система координат
                     \en Local coordinate system \~
    \param[in] r - \ru Радиус спирали
                   \en Spiral radius \~
    \param[in] s - \ru Шаг спирали
                   \en Spiral pitch \~
    \param[in] t1 - \ru Начальный параметр спирали
                    \en Start parameter of spiral \~
    \param[in] t2 - \ru Конечный параметр спирали
                    \en End parameter of spiral \~
    \param[in] sameCurve - \ru Признак использования оригинала образующей, а не ее копии
                           \en Attribute of using the original of generatrix instead of its copy. \~
  */
  MbSpiralSurface( const MbCurve3D & c, const MbPlacement3D & pos, double r, double s, double t1, double t2,
                   bool sameCurve );
  
  /** \brief \ru Конструктор по образующей и спирали.
             \en Constructor by generatrix and spiral. \~
    \details \ru Конструктор по образующей и спирали.
             \en Constructor by generatrix and spiral. \~
    \param[in] c - \ru Образующая
                   \en Generatrix \~
    \param[in] s - \ru Спираль
                   \en Spiral \~
    \param[in] sameCurve - \ru Признак использования оригинала образующей, а не ее копии
                           \en Attribute of using the original of generatrix instead of its copy. \~
  */
  MbSpiralSurface( const MbCurve3D & c, const MbConeSpiral & s, bool sameCurve );

protected:
  MbSpiralSurface( const MbSpiralSurface &, MbRegDuplicate * );
private:
  MbSpiralSurface( const MbSpiralSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbSpiralSurface();

public:
  VISITING_CLASS( MbSpiralSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг. \en Translation. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты. \en Get the base objects. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров. 
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... correct parameters
            when getting out of rectangular domain bounds.
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en A point on surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const;
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface domain.
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when getting out of rectangular domain bounds.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности. \en A point on extended surface. 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const;
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const;
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  /** \} */
  /** \ru \name Функции движения по поверхности
      \en \name Functions of moving on surface
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
      \en \name Common functions of surface.
      \{ */
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна линии по u. \en Curvature of line in u direction. 
  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской. \en Whether a surface is planar.         
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of surface. 
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности \en Creation of an offset surface 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en A spatial copy of the line v = const. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en A spatial copy of the line u = const. 

  // \ru Найти проекцию точки на поверхность. \en Find the projection of a point onto the surface. 
  virtual bool    NearPointProjection  ( const MbCartPoint3D & pnt, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;

  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces are similar to merge. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric region to the parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine a splitting of parametric region of a surface by verticals and horizontals. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const; 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the number of polygons in u-direction. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the number of polygons in v-direction. 

  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю. \en If it equals true then all derivatives with respect to u which have more than first order are equal to null. 
  /** \} */
  /** \ru \name Функции спиральной поверхности
      \en \name Functions of spiral surface
      \{ */     

          /** \brief \ru Определение матрицы переноса для образующей.
                     \en Determination of a transfer matrix for generatrix. \~
            \details \ru Определение матрицы при переносе образующей
              из параметра vmin в параметр v.
                     \en Determination of matrix when transferring the generatrix
              from the parameter vmin to the parameter v. \~
            \param[in] v - \ru Новый параметр на спирали
                           \en A new parameter on the spiral \~
            \param[out] matr - \ru Матрица-резцультат
                               \en A matrix - the result \~       
          */
          void    TransformMatrix( double v, MbMatrix3D & matr ) const;

          /// \ru Внутренний радиус витков. \en Internal radius of coils. 
          double  GetSpiralR() const { return radius; } 
          /// \ru Внутренний шаг витков. \en Internal pitch of coils. 
          double  GetStep()    const { return step; }   

          /// \ru Физический радиус витков. \en Physical radius of coils. 
          double  GetSpiralRadius() const; 
          /// \ru Физический шаг витков. \en Physical pitch of coils. 
          double  GetSpiralStep() const;   

  /// \ru Местная система координат (ось position.axisZ - ось спирали). \en Local coordinate system ('position.axisZ' is axis of spiral). 
  const   MbPlacement3D & GetPlacement() const { return position; } 
  /// \ru Центр тяжести образующей. \en Center of gravity of generatrix. 
  const   MbCartPoint3D & GetOrigin()    const { return origin; } 

          /// \ru Построить спираль. \en Construct a spiral.  
          MbConeSpiral  & CreateSpiral() const; 

          /// \ru Является ли локальная система координат поверхности ортонормированной. \en Whether the local coordinate system of a surface is orthonormalized. 
          bool    IsPositionNormal()    const { return ( position.IsNormal()    ); } 
          /// \ru Является ли локальная система координат поверхности ортогональной с равными по длине осями X,Y. \en Whether the local coordinate system of a surface is orthogonal with X and Y axes equal by length. 
          bool    IsPositionCircular()  const { return ( position.IsCircular()  ); }
          /// \ru Является ли локальная система координат поверхности ортогональной и изотропной по осям. \en Whether the local coordinate system of a surface is orthogonal and isotropic by the axes. 
          bool    IsPositionIsotropic() const { return ( position.IsIsotropic() ); }
          /// \ru Является ли образующая кривая окружностью. \en Whether a generatrix is a circle. 
          bool    IsCircleType() const;

          /// \ru Оценить рабочий диапазон для проецирования. \en Estimate the projection range along V.
          bool    GetProjectionRange( const MbCartPoint3D & pnt, bool ext, const MbRect2D * userRange, MbRect2D & resRange ) const;
          /// \ru Скорректировать разбивку для проецирования точки. \en Correct the number of splittings by v-parameter for point projection.
          bool    CorrectVCount( double vbeg, double vend, size_t & cntv ) const;
  /** \} */  
private:

          void    Init(); // \ru Инициализация. \en Initialization.    
  inline  void    CheckParam     ( double & v ) const;
  inline  void    RotateVector   ( const double & sin_V, const double & cos_V, MbVector3D &  ) const;
  inline  void    RotateDeriveV  ( const double & sin_V, const double & cos_V, MbVector3D &  ) const;
  inline  void    RotateDeriveVV ( const double & sin_V, const double & cos_V, MbVector3D &  ) const;
  inline  void    RotateDeriveVVV( const double & sin_V, const double & cos_V, MbVector3D &  ) const;
  inline  void    DirectrixPointOn  ( const double & v, const double & sinV, const double & cosV, MbCartPoint3D & ) const;
  inline  void    DirectrixDeriveV  ( const double & sinV, const double & cosV, MbVector3D &  ) const;
  inline  void    DirectrixDeriveVV ( const double & sinV, const double & cosV, MbVector3D &  ) const;
  inline  void    DirectrixDeriveVVV( const double & sinV, const double & cosV, MbVector3D &  ) const;

          void    operator = ( const MbSpiralSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSpiralSurface )
};

IMPL_PERSISTENT_OPS( MbSpiralSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметр \en Check parameter 
// ---
inline void MbSpiralSurface::CheckParam( double & v ) const
{
  if ( v < vmin )
    v = vmin;
  else
  if ( v > vmax )
    v = vmax;
}


//------------------------------------------------------------------------------
// \ru Выдать физический радиус спирали \en Get physical radius of spiral 
// ---
inline double MbSpiralSurface::GetSpiralStep() const
{
  if ( position.IsNormal() )
    return step;
  else if ( position.IsOrthogonal() ) {
    return (step * position.GetAxisZ().Length());
  }
  return 0.0;
}


//------------------------------------------------------------------------------
// \ru Поворот вектора вокруг оси спирали \en Rotation of vector around spiral axis 
// ---
inline void MbSpiralSurface::RotateVector( const double & sin_V, const double & cos_V, MbVector3D & _vector ) const
{
  _vector.Transform( into );
  double x =   (_vector.x * cos_V) - (_vector.y * sin_V);
  double y =   (_vector.x * sin_V) + (_vector.y * cos_V);
  _vector.x = x;
  _vector.y = y;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Первая производная поворота вектора вокруг оси спирали \en First derivative of vector rotation around the spiral axis 
// ---
inline void MbSpiralSurface::RotateDeriveV( const double & sin_V, const double & cos_V, MbVector3D & _vector ) const
{
  _vector.Transform( into );
  double x = - (_vector.x * sin_V) - (_vector.y * cos_V);
  double y =   (_vector.x * cos_V) - (_vector.y * sin_V);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Вторая производная поворота вектора вокруг оси спирали \en Second derivative of vector rotation around spiral axis 
// ---
inline void MbSpiralSurface::RotateDeriveVV( const double & sin_V, const double & cos_V, MbVector3D & _vector ) const
{
  _vector.Transform( into );
  double x = - (_vector.x * cos_V) + (_vector.y * sin_V);
  double y = - (_vector.x * sin_V) - (_vector.y * cos_V);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Третья производная поворота вектора вокруг оси спирали \en Third derivative of vector rotation around spiral axis 
// ---
inline void MbSpiralSurface::RotateDeriveVVV( const double & sin_V, const double & cos_V, MbVector3D & _vector ) const
{
  _vector.Transform( into );
  double x =   (_vector.x * sin_V) + (_vector.y * cos_V);
  double y = - (_vector.x * cos_V) + (_vector.y * sin_V);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


//------------------------------------------------------------------------------
// \ru Точка спирали \en A point of spiral 
// ---
inline void MbSpiralSurface::DirectrixPointOn( const double & v, const double & sinV, const double & cosV, MbCartPoint3D & p ) const {
  p = position.GetOrigin();
  p.Add( position.GetAxisZ(), (stepd2pi * v), position.GetAxisX(), (radius * cosV), position.GetAxisY(), (radius * sinV) );
}


//-------------------------------------------------------------------------------
// \ru Первая производная спирали \en First derivative of spiral 
// ---
inline void MbSpiralSurface::DirectrixDeriveV( const double & sinV, const double & cosV, MbVector3D & d ) const {
  d.Set( position.GetAxisZ(), stepd2pi, position.GetAxisX(), -(radius * sinV), position.GetAxisY(), (radius * cosV) );
}


//-------------------------------------------------------------------------------
// \ru Вторая производная спирали \en Second derivative of spiral 
// ---
inline void MbSpiralSurface::DirectrixDeriveVV( const double & sinV, const double & cosV, MbVector3D & d ) const {
  d.Set( position.GetAxisX(), -(radius * cosV), position.GetAxisY(), -(radius * sinV) );
}


//-------------------------------------------------------------------------------
// \ru Третья производная спирали \en Third derivative of spiral 
// ---
inline void MbSpiralSurface::DirectrixDeriveVVV( const double & sinV, const double & cosV, MbVector3D & d ) const {
  d.Set( position.GetAxisX(), (radius * sinV), position.GetAxisY(), -(radius * cosV) );
}


#endif // __SURF_SPIRAL_SURFACE_H
