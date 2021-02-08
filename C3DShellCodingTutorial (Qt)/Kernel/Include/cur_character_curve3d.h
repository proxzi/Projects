////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кривая, координатные функции которой заданы в символьном виде.
         \en Functionally defined curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CHARCTER_CURVE3D_H
#define __CUR_CHARCTER_CURVE3D_H


#include <curve3d.h>
#include <mb_placement3d.h>
#include <mb_matrix3d.h>
#include <mb_cube.h>
#include <vector>


class  MATH_CLASS  MbFunction;
class  MATH_CLASS  MbCharacterCurve;


//------------------------------------------------------------------------------
/** \brief \ru Кривая, координатные функции которой заданы в символьном виде.
           \en Functionally defined curve. \~
  \details \ru Координатные функции кривой заданы в виде пользовательских функций общего параметра t. 
    Каждая координата кривой описана своей функцией в виде строкового выражения. 
    Параметр кривой, он же параметр координатных функций, изменяется на отрезке [tmin tmax]. \n
    Все пользовательские функции заданы в локальной системе координат position.
    Система координат может быть декартовой, цилиндрической или сферической.
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией: \n
    r(t) = position.origin + (position.axisX xFunction(t)) + (position.axisY yFunction(t)) + (position.axisZ zFunction(t)).
           \en Functions of coordinates of the curve are given as custom functions of common parameter t. 
    Each coordinate of the curve is described by its own function in form of string expression. 
    Parameter of the curve, which is also the parameter of functions of coordinates, varies in range [tmin tmax]. \n
    All the custom functions are given in the local coordinate system position.
    The coordinate system can be Cartesian, cylindrical or spherical.
    The radius-vector of the curve in method PointOn(double&t,MbCartPoint3D&r) is described by a vector function: \n
    r(t) = position.origin + (position.axisX xFunction(t)) + (position.axisY yFunction(t)) + (position.axisZ zFunction(t)). \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbCharacterCurve3D : public MbCurve3D {
private:
  MbFunction *          xFunction; ///< \ru Функция координаты x. \en Function of x-coordinate. 
  MbFunction *          yFunction; ///< \ru Функция координаты y. \en Function of y-coordinate. 
  MbFunction *          zFunction; ///< \ru Функция координаты z. \en Function of z-coordinate 
  MbPlacement3D         position;  ///< \ru Локальная система координат, в которой заданы координатные функции. \en The local coordinate system the functions of coordinates are specified in. 
  MbMatrix3D            transform; ///< \ru Матрица трансформации кривой. \en Transformation matrix of the curve. 
  double                tmin;      ///< \ru Минимальное  значение параметра кривой. \en The minimal value of a curve parameter. 
  double                tmax;      ///< \ru Максимальное значение параметра кривой. \en The maximal value of the curve parameter. 
  bool                  closed;    ///< \ru Признак замкнутости кривой. \en An attribute of curve closedness. 
  MbeLocalSystemType3D  coordinateType; ///< \ru Тип системы координат, в которой заданы координатные функции. \en Type of coordinate system the functions of coordinates are specified in. 
  c3d::DoubleVector     specialParams;  ///< \ru Множество параметров особых точек кривой. \en Set of parameters of curve's singular points. 
  // \ru Буферные данные для ускорения вычислений. \en Buffer data to speed up computations. 
  mutable double        metricLength;
  mutable MbCube        cube;
  
public:
  MbCharacterCurve3D( MbFunction & x, MbFunction & y, MbFunction & z,
                      MbeLocalSystemType3D cs, const MbPlacement3D & place,
                      double tmin_, double tmax_ );
  MbCharacterCurve3D( const MbCharacterCurve & init, const MbPlacement3D & place ); // \ru Конструктор по двумерной кривой \en Constructor by two-dimensional curve 
protected:
  MbCharacterCurve3D( const MbCharacterCurve3D & );
public:
  virtual ~MbCharacterCurve3D();

public:
  VISITING_CLASS( MbCharacterCurve3D )

  virtual MbeSpaceType  IsA           ()       const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame        ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;           // \ru Кривая есть копия этой кривой ? \en Is a curve a copy of this curve? 
  virtual bool    SetEqual      ( const MbSpaceItem & );                 // \ru Сделать равным \en Make equal 
  virtual void    Transform     ( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move          ( const MbVector3D &, MbRegTransform * = NULL );               // \ru Сдвиг \en Translation 
  virtual void    Rotate        ( const MbAxis3D &, double angle, MbRegTransform * = NULL );   // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual void    AddYourGabaritTo( MbCube & ) const;
  virtual void    PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void    GetProperties ( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties ( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой. \en Common functions of the curve. 

  virtual double  GetTMin () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer( double & t, MbVector3D & ) const;    // \ru Первая производная \en The first derivative 
  virtual void    SecondDer( double & t, MbVector3D & ) const;    // \ru Вторая производная \en The second derivative 
  virtual void    ThirdDer( double & t, MbVector3D & ) const;    // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual double  Step         ( double t, double sag ) const; ///< \ru Вычисление шага параметра по величине прогиба кривой \en Calculation of parameter step by value of sag of the curve 
  virtual double  DeviationStep( double t, double ang ) const; ///< \ru Вычисление шага параметра по углу отклонения касательной \en Calculation of parameter by the angle of tangent deviation 

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  GetMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double  GetLengthEvaluation() const;
  
  virtual bool    IsPlanar() const; // \ru Является ли кривая плоской \en Whether the curve is planar 
  virtual bool    GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const; // \ru Заполнить плейсемент, если кривая плоская \en Fill the placement if curve is planar 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Get a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called on a three-dimensional curve) 
  virtual bool    GetPlaneCurve ( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  virtual MbCurve * GetMap( const MbMatrix3D & into, MbRect1D * pRegion = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of curve 
  // \ru Определить количество разбиений для прохода в операциях. \en Define the number of splittings for one passage in operations. 
  virtual size_t  GetCount() const;
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

          void    CheckParam    ( double & t )  const;
          void    CalculateParam( double t, MbCartPoint3D & point, 
                                  MbVector3D & firstDer, MbVector3D & secondDer, MbVector3D & thirdDer ) const;

  const   MbFunction * GetX() const { return xFunction; }
  const   MbFunction * GetY() const { return yFunction; }
  const   MbFunction * GetZ() const { return zFunction; }
  const   MbMatrix3D & GetMatrix() const { return transform; }
  const   MbPlacement3D & GetPlacement() const { return position;  }
  MbeLocalSystemType3D    GetCoordinateType() const { return coordinateType; }

protected:
//          void    GetSpecialParams( std::vector<double> & params ) const;
          double  ApproximationStep( double t, bool isAngle, double constraint ) const; 
          void    ConvertParamsInd( size_t componentIndex,
                                    const std::vector<double> & tComponent, 
                                    std::vector<double> & tCrv ) const;
          void    ConvertParams( const double tCrv, 
                                 double (&tComponents)[3],
                                 double (&proportionFactors)[3]) const;

private:
          // \ru Проверить и установить признак замкнутости. \en Check and set the flag of closedness. 
          void    CheckClosed();

private:
          void    operator =    ( const MbCharacterCurve3D & );         // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCharacterCurve3D )
};

IMPL_PERSISTENT_OPS( MbCharacterCurve3D )

#endif // __CUR_CHARCTER_CURVE3D_H
