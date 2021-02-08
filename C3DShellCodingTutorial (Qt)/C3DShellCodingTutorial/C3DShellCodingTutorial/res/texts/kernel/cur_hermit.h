﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Cоставной кубический сплайн Эрмитa в двумерном пространстве.
         \en Composite Hermite cubic spline in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_HERMIT_H
#define __CUR_HERMIT_H


#include <cur_polycurve.h>
#include <alg_base.h>
#include <mb_rect1d.h>


class MbRegDuplicate;
class MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Составной кубический сплайн Эрмитa в двумерном пространстве.
           \en Composite Hermite cubic spline in two-dimensional space. \~
  \details \ru Составной кубический сплайн Эрмитa определяется контрольными точками pointList, первыми производными 
    сплайна vectorList в контрольных точках и значениями параметра сплайна tList в контрольных точках. 
    Для не замкнутой кривой множества pointList, vectorList и tList должны содержать одинаковое количество элементов.
    Для замкнутой кривой количество элементов tList должно быть на единицу больше, чем количество элементов pointList и vectorList. 
    Сплайн Эрмитa является составной кубический кривой.
    На каждом участке между двумя соседними контрольными точками сплайн описывается кубическим полиномом 
    с заданными точками и производными на краях. 
    Сплайн Эрмитa проходит через свои контрольные точки при значениях параметра из множества tList и имеет в них заданные производные.
    Кубические полиномы гладко стыкуются в контрольных точках и имеют в них непрерывные первые производные. 
    Если производные в контрольных точках не заданы, то они рассчитываются по данной контрольной точке и двух её соседним точкам.
    Для этого то трём точкам и значениям параметров в них строится парабола и вычисляется производная параболы в средней точке.
    Производные в краевых контрольных точках определяются по двум точкам и условию на краю для второй производной (ноль).
           \en Composite Hermite cubic spline is defined by control points pointList, the first derivatives 
    of spline vectorList in control points and values of the spline parameter in control point. 
    For unclosed curve the sets pointList, vectorList and tList must contain the same number of elements.
    For closed curve the number of elements tList must be one greater than the number of elements of pointList and vectorList. 
    Hermite spline is a composite cubic curve.
    On each region between two neighboring control points the spline is described by the cubic polynomial 
    with given points and derivatives at the edges. 
    Hermite spline passes through its control points for parameter values ??from the set tList and has in them given derivatives.
    Cubic polynomials are connected smoothly at the control points and they have continuous first derivatives at these points. 
    If the derivatives at the control points are not specified then they are calculated by the given control point and its two neighboring points.
    For this purpose parabola is constructed by three points and the values ??of parameters in these points, and after this the derivative of parabola is calculated at the middle point.
    Derivatives at the boundary control points are defined by two points and the condition on the edge for the second derivative (zero). \~ 
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbHermit : public MbPolyCurve {
protected :
  SArray<MbVector> vectorList;   ///< \ru Множество производных в контрольных точках. \en Set of derivatives at the control points. 
  SArray<double>   tList;        ///< \ru Множество параметров в контрольных точках. \en Set of parameters at the control points. 
  ptrdiff_t        splinesCount; ///< \ru Количество сплайнов. \en The number of splines. 

protected:
  MbHermit(); ///< \ru Конструктор по умолчанию. \en Constructor by default.
  MbHermit( const MbHermit & ); ///< \ru Конструктор копирования. \en Copy constructor.
  /** \brief \ru Конструктор по набору точек и признаку замкнутости.
             \en Constructor by point set and an attribute of closedness. \~
    \details \ru Конструктор по набору точек и признаку замкнутости.
             \en Constructor by point set and an attribute of closedness. \~
    \param[in] initList - \ru Массив точек кривой.
                          Для замкнутой кривой количество точек должно быть не меньше трех,
                          для разомкнутой кривой - не меньше двух.
                          \en An array of curve points.
                          For a closed curve the number of points must be no less than three,
                          for an open curve - no less than two. \~
    \param[in] cls - \ru Замкнутость кривой.
                     \en A curve closedness. \~
  */
  MbHermit( const SArray<MbCartPoint> & initList, bool cls );

  MbHermit( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints, bool cls );
  MbHermit( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints, const SArray<MbVector> & initVectors, bool cls );
  MbHermit( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints, const SArray<ptrdiff_t> & vLabels, bool cls ); 
  MbHermit( const MbCartPoint & p1, const MbCartPoint & p2 ); // \ru Конструктор по двум точкам \en Constructor by two points 
  MbHermit( double t1, const MbCartPoint & p1, const MbVector & v1, 
            double t2, const MbCartPoint & p2, const MbVector & v2 ); // \ru Конструктор по двум точкам и производным в этих точках \en Constructor by two points and derivatives at this points. 
public :
  virtual ~MbHermit();

public :
  /** \brief \ru Создать копию сплайна.
             \en Create copy of spline. \~
    \details \ru Создать копию сплайна.\n
             \en Create copy of spline.\n \~
  */
  static MbHermit * Create( const MbHermit & );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] initList - \ru Набор контрольных точек.
                          \en Set of control points. \~
    \param[in] cls      - \ru Признак замкнутости.
                          \en A closedness attribute. \~
  */
  static MbHermit * Create( const SArray<MbCartPoint> & initList, bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] initParams  - \ru Набор параметров в контрольных точках.
                             \en Set of parameters at the control points. \~
    \param[in] initPoints  - \ru Набор контрольных точек.
                             \en Set of control points. \~
    \param[in] cls         - \ru Признак замкнутости.
                             \en A closedness attribute. \~
  */
  static MbHermit * Create( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints,
                            bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] initParams  - \ru Набор параметров в контрольных точках.
                             \en Set of parameters at the control points. \~
    \param[in] initPoints  - \ru Набор контрольных точек.
                             \en Set of control points. \~
    \param[in] initVectors - \ru Набор производных в контрольных точках.
                             \en Set of derivatives at the control points. \~
    \param[in] cls         - \ru Признак замкнутости.
                             \en A closedness attribute. \~
  */
  static MbHermit * Create( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints,
                            const SArray<MbVector> & initVectors, bool cls );
  /** \brief \ru Создать сплайн, согласованный с LoftSurface.
             \en Create spline, agreed with LoftSurface. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] initParams - \ru Набор параметров в контрольных точках.
                            \en Set of parameters at the control points. \~
    \param[in] initPoints - \ru Набор контрольных точек.
                            \en Set of control points. \~
    \param[in] vLabels    - \ru Массив, содержащий номера соседних точек с одинаковыми производными.
                            \en Array, containing indexes of points with same derivative. \~
    \param[in] cls        - \ru Признак замкнутости.
                            \en A closedness attribute. \~
  */
  static MbHermit * Create( const SArray<double> & initParams, const SArray<MbCartPoint> & initPoints,
                            const SArray<ptrdiff_t> & vLabels, bool cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать прямолинейный сплайн и установить параметры сплайна.\n
             \en Create a straight and set parameters of spline.\n \~
    \param[in] p1 - \ru Начальная точка кривой.
                    \en Start point of curve. \~
    \param[in] p2 - \ru Конечная точка кривой.
                    \en End point of curve. \~
  */
  static MbHermit * Create( const MbCartPoint & p1, const MbCartPoint & p2 );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] t1 - \ru Начальный параметр.
                    \en The initial parameter. \~
    \param[in] p1 - \ru Начальная точка кривой.
                    \en Start point of curve. \~
    \param[in] v1 - \ru Касательный вектор к кривой в начальной точке.
                    \en A tangent vector to the curve at the start point. \~
    \param[in] t2 - \ru  Конечный параметр.
                    \en The final parameter. \~
    \param[in] p2 - \ru Конечная точка кривой.
                    \en End point of curve. \~
    \param[in] v2 - \ru Касательный вектор к кривой в конечной точке.
                    \en A tangent vector to the curve at the end point. \~
  */
  static MbHermit * Create( double t1, const MbCartPoint & p1, const MbVector & v1,
                            double t2, const MbCartPoint & p2, const MbVector & v2 );

public :
  VISITING_CLASS( MbHermit ); 

          // \ru Установить параметры сплайна \en Set parameters of spline 
          bool        Init( const SArray<MbCartPoint> & initPoints, bool cls );
          bool        Init( const SArray<double> & initParams,
                            const SArray<MbCartPoint> & initPoints, bool cls );
          bool        Init( const SArray<double> & initParams,
                            const SArray<MbCartPoint> & initPoints, 
                            const SArray<MbVector> & initVectors, bool cls );
          bool        Init( const SArray<double> & initParams,
                            const SArray<MbCartPoint> & initPoints, 
                            const SArray<ptrdiff_t> & vLabels, bool cls ); 
          void        Init( const MbHermit & init );
          void        Init( double t1, const MbCartPoint & p1, const MbVector & v1, 
                            double t2, const MbCartPoint & p2, const MbVector & v2 );
          bool        Init( double t1, double t2 );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of geometric object.
      \{ */

  virtual MbePlaneType  IsA() const;                      // \ru Тип элемента \en Type of element 
  virtual bool        SetEqual( const MbPlaneItem & );  // \ru Сделать элементы равными \en Make the elements equal 
  virtual void        Transform( const MbMatrix & matr, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector & to, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 

  /** \} */
  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */

  // \ru Удалить часть кривой между параметрами t1 и t2 \en Delete a part of a curve between parameters t1 and t2 
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 );
  // \ru Оставить часть кривой между параметрами t1 и t2 \en Save a curve part between t1 and t2 parameters 
  virtual MbeState    TrimmPart( double t1, double t2, MbCurve *& part2 );
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;

  // \ru Создать NURBS представление кривой \en Create a NURBS representation of the curve 
  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 
  virtual	MbContour * NurbsContour() const;

  virtual double      GetTMin() const;       // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax() const;       // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void        PointOn  ( double & t, MbCartPoint & p  ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector    & fd ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & td ) const; // \ru Третья производная \en Third derivative 
  // \ru Функции для работы внутри и вне области определения кривой. \en Functions for working inside and outside of the curve domain. \~
  virtual void       _PointOn  ( double t,   MbCartPoint & p  ) const;
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double      Step( double t, double sag ) const;  // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of approximation step with consideration of curvature radius 
  virtual double      DeviationStep( double t, double angle ) const;  // \ru Вычисление шага аппроксимации по угловой толерантности \en Calculation of approximation step by angular tolerance 

  virtual double      PointProjection( const MbCartPoint & pnt ) const; // \ru Проекция точки на кривую \en Point projection on the curve 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции \en Point projection on the curve or its extension in the projection search area 
  virtual double      CalculateMetricLength() const; // \ru Посчитать метрическую длину разомкнутой \en Calculate the open metric length   
  virtual bool        GetWeightCentre( MbCartPoint & wc ) const; // \ru Посчитать центр тяжести кривой \en Calculate the gravity center of the curve  
  virtual void        CalculateGabarit( MbRect & r ) const; // \ru Определить габариты \en Calculate bounding box  
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const;
  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;


  virtual bool        IsStraight()   const; // \ru Признак прямолинейности кривой \en An attribute of curve straightness 

  virtual size_t      GetCount() const;

  // \ru Выдать индекс точки, ближайшей к заданной \en Get index of the nearest point to the given one 
  virtual	ptrdiff_t   GetNearPointIndex( const MbCartPoint & pnt ) const;

  virtual void        Rebuild();  // \ru Пересчитать кривую \en Rebuild the curve 
  virtual void        SetClosed( bool cls ); // \ru Установить признак замкнутости. \en Set attribute of closedness. 
  virtual void        AddPoint( const MbCartPoint & pnt );               // \ru Добавить точку в конец массива \en Add a point to the end of array 
  virtual void        InsertPoint( ptrdiff_t index, const MbCartPoint & pnt ); // \ru Вставить точку по индексу \en Insert a point by index 
  virtual void        InsertPoint( double t, const MbCartPoint & pnt, double xEps, double yEps ); // \ru Вставить точку. \en Insert a point. 
  virtual void        InsertPoint( double t, const MbCartPoint & pnt, const MbVector & v, double xEps, double yEps ); // \ru Вставить точку и производную. \en Insert a point and derivetive.
  virtual void        SetCurveValue( double t, const MbCartPoint & pnt, double tDelta, const MbVector & v, double xEps, double yEps ); // \ru Установить точку и производную на участке. \en Set a point and derivetive at region.
  virtual void        ChangePoint( ptrdiff_t index, const MbCartPoint & pnt ); // \ru Заменить точку \en Replace a point 
  virtual void        RemovePoint( ptrdiff_t index );                   // \ru Удалить точку \en Remove a point 
          void        GetVector( ptrdiff_t index, MbVector & vec ) const;
          MbCartPoint & SetPoint( ptrdiff_t index ); 
          MbVector &  SetVector ( ptrdiff_t index );
          bool        SetTangentVectors( const SArray<MbVector> & tauVectors ); // \ru vectorList[i] сделать параллельными tauVectors[i] \en Make vectorList[i] parallel to tauVectors[i] 
  virtual size_t      GetPointsCount() const; // \ru Выдать количество точек \en Get the number of points 
  virtual size_t      GetParamsCount() const; // \ru Выдать количество параметров \en Get the number of parameters. 
  virtual bool        CheckParam ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const; // \ru Установить параметр \en Set parameter 
  virtual double      GetParam( ptrdiff_t index ) const;
  // \ru Создание копии циклически перебросом части кривой с началом в t1 или t2 для замкнутой пространственной кривой на поверхности. \en Creation of a copy by cyclic flip of a curve part starting at t1 or t2 for a closed spatial curve on surface. 
  virtual MbCurve *   CicleCopy( double t1, double t2 ) const;

  // \ru Выдать интервал влияния точки \en Get the interval of point influence 
  virtual void        GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const;
  virtual void        SetBegEndDerivesEqual(); // \ru Установить равные производные на краях \en Set equal derivatives at the edges 
  virtual void        ClosedBreak(); // \ru Сделать незамкнутой, оставив совпадающими начало и конец \en Make unclosed, leave coinciding start and end 
          
          bool        SetLimitParam( double newTMin, double newTMax ); // \ru Установить область изменения параметра \en Set range of parameter  
          void        CalculateDerivatives(); 
          void        SetLimitVector( int n, const MbVector & v );
          /// \ru Создать кривую путём сращивания части данной кривой с частью кривой init. \en Create a curve by joining a part of this curve with a part of "init" curve.
          MbHermit *  CurvesCombine( double t0, double w0, bool add, 
                                     const MbHermit & init, double t1, double w1, double koef ) const;

          size_t      GetVectorListCount() const { return vectorList.Count(); }
          void        GetVectorList( SArray<MbVector> & vectors ) const { vectors = vectorList; }
    const MbVector & _GetVectorList( size_t i ) const { return vectorList[i]; }
          MbVector & _SetVectorList( size_t i )       { MbPolyCurve::Refresh(); return vectorList[i]; }

          size_t      GetTListCount() const { return tList.Count(); }
  virtual void        GetTList( SArray<double> & params ) const { params = tList; }
          double     _GetTList( size_t i ) const { return tList[i]; }

          // \ru Добавить точки и параметры в конец кривой в заданной последовательности. \en Parameters and points add to end successively. 
          bool        AddPoints( SArray<double> & params, SArray<MbCartPoint> & points );
          // \ru Вставить точки и параметры в перед кривой в заданной последовательности. \en Parameters and points insetr to beg successively.
          bool        InsertPoints( SArray<double> & params, SArray<MbCartPoint> & points );

          /// \ru Определение максимального индекса массива параметров слева. \en Determination of the maximum index of parameter array on the left.  
          ptrdiff_t   GetIndex( double t ) const;

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 

  /** \} */
          void        LocalCoordinate( double & t,
                                       ptrdiff_t & index1, ptrdiff_t & index2,
                                       double    & param1, double    & param2,
                                       double    & paramD, double    & paramW,
                                       double    & quota1, double    & quota2 ) const;

private:
          bool        Break( MbHermit & trimPart, double t1, double t2 ) const; // \ru Выделать часть \en Make a part 
          void        CheckClosed( double epsilon ); // \ru Проверить и установить признак замкнутости кривой. \en Check and set closedness attribute of curve. 
          bool        SetCorrection( size_t ind, double tDelta ); // \ru Скорректировать кривую по индексу. \en Curve correction by index.
          void        CalculateValues( size_t i1, size_t i2 ); // \ru Скорректировать кривую на интервале i1-i2. \en Curve correction on the interval i1-i2.

          void        operator = ( const MbHermit & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbHermit )
};

IMPL_PERSISTENT_OPS( MbHermit )

//------------------------------------------------------------------------------
/// \ru Определение местных координат области поверхности \en Definition of local coordinates in a surface region 
// ---
inline void MbHermit::LocalCoordinate( double & t,
                                       ptrdiff_t & index1, ptrdiff_t & index2,
                                       double    & param1, double    & param2,
                                       double    & paramD, double    & paramW,
                                       double    & quota1, double    & quota2 ) const
{
#define EPS_NULL(a,epsilon)   ((a) < epsilon && (a) > -epsilon) // проверка значения в epsilon-окрестности нуля без вызова функции ::fabs

  double tmin = tList[0];
  double tmax = tList[splinesCount];
  bool bmin = t < tmin;

  if ( bmin || t > tmax ) { // \ru Параметр вне границ \en Parameter is out of bounds 
    if ( closed ) { 
      double tmp = tmax - tmin;
      t -= ::floor((t-tmin) / tmp) * tmp; 
    }
    else {
      if ( bmin ) { // \ru Начальный участок \en Starting piece  
        t = tmin;
        index1 = 0;
        index2 = 1;
      }
      else {        // \ru Конечный участок \en Ending piece  
        t = tmax;
        index1 = splinesCount - 1;
        index2 = splinesCount % (uppIndex + 1);
      }
      param1 = tList[index1];
      param2 = tList[index1+1];
      paramD = param2 - param1;
      paramW = 1.0 / paramD;
      double tparam1 = t - param1;
      double tparam2 = param2 - t;
      if ( EPS_NULL( tparam1, DOUBLE_EPSILON ) ) { //::fabs(tparam1) < DOUBLE_EPSILON
        quota1 = 1.0;
        quota2 = 0.0;
      }
      else if ( EPS_NULL( tparam2, DOUBLE_EPSILON ) ) { // ::fabs(tparam2) < DOUBLE_EPSILON
        quota1 = 0.0;
        quota2 = 1.0;
      }
      else {
        quota1 = tparam2 * paramW;
        quota2 = tparam1 * paramW;
      }
      return;
    }
  }
  ptrdiff_t index11 = index1 + 1;
  // \ru Устанавливаем диапазон поиска \en Set the search range 
  if ( index11 > 0 && index1 < splinesCount ) {
    param1 = tList[index1];
    param2 = tList[index11];
    if ( param1 <= t && t < param2 ) { // \ru Предыдущее значение верно \en The previous value is true 
      double tparam1 = t - param1;
      double tparam2 = param2 - t;
      index2 = index11 % (uppIndex + 1);
      paramD = param2 - param1;
      paramW = 1.0 / paramD;
      if ( EPS_NULL( tparam1, DOUBLE_EPSILON ) ) { // ::fabs(tparam1) < DOUBLE_EPSILON
        quota1 = 1.0;
        quota2 = 0.0;
      }
      else if ( EPS_NULL( tparam2, DOUBLE_EPSILON ) ) { // ::fabs(tparam2) < DOUBLE_EPSILON
        quota1 = 0.0;
        quota2 = 1.0;
      }
      else {
        quota1 = tparam2 * paramW;
        quota2 = tparam1 * paramW;
      }
      return;
    }
    index2 = index11;
    if ( index1>0 )
      index1--;
    if ( t < tList[index1] )
      index1 = 0;
    if ( index2 < splinesCount )
      index2++;
    if ( t >= tList[index2] )
      index2 = splinesCount;
  }
  else {
    index1 = 0;
    index2 = splinesCount;
  }

  ptrdiff_t ind, delta = index2 - index1; // \ru Диапазон \en A range 
  // \ru Поиск половинным делением \en Search by bisection 
  while ( delta > 1 ) {
    ind = index1 + ( delta / (ptrdiff_t)2 ); // \ru Индекс в середине \en The index in the middle 
    if ( t < tList[ind] )  // \ru Если t меньше серединного параметра \en If t is less than the middle parameter 
      index2 = ind; // \ru Изменить правую границу \en Change the right bound 
    else 
      index1 = ind; // \ru Изменить левую границу \en Change the left bound 
    delta = index2 - index1; // \ru Диапазон \en A range 
  }

  index2 = index2 % (uppIndex + 1);
  param1 = tList[index1];
  param2 = tList[index1+1];
  paramD = param2 - param1;
  paramW = 1.0 / paramD;
  double tparam1 = t - param1;
  double tparam2 = param2 - t;
  if ( EPS_NULL( tparam1, DOUBLE_EPSILON ) ) { // ::fabs(tparam1) < DOUBLE_EPSILON
    quota1 = 1.0;
    quota2 = 0.0;
  }
  else if ( EPS_NULL( tparam2, DOUBLE_EPSILON ) ) { // ::fabs(tparam2) < DOUBLE_EPSILON
    quota1 = 0.0;
    quota2 = 1.0;
  }
  else {
    quota1 = tparam2 * paramW;
    quota2 = tparam1 * paramW;
  }

#undef EPS_NULL
}


//------------------------------------------------------------------------------
/// \ru Вычисление вектора производной в средней точке по трём точкам параболы \en Calculation of derivative vector at the middle point by three points of parabola 
// pPrev = pointList[i-1]
// point = pointList[i]
// pNext = pointList[i+1]
// paramDeltaPrev = tList[i] - tList[i-1]
// paramDeltaNext = tList[i+1] - tList[i]
// derivative = vectorList[i]
// --- 
inline 
void HermitDerivative( const MbCartPoint & pPrev, const MbCartPoint & point, const MbCartPoint & pNext, 
                       double paramDeltaPrev, double paramDeltaNext,
                       MbVector & derivative )
{
  double dt  = paramDeltaNext + paramDeltaPrev;
  double dtPrev = -dt * paramDeltaPrev;
  double dtNext =  dt * paramDeltaNext;
  if ( ::fabs(dtPrev) > Math::paramRegion && ::fabs(dtNext) > Math::paramRegion ) { 
    // \ru Находим из равенства производной в средней точке параболы, построенной по трём точкам \en Find from equation of the derivative at the middle point of the parabola built by three points 
//double _dtPrev = 1.0 / dtPrev; // \ru Не используется из-за BUG_20548 //исправляет BUG_62835 \en Isn't used because BUG_20548 //fixes BUG_62835 
//double _dtNext = 1.0 / dtNext; // \ru Не используется из-за BUG_20548 \en Isn't used because BUG_20548 
//    derivative.Set( pPrev, paramDeltaNext * _dtPrev, point, -dt * _dtPrev,
//pNext, paramDeltaPrev * _dtNext, point, -dt * _dtNext ); // \ru Ломается 2)Часть дейдвуда.c3d //модели не ломаются \en Crashes 2) Part of deadwood.c3d //models are not crash 
    derivative.Set( pPrev, paramDeltaNext / dtPrev, point, -dt / dtPrev,
                    pNext, paramDeltaPrev / dtNext, point, -dt / dtNext ); // \ru Не ломается 4)7-016.c3d \en Isn't crash 4)7-016.c3d 
  }
  else {
    if ( ::fabs(dt) > NULL_EPSILON )
      derivative = (pNext - pPrev) / dt; 
  }
}


#endif // __CUR_HERMIT_H
