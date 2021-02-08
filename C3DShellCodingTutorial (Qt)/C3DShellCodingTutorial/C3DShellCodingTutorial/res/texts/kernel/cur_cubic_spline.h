////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кубический сплайн в двумерном пространстве.
         \en Cubic spline in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CUBIC_SPLINE_H
#define __CUR_CUBIC_SPLINE_H


#include <cur_polycurve.h>


class MbCurveIntoNurbsInfo;
class MbRegDuplicate;
class MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Кубический сплайн в двумерном пространстве.
           \en Cubic spline in two-dimensional space. \~
  \details \ru Кубический сплайн определяется контрольными точками pointList и значениями параметра сплайна tList в контрольных точках. 
    По контрольным точкам сплайна и значениям параметра в контрольных точках рассчитываются 
    вторые производные сплайна vectorList в контрольных точках.
    Для не замкнутой кривой множества pointList, vectorList и tList должны содержать одинаковое количество элементов.
    Для замкнутой кривой количество элементов tList должно быть на единицу больше, чем количество элементов pointList и vectorList. 
    Кубический сплайн проходит через свои контрольные точки при значениях параметра из множества tList.
    На каждом участке между двумя соседними контрольными точками сплайн описывается кубическим полиномом. 
    Кубические полиномы гладко стыкуются в контрольных точках и имеют в них непрерывные вторые производные. 
    Вторые производные между двумя соседними контрольными точками сплайна изменяются по линейному закону.
           \en Cubic spline is defined by control points "pointList" and spline parameter values in the control points. 
    By control points of the spline and parameter values in the control points there are calculated 
    second derivatives of the spline vectorList in the control points.
    For unclosed curve the sets pointList, vectorList and tList must contain the same number of elements.
    For closed curve the number of elements tList must be one greater than the number of elements of pointList and vectorList. 
    Cubic spline passes through its control points for parameter values from the set tList.
    On each region between two neighboring control points the spline is described by the cubic polynomial. 
    Cubic polynomials are smoothly connected at the control points and they have continuous second derivatives at these points. 
    The second derivatives between the two neighboring control points of spline are changed linearly. \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbCubicSpline : public MbPolyCurve {
protected :
  SArray<MbVector> vectorList;   ///< \ru Множество вторых производных в контрольных точках. \en Set of second derivatives at the control points. 
  SArray<double>   tList;        ///< \ru Множество параметров в контрольных точках. \en Set of parameters at the control points. 
  ptrdiff_t        splinesCount; ///< \ru Максимальное значение индекса в множестве параметров tList. \en Maximal value of index in the parameters tList. 

protected :
  MbCubicSpline(); ///< \ru Конструктор по умолчанию. \en Constructor by default. 
  MbCubicSpline( const MbCubicSpline & other ); ///< \ru Дублирующий конструктор. \en Duplicating constructor. 
  /// \ru Конструктор по заданной кривой. \en Constructor by a given curve. 
  MbCubicSpline( const MbCurve & );
 
  /** \brief \ru Конструктор.
             \en Constructor. \~
    \details \ru Конструктор по точкам и признаку замкнутости.
             \en Constructor by points and an attribute of closedness. \~
    \param[in] points - \ru Набор узловых точек.
                        В случае незамкнутой кривой количество точек должно быть не меньше двух,
                        в случае замкнутой кривой - не меньше трех.
                        Если количество точек не соответствует требованиям - поведение кривой неопределено.
                        \en A knot set.
                        In the case of unclosed curve the number of points must be not less than two,
                        in the case of closed curve - not less than three.
                        If the number of points does not comply with the requirements - curve behavior is undefined. \~
    \param[in] cls    - \ru Признак замкнутости кривой.
                        \en An attribute of curve closedness. \~ 
  */
  MbCubicSpline( const SArray <MbCartPoint> & points, bool cls ); 

  /// \ru Конструктор по точкам, вторым производным и признаку замкнутости. \en Constructor by points, second derivatives and closedness attribute. 
  MbCubicSpline( const SArray <MbCartPoint> & points,
                 const SArray <MbVector   > & seconds, bool cls ); 
  /// \ru Конструктор по точкам, параметрам и признаку замкнутости. \en Constructor by points, parameters and closedness attribute.   
  MbCubicSpline( const SArray <MbCartPoint> & points,
                 const SArray <double     > & params, bool cls ); 
  /// \ru Конструктор по точкам, вторым производным, параметрам и признаку замкнутости. \en Constructor by points, second derivatives, parameters and closedness attribute. 
  MbCubicSpline( const SArray <MbCartPoint> & points,
                 const SArray <MbVector   > & seconds,
                 const SArray <double     > & params, bool cls );
public :
  virtual ~MbCubicSpline(); ///< \ru Деструктор. \en Destructor. 

public :
  /** \brief \ru Создать копию сплайна.
             \en Create copy of spline. \~
    \details \ru Создать копию сплайна.\n
             \en Create copy of spline.\n \~
  */
  static MbCubicSpline * Create( const MbCubicSpline & other );
  /** \brief \ru Создать сплайн gj rhb.
             \en Create spline. \~
    \details \ru Создать сплайн по заданной кривой и установить параметры сплайна.\n
             \en Create spline by a given curve and set parameters of spline.\n \~
    \param[in] curve - \ru Заданная кривая.
                       \en Given curve. \~
  */
  static MbCubicSpline * Create( const MbCurve & curve );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points - \ru Набор контрольных точек.
                        \en Set of control points. \~
    \param[in] cls    - \ru Признак замкнутости.
                        \en A closedness attribute. \~
  */
  static MbCubicSpline * Create( const SArray<MbCartPoint> & points, bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points  - \ru Набор контрольных точек.
                         \en Set of control points. \~
    \param[in] seconds - \ru Набор вторых производных в контрольных точках.
                         \en Set of second derivatives at the control points. \~
    \param[in] cls     - \ru Признак замкнутости.
                         \en A closedness attribute. \~
  */
  static MbCubicSpline * Create( const SArray<MbCartPoint> & points,
                                 const SArray<MbVector>    & seconds, bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points  - \ru Набор контрольных точек.
                         \en Set of control points. \~
    \param[in] params  - \ru Набор параметров в контрольных точках.
                         \en Set of parameters at the control points. \~
    \param[in] cls     - \ru Признак замкнутости.
                         \en A closedness attribute. \~
  */
  static MbCubicSpline * Create( const SArray<MbCartPoint> & points,
                                 const SArray<double>      & params, bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points  - \ru Набор контрольных точек.
                         \en Set of control points. \~
    \param[in] seconds - \ru Набор вторых производных в контрольных точках.
                         \en Set of second derivatives at the control points. \~
    \param[in] params  - \ru Набор параметров в контрольных точках.
                         \en Set of parameters at the control points. \~
    \param[in] cls     - \ru Признак замкнутости.
                         \en A closedness attribute. \~
  */
  static MbCubicSpline * Create( const SArray<MbCartPoint> & points,
                                 const SArray<MbVector>    & seconds,
                                 const SArray<double>      & params, bool cls );

public :
  VISITING_CLASS( MbCubicSpline ); 

  /** \ru \name Функции инициализации сплайна.
      \en \name Spline initialization functions.
      \{ */  
          /// \ru Инициализатор по заданной кривой. \en Initializer by a given curve. 
          bool        Init( const MbCurve & );
          /// \ru Инициализатор по точкам и признаку замкнутости. \en Initializer by points and an attribute of closedness. 
          bool        Init( const SArray <MbCartPoint> &, bool );
          /// \ru Инициализатор по точкам, вторым производным и признаку замкнутости. \en Initializer by points, second derivatives and closedness attribute. 
          bool        Init( const SArray <MbCartPoint> &,
                            const SArray <MbVector   > &, bool );
          /// \ru Инициализатор по точкам, параметрам и признаку замкнутости. \en Initializer by points, parameters and closedness attribute. 
          bool        Init( const SArray <MbCartPoint> &,
                            const SArray <double     > &, bool );
          /// \ru Инициализатор по точкам, вторым производным, параметрам и признаку замкнутости. \en Initializer by points, second derivatives, parameters and closedness attribute. 
          bool        Init( const SArray <MbCartPoint> &,
                            const SArray <MbVector   > &,
                            const SArray <double     > &, bool );
          /// \ru Дублирующий инициализатор. \en Duplicating initializer. 
          void        InitC( const MbCubicSpline & ); 
  /** \} */

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbePlaneType  IsA    () const; // \ru Тип элемента \en Type of element 
  virtual bool        SetEqual ( const MbPlaneItem & ); // \ru Сделать элементы равными \en Make equal elements 
  virtual	bool        IsSame   ( const MbPlaneItem &, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой \en Whether the curve "curve" is a copy of a given curve 
  virtual void        Transform( const MbMatrix &, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbCartPoint &, const MbDirection &, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions describing the domain of a curve.
      \{ */
  virtual double      GetTMin  () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax  () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
            Исключение составляет MbLine (прямая).
      \en \name Functions for working in the domain of a curve. 
            Functions: PointOn, FirstDer, SecondDer, ThirdDer,... correct the parameter
            when it is out of domain bounds.
            The exception is MbLine (line).
      \{ */
  virtual void        PointOn  ( double &, MbCartPoint & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double &, MbVector    & ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double &, MbVector    & ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double &, MbVector    & ) const; // \ru Третья производная \en Third derivative 
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;

          // \ru четвертая производная \en Fourth derivative 
          void        FourDer        ( double &, MbVector & ) const; ///< \ru Вычислить четвертую производную. \en Calculate the fourth derivative. 
          void        PointOnLine    ( double &, MbCartPoint & ); ///< \ru Вычислить точку на кривой при линейной аппроксимации. \en Calculate a point on the curve with a linear approximation. 
  /** \} */

  /** \ru \name Функции движения по кривой
      \en \name Functions of the motion along the curve
    \{ */
  virtual double      Step         ( double t, double sag   ) const; // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of approximation step with consideration of curvature radius 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации с учетом угла отклонения \en Calculation of approximation step with consideration of deviation angle 
  /** \} */

  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */
  virtual void        Rebuild  (); // \ru Пересчитать Безье кривую \en Recalculate Bezier curve 
  virtual void        SetClosed( bool cls ); // \ru Установить признак замкнутости. \en Set attribute of closedness. 
  virtual void        Inverse  ( MbRegTransform * iReg = NULL ); // \ru Изменение направления кривой на противоположное \en Change to the opposite direction of a curve 

  /** \brief \ru Построить усеченную кривую.
             \en Construct a trimmed curve. \~
    \details \ru Строит усеченную кривую, начало которой соответствует точке с параметром t1 и конец - точке с параметром t2. 
      Можно изменить направление полученной кривой относительно исходной с помощью параметра sense.
             \en Constructs a trimmed curve, a start point of which corresponds to a point with parameter t1 and an end point corresponds to a point with parameter t2. 
      Direction of the constructed curve relative to the initial curve may be changed by the parameter 'sense'. \~ 
    \param[in] t1 - \ru Параметр, соответствующий началу усеченной кривой.
                    \en Parameter corresponding to start of a trimmed curve. \~
    \param[in] t2 - \ru Параметр, соответствующий концу усеченной кривой.
                    \en Parameter corresponding to end of a trimmed curve. \~
    \param[in] sense - \ru Направление усеченной кривой относительно исходной.\n
      sense = 1 - направление кривой сохраняется.
      sense = -1 - направление кривой меняется на обратное.
                       \en Direction of a trimmed curve in relation to an initial curve.
      sense =  1 - direction does not change.
      sense = -1 - direction changes to the opposite value. \~
    \result \ru Построенная усеченная кривая.
            \en A constructed trimmed curve. \~
  */
  virtual MbCurve *   Trimmed  ( double t1, double t2, int sense ) const; // \ru Усечь кривую \en Trim a curve 
          MbCurve *   TrimmedBreak( double t1, double t2, int sense ) const; // \ru Усечь кривую с разрывом \en Trim a curve with a break 

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const;

  // \ru Удалить часть поликривой между параметрами t1 и t2 \en Remove a part of the polyline between t1 and t2 parameters 
  virtual MbeState    DeletePart( double, double, MbCurve *& );

  // \ru Оставить часть поликривой между параметрами t1 и t2 \en Save a part of the polyline between t1 and t2 parameters 
  virtual MbeState    TrimmPart( double, double, MbCurve *& );
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const;

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 

  // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double      CalculateMetricLength() const; 
  // \ru Сдвинуть параметр t на расстояние len. \en Move parameter t on the metric distance len. 
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const;
  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;

  /** \} */
  /** \ru \name Общие функции полигональной кривой
      \en \name Common functions of a polygonal curve
      \{ */

  virtual void        InsertPoint( ptrdiff_t index, const MbCartPoint & ); // \ru Добавить точку \en Add a point 
  virtual void        InsertPoint( double t, const MbCartPoint &, double xEps, double yEps ); // \ru Добавить точку \en Add a point 
  virtual void        ChangePoint( ptrdiff_t index, const MbCartPoint & ); // \ru Заменить точку \en Replace a point 
  virtual void        RemovePoints();                             // \ru Удалить все точки \en Remove all points 

  virtual void        GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const; // \ru Выдать интервал влияния точки кривой \en Get interval of influence of a curve point 

  virtual double      PointProjection( const MbCartPoint & to ) const; // \ru Проекция точки на полилинию \en Point projection on the polyline 
  virtual void        IntersectHorizontal( double y, SArray<double> & ) const; // \ru Пересечение кривой с горизонтальной прямой \en Intersection of a curve with a horizontal line 
  virtual void        IntersectVertical  ( double x, SArray<double> & ) const; // \ru Пересечение с вертикальной прямой \en Intersection with a vertical line 
  // \ru Загнать параметр получить локальный индексы и параметры \en Drive parameter into domain, get local indices and parameters 
  virtual bool        CheckParam ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const;
  virtual double      GetParam( ptrdiff_t i ) const;
  virtual size_t      GetParamsCount() const; 

  /** \brief \ru Создание копии кривой.
             \en Creation of a curve copy. \~
    \details \ru Создание копии кривой циклическим перебросом части кривой 
      с началом в t1 или t2 для замкнутой пространственной кривой на поверхности.
             \en Creation of a curve copy by cyclic flip of a curve part 
      starting at t1 or t2 for a closed spatial curve on the surface. \~
    \param[in] t1 - \ru Крайний параметр с копируемой части кривой.
                    \en The first parameter of copied part of the curve. \~
    \param[in] t2 - \ru Крайний параметр с копируемой части кривой.
                    \en The second parameter of copied part of the curve. \~
    \return \ru Копия части кривой.
            \en A copy of the curve part. \~
  */
  virtual MbCurve *   CicleCopy( double t1, double t2 ) const;

  /** \brief \ru Подготовить вычисление сплайна.
             \en Prepare the calculation of the spline. \~
  \details \ru Подготовить параметры для вычисления кубического сплайна.
    Если кривая не замкнута и black = true, система решается
    при условии отсутствия узла.
           \en Prepare parameters for calculation of a cubic spline.
    If a curve is not closed and "black" is true then the system has a solution
    when knot is absent. \~
  */
          void        InitCreate  ( MbVector &, MbVector &, SArray<MbVector> &, double &,
                                    double &, double &, double &, bool black = false );
          /// \ru Решить систему методом исключения Гаусса. \en Solve the system by Gaussian elimination method. 
          void        Create      ( MbVector &, MbVector &, bool black = false );
          /// \ru Вычислить производные на концах в случае незамкнутости сплайна. \en Calculate derivatives at the ends if the spline is not closed. 
          void        CreateEndS  ( MbVector &, MbVector & );
          /// \ru Построить сплайн если необходимо. \en Create a spline if necessary. 
          void        Create      (); 
          /// \ru Очистить кривую. \en Clear the curve. 
          void        Delete      (); 
          /// \ru Установить область изменения параметра: первый - минимальный, второй - максимальный. \en Set the range of parameter: the first is minimum, the second is maximum. 
          bool        SetLimitParam( double newTMin, double newTMax );
          /// \ru Преобразовать в замкнутую кривую, если кривая разомкнута но концы кривой гладко стыкуются. \en Convert to a closed curve if the curve is unclosed but the ends of the curve are connected smoothly. 
          bool        ConvertToClosed(); 
  virtual void        SetBegEndDerivesEqual(); // \ru Установить равные производные на краях \en Set equal derivatives at the edges 
  virtual void        ClosedBreak(); // \ru Сделать незамкнутой, оставив совпадающими начало и конец \en Make unclosed, leave coinciding start and end 
          /// \ru Вычисление шага аппроксимации. \en Calculation of a step of approximation. 
          double      StepD( double &t, double sag, bool bfirst, double ang = 0.35 ) const; 

          /// \ru Вернуть количество элементов в массиве векторов производных. \en Get the number of elements in array of derivative vectors. 
          ptrdiff_t   GetVectorListCount() const { return (ptrdiff_t)/*OV_x64 (int)*/vectorList.Count(); }
          /// \ru Вернуть массив вторых призводных в контрольных точках. \en Get the array of second derivatives at the control points. 
          void        GetVectorList( SArray<MbVector> & vectors ) const { vectors = vectorList; } 
          /// \ru Выдать вектор второй производной с индексов i. \en Get the vector of the second derivative with index i. 
  const   MbVector  & GetVectorList( size_t i ) const { return vectorList[i]; }
          /// \ru Выдать вектор второй производной с индексов i. \en Get the vector of the second derivative with index i. 
          MbVector  & SetVectorList( size_t i )       { return vectorList[i]; } 

          /// \ru Вернуть количество параметров в узлах. \en Get the number of parameters in knots. 
          ptrdiff_t   GetTListCount() const { return tList.Count(); } 
          /// \ru Вернуть массив параметров в узлах. \en Get the array of parameters in knots. 
  virtual void        GetTList( SArray<double> & params ) const { params = tList; } 
          /// \ru Вернуть значение параметра для точки с индексом i. \en Get the value of parameter for the point with index i. 
  const   double &    GetTList( size_t i ) const { return tList[i]; } 
          /// \ru Вернуть число сегментов сплайна. \en Get the number of spline segments. 
          ptrdiff_t   GetUppParam() const { return splinesCount; } 
          /// \ru Определение максимального индекса массива параметров слева. \en Determination of the maximum index of parameter array on the left.  
          ptrdiff_t   GetIndex( double t ) const; 
  /** \} */
private:
          // \ru Найти узел в положительном направлении \en Find a knot in the positive direction 
          void        AddKnot( ptrdiff_t &, double &, ptrdiff_t &, double &, ptrdiff_t &, double & ) const;
          void        CheckSpline(); // \ru Проверить корректность расчета сплайна \en Check correctness of the spline calculation 
          void        operator = ( const MbCubicSpline & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCubicSpline )
};

IMPL_PERSISTENT_OPS( MbCubicSpline )

//------------------------------------------------------------------------------
/// \ru Используется в трехмерном кубическом сплайне \en It is used in the three-dimensional cubic spline 
// ---
int SurStepCS( double & t, double & step, const SArray<double> & knots, ptrdiff_t idCs, bool bplus, bool bfirst,
               double & alp, double & qd, double df, double ds, double qds, double dt,
               double epsAL, double epsQD );


//------------------------------------------------------------------------------
/// \ru Используется в трехмерном кубическом сплайне \en It is used in the three-dimensional cubic spline 
// ---
int SurAngularStepCS( double & t, double & step, const SArray<double> & knots, ptrdiff_t idCs, bool bplus,
                      double & alf, double & alt, double df, double ds, double dt,
                      double epsAF, double epsAT );


#endif // __CUR_CUBIC_SPLINE_H
