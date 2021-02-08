////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Бикубическая поверхность Кунса на четырех кривых и их поперечных производных.
         \en Bicubic Coons surface on four curves and its transverse derivatives. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_COONS_SURFACE_H
#define __SURF_COONS_SURFACE_H


#include <surface.h>
#include <cur_surface_curve.h>
#include <mb_operation_result.h>


class MATH_CLASS MbCurve;


#define COONS_COUNT 4 ///< \ru Число кривых, используемых для построения поверхности Кунса \en Count of curves used to construct Coons surface. 


//------------------------------------------------------------------------------
/** \brief \ru Способ расчёта поверхности Кунса.
\en Type of calculation of Coons surface. \~
\details \ru Способ расчёта поверхности Кунса. \n
\en Type of calculation of Coons surface. \n \~
\ingroup Surfaces
*/ 
// ---
enum MbeCoonsSurfaceCalcType {
  cst_DefaultType = 0, ///< \ru Способ по умолчанию. \en Default type.
  cst_SurfaceType, ///< \ru Точный способ по кривым на поверхностях. \en Exact type by Curves on surfaces.
};


//------------------------------------------------------------------------------
/** \brief \ru Поверхность Кунса на четырех кривых.
           \en Coons surface on four curves. \~
  \details \ru Бикубическая поверхность Кунса определяется четырьмя кривыми и 
    производными поверхности на этих кривых в поперечном к кривым направлениях. 
    Поверхность проходит через определяющие её кривые и 
    имеет заданные производные на этих кривых в поперечном к кривым направлениях. \n
           \en Bicubic Coons surface is determined by four curves and 
    surface derivatives on these curves in transverse directions to curves. 
    Surface passes through its determining curves and 
    has specified derivatives on this curves in transverse directions to curves. \n \~
  \ingroup Surfaces
*/
// ---
class MATH_CLASS MbCoonsPatchSurface : public MbSurface {

//                                                      curve2V
//                                             t2min    curve2    t2max
//                                           P3 ______________________ P2
//                                       t3max |                      | t1max
//                                             |                      |
//                                             |                      |
//                                     curve3  |                      | curve1
//                                     curve3U |                      | curve1U
//     t0=t0min*(1-u)+t0max*u                  |                      |
//     t1=t1min*(1-v)+t1max*v                  |                      |
//     t2=t2min*(1-u)+t2max*u            t3min |______________________| t1min
//     t3=t3min*(1-v)+t3max*v                P0                        P1
//                                             t0min    curve0    t0max
//                                                      curve0V
// \ru Не переименовывать в MbCoonsSurface - хэш совпал с существующим объектом (BUG_60351). \en No renaming to MbCoonsSurface - hash was coincided with existing object (BUG_60351). 

private:
  MbCurve3D *   curve0;  ///< \ru Кривая  0. \en Curve 0. 
  MbCurve3D *   curve1;  ///< \ru Кривая  1. \en Curve 1. 
  MbCurve3D *   curve2;  ///< \ru Кривая  2. \en Curve 2. 
  MbCurve3D *   curve3;  ///< \ru Кривая  3. \en Curve 3. 
  MbCurve3D *   curve0V; ///< \ru Производная по v вдоль кривой  0. \en Derivative by v along curve 0. 
  MbCurve3D *   curve1U; ///< \ru Производная по u вдоль кривой  1. \en Derivative by u along curve 1. 
  MbCurve3D *   curve2V; ///< \ru Производная по v вдоль кривой  2. \en Derivative by v along curve 2. 
  MbCurve3D *   curve3U; ///< \ru Производная по u вдоль кривой  3. \en Derivative by u along curve 3. 
  MbCartPoint3D vertex[COONS_COUNT];   ///< \ru Вершины. \en Vertices. 
  MbCartPoint3D vertexU[COONS_COUNT];  ///< \ru Производная по u в вершинах. \en Derivative by u at vertices. 
  MbCartPoint3D vertexV[COONS_COUNT];  ///< \ru Производная по v в вершинах. \en Derivative by v at vertices. 
  MbCartPoint3D vertexUV[COONS_COUNT]; ///< \ru Производная по uv в вершинах. \en Derivative by uv at vertices. 
  double        t0min;   ///< \ru Минимальное значение параметра на кривой  0. \en Minimal value of parameter on curve 0. 
  double        t0max;   ///< \ru Максимальное значение параметра на кривой 0. \en Maximal value of parameter on curve 0. 
  double        t1min;   ///< \ru Минимальное значение параметра на кривой  1. \en Minimal value of parameter on curve 1. 
  double        t1max;   ///< \ru Максимальное значение параметра на кривой 1. \en Maximal value of parameter on curve 1. 
  double        t2min;   ///< \ru Минимальное значение параметра на кривой  2. \en Minimal value of parameter on curve 2. 
  double        t2max;   ///< \ru Максимальное значение параметра на кривой 2. \en Maximal value of parameter on curve 2. 
  double        t3min;   ///< \ru Минимальное значение параметра на кривой  3. \en Minimal value of parameter on curve 3. 
  double        t3max;   ///< \ru Максимальное значение параметра на кривой 3. \en Maximal value of parameter on curve 3. 
  bool          uclosed; ///< \ru Замкнутость по u. \en Closeness by u. 
  bool          vclosed; ///< \ru Замкнутость по v. \en Closeness by v. 
  bool          poleUMin;   ///< \ru Полюс в начале. \en Pole at the beginning. 
  bool          poleUMax;   ///< \ru Полюс в конце. \en Pole at the end. 
  bool          poleVMin;   ///< \ru Полюс в начале. \en Pole at the beginning. 
  bool          poleVMax;   ///< \ru Полюс в конце. \en Pole at the end. 
  MbeCoonsSurfaceCalcType calcType;  ///< \ru Версия реализации определяет способ расчёта поверхности. \en Version of implementation determines a type of calculation of surface.

protected:
  /** \brief \ru Конструктор поверхности Кунса.
             \en Constructor of Coons surface. \~
      \details \ru Конструктор поверхности Кунса по набору кривых и производных вдоль кривых.
               \en Constructor of Coons surface by set of curves and derivatives along curves. \~
      \param[in] initCurve0 - \ru Кривая 0.
                              \en Curve 0. \~
      \param[in] initCurve1 - \ru Кривая 1.
                              \en Curve 1. \~
      \param[in] initCurve2 - \ru Кривая 2.
                              \en Curve 2. \~
      \param[in] initCurve3 - \ru Кривая 3.
                              \en Curve 3. \~
      \param[in] derVCurve0 - \ru Производная по v вдоль кривой  0.
                              \en Derivative by v along curve 0. \~
      \param[in] derUCurve1 - \ru Производная по u вдоль кривой  1.
                              \en Derivative by u along curve 1. \~
      \param[in] derVCurve2 - \ru Производная по v вдоль кривой  2.
                              \en Derivative by v along curve 2. \~
      \param[in] derUCurve3 - \ru Производная по u вдоль кривой  3.
                              \en Derivative by u along curve 3. \~
  */
  MbCoonsPatchSurface ( MbCurve3D & initCurve0, MbCurve3D & initCurve1, MbCurve3D & initCurve2, MbCurve3D & initCurve3,
                        MbCurve3D & derVCurve0, MbCurve3D & derUCurve1, MbCurve3D & derVCurve2, MbCurve3D & derUCurve3,
                        double w0min, double w0max, double w1min, double w1max, double w2min, double w2max, double w3min, double w3max, 
                        MbeCoonsSurfaceCalcType calcType = cst_DefaultType );
private:
  MbCoonsPatchSurface( const MbCoonsPatchSurface & ); // \ru Не реализовано. \en Not implemented. 
  MbCoonsPatchSurface( const MbCoonsPatchSurface &, MbRegDuplicate * ); ///< \ru Конструктор копирования. \en Copy-constructor. 
public:
  virtual ~MbCoonsPatchSurface( void );

public:
  VISITING_CLASS( MbCoonsPatchSurface );

  /// \ru Создание поверхности Кунса заданным кривым на поверхностях. \en Creation of Coons surface by curves on surfaces. 
  static  MbCoonsPatchSurface * Create( const MbCurve3D & curve0, 
                                        const MbCurve3D & curve1, 
                                        const MbCurve3D & curve2, 
                                        const MbCurve3D & curve3, 
                                              MbResultType & resType );

  /// \ru Инициализация поверхности Кунса заданной поверхностью Кунса. \en Initialization of Coons surface by specified Coons surface. 
          void    Init( const MbCoonsPatchSurface & );

  /** \ru \name Общие функции геометрического объекта
      \en \name Common functions of a geometric object
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL )  const; // \ru Cделать копию элемента \en Make a copy of element 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;   // \ru Является ли объект копией. \en Whether the object is a copy. 
  virtual bool    SetEqual( const MbSpaceItem & init );        // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move( const MbVector3D & to, MbRegTransform * = NULL );                 // \ru Сдвиг \en Translation 
  virtual void    Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisItems ( RPArray <MbSpaceItem> &s ); // \ru Дать базовые объекты \en Get the base objects 
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
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности \en Point on the surface 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void    Normal   ( double & u, double & v, MbVector3D & ) const; // \ru Нормаль \en Normal 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
      \en \name Functions for working inside and outside the surface's domain
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when they are out of bounds of rectangular domain of parameters.
      \{ */
  virtual void   _PointOn  ( double  u, double  v, MbCartPoint3D & ) const; // \ru Точка на расширенной поверхности \en Point on the extended surface 
  virtual void   _DeriveU  ( double  u, double  v, MbVector3D & ) const; // \ru Первая производная по u \en First derivative with respect to u 
  virtual void   _DeriveV  ( double  u, double  v, MbVector3D & ) const; // \ru Первая производная по v \en First derivative with respect to v 
  virtual void   _DeriveUU ( double  u, double  v, MbVector3D & ) const; // \ru Вторая производная по u \en Second derivative with respect to u 
  virtual void   _DeriveVV ( double  u, double  v, MbVector3D & ) const; // \ru Вторая производная по v \en Second derivative with respect to v 
  virtual void   _DeriveUV ( double  u, double  v, MbVector3D & ) const; // \ru Вторая производная по uv \en Second derivative with respect to uv 
  virtual void   _DeriveUUU( double  u, double  v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUUV( double  u, double  v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveUVV( double  u, double  v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void   _DeriveVVV( double  u, double  v, MbVector3D & ) const; // \ru Третья производная \en Third derivative 
  virtual void   _Normal   ( double  u, double  v, MbVector3D & ) const; // \ru Нормаль \en Normal 
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
  virtual double  StepU( double u, double v, double sag ) const; // \ru Вычисление шага параметра u по по величине прогиба \en Calculation of parameter u step by the value of sag  
  virtual double  StepV( double u, double v, double sag ) const; // \ru Вычисление шага параметра v по по величине прогиба \en Calculation of parameter v step by the value of sag 
  virtual double  DeviationStepU( double u, double v, double ang ) const; // \ru Вычисление шага параметра u по углу отклонения нормали \en Calculation of parameter u step by the angle of deviation of normal 
  virtual double  DeviationStepV( double u, double v, double ang ) const; // \ru Вычисление шага параметра v по углу отклонения нормали \en Calculation of parameter v step by the angle of deviation of normal 
  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  /** \} */

  /** \ru \name Общие функции поверхности
      \en \name Common functions of surface
      \{ */
  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const \en Spatial copy of 'v = const'-line 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const \en Spatial copy of 'u = const'-line 

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
  /// \ru Получить кривую 3. \en Get curve 3. 
  const   MbCurve3D & GetCurve3() const { return *curve3; } 
  /// \ru Получить кривую производной в трансверсальном направлении к кривой 0. \en Get derivative curve transversal to curve 0.
  const   MbCurve3D & GetDerCurve0() const { return *curve0V; } 
  /// \ru Получить кривую производной в трансверсальном направлении к кривой 1. \en Get derivative curve transversal to curve 1.
  const   MbCurve3D & GetDerCurve1() const { return *curve1U; } 
  /// \ru Получить кривую производной в трансверсальном направлении к кривой 2. \en Get derivative curve transversal to curve 2.
  const   MbCurve3D & GetDerCurve2() const { return *curve2V; } 
  /// \ru Получить кривую производной в трансверсальном направлении к кривой 3. \en Get derivative curve transversal to curve 3.
  const   MbCurve3D & GetDerCurve3() const { return *curve3U; } 
  /// \ru Получить кривую по индексу. \en Get curve by an index. 
  const   MbCurve3D * GetCurve( size_t ind ) const; 
          /// \ru Получить количество кривых. \en Get count of curves. 
          size_t  GetCurvesCount() const { return COONS_COUNT; } //-V112
  const   MbCartPoint3D * GetVertex() const { return vertex; } ///< \ru Выдать вершины P0, P1, P2. \en Get vertices P0, P1, P2. 
  /** \} */
          double  GetT0Min() const { return t0min; } ///< \ru Минимальное значение параметра на кривой  0. \en Minimal value of parameter on curve 0. 
          double  GetT0Max() const { return t0max; } ///< \ru Максимальное значение параметра на кривой 0. \en Maximal value of parameter on curve 0. 
          double  GetT1Min() const { return t1min; } ///< \ru Минимальное значение параметра на кривой  1. \en Minimal value of parameter on curve 1. 
          double  GetT1Max() const { return t1max; } ///< \ru Максимальное значение параметра на кривой 1. \en Maximal value of parameter on curve 1. 
          double  GetT2Min() const { return t2min; } ///< \ru Минимальное значение параметра на кривой  2. \en Minimal value of parameter on curve 2. 
          double  GetT2Max() const { return t2max; } ///< \ru Максимальное значение параметра на кривой 2. \en Maximal value of parameter on curve 2. 
          double  GetT3Min() const { return t3min; } ///< \ru Минимальное значение параметра на кривой  3. \en Minimal value of parameter on curve 3. 
          double  GetT3Max() const { return t3max; } ///< \ru Максимальное значение параметра на кривой 3. \en Maximal value of parameter on curve 3. 

 /** \brief \ru Получить образующую кривую по индексу, если она точно совпадает с соответствующим краем поверхности.
            \en Get exact curve by index, if it coincides with the corresponding border of the surface. \~
   \details \ru Совпадение кривой с краем поверхности определяется по крайним точкам кривой.
            \en Coincidence of the curve with the border of the surface is determined by the end points of the curve. \~
   \param[in] k - \ru Индекс кривой.
                  \en Index of the curve. \~
   \param[out] sense - \ru Флаг совпадения направленности кривой с рисунком, приведенным выше.
                       \en Flag that indicates the coincidence of the curve with the picture shown above.\~
   \return - \ru Указатель на кривую или NULL.
             \en Pointer to the curve or NULL. \~
 */
  const   MbCurve3D * GetExactCurve( size_t k, bool & sense ) const;

  /** \brief \ru Проверка полюсов на кривых.
             \en Check poles on curves. \~
      \details \ru Определяет, есть ли полюс на границе области определения по длине кривой, определяющей границу.\n
      Результат вычислений можно получить с помощью функций GetPoleUMin, GetPoleUMax, GetPoleVMin, GetPoleVMax.
               \en Determines whether the pole at domain boundary by curve length determining boundary.\n
      Result of calculations can be obtained with help of GetPoleUMin, GetPoleUMax, GetPoleVMin, GetPoleVMax functions. \~ 
  */
          void    CheckPole(); 

private:
          void    operator = ( const MbCoonsPatchSurface & ); // \ru Не реализовано. \en Not implemented. 
          void    Setup();
          void    CheckParams( double & u, double & v ) const; // \ru Проверить и изменить при необходимости параметры. \en Check and correct parameters. 
          // \ru Определение местных координат. \en Determination of local coordinates. 
          void    CalculateCoordinate( double & u, double & v,
                                       double & t0, double & t1, double & t2, double & t3 ) const;
          void    CalculatePoint ( double & u, double & v,
                                   MbCartPoint3D * point, MbCartPoint3D * pointUV ) const;
          void    CalculateFirst ( double & u, double & v,
                                   MbCartPoint3D * point, MbVector3D * first, 
                                   MbCartPoint3D * pointUV, MbVector3D * firstUV ) const;
          void    CalculateThird ( double & u, double & v,
                                   MbCartPoint3D * point, MbVector3D * third,
                                   MbCartPoint3D * pointUV, MbVector3D * thirdUV ) const;
          void    CalculateExplore( double & u, double & v,
                                    MbCartPoint3D * point, MbVector3D * first, MbVector3D * second, 
                                    MbCartPoint3D * pointUV, MbVector3D * firstUV, MbVector3D * secondUV ) const;
          // \ru Производные. \en Derivatives with respect to u and to v.
          void    Derivatives( double & u, double & v, MbVector3D & uDer, MbVector3D & vDer ) const; 
          // \ru Нормаль. \en Calculate surface normal with refinement on borders. 
          void    Normal( double u, double v, MbVector3D & derU, MbVector3D & derV, MbVector3D & norm ) const;
  inline  void    ParamPoint ( double w, double * t ) const;
  inline  void    ParamFirst ( double w, double * t ) const;
  inline  void    ParamSecond( double w, double * t ) const;
  inline  void    ParamThird ( double w, double * t ) const;
          // \ru Добавить матрицу поверхности. \en Add the matrix of the surface.
  inline  void    AddMatrix  ( double * uu, double * vv, MbVector3D & p ) const; 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCoonsPatchSurface )
}; // MbCoonsSurface


IMPL_PERSISTENT_OPS( MbCoonsPatchSurface )


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметра точки \en Determination of array of degrees of point parameter 
// ---
inline void MbCoonsPatchSurface::ParamPoint ( double w, double * t ) const {
  t[0] = 1.0 - 3.0 * w * w + 2.0 * w * w * w; //*/ 1.0 - 10.0 * w * w * w + 15.0 * w * w * w * w - 6.0 * w * w * w * w * w;
  t[1] =       3.0 * w * w - 2.0 * w * w * w; //*/       10.0 * w * w * w - 15.0 * w * w * w * w + 6.0 * w * w * w * w * w;
  t[2] = w   - 2.0 * w * w +       w * w * w; //*/ 0.0;
  t[3] =     -       w * w +       w * w * w; //*/ 0.0;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметра производной \en Determination of array of degrees of derivative parameter 
// ---
inline void MbCoonsPatchSurface::ParamFirst ( double w, double * t ) const {
  t[0] =     - 6.0 * w + 6.0 * w * w; //*/ -30.0 * w * w + 60.0 * w * w * w - 30.0 * w * w * w * w;
  t[1] =       6.0 * w - 6.0 * w * w; //*/  30.0 * w * w - 60.0 * w * w * w + 30.0 * w * w * w * w;
  t[2] = 1.0 - 4.0 * w + 3.0 * w * w; //*/ 0.0;
  t[3] =     - 2.0 * w + 3.0 * w * w; //*/ 0.0;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметра второй производной \en Determination of array of degrees of second derivative parameter 
// ---
inline void MbCoonsPatchSurface::ParamSecond( double w, double * t ) const {
  t[0] = - 6.0 + 12.0 * w; //*/ -60.0 * w + 180.0 * w * w - 120.0 * w * w * w;
  t[1] =   6.0 - 12.0 * w; //*/  60.0 * w - 180.0 * w * w + 120.0 * w * w * w;
  t[2] = - 4.0 + 6.0  * w; //*/  0.0;
  t[3] = - 2.0 + 6.0  * w; //*/  0.0;
}


//------------------------------------------------------------------------------
// \ru Определение массива степеней параметра третьей производной \en Determination of array of degrees of third derivative parameter 
// ---
inline void MbCoonsPatchSurface::ParamThird ( double /*w*/, double * t ) const {
  t[0] =  12.0; //*/ -60.0 + 360.0 * w - 360.0 * w * w;
  t[1] = -12.0; //*/  60.0 - 360.0 * w + 360.0 * w * w;
  t[2] =   6.0; //*/   0.0;
  t[3] =   6.0; //*/   0.0;
}


//------------------------------------------------------------------------------
// \ru Добавить матрицу поверхности. \en Add the matrix of the surface.
// ---
inline void MbCoonsPatchSurface::AddMatrix( double * uu, double * vv, MbVector3D & p ) const {
  p.Add( vertex[0],   -uu[0]*vv[0], vertex[1],   -uu[1]*vv[0], vertex[2],   -uu[1]*vv[1], vertex[3],   -uu[0]*vv[1] );
  p.Add( vertexU[0],  -uu[2]*vv[0], vertexU[1],  -uu[3]*vv[0], vertexU[2],  -uu[3]*vv[1], vertexU[3],  -uu[2]*vv[1] );
  p.Add( vertexV[0],  -uu[0]*vv[2], vertexV[1],  -uu[1]*vv[2], vertexV[2],  -uu[1]*vv[3], vertexV[3],  -uu[0]*vv[3] );
  p.Add( vertexUV[0], -uu[2]*vv[2], vertexUV[1], -uu[3]*vv[2], vertexUV[2], -uu[3]*vv[3], vertexUV[3], -uu[2]*vv[3] );
}


//------------------------------------------------------------------------------
// \ru Получить кривую по индексу \en Get curve by an index 
// ---
inline const MbCurve3D * MbCoonsPatchSurface::GetCurve( size_t ind ) const
{
  if ( ind >= COONS_COUNT )
    ind = ind % COONS_COUNT;
  switch ( ind ) {
    case 0 : { return curve0; }
    case 1 : { return curve1; }
    case 2 : { return curve2; }
    case 3 : { return curve3; }
  }
  return NULL;
}


////////////////////////////////////////////////////////////////////////////////
//
// Вспомогательные объекты бикубической поверхности Кунса. 
// Auxiliary objects for bicubic Coons surface.
//
////////////////////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------------
// \ru Кривая производных, обслуживающаяя точную бикубическую поверхность Кунса, построенная кривой на поверхности.
// \en The curve of derivetives serving the exact bicubic Coons surface, constructed by a curve on the surface. \~
// ---
class MATH_CLASS MbCoonsDerivative : public MbCurve3D {
protected :
  MbSurfaceCurve * curve;  ///< \ru Кривая на поверхности (всегда не NULL). \en Curve on surface (always not NULL). 
  double           param1; ///< \ru Параметр первой точки кривой. \en The first point parameter of curve. 
  double           param2; ///< \ru Параметр второй точки кривой. \en The second point parameter of curve. 
  MbVector         rail1;  ///< \ru Вектор для вычисления поперечной производной в первой точке кривой. \en The vector for calculatiob of the transverse derivative in first point of curve.
  MbVector         rail2;  ///< \ru Вектор для вычисления поперечной производной во второй точке кривой. \en The vector for calculatiob of the transverse derivative in second point of curve.
  double           turner; ///< \ru Угол поворота векторов на единицу изменения параметра. \en The angle of rotation of vectors per unit of parameter change.

public :
  /// \ru Конструктор кривой на поверхности. \en Constructor of curve on surface. 
  MbCoonsDerivative( MbSurfaceCurve & c, double t1, const MbVector & r1, double t2, const MbVector & r2 ); 
protected:
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbCoonsDerivative( const MbCoonsDerivative &, MbRegDuplicate * );
private:
  MbCoonsDerivative( const MbCoonsDerivative & ); // \ru Не реализовано!!! \en Not implemented!!! 

public :
  virtual ~MbCoonsDerivative();

public:
  /// \ru Реализация функции, инициирующей посещение объекта. \en Implementation of a function initializing a visit of an object. 
  VISITING_CLASS( MbCoonsDerivative );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbeSpaceType     IsA() const;  // \ru Дать тип элемента. \en Get element type. 
  virtual MbSpaceItem &    Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Определить, являются ли объекты одинаковыми. \en Determine whether objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
  virtual bool    IsSimilar( const MbSpaceItem & ) const; // \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate about an axis. 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 

  /** \} */
  /** \ru \name Общие функции кривой.
      \en \name Common functions of curve.
      \{ */

  virtual double  GetTMin() const;   // \ru Вернуть минимальное значение параметра. \en Get the minimum value of parameter. 
  virtual double  GetTMax() const;   // \ru Вернуть максимальное значение параметра. \en Get the maximum value of parameter. 
  virtual bool    IsClosed() const;  // \ru Проверить замкнутость кривой. \en Check for curve closedness. 
  virtual double  GetPeriod() const; // \ru Вернуть период периодической кривой. \en Get period of a periodic curve. 

  // \ru Функции для работы в области определения. \en Functions for working in the definition domain. 
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Вычислить точку на кривой. \en Calculate a point on the curve. 
  virtual void    FirstDer ( double & t, MbVector3D & )    const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void    SecondDer( double & t, MbVector3D & )    const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void    ThirdDer ( double & t, MbVector3D & )    const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Функции для работы вне области определения. \en Functions for working outside of definition domain. 
  virtual void   _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Вычислить точку на расширенной кривой. \en Calculate a point on the extended curve. 
  virtual void   _FirstDer ( double t, MbVector3D & )     const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void   _SecondDer( double t, MbVector3D & )     const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void   _ThirdDer ( double t, MbVector3D & )     const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore  ( double & t, bool ext,
                             MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление. \en Change the direction. 

  virtual double  Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double  DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   

  virtual void    ChangeCarrier     ( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменить носитель. \en Change the carrier. 
  virtual bool    ChangeCarrierBorne( const MbSpaceItem &, MbSpaceItem &, const MbMatrix & matr ); // \ru Изменить носимые элементы. \en Change a carrier elements. 

  /** \} */

  /// \ru Вычислить нормаль к поверхности. \en Calculate surface normal. 
          void    SurfaceNormal( double & t, MbVector3D & n ) const { curve->SurfaceNormal( t, n ); }
  /// \ru Заменить кривую. \en Replace curve. 
          bool    ChangeCurve( MbSurfaceCurve & );
  /// \ru Дать кривую. \en Get curve. 
  const   MbSurfaceCurve * GetSurfaceCurve()   const { return curve; }
  /// \ru Дать кривую. \en Get curve. 
          MbSurfaceCurve * SetSurfaceCurve() { return curve; }

protected:
          void    CheckParam ( double & t ) const; // \ru Проверить и изменить при необходимости параметр. \en Check and correct parameter. 
                    
private:
          // \ru Объявить оператор приравнивания по ссылке. \en Declare operator of assignment by reference.
          void    operator = ( const MbCoonsDerivative & ); // \ru Не реализовано!!! \en Not implemented!!! 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCoonsDerivative )

};

IMPL_PERSISTENT_OPS( MbCoonsDerivative )


#endif // __SURF_COONS_SURFACE_H
