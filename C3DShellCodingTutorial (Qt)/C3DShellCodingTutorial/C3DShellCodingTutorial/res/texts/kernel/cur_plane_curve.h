////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Плоская кривая в трехмерном пространстве.
         \en Plane curve in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_PLANE_CURVE_H
#define __CUR_PLANE_CURVE_H


#include <cur_offset_curve.h>
#include <curve3d.h>
#include <mb_placement3d.h>


class  MATH_CLASS  MbContour;


//------------------------------------------------------------------------------
/** \brief \ru Плоская кривая в трехмерном пространстве.
           \en Plane curve in three-dimensional space. \~
  \details \ru Плоская кривая описывается двумерной кривой curve в плоскости XY локальной системы координат position. \n
    Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией: \n
    r(t) = position.origin + (position.axisX point.x) + (position.axisY point.y),
    где point = curve(t);
           \en Plane curve is described by two-dimensional uv-curve in the XY-plane of the local coordinate system "position". \n
    The radius-vector of curve in the method PointOn(double&t,MbCartPoint3D&r) is described by a vector function: \n
    r(t) = position.origin + (position.axisX point.x) + (position.axisY point.y),
    where point = curve(t); \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbPlaneCurve : public MbCurve3D {
protected :
  MbPlacement3D position; ///< \ru Локальная система координат, в плоскости XY которой расположена кривая. \en The local coordinate system in XY plane of which the curve is located. 
  MbCurve   *   curve;    ///< \ru Двумерная кривая (не может быть NULL). \en A two-dimensional uv-curve (can not be NULL). 

public :
  /// \ru same = false - копировать кривую init. \en Same = false - copy the curve "init". 
  MbPlaneCurve( const MbPlacement3D &, const MbCurve & init, bool same );
protected:
  MbPlaneCurve( const MbPlaneCurve & );
public :
  virtual ~MbPlaneCurve();

public :
  VISITING_CLASS( MbPlaneCurve );
  
          void        Init( const MbPlaneCurve &init );
          void        Init( const MbPlacement3D &pl, MbCurve &initCurve );

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const ; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;    // \ru Является ли объект копией \en Whether the object is a copy 
  virtual bool        SetEqual ( const MbSpaceItem & );          // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar( const MbSpaceItem & ) const;    // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );             // \ru Преобразовать \en Transform. 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );             // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const; // \ru Расстояние до точки \en Distance to a point 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual bool        IsSpaceSame( const MbSpaceItem & item, double eps = METRIC_REGION ) const; // \ru Являются ли объекты идентичными в пространстве \en Are the objects identical in space? 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double      GetTMax()   const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double      GetTMin()   const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool        IsClosed()  const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double      GetPeriod() const; // \ru Вернуть период \en Get period  
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector3D & )    const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector3D & )    const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector3D & )    const; // \ru Третья производная по t \en Third derivative with respect to t 
  virtual void        Normal   ( double & t, MbVector3D & )    const; // \ru Вектор главной нормали \en Vector of the principal normal 
  // \ru Функции кривой для работы вне области определения параметрической кривой \en Functions of curve for working outside the domain of parametric curve 
  virtual void       _PointOn  ( double t, MbCartPoint3D & )   const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void       _FirstDer ( double t, MbVector3D & )      const; // \ru Первая производная \en First derivative 
  virtual void       _SecondDer( double t, MbVector3D & )      const; // \ru Вторая производная \en Second derivative 
  virtual void       _ThirdDer ( double t, MbVector3D & )      const; // \ru Третья производная по t \en Third derivative with respect to t 
  virtual void       _Normal   ( double t, MbVector3D & )      const; // \ru Вектор главной нормали \en Vector of the principal normal 
    // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * NurbsCurve( const MbNurbsParameters & ) const;


  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 

  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Ближайшая проекция точки на кривую \en The nearest point projection to the curve 
  virtual double      Curvature( double  ) const; // \ru Кривизна кривой \en Curvature of the curve 
  virtual double      Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double      MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 

  virtual double      GetMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Evaluation of the metric length of the curve 
  virtual double      CalculateMetricLength() const;      // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double      CalculateLength( double t1, double t2 ) const;
  // \ru Сдвинуть параметр t на расстояние len по направлению \en Shift the parameter t by the distance 'len' in the direction 
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                     VERSION version = Math::DefaultMathVersion() ) const;   
  /// \ru Получить границы участков кривой, на которых сохраняется непрерывность кривизны. 
  /// \en Get the boundaries of the sections of the curve on which the continuity of curvature is preserved. \~
  virtual void        GetCurvatureContinuityBounds( std::vector<double> & params ) const;

  virtual bool        IsPlanar() const;   // \ru Является ли кривая плоской \en Whether a curve is planar 
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Являются ли стыки контура\кривой гладкими? \en Whether the joints of contour\curve are smooth. 
  // \ru Ближайшая точка кривой к плейсменту \en The nearest point of a curve by the placement 
  virtual double      DistanceToPlace( const MbPlacement3D & place, double & t0, double & angle ) const;

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of curve 
  virtual MbCurve *   GetMapPsp( const MbMatrix3D &, double zNear, 
                                 MbRect1D * pRgn = NULL ) const;

  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.
  virtual bool        GetCircleAxis  ( MbAxis3D & ) const; // \ru Дать ось кривой \en Get the curve axis 
  virtual void        GetCentre      ( MbCartPoint3D & wc ) const;
  virtual void        GetWeightCentre( MbCartPoint3D & wc ) const;
  virtual bool        IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual size_t      GetCount  () const;
  virtual void        GetPointsByEvenLengthDelta( size_t n,  std::vector<MbCartPoint3D> & pnts ) const; // \ru Выдать n точек кривой с равными интервалами по длине дуги \en Get n points of curves equally spaced by the arc length 

  virtual void        CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой \en Calculate the bounding box of curve 
  virtual void        CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 

  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Give a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called for a two-dimensional curve) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы) \en Get a surface curve if spatial curve is lying on the surface (after the using call DeleteItem for arguments) 
  virtual bool        GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Заполнить плейсемент, если кривая плоская \en Fill the placement if curve is planar 
  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

          MbCurve *   GetCurve ( const MbPlacement3D & , MbMatrix & ) const; // \ru Дать плоскую кривую \en Get the plane curve 
          MbCurve *   MakeCurve( const MbPlacement3D & ) const;
          MbCurve3D * MakeCurve() const; // \ru Дать пространственную кривую \en Get the spatial curve 

          void        SetCurve( const MbCurve & );      // \ru Заменить плоскую кривую \en Replace the plane curve 
          void        SetOrigin( const MbCartPoint3D & org ) { position.SetOrigin(org); }

    const MbPlacement3D & GetPlacement() const { return position; }
    const MbCurve &   GetCurve() const { return *curve;   } // \ru Дать плоскую кривую \en Get the plane curve 
          MbCurve &   SetCurve()       { return *curve;   } // \ru Дать плоскую кривую \en Get the plane curve 

  // \ru Является ли объект смещением? \en Is the object a shift? 
  virtual bool        IsShift( const MbSpaceItem &, MbVector3D &, bool & isSame, double accuracy = LENGTH_EPSILON ) const;
  virtual bool        IsSimilarToCurve( const MbCurve3D & curve, double precision = METRIC_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves are similar for merge (joining) 

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

private:
          void        operator = ( const MbPlaneCurve & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbPlaneCurve )
};

IMPL_PERSISTENT_OPS( MbPlaneCurve )

//------------------------------------------------------------------------------
/** \brief \ru Cоздать пространственную кривую.
           \en Create a spatial curve. \~
  \details \ru Создать пространственную кривую как точное представление двумерной кривой на плоскости.
           \en Create a spatial curve as an accurate representation of the two-dimensional uv-curve on the plane. \~
  \ingroup Curve3D_Modeling
*/
// ---
MATH_FUNC (MbCurve3D *) MakeCurve3D( const MbCurve & curve, const MbPlacement3D & );


//-------------------------------------------------------------------------------
// \ru Создать по плоской кривой подложке пространственную кривую \en Create a spatial curve from plane curve of substrate 
// \ru (кривой должен кто-то владеть иначе она может быть уничтожена) \en (someone must own the curve otherwise it can be destroyed) 
// ---
MbCurve3D & GetCurve3DWithCheckingPlaneCur( MbCurve3D & initCur );


#endif // __CUR_PLANE_CURVE_H
