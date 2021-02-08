////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Цилиндрическая поверхность.
         \en The cylindrical surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_CYLINDER_SURFACE_H
#define __SURF_CYLINDER_SURFACE_H


#include <surf_elementary_surface.h>


class  MATH_CLASS MbLineSegment3D;
class  MATH_CLASS MbPlane;


//------------------------------------------------------------------------------
/** \brief \ru Цилиндрическая поверхность.
           \en The cylindrical surface. \~
  \details \ru Цилиндрическая поверхность описывается радиусом radius и высотой height, заданными в локальной системе координат position. \n
    Первый параметр поверхности отсчитывается по дуге от оси position.axisX в направлении оси position.axisY. 
    Первый параметр поверхности u принимает значения на отрезке: umin<=u<=umax. 
    Значения u=0 и u=2pi соответствуют точке на плоскости XZ локальной системы координат. 
    Поверхность может быть замкнутой по первому параметру. 
    У замкнутой поверхности umax-umin=2pi, у не замкнутой поверхности umax-umin<2pi. \n
    Второй параметр поверхности отсчитывается по прямой вдоль оси position.axisZ. 
    Второй параметр поверхности v принимает значения на отрезке: vmin<=v<=vmax. 
    Значение v=0 соответствует точке плоскости XY локальной системы координат, 
    а значение v=1 соответствует точке на расстоянии height от плоскости XY локальной системы координат поверхности. \n
    Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = position.origin + (radius cos(u) position.axisX) + (radius sin(u) position.axisY) + (height v position.axisZ). \n
    Локальная система координат position может быть как правой, так и левой. 
    Если локальная система координат правая, то нормаль направлена в сторону выпуклости поверхности (от оси position.axisZ), 
    если локальная система координат левая, то нормаль направлена в сторону вогнутости поверхности (в сторону оси position.axisZ). \n
           \en Cylindrical surface is described by 'radius' radius and 'height' height given in 'position' local coordinate system. \n
    The first parameter of surface is measured along arc from position.axisX axis in the direction of position.axisY axis. 
    The first parameter u of surface possesses the values in the range: umin<=u<=umax. 
    Values u=0 and u=2pi correspond to point on XZ plane of local coordinate system. 
    Surface can be closed by first parameter. 
    In case of closed surface: umax-umin=2pi; in case of open surface: umax-umin<2pi. \n
    Second parameter of surface is measured by line along position.axisZ axis. 
    Second parameter v of surface possesses the values in the range: vmin<=v<=vmax. 
    Value v=0 corresponds to point on XY plane of local coordinate system, 
    but value v=1 corresponds to point at 'height' distance from XY plane of local coordinate system of surface. \n
    Radius-vector of surface is described by the vector function \n
    r(u,v) = position.origin + (radius cos(u) position.axisX) + (radius sin(u) position.axisY) + (height v position.axisZ). \n
    Local coordinate system 'position' can be both right and left. 
    If local coordinate system is right then normal is directed to the side of convexity of surface (from position.axisZ axis), 
    If local coordinate system is left then normal is directed to the side of concavity of surface (to position.axisZ axis). \n \~
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbCylinderSurface : public MbElementarySurface  {
private:
  double radius;  ///< \ru Радиус цилиндра. \en Radius of cylinder. 
  double height;  ///< \ru Высота цилиндра. \en Height of cylinder. 
  bool   uclosed; ///< \ru Признак замкнутости по первому параметру. \en Attribute of closedness by first parameter. 

public:
  /// \ru Конструктор по системе координат, радиусу и высоте. \en Constructor by a local coordinate system, radius and height. 
  MbCylinderSurface( const MbPlacement3D & place, double r, double h ); 
  
  /** \brief \ru Конструктор по радиусу, высоте и системе координат.
             \en Constructor by radius, height and coordinate system. \~
    \details \ru Конструктор по радиусу, высоте и системе координат.
             \en Constructor by radius, height and coordinate system. \~
    \warning \ru Только для использования в конвертерах.
             \en Used only in converters. \~
  */
  MbCylinderSurface( double r, double h, const MbPlacement3D & place );
  
  /** \brief \ru Конструктор по центру системы координат, оси Z и радиусу.
             \en Constructor by an origin of local coordinate system, Z-axis and radius. \~   
    \details \ru Конструктор по центру системы координат, оси Z и радиусу. \n
             \en Constructor by an origin of local coordinate system, Z-axis and radius. \n \~
    \param[in] org - \ru центр локальной системы координат
                     \en Origin of the local coordinate system \~
    \param[in] axisZ - \ru Ось Z локальной системы координат
                       \en Z-axis of the local coordinate system \~
    \param[in] r - \ru Радиус цилиндра и высота цилиндра, при r < Math::lengthRegion высота цилиндра = 1.0
                   \en Radius of cylinder and height of cylinder, height of cylinder is equal to 1.0 if r < Math::lengthRegion \~
    \param[in] left - \ru Если true, то система координат цилиндра левая
                      \en If true, then cylinder coordinate system is left \~
  */
  MbCylinderSurface( const MbCartPoint3D & org, const MbVector3D & axisZ, double r, bool left = false ); 
  
  /** \brief \ru Конструктор по трем точкам.
             \en Constructor by three points. \~   
    \details \ru Конструктор по трем точкам.
             \en Constructor by three points. \~  
    \param[in] c0 - \ru центр локальной системы координат цилиндра
                    \en Origin of the local coordinate system of cylinder \~
    \param[in] c1 - \ru Вектор из точки c0 в точку c1 определяет ось Z
                    \en Vector from c0 point to c1 point determines Z-axis \~                                                         
    \param[in] c2 - \ru Вектор из точки c0 в точку c2 определяет ось X, радиус цилиндра равен расстоянию от оси Z до точки c2
                    \en Vector from c0 point to c2 point determines X-axis, radius of cylinder is equal to distance from Z-axis to c2 point \~   
  */
  MbCylinderSurface( const MbCartPoint3D & c0, const MbCartPoint3D & c1, const MbCartPoint3D & c2 ); // \ru По трём точкам \en By three points 

protected:
  MbCylinderSurface( const MbCylinderSurface & );
public:
  virtual ~MbCylinderSurface ();

public:
  VISITING_CLASS( MbCylinderSurface );
  
  /** \ru \name Функции инициализации
      \en \name Initialization functions
  \{ */
          /// \ru Инициализация по цилиндрической поверхности. \en Initialization by cylindrical surface. 
          void    Init( const MbCylinderSurface & init ); 
          /// \ru Инициализация по локальной системе координат, радиусу и высоте. \en Initialization by a local coordinate system, radius and height. 
          void    Init( const MbPlacement3D & place, double r, double h ); 
          
          /** \brief \ru Инициализация по отрезку и точке.
                     \en Initialization by segment and point. \~   
            \details \ru Инициализация по отрезку и точке. \n
              Высота цилиндра определяется длиной отрезка seg. \n
              Ось определяется отрезком seg. \n
              Радиус цилиндра равен расстоянию от точки point до оси.
                     \en Initialization by segment and point. \n
              Height of cylinder is determined by length of 'seg' segment. \n
              Axis is determined by 'seg' segment. \n
              Radius of cylinder is equal to distance from 'point' point to axis. \~           
          */
          void    Init( const MbLineSegment3D & seg, const MbCartPoint3D & point );
       
          /** \brief \ru Построение цилиндра радиуса r как сопряжение двух плоскостей в указанном месте.
                     \en Construction of cylinder of radius 'r' as conjugation of two planes at specified place. \~   
            \details \ru Построение цилиндра радиуса r, касающегося двух плоскостей plane1 и plane2
                     \en Construction of cylinder of radius 'r' tangent to two planes 'plane1' and 'plane2' \~
            \param[in] plane1 - \ru Первая плоскость
                                \en First plane \~
            \param[in] plane2 - \ru Вторая плоскость
                                \en Second plane \~
            \param[in] side1 - \ru Если > 0, то цилиндр над первой плоскостью, если < 0, то цилиндр под первой плоскстью
                               \en If it is greater than 0, then cylinder is above first plane, if it is less than 0, then cylinder is under first plane \~
            \param[in] side2 - \ru Если > 0, то цилиндр над второй плоскостью, если < 0, то цилиндр под второй плоскстью
                               \en If it is greater than 0, then cylinder is above second plane, if it is less than 0, then cylinder is under second plane \~
            \param[in] r - \ru Радиус цилиндра
                           \en Radius of cylinder \~
          */
          bool    Init( const MbPlane & plane1, const MbPlane & plane2, int side1, int side2, double r );
  /** \} */
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 

  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetUMin() const;
  virtual double  GetVMin() const;
  virtual double  GetUMax() const;
  virtual double  GetVMax() const;
  virtual bool    IsUClosed() const;
  virtual bool    IsVClosed() const;      
  virtual double  GetUPeriod() const; // \ru Вернуть период для замкнутой функции. \en Return period for closed function. 
  virtual double  GetVPeriod() const; // \ru Вернуть период для замкнутой функции. \en Return period for closed function. 
  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.\n          
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of surfaces correct parameters
            when they are out of bounds of rectangular domain of parameters.\n
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const;  // \ru Точка на поверхности. \en The point on the surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const;     // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const;     // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const;     // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const;
  virtual void    Normal   ( double & u, double & v, MbVector3D & ) const;     // \ru Нормаль. \en Normal. 
  virtual void    NormalU  ( double & u, double & v, MbVector3D & ) const;     // \ru Производная нормали. \en The derivative of normal. 
  virtual void    NormalV  ( double & u, double & v, MbVector3D & ) const;     // \ru Производная нормали. \en The derivative of normal. 
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
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
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const;   // \ru Нормаль. \en Normal. 
  virtual void   _NormalU  ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
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
                               MbVector3D & deruu, MbVector3D & dervv, MbVector3D & deruv ) const; // \ru Значения производных в точке \en Values of derivatives at point 
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
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна вдоль u. \en Curvature along u. 
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна вдоль v. \en Curvature along v. 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const;
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Построить смещенную поверхность. \en Create a shifted surface. 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en Spatial copy of 'v = const'-line. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 
  virtual MbCurve3D * CurveUV( const MbLineSegment &, bool bApprox = true ) const; // \ru Пространственная копия линии по параметрической линии. \en Spatial copy of line by parametric line. 

  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const;
  // \ru Пересечение с кривой. \en Intersection with curve. 
  virtual void    CurveIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                     bool ext0, bool ext, bool touchInclude = false ) const;

  // \ru Определение точки касания поверхностей с одним неподвижным параметром. \en Determination of tangency point of surfaces with one fixed parameter. 
  virtual MbeNewtonResult SurfaceTangentNewton( const MbSurface & surf1, MbeParamDir switchPar, double funcEpsilon, size_t iterLimit,
                                                double & u0, double & v0, double & u1, double & v1, bool ext0, bool ext1 ) const;

  // \ru Определение точки пересечения цилиндрической поверхности и кривой. \en Determination of intersection point of cylindrical surface and curve. 
  virtual MbeNewtonResult CurveIntersectNewton( const MbCurve3D & curve, double funcEpsilon, size_t iterLimit,
                                                double & u, double & v, double & t, bool ext0, bool ext1 ) const;
  // \ru Определение точки касания цилиндрической поверхности и кривой. \en Determination of tangency point of cylindrical surface and curve. 
  virtual MbeNewtonResult CurveTangentNewton( const MbCurve3D & curv, double funcEpsilon, size_t iterLimit,
                                              double & u, double & v, double & t, bool ext0, bool ext1 ) const;

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  virtual bool    GetCylinderAxis( MbAxis3D & axis ) const; // \ru Дать ось вращения для поверхности. \en Get a rotation axis of a surface. 
  virtual bool    GetCenterLines( std::vector<MbCurve3D *> & clCurves ) const; // \ru Дать осевые (центральные) линии для поверхности. \en Get center lines of a surface.
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const; // \ru Является ли поверхность скруглением. \en Whether the surface is fillet. 
  virtual MbeParamDir GetFilletDirection() const; // \ru Направление поверхности скругления. \en Direction of fillet surface. 
  virtual ThreeStates Salient() const; // \ru Выпуклая ли поверхность. \en Whether the surface is convex. 

  virtual double  GetUParamToUnit() const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit() const;  // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual double  GetUParamToUnit( double u, double v ) const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit( double u, double v ) const; // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual void    GetParamsToUnit( double u, double v, double & uParam, double & vParam ) const; // \ru Дать приращение параметра u и параметра v, соответствующее единичной длине в пространстве. \en Get increment of parameters, corresponding to the unit length in space.  

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  virtual void    CalculateGabarit( MbCube & ) const; // \ru Рассчитать габарит поверхности. \en Calculate bounding box of surface. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  // \ru Является ли объект смещением. \en Is the object is a shift? 
  virtual bool    IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;

  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
          
  virtual void    SetLimit( double u1, double v1, double u2, double v2 );
  virtual void    SetExtendedParamRegion( double u1, double v1, double u2, double v2 );
  virtual void    IncludePoint( double u, double v ); // \ru Включить точку в область определения \en Include point into domain 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u \en Get the count of polygons by u 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v \en Get the count of polygons by v 

  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю \en If true, then all the derivatives by V higher the first one are equal to zero 
  /** \} */  
  /** \ru \name Функции элементарных поверхностей
      \en \name Functions of elementary surfaces
      \{ */
  virtual bool    GetPointProjection( const MbCartPoint3D & p, bool init, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const;
  /** \} */  
  /** \ru \name Функции цилиндрической поверхности
      \en \name Functions of the cylindrical surface
      \{ */ 
          /// \ru Получить внутренний радиус. \en Get internal radius. 
          double  GetR() const { return radius; } 
          /// \ru Установить внутренний радиус. \en Set an internal radius. 
          void    SetR( double r ) { radius = r; SetDirtyGabarit(); } 

          /// \ru Изменение внутренней высоты. \en Change internal height. 
          void    SetHeight( double h ) { height = h; SetDirtyGabarit(); } 
          /** \brief \ru Внутренняя высота.
                     \en Internal height. \~
              \details \ru Внутренняя высота. \n
                           Чтобы получить физическую высоту нужно внутреннюю высоту умножить 
                           на параметрическую длину по V и 
                           длину оси Z ЛСК поверхности. \n
                       \en Internal height. \n
                           To obtain the physical height you need to multiply the internal height 
                           by the parametric length along V and 
                           the length of the Z axis of the local coordinate system of the surface. \~
          */
          double  GetHeight() const { return height; } 
          /// \ru Выдать физическую высоту. \en Get physical height. \~
          double  GetRealHeight() const { return ( height * (vmax - vmin) * position.GetAxisZ().Length() ); } 

          /// \ru Дать точку на оси цилиндра. \en Get point on axis of cylinder. 
          void    GetAxisPoint( double v, MbCartPoint3D & pnt ) const; 
  /** \} */ 
private:
  inline  void    CheckParam( double & u, double & v ) const; // \ru Проверить параметры. \en Check parameters. 
          // \ru Пересечение с прямолинейной кривой. \en Intersection with rectilinear curve. 
          bool    StraightIntersection( const MbCurve3D & curv, SArray<MbCartPoint> & uv, SArray<double> & tt, bool ext0, bool ext ) const;
          void    operator = ( const MbCylinderSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCylinderSurface )
};

IMPL_PERSISTENT_OPS( MbCylinderSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры \en Check parameters 
// ---
inline void MbCylinderSurface::CheckParam( double & u, double & v ) const
{
  if ( (u < umin) || (u > umax) ) {
    if ( uclosed )
      u -= ::floor( (u - umin) * Math::invPI2 ) * M_PI2;
    else if ( u < umin )
      u = umin;
    else
      u = umax;
  }
  if ( v < vmin )
    v = vmin;
  else if ( v > vmax )
    v = vmax;
}


#endif // __SURF_CYLINDER_SURFACE_H
