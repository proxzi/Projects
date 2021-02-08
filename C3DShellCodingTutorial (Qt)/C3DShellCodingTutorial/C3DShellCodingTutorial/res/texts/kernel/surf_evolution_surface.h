////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Поверхность заметания.
         \en The swept surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_EVOLUTION_SURFACE_H
#define __SURF_EVOLUTION_SURFACE_H


#include <surf_swept_surface.h>
#include <surf_spine.h>
#include <tool_multithreading.h>
#include <templ_dptr.h>


class MbSurfaceWorkingData;


//------------------------------------------------------------------------------
/** \brief \ru Поверхность заметания.
           \en The swept surface. \~
  \details \ru Кинематическая поверхность образуется путем движения образующей кривой curve по направляющей кривой spine->curve.
    В процессе движения вдоль направляющей кривой образующая кривая сохраняет своё положение в движущейся локальной системе координат,
    начало которой совпадает с текущей точкой базовой кривой.
    Одна из осей движущейся локальной системы координат всегда совпадает с касательной направляющей кривой, 
    а две другие оси ортогональны ей.
    Первый параметр поверхности совпадает с параметром образующей кривой. 
    Второй параметр поверхности совпадает с параметром направляющей кривой.
           \en Sweep with guide curve surface is formed by moving the 'curve' generating curve along spine->curve guide curve.
    While moving along a guide curve the generating curve keeps its position in the moving local coordinate system,
    which origin coincides with the current point of the base curve.
    One of the axes of the moving local coordinate system is always coincident to the tangent of the guide curve, 
    and the other two axes are orthogonal to it.
    First parameter of surface coincides with parameter of generating curve. 
    Second parameter of surface coincides with parameter of guide curve. \~ 
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbEvolutionSurface : public MbSweptSurface {
protected:
  MbSpine *     spine;  ///< \ru Направляющая кривая. \en Spine (guide) curve. 
  MbCartPoint3D origin; ///< \ru Начало направляющей кривой. \en Begining of generating curve. 

  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbEvolutionSurfaceAuxiliaryData : public AuxiliaryData {
  public:
    DPtr<MbSurfaceWorkingData> wData; ///< \ru Рабочие данные для расчета поверхности. \en Working data for the calculation of a surface. 
    MbCartPoint3D              wPnt;  ///< \ru Рабочая точка. \en Working point.
    MbVector3D                 wVect; ///< \ru Рабочий вектор. \en Working vector.
    MbMatrix3D                 wMatr; ///< \ru Рабочая матрица. \en Working matrix.

    MbEvolutionSurfaceAuxiliaryData();
    MbEvolutionSurfaceAuxiliaryData( const MbEvolutionSurfaceAuxiliaryData & );
    virtual ~MbEvolutionSurfaceAuxiliaryData();

    void Init();
    void Init( const MbEvolutionSurfaceAuxiliaryData & );
    void Move( const MbVector3D & );
  };
  
  mutable CacheManager<MbEvolutionSurfaceAuxiliaryData> cache;

public:

  /** \brief \ru Конструктор по образующей и направляющей.
             \en Constructor by generating curve and guide curve. \~
    \details \ru Конструктор по образующей и направляющей.
             \en Constructor by generating curve and guide curve. \~ 
    \param[in] c - \ru Образующая
                   \en Generating curve \~
    \param[in] s - \ru Направляющая
                   \en Guide curve \~
    \param[in] sameCurve - \ru Признак использования оригинала образующей, а не копии
                           \en Attribute of usage of original of generating curve, not a copy \~
    \param[in] sameSpine - \ru Признак использования оригинала направляющей, а не копии
                           \en Attribute of usage of original of guide curve, not a copy \~
  */
  MbEvolutionSurface( const MbCurve3D & c, const MbSpine & s, bool sameCurve, bool sameSpine = false ); 
  
  /** \brief \ru Конструктор по образующей и направляющей.
             \en Constructor by generating curve and guide curve. \~
    \details \ru Конструктор по образующей, направляющей и её кривой векторa ориентации матрицы преобразования.
             \en Constructor by generating curve, guide curve and its curve of transformation matrix orientation vector. \~ 
    \param[in] c - \ru Образующая
                   \en Generating curve \~
    \param[in] s - \ru Направляющая
                   \en Guide curve \~
    \param[in] d - \ru Кривая векторa ориентации матрицы преобразования направляющей
                   \en Curve of orientation vector of transformation matrix of guide curve \~
    \param[in] sameCurve - \ru Признак использования оригинала образующей, а не копии
                           \en Attribute of usage of original of generating curve, not a copy \~
    \param[in] sameSpine - \ru Признак использования оригинала направляющей, а не копии
                           \en Attribute of usage of original of guide curve, not a copy \~
    \param[in] sameD - \ru Признак использования оригинала кривой d, а не копии
                       \en Attribute of usage of original of 'd' curve, not a copy \~
  */
  MbEvolutionSurface( const MbCurve3D & c, const MbCurve3D & s, const MbCurve3D & d, 
                      bool sameCurve, bool sameSpine, bool sameD );
  
  /** \brief \ru Конструктор по радиусу, направляющей и её кривой векторa ориентации матрицы преобразования.
             \en Constructor by radius, guide curve and its curve of transformation matrix orientation vector. \~
    \details \ru Конструктор кинематической поверхности с образующей кривой - дугой окружности.
      Используется только в конвертерах.
             \en Constructor of evolution surface with circular arc as generating curve.
      Used only in converters. \~
    \param[in] r - \ru Радиус образующей
                   \en Radius of generating curve \~
    \param[in] s - \ru Направляющая
                   \en Guide curve \~
    \param[in] d - \ru Кривая векторa ориентации матрицы преобразования направляющей
                   \en Curve of orientation vector of transformation matrix of guide curve \~
    \param[in] pURgn - \ru Область параметра U
                       \en Region of U parameter \~
    \param[in] pVRgn - \ru Область параметра V
                       \en Region of V parameter \~
  */       
  MbEvolutionSurface( double r, const MbCurve3D & s, const MbCurve3D & d, MbRect1D * pURgn, MbRect1D * pVRgn, VERSION version = Math::DefaultMathVersion() );

protected:
  MbEvolutionSurface( const MbEvolutionSurface &, MbRegDuplicate * );
private:
  MbEvolutionSurface( const MbEvolutionSurface & ); // \ru Не реализовано. \en Not implemented. 
public:
  virtual ~MbEvolutionSurface();

public:
  VISITING_CLASS( MbEvolutionSurface );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & );       // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar  ( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );          // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );          // \ru Сдвиг. \en Move. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  
  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems  ( RPArray <MbSpaceItem> & ); // \ru Дать базовые объекты. \en Get the base objects. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /** \} */
  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.\n  
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... of surfaces correct parameters
            when they are out of bounds of rectangular domain of parameters.\n
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en The point on the surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en The first derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en The first derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u. \en The second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v. \en The second derivative with respect to v. 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv. \en The second derivative with respect to uv. 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const;
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const;
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
  virtual double  MetricStepU   ( double u, double v, double length ) const; // \ru Вычисление шага по u по заданной длине. \en Calculation of the parameter step in u direction by the given length. 
  virtual double  MetricStepV   ( double u, double v, double length ) const; // \ru Вычисление шага по v по заданной длине. \en Calculation of the parameter step in v direction by the given length. 
  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  /** \} */
  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual double  CurvatureU    ( double u, double v ) const; // \ru Kривизна линии по u. \en Curvature of line by u. 
  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской. \en Whether the surface is planar. 
    
  virtual void    ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя. \en Changing of carrier. 

  virtual void    CalculateGabarit( MbCube & ) const; // \ru Выдать габарит. \en Get the bounding box. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  virtual MbSplineSurface * NurbsSurface( double, double, double, double, bool bmatch = false ) const; // \ru NURBS копия поверхности. \en NURBS copy of a surface. 
  virtual MbSurface *       Offset( double d, bool same ) const; // \ru Создание эквидистантной поверхности. \en Create an offset surface. 

  // \ru Подобные ли поверхности для объединения (слива) \en Whether the surfaces to union (joining) are similar 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const; // \ru Специальный случай \en Special case 

  virtual MbCurve3D * CurveU( double v, MbRect1D *pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en Spatial copy of 'v = const'-line. 
  virtual MbCurve3D * CurveV( double u, MbRect1D *pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en Spatial copy of 'u = const'-line. 

  // \ru Построить касательные и нормальные плейсменты конструктивных плоскостей. \en Construct tangent and normal placements of constructive planes. 
  virtual bool    CreateNormalPlacements ( const MbVector3D & axisZ, double angle, SArray<MbPlacement3D> & places ) const;
  virtual bool    CreateTangentPlacements( const MbVector3D & axisZ, SArray<MbPlacement3D> & places ) const;
  // \ru Подобные ли поверхности для объединения (слива). \en Whether the surfaces to union (joining) are similar. 
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional transformation matrix from own parametric region to parametric region of 'surf'. 
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const;
  virtual bool    GetCenterLines( std::vector<MbCurve3D *> & clCurves ) const; // \ru Дать осевые (центральные) линии для поверхности. \en Get center lines of a surface.
  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine splitting of parametric region of surface by vertical and horizontal lines. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;
  virtual bool    IsSpinePeriodic() const; // \ru Периодичность направляющей. \en Periodicity of a guide curve. 

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the count of polygons by u. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the count of polygons by v. 

  // \ru Включить точку в область определения. \en Include a point into domain. 
  virtual void    IncludePoint( double u, double v );
  /** \} */
  /** \ru \name Функции кинематической поверхности
      \en \name Functions of the evolution surface
      \{ */

          /** \brief \ru Определение матрицы переноса для образующей.
                     \en Determination of translation matrix for generating curve. \~
            \details \ru Определение матрицы переноса для образующей по параметру направляющей.
                     \en Determination of translation matrix for generating curve by parameter of guide curve. \~
            \param[in] v - \ru Параметр на направляющей
                           \en Parameter on the guide curve \~
            \param[in] matr - \ru Матрица-результат
                              \en Matrix-result \~
          */
          void    TransformMatrix( double v, MbMatrix3D & matr ) const; 

    /// \ru Направляющая. \en Guide curve. 
    const MbSpine       & GetSpine() const { return *spine; } 

    /// \ru Направляющая кривая. \en The spine (guide) curve. 
    const MbCurve3D     & GetSpineCurve() const { return spine->GetCurve(); } 
    /// \ru Центр тяжести образующей. \en Center of gravity of generating curve. 
    const MbCartPoint3D & GetOrigin() const { return origin; } 

          /// \ru Дать направляющую кривую для изменения. \en Get guide curve for editing. 
          MbCurve3D     & SetSpineCurve()   { return spine->SetCurve(); } 
          /// \ru Задать центр тяжести образующей. \en Set center of gravity of generating curve. 
          void            SetOrigin( const MbCartPoint3D & p ) { origin = p; SetDirtyGabarit(); } 
  /** \} */

protected :
          void    Init();
private:
          void    operator = ( const MbEvolutionSurface & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbEvolutionSurface )
};

IMPL_PERSISTENT_OPS( MbEvolutionSurface )

//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~
  \details \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~ 
  \param[in] curve - \ru Образующая кривая
                     \en Generating curve \~
  \param[in] spine - \ru Направляющая кривая
                     \en Guide curve \~
  \param[in] samec - \ru Признак использования оригинала образующей кривой, а не копии.
                     \en Attribute of usage of original of generating curve, not a copy. \~
  \param[in] sames - \ru Признак использования оригинала направляющей кривой spine, а не копии.
                     \en Attribute of usage of original of guide curve (spine), not a copy. \~
  \return \ru Возвращает созданную поверхность.
          \en Return the created surface. \~ 
  \ingroup Surface_Modeling
*/
// ---
MATH_FUNC (MbSurface &) CreateEvolutionSurface( const MbCurve3D & curve, const MbSpine & spine, bool samec, bool sames = false );


//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~
  \details \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~ 
  \param[in] curve - \ru Образующая кривая
                     \en Generating curve \~
  \param[in] spine - \ru Направляющая кривая
                     \en Guide curve \~
  \param[in] samec - \ru Признак использования оригинала образующей кривой, а не копии
                     \en Attribute of usage of original of generating curve, not a copy \~
  \param[in] sames - \ru Признак использования оригинала направляющей кривой, а не копии
                     \en Attribute of usage of original of guide curve, not a copy \~
  \return \ru Возвращает созданную поверхность.
          \en Return the created surface. \~ 
  \ingroup Surface_Modeling
*/
// ---
MATH_FUNC (MbSurface &) CreateEvolutionSurface( const MbCurve3D & curve, const MbCurve3D & spine,
                                                bool samec, bool sames );


//------------------------------------------------------------------------------
/** \brief \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~
  \details \ru Создать кинематическую поверхность.
           \en Create an evolution surface. \~ 
  \param[in] curve - \ru Образующая кривая
                     \en Generating curve \~
  \param[in] spine - \ru Направляющая кривая
                     \en Guide curve \~
  \param[in] spineDirection - \ru Направляющая кривая для направляющей кривой
                              \en Guide curve for guide curve \~
  \param[in] samec - \ru Признак использования оригинала образующей кривой, а не копии
                     \en Attribute of usage of original of generating curve, not a copy \~
  \param[in] sames - \ru Признак использования оригинала направляющей кривой, а не копии
                     \en Attribute of usage of original of guide curve, not a copy \~
  \param[in] samed - \ru Признак использования оригинала кривой spineDirection, а не копии
                     \en Attribute of usage of original of spineDirection curve, not a copy \~
  \return \ru Возвращает созданную поверхность.
          \en Return the created surface. \~ 
  \ingroup Surface_Modeling
*/
// ---
MATH_FUNC (MbSurface &) CreatePipeSurface( const MbCurve3D & curve, const MbCurve3D & spine, 
                                           const MbCurve3D & spineDirection, 
                                           bool samec, bool sames, bool samed );


#endif // __SURF_EVOLUTION_SURFACE_H
