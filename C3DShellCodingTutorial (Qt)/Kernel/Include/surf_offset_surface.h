////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Эквидистантная поверхность.
         \en Offset surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_OFFSET_SURFACE_H
#define __SURF_OFFSET_SURFACE_H


#include <templ_three_states.h>
#include <templ_dptr.h>
#include <tool_multithreading.h>
#include <surface.h>


class MbSurfaceContiguousData;


//------------------------------------------------------------------------------
/** \brief \ru Эквидистантная и расширенная поверхность.
           \en Offset surface. \~
  \details \ru Эквидистантная поверхность построена на базовой поверхности basisSurface и располагается на расстоянии от неё, определяемом параметрами offsetUminVmin, offsetUmaxVmin, offsetUminVmax, offsetUmaxVmax. 
    Параметры offsetUminVmin, offsetUmaxVmin, offsetUminVmax, offsetUmaxVmax могут быть как больше нуля, так и меньше нуля. 
    Область определения параметров эквидистантной поверхности может отличаться от область определения параметров базовой поверхности basisSurface.
    Это отличие задано параметрами deltaUmin, deltaUmax, deltaVmin, deltaVmax.
	  Радиус-вектор эквидистантной поверхности описывается векторной функцией \n
    r(u,v) = basisSurface(u,v) + (Offset0(u,v) * basisSurface->Normal(u,v)). \n
    Базовой поверхностью для эквидистантной поверхности не может служить другая эквидистантная поверхность.
    В подобной ситуации выполняется переход к первичной базовой поверхности.
           \en The offset surface is constructed on 'basisSurface' base surface and placed at distance from it, determined by 'offsetUminVmin, offsetUmaxVmin, offsetUminVmax, offsetUmaxVmax' parameters. 
    'offsetUminVmin, offsetUmaxVmin, offsetUminVmax, offsetUmaxVmax' parameters can be both greater than zero and less than zero. 
    Domain of parameters of the offset surface can differs from domain of parameters of basisSurface base surface.
    This difference is given by the parameters deltaUmin, deltaUmax, deltaVmin, deltaVmax.
	  Radius-vector of offset surface is described by the vector function \n
    r(u,v) = basisSurface(u,v) + (Offset0(u,v) * basisSurface->Normal(u,v)). \n
    Base surface for offset surface can't be other offset surface.
    In this situation it changes to the initial base surface. \~ 
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbOffsetSurface : public MbSurface {
private:
  MbSurface *   basisSurface;   ///< \ru Базовая поверхность (всегда не NULL). \en Base surface (always not NULL). 
  double        u0min;          ///< \ru Минимальный параметр  u базовой поверхности. \en Minimal parameter u of the base surface. 
  double        u0max;          ///< \ru Максимальный параметр u базовой поверхности. \en Maximal parameter u of the base surface. 
  double        v0min;          ///< \ru Минимальный параметр  v базовой поверхности. \en Minimal parameter v of the base surface. 
  double        v0max;          ///< \ru Максимальный параметр v базовой поверхности. \en Maximal parameter v of the base surface. 
  bool          u0closed;       ///< \ru Признак замкнутости по u базовой поверхности. \en Attribute of closedness of base surface by u. 
  bool          v0closed;       ///< \ru Признак замкнутости по v базовой поверхности. \en Attribute of closedness of base surface by v. 
  double        offsetUminVmin; ///< \ru Смещение от базовой поверхности по нормали в точке [u0min v0min]. \en The offset from the base surface along normal in a point [u0min v0min]. 
  double        offsetUmaxVmin; ///< \ru Смещение от базовой поверхности по нормали в точке [u0max v0min]. \en The offset from the base surface along normal in a point [u0max v0min]. 
  double        offsetUminVmax; ///< \ru Смещение от базовой поверхности по нормали в точке [u0min v0max]. \en The offset from the base surface along normal in a point [u0min v0max]. 
  double        offsetUmaxVmax; ///< \ru Смещение от базовой поверхности по нормали в точке [u0max v0max]. \en The offset from the base surface along normal in a point [u0max v0max]. 
  MbeOffsetType type;           ///< \ru Тип смещения точек: константный, линейный или кубический. \en The type of points offset: constant, or linear, or cubic.
  double        deltaUmin;      ///< \ru Изменение параметрической области относительно параметра u0min базовой поверхности. \en The change of minimum of the first parameter relative of u0min parameter of the base surface. 
  double        deltaUmax;      ///< \ru Изменение параметрической области относительно параметра u0max базовой поверхности. \en The change of maximum of the first parameter relative of u0max parameter of the base surface. 
  double        deltaVmin;      ///< \ru Изменение параметрической области относительно параметра v0min базовой поверхности. \en The change of minimum of the second parameter relative of v0min parameter of the base surface. 
  double        deltaVmax;      ///< \ru Изменение параметрической области относительно параметра v0max базовой поверхности. \en The change of maximum of the second parameter relative of v0max parameter of the base surface. 

private:
  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbOffsetSurfaceAuxiliaryData : public AuxiliaryData {
  public:
    DPtr<MbSurfaceContiguousData> data;  ///< \ru Дополнительные данные о поверхности. \en Additional data about a surface. 
    MbOffsetSurfaceAuxiliaryData();
    MbOffsetSurfaceAuxiliaryData( const MbOffsetSurfaceAuxiliaryData & init );
    virtual ~MbOffsetSurfaceAuxiliaryData();
  };
  
  mutable CacheManager<MbOffsetSurfaceAuxiliaryData> cache;

public:

  /** \brief \ru Конструктор по базовой поверхности и смещению.
             \en Constructor by base surface and offset. \~  
    \details \ru Конструктор по базовой поверхности и смещению.
             \en Constructor by base surface and offset. \~  
    \param[in] s - \ru Базовая поверхность
                   \en Base surface \~
    \param[in] d - \ru Величина смещения
                   \en Offset distance \~
    \param[in] same - \ru Признак использования оригинала базовой поверхности, а не ее копии
                      \en Attribute of usage of original of base surface, not copy \~
  */
  MbOffsetSurface( const MbSurface & s, double d, bool same );     
  
  /** \brief \ru Конструктор по базовой поверхности и смещению c приращениями параметров.
             \en Constructor by base surface and offset with increments of parameters. \~  
    \details \ru Конструктор по базовой поверхности и смещению c приращениями параметров.\n  
      Приращение параметров нужно использовать для изменения области определения поверхности
      относительно базовой поверхности.
             \en Constructor by base surface and offset with increments of parameters.\n  
      Increment of parameters needs to be used for change of surface domain
      relative to base surface. \~
    \param[in] s -    \ru Базовая поверхность
                      \en Base surface \~
    \param[in] d -    \ru Величина смещения
                      \en Offset distance \~
    \param[in] du0 -  \ru Изменение umin параметра
                      \en The change of umin parameter \~
    \param[in] du1 -  \ru Изменение umax параметра
                      \en The change of umax parameter \~
    \param[in] dv0 -  \ru Изменение umin параметра
                      \en The change of umin parameter \~
    \param[in] dv1 -  \ru Изменение umax параметра
                      \en The change of umax parameter \~
    \param[in] same - \ru Признак использования оригинала базовой поверхности, а не ее копии.
                      \en Attribute of usage of original of base surface, not copy. \~
  */
  MbOffsetSurface( const MbSurface & s, double d, double du0, double du1, double dv0, double dv1, bool same );

  /** \brief \ru Конструктор по базовой поверхности и смещению c приращениями параметров.
             \en Constructor by base surface and offset with increments of parameters. \~  
    \details \ru Смещение задано в углах параметрической области базовой поверхности и может изменяться по константному, линейному и кубическому законам.\n  
      Приращение параметров нужно использовать для изменения области определения поверхности относительно базовой поверхности.
             \en The offset displacement is defined in the corners of the parametric region of the base surface and can be changed by constant, linear and cubic laws.\n  
      Increment of parameters needs to be used for change of surface domain relative to base surface. \~
    \param[in] s -    \ru Базовая поверхность
                      \en Base surface \~
    \param[in] d0 -   \ru Величина смещения offsetUminVmin.
                      \en Offset distance offsetUminVmin. \~
    \param[in] d1 -   \ru Величина смещения offsetUmaxVmin.
                      \en Offset distance offsetUmaxVmin. \~
    \param[in] d2 -   \ru Величина смещения offsetUminVmax.
                      \en Offset distance offsetUminVmax. \~
    \param[in] d3 -   \ru Величина смещения offsetUmaxVmax.
                      \en Offset distance offsetUmaxVmax. \~
    \param[in] t  -   \ru Тип смещения точек: константный, линейный или кубический.
                      \en The offset type: constant, or linear, or cubic. \~
    \param[in] u0 -   \ru Изменение umin параметра
                      \en The change of umin parameter \~
    \param[in] u1 -   \ru Изменение umax параметра
                      \en The change of umax parameter \~
    \param[in] v0 -   \ru Изменение umin параметра
                      \en The change of umin parameter \~
    \param[in] v1 -   \ru Изменение umax параметра
                      \en The change of umax parameter \~               
    \param[in] same - \ru Признак использования оригинала базовой поверхности, а не ее копии.
                      \en Attribute of usage of original of base surface, not copy. \~
  */
  MbOffsetSurface( const MbSurface & s, double d0, double d1, double d2, double d3, MbeOffsetType t, 
                   double u0, double u1, double v0, double v1, bool same );

protected:
  MbOffsetSurface( const MbOffsetSurface &, MbRegDuplicate * );
private:
  MbOffsetSurface( const MbOffsetSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbOffsetSurface ();

public:
  VISITING_CLASS( MbOffsetSurface );

public:
  /** \ru \name Функции инициализации
      \en \name Initialization functions
      \{ */
          /** \brief \ru Инициализация по смещению и приращениям параметров.
                     \en Initialization by offset and increments of parameters. \~  
            \details \ru Инициализация по смещению и приращениям параметров.\n  
              Приращение параметров нужно использовать для изменения области определения поверхности относительно базовой поверхности.
                     \en Initialization by offset and increments of parameters.\n  
              Increment of parameters needs to be used for change of surface domain relative to base surface. \~          
            \param[in] d0 - \ru Величина смещения offsetUminVmin.
                            \en Offset distance offsetUminVmin. \~
            \param[in] d1 - \ru Величина смещения offsetUmaxVmin.
                            \en Offset distance offsetUmaxVmin. \~
            \param[in] d2 - \ru Величина смещения offsetUminVmax.
                            \en Offset distance offsetUminVmax. \~
            \param[in] d3 - \ru Величина смещения offsetUmaxVmax.
                            \en Offset distance offsetUmaxVmax. \~
            \param[in] t  - \ru Тип смещения точек: константный, линейный или кубический.
                            \en The offset type: constant, or linear, or cubic. \~
            \param[in] u0 - \ru Изменение umin параметра
                            \en The change of umin parameter \~
            \param[in] u1 - \ru Изменение umax параметра
                            \en The change of umax parameter \~
            \param[in] v0 - \ru Изменение umin параметра
                            \en The change of umin parameter \~
            \param[in] v1 - \ru Изменение umax параметра
                            \en The change of umax parameter \~               
          */
          void    Init( double d0, double d1, double d2, double d3, MbeOffsetType t, double u0, double u1, double v0, double v1 );  
          void    Init( double d, double u0, double u1, double v0, double v1 );  
  /** \} */
  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const;      // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией. \en Whether the object is a copy. 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual bool    IsPlanar() const;                       // \ru Является ли поверхность плоской. \en Whether the surface is planar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  virtual void    Refresh(); // \ru Сбросить все временные данные \en Flush all the temporary data 
  
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые поверхности. \en Get base surfaces. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */
  /** \ru \name Функции описания области определения поверхности
      \en \name Functions for surface domain description
      \{ */
  virtual double  GetUMin   () const; // \ru Вернуть минимальное значение параметра u. \en Return the minimum value of parameter u. 
  virtual double  GetVMin   () const; // \ru Вернуть минимальное значение параметра v. \en Return the minimum value of parameter v. 
  virtual double  GetUMax   () const; // \ru Вернуть максимальное значение параметра u. \en Return the maximum value of parameter u. 
  virtual double  GetVMax   () const; // \ru Вернуть максимальное значение параметра v. \en Return the maximum value of parameter v. 
  virtual bool    IsUClosed () const; // \ru Проверка замкнутости по параметру u. \en Check of closedness by parameter u. 
  virtual bool    IsVClosed () const; // \ru Проверка замкнутости по параметру v. \en Check of closedness by parameter v. 
  virtual double  GetUPeriod() const; // \ru Период по u. \en Period by u. 
  virtual double  GetVPeriod() const; // \ru Период по v. \en Period by v. 
  virtual size_t  GetUCount() const; // \ru Получить разбиение по u. \en Get splitting by u. 
  virtual size_t  GetVCount() const; // \ru Получить разбиение по v. \en Get splitting by v. 

  virtual bool    GetPoleUMin() const;
  virtual bool    GetPoleUMax() const;
  virtual bool    GetPoleVMin() const;
  virtual bool    GetPoleVMax() const;
  virtual bool    IsPole     ( double u, double v ) const; // \ru Является ли точка особенной. \en Whether the point is special. 
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
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const; // \ru Третья производная. \en The third derivative. 
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная. \en The third derivative. 
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная. \en The third derivative. 
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная. \en The third derivative. 
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
  virtual void   _PointOn ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности. \en The point on the extended surface. 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const;   // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const;   // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const;   // \ru Третья производная. \en The third derivative. 
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const;   // \ru Третья производная. \en The third derivative. 
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const;   // \ru Третья производная. \en The third derivative. 
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const;   // \ru Третья производная. \en The third derivative. 
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const;   // \ru Нормаль. \en Normal. 
  virtual void   _NormalU  ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalV  ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalUU ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalUV ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
  virtual void   _NormalVV ( double u, double v, MbVector3D & ) const;   // \ru Производная нормали. \en The derivative of normal. 
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
      \en \name Functions of moving along the surface
      \{ */
  virtual double  StepU         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по U. \en Calculation of the approximation step with consideration of the curvature radius by U. 
  virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по V. \en Calculation of the approximation step with consideration of the curvature radius by V. 
  virtual double  DeviationStepU( double u, double v, double sag ) const; // \ru Вычисление шага по u при пересечении поверхностей. \en Calculation of step by u while intersecting surfaces. 
  virtual double  DeviationStepV( double u, double v, double sag ) const; // \ru Вычисление шага по v при пересечении поверхностей. \en Calculation of step by v while intersecting surfaces. 
  /** \} */
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна линии u. \en Curvature of u-line. 
  virtual double  CurvatureV    ( double u, double v ) const; // \ru Kривизна линии v. \en Curvature of v-line. 
  // \ru Ближайшая проекция точки на поверхность. \en The nearest point projection onto the surface. 
  virtual bool    NearPointProjection( const MbCartPoint3D & p, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const;
  // \ru Изменение носителя. \en Changing of carrier. 
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init );
  // \ru Изменение носимых элементов. \en Change a carrier elements. 
  virtual bool    ChangeCarrierBorne( const MbSurface & item, MbSurface & init, const MbMatrix & matr );
  virtual const MbSurface & GetBasisSurface() const;        // \ru Дать базовую поверхность. \en Get the base surface. 
  virtual       MbSurface & SetBasisSurface();              // \ru Дать базовую поверхность. \en Get the base surface. 

  virtual bool    GetCylinderAxis( MbAxis3D & ) const; // \ru Дать ось вращения для поверхности. \en Get a rotation axis of a surface. 
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  
  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 
  
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;
  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v. 

  // \ru Определение параметрической области поверхности. \en Returns parametric region of surface. 
  virtual void    SetLimit( double u1, double v1, double u2, double v2 );
  virtual void    IncludePoint ( double u, double v ); // \ru Включить точку в область определения. \en Include point into domain. 
   
  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       Offset( double d, bool same ) const;  // \ru Построить смещенную поверхность. \en Create a shifted surface. 

  virtual bool    IsLineU    () const; // \ru Если true все производные по U выше первой равны нулю. \en If true, then all the derivatives by U higher the first one are equal to zero. 
  virtual bool    IsLineV    () const; // \ru Если true все производные по V выше первой равны нулю. \en If true, then all the derivatives by V higher the first one are equal to zero. 

  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & pnt, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const; 

  /** \brief \ru Проверить параметры. Аналог глобальной функции _CheckParams, оптимизированный под использование кэшей.
             \en Check parameters. Analogue of the global function _CheckParams, optimized for caches usage.  \~
    \details \ru Проверить параметры и загнать в область определения, если параметр вышел за полюс.
             \en Check parameters and move them inside domain if parameter is out of pole. \~
    \param[in] surface - \ru Поверхность.
                         \en Surface. \~
  \param[in] u -       \ru Первый параметр.
  \en First parameter. \~
  \param[in] v -       \ru Второй параметр.
  \en Second parameter. \~
  */
  virtual void CheckSurfParams( double & u, double & v ) const;

  /** \} */
  /** \ru \name Функции эквидистантной поверхности
      \en \name Functions of the offset surface
      \{ */ 

          // \ru Тип смещения точек. \en The type of points offset.
          MbeOffsetType GetOffsetType() const { return type; }
          // \ru Постоянное ли смещение точек? \en Is const the offset type?
          bool    IsConstOffset() const { return ( (type == off_Empty) || (type == off_Const) ); }
          // \ru Величина смещения. \en The offset distance. 
          double  GetDistance( size_t i = 0 ) const { 
            if ( i == 1 ) return offsetUmaxVmin;
            else
            if ( i == 2 ) return offsetUminVmax;
            else
            if ( i == 3 ) return offsetUmaxVmax;
            return offsetUminVmin;
          }
          
          /** \brief \ru Установить величины смещения.
                     \en Set offset distances. \~  
            \param[in] d - \ru Новая величина смещения
                           \en New offset distance \~
          */
          void    SetDistance( double d, size_t i = 0 );
                    
          /** \brief \ru Проверить корректность точки поверхности.
                     \en Check the correctness of the point of a surface. \~  
            \details \ru Проверить корректность точки поверхности по кривизне подложки.\n  
              Точка считается некорректной, если в ней поверхность самопересекается или имеет излом.
                     \en Check the correctness of the point of a surface by curvature of substrate.\n  
              Point is considered incorrect if a surface is self-intersected or has a break in it. \~
            \param[in] uv - \ru Точка для проверки
                            \en Point to check \~
            \return \ru true, если точка корректная
                    \en True if point is correct \~
          */         
          bool    IsCurvatureValid( const MbCartPoint & uv ) const;
  /** \} */
private:
          void    CheckParam   ( double & u, double & v ) const;  // \ru Проверка параметров (попадание в пределы). \en Check parameters (being in limits). 
          void    CheckExtParam( double & u, double & v, MbOffsetSurfaceAuxiliaryData * ucache ) const;  // \ru Проверка параметров (на наличие полюсов). \en Check parameters (for presence of poles). 
          void    CheckPoles   ( MbOffsetSurfaceAuxiliaryData * ) const; // \ru Проверить наличие полюсов на краях поверхности \en Check presence of poles on surface boundaries 
          void    CheckPole    ( double param, bool isU, MbeSurfacePoleType & poleType, CommonMutex* lock, MbOffsetSurfaceAuxiliaryData * ) const;

          // \ru Вычисление эквидистанты и её производных. \en The offset calculation and it derivatives calculation.
          double  Offset0  ( double u, double v ) const;
          double  OffsetU  ( double u, double v ) const;
          double  OffsetV  ( double u, double v ) const;
          double  OffsetUU ( double u, double v ) const;
          double  OffsetUV ( double u, double v ) const;
          double  OffsetVV ( double u, double v ) const;
          double  OffsetUUU( double u, double v ) const;
          double  OffsetUUV( double u, double v ) const;
          double  OffsetUVV( double u, double v ) const;
          double  OffsetVVV( double u, double v ) const;

          // \ru Точка на расширенной поверхности. \en The point on the extended surface. 
          void   _PointOn( double u, double v, MbCartPoint3D &, MbOffsetSurfaceAuxiliaryData * ) const;

          // \ru Частные случаи поверхностей. \en Special cases of surfaces. 
          MbSplineSurface * CasePlane     ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseCylinder  ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseCone      ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseSphere    ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseTorus     ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseFillets   ( double, double, double, double, bool ) const;          
          MbSplineSurface * CaseLine      ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseRevolution( double, double, double, double, bool ) const;
          MbSplineSurface * CaseExtrusion ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseSwept     ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseLofted    ( double, double, double, double, bool ) const;
          MbSplineSurface * CaseArbitrary ( double, double, double, double, bool ) const;

          void    operator = ( const MbOffsetSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbOffsetSurface )
};

IMPL_PERSISTENT_OPS( MbOffsetSurface )


#endif // __SURF_OFFSET_SURFACE_H
