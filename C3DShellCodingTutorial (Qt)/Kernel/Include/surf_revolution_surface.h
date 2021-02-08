////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность вращения.
         \en Revolution surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_REVOLUTION_SURFACE_H
#define __SURF_REVOLUTION_SURFACE_H


#include <surf_swept_surface.h>
#include <templ_dptr.h>
#include <mb_placement3d.h>
#include <mb_matrix3d.h>


class             MbSurfaceContiguousData;
class  MATH_CLASS MbOffsetSurface;


//------------------------------------------------------------------------------
/** \brief \ru Поверхность вращения.
           \en Revolution surface. \~
  \details \ru Поверхность вращения является кинематической поверхностью с образующей в форме дуги окружности. 
    Поверхность вращения получена путем движения образующей кривой curve по окружности или её дуге.
 	  Радиус-вектор поверхности описывается векторной функцией \n
    r(u,v) = position.origin + M(v)(curve(u) - position.origin), \n
    где M(v) - матрица поворота точки вокруг оси position.axisZ. \n
    Первый параметр поверхности совпадает с параметром образующей кривой. 
    Второй параметр поверхности совпадает с углом поворота образующей кривой.
           \en A revolution surface is a swept surface with generatrix in a circle arc form. 
    A revolution surface is obtained by moving of the generatrix 'curve' along the circle or its arc.
 	  Radius-vector of line surface is described by the vector function \n
    r(u,v) = position.origin + M(v)(curve(u) - position.origin), \n
    where M(v) - rotate matrix by axis position.axisZ. \n
    The first surface parameter coincides with the parameter of generatrix. 
    The second surface parameter coincides with the rotation angle of generatrix. \~ 
  \ingroup Surfaces
*/ // ---
class MATH_CLASS MbRevolutionSurface : public MbSweptSurface {
private:
  MbPlacement3D position;  ///< \ru Местная система координат (position.axisZ - ось вращения). \en Local coordinate system ('position.axisZ' is rotation axis). 
  double        uPoleMin;  ///< \ru Значение параметра U в полюсе поверхности, если он есть. \en A value of U parameter in the pole of a surface if it exists. 
  double        uPoleMax;  ///< \ru Значение параметра U в полюсе поверхности, если он есть. \en A value of U parameter in the pole of a surface if it exists. 
  bool          poleMin;   ///< \ru Наличие полюса при umin. \en Existence of a pole at umin. 
  bool          poleMax;   ///< \ru Наличие полюса при umax. \en Existence of a pole at umax. 
  bool          planeData; ///< \ru Кривая лежит в плоскости, содержащей ось вращения, (частный случай). \en A curve is located on a plane which contains the rotation axis (special case). 
  MbMatrix3D    into;      ///< \ru Матрица преобразования в систему position. \en Matrix of transformation to the system 'position'. 
  MbMatrix3D    from;      ///< \ru Матрица преобразования из системы position. \en Matrix of transformation from the system 'position'. 
  double    uMinNormDelta; ///< \ru Величина отступа от минимального  параметра u при подсчете нормали в полюсе. \en A value of indent from the minimum value of u in the calculation of normal vector in pole. 
  double    uMaxNormDelta; ///< \ru Величина отступа от максимального параметра u при подсчете нормали в полюсе. \en A value of indent from the maximum value of u in the calculation of normal vector in pole. 

protected:
  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
  \en Auxiliary data. \~
  \details \ru Вспомогательные данные служат для ускорения работы объекта.
  \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbRevolutionSurfaceAuxiliaryData : public AuxiliaryData {
  public:
    DPtr<MbSurfaceContiguousData> data;  ///< \ru Дополнительные данные о поверхности. \en Additional data about a surface. 
    MbRevolutionSurfaceAuxiliaryData();
    MbRevolutionSurfaceAuxiliaryData( const MbRevolutionSurfaceAuxiliaryData & init );
    virtual ~MbRevolutionSurfaceAuxiliaryData();
  };

  mutable CacheManager<MbRevolutionSurfaceAuxiliaryData> cache;
  
public:
 
  /** \brief \ru Конструктор по образующей, началу и оси Z локальной системы координат и углу.
             \en Constructor by generatrix, origin, Z axis of the local coordinate system and angle. \~ 
    \details \ru Конструктор по образующей, началу и оси Z локальной системы координат и углу.
             \en Constructor by generatrix, origin, Z axis of the local coordinate system and angle. \~ 
    \param[in] c - \ru Образующая кривая
                   \en Generating curve \~
    \param[in] p - \ru Начало оси вращения
                   \en Origin of rotation axis \~
    \param[in] a - \ru Направление оси вращения
                   \en Rotation axis direction \~
    \param[in] angle - \ru Угол вращения
                       \en Rotation angle \~
    \param[in] same - \ru Признак использования оригинала образующей кривой, а не её копии.
                      \en Attribute of using the original of generating curve instead of its copy. \~
  */
  MbRevolutionSurface( const MbCurve3D & c, const MbCartPoint3D & p, const MbVector3D & a, double angle, bool same );
  
  /** \brief \ru Конструктор по образующей, оси вращения и углу.
             \en Constructor by generatrix, rotation axis and angle. \~ 
    \details \ru Конструктор по образующей, оси вращения и углу.
             \en Constructor by generatrix, rotation axis and angle. \~ 
    \param[in] c - \ru Образующая кривая
                   \en Generating curve \~      
    \param[in] a - \ru Ось вращения
                   \en Rotation axis \~
    \param[in] angle - \ru Угол вращения
                       \en Rotation angle \~
    \param[in] same - \ru Признак использования оригинала образующей кривой, а не её копии.
                      \en Attribute of using the original of generating curve instead of its copy. \~
  */
  MbRevolutionSurface( const MbCurve3D & c, const MbAxis3D & a, double angle, bool same );
  
  /** \brief \ru Конструктор по образующей, оси вращения, минимальному и максимальному углу.
             \en Constructor by generatrix, rotation axis, minimal and maximal angles. \~ 
    \details \ru Конструктор по образующей, оси вращения, минимальному и максимальному углу.
             \en Constructor by generatrix, rotation axis, minimal and maximal angles. \~ 
    \param[in] c - \ru Образующая кривая
                   \en Generating curve \~      
    \param[in] a - \ru Ось вращения
                   \en Rotation axis \~
    \param[in] anMin - \ru Минимальное значение угла
                       \en Minimal value of angle \~
    \param[in] anMax - \ru Максимальное значение угла
                       \en Maximal value of angle \~
    \param[in] same - \ru Признак использования оригинала образующей кривой, а не её копии.
                      \en Attribute of using the original of generating curve instead of its copy. \~
  */
  MbRevolutionSurface( const MbCurve3D & c, const MbAxis3D & a, double anMin, double anMax, bool same );  

protected:
  MbRevolutionSurface( const MbRevolutionSurface &, MbRegDuplicate * );   
private:
  // \ru Конструктор для создания эквидистанты \en Constructor for offset creation 
  MbRevolutionSurface( const MbRevolutionSurface &, MbCurve3D & offsetCurve, bool same );
public:
  virtual ~MbRevolutionSurface();

public:
  VISITING_CLASS( MbRevolutionSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object 
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
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
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
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
  virtual void   _NormalU  ( double  u, double  v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
  virtual void   _NormalV  ( double  u, double  v, MbVector3D & ) const; // \ru Производная нормали. \en Derivative of normal vector. 
  virtual void   _NormalUU ( double  u, double  v, MbVector3D & ) const;
  virtual void   _NormalUV ( double  u, double  v, MbVector3D & ) const;
  virtual void   _NormalVV ( double  u, double  v, MbVector3D & ) const;
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
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
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна линии u. \en Curvature of u line. 
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна линии v. \en Curvature of v line. 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u \en Get the number of polygons in u-direction. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v \en Get the number of polygons in v-direction. 

  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности \en NURBS copy of surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const; // \ru NURBS копия поверхности \en NURBS copy of surface. 
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности \en Creation of an offset surface 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const \en A spatial copy of the line v = const. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const \en A spatial copy of the line u = const. 

  // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection on the surface. 
  virtual bool    NearPointProjection( const MbCartPoint3D & p, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection on the surface. 
  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & p, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const;

  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces are similar to merge. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric region to the parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  
  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces are similar to merge 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;

  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const; // \ru Является ли поверхность скруглением. \en Whether the surface is fillet. 
  virtual MbeParamDir GetFilletDirection() const; // \ru Направление поверхности скругления. \en Direction of fillet surface. 
  virtual ThreeStates Salient() const; // \ru Выпуклая ли поверхность. \en Whether a surface is convex. 
  virtual bool    GetCylinderAxis( MbAxis3D & axis ) const ; // \ru Дать ось поверхности. \en Get the axis of a surface. 
  virtual bool    GetCenterLines( std::vector<MbCurve3D *> & clCurves ) const; // \ru Дать осевые (центральные) линии для поверхности. \en Get center lines of a surface.
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine a splitting of parametric region of a surface by verticals and horizontals. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;
  // \ru Существует ли полюс на границе параметрической области сплайновой кривой. \en Whether a pole exists on parametric region boundary of spline curve. 
  virtual bool    GetPoleUMin() const;
  virtual bool    GetPoleUMax() const;
  virtual bool    IsPole( double u, double v ) const; // \ru Является ли точка особенной. \en Whether the point is singular. 
  
  virtual bool    IsRectangular() const; // \ru Если true производные по u и v ортогональны. \en If true then derivatives with respect to u and v are orthogonal. 
  virtual bool    IsLineU() const; // \ru Если true все производные по U выше первой равны нулю. \en If it equals true then all derivatives with respect to u which have more than first order are equal to null. 
  virtual void    SetLimit( double u1, double v1, double u2, double v2 ); 
  /** \} */
  /** \ru \name Функции поверхности вращения
      \en \name Function of revolution surface.
      \{ */ 
          double          GetAngle() const { return vmax - vmin; } ///< \ru Угол вращения. \en Rotation angle. 
          MbAxis3D        GetAxis  () const; ///< \ru Ось вращения. \en Rotation axis. 
  const   MbCartPoint3D & GetOrigin() const { return position.GetOrigin(); } ///< \ru Центр локальной системы координат. \en Center of the local coordinate system. 
  const   MbVector3D    & GetAxisZ () const { return position.GetAxisZ();  } ///< \ru Направление оси вращения. \en Rotation axis direction. 
  const   MbPlacement3D & GetPlacement() const { return position; } ///< \ru Локальная система координат. \en Local coordinate system. 
          void    SetAxis( const MbAxis3D & initAxis ); ///< \ru Установить ось вращения. \en Set rotation axis. 

          /// \ru Лежит ли образующая кривая в плоскости, содержащей ось вращения. \en Whether generating curve lies on a plane containing the rotation axis. 
          bool    IsPlaneData() const { return planeData; }              
          
          /** \brief \ru Единичный вектор - направление оси X локальной системы координат.
                     \en Unit vector - direction of the X axis of the local coordinate system. \~ 
            \details \ru Единичный вектор - направление оси X локальной системы координат.\n
              В случае, если образующая кривая лежит в плоскости, содержащей ось вращения,
              вектор является единичным вектором в плоскости образующей кривой.
                     \en Unit vector - direction of the X axis of the local coordinate system.\n
              In a case when generating curve lies on a plane containing rotation axis
              the vector is a unit vector in a plane of generating curve. \~ 
            \param[out] axis - \ru Вектор - результат
                               \en A vector - the result \~
            \result \ru true, если образующая кривая лежит в плоскости, содержащей ось вращеOния, и
              локальная система координат поверхности является ортогональной и изотропной по осям.
                    \en True if generating curve lies on a plane containing rotation axis and
              the local coordinate system of a surface is orthogonal and isotropic by the axes. \~
          */
          bool    GetPlaneDataAxis( MbVector3D & axis ) const;
          
          /** \brief \ru Создание эквидистантной поверхности.
                     \en Creation of an offset surface. \~
            \details \ru Создание поверхности типа st_OffsetSurface, совпадающей с данной поверхностью.\n
              Если образующая кривая является эквидистантной кривой на плоскости,
              то, используя ее базовую кривую в качестве образующей, создается поверхность
              вращения и по ней эквидистантная поверхность.\n
              Поверхность строится в случае, если образующая кривая лежит в плоскости, содержащей ось вращения.\n
              Используется только в конвертерах.
                     \en Creation of a surface of the type OffsetSurface coincident with the given surface. \n
              If the generating curve is an offset curve on a plane
              then using its basis curve as generatrix a revolution surface is created
              and an offset surface is created by it. \n
              A surface is constructed in case when generating curve lies on a plane containing rotation axis. \n
              This is used only in converters. \~
          */
          MbOffsetSurface * GetSurfaceFromPlaneCurveOffset() const;

          /// \ru Дать максимальный радиус поверхности, если это возможно. \en Get maximum radius of surface if it possible or null.
          double  GetMaxRadius() const;
  /** \} */

private: // \ru Внутренние функции поверхности. \en Internal functions of surface. 
          void    Init( const MbCartPoint3D & origin, const MbVector3D & axisZ, double v1, double v2 ); // \ru Продолжение конструктора. \en Continuation of constructor. 
          void    InitNormDeltaU(); // \ru Посчитать величины отступа от uMin и uMax при подсчете нормали. \en Calculate indent values from uMin  and uMax when calculation of a normal vector. 
          void    InitPosition( const MbCartPoint3D & origin, const MbVector3D & axisZ );
          void    ExactNormal( double u, double v, const MbVector3D & derU, const MbVector3D & derV, MbVector3D & nor ) const; // \ru Нормаль. \en Normal. 
          void    CheckPoles(); // \ru Проверить полюса. \en Check poles. 
  inline  void    CheckParam ( double &u, double &v ) const; // \ru Проверить параметры. \en Check parameters. 
  inline  void    CheckParam_( double &u ) const; // \ru Проверить параметр. \en Check parameter. 
  inline  void    RotateVector   ( double sinV, double cosV, MbVector3D & v ) const;
  inline  void    RotateDeriveV  ( double sinV, double cosV, MbVector3D & v ) const;          
  inline  void    RotateDeriveVV ( double sinV, double cosV, MbVector3D & v ) const;          
  inline  void    RotateDeriveVVV( double sinV, double cosV, MbVector3D & v ) const;          

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbRevolutionSurface )
  OBVIOUS_PRIVATE_COPY( MbRevolutionSurface ) // \ru Не реализовано. \en Not implemented. 
};

IMPL_PERSISTENT_OPS( MbRevolutionSurface )

//------------------------------------------------------------------------------
// \ru Проверить параметры \en Check parameters 
// ---
inline void MbRevolutionSurface::CheckParam ( double & u, double & v ) const
{
  if (v < vmin) {
    if ( vclosed )
      v -= ( ::floor((v - vmin) * Math::invPI2) * M_PI2 );
    else
      v = vmin;
  }
  if ( v > vmax ) {
    if ( vclosed )
      v -= ( ::floor((v - vmin) * Math::invPI2) * M_PI2 );
    else
      v = vmax;
  }
  if ( poleMin && (u < umin) )
    u = umin;
  if ( poleMax && (u > umax) )
    u = umax;
}


//------------------------------------------------------------------------------
// \ru Проверить параметры \en Check parameters 
// ---
inline void MbRevolutionSurface::CheckParam_( double & u ) const
{
  if ( poleMin && (u < umin) )
    u = umin;
  if ( poleMax && (u > umax) )
    u = umax;

  // BUG_58512
  if ( !poleMin && (uPoleMin != UNDEFINED_DBL) ) {
    if ( uPoleMin < umin && u < uPoleMin )
      u = uPoleMin;
  }
  if ( !poleMax && (uPoleMax != UNDEFINED_DBL) ) {
    if ( uPoleMax > umax && u > uPoleMax )
      u = uPoleMax;
  }
}


//------------------------------------------------------------------------------
// \ru Поворот вектора вокруг оси спирали \en Rotation of vector around spiral axis 
// ---
inline void MbRevolutionSurface::RotateVector( double sinV, double cosV, MbVector3D & _vector ) const
{
//  if ( planeData ) {
//    double r = _vector * axisX;
//    _vector.Set( axisX, r * cosV, axisY, r * sinV, axis.GetAxisZ(), _vector * axis.GetAxisZ() );
//  }
//  else {
//    _vector.Set( _vector, cosV, axis.GetAxisZ(), (_vector * axis.GetAxisZ()) * (1.0 - cosV), (axis.GetAxisZ() | _vector), sinV );
//  }
  _vector.Transform( into );
  double x =   (_vector.x * cosV) - (_vector.y * sinV);
  double y =   (_vector.x * sinV) + (_vector.y * cosV);
  _vector.x = x;
  _vector.y = y;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Первая производная поворота вектора вокруг оси спирали \en First derivative of vector of rotation around the spiral axis 
// ---
inline void MbRevolutionSurface::RotateDeriveV( double sinV, double cosV, MbVector3D & _vector ) const
{
//  if ( planeData ) {
//    double r = _vector * axisX;
//    _vector.Set( axisX, -r * sinV, axisY, r * cosV );
//  }
//  else {
//    _vector.Set( _vector, -sinV, axis.GetAxisZ(), (_vector * axis.GetAxisZ()) * sinV, (axis.GetAxisZ() | _vector), cosV );
//  }
  _vector.Transform( into );
  double x = - (_vector.x * sinV) - (_vector.y * cosV);
  double y =   (_vector.x * cosV) - (_vector.y * sinV);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Вторая производная поворота вектора вокруг оси спирали \en Second derivative of vector of rotation around spiral axis 
// ---
inline void MbRevolutionSurface::RotateDeriveVV( double sinV, double cosV, MbVector3D & _vector ) const 
{
//  if ( planeData ) {
//    double r = _vector * axisX;
//    _vector.Set( axisX, -r * cosV, axisY, -r * sinV );
//  }
//  else {
//    _vector.Set( _vector, -cosV, axis.GetAxisZ(), (_vector * axis.GetAxisZ()) * cosV, (axis.GetAxisZ() | _vector), -sinV );
//  }
  _vector.Transform( into );
  double x = - (_vector.x * cosV) + (_vector.y * sinV);
  double y = - (_vector.x * sinV) - (_vector.y * cosV);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


//-------------------------------------------------------------------------------
// \ru Третья производная поворота вектора вокруг оси спирали \en Third derivative of vector of rotation around spiral axis 
// ---
inline void MbRevolutionSurface::RotateDeriveVVV( double sinV, double cosV, MbVector3D & _vector ) const 
{
//  if ( planeData ) {
//    double r = _vector * axisX;
//    _vector.Set( axisX, r * sinV, axisY, -r * cosV );
//  }
//  else {
//    _vector.Set( _vector, sinV, axis.GetAxisZ(), -(_vector * axis.GetAxisZ()) * sinV, (axis.GetAxisZ() | _vector), -cosV );
//  }
  _vector.Transform( into );
  double x =   (_vector.x * sinV) + (_vector.y * cosV);
  double y = - (_vector.x * cosV) + (_vector.y * sinV);
  _vector.x = x;
  _vector.y = y;
  _vector.z = 0.0;
  _vector.Transform( from );
}


#endif // __SURF_REVOLUTION_SURFACE_H
