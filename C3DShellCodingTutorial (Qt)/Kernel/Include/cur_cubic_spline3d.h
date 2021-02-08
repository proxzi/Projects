﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кубический сплайн.
         \en Cubic spline. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CUBIC_SPLINE3D_H
#define __CUR_CUBIC_SPLINE3D_H


#include <cur_polycurve3d.h>
#include <cur_cubic_spline.h>
#include <mb_placement3d.h>


//------------------------------------------------------------------------------
/** \brief \ru Кубический сплайн.
           \en Cubic spline. \~
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
    second derivatives of the spline vectorList at the control points.
    For unclosed curve the sets pointList, vectorList and tList must contain the same number of elements.
    For closed curve the number of elements tList must be one greater than the number of elements of pointList and vectorList. 
    Cubic spline passes through its control points for parameter values from the set tList.
    On each region between two neighboring control points the spline is described by the cubic polynomial. 
    Cubic polynomials are smoothly connected at the control points and they have continuous second derivatives at these points. 
    The second derivatives between the two neighboring control points of spline are changed linearly. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbCubicSpline3D : public MbPolyCurve3D {
protected :
  SArray<MbVector3D> vectorList;   ///< \ru Множество вторых производных в контрольных точках. \en Set of second derivatives at the control points. 
  SArray<double>     tList;        ///< \ru Множество параметров в контрольных точках. \en Set of parameters at the control points. 
  ptrdiff_t          splinesCount; ///< \ru Максимальное значение индекса в множестве параметров tList. \en Maximal value of index in the parameters tList. 

protected:
  MbCubicSpline3D(); ///< \ru Конструктор по умолчанию. \en Constructor by default. 
  MbCubicSpline3D( const MbCubicSpline3D & other ); // \ru Дублирующий конструктор. \en Duplicating constructor.
  // \ru Конструктор по точкам и признаку замкнутости \en Constructor by points and an attribute of closedness 
  MbCubicSpline3D( const SArray<MbCartPoint3D> & points, bool cls, VERSION version = Math::DefaultMathVersion() );
  // \ru Конструктор по точкам параметрам и признаку замкнутости \en Constructor by points, parameters and an attribute of closedness 
  MbCubicSpline3D( const SArray<MbCartPoint3D> & points,
                   const SArray<double       > & params, bool cls );
  // \ru Конструктор по точкам вторым производным и признаку замкнутости \en Constructor by points, second derivatives and closedness attribute 
  MbCubicSpline3D( const SArray<MbCartPoint3D> & points,
                   const SArray<MbVector3D   > & seconds, bool cls, VERSION version = Math::DefaultMathVersion() );
  // \ru Конструктор по точкам вторым производным параметрам и признаку замкнутости \en Constructor by points, second derivatives, parameters and an attribute of closedness 
  MbCubicSpline3D( const SArray<MbCartPoint3D> & points,
                   const SArray<MbVector3D   > & seconds,
                   const SArray<double       > & params, bool cls );
  // \ru Конструктор по точкам, первым производным на краях (если их надо учитывать) \en Constructor by points, first derivatives at the edges (if they should be considered) 
  MbCubicSpline3D( const SArray<MbCartPoint3D> & points,
                   const MbVector3D            & vectS, 
                   const MbVector3D            & vectE, 
                         bool                    sInit,
                         bool                    eInit );
  MbCubicSpline3D( const MbCurve3D & curve ); // \ru Конструктор по другой кривой \en Constructor by another curve 
  // \ru Конструктор по двумерному сплайну на плоскости \en Constructor by a two-dimensional spline on the plane 
  MbCubicSpline3D( const MbCubicSpline & initFlat, const MbPlacement3D & plane );
public:
  virtual ~MbCubicSpline3D();
public :
  /** \brief \ru Создать копию сплайна.
             \en Create copy of spline. \~
    \details \ru Создать копию сплайна.\n
             \en Create copy of spline.\n \~
  */
  static MbCubicSpline3D * Create( const MbCubicSpline3D & other );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн по заданной кривой и установить параметры сплайна.\n
             \en Create spline by a given curve and set parameters of spline.\n \~
    \param[in] curve - \ru Заданная кривая.
                       \en Given curve. \~
  */
  static MbCubicSpline3D * Create( const MbCurve3D & curve );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points  - \ru Набор контрольных точек.
                         \en Set of control points. \~
    \param[in] cls     - \ru Признак замкнутости.
                         \en A closedness attribute. \~
    \param[in] version - \ru Версия.
                          \en Version. \~
  */
  static MbCubicSpline3D * Create( const SArray<MbCartPoint3D> & points,
                                         bool                    cls, 
                                         VERSION                 version = Math::DefaultMathVersion() );
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
    \param[in] version - \ru Версия.
                         \en Version. \~
  */
  static MbCubicSpline3D * Create( const SArray<MbCartPoint3D> & points,
                                   const SArray<MbVector3D>    & seconds,
                                         bool                    cls,
                                         VERSION                 version = Math::DefaultMathVersion() );
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
  static MbCubicSpline3D * Create( const SArray<MbCartPoint3D> & points,
                                   const SArray<double>        & params, 
                                         bool                    cls );
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
  static MbCubicSpline3D * Create( const SArray<MbCartPoint3D> & points,
                                   const SArray<MbVector3D>    & seconds,
                                   const SArray<double>        & params, 
                                         bool                    cls );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] initFlat - \ru Плоский сплайн.
                            \en Plane spline. \~
    \param[in] plane - \ru Плоскость кривой.
                       \en Plane of curve. \~
  */
  static MbCubicSpline3D * Create( const MbCubicSpline & initFlat, const MbPlacement3D & plane );
  /** \brief \ru Создать сплайн.
             \en Create spline. \~
    \details \ru Создать сплайн и установить параметры сплайна.\n
             \en Create spline and set parameters of spline.\n \~
    \param[in] points - \ru Набор контрольных точек.
                        \en Set of control points. \~
    \param[in] vectS -  \ru Первая производная в начале.
                        \en First derivative at the begin. \~
    \param[in] vectE -  \ru Первая производная в конце.
                        \en First derivative at the end. \~
    \param[in] sInit -  \ru Учитывать ли производную в начале.
                        \en Use or not first derivative at the begin. \~
    \param[in] eInit -  \ru Учитывать ли производную в конце.
                        \en Use or not first derivative at the end. \~
  */
  // \ru Конструктор по точкам, первым производным на краях (если их надо учитывать) \en Constructor by points, first derivatives at the edges (if they should be considered) 
  static MbCubicSpline3D * Create( const SArray<MbCartPoint3D> & points,
                                   const MbVector3D            & vectS,
                                   const MbVector3D            & vectE,
                                         bool                    sInit,
                                         bool                    eInit );
public:
  VISITING_CLASS( MbCubicSpline3D );

          // \ru Инициализатор по точкам и признаку замкнутости \en Initializer by points and an attribute of closedness 
          bool    Init( const SArray<MbCartPoint3D> &, bool cls, VERSION version = Math::DefaultMathVersion() );
          // \ru Инициализатор по точкам вторым производным и признаку замкнутости \en Initializer by points, second derivatives and closedness attribute 
          bool    Init( const SArray<MbCartPoint3D> &, const SArray<MbVector3D> &, bool cls, VERSION version = Math::DefaultMathVersion() );
          // \ru Инициализатор по точкам параметрам и признаку замкнутости \en Initializer by points, parameters and an attribute of closedness 
          bool    Init( const SArray<MbCartPoint3D> &, const SArray<double> &, bool );
          // \ru Инициализатор по точкам вторым производным параметрам и признаку замкнутости \en Initializer by points, second derivatives, parameters and an attribute of closedness 
          bool    Init( const SArray<MbCartPoint3D> &, const SArray<MbVector3D> &,
                        const SArray<double       > &, bool );
          // \ru Инициализация по точкам и краевым производным \en Initialization by points and boundary derivatives 
          bool    Init( const SArray<MbCartPoint3D> &, const MbVector3D &, const MbVector3D &, bool, bool );
          // \ru Инициализация по точкам, параметрам и краевым производным \en Initialization by points, parameters and boundary derivatives 
          bool    Init( const SArray<MbCartPoint3D> &, const SArray<double> &,
                        const MbVector3D &, const MbVector3D &, bool, bool );
          bool    Init( const MbCurve3D & ); // \ru Инициализатор по другой кривой \en Initializer by another curve 
          void    InitC( const MbCubicSpline3D & ); // \ru Дублирующий инициализатор \en Duplicating initializer 
          // \ru Инициализатор по двумерному сплайну на плоскости \en Initializer by a two-dimensional spline on the plane 
          void    Init( const MbCubicSpline &, const MbPlacement3D & );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным \en Make equal 
  virtual void    Transform( const MbMatrix3D    &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D    &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D      &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMin() const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax() const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn  ( double &, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on curve 
  virtual void    FirstDer ( double &, MbVector3D    & ) const; // \ru Первая производная \en First derivative 
  virtual void    SecondDer( double &, MbVector3D    & ) const; // \ru Вторая производная \en Second derivative 
  virtual void    ThirdDer ( double &, MbVector3D    & ) const; // \ru Третья производная \en Third derivative 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

          void    FourDer        ( double &, MbVector3D & ) const; // \ru четвертая производная \en Fourth derivative 
  
  // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const;

  virtual void    Inverse ( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual size_t  GetCount() const;
  virtual void    Rebuild (); // \ru Перестроить кривую \en Rebuild the curve 
  virtual void    SetClosed( bool cls ); // \ru Установить признак замкнутости. \en Set attribute of closedness. 
  virtual bool    IsDegenerate( double eps = METRIC_PRECISION ) const;
  virtual MbCurve3D * TrimmBreak( double t1, double t2, int sense ) const; // \ru Создать усеченную кривую \en Create the trimmed curve 
  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const;

  virtual bool    IsPlanar  () const; // \ru Является ли кривая плоской \en Whether a curve is planar 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const; // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if curve is planar 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Give a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called for a two-dimensional curve) 
  virtual bool    GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;

  // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double  CalculateMetricLength() const;
  // \ru Сдвинуть параметр t на расстояние len. \en Move parameter t on the metric distance len. 
  virtual bool    DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                 VERSION version = Math::DefaultMathVersion() ) const; 

  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void    GetCurvatureContinuityBounds( std::vector<double> & params ) const;

  // \ru Общие функции полигональной кривой \en Common functions of a polygonal curve 

  virtual void    InsertPoint( ptrdiff_t index, const MbCartPoint3D & ); // \ru Добавить точку \en Add a point 
  virtual void    InsertPoint( double t, const MbCartPoint3D &, double eps ); // \ru Добавить точку \en Add a point 
  virtual bool    ChangePoint( ptrdiff_t index, const MbCartPoint3D & ); // \ru Заменить точку \en Replace a point 
  virtual void    RemovePoints();                               // \ru Удалить все точки \en Remove all points 
  // \ru Загнать параметр получить локальный индексы и параметры \en Move parameter, get local indices and parameters 
  virtual bool    CheckParam  ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const;
  virtual double  GetParam( ptrdiff_t i ) const; // \ru Выдать параметр для точки с номером \en Get a parameter for point with number 
  virtual void    GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const; // \ru Выдать интервал влияния точки кривой \en Get interval of influence of a curve point 

  virtual double  Step         ( double t, double sag    ) const; // \ru Вычисление шага аппроксимации \en Calculation of approximation step 
  virtual double  DeviationStep( double t, double angle  ) const;
  // \ru Периодичность \en Periodicity  
  virtual bool    IsPointsPeriodic( ptrdiff_t & begPointNumber,              // \ru Номер первой точки \en Number of the first point 
                                    ptrdiff_t & endPointNumber,              // \ru Номер последней точки \en Number of the last point 
                                    ptrdiff_t & period )         const;      // \ru Количество точек в периоде \en The number of points in the period 

          void    Delete(); // \ru Очистить данные \en Clear data 
          // \ru Подготовить вычисление сплайна \en Prepare the calculation of the spline 
          void    InitCreate( MbVector3D &, MbVector3D &, SArray <MbVector3D> &,
                              double &, double &, double &, double &, bool black = false );

          // \ru Решить систему методом исключения гауса \en Solve the system by Gaussian elimination method 
          // \ru Если кривая не замкнута и black = true система решается \en If a curve is non-closed and black is true then the system is solved 
          // \ru При условии отсутствия узла Де Бор К. "Практическое руководство по сплайнам" \en If knot is not (Carl de Boor - "A Practical Guide to Splines") 
          // \ru 1985, М.: Радио и связь, стр. 52. \en 2001,  Springer 52. 
          void    Create    ( MbVector3D &, MbVector3D &, bool black = false );
          void    CreateEndS( MbVector3D &, MbVector3D & ) const;
          void    Create    (); // \ru Построить сплайн \en Create a spline 
          
          void    Create    ( const MbVector3D &, const MbVector3D &, bool , bool );
          // \ru Вычислить параметры сплайна \en Calculate parameters of the spline 
          void    CreateVects( const MbVector3D & startS, bool startFirst, 
                               const MbVector3D & endS,   bool endFirst );
          // \ru Установить область изменения параметра первый минимальный второй максимальный \en Set the range of the parameter: first minimum and second maximum 
          bool    SetLimitParam( double, double );
          bool    ConvertToClosed(); // \ru Преобразовать в замкнутую кривую если кривая разомкнута \en Convert to a closed curve if the curve is open 
                                     // \ru Но концы кривой гладко стыкуются \en But the ends of the curve are connected smoothly 
          double  StepD( double t, double sag, bool bfirst, double angle = Math::lowRenderAng ) const; // \ru Вычисление шага аппроксимации \en Calculation of approximation step 

          ptrdiff_t     GetVectorListCount() const { return (ptrdiff_t)vectorList.Count(); }
          void          GetVectorList( SArray<MbVector3D> & vectors ) const { vectors = vectorList; } ///< \ru Вторые призводные в хар. точках \en Second derivatives at control points.   
  const   MbVector3D  & GetVectorList( size_t i ) const { return vectorList[i]; } // \ru Вторые призводные в характеристических точках \en Second derivatives at control points. 
          MbVector3D  & SetVectorList( size_t i )       { return vectorList[i]; } // \ru Вторые призводные в характеристических точках \en Second derivatives at control points. 

          ptrdiff_t GetTListCount() const { return tList.Count(); } ///< \ru Количество параметров в узлах \en The number of parameters in knots. 
          void      GetTList( SArray<double> & params ) const { params = tList; } ///< \ru Параметры в узлах \en Parameters in knots 
  const   double &  GetTList( size_t i ) const { return tList[i]; } 
          
          ptrdiff_t GetUppParam() const { return splinesCount; } ///< \ru число сегментов \en The number of segments 
                                      

private:
          // \ru Найти узел в положительном направлении \en Find a knot in the positive direction 
          void    AddKnot( ptrdiff_t &, double &, ptrdiff_t &, double &, ptrdiff_t &, double & ) const;
          void    CheckSpline() const; // \ru Проверить корректность расчета сплайна \en Check correctness of the spline calculation 
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          void    operator = ( const MbCubicSpline3D & ); 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCubicSpline3D )
};

IMPL_PERSISTENT_OPS( MbCubicSpline3D )

#endif // __CUR_CUBIC_SPLINE3D_H
