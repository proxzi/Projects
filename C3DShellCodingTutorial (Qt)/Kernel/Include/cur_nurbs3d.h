////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Пространственная NURBS кривая.
         \en A spatial NURBS curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_NURBS3D_H
#define __CUR_NURBS3D_H


#include <templ_c_array.h>
#include <templ_array2.h>
#include <tool_multithreading.h>
#include <mb_homogeneous3d.h>
#include <mb_nurbs_function.h>
#include <mb_point_mating.h>
#include <cur_nurbs_vector3d.h>
#include <cur_polycurve3d.h>


class  MATH_CLASS MbNurbs;
class  MATH_CLASS MbBezier3D;


//------------------------------------------------------------------------------
/** \brief \ru NURBS кривая в трехмерном пространстве.
           \en NURBS curve in three-dimensional space. \~ 
  \details \ru NURBS кривая определяется контрольными точками pointList, 
    весами контрольных точек weights, узловым вектором knots и порядком сплайна degree.\n
    Аббревиатура NURBS получена из первых букв словосочетания Non-Uniform Rational B-Spline.
    NURBS кривая не проходит через свои контрольные точки.
    Узловой вектор knots должен представлять собой неубывающую последовательность действительных чисел.
    Множества pointList и weights должны содержать одинаковое количество элементов. 
    Для не замкнутой кривой узловой вектор knots должен содержать количество элементов множества pointList плюс degree.
    Для замкнутой кривой кривой узловой вектор knots должен содержать количество элементов множества pointList плюс 2*degree-1. 
    Минимальное значение параметра сплайна равно значению элемента узлового вектора с индексом degree-1. 
    Максимальное значение параметра сплайна равно значению элемента узлового вектора с индексом, равным последнему элементу минус degree-1. 
    Расчет кривой в каждой своей точке производится на основе нормированных неоднородных В-сплайнов.\n
    Семейство В-сплайнов определяется заданной неубывающей последовательностью узловых параметров и заданным порядком B-сплайна.\n
           \en NURBS curve is defined by 'pointList' control points, 
    'weights' weights of control points, 'knots' knot vector and 'degree' spline order.\n
    Abbreviation of NURBS is obtained from the first letters of the Non-Uniform Rational B-Spline phrase.
    NURBS curve doesn't pass through its control points.
    'knots' knot vector has to be nondecreasing sequence of real numbers.
    'pointList' and 'weights' sets have to contain the same count of elements. 
    For not closed curve knot vector 'knots' has to contain the count of elements of 'pointList' set plus 'degree'.
    For closed curve knot vector 'knots' has to contain the count of elements of 'pointList' set plus 2*degree-1. 
    Minimal value of spline parameter is equal to value of the element of knot vector with degree-1 index. 
    Maximal value of spline parameter is equal to the value of element of knot vector with index, which is equal to index of the last element minus degree-1. 
    Curve calculation at each point is performed using normalized non-uniform B-splines.\n
    Family of B-splines is defined by the given nondecreasing sequence of knot parameters and the given order of B-spline.\n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbNurbs3D : public MbPolyCurve3D {
private :
  ptrdiff_t      degree;        ///< \ru Порядок В-сплайна (порядок = степень + 1). \en Order of B-spline (order = degree + 1). 
  ptrdiff_t      uppKnotsIndex; ///< \ru Последний индекс узлового вектора. \en Last index of knot vector. 
  SArray<double> weights;       ///< \ru Множество весов контрольных точек. \en Set of weights of the control points. 
  SArray<double> knots;         ///< \ru Узловой вектор сплайна. \en Knot vector of the spline. 
  MbeNurbsCurveForm form;       ///< \ru Форма кривой. \en Shape of curve. 

private:
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  /** \brief \ru Вспомогательные данные. 
             \en Auxiliary data. \~
      \details \ru Вспомогательные данные служат для ускорения работы объекта.
               \en Auxiliary data are used for fast calculations. \n \~
    */
  // ---
  class MbNurbs3DAuxiliaryData : public AuxiliaryData {
  public:
    double            tCalc; ///< \ru Текущее значение параметра, по которому вычислены временные данные кривой. \en Current value of parameter the curve temporary data are calculated by. 
    double          * nd;    ///< \ru B - базис. \en B - basis. 
    MbHomogeneous3D * h0;    ///< \ru Текущий сегмент. \en Current segment. 
    MbHomogeneous3D * h1;    ///< \ru Текущий сегмент. \en Current segment. 
    MbHomogeneous3D * h2;    ///< \ru Текущий сегмент. \en Current segment. 
    MbHomogeneous3D * h3;    ///< \ru Текущий сегмент. \en Current segment. 
    double          * wc;               ///< \ru Насчитанные значения весов (может быть ноль). \en Calculated values of points (can be null). 
    MbVector3D        rc[cdt_CountDer]; ///< \ru Насчитанные значения точек. \en Calculated values of points. 
    ptrdiff_t         leftIndex;        ///< \ru Левый индекс узлового вектора. \en Left index of knot vector. 
    double          * m_left;
    double          * m_right;
  public:
    MbNurbs3DAuxiliaryData();
    MbNurbs3DAuxiliaryData( const MbNurbs3DAuxiliaryData & init );
    virtual ~MbNurbs3DAuxiliaryData();
    void FreeMemory();
    bool CatchMemory(  ptrdiff_t, bool );
  }; // MbNurbs3DAuxiliaryData

  mutable CacheManager<MbNurbs3DAuxiliaryData> cache;

protected:
  MbNurbs3D();
  /** \brief \ru Конструктор.
             \en Constructor. \~    
    \details \ru Конструктор плоского сплайна пространстве.
             \en Constructor of planar spline in space. \~
  */
  MbNurbs3D( const MbNurbs &, const MbPlacement3D & );
  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по порядку, точкам, параметрам и признаку замкнутости.\n
             \en Constructor by order, points, parameters and an attribute of closedness.\n \~
    \param[in] deg        - \ru Порядок сплайна. 
                            Должен быть больше единицы. Не должен превышать количество контрольных точек.
                            \en A spline order. 
                            Must be greater than unity. Shouldn't exceed the count of control points. \~
    \param[in] cls        - \ru Признак замкнутости.
                            \en Closedness attribute. \~
    \param[in] points     - \ru Набор контрольных точек. 
                            Количество точек должно быть больше или равно двум.
                            \en Set of control points. 
                            Count of points must be greater than or equal to two. \~
    \param[in] weights    - \ru Набор весов для контрольных точек. 
                            Количество весов должно соответствовать количеству точек.
                            \en Set of weights for control points. 
                            Count of weights must be equal to count of points. \~
    \param[in] knots      - \ru Последовательность узловых параметров.
                            \en Sequence of knot parameters. \~ 
    
  */
  MbNurbs3D( ptrdiff_t deg, bool cls, const SArray<MbCartPoint3D> & points, 
             const SArray<double> * weights = NULL, const SArray<double> * knots = NULL );
  MbNurbs3D( const MbNurbs3D & );
public :
  virtual ~MbNurbs3D();

public :
  VISITING_CLASS( MbNurbs3D );

  /** \brief \ru Создать копию сплайна.
             \en Create copy of spline. \~
      \details \ru Создать копию сплайна.\n
               \en Create copy of spline.\n \~
  */
  static  MbNurbs3D * Create( const MbNurbs3D & );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
      \details \ru Создать сплайн и установить параметры сплайна.\n
               \en Create spline and set parameters of spline.\n \~
      \param[in] nurbs - \ru Двумерный сплайн.
                         \en The two-dimensional spline. \~ 
      \param[in] place - \ru Локальная система координат сплайна.
                         \en Local coordinate system of spline. \~
  */
  static  MbNurbs3D * Create( const MbNurbs & nurbs, const MbPlacement3D & place );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
      \details \ru Создать сплайн и установить параметры сплайна.\n
               \en Create spline and set parameters of spline.\n \~
      \param[in] degree - \ru Порядок сплайна.
                          \en A spline order. \~ 
      \param[in] points - \ru Набор контрольных точек.
                          \en Set of control points. \~
      \param[in] closed - \ru Признак замкнутости.
                          \en Closedness attribute. \~
      \param[in] weights - \ru Набор весов для контрольных точек.
                           \en Set of weights for control points. \~ 
  */
  static  MbNurbs3D * Create( ptrdiff_t degree, const SArray<MbCartPoint3D> & points, bool closed,
                              const SArray<double> * weights = NULL );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
      \details \ru Создать сплайн и установить параметры сплайна.\n
               \en Create spline and set parameters of spline.\n \~
      \param[in] degree - \ru Порядок сплайна.
                          \en A spline order. \~
      \param[in] closed - \ru Признак замкнутости.
                          \en Closedness attribute. \~
      \param[in] points - \ru Набор контрольных точек.
                          \en Set of control points. \~
      \param[in] knots - \ru Неубывающая последовательность узлов.
                         \en Nondecreasing sequence of knots. \~
              
  */
  static  MbNurbs3D * Create( ptrdiff_t degree, bool closed, const SArray<MbCartPoint3D> & points,
                              const SArray<double> & knots );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
      \details \ru Создать сплайн и установить параметры сплайна.\n
               \en Create spline and set parameters of spline.\n \~
      \param[in] initDegree - \ru Порядок сплайна.
                              \en A spline order. \~
      \param[in] initClosed - \ru Признак замкнутости.
                              \en Closedness attribute. \~
      \param[in] initPoints - \ru Набор контрольных точек.
                              \en Set of control points. \~
      \param[in] initWeights - \ru Набор весов для контрольных точек.
                               \en Set of weights for control points. \~ 
      \param[in] initKnots   - \ru Неубывающая последовательность узлов.
                               \en Nondecreasing sequence of knots. \~
      \param[in] initForm    - \ru Тип построения.
                               \en Type of construction. \~
              
  */
  template <class PointsVector, class DoubleVector>
  static  MbNurbs3D * Create( ptrdiff_t initDegree, bool initClosed, const PointsVector & initPoints,
                              const DoubleVector & initWeights, const DoubleVector & initKnots,
                              MbeNurbsCurveForm initForm = ncf_Unspecified )
  {
    MbNurbs3D * resNurbs = new MbNurbs3D;
    if ( !resNurbs->Init( initDegree, initClosed, initPoints, initWeights, initKnots, initForm ) )
      ::DeleteItem( resNurbs );
    return resNurbs;
  }
  /** \brief \ru Создать сплайн.
              \en Create spline. \~
      \details \ru Сплайн, проходящий через заданные точки при заданных параметрах.\n
        В случае замкнутости нужно передавать массив с совпадением первой и последней точек.\n
                \en Spline passing through the given points at the given parameters.\n
        In case of closedness it is necessary to pass the array with coincidence of the first and the last points.\n \~
      \param[in] degree  - \ru Порядок сплайна.
                            \en A spline order. \~
      \param[in] cls     - \ru Признак замкнутости.
                            \en Closedness attribute. \~
      \param[in] points  - \ru Набор точек, через которые проходит сплайн.
                            \en Set of points which the spline passes through. \~
      \param[in] params  - \ru Последовательность узловых параметров.
                            \en Sequence of knot parameters. \~
      \param[in] aKnots  - \ru Неубывающая последовательность узлов.
                            \en Nondecreasing sequence of knots. \~
  */
  static  MbNurbs3D * CreateThrough( ptrdiff_t degree, bool cls, const SArray<MbCartPoint3D> & points,
                                     const SArray<double> & params, SArray<double> * aKnots = NULL ); 
  /** \brief \ru Заполнить NURBS по данным parasolid.
             \en Fill NURBS by parasolid data. \~
      \details \ru Заполнить NURBS по данным parasolid.\n
               \en Fill NURBS by parasolid data.\n \~
      \param[in] degree     - \ru Степень сплайна.
                              \en Order of spline. \~
      \param[in] closed     - \ru Признак замкнутости.
                              \en Closedness attribute. \~
      \param[in] rational   - \ru Является ли кривая рациональной. Если true - строится NURBS, false - кривая Безье.
                              \en Whether the curve is rational. if true - NURBS is created, false - Bezier curve. \~
      \param[in] count      - \ru Количество контрольных точек.
                              \en Count of control points. \~
      \param[in] verts      - \ru Массив координат точек. Если сплайн рациональный, четвертая координата - вес точки.
                              \en An array of coordinates of points. If spline is rational, then the fourth coordinate is the weight of a point. \~ 
      \param[in] vertsCount - \ru Количество элементов в массиве verts.
                              \en Count of elements in 'verts' array. \~
      \param[in] mul        - \ru Массив с данными о кратности каждого узла.
                              \en Array with multiplicity of each knot. \~
      \param[in] mulCount   - \ru Количество элементов в массиве mul.
                              \en Count of elements in 'mul' array. \~
      \param[in] knots      - \ru Массив со значениями параметров в узлах. Каждое значение представлено один раз. 
                              Информация о кратности узла лежит в элементе массива mul с тем же номером.
                              \en Array with values of parameters at knots. Each value is presented only once. 
                              Information about knot multiplicity is in the element of 'mul' array with the same index. \~
      \param[in] knotsCount - \ru Количество элементов в массиве knots.
                              \en Count of elements in 'knots' array. \~
      \param[in] scl        - \ru Коэффициент масштабирования.
                              \en Scale factor. \~
  */
  static  MbNurbs3D * CreateParasolid( ptrdiff_t degree, bool closed, bool rational, ptrdiff_t count,
                                       const CcArray<double> & verts, ptrdiff_t vertsCount,
                                       const CcArray<ptrdiff_t> & mul, ptrdiff_t mulCount,
                                       const CcArray<double> & knots, ptrdiff_t knotsCount, 
                                       double scl );

public:
          /// \ru Установить параметры сплайна. \en Set parameters of the spline. 
          void        Init( const MbNurbs3D & );
          void        Init( const MbNurbs &, const MbPlacement3D & );
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Установить параметры сплайна.\n
                       \en Set parameters of the spline.\n \~
              \param[in] degree      - \ru Порядок сплайна.
                                       \en A spline order. \~ 
              \param[in] points      - \ru Набор контрольных точек.
                                       \en Set of control points. \~
              \param[in] weights     - \ru Набор весов для контрольных точек.
                                       \en Set of weights for control points. \~ 
              \param[in] closed      - \ru Признак замкнутости.
                                       \en Closedness attribute. \~
          */
          bool        Init( ptrdiff_t degree, const SArray<MbCartPoint3D> & points, bool closed,
                            const SArray<double> * weights = NULL );
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Установить параметры сплайна.\n
                       \en Set parameters of the spline.\n \~
              \param[in] degree      - \ru Порядок сплайна.
                                       \en A spline order. \~
              \param[in] closed      - \ru Признак замкнутости.
                                       \en Closedness attribute. \~
              \param[in] points      - \ru Набор контрольных точек.
                                       \en Set of control points. \~
              \param[in] knots       - \ru Неубывающая последовательность узлов.
                                       \en Nondecreasing sequence of knots. \~
              
          */
          bool        Init( ptrdiff_t degree, bool closed, const SArray<MbCartPoint3D> & points,
                            const SArray<double> & knots );
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Установить параметры сплайна.\n
                       \en Set parameters of the spline.\n \~
              \param[in] degree      - \ru Порядок сплайна.
                                       \en A spline order. \~
              \param[in] closed      - \ru Признак замкнутости.
                                       \en Closedness attribute. \~
              \param[in] points      - \ru Набор контрольных точек.
                                       \en Set of control points. \~
              \param[in] weights     - \ru Набор весов для контрольных точек.
                                       \en Set of weights for control points. \~ 
              \param[in] knots       - \ru Неубывающая последовательность узлов.
                                       \en Nondecreasing sequence of knots. \~
              \param[in] initForm    - \ru Тип построения.
                                       \en Type of construction. \~
              
          */
          template <class PointsVector, class DoubleVector>
          bool        Init( ptrdiff_t initDegree, bool initClosed, const PointsVector & initPoints,
                            const DoubleVector & initWeights, const DoubleVector & initKnots,
                            MbeNurbsCurveForm initForm = ncf_Unspecified )
          {
            bool bRes = ::IsValidNurbsParamsExt( initDegree, initClosed, initPoints, &initWeights, &initKnots );

            if ( bRes ) {
              Refresh(); // Must come first, since frees allocated memory

              pointList = initPoints;
              uppIndex = (ptrdiff_t)pointList.size() - 1;
              closed = initClosed;
              form = initForm;
              degree = initDegree;
              uppKnotsIndex = (ptrdiff_t)initKnots.size() - 1;
              weights = initWeights;
              knots = initKnots;

              SetClamped();
            }
            else if ( ::IsValidNurbsParams( initDegree, initClosed, initPoints.size(), initWeights.size() ) ) {
              // Lets try to redefine knots vector (BUG_42356)
              Refresh(); // Must come first, since frees allocated memory
              pointList = initPoints;
              uppIndex = (ptrdiff_t)pointList.size() - 1;
              closed = initClosed;
              form = ncf_Unspecified;
              degree = initDegree;
              weights = initWeights;

              DefineKnotsVector();
              C3D_ASSERT_UNCONDITIONAL( false ); // Wrong constructor use
                                     // Valid variants:
                                     // 1. Really, result is false
                                     // 2. The result should have 3 positions,
                                     // 3. Initial knots should be analyzed and corrected
              bRes = true; // Not been deleted recurring point for a closed curve
            }

            return bRes;
          }
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Установить параметры сплайна.\n
                       \en Set parameters of the spline.\n \~
              \param[in] degree      - \ru Порядок сплайна.
                                       \en A spline order. \~
              \param[in] points      - \ru Набор контрольных точек.
                                       \en Set of control points. \~
              \param[in] weights     - \ru Набор весов для контрольных точек.
                                       \en Set of weights for control points. \~ 
              \param[in] begData     - \ru Параметр сопряжения в начальной точке сплайна.
                                       \en Parameter of conjugation at the start point of the spline. \~
              \param[in] endData     - \ru Параметр сопряжения в конечной точке сплайна.
                                       \en Parameter of conjugation at the end point of the spline. \~
          */
          bool        Init( ptrdiff_t degree, const SArray<MbCartPoint3D> & points, const SArray<double> & weights,
                            MbPntMatingData<MbVector3D> & begData, 
                            MbPntMatingData<MbVector3D> & endData );
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Установить параметры сплайна.\n
                       \en Set parameters of the spline.\n \~
              \param[in] degree      - \ru Порядок сплайна.
                                       \en A spline order. \~
              \param[in] closed      - \ru Признак замкнутости.
                                       \en Closedness attribute. \~
              \param[in] points      - \ru Набор контрольных точек.
                                       \en Set of control points. \~
              \param[in] knots       - \ru Неубывающая последовательность узлов.
                                       \en Nondecreasing sequence of knots. \~
              \param[in] nPoints     - \ru Число контрольных точек.
                                       \en The number of control points. \~
              \param[in] endData     - \ru Количество узлов.
                                       \en Count of knots. \~
          */
          bool        Init( ptrdiff_t degree, bool closed, const CcArray<double> & points,
                            const CcArray<double> & knots, ptrdiff_t nPoints, ptrdiff_t nKnots );
          /** \brief \ru Инициализация.
                     \en Initialization. \~
              \details \ru Сплайн, проходящий через заданные точки при заданных параметрах.\n
                В случае замкнутости нужно передавать массив с совпадением первой и последней точек.\n
                       \en Spline passing through the given points at the given parameters.\n
                In case of closedness it is necessary to pass the array with coincidence of the first and the last points.\n \~
              \param[in] degree  - \ru Порядок сплайна.
                                   \en A spline order. \~
              \param[in] cls     - \ru Признак замкнутости.
                                   \en Closedness attribute. \~
              \param[in] points  - \ru Набор точек, через которые проходит сплайн.
                                   \en Set of points which the spline passes through. \~
              \param[in] params  - \ru Последовательность узловых параметров.
                                   \en Sequence of knot parameters. \~
              \param[in] aKnots  - \ru Неубывающая последовательность узлов.
                                   \en Nondecreasing sequence of knots. \~
          */
          bool        InitThrough( ptrdiff_t degree, bool cls, const SArray<MbCartPoint3D> & points,
                                   const SArray<double> & params, SArray<double> * aKnots = NULL ); 
          /// \ru Установить тип формы. \en Set the type of shape. 
          void 	      SetFormType( MbeNurbsCurveForm f ) { form = f; }

  // \ru Общие функции математического объекта. \en The common functions of the mathematical object. 

  virtual MbeSpaceType  IsA()              const;  // \ru Тип элемента. \en A type of element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента. \en Create a copy of the element. 
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая копией данной кривой? \en Whether the curve is a duplicate of the current curve. 
  virtual bool        SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг. \en Move. 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
          void        GetControlPoints( SArray<MbCartPoint3D> & s ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.

  // \ru Общие функции кривой. \en Common functions of curve. 

  virtual double      GetTMin()    const; // \ru Вернуть минимальное значение параметра. \en Get the minimum value of parameter. 
  virtual double      GetTMax()    const; // \ru Вернуть максимальное значение параметра. \en Get the maximum value of parameter. 
  virtual bool        IsClosed()   const; // \ru Замкнутость кривой. \en A curve closedness. 
  virtual bool        IsPeriodic() const; // \ru Периодичность замкнутой кривой. \en Periodicity of a closed curve. 
  virtual bool        IsStraight() const; // \ru Прямолинейность кривой. \en Straightness of curve. 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void        PointOn   ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой. \en Point on the curve. 
  virtual void        FirstDer  ( double & t, MbVector3D & ) const;    // \ru Первая производная. \en The first derivative. 
  virtual void        SecondDer ( double & t, MbVector3D & ) const;    // \ru Вторая производная. \en The second derivative. 
  virtual void        ThirdDer  ( double & t, MbVector3D & ) const;    // \ru Третья производная по t. \en The third derivative with respect to t. 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;
  // \ru Вычислить значения производных для заданного параметра. \en Calculate derivatives of object for given parameter. \~
          void        Derivatives( double & t, bool ext, MbVector3D & fir, MbVector3D * sec, MbVector3D * thi ) const;

  virtual double      Step         ( double t, double sag    ) const; // \ru Вычисление шага аппроксимации. \en Calculation of step of approximation. 
  virtual double      DeviationStep( double t, double angle  ) const; // \ru Вычисление шага аппроксимации. \en Calculation of step of approximation. 

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS копию кривой. \en Construct a NURBS copy of a curve. 

  virtual MbCurve3D * TrimmBreak( double t1, double t2, int sense ) const;
          
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой \en Get the axis of the curve 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую). \en Get a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called for a two-dimensional curve) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Ближайшая проекция точки на кривую. \en The nearest projection of a point onto the curve. 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const;

  virtual void        Refresh(); // \ru Сбросить все временные данные. \en Reset all temporary data. 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление. \en Change the direction. 

  // \ru Определить, является ли кривая репараметризованно такой же. \en Determine whether a reparameterized curve is the same. 
  virtual bool        IsReparamSame( const MbCurve3D & curve, double & factor ) const;

  virtual bool        IsDegenerate ( double eps = METRIC_PRECISION ) const; // \ru Проверка вырожденности кривой. \en Check the curve degeneracy. 
          void        SetDegenerate();       // \ru Стать вырожденным. \en Became degenerate. 

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой. \en Creation of a trimmed curve. 
          /// \ru Усечение кривой. \en Trim the curve. 
          MbNurbs3D * Trimm( double t1, double t2, int sense ) const;

  // \ru Вычислить габарит кривой. \en Calculate bounding box of a curve. 
  virtual void        CalculateGabarit( MbCube & cube ) const;
  // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double      CalculateMetricLength() const;
  // \ru Сдвинуть параметр t на расстояние len. \en Move parameter t on the metric distance len. 
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                     VERSION version = Math::DefaultMathVersion() ) const; 
  // \ru Вычислить метрическую длину кривой. \en Calculate the metric length of a curve.
  virtual double      CalculateLength( double t1, double t2 ) const;

  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны.
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;

  // \ru Общие функции полигональной кривой. \en Common functions of the polygonal curve.
  virtual void        GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const; // \ru Выдать интервал влияния точки B-сплайна. \en Get the range of influence of a B-spline point. 

  virtual void        Rebuild(); // \ru Перестроить B-сплайн. \en Rebuild B-spline. 
  virtual void        SetClosed( bool cls ); // \ru Установить признак замкнутости. \en Set attribute of closedness. 

  virtual void        AddPoint   ( const MbCartPoint3D & ); // \ru Добавить точку в конец массива. \en Add a point to the end of the array. 
  virtual void        InsertPoint( ptrdiff_t index, const MbCartPoint3D & p ); // \ru Добавить точку. \en Add a point. 
  virtual void        InsertPoint( double t,  const MbCartPoint3D & p, double eps ); // \ru Добавить точку. \en Add a point. 
  virtual void        RemovePoint( ptrdiff_t index ); // \ru Удалить точку. \en Remove the point. 
  virtual void        RemovePoints(); // \ru Удалить все точки. \en Delete all points. 
  virtual bool        CheckParam ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const; // \ru Загнать параметр в область задания, получить локальный индексы и параметры. \en Drive parameter into the definition domain, get local indices and parameters. 
  virtual double      GetParam( ptrdiff_t i ) const; // \ru Выдать параметр для точки с заданным номером. \en Get parameter for a point with the given index. 
  virtual void        ResetTCalc() const;     // \ru Сбросить текущее значение параметра \en Reset the current value of the parameter 

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

  // \ru Функции B-сплайн кривой. \en Functions of B-spline curve. 
          /// \ru Выделить часть кривой. \en Extract a piece of a curve. 
          MbNurbs3D * Break( double t1, double t2 ) const;
          /// \ru Задать вес для вершины. \en Set weight for a control point. 
          void        SetWeight( ptrdiff_t pointNumber, double newWeight );
          /// \ru Добавить точку с весом. \en Add a point with weight. 
          void        AddPoint ( ptrdiff_t index, const MbCartPoint3D & pnt, double weight );

  // \ru Функции B-сплайна. \en Functions of B-spline. 
          /// \ru Добавление нового узла с заданной кратностью. \en Add a new knot with the given multiplicity. 
          void        InsertKnots     ( double & newKnot, ptrdiff_t multiplicity, double relEps = Math::paramEpsilon ); 
          /// \ru Добавление новых узлов равномерно в промежуток от idBegin до idBegin+1. \en Add new equally spaced knots into the range from idBegin to idBegin+1. 
          void        InsertKnotsInRegion( ptrdiff_t idBegin ); 

          /// \ru Удалить кратный внутренний узел id num раз, вернуть количество удалений, которое удалось сделать. \en Remove multiple internal 'id' knot 'num' times, return count of removals which were successfully made. 
          ptrdiff_t   RemoveKnot( ptrdiff_t id, ptrdiff_t num, double relEps = Math::paramEpsilon, double absEps = Math::lengthEpsilon );

          /// \ru Удалить узел id 1 раз, не проверяя точность изменения кривой. \en Remove knot 'id' once without checking the accuracy of the curve modification. 
          bool        RemoveKnotAlways( ptrdiff_t id );

          /// \ru Удалить все внутренние узлы, если это возможно. \en Remove all the internal knots if it is possible. 
          void        RemoveAllKnots( double relEps = Math::paramEpsilon, double absEps = Math::lengthEpsilon );
          /// \ru Преобразовать данный NURBS в форму кривой Безье. \en Transform current NURBS into Bezier curve. 
          bool        DecomposeCurve(); 

          /// \ru Увеличить порядок NURBS-кривой, не меняя ее геометрическую форму и парамеризацию. \en Increase the order of a NURBS-curve without changing its geometric shape and parameterization. 
          bool        RaiseDegree    ( ptrdiff_t, double relEps = Math::paramEpsilon );
          /// \ru Уменьшить порядок кривой на 1. \en Decrease the order of a curve by 1. 
          bool        ReductionDegree( double relEps = Math::paramEpsilon );

          /// \ru Получить кратность узла с заданным номером. \en Get multiplicity of a knot with a given index. 
          ptrdiff_t   KnotMultiplicity( ptrdiff_t knotIndex ) const;
          /// \ru Определение базисного узлового вектора. \en Definition of the basis knot vector. 
          void        DefineKnotsVector();
          /// \ru Переопределение базисного узлового вектора из Close в Open. \en Redefine the basis knot vector from Close to Open. 
          bool        OpenKnotsVector  ();
          /// \ru Переопределение базисного узлового вектора из Open в Close. \en Redefine the basis knot vector from Open to Close. 
          bool        CloseKnotsVector ();

          /// \ru Установить область изменения параметра. \en Set the range of parameter. 
          bool        SetLimitParam   ( double pmin, double pmax );
          /// \ru Добавить кривую в конец. \en Add a curve to the end. 
          void        AddCurve        ( MbNurbs3D &, bool bmerge = true );
          /// \ru Добавить кривые в конец. \en Add curves to the end. 
          void        AddCurves       ( const RPArray<MbNurbs3D> & );

          /// \ru Репераметризовать кривую в соответствии с длиной в случае, если кривая получена из набора кривых Безье. \en Reparameterize a curve according to the length if the curve is obtained from a set of Bezier curves. 
          bool        ReparamCurveInBezierForm();

          /// \ru Получить форму В-сплайна. \en Get the form of B-spline. 
          MbeNurbsCurveForm  GetFormType() const { return form; }
          /// \ru Получить порядок В-сплайна. \en Get the order of B-spline. 
          ptrdiff_t   GetDegree() const { return degree; }
          /// \ru Вернуть признак рациональности, но не регулярности кривой. \en Get the attribute of rationality, but not regularity of a curve. 
          bool        IsRational() const;

          size_t      GetWeightsCount() const { return weights.Count(); }
          void        GetWeights(       SArray<double> & wts ) const { wts = weights; }
          double      GetWeight( size_t ind ) const { return weights[ind]; }
          double  &   SetWeight( size_t ind )       { return weights[ind]; }

          size_t      GetKnotsCount()   const { return knots.Count(); }
          void        GetKnots( SArray<double> & knts ) const { knts = knots; }
          double      GetKnot  ( size_t ind ) const { return knots[ind]; }
          double &    SetKnot  ( size_t ind )       { return knots[ind]; }
          ptrdiff_t   GetUppKnotsIndex()  const { return uppKnotsIndex; }

  // \ru Функции только 3D кривой. \en Functions of 3D curve only. 

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of a curve. 

  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях с поверхностями. \en Count of subdivisions for pass in operations with surfaces. 

          /// \ru Установить сопряжение на конце. \en Set conjugation at the end. 
          bool        AttachG( MbPntMatingData<MbVector3D> & connectData, bool beg, bool isWrongAttachG1_K12 = false );
          
          /// \ru Создать кубический NURBS по точкам, через которые он проходит, и параметрам сопряжения. \en Create cubic NURBS by parameters of conjugation and points which it passes through. 
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> &, MbeSplineParamType spType,
                                    const MbPntMatingData<MbVector3D> & begData, 
                                    const MbPntMatingData<MbVector3D> & endData,
                                    MbeSplineCreateType useInitThrough );
          /// \ru Создать кубический NURBS по интерполяционным точкам и данным сопряжения в каждой точке. \en Create cubic NURBS by interpolation points and data of conjugation at each point. 
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> &, MbeSplineParamType spType,
                                    bool closed,
                                    RPArray< MbPntMatingData<MbVector3D> > &,
                                    MbeSplineCreateType useInitThrough );
          /// \ru Создать кубический NURBS по интерполяционным точкам, их параметрам и данным сопряжения в каждой точке. \en Create cubic NURBS by interpolation points, parameters and data of conjugation at each point. 
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> &, const SArray<double> &,
                                    bool closed,
                                    RPArray< MbPntMatingData<MbVector3D> > &,
                                    MbeSplineCreateType useInitThrough );
          /// \ru Создать кубический NURBS по точкам, через которые он проходит, и признаку замкнутости. \en Create a cubic NURBS by the attribute of closedness and points which it passes through. 
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> &, bool cls, MbeSplineParamType spType,
                                    MbeSplineCreateType useInitThrough = sct_Version2 );
          /** \brief \ru Интерполяция.
                     \en Interpolation. \~
            \details \ru Создать незамкнутый сплайн четвертого порядка по точкам, параметрам и признаку замкнутости.\n
                         Используется граничное условие отсутствия узла.\n
                     \en Create an open spline of fourth order by points, parameters and the attribute of closedness.\n
                         Used boundary condition of knot absence.\n \~
          */
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> & points, const SArray<double> & params, bool cls, 
                                    MbeSplineCreateType useInitThrough = sct_Version2 );
          /** \brief \ru Интерполяция.
                     \en Interpolation. \~
            \details \ru Создать незамкнутый сплайн четвертого порядка по точкам, параметрам и признаку замкнутости.\n
                         Используется граничное условие отсутствия узла.
                     \en Create an open spline of fourth order by points, parameters and the attribute of closedness.\n
                        Used boundary condition of knot absence. \~
          */
  static  MbNurbs3D * CreateNURBS4( const SArray<double> & weights, const SArray<MbCartPoint3D> & points,
                                    SArray<double> & params, bool cls );
          /** \brief \ru Интерполяция.
                     \en Interpolation. \~
              \details \ru Создать сплайн четвертого порядка по точкам, параметрам и признаку замкнутости
                с граничными условиями - заданными векторами первых или вторых производных.\n
                Имеет 2 кратных внутренних узла, принадлежит классу дифференцируемых ( но не дважды дифференцируемых ) функций..
                       \en Create a spline of the fourth order by points, parameters and the attribute of closedness
                with boundary conditions - given vectors of the first or the second derivatives.\n
                Has 2 multiple internal knots, belongs to the class of differentiable (but not twice differentiable) functions. \~
                \param[in] bfstS  - \ru Если true, то начальное граничное условие - вектор первой производной, иначе - вектор второй производной.
                                    \en If true, then start boundary condition is the vector of the first derivative, otherwise - the vector of the second derivative. \~
                \param[in] bfstN  - \ru Если true, то конечное граничное условие - вектор первой производной, иначе - вектор второй производной.
                                    \en If true, then end boundary condition - vector of first derivative, otherwise - vector of second derivative. \~
          */
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> &, const SArray<double> &,
                                    const MbVector3D &, const MbVector3D &, bool cls,
                                    bool bfstS = true, bool bfstN = true );
          /** \brief \ru Интерполяция.
                     \en Interpolation. \~
            \details \ru Создать сплайн четвертого порядка по точкам, производным, параметрам и признаку замкнутости.\n
                         Имеет 2 кратных внутренних узла, принадлежит классу дифференцируемых ( но не дважды дифференцируемых ) функций.
                     \en Create a spline of the fourth order by points, derivatives, parameters and the attribute of closedness.\n
                         Has 2 multiple internal knots, belongs to the class of differentiable (but not twice differentiable) functions. \~
          */
  static  MbNurbs3D * CreateNURBS4( const SArray<MbCartPoint3D> & points, const SArray<MbVector3D> & vectors,
                                    const SArray<double> & params, bool cls );
          /// \ru Создать сплайн четвертого порядка c учетом изломов кривой \en Create a spline of the fourth order taking breaks of curve into account 
  static  MbNurbs3D * CreateNURBS4WithBreak( const SArray<MbCartPoint3D> &, const SArray<MbVector3D> &,
                                             const SArray<double> &, bool cls );
         /** \brief \ru Интерполяция.
                    \en Interpolation. \~
              \details \ru Создать сплайн четвертого порядка по составному сплайну Безье четвертого порядка.\n
                Внимание! Парамеризация отлична от параметризации исходной кривой Безье.
                       \en Create a spline of the fourth order by a composite Bezier spline of the fourth order.\n
                Attention! Parameterization is different from the parameterization of the source Bezier curve. \~
          */
  static  MbNurbs3D * CreateNURBS4( const MbBezier3D & );
          /** \brief \ru Разбить кривую.
                     \en Split the curve. \~
              \details \ru Разбить недифференцируемую NURBS-кривую четвертой степени в трижды кратном внутреннем узле.\n
                Если внутренних трижды кратных узлов не существует, то в массив заносится копия кривой.\n
                Если bline = true, то проверить вырожденность в прямую, если прямая - преобразовать в прямую.
                       \en Split the non-differentiable NURBS-curve of the fourth degree at an internal knot with multiplicity of three.\n
                If there is no internal knots with multiplicity of three, then a copy of the curve is added to the array.\n
                If bline = true, then check the curve for degeneration into a line, if it is a line - transform to a line. \~
          */
          bool        BreakC0NURBS4( RPArray<MbCurve3D> &, bool bline = true ) const;

          /// \ru Расширить незамкнутую NURBS-кривую по касательным. \en Extend an open NURBS-curve by tangents. 
          bool        ExtendNurbs( double, double, bool bmerge = false );
          
          /// \ru Преобразовать узловой вектор в зажатый (если кривая замкнута и clm = false) или разжатый (если кривая не замкнута и clm = true). \en Transform knot vector to a clamped one (if the curve is closed and clm = false) or unclamped one (if the curve is open and clm = true). 
          bool        UnClamped( bool clm, bool savePointsCount = false );
          /// \ru Преобразовать кривую в коническое сечение, если это возможно. \en Transform a curve into a conic section if it is possible. 
          MbCurve3D * ConvertToConic();
          /// \ru Разбить NURBS-кривую в местах, где кривая не дифференцируема. Если кривая дифференцируема, то добавляется копия кривой. \en Split a NURBS-curve at places where the curve is non-differentiable. If the curve is differentiable, then the curve copy is added. 
          bool        BreakC0( RPArray<MbCurve3D> & );

          /** \brief \ru Замкнуть кривую.
                     \en Make the curve closed. \~
              \details \ru Замкнуть фактически замкнутую кривую.\n
                То есть если первая и последняя точки кривой совпадают, но она реализована как незамкнутая,
                то одна из совпадающих точек убирается и кривая делается замкнутой.
                       \en Make the actually closed curve closed.\n
                That is, if the first and the last points of curve are coincident, but curve was implemented as open,
                then one of the coincident points is took away and the curve becomes closed. \~
          */
          void        FixClosedNurbs();
          /// \ru Получить значение параметра, соответствующего узловой точке с номером num. \en Get value of the parameter corresponding to a knot point with 'num' index. 
          double      GetBSplineParameter ( size_t num ) const;

private:
          bool        CatchMemory( MbNurbs3DAuxiliaryData * cache ) const; // \ru Выделить память. \en Allocate memory. 
          void        FreeMemory ( MbNurbs3DAuxiliaryData * cache ) const;  // \ru Освободить память. \en Free memory. 
          void        VerifyParam( double & t ) const; // \ru Загнать параметр t в параметрическую область кривой. \en Parameter set in the curve region. 
          void        CalculateSegment( double & t, MbNurbs3DAuxiliaryData * cache ) const;
          void        CalculateSpline( ptrdiff_t n, MbNurbs3DAuxiliaryData * cache ) const;
          void        CalculateSplineWeight( double & t, ptrdiff_t n, MbNurbs3DAuxiliaryData * cache ) const;
          bool        InitSegments( MbNurbs3DAuxiliaryData * cache ) const;

          // \ru Вычислить значения производных для заданного параметра, используя заданный кэш. \en Calculate derivatives of object for given parameter using defined cache. \~
          void        DerivativesEx( double & t, bool ext, MbVector3D & fir, MbVector3D * sec, MbVector3D * thi, MbNurbs3DAuxiliaryData * ucache ) const;

          void        SetClamped(); // \ru Делаем зажатый узловой вектор. \en Set clamped knots vector. 

          void        ResetMainCache() const; // \ru Очистить кэш главного потока. Использует блокировку кэша. \en Reset main thread cache. Use cache lock.

          MbNurbs3D * NurbsPlus( double tin, double tax ) const;          

          // \ru BEG: Внутренние функции CreateNURBS4 по двум сопряжениям. \en BEG: Internal CreateNURBS4 functions by two conjugations. 
          // \ru Создать интерполяционный кубический NURBS, удовлетворяющий условиям сопряжения по касательным. \en Create an interpolation cubic NURBS meeting conditions of conjugation by tangents. 
          bool        AttachG1_NURBS4( const SArray<MbCartPoint3D> &, const SArray<double> & params, 
                                       const MbPntMatingData<MbVector3D> & begData, 
                                       const MbPntMatingData<MbVector3D> & endData ); 
          // \ru Создать интерполяционный кубический NURBS, удовлетворяющий условиям сопряжения со вторым порядком гладкости. \en Create an interpolation cubic NURBS meeting conditions of conjugation with the second order of smoothness. 
          bool        AttachG2_NURBS4( const SArray<MbCartPoint3D> &, const SArray<double> & params, 
                                       const MbPntMatingData<MbVector3D> & begData, 
                                       const MbPntMatingData<MbVector3D> & endData ); 
          // \ru END: Внутренние функции CreateNURBS4 по двум сопряжениям. \en END: Internal CreateNURBS4 functions by two conjugations. 

          // \ru BEG: Внутренние функции CreateNURBS4 по массиву сопряжений. \en BEG: Internal CreateNURBS4 functions by an array of conjugations. 
          // \ru Построение интерполяционного NURBS4 с возможными заданными управляющими параметрами. \en Create an interpolation NURBS4 with possibly given driving parameters. 
          bool        CreateC2_NURBS4( const SArray<MbCartPoint3D> &, MbeSplineParamType spType, 
                                       RPArray< MbPntMatingData<MbVector3D> > &,
                                       const SArray<double> &,
                                       MbeSplineCreateType useInitThrough,
                                       bool cls = false );
          // \ru Построение интерполяционного незамкнутого NURBS4 в общем случае \en Create an interpolation open NURBS4 in general case 
          // \ru С возможными заданными управляющими параметрами в средних точках. \en With possibly given driving parameters at middle points. 
          // \ru Считаем, что данные для сопряжений заданы корректно. Этот факт проверяется до запуска функции. \en Consider that the given data for conjugations is correct. This fact is checked before calling the function. 
  static  MbNurbs3D * CreateC2Nurbs4Common( const SArray<MbCartPoint3D> & arPoints, 
                                            RPArray< MbPntMatingData<MbVector3D> > & inferredData,
                                            const SArray<double> & arParams,
                                            const SArray<double> & arKnots,
                                            ptrdiff_t addCount,
                                            bool cls,
                                            MbeSplineCreateType useInitThrough,
                                            size_t deg = 4 );
          // \ru END: Внутренние функции CreateNURBS4 по массиву сопряжений. \en END: Internal CreateNURBS4 functions by an array of conjugations. 
          
          // \ru Расчет весовых функций и их первых производных. \en Calculation of weight functions and their first derivatives. 
          ptrdiff_t   WeightFunctions ( double & x, CcArray<double> & m ) const;
          /// \ru Вычисление шага аппроксимации. \en Calculation of a step of approximation. 
          double      StepD( double t, double sag, bool checkAngle, double angle = Math::lowRenderAng, MbNurbs3DAuxiliaryData * cache = NULL ) const;
          // \ru Вычисление шага аппроксимации сплайна второго порядка. \en Calculation of approximation step of second order spline. 
          double      PolylineStep( double t, bool half, MbNurbs3DAuxiliaryData * cache ) const;
          // \ru Уточнить проекцию \en Specify projection.
          double      SpecifyProjection( const MbCartPoint3D & pnt, double t, bool ext ) const;

          void        operator = ( const MbNurbs3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbNurbs3D )
};

IMPL_PERSISTENT_OPS( MbNurbs3D )


#endif // __CUR_NURBS3D_H
