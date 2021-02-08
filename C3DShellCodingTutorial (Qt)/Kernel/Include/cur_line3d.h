////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Прямая в трехмерном пространстве.
         \en Line in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_LINE3D_H
#define __CUR_LINE3D_H


#include <curve3d.h>


class  MATH_CLASS   MbLine;


//------------------------------------------------------------------------------
/** \brief \ru Прямая в трехмерном пространстве.
           \en Line in three-dimensional space. \~
  \details \ru Прямая линия ведёт себя как бесконечный объект, хотя в своих данных имеет граничные значения параметра tmin и tmax. 
    В отличие от других кривых в методах вычисления радиуса-вектора и его производных прямая не корректирует параметр t при его выходе за предельные значения tmin и tmax. \n
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией\n
    r(t) = origin + (t direction).
           \en Straight line behaves as an infinite object although its data has boundary parameter values tmin and tmax. 
    In contrast to curves in the calculation methods of radius-vector and its derivatives the line doesn't correct parameter "t" if it is outside the values tmin and tmax. \n
    Radius-vector of the curve in the method PointOn(double&t,MbCartPoint3D&r) is described by the vector function\n
    r(t) = origin + (t direction). \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbLine3D : public MbCurve3D {
private :
  MbCartPoint3D origin;     ///< \ru Начальная точка. \en Start point. 
  MbVector3D    direction;  ///< \ru Вектор направления. \en A direction vector. 

public :
  MbLine3D();
  MbLine3D( const MbCartPoint3D & initP, const MbVector3D & initV );
  MbLine3D( const MbCartPoint3D & p1,    const MbCartPoint3D & p2 );
protected:
  MbLine3D( const MbLine3D & );
public :
  virtual ~MbLine3D();

public :
  VISITING_CLASS( MbLine3D ); 

          void    Init( const MbLine3D & init );
          void    Init( const MbCartPoint3D & p0,  const MbVector3D & dir );
          void    Init( const MbCartPoint3D & p1,  const MbCartPoint3D & p2 );
          void    Init( const MbPlacement3D & pos, const MbLine & line );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool    SetEqual ( const MbSpaceItem & );          // \ru Сделать равным \en Make equal 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL );             // \ru Преобразовать \en Transform 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвиг \en Translation 
  virtual void    Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate around an axis 
  virtual double  DistanceToPoint( const MbCartPoint3D & ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual void    AddYourGabaritTo( MbCube & ) const; // \ru Добавить габарит кривой в куб. \en Add a bounding box of a curve to a cube. 

  virtual void    GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void    SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double  GetTMax()  const;  // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double  GetTMin()  const;  // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool    IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void    PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void    FirstDer ( double & t, MbVector3D & )    const; // \ru Первая производная \en First derivative 
  virtual void    SecondDer( double & t, MbVector3D & )    const; // \ru Вторая производная \en Second derivative 
  virtual void    ThirdDer ( double & t, MbVector3D & )    const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Функции кривой для работы вне области определения параметрической кривой \en Functions of curve for working outside the domain of parametric curve 
  virtual void   _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void   _FirstDer ( double t, MbVector3D & )     const; // \ru Первая производная \en First derivative 
  virtual void   _SecondDer( double t, MbVector3D & )     const; // \ru Вторая производная \en Second derivative 
  virtual void   _ThirdDer ( double t, MbVector3D & )     const; // \ru Третья производная по t \en Third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void    Explore( double & t, bool ext,
                           MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  // \ru Построить NURBS копию кривой \en Create a NURBS copy of the curve 
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const; // \ru Построить Nurbs-копию кривой \en Construct NURBS copy of the curve 

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 
  // \ru Сдвинуть параметр t на расстояние len по направлению \en Shift the parameter t by the distance 'len' in the direction 
  virtual bool    DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                 VERSION version = Math::DefaultMathVersion() ) const; 

  virtual void    Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual double  GetMetricLength() const;  // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double  Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double  DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double  MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  /// \ru Вычислить габарит кривой. \en Calculate bounding box of a curve. 
  virtual void    CalculateGabarit( MbCube &  ) const;
  // \ru Вычислить габарит в локальной системе координат. \en Calculate bounding box in the local coordinate system. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube &  ) const;

  // \ru Все проекции точки на кривую \en All point projections on the curve 
  // \ru Ближайшая проекция точки на кривую \en The nearest point projection to the curve 
  virtual bool    NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const;

          bool    operator == ( const MbLine3D & with ) const; // \ru Проверка на равенство \en Check for equality 
          bool    operator != ( const MbLine3D & with ) const; // \ru Проверка на неравенство \en Check for inequality 

  virtual void    GetCentre      ( MbCartPoint3D &  c ) const; // \ru Выдать центр кривой \en Get the center of curve 
  virtual void    GetWeightCentre( MbCartPoint3D & wc ) const; // \ru Выдать центр тяжести кривой \en Get the center of gravity of the curve 
  virtual bool    IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual bool    IsPlanar  () const; // \ru Является ли кривая плоской \en Whether a curve is planar 

  virtual double  GetParamToUnit() const; // \ru Дать приращение параметра, осреднённо соответствующее единичной длине в пространстве \en Get increment of parameter, corresponding to the unit length in space 
  virtual double  GetParamToUnit( double t ) const; // \ru Дать приращение параметра, соответствующее единичной длине в пространстве \en Get increment of parameter, corresponding to the unit length in space 

  // \ru Дать плоскую проекцию кривой \en Get a planar projection of curve 
  virtual MbCurve * GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const;
  virtual MbCurve * GetMapPsp( const MbMatrix3D &, double zNear, 
                               MbRect1D * pRgn = NULL ) const;
  virtual void    CalculatePolygon( const MbStepData & stepData, MbPolygon3D & ) const; // \ru pассчитать полигон \en Calculate a polygon 
  virtual bool    IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves for union (joining) are similar 

  const MbCartPoint3D & GetOrigin()    const { return origin;   }
  const MbVector3D    & GetDirection() const { return direction;}
        MbCartPoint3D & SetOrigin()    { return origin;   }
        MbVector3D    & SetDirection() { return direction;}
        void            SetOrigin( const MbCartPoint3D & p ) { origin    = p; }
        void            SetDirection( const MbVector3D & v ) { direction = v; }
        bool      RoundColinear ( const MbLine3D & with, double eps = Math::angleRegion ) const; // \ru Грубая коллинеарность \en Rough collinearity 
        bool      Colinear ( const MbLine3D & with, double eps = Math::angleRegion ) const; // \ru Коллинеарность \en Collinearity 
        bool      Orthogonal( const MbLine3D & with, double eps = Math::angleRegion ) const; // \ru Ортогональность \en Orthogonality 

private:
          void    operator = ( const MbLine3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbLine3D )
};

IMPL_PERSISTENT_OPS( MbLine3D )

//------------------------------------------------------------------------------
// \ru Проверка на равенство \en Check for equality 
// ---
inline bool MbLine3D::operator == ( const MbLine3D &with ) const {
  return (origin == with.origin) && ( direction.Colinear( with.direction ) );
}


//------------------------------------------------------------------------------
// \ru Проверка на неравенство \en Check for inequality 
// ---
inline bool MbLine3D::operator != ( const MbLine3D &with ) const {
  return !(*this == with);
}


//------------------------------------------------------------------------------
// \ru Грубая коллинеарность по скалярному произведению \en Rough colinearity by dot product 
// ---
inline bool MbLine3D::RoundColinear( const MbLine3D &with, double eps ) const {
  return direction.RoundColinear( with.direction, eps );
}


//------------------------------------------------------------------------------
// \ru Коллинеарность \en Collinearity 
// ---
inline bool MbLine3D::Colinear( const MbLine3D &with, double eps ) const {
  return direction.Colinear( with.direction, eps );
}


//------------------------------------------------------------------------------
// \ru Ортогональность \en Orthogonality 
// ---
inline bool MbLine3D::Orthogonal( const MbLine3D &with, double eps ) const {
  return direction.Orthogonal( with.direction, eps );
}

                                  
#endif // __CUR_LINE3D_H
