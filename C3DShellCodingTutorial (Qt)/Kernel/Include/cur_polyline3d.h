////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Ломаная линия в трехмерном пространстве.
         \en Polyline in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_POLYLINE3D_H
#define __CUR_POLYLINE3D_H


#include <templ_c_array.h>
#include <curve.h>
#include <cur_polycurve3d.h>
#include <vector>


class  MATH_CLASS   MbPolyline;
class  MATH_CLASS   MbItem;


//------------------------------------------------------------------------------
/** \brief \ru Ломаная линия в трехмерном пространстве.
           \en Polyline in three-dimensional space. \~
  \details \ru Ломаная линия в трехмерном пространстве определяется контрольными точками pointList.
    Параметр ломаной в контрольных точках принимают целочисленные значения, начиная с нуля. 
    Ломаная проходит через свои контрольные точки при целочисленных значениях параметра. 
    Параметр ломаной изменяется от нуля до k, 
    где k - количество контрольных точек минус один для не замкнутой ломаной и k - количество контрольных для замкнутой ломаной. 
    Производная ломаной на кождом участке постоянна и равна вектору, построенному между двумя соседними контрольными точками.
           \en Polyline in three-dimensional space is defined by 'pointList' control points.
    Parameters of polyline at control points take on integer values starting from zero. 
    Polyline passes through its control points at integer values of parameter. 
    Parameter of a polyline changes from zero to 'k', 
    where 'k' - count of control points minus one for an open polyline and 'k' - count of control points for a closed polyline. 
    Derivative of polyline is constant at each piece and is equal to vector constructed between two neighboring control points. \~ 
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbPolyline3D : public MbPolyCurve3D {
private :
  ptrdiff_t segmentsCount; ///< \ru Число сегментов ломаной. \en Count of segments of polyline.  

public :
  /// \ru Конструктор отрезка. \en Constructor of a segment.
  MbPolyline3D( const MbCartPoint3D & p1, const MbCartPoint3D & p2 );
  /// \ru Конструктор по набору точек и признаку замкнутости. \en Constructor by points and closedness state.
  MbPolyline3D( const SArray<MbCartPoint3D> & initList, bool cls )
    : MbPolyCurve3D(   )
    , segmentsCount( 0 )
  {
    Init( initList, cls );
  }
  /// \ru Конструктор по набору точек и признаку замкнутости. \en Constructor by points and closedness state.
  MbPolyline3D( const std::vector<MbCartPoint3D> & initList, bool cls )
    : MbPolyCurve3D(   )
    , segmentsCount( 0 )
  {
    Init( initList, cls );
  }
  /// \ru Конструктор по плоской ломаной. \en Constructor by planar polyline.
  MbPolyline3D( const MbPolyline &, const MbPlacement3D & );
  MbPolyline3D( const CcArray<MbCartPoint3D> & initList, ptrdiff_t count, bool cls, double scale ); ///< \ru Используется в конвертере Parasolid. \en Used in converter of Parasolid.
protected :
  // \ru Конструктор копирования. \en Copy constructor.
  MbPolyline3D( const MbPolyline3D & );
public :
  virtual ~MbPolyline3D();

public :
  VISITING_CLASS( MbPolyline3D ); 

          /// \ru Инициализация по другой ломаной. \en Initialization by another polyline.
          void        Init( const MbPolyline3D & );
          /// \ru Инициализация по другой плоской ломаной. \en Initialization by another planar polyline.
          void        Init( const MbPolyline &, const MbPlacement3D & );
          /// \ru Инициализация по точкам и признаку замкнутости. \en Initialization by points and an attribute of closedness.
          template <class Points>
          bool        Init( const Points & initList, bool cls ) {
            if ( initList.size() > 1 ) {
              pointList = initList;
              uppIndex = (ptrdiff_t)pointList.size() - 1;
              closed = cls;
              // if curve is closed then the start and the end points have to be different
              if ( uppIndex>1 && closed && c3d::EqualPoints( pointList.front(), pointList.back(), Math::metricRegion ) ) {
                pointList.erase( pointList.begin() + uppIndex );
                uppIndex--;
              }
              segmentsCount = ( uppIndex > 0 ) ? ( uppIndex + !!closed ) : 0;
              Refresh();
            }
            return false;
          }
          /// \ru Построение прямоугольника. \en Construction of a rectangle. 
          void        Init( const MbCartPoint3D & p1, const MbCartPoint3D & p2 );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool        SetEqual ( const MbSpaceItem & );          // \ru Сделать равным \en Make equal 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             // \ru Преобразовать \en Transform 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const;// \ru Расстояние до точки \en Distance to a point 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 

  // \ru Общие функции полилинии \en Common functions of polyline 

  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const;// \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector3D & ) const; // \ru Первая производная \en The first derivative 
  virtual void        SecondDer( double & t, MbVector3D & ) const; // \ru Вторая производная \en The second derivative 
  virtual void        ThirdDer ( double & t, MbVector3D & ) const; // \ru Третья производная \en The third derivative 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  // \ru Построить NURBS копию кривой \en Create a NURBS copy of the curve 
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const;

  virtual MbCurve3D * TrimmBreak( double t1, double t2, int sense ) const;
          void        Trimm( SArray<MbCartPoint3D> & points, double t1, double t2 ) const;

  virtual double      GetTMin() const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of the parameter 
  virtual double      GetTMax() const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 

  virtual double      Step         ( double t, double sag ) const;    // \ru Шаг параметра с учетом радиуса кривизны \en Step of parameter with consideration of curvature 
  virtual double      DeviationStep( double t, double angle ) const;  // \ru Шаг параметра по заданному углу отклонения касательной \en Step of parameter by a given angle of deviation of tangent 

  virtual void        CalculateGabarit( MbCube & ) const; // \ru Определить габариты кривой \en Determine the bounding box of a curve 
  virtual void        CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system 

  virtual double      CalculateMetricLength() const;      // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual void        GetCentre      ( MbCartPoint3D & wc ) const; // \ru Посчитать центр кривой \en Calculate the center of a curve 
  virtual void        GetWeightCentre( MbCartPoint3D & wc ) const; // \ru Посчитать центр тяжести кривой \en Calculate the gravity center of the curve 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Get the planar curve and placement if the spatial curve is planar (call DeleteItem for two-dimensional curve after using) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;

  // \ru Общие функции полигональной кривой \en Common functions of polygonal curve 

  virtual void        Rebuild(); // \ru Перестроить кривую \en Rebuild curve 
  virtual void        GetRuleInterval( ptrdiff_t index, double & t1, double & t2 ) const; // \ru Выдать интервал влияния точки кривой \en Get the interval of point influence 

  // \ru Функции только 3D кривой \en Functions of 3D curve only 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Ближайшая проекция точки на кривую \en The nearest point projection to the curve 
  virtual void        InsertPoint( ptrdiff_t index, const MbCartPoint3D &         ); // \ru Добавить точку \en Add a point 
  virtual void        InsertPoint( double t,  const MbCartPoint3D &, double ); // \ru Добавить точку \en Add a point 
  virtual bool        CheckParam ( double & t, ptrdiff_t & i0, ptrdiff_t & i1, double & t0, double & t1 ) const; // \ru Установить параметр \en Set parameter 
  virtual double      GetParam( ptrdiff_t i ) const;            // \ru Выдать параметр для точки с номером \en Get parameter for a point with index 

          void        CheckParameter( double & ) const;  ///< \ru Проверка параметра. \en Check parameter. 

  //virtual bool        GoThroughPoint( double t, MbCartPoint3D & p ); // \ru Пройти через точку \en Pass through point 

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL,
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of a curve. 
  virtual MbCurve *   GetMapPsp( const MbMatrix3D &, double zNear, MbRect1D * pRgn = NULL ) const; // \ru Дать перспективную плоскую проекцию кривой. \en Get a planar geometric projection of a curve. 

  virtual size_t      GetCount() const;
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Являются ли стыки контура\кривой гладкими? \en Whether the joints of a contour\curve are smooth. 

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

          bool        UnClamped( bool );
          void        DeleteEqPoints( double absEps ); // \ru Удалить одинаковые точки \en Remove equal points 
          void        AddAt( const MbCartPoint3D & spsP, ptrdiff_t i );
          ptrdiff_t   GetSegmentsCount() const { return segmentsCount; }

private:
          void        operator = ( const MbPolyline3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbPolyline3D )
};

IMPL_PERSISTENT_OPS( MbPolyline3D )

//------------------------------------------------------------------------------
/** \brief \ru Построить пространственный проволочный каркас по полигональному объекту.
           \en Create a spatial wireframe by a mesh \~
  \details \ru Построить набор пространственных кривых, характеризующих полигональных объект. \n
           \en Create a spatial wireframe by a mesh. \n \~
  \ingroup Curves_3D
*/
// ---
MATH_FUNC (void) MakeSpaceWireFrame( const MbItem & item, RPArray<MbCurve3D> & wire );


//------------------------------------------------------------------------------
/** \brief \ru Построить плоский проволочный каркас по полигональному объекту.
           \en Create a planar wireframe by a mesh \~
  \details \ru Построить пространственных набор кривых, являющихся проекциями кривых, характеризующих полигональных объект, на плоскость XY локальной системы координат. \n
           \en Create a planar wireframe by a mesh. \n \~
  \ingroup Curves_3D
*/
// ---
MATH_FUNC (void) MakePlaneWireFrame( const MbItem & item, const MbPlacement3D & place,
                                     RPArray<MbCurve3D> & wire );


//------------------------------------------------------------------------------
/** \brief \ru Построить плоский проволочный каркас по полигональному объекту в перспективе.
           \en Create a planar wireframe by a mesh in perspective \~
  \details \ru Построить пространственных набор кривых, являющихся проекциями кривых в перспективе, характеризующих полигональных объект, на плоскость XY локальной системы координат. \n
           \en Create a planar wireframe by a mesh in perspective. \n \~
  \ingroup Curves_3D
*/
// ---
MATH_FUNC (void) MakePlaneVistaWireFrame( const MbItem & item, const MbPlacement3D & place, 
                                          const MbCartPoint3D & vista, RPArray<MbCurve3D> & wire );


//------------------------------------------------------------------------------
/** \brief \ru Построить плоский проволочный каркас по полигональному объекту.
           \en Create a planar wireframe by a mesh \~
  \details \ru Построить набор двумерных кривых, являющихся проекциями пространственных кривых, характеризующих полигональных объект, на плоскость XY локальной системы координат. \n
           \en Create a planar wireframe by a mesh. \n \~
  \ingroup Curves_3D
*/
// ---
MATH_FUNC (void) MakePlaneWireFrame( const MbItem & item, const MbPlacement3D & place,
                                     RPArray<MbCurve> & wire );


//------------------------------------------------------------------------------
/** \brief \ru Построить плоский проволочный каркас по полигональному объекту в перспективе.
           \en Create a planar wireframe by a mesh in perspective \~
  \details \ru Построить набор двумерных кривых, являющихся проекциями в перспективе пространственных кривых, характеризующих полигональных объект, на плоскость XY локальной системы координат. \n
           \en Create a planar wireframe by a mesh in perspective. \n \~
  \ingroup Curves_3D
*/
// ---
MATH_FUNC (void) MakePlaneVistaWireFrame( const MbItem & item, const MbPlacement3D & place,
                                          const MbCartPoint3D & vista, RPArray<MbCurve> & wire );


#endif // __CUR_POLYLINE3D_H
