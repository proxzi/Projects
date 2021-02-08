////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Кривая-мостик, соединяющая концы двух кривых.
         \en Bridge curve connecting ends of two curves. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_BRIDGE3D_H
#define __CUR_BRIDGE3D_H


#include <curve3d.h>
#include <mb_cube.h>


//------------------------------------------------------------------------------
/** \brief \ru Кривая-мостик, соединяющая концы двух кривых.
           \en Bridge curve connecting ends of two curves. \~
  \details \ru Кривая-мостик соединяет точки двух кривых кривой третьей степени, 
    построенной по конечным точкам и производным в конечных точках. 
    Конечные точки и производные в конечных точках вычисляются в соединяемых точках соединяемых кривых. \n
           \en The bridge curve connects points of two curves with a curve of the third degree 
    constructed by the end points and derivatives at the end points. 
    The end points and derivatives at the end points are calculated for curves' points being connected. \n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbBridgeCurve3D : public MbCurve3D {
protected:
  MbCurve3D *    curve1; ///< \ru Первая соединяемая кривая. \en The first curve to connect. 
  MbCurve3D *    curve2; ///< \ru Вторая соединяемая кривая. \en The second curve to connect. 
  double         param1; ///< \ru Параметр точки соединения первой кривой. \en Parameter of the first curve's connection point. 
  double         param2; ///< \ru Параметр точки соединения второй кривой. \en Parameter of the second curve's connection point. 
  bool           sense1; ///< \ru Совпадение (true) направления производных кривой и первой кривой. \en The coincidence(true) of directions this curve and the first curve in connection points. 
  bool           sense2; ///< \ru Совпадение (true) направления производных кривой и второй кривой. \en The coincidence(true) of directions this curve and the second curve in connection points. 
  double         tmin;   ///< \ru Начальный параметр кривой. \en The starting parameter of the curve. 
  double         tmax;   ///< \ru Конечный  параметр кривой. \en The end parameter of the curve. 
  // \ru Насчитанные по кривым данные. \en Data calculated for the curves. 
  MbCartPoint3D  point1; ///< \ru Точка на первой кривой. \en Point on the first curve. 
  MbCartPoint3D  point2; ///< \ru Точка на второй кривой. \en Point on the second curve. 
  MbVector3D     derive1;///< \ru Производная в начальной точке. \en Derivative at the starting point. 
  MbVector3D     derive2;///< \ru Рроизводная в конечной  точке. \en Derivative at the end point. 
  // \ru Временные данные. \en Temporary data. 
  mutable MbCube cube;   ///< \ru Габаритный куб. \en Bounding box. 

public :
  MbBridgeCurve3D( MbCurve3D & c1, double t1, bool s1,
                   MbCurve3D & c2, double t2, bool s2, 
                   double _tmin = 0.0, double _tmax = 1.0 );
protected:
  MbBridgeCurve3D( const MbBridgeCurve3D & ); // \ru НЕЛЬЗЯ \en NOT ALLOWED 
  MbBridgeCurve3D( const MbBridgeCurve3D &, MbRegDuplicate * ireg );

public:
  virtual ~MbBridgeCurve3D();

public:
  VISITING_CLASS( MbBridgeCurve3D );

          void    Init( MbCurve3D & c1, double t1, bool s1,
                        MbCurve3D & c2, double t2, bool s2, 
                        double _tmin, double _tmax ); 

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en A type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;      // \ru Является ли объект копией \en Whether the object is a copy       
  virtual bool    SetEqual ( const MbSpaceItem & );            // \ru Сделать равным \en Make equal 
  virtual bool    IsSimilar( const MbSpaceItem & init ) const; // \ru Сделать элементы равными \en Make the elements equal 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );    // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL );    // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual void    AddYourGabaritTo( MbCube & ) const; // \ru Добавь свой габарит в куб \en Add own bounding box into a bounding box 
  virtual void    Refresh(); // \ru Сбросить все временные данные \en Flush all the temporary data 
  virtual void    PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void    GetProperties( MbProperties & );    // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & );    // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of the curve 

  virtual double  GetTMin  () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double  GetTMax  () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool    IsClosed () const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const;// \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double & t, MbVector3D & ) const;   // \ru Первая производная \en The first derivative 
  virtual void    SecondDer( double & t, MbVector3D & ) const;   // \ru Вторая производная \en The second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & ) const;   // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual void    Inverse  ( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  Step     ( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculation of the approximation step 
  virtual double  DeviationStep( double t, double angle ) const;

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить NURBS-копию кривой \en Create a NURBS-copy of the curve 

  const   MbCube &GetGabarit() const { if ( cube.IsEmpty() ) CalculateGabarit( cube ); return cube; } // \ru Выдать габарит кривой \en Get the bounding box of a curve 

private:
  inline  void    CheckParam  ( double & t ) const; // \ru Проверка параметра \en Check parameter 
  inline  void    LocalParams ( const double & t, double & quota1, double & quota2 ) const;  // \ru Вычисление локальных данных по параметру \en Calculation of local data by the parameter 
          void    LocalData   ();                   // \ru Определение значений точек и производных на концах \en Determination of values of points and derivatives at the ends 
          void    ChangeCurves( MbCurve3D & c1, MbCurve3D & c2 );
          void    operator =  ( const MbBridgeCurve3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbBridgeCurve3D )
};

IMPL_PERSISTENT_OPS( MbBridgeCurve3D )

//------------------------------------------------------------------------------
/// \ru Проверка параметра. \en Check parameter. 
// ---
inline void MbBridgeCurve3D::CheckParam( double & t ) const {
  if ( t < tmin )
    t = tmin;
  else 
    if ( t > tmax )
      t = tmax;
}


//------------------------------------------------------------------------------
/// \ru Определение необходимых локальных параметров. \en Determination of the necessary local parameters. 
// ---
inline void MbBridgeCurve3D::LocalParams( const double & t, double & quota1, double & quota2 ) const {
  double paramW = 1 / ( tmax - tmin );
  quota1 = ( tmax - t ) * paramW;
  quota2 = ( t - tmin ) * paramW;
}


#endif // __CUR_BRIDGE3D_H
