////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Плоскость.
         \en A plane. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_PLANE_H
#define __SURF_PLANE_H


#include <surf_elementary_surface.h>


class  MATH_CLASS  MbCurve;
class  MATH_CLASS  MbLine3D;


//------------------------------------------------------------------------------
/** \brief \ru Плоскость.
           \en A plane. \~
  \details \ru Плоскость располагается в координатной плоскости XY местной системы координат position. \n
    Параметры плоскости отсчитываются от начала координат position.origin.
    Первый параметр плоскости отсчитывается по оси position.axisX, второй параметр плоскости отсчитывается по оси position.axisY. \n
    Плоскость ведёт себя как бесконечная поверхность, хотя в своих данных имеет граничные значения параметров umin, umax и vmin, vmax. 
    В отличие от других поверхностей Функции PointOn и Derive... плоскости не корректируют
    параметры при выходе их за пределы прямоугольной области определения параметров. \n
 	  Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = position.origin + (u position.axisX) + (v position.axisY). \n
           \en A plane is located on the XY coordinate plane of the local coordinate system 'position'. \n
    Parameters of plane are calculated from the coordinates origin 'position.origin'.
    The first parameter of plane is calculated on the axis 'position.axisX', the second parameter of plane is calculated on the axis 'position.axisY'. \n
    A plane behaves like an infinite surface, although it has boundary parameter values umin, umax and vmin, vmax.  
    In contrast to other surfaces functions PointOn and Derive.. of plane don't correct
    parameters when getting out of rectangular domain bounds. \n \n
 	  Radius-vector of the surface is described by the vector function \n
    r(u,v) = position.origin + (u position.axisX) + (v position.axisY). \n \~
  \ingroup Surfaces
*/ // ---
class MATH_CLASS MbPlane : public MbElementarySurface {

public:
  MbPlane ();
  /// \ru Конструктор по локальной системе координат. \en Constructor by a local coordinate system. 
  MbPlane ( const MbPlacement3D & initPlane ); 
  /// \ru Конструктор по трем точкам. \en Constructor by three points. 
  MbPlane ( const MbCartPoint3D & c0, const MbCartPoint3D & c1, const MbCartPoint3D & c2 ); 
  /// \ru Конструктор по центру и осям X и Z. \en Constructor by center and axes X and Z. 
  MbPlane ( const MbCartPoint3D & c0, const MbCartPoint3D & ax, const MbVector3D & aZ ); 
  /// \ru Конструктор по центру и осям X и Y. \en Constructor by center and axes X and Y.  
  MbPlane ( const MbCartPoint3D & c0, const MbVector3D & ax, const MbVector3D & ay ); 
  /// \ru Конструктор построения смещенной плоскости. \en Constructor of shifted plane. 
  MbPlane ( const MbPlacement3D &, double distance ); 
protected:
  MbPlane ( const MbPlane & );
public:
  virtual ~MbPlane();

public:
  VISITING_CLASS( MbPlane );
  
  /** \ru \name Функции инициализации
      \en \name Initialization functions 
      \{ */
          /// \ru Инициализация по плоскости. \en Initialization by plane. 
          void    Init( const MbPlane & ); 
          
          /** \brief \ru Инициализация по системе координат и расстоянию.
                     \en Initialization by coordinate system and distance. \~
            \details \ru Инициализация плоскости системой координат init co сдвигом на 
              расстояние distance в направлении нормали (оси Z).
                     \en Initialization by coordinate system and translation by 
              the distance 'distance' in direction of the normal vector (Z axis). \~
            \param[in] init - \ru Система координат
                              \en Coordinate system \~
            \param[in] distance - \ru Расстояние
                                  \en Distance \~
          */
          void    Init( const MbPlacement3D & init, double distance ); 
         
          /** \brief \ru Инициализация по точке и системе координат.
                     \en Initialization by point and coordinate system. \~
            \details \ru Инициализация по точке и системе координат.\n
              В результате получаем плоскость с правой системой координат.
                     \en Initialization by point and coordinate system.\n
              The result is a plane with right coordinate system. \~
            \param[in] p - \ru Точка, определяет положение начала системы координат плоскости
                           \en A point, it defines location of the plane origin. \~
            \param[in] init - \ru Система координат, определяет направление осей Z, X
                              \en A coordinate system, it defines direction of Z and X axes. \~
          */
          void    Init( const MbCartPoint3D & p, const MbPlacement3D & init ); 
          
          /** \brief \ru Инициализация по точке.
                     \en Initialize by point. \~
            \details \ru Инициализация по точке.\n
              В результате получаем плоскость с правой системой координат.\n
              Направление осей координат Z, X остается.
                     \en Initialization by point.\n
              The result is a plane with right coordinate system.\n
              Directions of Z and X axes remain. \~
            \param[in] p - \ru Точка, определяет положение начала системы координат плоскости
                           \en A point, it defines location of the plane origin. \~             
          */
          void    Init( const MbCartPoint3D & p );

          /** \brief \ru Инициализация по системе координат, углу, кривой и параметру.
                     \en Initialization by coordinate system, angle, curve and parameter. \~
            \details \ru Инициализация по системе координат, углу, кривой и параметру.\n  
              В случае успеха получаем плоскость:\n
                с правой системой координат;\n
                центр системы координат определяет точка кривой curve с параметром t;\n
                направление оси X показывает вектор производной кривой curve в точке с параметром t;\n
                направление оси Z показывает ось Z системы координат init, повернутая вокруг оси с направлением - 
                осью X на угол angle.
                     \en Initialization by coordinate system, angle, curve and parameter.\n  
              In case of success we get a plane:\n
                with right coordinate system,\n
                center of coordinate system is defined by a point on a curve 'curve' with parameter t;\n
                direction of the axis X is defined by the derivative vector of a curve 'curve' in the point with parameter t;\n
                direction of Z axis is defined by Z axis of the coordinate system 'init' rotated around the axis with the direction of  
                X axis by the angle 'angle'. \~
            \param[in] init - \ru Система координат
                              \en Coordinate system \~   
            \param[in] ang - \ru Угол
                             \en Angle \~
            \param[in] curve - \ru Кривая
                               \en Curve \~
            \param[in] t - \ru Параметр на кривой
                           \en Parameter on curve \~
            \return \ru true в случае успеха
                    \en Returns true in case of success. \~
          */
          bool    Init( const MbPlacement3D & init, double ang, MbCurve3D & curve, double t = 0 );
          
          /** \brief \ru Инициализация по точке, кривой и параметру.
                     \en Initialization by point, curve and parameter. \~
            \details \ru Инициализация по точке, кривой и параметру.\n
              В случае успеха получаем плоскость:\n
                с началом координат в точке на кривой curve с параметром t;\n
                направление оси X показывает вектор производной кривой в точке с параметром t;\n
                направление оси Y показывает вектор из точки на кривой в точку p.
                     \en Initialization by point, curve and parameter.\n
              In case of success we get a plane:\n
                with origin at the point of the curve with parameter t;\n
                direction of the axis X is defined by the derivative vector of a curve in the point with parameter t;\n
                direction of Y axis is defined by the vector from the point on the curve to point p. \~           
            \param[in] p - \ru Точка
                           \en Point \~
            \param[in] curve - \ru Кривая
                               \en Curve \~
            \param[in] t - \ru Параметр на кривой
                           \en Parameter on curve \~
            \return \ru true в случае успеха
                    \en Returns true in case of success. \~
          */
          bool    Init( const MbCartPoint3D & p, MbCurve3D & curve, double t = 0 );
          
          /** \brief \ru Инициализация по точке, перпендикулярно кривой.
                     \en Initialization by point, perpendicularly to curve. \~
            \details \ru Инициализация по точке, перпендикулярно кривой.
                     \en Initialization by point, perpendicularly to curve. \~
            \param[in] p - \ru Точка
                           \en Point \~
            \param[in] curve - \ru Кривая
                               \en Curve \~
            \param[in] checkPlanar - \ru Использовать информацию о кривой, если он плоская.
                                     \en Use curve information, if it's planar. \~
          */
          bool    Init( const MbCurve3D & curve, const MbCartPoint3D & p, bool checkPlanar );
          
          /// \ru Инициализация по локальной системе координат. \en Initialization by local coordinate system. 
          void    Init( const MbPlacement3D & ); 
          /// \ru Инициализация по прямой и точке. \en Initialization by line and point. 
          bool    Init( const MbLine3D &,  const MbCartPoint3D & ); 
          /// \ru Инициализация по прямой и вектору. \en Initialization by line and vector. 
          bool    Init( const MbLine3D &,  const MbVector3D    & ); 
          
          /** \brief \ru Инициализация по двум прямым.
                     \en Initialization by two lines. \~
            \details \ru Инициализация по двум прямым.  
              В случа успеха инициализирует плоскость по первой прямой 
              и вектору - направлению второй прямой.
                     \en Initialization by two lines.  
              In case of success it initializes a plane by the first line 
              and direction of the second line. \~
            \param[in] line1 - \ru Первая прямая
                               \en First line. \~
            \param[in] line2 - \ru Вторая прямая
                               \en Second line \~                
          */
          bool    Init( const MbLine3D & line1,  const MbLine3D & line2 );

          /// \ru Инициализация плоскости по трем точкам. \en Initialization of plane by three points. 
          bool    Init( const MbCartPoint3D & c0, const MbCartPoint3D & c1, const MbCartPoint3D & c2 );
          
          /** \brief \ru Инициализация по плейсменту и версии.
                     \en Initialization by placement and version. \~
            \details \ru Инициализация по плейсменту и версии.
                     \en Initialization by placement and version. \~  
            \warning \ru Только для использования в КОМПАС-3D.
                     \en This can be used only in KOMPAS-3D. \~
          */
          void    Update( const MbPlacement3D &, VERSION version ); // \ru Жёсткая привязка к плейсменту(детали) \en Rigid binding to a placement (a part) 
  /** \} */   
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );    // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равными. \en Make equal. 

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
  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            В отличии от других поверхностей функции PointOn, Derive... плоскости не корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров. 
      \en \name Functions for working at surface domain
            In contrast to other surfaces functions PointOn and Derive..  of plane don't correct parameters
            when getting out of rectangular domain bounds.
  \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en A point on surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const;
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
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по u. \en Second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по v. \en Second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
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
      \en \name Function of moving on surface 
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
  virtual void    GetLimitPoint( ptrdiff_t number, MbCartPoint3D & pnt ) const;
  virtual void    GetLimitPoint( ptrdiff_t number, MbCartPoint   & pnt ) const;

  virtual double  CurvatureU ( double u, double v ) const; // \ru Кривизна линии u. \en Curvature of the line u. 
  virtual double  CurvatureV ( double u, double v ) const; // \ru Кривизна линии v. \en Curvature of the line v. 

  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской \en Whether a surface is planar. 

  virtual MbSplineSurface * NurbsSurface( double u1, double u2, double v1, double v2, bool bmatch = false ) const; // \ru NURBS копия поверхности \en NURBS copy of surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const;
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Creation of an offset surface. 

  virtual MbCurve3D * CurveU ( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const \en A spatial copy of the line v = const. 
  virtual MbCurve3D * CurveV ( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const \en A spatial copy of the line u = const. 
  virtual MbCurve3D * CurveUV( const MbLineSegment &, bool bApprox = true ) const; // \ru Пространственная копия линии по параметрической линии \en A spatial copy of line by parametric line. 

  // \ru С какой стороны от плоскости находится точка. \en Point location relative to the plane. 
  // \ru Возвращает результат : \en Returns result: 
  // \ru iloc_InItem = 1 - точка находится над плоскостью, \en Iloc_InItem = 1 - point is located above the plane, 
  // \ru iloc_OnItem = 0 - точка находится на плоскости, \en Iloc_OnItem = 0 - point is located on the plane, 
  // \ru iloc_OutOfItem = -1 - точка находится под плоскостью. \en Iloc_OutOfItem = -1 - point is located below the plane. 
  virtual MbeItemLocation PointRelative  ( const MbCartPoint3D & pnt, double eps = ANGLE_REGION ) const;
  virtual double  DistanceToPoint( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate the distance to a point. 
  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & v, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const;
  // \ru Ближайшая проекция точки на поверхность в направлении вектора. \en The nearest projection of a point to the surface in direction of the vector. 
  virtual bool    NearDirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vector,
                                             double & u, double & v, bool ext, MbRect2D * uvRange = NULL, bool onlyPositiveDirection = false ) const;
  // \ru Пересечения с линией. \en Intersection with a line. 
  virtual MbeNewtonResult CurveIntersectNewton( const MbCurve3D &, double funcEpsilon, size_t limit,
                                                double & u, double & v, double & t, bool ext0, bool ext ) const; // \ru Нахождениe точки пересечения c кривой. \en Search of a point of intersection with curve. 
  virtual void    CurveIntersection   ( const MbCurve3D &, SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                        bool ext0, bool ext, bool touchInclude = false ) const; // \ru Все точки пересечения плоскости и кривой. \en All points of intersection between a plane and a curve. 
  // \ru Пересечение с поверхностью. \en Intersection with surface. 
  virtual MbeNewtonResult SurfaceIntersectNewton( const MbSurface & surf, MbeParamDir switchPar, double funcEpsilon, size_t limit,
                                                  double & u0, double & v0, double & u1, double & v1, bool ext0, bool ext1 ) const;
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces are similar to merge. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric region to the parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;

  virtual double  GetParamDelta() const; // \ru Дать максимальное приращение параметра. \en Get the maximum increment of parameter. 
  virtual double  GetParamPrice() const; // \ru Дать мимнимально различимую величину параметра. \en Get the minimum distinguishable value of parameter. 

  virtual double  GetUParamToUnit() const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit() const;  // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual double  GetUParamToUnit( double u, double v ) const; // \ru Дать приращение параметра u, соответствующее единичной длине в пространстве. \en Get increment of u-parameter, corresponding to the unit length in space. 
  virtual double  GetVParamToUnit( double u, double v ) const; // \ru Дать приращение параметра v, соответствующее единичной длине в пространстве. \en Get increment of v-parameter, corresponding to the unit length in space. 
  virtual void    GetParamsToUnit( double u, double v, double & uParam, double & vParam ) const; // \ru Дать приращение параметра u и параметра v, соответствующее единичной длине в пространстве. \en Get increment of parameters, corresponding to the unit length in space.  

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine a splitting of parametric region of a surface by verticals and horizontals. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;
  
  virtual void    CalculateGabarit( MbCube &gab ) const; // \ru Выдать габарит поверхности. \en Get bounding box of surface. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  virtual void    SetLimit( double u1, double v1, double u2, double v2 );
  virtual void    SetExtendedParamRegion( double u1, double v1, double u2, double v2 );
  virtual void    IncludePoint( double u, double v ); // \ru Включить точку в область определения. \en Include a point into domain. 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the number of polygons in u-direction. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the number of polygons in v-direction. 

  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю. \en If it equals true then all derivatives with respect to u which have more than first order are equal to null. 
  virtual bool    IsLineV() const; // \ru Если true все производные по V выше первой равны нулю. \en If it equals true then all derivatives with respect to v which have more than first order are equal to null.    
  
  virtual bool    IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект смещением. \en Is the object a shift? 
  /** \} */
  /** \ru \name Функции элементарных поверхностей
      \en \name Functions of elementary surfaces.
      \{ */
  virtual bool    GetPointProjection( const MbCartPoint3D & p, bool init, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const;
  /** \} */
  /** \ru \name Функции плоскости
      \en \name Functions of plane.
      \{ */
          /// \ru Пересекается ли габаритный куб поверхности с плоскостью. \en Whether the bounding cube of a surface intersects a plane. 
          bool    CubeIntersection( const MbSurface & ) const; 
          /// \ru Пересекается ли плоскость с кубом. \en Whether a plane intersects a cube. 
          bool    Intersect( const MbCube & c ) const; 
          
          /** \brief \ru Установить пределы поверхности.
                     \en Set surface limits. \~
              \details \ru Установить пределы поверхности квадратом с центром в начале координат    
                и стороной, равной 2 * d.
                       \en Set surface limits by the square with a center in origin    
                and a side equal to 2 * d. \~
          */ 
          void    SetLimit( double d )            { umax = vmax = ::fabs(d); umin = vmin = -::fabs(d); }
          
          /** \brief \ru Установить пределы поверхности.
                     \en Set surface limits. \~
              \details \ru Установить пределы поверхности прямоугольником с центром в начале координат,
                шириной, равной 2 * u, и высотой, равной 2 * v.
                       \en Set surface limits by the rectangle with a center in origin,
                width equal to 2 * u and height equal to 2 * v. \~
          */
          void    SetLimit( double u, double v )  { umax = ::fabs(u); vmax = ::fabs(v); umin = -umax; vmin = -vmax; }

          /** \brief \ru Включить проекцию куба.
                     \en Include a cube projection. \~
              \details \ru Расширить пределы плоскости, добавив проекцию куба.
                       \en Extend the plane limits by adding of the cube projection. \~
          */
          bool    IncludeCube( const MbCube & ); 

          /** \brief \ru Установить проекцию куба.
                     \en Set cube projection. \~
              \details \ru Изменить пределы плоскости на проекцию куба на плоскость.
                       \en Change the limits of plane to the cube projection on plane. \~
          */
          bool    AssignCube ( const MbCube & ); 

          /// \ru Синус угла прямой с плоскостью. \en A sine of an angle between the line and the plane. 
          double  GetNormalAngle( const MbLine3D & line ) const; 
          /// \ru Матрица для преобразования симметрии относительно плоскости. \en The matrix of symmetry transformation relative to the plane 
          void    Symmetry   ( MbMatrix3D & m ) const { position.Symmetry(m); } 
          /// \ru Инвертировать нормаль плоскости. \en Invert the normal of plane. 
          void    Invert( MbMatrix * = NULL, MbRegTransform * ireg = NULL ); 

          /// \ru Сделать систему координат правой. \en Make the coordinate system right. 
          void    SetRightPlacement()                     { position.SetRight();      SetDirtyGabarit(); }
          
          /** \brief \ru Совместить с плейсментом.
                     \en Match with the placement. \~
            \details \ru Совместить с плейсментом путем вращения до параллельности и перемещения вдоль нормали плейсмента.\n
              Центром плоскости становится проекция центра системы координат p.\n 
              Ось Z плоскости сохраняется.\n
              Осью X плоскости становится проекция оси X системы координат p.
                     \en Match with the placement by rotation till the parallelism and translation along placement normal.
              The projection of the coordinate system p origin becomes the center of a plane.\n 
              The axis Z of a plane remains.\n
              The projection X axis of the coordinate system p becomes the axis X of the plane. \~
            \warning \ru Только для использования в КОМПАС-3D.
                     \en This can be used only in KOMPAS-3D. \~
          */
          void    AdaptToPlace( const MbPlacement3D & p ) { position.AdaptToPlace(p); SetDirtyGabarit(); }
          
          /// \ru Установить систему координат. \en Set the coordinate system. 
          void    SetPlacement( const MbPlacement3D & p ) { position.Init(p);         SetDirtyGabarit(); }
          
          /** \brief \ru Точки пересечения плоскости и плоской кривой.
                     \en Intersection points of a plane and a planar curve. \~
            \details \ru Точки пересечения плоскости и плоской кривой.
                     \en Intersection points of a plane and a planar curve. \~
            \param[in] curvePlace - \ru Плейсмент кривой
                                    \en Curve placement \~
            \param[in] curve - \ru Кривая
                               \en Curve \~
            \param[out] uv - \ru Точки пересечения на плоскости
                             \en Intersection points on plane \~ 
            \param[out] tt - \ru Параметры точек пересечения на кривой
                             \en Parameters of intersection points on curve \~
            \param[in] ext0 - \ru Признак поиска точек пересечения на продолжении плоскости
                              \en An attribute of search of intersection points on the plane extension \~
            \param[in] ext - \ru Признак поиска точек пересечения на продолжении кривой
                             \en An attribute of search of intersection points on the curve extension \~
            \param[in] touchInclude - \ru true, если нужны точки касания
                                      \en True if tangency points are required \~
          */
          void    PlaneCurveIntersection( const MbPlacement3D & curvePlace, MbCurve & curve,
                                          SArray<MbCartPoint> & uv, SArray<double> & tt, 
                                          bool ext0, bool ext, bool touchInclude = false ) const;

          // \ru Подобные ли поверхности для объединения (слива) проверкой по угловым точкам \en Whether surfaces are similar to merge with check by angular points      
          /** \brief \ru Подобны ли плоскости для объединения.
                     \en Whether planes are similar to merge. \~
            \details \ru Подобны ли плоскости для объединения.
                     \en Whether planes are similar to merge. \~
            \param[in] plane - \ru Вторая плоскость
                               \en Second plane \~
            \param[in] rect0 - \ru Область параметров на первой плоскости
                               \en Parameter region on the first plane \~
            \param[in] rect1 - \ru Область параметров на второй плоскости
                               \en Parameter region on the second plane \~
          */
          bool    IsSimilarPlanes( const MbPlane & plane, const MbRect & rect0, const MbRect & rect1 ) const;
          
          /// \ru Является ли габарит плоскости вырожденным. \en Whether the bounding box of a plane is degenerate. 
          bool    IsAreaDegenerate() const; 
  /** \} */

private:
          void    operator = ( const MbPlane & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbPlane )
}; // MbPlane

IMPL_PERSISTENT_OPS( MbPlane )

//------------------------------------------------------------------------------
// \ru Пересечение с граничным прямоугольником \en Intersection with the bounding rectangle. 
// ---
bool LineClassification( const MbCartPoint & p, const MbVector & direct,
                         double umin, double vmin, double umax, double vmax,
                         double & tmin, double & tmax );


//------------------------------------------------------------------------------
/** \brief \ru Пересечение или расстояние между бесконечной прямой и бесконечной плоскостью.
           \en Intersection or distance between infinite line and infinite plane. \~
  \details \ru Пересечение бесконечной прямой и бесконечной плоскости\n
    или расстояние между бесконечной прямой и бесконечной плоскостью.
           \en Intersection of infinite line and infinite plane.\n
    or distance between infinite line and infinite plane. \~
  \param[in] line1 - \ru Прямая
                     \en Line \~
  \param[in] plane2 - \ru Плоскость
                      \en Plane \~
  \param[out] p1 - \ru Точка пересечения на кривой
                   \en Intersection point on curve \~
  \param[out] p2 - \ru Точка пересечения на плоскости
                   \en Intersection point on plane \~  
  \return \ru Расстояние между прямой и плоскостью
          \en Distance between line and plane \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (double) LinePlaneNearestPoints( const MbLine3D & line1, const MbPlane & plane2,
                                           MbCartPoint3D & p1, MbCartPoint3D & p2 );


//------------------------------------------------------------------------------
/** \brief \ru Пересечение двух бесконечных плоскостей
           \en Intersection of two infinite planes \~
  \details \ru Пересечение двух бесконечных плоскостей
           \en Intersection of two infinite planes \~
  \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (MbLine3D *) PlanesIntersection( const MbPlane & plane1, const MbPlane & plane2 );


#endif // __SURF_PLANE_H
