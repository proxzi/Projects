////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Набор В-сплайнов NURBS кривой.
         \en B-spline set of NURBS-curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_B_SPLINE_H
#define __CUR_B_SPLINE_H


#include <mb_placement3d.h>
#include <curve3d.h>


class  MATH_CLASS MbNurbs3D;
class  MATH_CLASS MbNurbs;


//------------------------------------------------------------------------------
/** \brief \ru Набор В-сплайнов NURBS кривой.
           \en B-spline set of NURBS-curve. \~
  \details \ru Объект со свойствами кривой служит для визуализации набора В-сплайнов некоторой NURBS кривой. \n
    В-сплайны NURBS кривой располагаются в плоскости XY локальной системы координат position.
    Длина рисунка всех В-сплайнов равна параметру a, высота рисунка всех В-сплайнов равна параметру h.
           \en Object with curve properties is used to visualize B-spline set of some NURBS-curve. \n
    B-splines of NURBS-curve are located in the XY plane of the local coordinate system.
    Picture length of all B-splines is equal to the parameter a, the height of all B-splines is the parameter h. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbBSpline : public MbCurve3D {
private:
  ptrdiff_t      degree;   ///< \ru Степень В-сплайнов. \en Degree of B-splines. 
  SArray<double> knots;    ///< \ru Узловой вектор. \en Knot vector. 
  ptrdiff_t      pCount;   ///< \ru Число точек. \en Number of points. 
  bool           closed;   ///< \ru Признак замкнутости кривой. \en An attribute of curve closedness. 
  MbPlacement3D  position; ///< \ru Плоскость для отрисовки. \en A plane for drawing. 
  double         a;        ///< \ru Горизонтальный размер (длина  рисунка). \en Horizontal size (picture length). 
  double         h;        ///< \ru Вертикальный  размер (высота рисунка). \en Vertical size (picture height). 

public:
  MbBSpline( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, const MbNurbs & nurbs );
  MbBSpline( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, const MbNurbs3D & nurbs );
  MbBSpline( const MbCartPoint3D & p0, const MbCartPoint3D & p1, const MbCartPoint3D & p2, const SArray<double> & t );
private:
  MbBSpline( const MbBSpline & init );
public:
  virtual ~MbBSpline();

public:
  VISITING_CLASS( MbBSpline );

  // \ru Общие функции математического объекта \en The common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual( const MbSpaceItem & init );           // \ru Сделать равным \en Make equal 
  virtual void    Transform( const MbMatrix3D & matr, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move( const MbVector3D & to, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate( const MbAxis3D & axis, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMin() const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax() const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn  ( double &t, MbCartPoint3D &pnt ) const; // \ru Точка на кривой \en The point on the curve 
  virtual void    FirstDer ( double &t, MbVector3D &fd ) const;     // \ru Первая производная \en First derivative 
  virtual void    SecondDer( double &t, MbVector3D &sd ) const; // \ru Вторая производная \en Second derivative 
  virtual void    ThirdDer ( double &t, MbVector3D &td ) const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual double  Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculate step of approximation 

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 

          void    CalculateOnePolygon( size_t i, const MbStepData & stepData, MbPolygon3D * polygon ) const; // \ru Pассчитать полигон по параметру T \en Calculate polygon of the parameter T 
          // \ru Расчет весовых функций и их первых, вторых и третьих производных \en Calculation of the weight functions and their first, second and third derivatives 
          ptrdiff_t CalculateFunctions( double x, double * m, 
                                        double * mm0, double * mm1, double * mm2, double * mm3 ) const;
          ptrdiff_t CalculateParam( double & t, double & x ) const; // \ru Расчет параметра и номера сплайна \en Calculation of the parameter and spline number 
          void    GetWeightFunctions( double t, double * m, 
                                      double * mm0, double * mm1, double * mm2, double * mm3 ) const; // \ru Определение В-сплайнов \en Definition of B-splines 

private:
          void    operator = ( const MbBSpline & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbBSpline )
}; // MbBSpline

IMPL_PERSISTENT_OPS( MbBSpline )

#endif // __CUR_B_SPLINE_H
