////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NURBS поверхность.
         \en NURBS surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SURF_SPLINE_SURFACE_H
#define __SURF_SPLINE_SURFACE_H


#include <templ_c_array.h>
#include <tool_multithreading.h>
#include <templ_dptr.h>
#include <surf_polysurface.h>
#include <mb_nurbs_function.h>


class  MATH_CLASS  MbSurfaceIntersectionCurve;
class  MATH_CLASS  MbSurfaceCurve;
class              MbSurfaceContiguousData;
class              MbSplineWorkingData;


//------------------------------------------------------------------------------
/** \brief \ru Веса NURBS поверхности.
           \en Weights of a NURBS surface. \~
  \details \ru Веса NURBS поверхности.
           \en Weights of a NURBS surface. \~ 
  \ingroup Data_Structures
*/ // ---
class MbWeightMatrix {
private:
  size_t          linesCnt;     ///< \ru Количество строк матрицы. \en A number of matrix lines. 
  size_t          columnsCnt;   ///< \ru Количество столбцов матрицы. \en A number of matrix columns. 
  double          commonWeight; ///< \ru Общий вес контрольных точек. \en A common weight of control points. 
  Array2<double>  weights;      ///< \ru Матрица весов контрольных точек. \en A matrix of control points weights. 
public:
  /// \ru Пустой конструктор. \en Empty constructor. 
  MbWeightMatrix() : linesCnt( 0 ), columnsCnt( 0 ), commonWeight( UNDEFINED_DBL ), weights() {}
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbWeightMatrix( const MbWeightMatrix & wm );
 ~MbWeightMatrix() {}
public:
  // Количество строк.
  size_t            Lines()   const { return linesCnt;   }
  // Количество столбцов.
  size_t            Columns() const { return columnsCnt; }
  // Общий вес?
  bool              IsCommonWeight() const;
  // Инициализация по общему весу.
  bool              InitWeights( double wt, size_t linesCnt, size_t columnsCnt );
  // Инициализация по матрице весов.
  bool              InitWeights( const Array2<double> & wts );
  // Инициализация по матрице весов.
  void              InitWeights( const MbWeightMatrix & wm );
  // Получить веса.
  void              GetWeights( Array2<double> & wts ) const;
  // Установить веса.
  bool              SetWeights( const Array2<double> & wts ) { return InitWeights( wts ); }
  // Получить вес.
  double            GetWeight( size_t lineIndex, size_t columnIndex ) const;
  // Установить вес.
  bool              SetWeight( size_t lineIndex, size_t columnIndex, double wt );

  // Вставить строку.
  void              InsertLine  ( size_t k, double wt = 1.0 );
  // Вставить столбец.
  void              InsertColumn( size_t k, double wt = 1.0 );
  // Добавить строку.
  void              AddLine( double wt = 1.0 ) { InsertLine( linesCnt, wt ); }
  // Добавить столбец.
  void              AddColumn( double wt = 1.0 ) { InsertColumn( columnsCnt, wt ); };
  // Удалить строку.
  void              RemoveLine( size_t k );
  // Удалить столбец.
  void              RemoveColumn( size_t k );

  // Получить указатель на строку, если не используется общий вес. Иначе возвращает NULL.
  const double *   _GetLine( size_t k ) const;
  // Можно ли оптимизировать расход памяти.
  bool              CanAdjust( const Array2<double> & wts ) const;
  // Оптимизировать расход памяти.
  bool              Adjust();
  // Оператор присваивания.
  MbWeightMatrix &  operator = ( const MbWeightMatrix & wm ) { InitWeights( wm ); return *this; }
  // Оператор присваивания.
  MbWeightMatrix &  operator = ( const Array2<double> & wm ) { InitWeights( wm ); return *this; }
protected:
  // Сформировать полную матрицу весов, если используется общий вес.
  bool              FillArray2();
private:
  MbWeightMatrix( const Array2<double> & ); // не реализовано, запрещено
};


//------------------------------------------------------------------------------
/** \brief \ru NURBS поверхность.
           \en NURBS surface. \~
  \details \ru NURBS поверхность строится по заданной матрице контрольных точек.
    Каждая контрольная точка имеет вес, который задан в матрице весов (по умолчанию все веса равны 1). \n
    Аббревиатура NURBS получена из первых букв словосочетания Non-Uniform Rational B-Spline.
    NURBS поверхность не проходит через свои контрольные точки.
    Расчет поверхности в каждой точке производится на основе двух семейств нормированных неоднородных В-сплайнов. \n
    Каждое семейство В-сплайнов определяется заданной неубывающей последовательностью узловых параметров и заданным порядком B-сплайна. 
    Для не замкнутой по первому параметру поверхности узловой вектор uknots должен содержать количество столбцов матрицы контрольных точек плюс udegree. 
    Для замкнутой по первому параметру поверхности узловой вектор uknots должен содержать количество столбцов матрицы контрольных точек плюс 2*udegree-1. 
    Для не замкнутой по второму параметру поверхности узловой вектор vknots должен содержать количество строк матрицы контрольных точек плюс vdegree. 
    Для замкнутой по второму параметру поверхности узловой вектор vknots должен содержать количество строк матрицы контрольных точек плюс 2*vdegree-1.
           \en NURBS surface is constructed by a given matrix relative to control points.
    Each control point has  a weight which is given in the matrix of weights (by default all weights are equal to 1). \n
    Abbreviation of NURBS is obtained from the first letters of the Non-Uniform Rational B-Spline phrase.
    NURBS surface doesn't pass through its control points.
    Calculation of a surface at each point is performed on the basis of two families of normalized non-uniform B-splines. \n
    Each family of B-splines is defined by the given nondecreasing sequence of knot parameters and the given order of B-spline. 
    For an unclosed by the first parameter surface the knot vector 'uknots' should contain a count of columns of matrix control points plus udegree. 
    For a closed by the first parameter surface the knot vector 'uknots' should contain a count of columns of matrix control points plus 2*udegree-1. 
    For an unclosed by the second parameter surface the knot vector 'vknots' should contain a count of rows of matrix control points plus vdegree. 
    For a closed by the second parameter surface the knot vector 'vknots' should contain a count of rows of matrix control points plus 2*vdegree-1. \~ 
  \ingroup Surfaces
*/ // ---
class MATH_CLASS MbSplineSurface : public MbPolySurface {

private:
  size_t         udegree; ///< \ru Порядок В-сплайна по u (порядок = степень + 1). \en Order of B-spline by u (order = degree + 1). 
  size_t         vdegree; ///< \ru Порядок В-сплайна по v (порядок = степень + 1). \en Order of B-spline by v (order = degree + 1). 
  SArray<double> uknots;  ///< \ru Узлы по u. \en Knots in u direction. 
  SArray<double> vknots;  ///< \ru Узлы по v. \en Knots in v direction. 
  MbWeightMatrix weights; ///< \ru Матрица весов контрольных точек. \en A matrix of control points weights. 

private:
  //------------------------------------------------------------------------------
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
    \details \ru Вспомогательные данные служат для ускорения работы объекта.
             \en Auxiliary data are used for fast calculations. \n \~
  */
  // ---
  class MbSplineSurfaceAuxiliaryData : public AuxiliaryData {
  public:
    double                        uc;               ///< \ru Параметр u, при котором насчитаны значения. \en Parameter u for the calculated values. 
    double                        vc;               ///< \ru Параметр v, при котором насчитаны значения. \en Parameter v for the calculated values. 
    MbVector3D                    rc[sdt_CountNor]; ///< \ru Расчитанные в точке (uc,vc) значения. \en Values calculated in the point (uc, vc). 

    DPtr<MbSurfaceContiguousData> data;  ///< \ru Дополнительные данные о поверхности. \en Additional data about a surface. 
    DPtr<MbSplineWorkingData>     wdata; ///< \ru Рабочие данные для расчета поверхности. \en Working data for the calculation of a surface. 
    double *                      wc;    ///< \ru Рассчитанные в точке (uc,vc) значения весов (может быть NULL). \en Weights values calculated in the point (uc, vc) (may be NULL). 

    MbSplineSurfaceAuxiliaryData();
    MbSplineSurfaceAuxiliaryData( const MbSplineSurfaceAuxiliaryData & init );
    virtual ~MbSplineSurfaceAuxiliaryData();
    void FreeMemory();
    bool CatchMemory( const size_t &, const size_t &, bool );
  };

  
  mutable CacheManager<MbSplineSurfaceAuxiliaryData> cache;

public:
  /// \ru Пустой конструктор. \en Empty constructor. 
  MbSplineSurface(); 
  
  /** \brief \ru Конструктор NURBS поверхности.
             \en Constructor of NURBS surface. \~
      \details \ru Конструктор NURBS поверхности. \n
               \en Constructor of NURBS surface. \n \~
      \param[in] uDeg - \ru Порядок сплайнов по u.
                        \en Splines order by U. \~
      \param[in] vDeg - \ru Порядок сплайнов по v.
                        \en Splines order by V. \~
      \param[in] uCls - \ru Замкнутость поверхности по u.
                        \en Closedness of a surface in u direction. \~
      \param[in] vCls - \ru Замкнутость поверхности по v.
                        \en Closedness of a surface in v direction. \~
      \param[in] initPoints - \ru Матрица контрольных точек.
                              \en A matrix of control points. \~
      \param[in] initUKnots - \ru Узловой вектор по u.
                              \en A knot vector by U. \~
      \param[in] initVKnots - \ru Узловой вектор по v.
                              \en A knot vector by V. \~
  */
  MbSplineSurface( size_t uDeg, size_t vDeg, bool uCls, bool vCls, const Array2<MbCartPoint3D> & initPoints,
                   const SArray<double> & initUKnots, const SArray<double> & initVKnots );

  /** \brief \ru Конструктор NURBS поверхности.
             \en Constructor of NURBS surface. \~
      \details \ru Конструктор NURBS поверхности. \n
               \en Constructor of NURBS surface. \n \~
      \param[in] uDeg - \ru Порядок сплайнов по u.
                        \en Splines degree by U. \~
      \param[in] vDeg - \ru Порядок сплайнов по v.
                        \en Splines degree by V. \~
      \param[in] uCls - \ru Замкнутость поверхности по u.
                        \en Closedness of a surface in u direction. \~
      \param[in] vCls - \ru Замкнутость поверхности по v.
                        \en Closedness of a surface in v direction. \~
      \param[in] initPoints - \ru Матрица контрольных точек.
                              \en A matrix of control points. \~
      \param[in] initWeights - \ru Матрица весов точек.
                               \en Matrix of point weights. \~
      \param[in] initUKnots - \ru Узловой вектор по u.
                              \en A knot vector by U. \~
      \param[in] initVKnots - \ru Узловой вектор по v.
                              \en A knot vector by V. \~
  */
  MbSplineSurface( size_t uDeg, size_t vDeg, bool uCls, bool vCls, const Array2<MbCartPoint3D> & initPoints, const Array2<double> & initWeights,
                   const SArray<double> & initUKnots, const SArray<double> & initVKnots );

  /** \brief \ru Конструктор NURBS поверхности по четырем углам при обходе против часовой стрелки.
             \en Constructor of NURBS surface by four angles of counterclockwise traverse. \~
      \details \ru Заданы углы поверхности. Остальные точки равномерно распределены внутри прямоугольника, заданного угловыми точками.
               \en Surface angles are given. Other points are uniformly distributed inside the rectangle which is given by angular points. \~
      \param[in] p1 - \ru Левый нижний угол. Соответствует точке (0, 0).
                      \en Left bottom angle. It corresponds to the point (0,0). \~
      \param[in] p2 - \ru Правый нижний угол. Соответствует точке (1, 0).
                      \en Right bottom angle. It corresponds to the point (1, 0). \~
      \param[in] p3 - \ru Правый верхний угол. Соответствует точке (1, 1).
                      \en Right top angle. It corresponds to the point (1, 1). \~
      \param[in] p4 - \ru Левый верхний угол. Соответствует точке (0, 1).
                      \en Left top angle. It corresponds to the point (0, 1). \~
      \param[in] iDegreeU - \ru Порядок сплайнов по u.
                            \en Splines degree by U. \~
      \param[in] iDegreeV - \ru Порядок сплайнов по v.
                            \en Splines degree by V. \~
      \param[in] iCountU - \ru Количество точек по u (Число столбцов в матрице точек).
                           \en The number of points by u (the number of columns in the points matrix). \~
      \param[in] iCountV - \ru Количество точек по v (Число строк в матрице точек).
                           \en The number of points by v (the number of rows in the points matrix). \~
  */
  MbSplineSurface( const MbCartPoint3D & p1, const MbCartPoint3D & p2,                 // p4---p3
                   const MbCartPoint3D & p3, const MbCartPoint3D & p4,                 //  |   |
                   size_t iDegreeU, size_t iDegreeV, size_t iCountU, size_t iCountV ); // p1---p2
protected:
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbSplineSurface( const MbSplineSurface & ); 
public:
  virtual ~MbSplineSurface ();

public:
  VISITING_CLASS( MbSplineSurface );

public:

          /// \ru Инициализация по другой поверхности. \en The initialization by another surface. 
          void    Init( const MbSplineSurface & );

          /** \brief \ru Инициализация заполненной поверхности.
                     \en Initialization of filled surface. \~
              \details \ru Инициализация заполненной поверхности.\n
                       \en Initialization of filled surface.\n \~
              \param[in] cPoints - \ru Матрица контрольных точек.
                                   \en A matrix of control points. \~
              \param[in] pWeights - \ru Матрица весов точек.
                                    \en Matrix of point weights. \~
          */
          bool    Init( const Array2<MbCartPoint3D> & cPoints,
                        const Array2<double> & pWeights );
          /** \brief \ru Инициализация заполненной поверхности.
                     \en Initialization of filled surface. \~
              \details \ru Инициализация заполненной поверхности.\n
                       \en Initialization of filled surface.\n \~
              \param[in] iDegreeU - \ru Новая степень сплайнов по u.
                                    \en New degree of splines by u. \~
              \param[in] iDegreeV - \ru Новая степень сплайнов по v.
                                    \en New degree of splines by v. \~
              \param[in] iClosedU - \ru Замкнутость поверхности по u.
                                    \en Closedness of a surface in u direction. \~
              \param[in] iClosedV - \ru Замкнутость поверхности по v.
                                    \en Closedness of a surface in v direction. \~
          */
          bool    Init( size_t iDegreeU, size_t iDegreeV, bool iClosedU, bool iClosedV );
          /** \brief \ru Заполнить сплайновую поверхность по данным parasolid.
                     \en Fill spline surface by parasolid data. \~
              \details \ru Заполнить сплайновую поверхность по данным parasolid.\n
                       \en Fill spline surface by parasolid data.\n \~
              \param[in] uCls - \ru Замкнутость поверхности по u.
                                \en Closedness of a surface in u direction. \~
              \param[in] vCls - \ru Замкнутость поверхности по v.
                                \en Closedness of a surface in v direction. \~
              \param[in] brational - \ru Является ли поверхность рациональной. true - строится NURBS поверхность, false - поверхность Безье.
                                     \en Whether a surface is rational. true - NURBS surface is constructed, false - Bezier surface. \~
              \param[in] uDgr - \ru Степень сплайнов по u.
                                \en Splines degree by U. \~
              \param[in] vDgr - \ru Степень сплайнов по v.
                                \en Splines degree by V. \~
              \param[in] uCnt - \ru Количество точек по u.
                                \en A number of points by U direction. \~
              \param[in] vCnt - \ru Количество точек по v.
                                \en A number of points by V direction. \~
              \param[in] vcs - \ru Множество координат точек. Если сплайн рациональный, четвертая координата - вес точки.
                               \en A set of points coordinates.. If spline is rational, then the fourth coordinate is the weight of a point. \~ 
              \param[in] vcsCnt - \ru Количество элементов в массиве vcs.
                                  \en Count of elements in the array vcs. \~
              \param[in] uKMul - \ru Множество с данными о кратности каждого узла по u.
                                 \en A set with the data about the multiplicity of each knot by u. \~
              \param[in] uKMulCnt - \ru Количество элементов в массиве uKMul.
                                    \en Count of elements in the array uKMul. \~
              \param[in] vKMul - \ru Множество с данными о кратности каждого узла по v.
                                 \en A set with the data about the multiplicity of each knot by v. \~
              \param[in] vKMulCnt - \ru Количество элементов в массиве vKMul.
                                    \en Count of elements in the array vKMul. \~
              \param[in] uKnt - \ru Множество со значениями узлов по u. Каждое значение представлено один раз. 
                Информация о кратности узла лежит в элементе массива uKMul с тем же номером.
                                \en A set with values of knots by u. Each value is represented once. 
                Information about knot multiplicity is in the element of 'uKMul' array with the same index. \~
              \param[in] uKntCnt - \ru Количество элементов в массиве uKnt.
                                   \en Count of elements in the array uKnt. \~
              \param[in] vKnt - \ru Множество со значениями узлов по v. Каждое значение представлено один раз. 
              Информация о кратности узла лежит в элементе массива vKMul с тем же номером.
                                \en A set with values of knots by v. Each value is represented once. 
              Information about knot multiplicity is in the element of 'vKMul ' array with the same index. \~
              \param[in] vKntCnt - \ru Количество элементов в массиве vKnt.
                                   \en Count of elements in the array vKnt. \~
              \param[in] scl - \ru Коэффициент масштабирования.
                               \en Scale factor. \~
          */
          bool    InitParasolid(     bool uCls, 
                                     bool vCls, 
                                     bool brational, 
                                     size_t uDgr, 
                                     size_t vDgr, 
                                     ptrdiff_t uCnt, 
                                     ptrdiff_t vCnt,
                                     const CcArray<double> & vcs,   
                                     ptrdiff_t vcsCnt,
                                     const CcArray<ptrdiff_t>    & uKMul, 
                                     ptrdiff_t uKMulCnt,
                                     const CcArray<ptrdiff_t>    & vKMul, 
                                     ptrdiff_t vKMulCnt,
                                     const CcArray<double> & uKnt,  
                                     ptrdiff_t uKntCnt,
                                     const CcArray<double> & vKnt,  
                                     ptrdiff_t vKntCnt, 
                                     double scl );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of geometric object.
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Cделать копию элемента. \en Make a copy of an element. 
  virtual bool    IsSame  ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Равны ли объекты. \en Whether the objects are equal. 
  virtual bool    SetEqual( const MbSpaceItem & );            // \ru Сделать равным. \en Make equal. 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void    GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты. \en Get the base objects. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */

  /** \ru \name Функции описания области определения поверхности.
      \en \name Functions for surface domain description.
      \{ */
  virtual double  GetUMin()   const;
  virtual double  GetVMin()   const;
  virtual double  GetUMax()   const;
  virtual double  GetVMax()   const;

  virtual bool    IsUClosed() const;  // \ru Замкнута ли гладко поверхность по параметру u без учета граничного контура. \en Whether the surface is smoothly closed by parameter u without regard to the boundary contour. 
  virtual bool    IsVClosed() const;  // \ru Замкнута ли гладко поверхность по параметру v без учета граничного контура. \en Whether the surface is smoothly closed by parameter v without regard to the boundary contour. 
  virtual bool    IsUTouch() const;  // \ru Замкнута ли фактически поверхность по параметру u независимо от гладкости. \en Whether the surface is actually closed by parameter u regardless of the smoothness. 
  virtual bool    IsVTouch() const;  // \ru Замкнута ли фактически поверхность по параметру v независимо от гладкости. \en Whether the surface is actually closed by parameter v regardless of the smoothness. 
  virtual bool    IsUPeriodic() const;  // \ru Замкнута ли гладко поверхность по параметру u. \en Whether the surface is smoothly closed by parameter u. 
  virtual bool    IsVPeriodic() const;  // \ru Замкнута ли гладко поверхность по параметру v. \en Whether the surface is smoothly closed by parameter v. 

  virtual size_t  GetUCount() const;
  virtual size_t  GetVCount() const;
  // \ru Существует ли полюс на границе параметрической области сплайновой кривой. \en Whether a pole exists on parametric region boundary of spline curve. 
  virtual bool    GetPoleUMin() const;
  virtual bool    GetPoleUMax() const;
  virtual bool    GetPoleVMin() const;
  virtual bool    GetPoleVMax() const;
  virtual bool    IsPole( double u, double v ) const; // \ru Является ли точка особенной. \en Whether the point is singular. 
  /** \} */

  /** \ru \name Функции для работы в области определения поверхности
            Функции PointOn, Derive... поверхностей корректируют параметры
            при выходе их за пределы прямоугольной области определения параметров.\n
      \en \name Functions for working at surface domain
            Functions PointOn, Derive... correct parameters
            when getting out of rectangular domain bounds. \n
      \{ */
  virtual void    PointOn  ( double & u, double & v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en A point on surface. 
  virtual void    DeriveU  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void    DeriveV  ( double & u, double & v, MbVector3D & ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void    DeriveUU ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
  virtual void    DeriveVV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
  virtual void    DeriveUV ( double & u, double & v, MbVector3D & ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
  virtual void    DeriveUUU( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по u. \en Second derivative with respect to u. 
  virtual void    DeriveUUV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по uuv. \en Third derivative with respect to uuv. 
  virtual void    DeriveUVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по uvv. \en Third derivative with respect to uvv. 
  virtual void    DeriveVVV( double & u, double & v, MbVector3D & ) const; // \ru Третья производная по v. \en Third derivative with respect to v. 
  virtual void    Normal   ( double & u, double & v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения поверхности
            функции _PointOn, _Derive... поверхностей не корректируют
            параметры при выходе их за пределы прямоугольной области определения параметров.
            За пределами параметрической области поверхность продолжается по касательной.
      \en \name Functions for working inside and outside the surface domain.
            functions _PointOn, _Derive... of surfaces don't correct
            parameters when getting out of rectangular domain bounds.
            Outside the limits of parametric region a surface is extended along a tangent.
      \{ */
  virtual void   _PointOn  ( double u, double v, MbCartPoint3D & ) const; // \ru Точка на поверхности. \en A point on surface. 
  virtual void   _DeriveU  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
  virtual void   _DeriveV  ( double u, double v, MbVector3D & ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
  virtual void   _DeriveUU ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
  virtual void   _DeriveVV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
  virtual void   _DeriveUV ( double u, double v, MbVector3D & ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
  virtual void   _DeriveUUU( double u, double v, MbVector3D & ) const; // \ru Третья производная по u. \en Second derivative with respect to u. 
  virtual void   _DeriveUUV( double u, double v, MbVector3D & ) const; // \ru Третья производная по uuv. \en Third derivative with respect to uuv. 
  virtual void   _DeriveUVV( double u, double v, MbVector3D & ) const; // \ru Третья производная по uvv. \en Third derivative with respect to uvv. 
  virtual void   _DeriveVVV( double u, double v, MbVector3D & ) const; // \ru Третья производная по v. \en Third derivative with respect to v. 
  virtual void   _Normal   ( double u, double v, MbVector3D & ) const; // \ru Нормаль. \en Normal. 
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметров поверхности.
      \en \name Functions for get of the group of data inside and outside the surface's domain of parameters.
      \{ */
  virtual void    Explore( double & u, double & v, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & uDer, MbVector3D & vDer,
                           MbVector3D * uuDer, MbVector3D * vvDer, MbVector3D * uvDer, MbVector3D * nor ) const;
  /** \} */

  /** \ru \name Функции движения по поверхности.
      \en \name Functions of moving on surface
      \{ */
  virtual double  StepU         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по U. \en Calculation of the approximation step with consideration of the curvature radius by U. 
  virtual double  StepV         ( double u, double v, double sag ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны по V. \en Calculation of the approximation step with consideration of the curvature radius by V. 

  virtual double  DeviationStepU( double u, double v, double sag ) const; // \ru Вычисление шага по u при пересечении поверхностей. \en Calculation of a step in direction of u for surfaces intersection. 
  virtual double  DeviationStepV( double u, double v, double sag ) const; // \ru Вычисление шага по v при пересечении поверхностей. \en Calculation of a step in direction of v for surfaces intersection. 
  /** \} */

  /** \ru \name Общие функции поверхности.
      \en \name Common functions of surface.
      \{ */
  virtual void    SetUClosed( bool cls ); // \ru Установить признак замкнутости по U. \en Set the attribute of closedness in direction of u. 
  virtual void    SetVClosed( bool cls ); // \ru Установить признак замкнутости по V. \en Set the attribute of closedness in direction of v. 

  virtual MbSplineSurface * NurbsSurface( double umin, double umax, double vmin, double vmax, bool bmatch = false ) const; // \ru NURBS-копия поверхности. \en NURBS copy of surface. 
  virtual MbSurface *       NurbsSurface( const MbNurbsParameters & uParam, const MbNurbsParameters & vParam ) const; // \ru NURBS-копия поверхности с заданными параметрами. \en NURBS copy of surface with given parameters. 

  virtual MbCurve3D * CurveU( double v, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии v = const. \en A spatial copy of the line v = const. 
  virtual MbCurve3D * CurveV( double u, MbRect1D * pRgn, bool bApprox = true ) const; // \ru Пространственная копия линии u = const. \en A spatial copy of the line u = const. 

  virtual void    Refresh(); // \ru Сбросить все временные данные. \en Reset all temporary data. 
  virtual void    Rebuild(); // \ru Инициализация поверхности. \en Initialization of surface. 

  // \ru Определение разбивки параметрической области поверхности вертикалями и горизонталями. \en Determine a splitting of parametric region of a surface by verticals and horizontals. 
  virtual void    GetTesselation( const MbStepData & stepData,
                                  double u1, double u2, double v1, double v2,
                                  SArray<double> & uu, SArray<double> & vv ) const;

  virtual void    SetLimit( double u1, double v1, double u2, double v2 );

  /** \brief \ru Проверить параметры. Аналог глобальной функции _CheckParams, оптимизированный под использование кэшей.
             \en Check parameters. Analogue of the global function _CheckParams, optimized for caches usage.  \~
    \details \ru Проверить параметры и загнать в область определения, если параметр вышел за полюс.
             \en Check parameters and move them inside domain if parameter is out of pole. \~
    \param[in] surface - \ru Поверхность. \en Surface. \~
    \param[in] u -       \ru Первый параметр. \en First parameter. \~
    \param[in] v -       \ru Второй параметр. \en Second parameter. \~
  */
  virtual void CheckSurfParams( double & u, double & v ) const;

  /** \brief \ru Построить усеченную поверхность.
             \en Construct a trimmed surface. \~
    \details \ru Построить усеченную поверхность.
             \en Construct a trimmed surface. \~
    \param[in] uBeg - \ru Параметр U, соответствующий началу усеченной поверхности.
                      \en Parameter U corresponding to start of a trimmed surface. \~
    \param[in] uEnd - \ru Параметр U, соответствующий концу усеченной поверхности.
                      \en Parameter U corresponding to end of a trimmed surface. \~
    \param[in] vBeg - \ru Параметр V, соответствующий началу усеченной поверхности.
                      \en Parameter V corresponding to start of a trimmed surface. \~
    \param[in] vEnd - \ru Параметр V, соответствующий концу усеченной поверхности.
                      \en Parameter V corresponding to end of a trimmed surface. \~
    \result \ru Построенная усеченная поверхность.
            \en A constructed trimmed surface. \~
  */
  MbSplineSurface * Trimmed( double uBeg, double uEnd, double vBeg, double vEnd ) const;

  virtual bool    IsPlanar() const; // \ru Является ли поверхность плоской. \en Whether a surface is planar. 

  // \ru Найти ближайшую проекцию точки на поверхность или ее продолжение по заданному начальному приближению. \en Find the neares projection of a point onto the surface. 
  virtual bool    NearPointProjection  ( const MbCartPoint3D & pnt, double & u, double & v, bool ext, MbRect2D * uvRange = NULL ) const; 
  // \ru Найти все проекции точки на поверхность вдоль вектора в любом из двух направлений. \en Find all a point projection onto the surface along a vector in either of two directions. 
  virtual void    DirectPointProjection( const MbCartPoint3D & pnt, const MbVector3D & vect, SArray<MbCartPoint> & uv, bool ext, MbRect2D * uvRange = NULL ) const; 

  // \ru Являются ли узловые векторы равными? \en Are knotVectos equal?
          bool    IsKnotsTheSame( const MbSplineSurface & e, bool sameDir, double precision ) const;
  // \ru Являются ли точки и веса равными? \en Are points and weights equal?
          bool    IsPointsTheSame( const MbSplineSurface & e, bool sameDir, bool uBeg, bool vBeg, double precision ) const;
  // \ru Определить, подобны ли поверхности для объединения. \en Define whether the surfaces are similar for merge.
  virtual bool    IsSimilarToSurface( const MbSurface & surf, double precision = METRIC_PRECISION ) const; 
  virtual bool    IsSpecialSimilarToSurface( const MbSurface & surf, VERSION version, double precision = METRIC_PRECISION ) const;
  // \ru Дать двумерную матрицу преобразования из своей параметрической области в параметрическую область surf. \en Get two-dimensional matrix of transformation from its parametric region to the parametric region of 'surf'.
  virtual bool    GetMatrixToSurface( const MbSurface & surf, MbMatrix & matr, double precision = METRIC_PRECISION ) const; 

          /** \brief \ru Изменение веса одной вершины.
                     \en Changing of one point weight \~
              \details \ru Изменение веса одной вершины.\n
                       \en Changing of one point weight \n \~
              \param[in] i - \ru Номер строки.
                             \en Row index. \~
              \param[in] j - \ru Номер столбца.
                             \en Column index. \~
              \param[in] w - \ru Новое значение веса.
                             \en New value of weight. \~
          */
          void    ChangeWeight ( ptrdiff_t i, ptrdiff_t j, double w ); 
          /** \brief \ru Изменение порядка поверхности.
                     \en Changing of surface order. \~
              \details \ru Изменение порядка поверхности.\n
                       \en Changing of surface order.\n \~
              \param[in] isU - \ru Определяет, по какой координате надо изменить порядок: true - по u, false - по v.
                               \en Determines a coordinate of the order changing: true - u, false - v. \~
              \param[in] order - \ru Новый порядок поверхности.
                                 \en A new surface order. \~
          */
          void    SetDegree ( bool isU, ptrdiff_t order );              
          /** \brief \ru Установить область изменения параметров.
                     \en Set the range of parameters. \~
              \details \ru Установить область изменения параметров.\n
                       \en Set the range of parameters.\n \~
              \param[in] pmin - \ru Минимальное значение по u.
                                \en The minimal parameter value by U. \~
              \param[in] pmax - \ru Максимальное значение по u.
                                \en The maximal parameter value by U. \~
              \param[in] qmin - \ru Минимальное значение по v.
                                \en The minimal parameter value by V. \~
              \param[in] qmax - \ru Максимальное значение по v.
                                \en The maximal parameter value by V. \~
          */
          MbMatrix SetLimitParam( double pmin, double pmax, double qmin, double qmax ); 

          /// \ru Получить порядок В-сплайна по u. \en Get the order of B-spline by u. 
          size_t    GetUDegree  ()            const { return udegree; } 
          /// \ru Получить порядок В-сплайна по v. \en Get the order of B-spline by v. 
          size_t    GetVDegree  ()            const { return vdegree; } 
          /// \ru Получить количество строк в матрице весов. \en Get rows count in weights matrix. 
          size_t    GetWeightsLines()         const { return weights.Lines();   } 
          /// \ru Получить количество столбцов в матрице весов. \en Get columns count in weights matrix. 
          size_t    GetWeightsColumns()       const { return weights.Columns(); } 
          /** \brief \ru Получить вес вершины.
                     \en Get vertex weight. \~
              \details \ru Получить вес вершины.\n
                       \en Get vertex weight.\n \~
              \param[in] i - \ru Номер строки.
                             \en Row index. \~
              \param[in] j - \ru Номер столбца.
                             \en Column index. \~
              \return \ru Значение веса.
                      \en A value of weight. \~
          */
          double    GetWeight( ptrdiff_t i, ptrdiff_t j ) const { return weights.GetWeight( i, j ); }

  // \ru Получить матрицу весов вершин. \en Get the matrix of vertices weights. 
  virtual void    GetWeights( Array2<double> & wts ) const { weights.GetWeights( wts ); }

          /** \brief \ru Получить количество элементов в узловом векторе.
                     \en Get the number of elements in a knot vector. \~
              \details \ru Получить количество элементов в узловом векторе.\n
                       \en Get the number of elements in a knot vector.\n \~
              \param[in] isU - \ru Определяет, по какой координате запрашивается узловой вектор: true - по u, false - по v.
                               \en Determines the requested coordinate of a knot vector: true - u, false - v. \~
              \return \ru Количество элементов в узловом векторе.
                      \en The number of elements in a knot vector. \~
          */
          size_t  GetKnotsCount( bool isU ) const { return (isU ? uknots.Count() : vknots.Count()); }

  // \ru Получить узловой вектор по выбранному параметру. \en Get a knot vector by the chosen parameter. 
  virtual void    GetKnots( bool isU, SArray<double> & knots ) const { knots = (isU ? uknots :  vknots); }
          /** \brief \ru Получить значение одного узла.
                     \en Get the value of one knot. \~
              \details \ru Получить значение одного узла.\n
                       \en Get the value of one knot.\n \~
              \param[in] isU - \ru Определяет, по какой координате запрашивается узловой вектор: true - по u, false - по v.
                               \en Determines the requested coordinate of a knot vector: true - u, false - v. \~
              \param[in] i - \ru Номер элемента в узловом векторе.
                             \en The index of an element in a knot vector. \~
              \return \ru Значение узла.
                      \en A value of knot. \~
          */
          double  GetKnot( bool isU, size_t i ) const;

  // \ru Вставка ряда после ряда с номером idBegin без изменения поверхности по u. \en Insertion of a row after the row with the index idBegin without changing of a surface by u. 
  virtual void    InsertUKnotsInRegion( ptrdiff_t idBegin, ptrdiff_t num = 1 );

          /** \brief \ru Вставка ряда со значением узла newKnot без изменения поверхности по u.
                     \en Insertion of a row with the value of the knot newKnot without changing of a surface by u. \~
              \details \ru Вставка ряда со значением узла newKnot без изменения поверхности по u.\n
                       \en Insertion of a row with the value of the knot newKnot without changing of a surface by u.\n \~
              \param[in] newKnot - \ru Значение узла.
                                   \en A value of knot. \~
              \param[in] multiplicity - \ru Количество вставляемых рядов.
                                        \en Count of inserted rows. \~
          */
          void    InsertUKnots( double & newKnot, ptrdiff_t multiplicity ); // 

  // \ru Вставка ряда после ряда с номером idBegin без изменения поверхности по v. \en Insertion of a row after the row with the index idBegin without changing of a surface by v. 
  virtual void    InsertVKnotsInRegion( ptrdiff_t idBegin, ptrdiff_t num = 1 );

          /** \brief \ru Вставка ряда со значением узла newKnot без изменения поверхности по v.
                     \en Insertion of a row with the value of the knot newKnot without changing of a surface by v. \~
              \details \ru Вставка ряда со значением узла newKnot без изменения поверхности по v.\n
                       \en Insertion of a row with the value of the knot newKnot without changing of a surface by v.\n \~
              \param[in] newKnot - \ru Значение узла.
                                   \en A value of knot. \~
              \param[in] multiplicity - \ru Количество вставляемых рядов.
                                        \en Count of inserted rows. \~
          */
          void    InsertVKnots( double & newKnot, ptrdiff_t multiplicity ); // 

  // \ru Вычисление точек на поверхности, соответствующих узлам. \en Calculation of points on surface corresponding to knots. 
  virtual void    CalculateUVParameters( Array2<MbCartPoint> & params ) const;
  // \ru Вычисление точки на поверхности, соответствующей контрольной точке. \en Calculation of point on surface corresponding to control point. 
  virtual bool    CalculateUVParameterForKnot( size_t uIndex, size_t vIndex, MbCartPoint & point ) const;

  // \ru Вычисление доли смещения узлов при перемещении со сглаживанием. \en Calculation of a shift part of knots during the translation with blending. 
  virtual bool    CalculatePartsForSpecMove( const Array2<bool> & movedPoints, 
                                             size_t uIndex, size_t vIndex, 
                                             const MbVector3D & moveVector,
                                             MbeDirectSmoothType smoothType,
                                             double smoothDegree,
                                             Array2<double> & partsPoints ) const;

  // \ru Вычисление фиксированных контрольных точек. \en Calculation of fixed control points. 
  virtual bool    CalculateFixedPoints( const RPArray<const MbSurfaceIntersectionCurve> & curves, Array2<bool> & fixedPoints ) const;

          bool    CalculateFixedLimits( const MbSurfaceCurve & curve, ptrdiff_t & u1, ptrdiff_t & u2, ptrdiff_t & v1, ptrdiff_t & v2 ) const;

  // \ru Удаление столбца контрольных точек без изменения поверхности. \en Deletion of a column of control points without changing of a surface. 
  virtual size_t  RemoveUKnots( ptrdiff_t & rowId, ptrdiff_t num = 1, double absEps = Math::lengthEpsilon ); // \ru Удаление узла в u \en Deletion of knot in u direction 
  // \ru Удаление строки контрольных точек без изменения поверхности. \en Deletion of a row of control points without changing of a surface. 
  virtual size_t  RemoveVKnots( ptrdiff_t & rowId, ptrdiff_t num = 1, double absEps = Math::lengthEpsilon ); // \ru Удаление узла в v \en Deletion of knot in v direction 
  // \ru Изменить порядок nurbs путем перестроения поверхности с помощью функции NurbsSurface. \en Change an order of NURBS by construction of a surface by the function NurbsSurface. 
  virtual bool    ChangeUDegreeApprox ( size_t newDegree );
  // \ru Изменить порядок nurbs путем перестроения поверхности с помощью функции NurbsSurface. \en Change an order of NURBS by construction of a surface by the function NurbsSurface. 
  virtual bool    ChangeVDegreeApprox ( size_t newDegree );
  // \ru Изменить порядок и количество узлов nurbs путем перестроения поверхности с помощью функции NurbsSurface. \en Change an order and a number of knots of NURBS by construction of a surface by the function NurbsSurface. 
  virtual bool    ChangeParametersApprox ( size_t nUDegree, size_t nVDegree, ptrdiff_t nUCount, ptrdiff_t nVCount );
          /** \brief \ru Перестроить поверхность с помощью функции NurbsSurface без кратных узлов.
                     \en Rebuild a surface by the function NurbsSurface without multiple knots. \~
              \details \ru Перестроить поверхность с помощью функции NurbsSurface без кратных узлов.\n
                       \en Rebuild a surface by the function NurbsSurface without multiple knots.\n \~
              \return \ru true, если аппроксимация выполнена успешно.
                      \en True if approximation is succeeded. \~
          */
          bool    ApproxSurfWithoutMultKnots ();

  // \ru Вернуть массив узловых точек и их видимость для операции редактирования как сплайна. \en Return an array of knot points and their visibility for the operation of editing as spline. 
  virtual void    GetPointsWithVisible ( Array2<MbNurbsPointInfo> & params ) const; 
          /** \brief \ru Модифицировать массив узловых точек с учетом перемещения невидимых точек.
                     \en Modify an array of knot points considering the moving of invisible points. \~
              \details \ru Модифицировать массив узловых точек с учетом перемещения невидимых точек.\n
                       \en Modify an array of knot points considering the moving of invisible points.\n \~
              \param[in] oldPoints - \ru Матрица контрольных точек.
                                     \en A matrix of control points. \~
              \param[in,out] newPoints - \ru Матрица контрольных точек после корректирования положения невидимых точек.
                                         \en A matrix of control points after the correction of invisible points location. \~
          */
          void    ModifyPointsWithVisible ( const Array2<MbCartPoint3D> & oldPoints, Array2<MbCartPoint3D> & newPoints ) const; 

          /** \brief \ru Зажать или разжать узловой вектор.
                     \en Whether to clamp a knot vector. \~
              \details \ru Преобразовать узловой вектор по u в зажатый, если поверхность замкнута по u и clm = false. 
                     Если не замкнута и clm = true - преобразовать узловой вектор в разжатый.
                       \en Make a knot vector  by u clamped if a surface is closed in u direction and clm = false. 
                     If it is not closed and clm = true then make knot vector unclamped. \~
              \param[in] clm - \ru Зажать или разжать узловой вектор.
                               \en Whether to clamp a knot vector. \~
          */
          bool    UnClampedU( bool clm );
          /** \brief \ru Зажать или разжать узловой вектор.
                     \en Whether to clamp a knot vector. \~
              \details \ru Преобразовать узловой вектор по v в зажатый, если поверхность замкнута по v и clm = false. 
                     Если не замкнута и clm = true - преобразовать узловой вектор в разжатый.
                       \en Make a knot vector  by v clamped if a surface is closed in v direction and clm = false. 
                     If it is not closed and clm = true then make knot vector unclamped. \~
              \param[in] clm - \ru Зажать или разжать узловой вектор.
                               \en Whether to clamp a knot vector. \~
          */
          bool    UnClampedV( bool clm );

          /// \ru Делаем зажатый узловой вектор. \en Make a clumped knot vector. 
          void    SetClampedU(); 
          /// \ru Делаем зажатый узловой вектор. \en Make a clumped knot vector. 
          void    SetClampedV(); 

          /** \brief \ru Установить типы границ поверхности.
                     \en Set types of surfaces boundaries. \~ 
              \details \ru Установить типы границ поверхности.  Используется в конвертерах.
                       \en Set types of surfaces boundaries.  This is used in converters. \~
              \param[in] cuMin - \ru Тип поверхности при u - минимальном.
                                 \en A type of surface when u is minimal. \~
              \param[in] cuMax - \ru Тип поверхности при u - максимальном.
                                 \en A type of surface when u is maximal. \~
              \param[in] cvMin - \ru Тип поверхности при v - минимальном.
                                 \en A type of surface when v is minimal. \~
              \param[in] cvMax - \ru Тип поверхности при v - максимальном.
                                 \en A type of surface when v is maximal. \~
          */
          void    SetBordersTypes( bool cuMin, bool cuMax, bool cvMin, bool cvMax );

          /** \brief \ru Проверить является ли точка полюсной и убрать разрыв в первой производной.
                     \en Check whether a point is a pole and remove discontinuity of the first derivative. \~
              \details \ru Проверить является ли точка полюсной и убрать разрыв в первой производной.\n
                       \en Check whether a point is a pole and remove discontinuity of the first derivative.\n \~
              \param[in] pnt - \ru Точка, в которой производится проверка.
                               \en A point where the check is performed. \~
              \param[in] absEps - \ru Точность.
                                  \en Tolerance. \~
              \param[in] bSet - \ru Замещать ли контрольные точки, соответствующие полюсу и 
                совпадающие с указанной точностью с точкой pnt, точкой pnt.
                                \en Whether to replace control points corresponding to the pole and 
                coincident with the given tolerance with the point pnt. \~
          */
          bool    CheckPolePoint( const MbCartPoint3D & pnt, double absEps, bool bSet );

          /// \ru Если поверхность касается по U - убрать разрыв в первой производной. \en If surface is touched by U then remove the discontinuity of the first derivative. 
          void    SoftUTouch(); 
          /// \ru Если поверхность касается по V - убрать разрыв в первой производной. \en If surface is touched by V then remove the discontinuity of the first derivative. 
          void    SoftVTouch(); 

  virtual bool    IsLineU() const; // \ru Если true, то все производные по U выше первой равны нулю. \en If it equals true, then all derivatives with respect to u which have more than first order are equal to null. 
  virtual bool    IsLineV() const; // \ru Если true, то все производные по V выше первой равны нулю. \en If it equals true, then all derivatives with respect to v which have more than first order are equal to null. 

  /// \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual double  GetRadius() const;
  /// \ru Дать радиус скругления, если поверхность является поверхностью скругления. \en Get fillet radius if the surface is a fillet surface. 
  virtual double  GetFilletRadius( const MbCartPoint3D & p ) const;
  /// \ru Направление поверхности скругления. \en Direction of fillet surface. 
  virtual MbeParamDir GetFilletDirection() const;
  /// \ru Дать ось вращения для поверхности. \en Get rotation axis of a surface. 
  virtual bool    GetCylinderAxis( MbAxis3D & ) const;

  virtual size_t  GetUMeshCount() const; // \ru Выдать количество полигонов по u. \en Get the number of polygons in u-direction. 
  virtual size_t  GetVMeshCount() const; // \ru Выдать количество полигонов по v. \en Get the number of polygons in v-direction. 

          /// \ru Проверить, является ли поверхность рациональной, но не регулярной. \en Check whether a surface is rational but not regular. 
          bool    IsRational() const;

          /// \ru Удалить временную структуру данных - разбивку поверхности. \en Delete the temporary data structure - surface tesselation.
          void    DeleteTesselation() const; 

          /** \brief \ru Создать двумерную кривую, если пространственная кривая является границей поверхности.
                     \en Create a two-dimensional curve if a space curve is a surface boundary. \~
              \details \ru Создать двумерную кривую, если пространственная кривая является границей поверхности.\n
                       \en Create a two-dimensional curve if a space curve is a surface boundary.\n \~
              \param[in] curve - \ru Заданная пространственная кривая.
                                 \en A given space curve. \~
              \return \ru Ссылка на двумерную кривую на поверхности или NULL, если построить ее не удалось.
                      \en A reference to the two-dimensional curve on a surface or NULL if the construction of it is failed. \~
          */
          MbCurve * IsSplineBorder( const MbCurve3D & curve ) const;

          /** \brief \ru Области поверхности, параллельные направлению.
                     \en Regions of a surface parallel to the direction. \~
            \details \ru Области поверхности, наборы точек в которой параллельны заданному направлению.
                     \en Regions of a surface the point sets of which are parallel to the given direction. \~
            \param[in]  direction      - \ru Направление.
                                         \en Direction. \~
            \param[out] collinearRects - \ru Найденные области внутри области определения поверхности.
                                         \en Found regions inside the domain of a surface. \~
            \warning \ru В разработке.
                     \en Under development. \~
          */
          void    DirectParallelRects( const MbVector3D & direction, std::vector<MbRect> & parallelRects ) const;

private:
          bool    CheckPoles( MbSplineSurfaceAuxiliaryData * ) const; // \ru Проверить наличие полюсов. \en Check poles existence. 

          void    SetClosed( bool isU, bool cls );  // \ru Установить признак замкнутости. \en Set attribute of closedness. 

          void    SetKnots             ( size_t degree, ptrdiff_t count, bool close, SArray<double> & knots ); // \ru Установка значений узлового вектора \en Setting of knot vector values. 
          void    OpenKnotsVector      ( size_t degree, ptrdiff_t count, SArray<double> & knots ); // \ru Переопределение базисного узлового вектора из Close в Open. \en Redetermination of the basis knot vector from Close to Open. 
          void    CloseKnotsVector     ( size_t degree, ptrdiff_t count, SArray<double> & knots, double ); // \ru Переопределение базисного узлового вектора из Open в Close. \en Redetermination of the basis knot vector from Open to Close. 

          bool    InitPatch            ( MbSplineSurfaceAuxiliaryData * ) const;
          void    CalculatePatch       ( double & u, double & v, MbSplineSurfaceAuxiliaryData * ) const;
          void    CalculateSpline      ( int, MbSplineSurfaceAuxiliaryData * ) const; // \ru Расчет вектора точки и его первых, вторых и третьих производных. \en Calculation of the point vector and its first, second and third derivatives 
          void    CalculateSplineWeight( int, MbSplineSurfaceAuxiliaryData * ) const;

          bool    CatchMemory( MbSplineSurfaceAuxiliaryData * ) const;
          void    FreeMemory ( MbSplineSurfaceAuxiliaryData * ) const;

          void    ResetCache();

          void    operator = ( const MbSplineSurface & ); // \ru Не реализовано. \en Not implemented. 

          double  GetMeanParam( bool isU, double, double ) const; // \ru Получить среднее расстояние между band-ами. \en Get the middle distance between 'band'-s. 
          double  GetKoef( bool isU ) const; // \ru Получить коэффициент пересчета из длины в параметры. \en Get a coefficient of recalculation of the length to the parameters. 
         
          // \ru Служебные аналоги публичных функций, которые используют заданный кэш. \en Service analogs of public functions that use a given cache.
          void    DeriveU         ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
          void    DeriveV         ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
          void    DeriveUU        ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Вторая производная по u. \en Second derivative with respect to u. 
          void    DeriveVV        ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Вторая производная по v. \en Second derivative with respect to v. 
          void    DeriveUUU       ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по u. \en Second derivative with respect to u. 
          void    DeriveVVV       ( double & u, double & v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по v. \en Third derivative with respect to v. 
          void    DeriveUV        ( double & u, double & v, MbVector3D & , MbSplineSurfaceAuxiliaryData * ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
          void    DeriveUUV       ( double & u, double & v, MbVector3D & , MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по uuv. \en Third derivative with respect to uuv. 
          void    DeriveUVV       ( double & u, double & v, MbVector3D & , MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по uvv. \en Third derivative with respect to uvv. 
          bool    IsRational      ( MbSplineSurfaceAuxiliaryData * ) const; // \ru Проверить, является ли поверхность рациональной, но не регулярной. \en Check whether a surface is rational but not regular. 
          size_t  GetUCount       ( MbSplineSurfaceAuxiliaryData * ) const;
          size_t  GetVCount       ( MbSplineSurfaceAuxiliaryData * ) const;
          double  DeviationStepV  ( double u, double v, double sag, MbSplineSurfaceAuxiliaryData * ) const; // \ru Вычисление шага по v при пересечении поверхностей. \en Calculation of a step in direction of v for surfaces intersection. 
          double  DeviationStepU  ( double u, double v, double sag, MbSplineSurfaceAuxiliaryData * ) const; // \ru Вычисление шага по u при пересечении поверхностей. \en Calculation of a step in direction of u for surfaces intersection. 
          void    CheckSurfParams ( double & u, double & v, MbSplineSurfaceAuxiliaryData * ) const; // \ru Проверить параметры. \en Check parameters.
          void    _DeriveU        ( double u, double v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Первая производная по u. \en First derivative with respect to u. 
          void    _DeriveV        ( double u, double v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Первая производная по v. \en First derivative with respect to v. 
          void    _DeriveUV       ( double u, double v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Вторая производная по uv. \en Second derivative with respect to u and v. 
          void    _DeriveUUV      ( double u, double v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по uuv. \en Third derivative with respect to uuv. 
          void    _DeriveUVV      ( double u, double v, MbVector3D &, MbSplineSurfaceAuxiliaryData * ) const; // \ru Третья производная по uvv. \en Third derivative with respect to uvv. 
          bool    GetPoleUMin     ( MbSplineSurfaceAuxiliaryData * ) const;
          bool    GetPoleUMax     ( MbSplineSurfaceAuxiliaryData * ) const;
          bool    GetPoleVMin     ( MbSplineSurfaceAuxiliaryData * ) const;
          bool    GetPoleVMax     ( MbSplineSurfaceAuxiliaryData * ) const;
          bool    IsPole          ( double u, double v, MbSplineSurfaceAuxiliaryData * ) const; // \ru Является ли точка особенной. \en Whether the point is singular. 

          double  StepD             ( bool isU, double u, double v, double sag, bool checkAngle, double angle, MbSplineSurfaceAuxiliaryData * ) const;
          double  StepDPlus         ( bool isU, double u, double v, double sag, bool checkAngle, double angle, MbSplineSurfaceAuxiliaryData * ) const;
          double  DeviationStep     ( bool isU, double u, double v, double angle, MbSplineSurfaceAuxiliaryData * ) const;
          double  DeviationStepPlus ( bool isU, double u, double v, double angle, MbSplineSurfaceAuxiliaryData * ) const;
          void    TypedStepPlus     ( double u, double v, bool alongU, const MbStepData & stepData, double & step, MbSplineSurfaceAuxiliaryData * ) const;
          double  GetMinStep        ( bool isU, const double * pRng = NULL ) const;

          bool    ApproxAsPlane() const; // \ru Можно ли аппроксимировать поверхность как плоскость. \en Whether a surface can be approximated by a plane. 
          // \ru Вычислить аппроксимацию поверхности, считая, что ее можно аппроксимировать как плоскость. \en Calculate an approximation of surface assuming that it can be approximated by a plane. 
          MbSplineSurface * CalcApproxAsPlane( size_t nUDegree, size_t nVDegree, ptrdiff_t nUCount, ptrdiff_t nVCount ) const; 
          bool    UseMultiplKnots() const;

          void    PoleDerive( double u, double v, MbVector3D & vDerU, MbVector3D & vDerV, MbSplineSurfaceAuxiliaryData * ) const;

  inline  void    CheckParam( const SArray<double> & knots, const ptrdiff_t & degree, const bool & closed, double & t ) const; 

          // \ru Создать двумерную кривую, если пространственная кривая является границей поверхности. \en Create a two-dimensional curve if a space curve is surface boundary. 
          MbCurve * IsFullSplineBorder( const MbCurve3D & curve ) const;
          MbCurve * IsPartSplineBorder( const MbCurve3D & curve ) const;

          void    GetVertecisRects( const MbVector3D & direction, bool u, 
                                    std::vector<std::pair<c3d::IndicesPair, c3d::IndicesPair> > & vertecesRects ) const;
 private:
          void    CalculateDerivativesAlong( double & u, double & v, bool isU, MbVector3D & tDer, MbVector3D & ttDer,
                                             MbSplineSurfaceAuxiliaryData * ) const;
          void    CalculateDerivativesAlong( double & u, double & v, bool isU, MbVector3D & tDer, MbVector3D & ttDer, MbVector3D & tttDer,
                                             MbSplineSurfaceAuxiliaryData * ) const;

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbSplineSurface )
};

IMPL_PERSISTENT_OPS( MbSplineSurface )

//------------------------------------------------------------------------------
// \ru Проверка нахождения параметра в области определения и корректировка. \en Check that parameter is within the domain and correction. 
// ---
 inline void MbSplineSurface::CheckParam( const SArray<double> & knots, const ptrdiff_t& degree, const bool& closed, double & t ) const
{
  const double & tmin = knots[degree - 1];
  const double & tmax = knots[knots.Count() - degree];

  if ( closed ) {
    if ( (t < tmin) || (t > tmax) ) {
      double trgn = tmax - tmin;
      t -= ::floor( (t - tmin) / trgn ) * trgn;
    }
  }
  else if ( t < tmin )
    t = tmin;
  else if ( t > tmax )
    t = tmax;
}


//------------------------------------------------------------------------------
/** \brief \ru Определить параметрическое распределение точек для построения NURBS поверхности, проходящей через эти точки.
           \en Determine a parametric distribution of points for the construction of NURBS surface passing through these points. \~
    \details \ru Определить параметрическое распределение точек для построения NURBS поверхности, проходящей через эти точки. 
             Параметр, для которого определяется распределение точек, задается переменной alongLines 
             (если true - то распределение по v, иначе по u). Определяется усредненное распределение по всем рядам (строкам).
             \en Determine a parametric distribution of points for the construction of NURBS surface passing through these points. 
             The parameter for which distribution of points is determined is set by the variable alongLines. 
             (if true then there is a distribution by v, otherwise - by u). An average distribution by all rows is determined. \~
    \param[in] degree - \ru Порядок поверхности по заданному параметру.
                        \en An order of a surface by the given parameter. \~
    \param[in] closed - \ru Замыкание поверхности по заданному параметру.
                        \en A closure of a surface by the given parameter. \~
    \param[in] points - \ru Матрица точек, для которых надо определить параметрическое распределение.
                        \en A matrix of points for which the parametric distribution should be determined. \~
    \param[in] alongLines - \ru Определяет, по какому параметру ищется распределение (true - по v, false - по u).
                            \en Determines a parameter by which the distribution is sought (true - by v, false - by u). \~
    \param[in] spType - \ru Тип параметризации сплайновых объектов: \n
      spt_Unstated - неустановленный, \n
      spt_EquallySpaced - равномерная, \n
      spt_ChordLength - по длине хорды (расстоянию между точками), \n
      spt_Centripetal - центростремительная (квадратный корень расстояния между точками).
                        \en The parameterization type of spline objects: \n
      spt_Unstated - unspecified, \n
      spt_EquallySpaced - uniform, \n
      spt_ChordLength - by chord length (by distance between the points), \n
      spt_Centripetal - centripetal (square root of the distance between the points). \~
    \param[in] params - \ru Множество с искомым распределением.
                        \en A set with the required distribution. \~
    \return \ru true, если вычисления прошли успешно.
            \en True if the calculations were successfully performed.. \~
    \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) DefineThroughPointsParams( ptrdiff_t degree, bool closed, const Array2<MbCartPoint3D> & points, bool alongLines,
                                            MbeSplineParamType spType, SArray<double> & params );


//------------------------------------------------------------------------------
/** \brief \ru Определить параметрическое распределение точек для построения NURBS поверхности, проходящей через эти точки.
           \en Determine a parametric distribution of points for the construction of NURBS surface passing through these points. \~
    \details \ru Определить параметрическое распределение точек для построения NURBS поверхности, проходящей через эти точки. 
             Параметр, для которого определяется распределение точек, задается переменной alongLines 
             (если true - то распределение по v, иначе по u).
             \en Determine a parametric distribution of points for the construction of NURBS surface passing through these points. 
             The parameter for which distribution of points is determined is set by the variable alongLines. 
             (if true then there is a distribution by v, otherwise - by u). \~
    \param[in] degree - \ru Порядок поверхности по заданному параметру.
                        \en An order of a surface by the given parameter. \~
    \param[in] closed - \ru Замыкание поверхности по заданному параметру.
                        \en A closure of a surface by the given parameter. \~
    \param[in] points - \ru Матрица точек, для которых надо определить параметрическое распределение.
                        \en A matrix of points for which the parametric distribution should be determined. \~
    \param[in] alongLines - \ru Определяет, по какому параметру ищется распределение (true - по v, false - по u).
                            \en Determines a parameter by which the distribution is sought (true - by v, false - by u). \~
    \param[in] rowInd - \ru Строка или столбец, по которому вычисляется распределение.
                        \en A row or a column by which the distribution is calculated. \~
    \param[in] spType - \ru Тип параметризации сплайновых объектов: \n
      spt_Unstated - неустановленный, \n
      spt_EquallySpaced - равномерная, \n
      spt_ChordLength - по длине хорды (расстоянию между точками), \n
      spt_Centripetal - центростремительная (квадратный корень расстояния между точками).
                        \en The parameterization type of spline objects: \n
      spt_Unstated - unspecified, \n
      spt_EquallySpaced - uniform, \n
      spt_ChordLength - by chord length (by distance between the points), \n
      spt_Centripetal - centripetal (square root of the distance between the points). \~
    \param[in] params - \ru Множество с искомым распределением.
                        \en A set with the required distribution. \~
    \return \ru true, если вычисления прошли успешно.
            \en True if the calculations were successfully performed.. \~
    \ingroup Algorithms_3D
*/
// ---
MATH_FUNC (bool) DefineThroughPointsParams( ptrdiff_t degree, bool closed, const Array2<MbCartPoint3D> & points, bool alongLines, ptrdiff_t rowInd,
                                            MbeSplineParamType spType, SArray<double> & params );


//------------------------------------------------------------------------------
// \ru Расчет точки поверхности. \en Calculation of surface point. 
// ---
MATH_FUNC (bool) NurbsSurfacePoint( ptrdiff_t uDeg, const SArray<double> & uKnots, bool uCls, double uCur, SArray<double> & uSplines,
                                    ptrdiff_t vDeg, const SArray<double> & vKnots, bool vCls, double vCur, SArray<double> & vSplines,
                                    const Array2<MbCartPoint3D> & points, const Array2<double> * weights,
                                    MbCartPoint3D & nsPnt );


//------------------------------------------------------------------------------
// \ru Корректна ли плоская сплайновая поверхность. \en Whether a planar spline surface is correct. 
// ---
MATH_FUNC (bool) IsValidPlanar( const MbSplineSurface & );


//------------------------------------------------------------------------------
// \ru Корректна ли сплайновая поверхность с полюсами. \en Whether a spline surface with poles is correct. 
// ---
MATH_FUNC (bool) IsValidPoles( const MbSplineSurface & newSurf, const MbSurface & oldSurf );


#endif // __SURF_SPLINE_SURFACE_H
