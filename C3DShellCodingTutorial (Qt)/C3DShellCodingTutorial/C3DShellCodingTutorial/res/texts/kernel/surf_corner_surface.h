////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Треугольная поверхность на сетке из трех кривых.
         \en Triangular surface on grid of three curves. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_CORNER_SURFACE_H
#define __SURF_CORNER_SURFACE_H


#include <surface.h>


#define CORNER_COUNT 3 ///< \ru Число кривых, нужных для построения треугольной поверхности. \en Count of curves used to construct triangular surface. 
#define VECT_CNT     CORNER_COUNT   


class  MATH_CLASS   MbContour3D;


//------------------------------------------------------------------------------
/** \brief \ru Треугольная поверхность на кривых.
           \en Triangular surface on curves. \~
  \details \ru Треугольная поверхность на сетке из трех кривых. 
    Кривые должны попарно пересекаться или иметь точки скрещения. 
    Если кривые попарно пересекаются, то поверхность проходит через определяющиее её кривые. \n
           \en Triangular surface on grid of three curves. 
    Curves have to be intersected pairwise or have crossing points. 
    If curves are intersected pairwise then surface passes through its determining curves. \n \~
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbCornerSurface : public MbSurface {
//                                                          P2
//                                                    t1max ^* t0min
//             R(s0,s1,s2) =                               /  *
//   (curve2(1-s1)+curve1(s2)-P0)*s0+                     /    *
//   (curve0(1-s2)+curve2(s0)-P1)*s1+                    /      *
//   (curve1(1-s0)+curve0(s1)-P2)*s2             curve1 /        * curve0
//                                                     /    R     * 
//   s0(u,v) + s1(u,v) + s2(u,v) = 1                  /            *
//     R(0,s1,s2) = curve0(s1)                       /              *
//     R(s0,0,s2) = curve1(s2)                t1min <----------------v t0max
//     R(s0,s1,0) = curve2(s0)                  P0                     P1
//                                                t2max   curve2   t2min 
//
// \ru s0,s1,s2 - Барицентрические (треугольные) координаты, \en S0,s1,s2 - Baricentric (triangular) coordinates.
// \ru P0 - полюс \en P0 - pole
private:
  MbCurve3D   * curve0;     ///< \ru Кривая  0. \en Curve 0. 
  MbCurve3D   * curve1;     ///< \ru Кривая  1. \en Curve 1. 
  MbCurve3D   * curve2;     ///< \ru Кривая  2. \en Curve 2. 
  MbCartPoint3D vertex[CORNER_COUNT]; ///< \ru Вершины P0, P1, P2. \en Vertices P0, P1, P2. 
  double        t0min;      ///< \ru Минимальное значение параметра на кривой  0. \en Minimal value of parameter on curve 0. 
  double        t0max;      ///< \ru Максимальное значение параметра на кривой 0. \en Maximal value of parameter on curve 0. 
  double        t1min;      ///< \ru Минимальное значение параметра на кривой  1. \en Minimal value of parameter on curve 1. 
  double        t1max;      ///< \ru Максимальное значение параметра на кривой 1. \en Maximal value of parameter on curve 1. 
  double        t2min;      ///< \ru Минимальное значение параметра на кривой  2. \en Minimal value of parameter on curve 2. 
  double        t2max;      ///< \ru Максимальное значение параметра на кривой 2. \en Maximal value of parameter on curve 2. 

public:
  /** \brief \ru Конструктор треугольной поверхности.
             \en Constructor of triangular surface. \~
      \details \ru Конструктор треугольной поверхности по набору кривых.
               \en Constructor of triangular surface by set of curves. \~
      \param[in] initCurve0 - \ru Кривая 0.
                              \en Curve 0. \~
      \param[in] initCurve1 - \ru Кривая 1.
                              \en Curve 1. \~
      \param[in] initCurve2 - \ru Кривая 2.
                              \en Curve 2. \~
  */
  MbCornerSurface ( const MbCurve3D & initCurve0, const MbCurve3D & initCurve1, const MbCurve3D & initCurve2 );
private:
  MbCornerSurface( const MbCornerSurface & ); // \ru Не реализовано. \en Not implemented. 
  MbCornerSurface( const MbCornerSurface & init, MbRegDuplicate * );
public:
  virtual ~MbCornerSurface( void );

public:
  VISITING_CLASS( MbCornerSurface );

  /// \ru Инициализация треугольной поверхности заданной треугольной поверхностью. \en Initialization of triangular surface by given triangular surface. 
          void    Init( const MbCornerSurface &init );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Cделать копию элемента \en Make a copy of element 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;    // \ru Является ли объект копией. \en Whether the object is a copy. 
  virtual bool    SetEqual( const MbSpaceItem & init );        // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move( const MbVector3D & to, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void    CalculateSurfaceWire( const MbStepData & stepData, size_t beg, MbMesh & mesh, 
                                        size_t uMeshCount = c3d::WIRE_MAX, size_t vMeshCount = c3d::WIRE_MAX ) const;

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem>   & ); // \ru Дать базовые объекты \en Get the base objects 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetUMin() const;
  virtual double  GetVMin() const;
  virtual double  GetUMax() const;
  virtual double  GetVMax() const;
  virtual bool    IsUClosed() const; // \ru Замкнута ли поверхность по параметру u. \en Whether the surface is closed by parameter u. 
  virtual bool    IsVClosed() const; // \ru Замкнута ли поверхность по параметру v. \en Whether the surface is closed by parameter v. 
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
  virtual void    TangentV ( double & u, double & v, MbVector3D & p ) const;
  virtual void    Normal   ( double & u, double & v, MbVector3D & p ) const; // \ru Нормаль \en Normal 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void   _PointOn  ( double  u, double  v, MbCartPoint3D & p ) const; // \ru Точка на расширенной поверхности \en Point on the extended surface 
  virtual void   _DeriveU  ( double  u, double  v, MbVector3D & p ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void   _DeriveV  ( double  u, double  v, MbVector3D & p ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void   _DeriveUU ( double  u, double  v, MbVector3D & p ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void   _DeriveVV ( double  u, double  v, MbVector3D & p ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void   _DeriveUV ( double  u, double  v, MbVector3D & p ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void   _DeriveUUU( double  u, double  v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUUV( double  u, double  v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUVV( double  u, double  v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveVVV( double  u, double  v, MbVector3D & p ) const; // \ru Третья производная \en Third derivative 
  virtual void   _TangentV ( double  u, double  v, MbVector3D & p ) const;
  virtual void   _Normal   ( double  u, double  v, MbVector3D & p ) const; // \ru Нормаль \en Normal 
  virtual void   _NormalV  ( double  u, double  v, MbVector3D & p ) const; // \ru Производная нормали \en Derivative of normal 
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
  virtual double  StepU( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по U \en Calculation of the approximation step with consideration of the curvature radius by U 
  virtual double  StepV( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по V \en Calculation of the approximation step with consideration of the curvature radius by V 
  virtual double  DeviationStepU( double u, double v, double ang ) const; ///< \ru Вычисление шага параметра u по углу отклонения нормали \en Calculation of parameter u step by the angle of deviation of normal 
  virtual double  DeviationStepV( double u, double v, double ang ) const; ///< \ru Вычисление шага параметра v по углу отклонения нормали \en Calculation of parameter v step by the angle of deviation of normal 

  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  /** \} */

  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool doApprox = true ) const; // \ru Пространственная копия линии v = const \en Spatial copy of 'v = const'-line 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool doApprox = true ) const; // \ru Пространственная копия линии u = const \en Spatial copy of 'u = const'-line 

  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 
  // \ru Существует ли полюс на границе параметрической области \en Whether there is pole on boundary of parametric region 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u \en Get the count of polygons by u 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v \en Get the count of polygons by v 

  /// \ru Получить кривую 0. \en Get curve 0. 
  const   MbCurve3D & GetCurve0() const { return *curve0; } 
  /// \ru Получить кривую 1. \en Get curve 1. 
  const   MbCurve3D & GetCurve1() const { return *curve1; } 
  /// \ru Получить кривую 2. \en Get curve 2. 
  const   MbCurve3D & GetCurve2() const { return *curve2; } 
  /// \ru Получить кривую по индексу. \en Get curve by an index. 
  const   MbCurve3D * GetCurve( size_t ind ) const; 
          /// \ru Получить количество кривых. \en Get count of curves. 
          size_t  GetCurvesCount() const { return 3; } //-V112
  const   MbCartPoint3D * GetVertex() const { return vertex; } ///< \ru Выдать вершины P0, P1, P2. \en Get vertices P0, P1, P2. 
          double  GetT0Min() const { return t0min; } ///< \ru Минимальное значение параметра на кривой  0. \en Minimal value of parameter on curve 0. 
          double  GetT0Max() const { return t0max; } ///< \ru Максимальное значение параметра на кривой 0. \en Maximal value of parameter on curve 0. 
          double  GetT1Min() const { return t1min; } ///< \ru Минимальное значение параметра на кривой  1. \en Minimal value of parameter on curve 1. 
          double  GetT1Max() const { return t1max; } ///< \ru Максимальное значение параметра на кривой 1. \en Maximal value of parameter on curve 1. 
          double  GetT2Min() const { return t2min; } ///< \ru Минимальное значение параметра на кривой  2. \en Minimal value of parameter on curve 2. 
          double  GetT2Max() const { return t2max; } ///< \ru Максимальное значение параметра на кривой 2. \en Maximal value of parameter on curve 2. 
          double  GetTMin( size_t ind ) const; ///< \ru Минимальное  значение параметра на кривой с индексом ind. \en Get The minimal value of parameter on curve by index. 
          double  GetTMax( size_t ind ) const; ///< \ru Максимальное значение параметра на кривой с индексом ind. \en Get The maximal value of parameter on curve by index. 
  /** \} */

private:
          void    Init();
  inline  void    CalculateCoordinate( double & u,  double & v,  bool ext,
                                       double & s0, double & s1, double & s2,
                                       double & c0, double & c1, double & c2,
                                       double & t0, double & t1, double & t2 ) const;
          void    CalculatePoint ( double & u, double & v, bool ext,
                                   MbCartPoint3D & point ) const;
          void    CalculateFirst ( double & u, double & v, bool ext,
                                   MbVector3D * first ) const;
          void    CalculateSecond( double & u, double & v, bool ext, 
                                   MbVector3D * second ) const;
          void    CalculateThird ( double & u, double & v, bool ext, 
                                   MbVector3D * second, MbVector3D * third ) const;
          void    CalculateExplore( double & u, double & v, bool ext, 
                                    MbCartPoint3D * point, MbVector3D * first, MbVector3D * second ) const;
          bool    GetNormalFactor( MbVector3D & norm ) const; // \ru Нормаль в точке с параметрами u=0. \en Normal at u=0. 
          void    Derivatives( double u, double v, bool ext, MbVector3D & uDer, MbVector3D & vDer ) const; // \ru Ппроизводные. \en Derivatives with respect to u and to v.
          void    operator = ( const MbCornerSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCornerSurface )
}; // MbCornerSurface

IMPL_PERSISTENT_OPS( MbCornerSurface )

//------------------------------------------------------------------------------
// \ru Определение местных координат \en Determination of local coordinates 
// ---
inline void MbCornerSurface::CalculateCoordinate( double & u,  double & v,  bool ext,
                                                  double & s0, double & s1, double & s2,
                                                  double & c0, double & c1, double & c2,
                                                  double & t0, double & t1, double & t2 ) const
{
  if ( !ext ) {
    if ( v <-1.0 ) v =-1.0;
    if ( u > 1.0 ) u = 1.0;
    if ( v > 1.0 ) v = 1.0;
  }
  if (u < 0.0) 
    u = 0.0; // \ru Нельзя заходить за полюс. \en Is impossible to go behind a pole 

  s0 = 1.0 - u;
  s1 = 0.5 * (u - u*v);
  s2 = 0.5 * (u + u*v);
// \ru Пересчет параметров u,v в параметры a,b,c \en Recalculation of u,v parameters to a,b,c parameters 
//
//      v    c=1
//   +1 |   /|
//      |  / |
// curve1 /  | curve0
//      |/   |
//   a=1+----+--> u
//      |\   |1
// curve2 \  |
//      |  \ |
//   -1 |   \|
//      |    b=1
//
  c0 = t0min*(1.0-s1) + t0max*s1;
  c1 = t1min*(1.0-s2) + t1max*s2;
  c2 = t2min*(1.0-s0) + t2max*s0;
  t0 = t0min*s2 + t0max*(1.0-s2);
  t1 = t1min*s0 + t1max*(1.0-s0);
  t2 = t2min*s1 + t2max*(1.0-s1);

  //if ( u < PARAM_EPSILON ) {
  //  if ( vc> PARAM_EPSILON && v> PARAM_EPSILON ) 
  //    v = 1.0;
  //  else
  //  if ( vc<-PARAM_EPSILON && v<-PARAM_EPSILON ) 
  //    v =-1.0;
  //}
}


//------------------------------------------------------------------------------
// \ru Получить кривую по индексу \en Get curve by an index 
// ---
inline const MbCurve3D * MbCornerSurface::GetCurve( size_t ind ) const
{
  if ( ind >= CORNER_COUNT )
    ind = ind % CORNER_COUNT;
  switch ( ind ) {
    case 0 : { return curve0; }
    case 1 : { return curve1; }
    case 2 : { return curve2; }
  }
  return NULL;
}


//------------------------------------------------------------------------------
// \ru Минимальное  значение параметра на кривой с индексом ind. \en Get The minimal value of parameter on curve by index. 
// ---
inline double MbCornerSurface::GetTMin( size_t ind ) const
{
  if ( ind >= CORNER_COUNT )
    ind = ind % CORNER_COUNT;
  switch ( ind ) {
    case 0 : { return t0min; }
    case 1 : { return t1min; }
    case 2 : { return t2min; }
  }
  return UNDEFINED_DBL;
}


//------------------------------------------------------------------------------
// \ru Максимальное значение параметра на кривой с индексом ind. \en Get The maximal value of parameter on curve by index. 
// ---
inline double MbCornerSurface::GetTMax( size_t ind ) const
{
  if ( ind >= CORNER_COUNT )
    ind = ind % CORNER_COUNT;
  switch ( ind ) {
    case 0 : { return t0max; }
    case 1 : { return t1max; }
    case 2 : { return t2max; }
  }
  return UNDEFINED_DBL;
}


#endif // __SURF_CORNER_SURFACE_H
