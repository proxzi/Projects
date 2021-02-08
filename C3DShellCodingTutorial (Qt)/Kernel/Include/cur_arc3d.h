////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Эллипс в трёхмерном пространстве.
         \en Ellipse in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_ARC3D_H
#define __CUR_ARC3D_H


#include <curve3d.h>
#include <mb_placement3d.h>


#define CONIC_COUNT 32
#define LINES_COUNT 10


class  MATH_CLASS MbArc;


//------------------------------------------------------------------------------
/** \brief \ru Дуга эллипса в трёхмерном пространстве.
           \en Elliptical arc in three-dimensional space. \~
  \details \ru Дуга эллипса описывается двумя радиусами a и b и двумя параметрами trim1 и trim2, заданными в локальной системе координат position. \n
    Параметры trim1 и trim2 отсчитываются по дуге в направлении движения от оси position.axisX к оси position.axisY. 
    Параметры trim1 и trim2 будем называть параметрами усечения. 
    Значения параметров усечения, равные нулю и 2pi, соответствуют точке на оси position.axisX. \n
    Параметр кривой t принимает значения на отрезке: 0<=t<=trim2–trim1. 
    Кривая может быть замкнутой. У замкнутой кривой trim2–trim1=2pi. \n
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией\n
    r(t) = position.origin + (a cos(trim1+t) position.axisX) + (b sin(trim1+t) position.axisY).\n
    Радиусы кривой дожны быть больше нуля: a>0, b>0. \n
    Для параметров усечения должны соблюдаться неравенства: trim1<trim2. \n
    Локальная система координат position может быть как правой, так и левой. \n
           \en The elliptical arc is described by two radii a and b and two parameters trim1 and trim2 given in the local coordinate system 'position'. \n
    Parameters 'trim1' and 'trim2' are measured along the arc in direction from position.axisX axis to position.axisY axis. 
    Parameters 'trim1' and 'trim2' will be called parameters of trimming. 
    Values of parameters of trimming equal to 0 and 2pi correspond to a point on position.axisX axis. \n
    Parameter t of curve possesses the values in the range: 0<=t<=trim2-trim1. 
    The curve can be closed. For closed curve: trim2-trim1=2pi. \n
    Radius-vector of the curve in the method PointOn(double&t,MbCartPoint3D&r) is described by the function\n
    r(t) = position.origin + (a cos(trim1+t) position.axisX) + (b sin(trim1+t) position.axisY).\n
    Radii of the curve must be positive: a>0, b>0. \n
    The following inequalities must be satisfied for the parameters of trimming: trim1<trim2. \n
    Local coordinate system 'position' can be both right and left. \n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbArc3D : public MbCurve3D {
protected :
  MbPlacement3D position; ///< \ru Локальная система координат. \en Local coordinate system.  
  double        a;        ///< \ru Радиус полуоси вдоль X. \en Radius of semiaxis along X. 
  double        b;        ///< \ru Радиус полуоси вдоль Y. \en Radius of semiaxis along Y. 
  double        trim1;    ///< \ru Параметры начальной точки. \en The start point parameters. 
  double        trim2;    ///< \ru Параметры конечной  точки. \en The end point parameters. 
  bool          closed;   ///< \ru Замкнутость. \en Closedness. 

public :
  /** \brief \ru Конструктор дуги эллипса.
             \en Constructor of an elliptical arc. \~
    \details \ru Создается дуга эллипса с заданными полуосями и локальной системой координат. 
      angle определяет угол дуги. Угол отсчитываются от оси OX против часовой стрелки. 
      Угол задан в радианах.
             \en An elliptical arc is created with the given semiaxes and the local coordinate system. 
      'angle' determines the arc angle. The angle is measured from the OX axis counterclockwise. 
      The angle is given in radians. \~
    \param[in] place - \ru Локальная система координат эллипса.
                       \en The local coordinate system of the ellipse. \~
    \param[in] aa - \ru Радиус полуоси вдоль X.
                    \en Radius of semiaxis along X. \~
    \param[in] bb - \ru Радиус полуоси вдоль Y.
                    \en Radius of semiaxis along Y. \~
    \param[in] angle - \ru Угол, определяющий конец дуги.
                       \en An angle specifying the end of the arc. \~
  */
  MbArc3D( const MbPlacement3D & place, double aa, double bb, double angle );

  /** \brief \ru Конструктор эллипса, окружности или их дуг.
             \en Constructor of an ellipse, a circle or an elliptical or circular arc. \~
    \details \ru Создается дуга с центром в точке pc. \n
      Первая полуось определяется как расстояние между точками pc и p1.
      Вторая полуось определяется как длина проекции вектора из pс в p2 на перпендикуляр к (p1 - pc). 
      Начальная точка дуги лежит на луче, выходящем из центра окружности и проходящем через точку p1.
      Конечная точка - на луче из центра, проходящем через точку p2.  \n
      Параметр initSense определяет цельность и направление дуги. 
      Если initSense == 0, то строится полный эллипс или окружность. \n
      Если initSense > 0, то направление движения против часовой стрелки, если смотреть навстречу векторному произведению (p1 - pc) и (p2 - pc). \n
      Если initSense < 0, то направление движения против часовой стрелки, если смотреть навстречу векторному произведению (p1 - pc) и (p2 - pc). \n
             \en An arc centered in point 'pc' is created. \n
      The first semiaxis is determines as the distance between points pc and p1.
      The second semiaxis is determined as the length of projection of the vector from pc to p2 onto the perpendicular to (p1 - pc). 
      The start point of the arc lies on the ray starting from the circle center and passing through point 'p1'.
      The end point is on the ray from the center passing through the point 'p2'.  \n
      Parameter 'initSense' specifies completeness and the arc direction. 
      If initSense == 0, then the complete ellipse or circle is constructed. \n
      If initSense > 0, then the direction of moving is counterclockwise if seeing against the vector product (p1 - pc) and (p2 - pc). \n
      If initSense < 0, , then the direction of moving is counterclockwise if seeing against the vector product (p1 - pc) and(p2 - pc). \n \~
    \param[in] pc - \ru Центр эллипса или окружности.
                    \en Center of the ellipse or the circle. \~
    \param[in] p1 - \ru Точка, определяющая начало кривой и первую полуось.
                    \en A point determining the beginning of the curve and the first semiaxis. \~
    \param[in] p2 - \ru Точка, определяющая конец кривой и вторую полуось.
                    \en A point determining the end of the curve and the second semiaxis. \~
    \param[in] initSense - \ru Определяет цельность и направление. initSense == 0 - замкнутая кривая initSense > 0 - движение против часовой стрелки, initSense < 0 - по часовой стрелке.
                           \en Determines the completeness and the direction. initSense == 0 - closed curve initSense > 0 - moving counterclockwise, initSense < 0 - clockwise. \~
  */
  MbArc3D( const MbCartPoint3D & pc, const MbCartPoint3D & p1, const MbCartPoint3D & p2, int initSense = 0 );

  /** \brief \ru Конструктор окружности или дуги окружности.
             \en Constructor of a circle or a circular arc. \~
    \details \ru Конструктор окружности или дуга окружности одним из двух способов.
             \en Constructor of a circle or a circular arc by one of two methods.
    \param[in] p0 - \ru Центр (n == 0) или начальная точка (n != 0).
                    \en Center (n == 0) or starting point (n != 0). \~
    \param[in] p1 - \ru Начальная точка (n == 0) или точка, через которую проходит окружность (n != 0).
                    \en Starting point (n == 0) or point the circle passes through (n == 1). \~
    \param[in] p2 - \ru Точка, определяющая конец кривой и вторую полуось.
                    \en A point determining the end of the curve and the second semiaxis. \~
    \param[in] n  - \ru Определяет способ построения окружности.
                        Если n == 0, то окружность или дуга имеют центр в точке p0.
                        Если n == 1, то окружность или дуга проходят по трем заданным точкам. \n
                        Если |n| == 2 и closed == false, то дуга будет дополнять до полной окружности дугу, проходящую по трем заданным точкам. \n
                    \en The parameter defines the method of arc construction. \~
                        If n == 0, then a circle or a circular arc have the center in point p0.
                        If n == 1, then a circle or an arc passes through the specified three points. \n 
                        If |n| == 2 & closed == false, then an arc passes through p0 and p2 but not p1. \n \~
    \param[in] closed - \ru Определяет окружность (true) или дугу (false).
                        \en Specifies a circle (true) or an arc (false). \~
  */
  MbArc3D( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, int n, bool closed );

  /** \brief \ru Конструктор окружности или дуги окружности.
             \en Constructor of a circle or a circular arc. \~
    \details \ru Создается дуга окружности с центром в точке pc и с заданным радиусом.
      Радиус окружности или ее дуги определяется как расстояние между точками pc и p1.
      Точки pc, p1 и p2 определяют плоскость дуги. 
      Точки p1 и p2 определяют границы дуги. 
      Вектор aZ определяет направление оси Z локальной системы координат дуги окружности. 
      Начальная точка дуги лежит в точке p1.
      Конечная точка дуги лежит на луче, выходящем из центра окружности и проходящем через точку p2. 
      Параметр initSense определяет направление дуги. 
             \en A circular arc is created with a center in point 'pc'.
      Points 'p1' and 'p2' specify the bounds of arc. 
      The start point of the arc lies on point 'p1'.
      The end point is on the ray passing through the point 'p2'. 
      Parameter 'initSense' specifies the arc direction. \~
    \param[in] pc - \ru Центр окружности.
                    \en Center of circle. \~
    \param[in] p1 - \ru Точка, определяющая начало дуги.
                    \en A point specifying the beginning of the arc. \~
    \param[in] p2 - \ru Точка, определяющая конец дуги.
                    \en A point specifying the end of the arc. \~
    \param[in] aZ - \ru Направление оси Z локальной системы координат дуги окружности.
                    \en A direction of axis Z local coordinate system of the arc. \~
    \param[in] initSense - \ru Направление дуги.
                    Если initSense > 0, то направление движения дуги против часовой стрелки, если cмотреть навстречу вектору aZ.
                    Если initSense < 0, то направление движения дуги по часовой стрелке, если cмотреть навстречу вектору aZ.
                    Если initSense == 0, то будет построена полная окружность.
                           \en Arc direction. 
                    If initSense > 0, then the orientation is counterclockwise if you look towards the vector aZ.  
                    If initSense < 0, then the orientation is clockwise if you look towards the vector aZ.
                    If initSense = 0, then the circle is building. \~
  */
  MbArc3D( const MbCartPoint3D & pc, const MbCartPoint3D & p1, const MbCartPoint3D & p2, 
           const MbVector3D & aZ, int initSense );

  /** \brief \ru Конструктор дуги эллипса.
             \en Constructor of an elliptical arc. \~
    \details \ru Создается дуга эллипса с заданными полуосями и локальной системой координат. 
      angle определяет угол дуги. Угол отсчитываются от оси OX против часовой стрелки. 
      Угол задан в радианах.
             \en An elliptical arc is created with the given semiaxes and the local coordinate system. 
      'angle' determines the arc angle. The angle is measured from the OX axis counterclockwise. 
      The angle is given in radians. \~
    \param[in] p0 - \ru Центр локальной системы координат эллипса.
                    \en The ellipse local coordinate system center. \~
    \param[in] vZ - \ru Ось Z локальной системы координат эллипса.
                    \en Z-axis of the local coordinate system of the ellipse. \~
    \param[in] vX - \ru Ось X локальной системы координат эллипса.
                    \en X-axis of the local coordinate system of the ellipse. \~
    \param[in] aa - \ru Радиус полуоси вдоль X.
                    \en Radius of semiaxis along X. \~
    \param[in] bb - \ru Радиус полуоси вдоль Y.
                    \en Radius of semiaxis along Y. \~
    \param[in] angle - \ru Угол, определяющий конец дуги.
                       \en An angle specifying the end of the arc. \~
  */
  MbArc3D( const MbCartPoint3D & p0, const MbVector3D & vZ, const MbVector3D & vX, double aa, double bb, double angle );

  /** \brief \ru Конструктор дуги эллипса.
             \en Constructor of an elliptical arc. \~
    \details \ru Создается дуга эллипса с локальной системой координат и полуосями заданного эллипса.
      t1 и t2 определяют начальный и конечный углы дуги. Углы отсчитываются от оси OX против часовой стрелки. 
      Углы заданы в радианах.
      Параметр initSense определяет направление дуги. Если initSense > 0, то направление движения против часовой стрелки.
             \en An elliptical arc is constructed with the local coordinate system and semiaxes of the given ellipse.
      t1 and t2 specify the start and the end angles of the arc. The angles are measured from the OX axis counterclockwise. 
      The angles are given in radians.
      Parameter 'initSense' specifies the arc direction. If initSense > 0, then the direction of moving is counterclockwise. \~
    \param[in] init - \ru Эллипс - образец.
                      \en A pattern ellipse. \~
    \param[in] t1 - \ru Угол, определяющий начало дуги.
                    \en An angle specifying the beginning of the arc. \~
    \param[in] t2 - \ru Угол, определяющий конец дуги.
                    \en An angle specifying the end of the arc. \~
    \param[in] initSense - \ru Направление. initSense > 0 - движение против часовой стрелки, initSense < 0 - по часовой стрелке.
      initSense не должно быть равным нулю.
                       \en Direction. initSense > 0 - moving counterclockwise, clockwise < 0 - clockwise.
      'initSense' can't be equal to zero. \~
  */
  MbArc3D( const MbArc3D & init, double t1, double t2, int initSense ); 

  /** \brief \ru Конструктор дуги эллипса.
             \en Constructor of an elliptical arc. \~
    \details \ru Создается дуга эллипса с локальной системой координат и полуосями заданного эллипса.
      Проекции p1 и p2 на init определяют начальный и конечный углы дуги. 
      Параметр initSense определяет направление дуги. Если initSense > 0, то направление движения против часовой стрелки.
             \en An elliptical arc is constructed with the local coordinate system and semiaxes of the given ellipse.
      Projections of p1 and p2 onto 'init' determines the starting and the end angles of the arc. 
      Parameter 'initSense' specifies the arc direction. If initSense > 0, then the direction of moving is counterclockwise. \~
    \param[in] init - \ru Эллипс - образец.
                      \en A pattern ellipse. \~
    \param[in] p1 - \ru Точка, определяющая начало дуги.
                    \en A point specifying the beginning of the arc. \~
    \param[in] p2 - \ru Точка, определяющая конец дуги.
                    \en A point specifying the end of the arc. \~
    \param[in] initSense - \ru Направление. initSense > 0 - движение против часовой стрелки, initSense < 0 - по часовой стрелке.
      initSense не должно быть равным нулю.
                       \en Direction. initSense > 0 - moving counterclockwise, clockwise < 0 - clockwise.
      'initSense' can't be equal to zero. \~
  */
  MbArc3D( const MbArc3D & init, MbCartPoint3D p1, MbCartPoint3D p2, int initSense );

  /** \brief \ru Конструктор дуги окружности.
             \en Constructor of a circular arc. \~
    \details \ru Создается дуга окружности с концами в заданных точках. 
      Радиус окружности определяется по заданному тангенсу 1/4 угла раствора дуги.
             \en An arc is created with ends at the given points. 
      A circle radius is defined by the given tangent of 1/4 of arc opening angle. \~
    \param[in] p1 - \ru Начало дуги.
                    \en Beginning of the arc. \~
    \param[in] p2 - \ru Конец дуги.
                    \en End of the arc. \~
    \param[in] a4 - \ru Тангенс 1/4 угла раствора дуги.
                    \en Tangent of 1/4 of the arc opening angle. \~
    \param[in] vZ - \ru Ось дуги.
                    \en Axis of the arc. \~
  */
  MbArc3D( const MbCartPoint3D & p1, const MbCartPoint3D & p2, double a_4, MbVector3D & vZ ); 

  /** \brief \ru Конструктор по локальной системе и двумерной дуге эллипса.
             \en Constructor by a local system and two-dimensional elliptical arc. \~
    \details \ru Конструктор по локальной системе координат и двумерной дуге эллипса.
             \en Constructor by a local coordinate system and two-dimensional elliptical arc. \~ 
    \param[in] ellipse - \ru Двумерная дуга эллипса.
                         \en Two-dimensional elliptical arc. \~
    \param[in] place - \ru Локальная система координат.
                       \en A local coordinate system. \~
  */
  MbArc3D( const MbArc & ellipse, const MbPlacement3D & place );

  /** \brief \ru Конструктор окружности по двум точкам и направлению к центру в одной из них.
             \en Constructor of a circle by two points and direction to the center from one of them. \~
    \details \ru Создается окружность по двум точкам и направлению в одной из них.
             \en A circle is created by two points and direction at one of them. \~ 
    \param[in] p1 - \ru Начальная точка.
                    \en The starting point. \~
    \param[in] p2 - \ru Конечная точка.
                    \en The end point. \~
    \param[in] dirInPoint - \ru Направление из одной из точек (p1 или p2) к центру окружности.
                            \en Direction at one of points (p1 or p2) to the center of the circle. \~
    \param[in] insecond - \ru Направление из первой точки (insecond == true) к центру окружности.
                          \en Direction from the first point (insecond == true) to the circle center. \~
  */
  MbArc3D( const MbCartPoint3D & p1, const MbCartPoint3D & p2, const MbVector3D & dirInPoint, bool insecond );

//protected:
  explicit MbArc3D( const MbArc3D & init );
public :
  virtual ~MbArc3D();

  VISITING_CLASS( MbArc3D );

          void    Init( const MbArc3D & );
          void    Init( const MbPlacement3D &, double aa, double bb, double angle );
          void    Init( const MbArc3D & init, double t1, double t2, int initSense );
          /// \ru Инициализация окружности или дуги окружности по трем точкам, (n == 0) - окружность или дуга по центру и двум точкам, (n == 1) - окружность или дуга по трем точкам \en Initialization of a circular arc by three points; (n == 0) - a circle or an arc by the center and two points, (n == 1) - a circle or an arc by three points.
          void    Init( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, int n, bool closed ); 
          /// \ru Инициализация дуги окружности по начальной и конечной точкам и 1/2 угла раствора дуги. \en Initialization of a circular arc by the starting and the end points and 1/2 of the arc opening angle. 
          void    Init( double a_2, const MbCartPoint3D & p1, const MbCartPoint3D & p2, MbVector3D & vZ ); 
          /// \ru Инициализация дуги окружности по 2D-дуге и локальной системе координат. \en Initialization of an arc by 2D-arc and local coordinate system. 
          void    Init( const MbArc & ellipse, const MbPlacement3D & pos );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 
  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */
  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );          // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual ( const MbSpaceItem & ); // \ru Сделать равным \en Make equal 
  virtual double  DistanceToPoint( const MbCartPoint3D & ) const;// \ru Расстояние до точки \en Distance to a point 
  virtual bool    IsSpaceSame( const MbSpaceItem & item, double eps = METRIC_REGION ) const; // \ru Являются ли объекты идентичными в пространстве \en Whether the objects are identical in the space 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  /** \} */
  // \ru Общие функции кривой \en Common functions of the curve 
  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for curve domain description
      \{ */
  virtual double  GetTMax()  const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double  GetTMin()  const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double  GetPeriod() const; // \ru Вернуть период \en Return the period  
  /** \} */
  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the domain of a curve. 
            PointOn, FirstDer, SecondDer, ThirdDer,... functions correct parameter
            when it runs out the domain.
      \{ */
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double & t, MbVector3D & ) const;    // \ru Первая производная \en The first derivative 
  virtual void    SecondDer( double & t, MbVector3D & ) const;    // \ru Вторая производная \en The second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & ) const;    // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void    Normal   ( double & t, MbVector3D & ) const;    // \ru Вектор главной нормали \en Vector of the principal normal 
  /** \} */
  /** \ru \name Функции для работы внутри и вне области определения кривой. 
            Функции _PointOn, _FirstDer, _SecondDer, _ThirdDer,... не корректируют параметр
            при выходе за пределы области определения. Ограниченная кривая продолжается в соответствии с уравнениями кривой.
      \en \name Functions for working inside and outside of the curve domain. 
            _PointOn, _FirstDer, _SecondDer, _ThirdDer,... functions don't correct parameter
            when it runs out the domain. The bounded curve is extended due to the equations of curve.
      \{ */
  virtual void   _PointOn  ( double t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void   _FirstDer ( double t, MbVector3D & ) const;  // \ru Первая производная \en The first derivative 
  virtual void   _SecondDer( double t, MbVector3D & ) const;  // \ru Вторая производная \en The second derivative 
  virtual void   _ThirdDer ( double t, MbVector3D & ) const;  // \ru Третья производная по t \en The third derivative with respect to t 
  virtual void   _Normal   ( double t, MbVector3D & ) const;// \ru Вектор главной нормали \en Vector of the principal normal 
  /** \} */
  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;
  /** \} */
  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double  DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double  MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  // \ru Все проекции точки на кривую \en All the projections of a point onto the curve 
  virtual bool    NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Ближайшая проекция точки на кривую \en The closest projection of a point onto the curve 

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить Nurbs-копию кривой \en Construct NURBS-copy of the curve 
  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of the trimmed curve 

  virtual double  CalculateMetricLength() const; // \ru Посчитать метрическую длину \en Calculate metric length 
  virtual double  GetLengthEvaluation() const;
  virtual double  Curvature( double t ) const; // \ru Кривизна по t \en Curvature by t 
  // \ru Сдвинуть параметр t на расстояние len по направлению \en Shift the parameter t by the distance 'len' in the direction 
  virtual bool    DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                 VERSION version = Math::DefaultMathVersion() ) const; 
  virtual size_t  GetCount() const;
  virtual void    GetPointsByEvenLengthDelta( size_t n,  std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curves equally spaced by the arc length 

  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of a curve 
  virtual MbCurve * GetMapPsp( const MbMatrix3D &, double zNear, 
                               MbRect1D * pRgn = NULL ) const;

  virtual double  GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool    GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой \en Get the axis of the curve 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Get a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called on a three-dimensional curve) 
  virtual bool    GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;

  virtual void    CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой \en Calculate bounding box of curve 
  virtual void    CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to local coordinate system 
  /// \ru Является ли объект смещением \en Whether the object is a shift 
  virtual bool    IsShift ( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 

          void    SetRadiusA( double aa ) { a = aa; Refresh(); }  // \ru Установить большую полуось \en Set the major semiaxis 
          void    SetRadiusB( double bb ) { b = bb; Refresh(); }  // \ru Установить малую полуось \en Set the minor semiaxis 
          void    SetRadius( double r ) { a = r; b = r; Refresh(); } // \ru Установить радиус окружности \en Set circle radius 
          double  GetRadiusA() const { return a; }
          double  GetRadiusB() const { return b; }
          void    SetLimitPoint( ptrdiff_t number, const MbCartPoint3D & );   // \ru Заменить точку отрезка \en Replace a point of the segment 
          double  GetAngle() const { return (trim2 - trim1); } // \ru Выдать граничный угол дуги \en Get the end angle of the arc 
          void    SetAngle ( double ang ) { trim2 = trim1 + ang; CheckClosed(); Refresh(); } // \ru Изменить граничный угол дуги \en Change the end angle of the arc 

          bool    IsCircle( double eps = Math::metricRegion ) const;
          
  inline  double  CheckParam( double & t ) const;
  inline  void    ParamToAngle( double & t ) const;    // \ru Перевод параметра кривой в угол \en Convert parameter of curve to the angle 
  inline  void    AngleToParam( double & t ) const;    // \ru Перевод угла кривой в параметр кривой \en Convert an angle of curve to a parameter of curve 
  inline  double  GetTrim1() const { return trim1; }   ///< \ru Параметры начальной точки \en Parameters of start point 
  inline  double  GetTrim2() const { return trim2; }   ///< \ru Параметры конечной точки \en Parameters of end point 
          bool    MakeTrimmed( double t1, double t2 ); ///< \ru Установка параметров усечения с сохранением направления кривой. \en Setting of the parameters of trimming with keeping the curve direction. 
          void    AlignXAxis();                        ///< \ru Повернуть плейсмент круговой дуги так, чтобы ось ox указывала в начальную точку дуги. \en Rotate the placement of a circular arc so as the ox-axis points to the start point of the arc. 

  /// \ru Является ли кривая плоской? \en Whether the curve is planar? 
  virtual bool    IsPlanar() const;
  /// \ru Заполнить плейсемент, если кривая плоская. \en Fill the placement if a curve is planar. 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

  const   MbPlacement3D & GetPlacement() const { return position; }
          MbPlacement3D & SetPlacement() { return position; }
          void    SetPlacement( const MbPlacement3D & pl ) { position = pl; }
  virtual void    GetCentre( MbCartPoint3D & wc ) const;
  virtual void    GetWeightCentre( MbCartPoint3D & wc ) const;

          bool    Normalize(); ///< \ru Ортонормировать локальную систему координат. \en Orthonormalize the local coordinate system. 
          bool    IsPositionNormal()    const { return ( !position.IsAffine()   ); }
          bool    IsPositionCircular()  const { return (  position.IsCircular() ); }
          bool    IsPositionIsotropic() const { return (  position.IsIsotropic()); }

  const   MbCartPoint3D & GetCentre() const { return position.GetOrigin(); }

private:
          void    CheckClosed(); // \ru Проверить и установить признак замкнутости кривой. \en Check and set attribute of curve closedness. 

private:
          void    operator = ( const MbArc3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbArc3D )
};

IMPL_PERSISTENT_OPS( MbArc3D )

//------------------------------------------------------------------------------
// \ru Установить параметр в область допустимых значений \en Set the parameter into the region of the legal values 
// ---
inline double MbArc3D::CheckParam( double & t ) const
{
  double tMax = trim2 - trim1;
  if ( (t < 0.0) || (t > tMax) ) {
    if ( closed ) 
      t -= ::floor( t * Math::invPI2 ) * M_PI2;
    else if ( t < 0.0 )
      t = 0.0;
    else if ( t > tMax )
      t = tMax;
  }
  double w = t;
  if ( ::fabs(trim1) > NULL_EPSILON ) {
    w = trim1 + w;
    if ( (w < 0.0) || (w > M_PI2) ) 
      w -= ::floor( w * Math::invPI2 ) * M_PI2;
  }
  return w;
}


//------------------------------------------------------------------------------
// \ru Перевод параметра кривой в угол \en Convert parameter of curve to the angle 
// ---
inline void MbArc3D::ParamToAngle( double & t ) const
{
  if ( ::fabs(trim1) > NULL_EPSILON ) {
    t = trim1 + t;
    if ( (t < 0.0) || (t > M_PI2) ) 
      t -= ::floor( t * Math::invPI2 ) * M_PI2;
  }
}


//------------------------------------------------------------------------------
// \ru Перевод угла кривой в параметр кривой \en Convert an angle of curve to a parameter of curve 
// ---
inline void MbArc3D::AngleToParam( double & t ) const
{
  if ( ::fabs(trim1) > NULL_EPSILON ) {
    double dtr = ( trim2 + trim1 - M_PI2 ) * 0.5;
    t -= ::floor( (t - dtr) * Math::invPI2 ) * M_PI2;
    t = t - trim1;
  }
}


#endif // __CUR_ARC3D_H
