////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Сплайн Безье в двумерном пространстве.
         \en Bezier spline in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_BEZIER_H
#define __CUR_BEZIER_H


#include <cur_polycurve.h>
#include <templ_c_array.h>


class  MATH_CLASS MbArc;
class             MbRegDuplicate;
class             MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Сплайн Безье в двумерном пространстве.
           \en Bezier spline in two-dimensional space. \~
  \details \ru Сплайн Безье в двумерном пространстве определяется контрольными точками pointList. \n
    Сплайн Безье является составной кривой, образованной стыкующимися между собой кривыми Безье третьей степени. 
    Каждая кривая Безье третьей степени построена по четырём соседним контрольным точкам множества pointList. 
    Для незамкнутого сплайна Безье первая и последняя контрольная точка множества pointList не используются.
    Таким образом, сплайн Безье проходит через каждую контрольную точку множества pointList с индексом 3n+1, где n - целое число.
    Значение параметра вдоль каждой кривой Безье третьей степени увеличивается на единицу. 
    Параметр сплайна Безье изменяется от нуля до k, где k - количество кривых Безье третьей степени, образующих сплайн. 
    В общем случае первая производная сплайна Безье может быть разрывной как по длине, так и по направлению.
           \en Bezier spline in two-dimensional space is defined by control points pointList. \n
    Bezier spline is composite curve formed by connected among themselves Bezier curves with third degree. 
    Each third-degree Bezier curve is constructed by four adjacent control points pointList. 
    First and last control point from pointList for unclosed Bezier spline are not used
    Thus Bezier spline passes through each control point with index 3n+1, where n is integer.
    The value of parameter along each third-degree Bezier curve is incremented. 
    The parameter of Bezier spline changes from zero to k, where k is the number of  tree-degree Bezier curves which form spline. 
    In general case the first derivative of Bezier spline can be discontinuous by length and direction. \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbBezier : public MbPolyCurve {
private :
  ptrdiff_t splinesCount; ///< \ru Количество сплайнов. \en The number of splines. 
  int       form;         ///< \ru Форма сплайна. \en The shape of spline. 

public :
    /** \brief \ru Конструктор по массиву всех точек.
             \en Constructor by array of all points. \~
    \details \ru Конструктор по массиву всех точек(полюсов и коромысел),
      для создания из трехмерной кривой MbBezier3D.
             \en Constructor by array of all points(poles and rockers),
      for creation from three-dimensional curve MbBezier3D. \~         
    \param[in] closed - \ru Замкнута ли кривая.
                        \en Is curve closed? \~
    \param[in] points - \ru Массив точек. 
                        Должен быть получен из массива точек трехмерной кривой MbBezier3D, которая является
                        плоской, путем проецирования их на плоскость кривой.
                        Количество точек должно быть кратно трем. Минимальное количество точек - шесть.
                        \en An array of points. 
                        It must be obtained from point array of three-dimensional curve MbBezier3D which is 
                        planar, by projecting them onto the plane of the curve.
                        The number of points must be multiple of three. The minimal number of points is six. \~
  */
  DEPRECATE_DECLARE MbBezier( bool closed, const SArray<MbCartPoint> & points );
  /** \brief \ru Конструктор по полюсам.
             \en Constructor by poles. \~
    \details \ru Конструктор по полюсам. В массиве initList заданы только полюса.
             \en Constructor by poles. initList array contains only poles. \~
    \param[in] initList - \ru Массив полюсов кривой. 
                          Минимальное количество точек в массиве равно двум.
                          \en An array of curve poles. 
                          Minimal number of points in array equals two. \~
    \param[in] cls - \ru Замкнутость кривой.
                     \en A curve closedness. \~
    \param[in] initForm - \ru Форма сплайна. Возможные значения:\n
      0 - Стандартная форма.
      1 - Более выпуклая форма кривой.
                          \en The shape of spline. Possible values:\n
      0 - The standard form.
      1 - More convex form of curve. \~
  */
  DEPRECATE_DECLARE MbBezier( const SArray<MbCartPoint> & initList, bool cls, int initForm = 0 );
  
protected :
  MbBezier( const MbBezier & pCurve ); ///< \ru Конструктор копирования. \en Copy-constructor. 
  /** \brief \ru Конструктор по четырем точкам.
             \en Constructor by four points. \~
    \details \ru Конструктор по четырем точкам.
             \en Constructor by four points. \~
    \param[in] initList - \ru Массив точек. Количество точек должно быть равно четырем.
                              Если точек больше четырех, то на каждых последовательных четырех
                              точках строится классический кубический сплайн Безье.
                              Гладкость полученной кривой в точках стыка сегментов может нарушаться.
                          \en An array of points. Number of points must be equal to four.
                              When number of points is more then four classical cubic bezier is
                              created for each sequential four points. The smoothness of result curve
                              can be broken. \~
  */
  MbBezier( const SArray<MbCartPoint> & initList );

  /** \brief \ru Конструктор по сегменту Bezier-кривой.
             \en Constructor by segment of Bezier curve. \~
    \details \ru Конструктор по сегменту заданной Bezier-кривой.
             \en Constructor by segment of a given Bezier curve. \~
    \param[in] pCurve - \ru Заданная кривая.
                        \en A given curve. \~
    \param[in] iseg - \ru Номер сегмента кривой.
                      \en A number of curve segment. \~
  */
  MbBezier( const MbBezier & pCurve, ptrdiff_t iseg );
  /** \brief \ru Конструктор по дуге окружности.
             \en Constructor by circle arc. \~
    \details \ru Построена кривая Безье, точно аппроксимирующая заданную дугу окружности.
             \en There was constructed a Bezier curve which approximates a given arc of a circle. \~
    \param[in] arc - \ru Дуга окружности.
                     \en Circle arc. \~
  */
  MbBezier( const MbArc & arc ); // \ru Инициализация по дуге окружности \en Initialization by a circle arc 
public :
  virtual ~MbBezier();  ///< \ru Деструктор. \en Destructor. 

public :
  /** \brief \ru Создать копию сплайна.
             \en Create copy of spline. \~
    \details \ru Создать копию сплайна.\n
             \en Create copy of spline.\n \~
  */
  static MbBezier *   Create( const MbBezier & other );
  /** \brief \ru Создать сплайн по четырем точкам.
             \en Create spline by four points. \~
    \details \ru Создать сплайн по четырем точкам.
             \en Create spline by four points. \~
    \param[in] initList - \ru Массив точек. Количество точек должно быть равно четырем.
                              Если точек больше четырех, то на каждых последовательных четырех
                              точках строится классический кубический сплайн Безье.
                              Гладкость полученной кривой в точках стыка сегментов может нарушаться.
                          \en An array of points. Number of points must be equal to four.
                              When number of points is more then four classical cubic bezier is
                              created for each sequential four points. The smoothness of result curve
                              can be broken. \~
  */
  static MbBezier *   Create( const SArray<MbCartPoint> & initList );
  /** \brief \ru Создать сплайн по массиву всех точек.
             \en Create spline by array of all points. \~
    \details \ru Создать сплайн по массиву всех точек(полюсов и коромысел),
                 для создания из трехмерной кривой MbBezier3D.
             \en Create spline by array of all points(poles and rockers),
                 for creation from three-dimensional curve MbBezier3D. \~         
    \param[in] closed - \ru Замкнута ли кривая.
                        \en Is curve closed? \~
    \param[in] points - \ru Массив точек. 
                            Должен быть получен из массива точек трехмерной кривой MbBezier3D, которая является
                            плоской, путем проецирования их на плоскость кривой.
                            Количество точек должно быть кратно трем. Минимальное количество точек - шесть.
                        \en An array of points. 
                            It must be obtained from point array of three-dimensional curve MbBezier3D which is 
                            planar, by projecting them onto the plane of the curve.
                            The number of points must be multiple of three. The minimal number of points is six. \~
  */
  static MbBezier *   Create( bool closed, const SArray<MbCartPoint> & points );
  /** \brief \ru Создать сплайн по сегменту Bezier-кривой.
             \en Create spline by segment of Bezier curve. \~
    \details \ru Создать сплайн по сегменту заданной Bezier-кривой.
             \en Create spline by segment of a given Bezier curve. \~
    \param[in] pCurve - \ru Заданная кривая.
                        \en A given curve. \~
    \param[in] iseg - \ru Номер сегмента кривой.
                      \en A number of curve segment. \~
  */
  static MbBezier *   Create( const MbBezier & pCurve, ptrdiff_t iseg );
  /** \brief \ru Создать сплайн по полюсам.
             \en Create spline by poles. \~
    \details \ru Создать сплайн по полюсам. В массиве initList заданы только полюса.
             \en Create spline by poles. initList array contains only poles. \~
    \param[in] initList - \ru Массив полюсов кривой. 
                          Минимальное количество точек в массиве равно двум.
                          \en An array of curve poles. 
                          Minimal number of points in array equals two. \~
    \param[in] cls - \ru Замкнутость кривой.
                     \en A curve closedness. \~
    \param[in] initForm - \ru Форма сплайна. Возможные значения:\n
      0 - Стандартная форма.
      1 - Более выпуклая форма кривой.
                          \en The shape of spline. Possible values:\n
      0 - The standard form.
      1 - More convex form of curve. \~
  */
  static MbBezier *   Create( const SArray<MbCartPoint> & initList, bool cls, int initForm = 0 );
  /** \brief \ru Создать сплайн по дуге окружности.
             \en Create spline by circle arc. \~
    \details \ru Построена кривая Безье, точно аппроксимирующая заданную дугу окружности.
             \en There was constructed a Bezier curve which approximates a given arc of a circle. \~
    \param[in] arc - \ru Дуга окружности.
                     \en Circle arc. \~
  */
  static MbBezier *   Create( const MbArc & arc ); // \ru Инициализация по дуге окружности \en Initialization by a circle arc 

public :
  VISITING_CLASS( MbBezier ); 

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbePlaneType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual bool        SetEqual( const MbPlaneItem & );        // \ru Сделать элементы равными \en Make the elements equal 
  virtual bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether the 'curve' curve is duplicate of current curve. 
  virtual void        Transform( const MbMatrix & matr, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector & to, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
/** \} */
 /** \ru \name Функции инициализации сплайна.
     \en \name Spline initialization functions.
      \{ */  

  /** \brief \ru Инициировать кривую по полюсам и замкнутости.
             \en Initialize a curve by poles and closedness. \~
    \details \ru Инициировать кривую по полюсам и замкнутости. В массиве initList заданы только полюса.
             \en Initialize a curve by poles and closedness. initList array contains only poles. \~
    \param[in] initList - \ru Массив полюсов кривой.
                          \en An array of curve poles. \~
    \param[in] cls - \ru Замкнутость кривой.
                     \en A curve closedness. \~
  */
          void        Init( const SArray<MbCartPoint> & initList, bool cls );

  /** \brief \ru Инициировать кривую по заданной кривой Безье.
             \en Initialize a curve by a given Bezier curve. \~
    \details \ru Инициировать кривую по заданной кривой Безье. \n
             \en Initialize a curve by a given Bezier curve. \n \~
    \param[in] initCurve - \ru Заданная кривая.
                           \en A given curve. \~
  */
          void        Init( const MbBezier & initCurve );

  /** \brief \ru Инициировать кривую по дуге окружности.
             \en Initialize a curve by a circle arc. \~
    \details \ru Построена кривая Безье, точно аппроксимирующая заданную дугу окружности.
             \en There was constructed a Bezier curve which approximates a given arc of a circle. \~
    \param[in] arc - \ru Дуга окружности.
                     \en Circle arc. \~
  */
          void        Init( const MbArc & arc ); // \ru Инициализация по дуге окружности \en Initialization by a circle arc 

  /** \brief \ru Инициировать кривую по контрольным точкам.
             \en Initialize a curve by control points. \~
    \details \ru Инициировать кривую по контрольным точкам. 
      В массиве initList входят и полюса и коромысла.
             \en Initialize a curve by control points. 
      The array initList contains poles and "rocker arms". \~ 
    \param[in] initList - \ru Массив контрольных точек кривой.
                          \en An array of control points of curve. \~
  */
          void        InitCtrlPoints( const SArray<MbCartPoint> & initList );
/** \} */
 /** \ru \name Функции описания области определения кривой.
     \en \name Functions for curve domain description.
      \{ */
  virtual double      GetTMin() const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax() const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  /** \} */
  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the domain of a curve. 
            Functions: PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            when it is outside domain.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & p  ) const; // \ru Точка на кривой \en The point on the curve 
  virtual void        FirstDer ( double & t, MbVector    & fd ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & td ) const; // \ru Третья производная \en Third derivative 
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;
  /** \} */
  /** \ru \name Функции движения по кривой
      \en \name Functions of the motion along the curve
    \{ */
  virtual double 	    Step( double t, double sag ) const;  // \ru Вычисление шага аппроксимации с учетом радиуса кривизны \en Calculation of the approximation step with consideration of the curvature radius 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации по угловой толерантности \en Calculation of the approximation step by angular tolerance 

  /** \} */
  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve *   NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 
  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const;
  virtual	MbContour * NurbsContour() const;

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменение направления кривой на противоположное \en Change to the opposite direction of a curve 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
          /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
          /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;


  /** \} */
  /** \ru \name Общие функции полигональной кривой
      \en \name Common functions of a polygonal curve
      \{ */
  virtual size_t      GetPointsCount() const; ///< \ru Вернуть количество несовпадающих контрольных точек. \en Return the number of non-coincedent control points. 
  virtual void        GetPoint( ptrdiff_t index, MbCartPoint & pnt ) const; // \ru Выдать точку \en Get point 

  virtual	ptrdiff_t   GetNearPointIndex( const MbCartPoint & pnt ) const; ///< \ru Выдать индекс точки, ближайшей к заданной. \en Get the point index which is nearest to the given. 

  virtual void        GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const; // \ru Выдать интервал влияния точки \en Get the interval of point influence 

  virtual void        Rebuild();      // \ru Пересчитать Безье кривую \en Recalculate Bezier curve 
  virtual void        SetClosed( bool cls );

          // \ru BEG: для библиотеки (хорошо бы избавиться) \en BEG: for the library (it would be good to get rid of this) 
          void        LtSetClosed( bool cls );  // \ru Установить признак замкнутости. \en Set the closedness attribute. 
          // \ru END: для библиотеки (хорошо бы избавиться) \en END: for the library (it would be good to get rid of this) 

  virtual void        RemovePoint( ptrdiff_t index ); // \ru Удалить точку \en Remove the point. 
  virtual void        RemovePoints();                 // \ru Удалить все точки \en Remove all points 

  virtual void        AddPoint( const MbCartPoint & pnt );               // \ru Добавить точку в конец массива \en Add a point to the end of array 
  virtual void        InsertPoint( ptrdiff_t index, const MbCartPoint & pnt ); // \ru Вставить точку по индексу \en Insert a point by index 
  virtual void        InsertPoint( double t,  const MbCartPoint & pnt, double xEps, double yEps ); // \ru Вставить точку по индексу \en Insert a point by index 

  /** \brief \ru Заменить полюс.
             \en Replace the pole. \~
    \details \ru Заменяет характерную точку с указанным индексом.
             \en Replaces characteristic point with a given index. \~
    \param[in] index - \ru Индекс изменяемой точки.
                       \en An index of changed point. \~
    \param[in] pnt - \ru Заданная точка.
                     \en A given point. \~
  */
  virtual void        ChangePole ( ptrdiff_t index, const MbCartPoint & pnt );  // \ru Заменить полюс \en Replace the pole 
  virtual void        ChangePoint( ptrdiff_t index, const MbCartPoint & pnt ); // \ru Заменить точку или производную \en Replace a point or derivative 
  virtual bool        CheckParam ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const; // \ru Загнать параметр получить локальный индексы и параметры \en Move parameter, get local indices and parameters 
  virtual double      GetParam( ptrdiff_t i ) const;
  virtual size_t      GetParamsCount() const; 
  virtual void        GetTList( SArray<double> & params ) const;

  // \ru Функции только 2D кривой \en Functions for 2D-curve 

  virtual void        CalculateGabarit ( MbRect & ) const; // \ru Определить габариты кривой \en Determine the bounding box of the curve 

  virtual MbeState    DeletePart( double t1, double t2, MbCurve *&part2 ); // \ru Удалить часть поликривой между параметрами t1 и t2 \en Remove a part of the polyline between t1 and t2 parameters 
  virtual MbeState    TrimmPart( double t1, double t2, MbCurve *&part2 ); // \ru Оставить часть поликривой между параметрами t1 и t2 \en Save a part of the polyline between t1 and t2 parameters 

  virtual MbeState    Deformation( const MbRect &, const MbMatrix & );  // \ru Деформация \en Deformation 
  virtual bool        IsInRectForDeform( const MbRect & r ) const;      // \ru Виден ли объект в заданном прямоугольнике для деформации \en Whether the object is visible in the specified rectangle for the deformation 
  virtual void        TangentPoint( const MbCartPoint & pnt, SArray<double> & tFind ) const; // \ru Вычисление всех касательных к кривой из данной точки \en Calculation of all tangents to the curve from a given point 

  /** \brief \ru Добавить точку и производные в конец массива.
             \en Add point and derivatives to the end of array. \~
    \details \ru Добавить полюс в конец кривой и перемещением соседних точек (не полюсов), обеспечить 
      направление касательной к кривой в точке полюса и длины производных в полюсе.
             \en Add pole to the end of curve, and the movement of neighboring points (no poles), to ensure 
      the direction of the tangent to the curve at the pole and derivatives lengths in the pole. \~
    \param[in] pnt - \ru Заданная точка.
                     \en A given point. \~
    \param[in] dl - \ru Длина производной в полюсе слева.
                    \en Derivative length in pole on the left. \~
    \param[in] dr - \ru Длина производной в полюсе справа.
                    \en Derivative length in pole on the right. \~
    \param[in] angle - \ru Угол между направлением касательной и осью OX текущей системы координат.
                       \en The angle between the direction of the tangent and the OX-axis of the current coordinate system. \~
  */
          void        AddPoint( MbCartPoint & pnt, double dl, double dr, double angle );

  /** \brief \ru Определить выпуклую оболочку сегмента кривой.
             \en Determine the convex hull of the curve segment. \~
    \details \ru Определить выпуклую оболочку сегмента кривой.\n
             \en Determine the convex hull of the curve segment.\n \~
    \param[in] seg - \ru Номер сегмента кривой.
                     \en A number of curve segment. \~
    \param[out] poly - \ru Массив точек, составляющих выпуклую оболочку сегмента.
                       \en Array of points which constitute the convex hull of the segment. \~
  */
          void        ConvexHull( ptrdiff_t seg, SArray<MbCartPoint> & poly ) const;
          // \ru Определение особых точек офсетной кривой \en Determination of singular points of the offset curve 
  virtual void        OffsetCuspPoint( SArray<double> & tCusps, double dist ) const;
          /// \ru Вернуть массив отдельных сегментов Bezier-кривой. \en Return an array of separate segments of the Bezier-curve. 
          void        GetSegments( RPArray<MbBezier> & segments ) const;
          /// \ru Удалить совпадающие точки. \en Delete coincident points. 
          void        ExeptEqualPoints(); 

  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const;  // \ru Проверка вырожденности кривой \en Check for curve degeneracy 
          /// \ru Сделать контур из NURBS-кривой. \en Create a contour from the NURBS curve. 
          MbContour * CreateContour() const; 

  // \ru Функции только Bezier кривой \en Functions for Bezier curve           

  /** \brief \ru Выделить часть кривой Безье.
             \en Allocate a part of the Bezier curve. \~
    \details \ru Создается новая кривая - часть кривой Безье между параметрами t1 и t2.
             \en The new curve is created - a part of the Bezier curve between t1 and t2 parameters. \~
    \param[out] trimPart - \ru Созданная кривая.
                           \en Created curve. \~
    \param[in] t1 - \ru Параметр начала выделенной части.
                    \en A beginning parameter. \~
    \param[in] t2 - \ru Параметр конца выделенной части.
                    \en An end parameter. \~
    \result \ru true - если построение прошло успешно.
            \en True - if construction has been successfully. \~ 
  */
          bool        Break( MbBezier & trimPart, double t1, double t2 ) const; // \ru Выделить часть \en Break a part 
          void        SetBezierSplines();  ///< \ru Вычислить параметры кривой-Bezier. \en > Calculate parameters of the Bezier curve. 
          int         GetFormType() const { return form; } ///< \ru Вернуть форму сплайна. \en Return the spline shape. 
          void        SetFormType( int newForm );          ///< \ru Установить форму сплайна. \en Set the spline shape. 
          ptrdiff_t   GetSplinesCount() const { return splinesCount; } ///< \ru Количество сплайнов \en The number of splines 

  /** \brief \ru Выделить часть кривой Безье.
             \en Break a part of the Bezier curve. \~
    \details \ru Создается новая кривая - часть кривой Безье между параметрами t1 и t2.
             \en The new curve is created - a part of the Bezier curve between t1 and t2 parameters. \~
    \param[out] trimm - \ru Созданная кривая.
                        \en Created curve. \~
    \param[in] t1 - \ru Параметр начала выделенной части.
                    \en A beginning parameter. \~
    \param[in] t2 - \ru Параметр конца выделенной части.
                    \en An end parameter. \~
    \param[in] sense - \ru Совпадает ли направление полученной кривой с направлением исходной кривой.
                       \en Whether the direction of the resulting curve coincides with the direction of the original curve. \~
  */
          void        Trimm( MbBezier & trimm, double t1, double t2, int sense ) const;

  virtual bool        DistanceToPointIfLess( const MbCartPoint & to, double &d ) const; // \ru Расстояние до точки, если оно меньше d \en Distance to the point if it is less than d 

  /** \brief \ru Вычислить все базовые функции в точке.
             \en Calculate all base functions in the point. \~
    \details \ru При заданном параметре вычисляются все базовые функции сплайна и 
      индекс первой характерной точки, от которой зависит поведение сплайна 
      при заданном параметре.
             \en For a given parameter, are calculated all base functions of the spline and 
      the index of the first characteristic point which determines the behavior of the spline 
      at a given parameter. \~
    \param[in] t - \ru Параметр.
                   \en A parameter. \~
    \param[out] values - \ru Массив со значениями базовых функций в точке.
                         \en An array with values of base functions in the point. \~
    \param[in] left - \ru Индекс характерной точки - начала интервала влияния.
                      \en An index of characteristic point. \~
    \result \ru true - если операция прошла успешно.
            \en True - if operation has been successfully. \~ 
  */
          bool        BasicFunctions( double & t, CcArray<double> & values, ptrdiff_t & left ) const;

  // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double      CalculateMetricLength() const; 
  // \ru Сдвинуть параметр t на расстояние len. \en Move parameter t on the metric distance len. 
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const;

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

  /** \} */

protected:
  virtual bool        CanChangeClosed() const; // \ru Можно ли поменять признак замкнутости \en Whether it is possible to change the attribute of closedness 
private :
          void        CheckData( double & t ) const;
          void		    EvaluateSlope  ( ptrdiff_t index ); // \ru Рассчитать производные в полюсе index \en Calculate derivatives at the pole "index" 
          void		    EvaluateSlope0 ( ptrdiff_t index ); // \ru Рассчитать производные в полюсе index для 0-ой формы \en Calculate derivatives at the pole "index" for 0-th form 
          void		    EvaluateSlope1 ( ptrdiff_t index ); // \ru Рассчитать производные в полюсе index для 1-ой формы \en Calculate derivatives at the pole "index" for 1-th form 
          void        SetDerives(); // \ru Рассчитать все производные \en Calculate all derivatives 
          void		    SetDerives ( ptrdiff_t index ); // \ru Рассчитать производные в полюсах при изменении полюса index. \en Calculate derivatives at poles when changing the pole "index". 

          void        operator = ( const MbBezier & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbBezier )
};

IMPL_PERSISTENT_OPS( MbBezier )

#endif // __CUR_BEZIER_H
