////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Tороидальная поверхность.
         \en Toroidal surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_TORUS_SURFACE_H
#define __SURF_TORUS_SURFACE_H


#include <surf_elementary_surface.h>


//------------------------------------------------------------------------------
/** \brief \ru Tороидальная поверхность.
           \en Toroidal surface. \~
  \details \ru Поверхность тора описывается радиусом центров majorRadius и радиусом трубки minorRadius, 
    заданными в локальной системе координат position.\n
    Первый параметр поверхности отсчитывается по дуге от оси position.axisX в направлении оси position.axisY. 
    Первый параметр поверхности u принимает значения на отрезке: umin<=u<=umax. 
    Значения u=0 и u=2pi соответствуют точке на плоскости XZ локальной системы координат. 
    Поверхность может быть замкнутой по первому параметру. 
    У замкнутой поверхности umax-umin=2pi, у не замкнутой поверхности umax-umin<2pi.\n
    Второй параметр поверхности отсчитывается по дуге от плоскости XY локальной системы координат поверхности в направлении оси position.axisZ. 
    Второй параметр поверхности v принимает значения на отрезке: vmin<=v<=vmax. 
    Значения v=0 и v=2pi соответствуют точке на плоскости XY локальной системы координат поверхности. 
    Поверхность может быть замкнутой по второму параметру при majorRadius>minorRadius. 
    У замкнутой поверхности vmax-vmin=2pi, у не замкнутой поверхности vmax-vmin<2pi. \n
    Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = position.origin + ((majorRadius + (minorRadius cos(v)) (cos(u) position.axisX + sin(u) position.axisY)) + (minorRadius sin(v) position.axisZ).\n
    Радиус трубки должен быть больше нуля: minorRadius>0. 
    Радиус центров должен быть не меньше радиуса трубки, взятого с обратным знаком: majorRadius>–minorRadius. 
    Если majorRadius<minorRadius, то поверхность имеет полюс для параметра v=arccos(majorRadius/minorRadius) и v=2pi–arccos(majorRadius/minorRadius).\n
    Для граничных параметров поверхности должны соблюдаться неравенства: umin<umax, vmin<vmax.\n
    Локальная система координат position может быть как правой, так и левой. 
    Если локальная система координат правая, то нормаль направлена от трубки поверхности, 
    если локальная система координат левая, то нормаль направлена внутрь трубки поверхности.\n
           \en A surface of torus is described by the radius of centers 'majorRadius' and the radius of tube 'minorRadius', 
    which are set in the local coordinate system.\n
    The first parameter of a surface is measured by an arc  from the axis 'position.axisX' in direction of the axis 'position.axisY'. 
    The first parameter of a surface u takes values on the segment: umin<=u<=umax. 
    Values u=0 and u=2pi correspond to the point on the plane XZ of a local coordinate system. 
    A surface may be closed in direction of the first parameter. 
    If a surface is closed, then umax-umin=2pi, otherwise umax-umin<2pi.\n
    The second parameter of a surface is measured by an arc from the plane XY of the surface local coordinate system in direction of the axis 'position.axisZ'. 
    The second parameter of a surface v takes values on the segment: vmin<=v<=vmax. 
    The values v=0 and v=2pi correspond to a point on the plane XY of the surface local coordinate system. 
    A surface may be closed in direction of the second parameter if majorRadius>minorRadius. 
    If a surface is closed, then vmax-vmin=2pi, otherwise vmax-vmin<2pi. \n
    Radius-vector of line surface is described by the vector function \n
    r(u,v) = position.origin + ((majorRadius + (minorRadius cos(v)) (cos(u) position.axisX + sin(u) position.axisY)) + (minorRadius sin(v) position.axisZ).\n
    Radius of tube must be positive: minorRadius>0. 
    Radius of centers must be not less than the radius of tube with the opposite sign: majorRadius>-minorRadius. 
    If majorRadius<minorRadius, then the surface has a pole for the parameter v=arccos(majorRadius/minorRadius) and v=2pi-arccos(majorRadius/minorRadius).\n
    The following inequalities must be satisfied for the parameters of surface boundary: umin<umax, vmin<vmax.\n
    Local coordinate system 'position' can be both right and left. 
    If the local coordinate system is right then the normal is directed outside the tube of a surface, 
    if the local coordinate system is left then the normal is directed inside the tube of a surface.\n \~
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbTorusSurface : public MbElementarySurface {
private:
  double majorRadius; ///< \ru Большой радиус - радиус центров трубки. \en Major radius - radius of tube centers. 
  double minorRadius; ///< \ru Малый радиус - радиус трубки (всегда положителен). \en Minor radius - radius of tube (it is always positive). 
  bool   uclosed;     ///< \ru Признак замкнутости по параметру u. \en An attribute of closedness in u-parameter direction. 
  bool   vclosed;     ///< \ru Признак замкнутости по параметру v. \en An attribute of closedness in v-parameter direction. 
                      ///< \ru majorRadius == minorRadius - осциллирующее яблоко по v замкнут в -M_PI и M_PI полюса, \en MajorRadius == minorRadius - oscillatory apple is closed in v direction in -M_PI and M_PI poles, 
                      ///< \ru majorRadius >  minorRadius - пончик, \en MajorRadius >  minorRadius - a donut, 
                      ///< \ru majorRadius <= minorRadius - яблоко, \en MajorRadius <= minorRadius - an apple, 
                      ///< \ru (-minorRadius < majorRadius < 0.0) - лимон. \en (-minorRadius < majorRadius < 0.0) - a lemon. 

public:
  /// \ru Конструктор по локальной системе координат, большому и малому радиусу. \en Constructor by local coordinate system, major and minor radii. 
  MbTorusSurface ( const MbPlacement3D & pl, double initMajorR, double initMinorR );
  
  /** \brief \ru Конструктор по большому и малому радиусу, локальной системе координат, минимальному и максимальному параметрам по V.
             \en Constructor by major and minor radii, local coordinate system, minimal and maximal parameters by V. \~
    \details \ru Конструктор по большому и малому радиусу, локальной системе координат, минимальному и максимальному параметрам по V.
             \en Constructor by major and minor radii, local coordinate system, minimal and maximal parameters by V. \~
    \warning \ru Используется только в конвертерах.
             \en This is used only in converters. \~
  */
  MbTorusSurface ( double initMajorR, double initMinorR, const MbPlacement3D & pl, double vin, double vax ); 
  
  /** \brief \ru Конструктор по трем точкам.
             \en Constructor by three points. \~
    \details \ru Первая точка - центр локальной системы координат поверхности.\n
      Длина вектора, направленного из первой точки во вторую, равна большому радиусу,\n
      его направление совпадает с направлением оси X.\n
      Длина вектора, направленного из второй точки в третью, равна малому радиусу.\n
      Ось Z лежит в плоскости точек и направлена в сторону вектора из первой точки в третью.
             \en The first point is the center of the surface local coordinate system.\n
      A length of a vector directed from the first point to the second point is equal to the major radius,\n
      its direction coincides with the direction of the axis X.\n
      A length of a vector directed from the second point to the third point is equal to the minor radius,\n
      The axis Z lies on the plane of the points and directed to the side of the vector from the first point to the third point. \~       
  */
  MbTorusSurface ( const MbCartPoint3D & c0, const MbCartPoint3D & c1, const MbCartPoint3D & c2 );
  
  /** \brief \ru Конструктор по трем точкам и малому радиусу.
             \en Constructor by three points and minor radius. \~
    \details \ru Конструктор по трем точкам и малому радиусу.\n
      Первая точка - центр локальной системы координат тороидальной поверхности.\n
      Вектор из первой точки во вторую - направление оси Z.
      Большой радиус равен длине проекции на ось Z вектора, направленного из первой точки в третью.
             \en Constructor by three points and minor radius.\n
      The first point is the center of the toroidal surface local coordinate system.\n
      A vector from the first point to the second point - direction of the axis Z.
      Major radius is equal to the length of the projection to the axis Z of the vector directed from the first point to the third point. \~
  */
  MbTorusSurface ( const MbCartPoint3D & c0, const MbCartPoint3D & c1, const MbCartPoint3D & c2, double initMinorR );

protected:
  MbTorusSurface ( const MbTorusSurface & );
public:
  virtual ~MbTorusSurface();

public:
  VISITING_CLASS( MbTorusSurface );
  
  /** \ru \name Функции инициализации
      \en \name Initialization functions
  \{ */
          /// \ru Инициализация по тороидальной поверхности. \en The initialization by toroidal surface. 
          void    Init( const MbTorusSurface & ); 
  /** \} */   
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame  ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
 
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description 
      \{ */
  virtual double  GetUMin  () const;
  virtual double  GetVMin  () const;
  virtual double  GetUMax  () const;
  virtual double  GetVMax  () const;
  virtual bool    IsUClosed() const;
  virtual bool    IsVClosed() const;    
  virtual double  GetUPeriod() const; // \ru Вернуть период для замкнутой функции. \en Return period for a closed function. 
  virtual double  GetVPeriod() const; // \ru Вернуть период для замкнутой функции. \en Return period for a closed function. 
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
  virtual void    Normal   ( double & u, double & v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void    NormalU  ( double & u, double & v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
  virtual void    NormalV  ( double & u, double & v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
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
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  virtual void   _NormalU  ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
  virtual void   _NormalUU ( double u, double v, MbVector3D & ) const;
  virtual void   _NormalUV ( double u, double v, MbVector3D & ) const;
  virtual void   _NormalVV ( double u, double v, MbVector3D & ) const;
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  virtual void   _PointNormal( double u, double v,
                               MbCartPoint3D & pnt, MbVector3D & deru, MbVector3D & derv,
                               MbVector3D & norm, MbVector3D & noru, MbVector3D & norv,
                               MbVector3D & deruu, MbVector3D & dervv, MbVector3D & deruv ) const; // \ru Значения производных в точке. \en Values of derivatives at point.       
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
      \en \name Common functions of surface
      \{ */
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна вдоль u. \en Curvature in u direction. 
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна вдоль v. \en Curvature in v direction. 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const;
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Creation of an offset surface. 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en A spatial copy of the line v = const. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en A spatial copy of the line u = const. 
  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const;
  // \ru Пересечение с кривой. \en Intersection with a curve. 
  virtual void    CurveIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                     bool ext0, bool ext, bool touchInclude = false ) const;

  // \ru Определение точки касания поверхностей с одним неподвижным параметром. \en Determination of tangency point of surfaces with one fixed parameter. 
  virtual MbeNewtonResult SurfaceTangentNewton( const MbSurface & surf1, MbeParamDir switchPar, double funcEpsilon, size_t iterLimit,
                                                double & u0, double & v0, double & u1, double & v1, bool ext0, bool ext1 ) const;
  // \ru Определениe точки касания поверхности и кривой. \en Determination of tangency point between a surface and a curve. 
  virtual MbeNewtonResult CurveTangentNewton( const MbCurve3D & curv, double funcEpsilon, size_t iterLimit,
                                              double & u, double & v, double & t, bool ext0, bool ext1 ) const;

  virtual bool    GetCylinderAxis( MbAxis3D & axis ) const; // \ru Дать ось вращения для поверхности. \en Get rotation axis of a surface. 
  virtual bool    GetCenterLines( std::vector<MbCurve3D *> & clCurves ) const; // \ru Дать осевые (центральные) линии для поверхности. \en Get center lines of a surface.

  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces are similar to merge. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric region to the parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const; // \ru Является ли поверхность скруглением. \en Whether a surface is fillet. 
  virtual ThreeStates Salient() const; // \ru Выпуклая ли поверхность. \en Whether a surface is convex. 
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine a splitting of parametric region of a surface by verticals and horizontals. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  virtual void    SetLimit( double u1, double v1, double u2, double v2 );
  virtual void    SetExtendedParamRegion( double u1, double v1, double u2, double v2 );

  virtual void    IncludePoint( double u, double v ); // \ru Включить точку в область определения. \en Include a point into domain. 
  // \ru Существует ли полюс на границе параметрической области сплайновой кривой. \en Whether a pole exists on parametric region boundary of spline curve. 
  virtual bool    GetPoleVMin() const;
  virtual bool    GetPoleVMax() const;
  virtual bool    IsPole( double u, double v ) const; // \ru Является ли точка особенной. \en Whether the point is singular. 
  
  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the number of polygons in u-direction. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the number of polygons in v-direction. 

  virtual double  GetUParamToUnit() const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit() const;  // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual double  GetUParamToUnit( double u, double v ) const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit( double u, double v ) const; // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual void    GetParamsToUnit( double u, double v, double & uParam, double & vParam ) const; // \ru Дать приращение параметра u и параметра v, соответствующее единичной длине в пространстве. \en Get increment of parameters, corresponding to the unit length in space.  

  // \ru Является ли объект смещением. \en Is the object a shift? 
  virtual bool    IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const; 
  virtual double  GetRadius() const; // \ru Дать максимальный физический радиус объекта или ноль, если это невозможно. \en Get the maximum physical radius of the object or null if it impossible.
  /** \} */  
  /** \ru \name Функции элементарных поверхностей
      \en \name Functions of elementary surfaces.
      \{ */
  virtual bool    GetPointProjection( const MbCartPoint3D & p, bool init, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const;
  /** \} */  
  /** \ru \name Функции тороидальной поверхности
      \en \name Functions of toroidal surface
      \{ */
          /// \ru Дать физический главный радиус центров. \en Get physical major radius. 
          double  GetMajorRadius() const; 
          /// \ru Дать физический меньший радиус. \en Get physical minor radius. 
          double  GetMinorRadius() const; 

          /// \ru Изменение главного радиуса. \en Changing of major radius. 
          void    SetMajorR( double r ) { majorRadius = r; CheckTorusRadii(); CalculateAngle(); SetDirtyGabarit(); } 
          /// \ru Изменение меньшего радиуса. \en Changing of minor radius. 
          void    SetMinorR( double r ) { minorRadius = r; CheckTorusRadii(); CalculateAngle(); SetDirtyGabarit(); } 
          /// \ru Главный радиус. \en Major radius. 
          double  GetMajorR() const     { return majorRadius; }  
          /// \ru Меньший радиус. \en Minor radius. 
          double  GetMinorR() const     { return minorRadius; }  
          /// \ru Радиус v-параллели. \en Radius of v-parallel. 
          double  GetR( double v ) const { return majorRadius + minorRadius * ::cos(v); } 

          /// \ru Дать центр u-линии тора. \en Get center of torus u-line. 
          void    GetMinorCentre( double u, MbCartPoint3D & c ) const; 
          /// \ru Дать проекцию точки на линию центров малого радиуса. \en Get projection of the point to the line of centers of minor radius. 
          double  MinorCentreProjection( MbCartPoint3D & p ) const; 

          /** \brief \ru Определить положение полюсов.
                     \en Define position of the poles. \~
            \details \ru Определить положение полюсов.
                     \en Define position of the poles. \~           
            \param[out] poleVMin, poleVMax - \ru Значения полюсов.
                                             \en Values of the poles. \~
            \return \ru true, если полюса найдены.
                    \en True if the poles are found. \~
          */
          bool    GetVPoles( double & poleVMin, double & poleVMax ) const;

private:
          void    CheckTorusRadii();
  inline  void    CheckParam( double & u, double & v ) const; // \ru Проверка параметров \en Check parameters 
          bool   _CheckParamV( double & v ) const; // \ru Проверить параметр \en Check parameter 
          // \ru Пересечение с прямолинейной кривой \en Intersection with rectilinear curve 
          bool    StraightIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, bool ext0, bool ext ) const;
          void    CalculateAngle(); // \ru Вычислить угол \en Evaluate the angle 
          void    operator = ( const MbTorusSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbTorusSurface )
};

IMPL_PERSISTENT_OPS( MbTorusSurface )

//------------------------------------------------------------------------------
// \ru Проверка параметров \en Check parameters 
// ---
inline void MbTorusSurface::CheckParam( double & u, double & v ) const
{
  if ( (u < umin) || (u > umax) ) {
    if ( uclosed ) 
      u -= ::floor( (u - umin) * Math::invPI2 ) * M_PI2;
    else if ( u < umin )
      u = umin;
    else if ( u > umax )
      u = umax;
  }
  if ( (v < vmin) || (v > vmax) ) {
    if ( vclosed ) 
      v -= ::floor( (v - vmin) * Math::invPI2 ) * M_PI2;
    else if ( v < vmin )
      v = vmin;
    else if ( v > vmax )
      v = vmax;
  }
}


#endif // __SURF_TORUS_SURFACE_H
