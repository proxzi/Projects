////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность скругления с постоянными радиусами обычная или с сохранением кромки.
         \en Fillet surface of constant radii, ordinary or with preservation of fillet. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_FILLET_SURFACE_H
#define __SURF_FILLET_SURFACE_H


#include <surf_smooth_surface.h>


class  MATH_CLASS  MbFunction;


//------------------------------------------------------------------------------
/** \brief \ru Поверхность скругления с постоянными радиусами обычная или с сохранением кромки.
           \en Fillet surface of constant radii, ordinary or with preservation of fillet. \~
  \details \ru Поверхность скругления является NURBS-поверхностью,
    построенной по трём кривым: curve1, curve0, curve2. 
    Первый параметр поверхности совпадает с параметром кривых curve1, curve0, curve2.
    Второй параметр изменяется от нуля (точки совпадают с curve1) до единицы (точки совпадают с curve2).
    В отличие от других поверхностей Функции PointOn и Derive... поверхность скругления не корректирует
    первый параметр при выходе его за пределы области определения.
    Если коэффициент формы conic = _ARC_ ( 0 ), то вес каждой точки кривой curve0 задаётся функцией weights0 и
    вычислен так, что сечение поверхности вдоль её второго параметра будет дугой окружности,
    то есть при любом параметре u три точки curve1(u), curve0(u), curve2(u) определяют NURBS-кривую в форме дуги окружности. 
    Если коэффициент формы conic != _ARC_, то вес каждой точки кривой curve0 равен conic / ( 1.0 - conic ). 
    При conic = 0.5 сечение поверхности вдоль её второго параметра будет параболой. \n
           \en Fillet surface is NURBS-surface
    constructed by three curves: curve1, curve0, curve2. 
    First parameter of surface coincides with parameter of curve1, curve0, curve2 curves.
    Second parameter is changed between 0 (points are coincident to curve1) and 1 (points are coincident to curve2).
    For fillet surface in contrast to other surfaces PointOn and Derive... functions don't correct
    first parameter when it is out of domain bounds.
    If coefficient of shape conic = _ARC_ ( 0 ), then weight of each point of curve0 curve is given by weights0 function and
    is calculated as that the section of surface along its second parameter will be a circular arc,
    that is three points curve1(u), curve0(u), curve2(u) determine NURBS-curve with shape of circular arc at any u parameter. 
    If coefficient of shape conic != _ARC_, then weight of each point of curve0 curve is equal to conic / ( 1.0 - conic ). 
    If conic = 0.5, then section of surface along its second parameter will be a parabola. \n \~
  \ingroup Surfaces
*/// ---
class MATH_CLASS MbFilletSurface : public MbSmoothSurface {
protected:
  MbCurve3D  * curve0;    ///< \ru Кривая пересечения касательных к поверхностям - всегда не NULL. \en Intersection curve of tangents to surfaces - always not NULL. 
  MbFunction * weights0;  ///< \ru Функция веса точек средней кривой curve0. \en Function of weight of points of curve0 mid-curve. 
  double       conic;     ///< \ru Коэффициент формы, изменяется от 0.05 до 0.95, определяет вес точек кривой curve0. \en Coefficient of shape is changed between 0.05 and 0.95 and determines weight of points of curve0 curve. 
  bool         even;      ///< \ru Равномерная параметризация по дуге или нет. \en Whether arc length parameterization is uniform or not. 
  bool         equable;   ///< \ru true - обычная поверхность, false - curve1 или curve2 является кромкой. \en True - ordinary surface, false - curve1 or curve2 is fillet. 
  bool         byCurve1;  ///< \ru true - curve2 является кромкой, false - curve1 является кромкой. \en True - curve2 is fillet, false - curve1 is fillet. 
  MbCurve3D  * spine;     ///< \ru Кривая центров дуг окружности для случая равномерной параметризации. \en Curve of centers of circular arcs in case of uniform parameterization. 
  MbVector3D * spineDerUMin;  // \ru Производные spine в точках uMin и uMax ( для случая равномерной параметризации ). \en Derivatives of spine at uMin and uMax points (in case of uniform parameterization). 
  MbVector3D * spineDerUMax;  // \ru Производные spine в точках uMin и uMax ( для случая равномерной параметризации ). \en Derivatives of spine at uMin and uMax points (in case of uniform parameterization). 

public:

  /** \brief \ru Конструктор поверхности скругления.
             \en Constructor of fillet surface. \~ 
    \details \ru Конструктор поверхности скругления.
             \en Constructor of fillet surface. \~ 
    \param[in] curv1 - \ru Опорная кривая на первой поверхности
                       \en Support curve on the first surface \~ 
    \param[in] curv2 - \ru Опорная кривая на второй поверхности
                       \en Support curve on the second surface \~ 
    \param[in] d1 - \ru Радиус скругления со знаком для поверхности кривой curve1
                    \en Fillet radius with sign for surface of crve1 curve \~
    \param[in] d2 - \ru Радиус скругления со знаком для поверхности кривой curve2
                    \en Fillet radius with sign for surface of crve2 curve \~
    \param[in] fm - \ru Тип сопряжения: \n 
               st_Span - скругление с заданной хордой
               st_Fillet - скругление с заданными радиусами
                    \en Conjugation type: \n 
               st_Span - fillet with a given chord
               st_Fillet - fillet with given radii \~      
    \param[in] cn - \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0 - дуга окружности)
                    \en Coefficient of shape is changed between 0.05 and 0.95 (if 0 - circular arc) \~
    \param[in] ev - \ru Равномерная параметризация по дуге или нет
                    \en Whether arc length parameterization is uniform or not \~
  */
  MbFilletSurface( MbSurfaceCurve & curv1, MbSurfaceCurve & curv2,
                   double d1, double d2, MbeSmoothForm fm, double cn, bool ev );
  
  /** \brief \ru Конструктор поверхности с сохранением кромки.
             \en Constructor of surface with preservation of fillet. \~ 
    \details \ru Конструктор поверхности с сохранением кромки.
             \en Constructor of surface with preservation of fillet. \~ 
    \param[in] curv1 - \ru Опорная кривая на первой поверхности
                       \en Support curve on the first surface \~ 
    \param[in] curv2 - \ru Опорная кривая на второй поверхности
                       \en Support curve on the second surface \~ 
    \param[in] d1 - \ru Радиус скругления со знаком для поверхности кривой crve1
                    \en Fillet radius with sign for surface of crve1 curve \~
    \param[in] d2 - \ru Радиус скругления со знаком для поверхности кривой crve2
                    \en Fillet radius with sign for surface of crve2 curve \~
    \param[in] fm - \ru Тип сопряжения: \n
               st_Span - скругление с заданной хордой \n
               st_Fillet - скругление с заданными радиусами
                    \en Conjugation type: \n
               st_Span - fillet with a given chord\n
               st_Fillet - fillet with given radii \~    
    \param[in] cn - \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0 - дуга окружности)
                    \en Coefficient of shape is changed between 0.05 and 0.95 (if 0 - circular arc) \~
    \param[in] byFirst - \ru true - кривая curve2 является кромкой, false - кривая curve1 является кромкой
                         \en True - curve2 curve is fillet, false - curve1 curve is fillet. \~
    \param[in] ev - \ru Равномерная параметризация по дуге или нет
                    \en Whether arc length parameterization is uniform or not \~
  */
  MbFilletSurface( MbSurfaceCurve & curv1, MbSurfaceCurve & curv2,
                   double d1, double d2, MbeSmoothForm fm, double cn, bool byFirst, bool ev );
  
  /** \brief \ru Конструктор поверхности скругления.
             \en Constructor of fillet surface. \~ 
    \details \ru Конструктор поверхности скругления c кривой пересечения касательных к поверхностям.
             \en Constructor of fillet surface with intersection curve of tangents to surfaces. \~ 
    \param[in] surf1 - \ru Первая поверхность
                       \en First surface \~
    \param[in] curv1 - \ru Опорная кривая в параметрах первой поверхности
                       \en Support curve at parameters of the first surface \~ 
    \param[in] surf2 - \ru Вторая поверхность
                       \en Second surface \~
    \param[in] curv2 - \ru Опорная кривая в параметрах второй поверхности
                       \en Support curve at parameters of the second surface \~ 
    \param[in] curv0 - \ru Кривая пересечения касательных к поверхностям
                       \en Intersection curve of tangents to surfaces \~
    \param[in] d1 - \ru Радиус скругления со знаком для поверхности кривой curv1
                    \en Fillet radius with sign for surface of curv1 curve \~
    \param[in] d2 - \ru Радиус скругления со знаком для поверхности кривой curv2
                    \en Fillet radius with sign for surface of curv2 curve \~
    \param[in] fm - \ru Тип сопряжения: \n 
               st_Span - скругление с заданной хордой \n
               st_Fillet - скругление с заданными радиусами
                    \en Conjugation type: \n 
               st_Span - fillet with a given chord\n
               st_Fillet - fillet with given radii \~    
    \param[in] cn - \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0 - дуга окружности)
                    \en Coefficient of shape is changed between 0.05 and 0.95 (if 0 - circular arc) \~
    \param[in] ev - \ru Равномерная параметризация по дуге или нет
                    \en Whether arc length parameterization is uniform or not \~
  */
  MbFilletSurface( MbSurface & surf1, MbCurve & curv1,
                   MbSurface & surf2, MbCurve & curv2, 
                   MbCurve3D & curv0, double d1, double d2, MbeSmoothForm fm, double cn, bool ev );

protected:
  /// \ru Конструктор для наследников обычной поверхности скругления. \en Constructor for inheritors of ordinary fillet surface.  
  MbFilletSurface( MbSurfaceCurve & curv1, double d1, 
                   MbSurfaceCurve & curv2, double d2, MbeSmoothForm fm, double cn, bool ev ); 
  /// \ru Конструктор для наследников поверхности с сохранением кромки. \en Constructor for inheritors of surface with preservation of fillet. 
  MbFilletSurface( MbSurfaceCurve & curv1, double d1, 
                   MbSurfaceCurve & curv2, double d2, MbeSmoothForm fm, double cn, bool byFirst, bool ev ); 
  /// \ru Конструктор поверхности скругления c кривой пересечения касательных к поверхностям. \en Constructor of fillet surface with intersection curve of tangents to surfaces. \~ 
  MbFilletSurface( MbSurface & surf1, MbCurve & curv1, double d1, 
                   MbSurface & surf2, MbCurve & curv2, double d2,
                   MbCurve3D & curv0, MbFunction & weig0, 
                   MbeSmoothForm fm, double cn, bool ev ); 

  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbFilletSurface( const MbFilletSurface &, MbRegDuplicate * );
  /// \ru Конструктор копирования с теми же опорными поверхностями. \en Copy-constructor with the same support surfaces.
  MbFilletSurface( const MbFilletSurface * ); 
                                              // \ru Для CurvesDuplicate() \en For CurvesDuplicate() 
private:
  MbFilletSurface( const MbFilletSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbFilletSurface ();

public:
  VISITING_CLASS( MbFilletSurface );
  
  /** \ru \name Функции инициализации
      \en \name Initialization functions
      \{ */
          // \ru Коррекция средней линии поверхности скругления. \en Correction of mid-line of fillet surface.  
  virtual void    Init0( double wmin, double wmax, bool insertPoints = true );
  /** \} */
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );          // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 

  virtual void    GetProperties( MbProperties &properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties &properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems( RPArray <MbSpaceItem> &s ); // \ru Дать базовые поверхности. \en Get base surfaces. 

  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetVPeriod() const; // \ru Период для замкнутой поверхности или 0. \en Period for closed surface or 0. 

  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn и Derive... поверхностей сопряжения не корректируют
            первый параметр при его выходе за пределы определения параметров.
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of smooth surfaces don't correct
            first parameter when it is out of domain bounds.
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
  virtual void    NormalU  ( double &u, double &v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  virtual void    NormalV  ( double &u, double &v, MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters. 
      \{ */
  virtual void   _PointOn ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности. \en The point on the extended surface. 
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
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  // \ru Вычислить значения всех производных в точке. \en Calculate all derivatives at point. \~
  virtual void   _PointNormal( double u, double v,
                               MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                               MbVector3D & norm, MbVector3D & uNorm, MbVector3D & vNorm,
                               MbVector3D & uuDer, MbVector3D & vvDer, MbVector3D & uvDer ) const; 
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

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru Построить NURBS копию поверхности. \en Construct a NURBS copy of a surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const; // \ru Построить NURBS-копию поверхности. \en Construct a NURBS-copy of a surface. 
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Create an offset surface. 

  virtual MbCurve3D * CurveV( double u, MbRect1D *pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 

  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя. \en Changing of carrier. 
  virtual bool    ChangeCarrierBorne( const MbSurface & item, MbSurface & init, const MbMatrix & matr ); // \ru Изменение носимых элементов. \en Change a carrier elements. 
  // \ru Нахождениe точки касания поверхностей \en Searching of surfaces tangency point 
  virtual MbeNewtonResult SurfaceTangentNewton( const MbSurface &, MbeParamDir switchPar, double funcEpsilon, size_t iterLimit,
                                                double &u0, double &v0, double &u1, double &v1,
                                                bool ext0, bool ext1 ) const;

  // \ru Проекции точки на поверхность. \en The point projections onto the surface. 
  virtual MbeNewtonResult PointProjectionNewton( const MbCartPoint3D & p, size_t iterLimit,
                                                 double & u, double & v, bool ext ) const; // \ru Функция для нахождения проекции точки на поверхность. \en Function for searching the point projection onto the surface. 
  virtual bool    NearPointProjection  ( const MbCartPoint3D & p, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection onto the surface. 

  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const; // \ru Является ли поверхность скруглением. \en Whether the surface is fillet. 
  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  virtual bool    GetCylinderAxis( MbAxis3D &axis ) const; // \ru Дать ось вращения для поверхности. \en Get a rotation axis of a surface. 
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  virtual ThreeStates Salient() const; // \ru Выпуклая ли поверхность. \en Whether the surface is convex. 
  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v. 
  /** \} */
  /** \ru \name Функции поверхности сопряжения
      \en \name Functions of smooth surface
      \{ */
  virtual MbSmoothSurface & CurvesDuplicate() const; // \ru Копия с теми же опорными поверхностями. \en Copy with the same support surfaces. 
  virtual double  GetSmoothRadius() const; // \ru Дать радиус. \en Get radius. 
  virtual void    GetDistances( double u, double &d1, double &d2 ) const; // \ru Дать радиусы со знаком. \en Get radii with a sign. 
  virtual double  GetDistance( bool s ) const; // \ru Дать радиус со знаком. \en Get radius with a sign. 
  // \ru Объединить поверхности путём включения поверхности init в данную поверхность. \en Unite surfaces by inclusion of 'init' surface into current surface. 
  virtual bool    SurfacesCombine( const MbSurfaceIntersectionCurve & edge, 
                                   const MbSurface & init, bool add, MbMatrix & matr,
                                   const MbSurfaceIntersectionCurve * seam ); 
  /// \ru Дать коэффициент для радиуса. \en Get coefficient for radius. 
  virtual double  DistanceRatio( bool firstCurve, MbCartPoint3D & p, double distance ) const;
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  /** \} */
  /** \ru \name Функции поверхности скругления
      \en \name Functions of fillet surface 
      \{ */

          /** \brief \ru Веса точек средней кривой.
                     \en Weights of points of mid-curve. \~ 
            \details \ru Веса точек средней кривой.
                     \en Weights of points of mid-curve. \~   
            \param[in] u - \ru Параметр на средней кривой (по направлению U)
                           \en Parameter on mid-curve (by U direction) \~
          */
          double  GetWeight( double u ) const; 

          /** \brief \ru Угол раствора дуги.
                     \en Arc opening angle. \~ 
            \details \ru Угол раствора дуги.
                     \en Arc opening angle. \~   
            \param[in] u - \ru Параметр по направлению U
                           \en Parameter by U direction \~
            \return \ru Угол раствора
                    \en Angle of opening \~
          */
          double  GetAngle( double u ) const; // \ru Дать угол раствора дуги v \en Get v arc opening angle 
          
          /** \brief \ru Ось поверхности в данной точке.
                     \en Axis of surface at given point. \~ 
            \details \ru Ось поверхности в данной точке.
                     \en Axis of surface at given point. \~   
            \param[in] u - \ru Параметр по направлению U
                           \en Parameter by U direction \~
            \param[out] axis - \ru Результат - ось вращения
                               \en Result - rotation axis \~
          */
          double  GetLocalAxis  ( double u, MbAxis3D & axis ) const; // \ru Дать ось поверхности в данной точке \en Get axis of surface at given point 
          
          /** \brief \ru Дать точку на оси.
                     \en Get point on axis. \~ 
            \details \ru Дать точку на оси.
                     \en Get point on axis. \~ 
            \param[in] u - \ru Параметр по направлению U
                           \en Parameter by U direction \~
            \param[out] p1 - \ru Точка на первой опорной кривой по параметру U
                             \en Point on first support curve by U parameter \~
            \param[out] p2 - \ru Точка на второй опорной кривой по параметру U
                             \en Point on second support curve by U parameter \~
            \param[out] p0 - \ru Точка на кривой пересечения касательных к поверхностям по параметру u (точка на оси)
                             \en Point on intersection curve of tangents to surfaces by u parameter (point on axis) \~
          */
          void    GetCentrePoint( double u, MbCartPoint3D &p1, MbCartPoint3D &p2, MbCartPoint3D &p0 ) const;
          
          /** \brief \ru Дать среднюю точку.
                     \en Get the mid-point. \~ 
            \details \ru Дать среднюю точку.
                     \en Get the mid-point. \~ 
            \param[in] u - \ru Параметр по направлению U
                           \en Parameter by U direction \~
            \param[out] p1 - \ru Точка на первой опорной кривой по параметру U
                             \en Point on first support curve by U parameter \~
            \param[out] p2 - \ru Точка на второй опорной кривой по параметру U
                             \en Point on second support curve by U parameter \~
            \param[out] p0 - \ru Средняя точка
                             \en Mid-point \~
            \param[out] w - \ru Вес полученной средней точки
                            \en Weight of obtained mid-point \~
          */
          bool    GetMiddlePoint( double u, MbCartPoint3D &p1, MbCartPoint3D &p2, MbCartPoint3D &p0, double &w ) const;
   
          // \ru Если параметризация равномерная, то на продолжении по V замыкается и период зависит от U \en If parameterization is uniform, then it is closed on extension by V and period depends on U 
          /** \brief \ru Период по направлению V.
                     \en Period by direction V. \~ 
            \details \ru Период по направлению V.\n 
              Если параметризация поверхности равномерная, то период по направлению V зависит от параметра U.
                     \en Period by direction V.\n 
              If parameterization of surface is uniform, then period by direction V depends on U parameter. \~
            \param[in] u - \ru Параметр по направлению U
                           \en Parameter by U direction \~  
            \return \ru Период для заданного параметра
                    \en Period for given parameter \~
          */
          double  GetVPeriod( double u ) const;

          /// \ru Кривая пересечения касательных к поверхностям. \en Intersection curve of tangents to surfaces. 
    const MbCurve3D & GetCurve0() const { return *curve0; }
          
          /** \brief \ru Скругление не круговое.
                     \en Fillet isn't circular. \~
            \details \ru Скругление не круговое.
                     \en Fillet isn't circular. \~
            \return \ru true, если радиусы скруглений для поверхностей не равны
                    \en True if surfaces fillet radii aren't equal \~            
          */
          bool    IsEllipse() const { return (fabs(fabs(distance1) - fabs(distance2))>=LENGTH_EPSILON); } // \ru Не равные радиусы \en Not equal radii 
          
          /// \ru Параметризация по дуге равномерная. \en Uniform arc length parameterization.  
          bool    IsEven() const { return even; } 

          /** \brief \ru Однородная ли поверхность скругления.
                     \en Whether the fillet surface is homogeneous. \~
            \details \ru Однородная ли поверхность скругления. Поверхность скругления без сохранения кромки.
                     \en Whether the fillet surface is homogeneous. Fillet surface without preservation of fillet. \~ 
            \return \ru false, если одна из кривых curve1 или curve2 является кромкой
                    \en False if one of curve1 or curve2 curves is fillet \~            
          */
          bool    IsFilletSurface() const { return equable; }      
         
          /** \brief \ru Коническое сечение общего вида.
                     \en General conic section. \~
            \details \ru Коническое сечение общего вида.
                     \en General conic section. \~
            \return \ru false, если сечение поверхности скругления является дугой окружности
                    \en False if section of fillet surface is circular arc \~            
          */
          bool    IsConic() const { return ( ::fabs(conic - c3d::_ARC_) >= EPSILON ); } // \ru Коническое сечение общего вида \en General conic section 
          
          /** \brief \ru Коэффициент формы.
                     \en Coefficient of shape. \~
            \details \ru Коэффициент формы сечения поверхности скругления.\n
              Изменяется от 0.05 до 0.95, при 0 сечение является дугой окружности.
                     \en Coefficient of shape of section of fillet surface.\n
              Is changed between 0.05 and 0.95, if 0, then section is circular arc. \~
            \return \ru Коэффициент
                    \en Coefficient \~          
          */
          double  Conic() const { return conic; }
          
          /** \brief \ru Поверхность скругления с сохранением кромки.
                     \en Fillet surface with preservation of fillet. \~
            \details \ru Поверхность скругления с сохранением кромки.
                     \en Fillet surface with preservation of fillet. \~         
            \return \ru true, если одна из кривых curve1 или curve2 является кромкой
                    \en True if one of curve1 or curve2 curves is fillet \~          
          */
          bool    IsKerbSurface() const { return !equable; }
          
          /** \brief \ru Является ли первая кривая кромкой.
                     \en Whether the first curve is fillet. \~
            \details \ru Является ли первая кривая кромкой.
                     \en Whether the first curve is fillet. \~       
            \return \ru true, если первая кривая является кромкой
                    \en True if the first curve is fillet. \~   
          */
          bool    ByFirstCurve() const { return byCurve1; }

          /** \brief \ru Установить поверхность скругления типа с сохранением кромки.
                     \en Set fillet surface with preservation of fillet. 
                         Need to call this->Init0() after this method \~
            \details \ru Установить поверхность скругления с сохранением кромки и указать определяющую кривую на поверхности.
                         Далее нужно вызвать метод this->Init0().
                     \en Set fillet surface with preservation of fillet. \~         
            \param[in] bc1 - \ru Определяющая кривая на поверхности: curve1 (bc1 = true), curve2 (bc1 = false).
                             \en General curve on surface: curve1 (bc1 = true), curve2 (bc1 = false). \~  
          */
          void    SetKerbSurface( bool bc1 ) { if ( equable ) { equable = false; byCurve1 = bc1; } }

          // \ru Выдать функцию весов точек средней кривой curve0. \en Get weight function for points of mid-curve (curve0). 
          const MbFunction * GetWeights() const;
          // \ru Установить функцию весов точек средней кривой curve0. \en Set weight function for points of mid-curve (curve0). 
          bool        SetWeights( MbFunction & func );

          MbCurve3D * GetSpine() const;
          void        SetSpine( MbCurve3D * );
        
   /** \} */
protected:
          void    WeightKoefficient( double & w ) const; // \ru Вычисление веса при заданном коэффициенте \en Calculation of weight at given coefficient  
          void    InitFilletSurface ( const MbFilletSurface & init );
          void    CalculateCurve( double wmin, double wmax, bool insertPoints );
          double  CalculateVParam( const MbCartPoint3D & p, double u ) const; // \ru Нахождение параметра v проекции точки на вырожденную поверхность \en Searching of v parameter of point projection onto degenerate surface 

protected:
          // \ru Вычисление точки \en Calculation of a point 
//          void    CalculateSurface( double u ) const;
  // \ru Дать коэффициент для радиуса \en Get coefficient for radius 
  virtual double  FunctionValue( double u ) const; 
          void    CalculateData ( double & u, double & v,
                                  MbCartPoint3D & uPoint0, MbCartPoint3D & uPoint1, MbCartPoint3D & uPoint2, // \ru Точки на кривых    curve0, curve1, curve2. \en Points on curve0, curve1, curve2. 
                                  MbVector3D * uFirst0, MbVector3D * uFirst1, MbVector3D * uFirst2, // \ru Производные кривых curve0, curve1, curve2. \en Derivatives of curve0, curve1, curve2. 
                                  MbVector3D * uSecond0, MbVector3D * uSecond1, MbVector3D * uSecond2, // \ru Производные кривых curve0, curve1, curve2. \en Derivatives of curve0, curve1, curve2. 
                                  double & uWeight, double * wFirst, double * wSecond, // \ru Вес и его производные средней точки uPoint0. \en The weight and it derivatives of the mid-point uPoint0. 
                                  double & uP0, double & uP1, double & uP2, double & uPw, // \ru Коэффициенты точек       uPoint0, uPoint1, uPoint2. \en Coefficients of points uPoint0, uPoint1, uPoint2. 
                                  double & uF0, double & uF1, double & uF2, double & uFw ) const; // \ru Коэффициенты производных uFirst0, uFirst1, uFirst2. \en Coefficients of derivatives uFirst0, uFirst1, uFirst2. 
          void    InitSpineDerives();
          void    CalculatePointOn  ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const double & uWeight, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw,
                                      MbCartPoint3D & ) const; // \ru Точка на поверхности. \en The point on the surface. 
          void    CalculateDeriveU  ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const double & uWeight, const double & wFirst, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
          void    CalculateDeriveV  ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const double & uWeight, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
          void    CalculateDeriveUU ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const MbVector3D & uSecond0, const MbVector3D & uSecond1, MbVector3D &uSecond2,
                                      const double & uWeight, const double & wFirst, const double & wSecond, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
          void    CalculateDeriveVV ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const double & uWeight, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Вторая производная по v. \en The second derivative with respect to v. 
          void    CalculateDeriveUV ( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const double & uWeight, const double & wFirst, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
          void    CalculateDeriveUUU( double & u, double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const MbVector3D & uSecond0, const MbVector3D & uSecond1, MbVector3D &uSecond2,
                                      const double & uWeight, const double & wFirst, const double & wSecond, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      MbVector3D & ) const;
          void    CalculateDeriveUUV( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const MbVector3D & uSecond0, const MbVector3D & uSecond1, MbVector3D &uSecond2,
                                      const double & uWeight, const double & wFirst, const double & wSecond, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const;
          void    CalculateDeriveUVV( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const double & uWeight, const double & wFirst, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const;
          void    CalculateDeriveVVV( double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const double & uWeight, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const;
          void    CalculateNormal   ( double & u, double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const double & uWeight, const double & wFirst, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Нормаль. \en Normal. 
          void    CalculateNormalU  ( double & u, double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const MbVector3D & uSecond0, const MbVector3D & uSecond1, MbVector3D &uSecond2,
                                      const double & uWeight, const double & wFirst, const double & wSecond, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 
          void    CalculateNormalV  ( double & u, double & v, 
                                      const MbCartPoint3D & uPoint0, const MbCartPoint3D & uPoint1, const MbCartPoint3D & uPoint2,
                                      const MbVector3D & uFirst0, const MbVector3D & uFirst1, const MbVector3D & uFirst2,
                                      const double & uWeight, const double & wFirst, 
                                      const double & uP0, const double & uP1, const double & uP2, const double & uPw, 
                                      const double & uF0, const double & uF1, const double & uF2, const double & uFw,
                                      MbVector3D & ) const; // \ru Производная нормали. \en The derivative of normal. 

          // \ru Проверка параметров. \en Check parameters. 
          void    CheckUParam( double & u ) const; 
          void    CheckVParam( double & v ) const;

          void    operator = ( const MbFilletSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbFilletSurface )
}; // MbFilletSurface


IMPL_PERSISTENT_OPS( MbFilletSurface )


//------------------------------------------------------------------------------
// \ru Проверка параметра u по отношению к полюсам и замкнутости \en Check u parameter against poles and closedness 
// ---
inline void MbFilletSurface::CheckUParam( double & u ) const {
  if ( uclosed ) {
    if ( (u < umin) || (u > umax ) ) {
      double tmp = umax - umin;
      u -= ::floor((u - umin) / tmp) * tmp; 
    }
  }
  else {
    if ( poleMin && u<umin )
      u = umin;
    if ( poleMax && u>umax )
      u = umax;
  }
}


//------------------------------------------------------------------------------
// \ru Проверка параметра v \en Check v parameter  
// ---
inline void MbFilletSurface::CheckVParam( double & v ) const {
  if ( v < vmin )
    v = vmin;
  else
    if ( v > vmax )
      v = vmax;
}


//------------------------------------------------------------------------------
// \ru Вычислить вес для эллиптической точки \en Calculate weight for elliptic point 
// ---
inline bool FilletWeight( double cos_a, double d1, double d2, double & uW )
{
  bool result = false;
  // \ru cos_a - косинус угла между нормалями \en Cos_a - cosine of angle between normals 
  if ( ::fabs( cos_a ) > PARAM_PRECISION ) { // \ru Не прямой угол \en Angle not right  
    if ( (d1 * d2) < 0 )
      cos_a = -cos_a;
    double cos2_a = cos_a * cos_a;
    double sin2_a = ::fabs( 1.0 - cos2_a );
    double sin_a = ::sqrt( sin2_a ); // \ru Синус угла между нормалями \en Sine of angle between normals 
    bool   first = ( ::fabs(d1) > ::fabs(d2) );
    double a = first ? ::fabs( d1 ) : ::fabs( d2 ); // \ru Большая полуось эллипса \en Major semi axis of ellipse 
    double b = first ? ::fabs( d2 ) : ::fabs( d1 ); // \ru Малая   полуось эллипса \en Minor semi axis of ellipse 
    // \ru Эллипс наиболее удалённой от центра точкой касался одной из поверхностей \en Ellipse concerns one of the surfaces by the point most remote from the center 
    if ( sin_a > PARAM_PRECISION ) { // \ru Не малый угол \en Angle not small  
      double aa = a * a;
      double bb = b * b;
      double p = ::sqrt( (aa*cos2_a) + (bb*sin2_a) ); // \ru Знаменатель (расстояние от центра эллипса до касательной) \en Denominator (distance from center of ellipse to tangent) 
      if ( p > NULL_EPSILON ) { // \ru Всегда должно выполняться, если a!=0 и b!=0 \en Always hold, if a! =0 and b! =0 
        double d = 1.0 / p;
        double cos_t = a * cos_a * d; // \ru Косинус параметрического угла эллипса \en Cosine of metric angle of ellipse 
        uW = ::sqrt( (1.0 + cos_t) * 0.5 ); // \ru Половина косинуса параметрического угла эллипса \en Half of cosine of metric angle of ellipse 
        result = true;
      }
    }
  }
  return result;
}


//------------------------------------------------------------------------------
/** \brief \ru Создать поверхность сопряжения.
           \en Create the fillet surface. \~
  \details \ru Создать поверхность сопряжения с сохранением кромки грани.
           \en Create the fillet surface with the edge. \~
  \param[in] surface1 -  \ru Сопрягаемая поверхность.
                         \en The conjugate surface. \~
  \param[in] points1 -   \ru Точки для опорной кривой на сопрягаемой поверхности.
                         \en Points for curve on the conjugated surface. \~
  \param[in] surface2  - \ru Сопрягаемая поверхность.
                         \en The conjugate surface. \~
  \param[in] points2   - \ru Точки для опорной кривой на сопрягаемой поверхности.
                         \en Points for curve on the conjugated surface. \~
  \param[in] form      - \ru Тип повержности сопряжения.
                         \en The surface type \~
  \param[in] distance1 - \ru Радиус скругления со знаком для поверхности кривой crve1
                         \en Fillet radius with sign for surface of crve1 curve \~
  \param[in] distance2 - \ru Радиус скругления со знаком для поверхности кривой crve2
                         \en Fillet radius with sign for surface of crve2 curve \~
  \param[in] conic     - \ru Коэффициент формы, изменяется от 0.05 до 0.95 (при 0.5 - дуга окружности)
                         \en Coefficient of shape is changed from 0.05 to 0.95 (if 0.5 - circular arc) \~
  \param[in] curve     - \ru Кривая опорной кромки.
                         \en The edge curve \~
  \param[in] params    - \ru Параметры поверхности вдоль первого напрвыления (u).
                         \en The parameters of new the surface by first direction (u) \~
  \param[in] byFirstSurface - \ru Пурвая или вторая поверхность сопрягается гладко с новой поверхностью.
                              \en Is the first or second conjugate surface smooth with the new surface. \~
  \param[in] even      - \ru Равномерная параметризация по дуге (v) или нет
                         \en Uniform parametrization by arc (v) or not \~
  \return \ru Возвращает созданную поверхность.
          \en Return the created surface. \~ 
  \ingroup Surface_Modeling
*/
MbSmoothSurface * CreateKerbSurface( const MbSurface &surface1, SArray<MbCartPoint> & points1,
                                     const MbSurface &surface2, SArray<MbCartPoint> & points2,
                                     MbeSmoothForm form, double distance1, double distance2, double conic,
                                     const MbSurfaceIntersectionCurve & curve, SArray<double> & params,
                                     bool byFirstSurface, bool even );


#endif // __SURF_FILLET_SURFACE_H
