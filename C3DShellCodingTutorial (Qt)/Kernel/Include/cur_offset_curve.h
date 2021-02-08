////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Эквидистантная продолженная кривая.
         \en Offset extended curve. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_OFFSET_CURVE_H
#define __CUR_OFFSET_CURVE_H


#include <curve.h>
#include <mb_rect.h>
#include <mb_matrix.h>


class MbRegDuplicate;
class MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Эквидистантная продолженная кривая.
           \en Offset extended curve. \~
  \details \ru Эквидистантная продолженная кривая строится смещением точек базовой кривой вдоль нормали к ней. \n
    Параметры "offsetTmin, offsetTmax" задают смещение точек базовой кривой в точках tmin, tmax.
	  Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией \n
    r(t) = basisCurve(t) + (Offset0(t) * normal(t)), где normal(t) - нормаль базовой кривой. \n
    Базовой кривой для эквидистантной кривой не может служить другая эквидистантная кривая.
    В подобной ситуации выполняется переход к первичной базовой кривой.
           \en Offset extended curve is constructed by shifting points of the base curve along a normal to it. \n
    The "offsetTmin, offsetTmax" parameters set shift of base curve on begin and end points.
	  Radius-vector of the curve in the method PointOn(double&t,MbCartPoint3D&r) is described by the function \n
    r(t) = basisCurve(t) + (Offset0(t) * normal(t)), where normal(t) - normal of base curve. \n
    Base curve for offset curve can not be other offset curve.
    In such situation it changes to the initial base curve. \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbOffsetCurve : public MbCurve {
protected :
  MbCurve *      basisCurve;   ///< \ru Базовая кривая (всегда не NULL) \en Base curve (always not NULL). 
  double         tmin;         ///< \ru Начальный параметр basisCurve. \en Start parameter of basisCurve. 
  double         tmax;         ///< \ru Конечный  параметр basisCurve. \en End parameter of basisCurve. 
  bool           closed;       ///< \ru Замкнутость basisCurve. \en Closedness of basisCurve. 
  double         offsetTmin;   ///< \ru Смещение от базовой кривой по нормали в точке tmin. \en The offset from the base curve along normal in point tmin. 
  double         offsetTmax;   ///< \ru Смещение от базовой кривой по нормали в точке tmax. \en The offset from the base curve along normal in point tmax. 
  MbeOffsetType  type;         ///< \ru Тип смещения точек: константный, линейный или кубический. \en The type of points offset: constant, or linear, or cubic.
  double         deltaTmin;    ///< \ru Увеличение tmin параметра базовой кривой. \en Increase of tmin of base curve parameter. 
  double         deltaTmax;    ///< \ru Увеличение tmax параметра базовой кривой. \en Increase of tmax of base curve parameter. 
  MbMatrix       transform;    ///< \ru Матрица преобразования (используется при разных масштабных коэффициентах трансформации). \en A transformation matrix (is used for different scale transformation). 

  mutable MbRect rect;         ///< \ru Габаритный прямоугольник \en Bounding box 
  mutable double metricLength; ///< \ru Метрическая длина \en The metric length 

public :
  MbOffsetCurve( const MbCurve & bc, double dist, double t1, double t2, bool same );      
  MbOffsetCurve( const MbCurve & bc, double dist, double t1, double t2, const MbMatrix & matr, bool same );
  MbOffsetCurve( const MbCurve & bc, double dist, bool same );
  MbOffsetCurve( const MbCurve & bc, double dist, const MbMatrix & matr, bool same );

  /** \brief \ru Конструктор по базовой кривой и смещению c приращениями параметров.
             \en Constructor by base curve and offset with increments of parameters. \~  
    \details \ru Смещение задано на краях параметрической области базовой кривой и может изменяться по константному, линейному и кубическому законам.\n  
      Приращение параметров нужно использовать для изменения области определения кривой относительно базовой кривой.
             \en The offset displacement is defined in the begin and the end of the parametric region of the base curve and can be changed by constant, linear and cubic laws.\n  
      Increment of parameters needs to be used for change of curve domain relative to base curve. \~
    \param[in] bc -   \ru Базовая кривая.
                      \en Base curve. \~
    \param[in] d1 -   \ru Смещение в точке Tmin базовой кривой.
                      \en Offset distance on point Tmin of base curve. \~
    \param[in] d2 -   \ru Смещение в точке Tmax базовой кривой.
                      \en Offset distance on point Tmax of base curve. \~
    \param[in] t  -   \ru Тип смещения точек: константный, линейный или кубический.
                      \en The offset type: constant, or linear, or cubic. \~
    \param[in] t1 -   \ru Минимальный параметр кривой.
                      \en The maximum parameter of offset curve. \~
    \param[in] t2 -   \ru Максимальный параметр кривой.
                      \en The minimum parameter of offset curve. \~
    \param[in] matr - \ru Матрица преобразования (единичная или анизотропная).
                      \en The matrix (single or anisotropic). \~               
    \param[in] same - \ru Признак использования оригинала базовой кривой, а не ее копии.
                      \en Attribute of usage of original of base curve, not copy. \~
  */
  MbOffsetCurve( const MbCurve & bc, double d1, double d2, MbeOffsetType t, double t1, double t2, const MbMatrix & matr, bool same );

protected :
  MbOffsetCurve( const MbOffsetCurve &, MbRegDuplicate * ireg );
private:
  MbOffsetCurve( const MbOffsetCurve & ); // \ru Не реализовано. \en Not implemented. 
public :
  virtual ~MbOffsetCurve ();

public :
  VISITING_CLASS( MbOffsetCurve ); 

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of geometric object.
      \{ */

  virtual MbePlaneType  IsA() const;                        // \ru Тип элемента \en Type of element 
  virtual bool        IsSimilar ( const MbPlaneItem & ) const;   // \ru Являются ли элементы подобными \en Whether the elements are similar 
  virtual bool        SetEqual( const MbPlaneItem & );         // \ru Сделать элементы равными \en Make equal elements 
  virtual MbPlaneItem & Duplicate( MbRegDuplicate * = NULL ) const;   // \ru Сделать копию элемента \en Create a copy of the element 
  virtual void        Transform( const MbMatrix & matr, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move( const MbVector & to, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual	bool        IsSame( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли кривая curve копией данной кривой ? \en Whether the 'curve' curve is duplicate of current curve. 
  virtual void        AddYourGabaritTo( MbRect & ) const; // \ru Добавь свой габарит в прямой прям-к \en Add bounding box into a straight box 

  /** \} */
  /** \ru \name Функции инициализации.
      \en \name Initialization functions.
      \{ */  
          /** \brief \ru Инициализация по смещению и приращениям параметров.
                     \en Initialization by offset and increments of parameters. \~  
            \details \ru Смещение задано на краях параметрической области базовой кривой и может изменяться по константному, линейному и кубическому законам.\n  
              Приращение параметров нужно использовать для изменения области определения кривой относительно базовой кривой.
                     \en The offset displacement is defined in the begin and the end of the parametric region of the base curve and can be changed by constant, linear and cubic laws.\n  
              Increment of parameters needs to be used for change of curve domain relative to base curve. \~          
            \param[in] d1 - \ru Смещение в точке Tmin базовой кривой.
                            \en Offset distance on point Tmin of base curve. \~
            \param[in] d2 - \ru Смещение в точке Tmax базовой кривой.
                            \en Offset distance on point Tmax of base curve. \~
            \param[in] t  - \ru Тип смещения точек: константный, линейный или кубический.
                            \en The offset type: constant, or linear, or cubic. \~
            \param[in] t1 - \ru Увеличение tmin параметра
                            \en Increment of tmin parameter \~
            \param[in] t2 - \ru Увеличение tmax параметра
                            \en Increment of tmax parameter \~
          */
          void        Init( double d1, double d2, MbeOffsetType t, double t1, double t2 );  
          void        Init( double d, double t1, double t2 );
          void        Init( double t1, double t2 );
  /** \} */

  /** \ru \name Функции описания области определения кривой.
      \en \name Functions for curve domain description.
      \{ */
  virtual double      GetTMax()   const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual double      GetTMin()   const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual bool        IsClosed()  const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual double      GetPeriod() const; // \ru Вернуть период \en Get period  
  /** \} */

  /** \ru \name Функции для работы в области определения кривой.
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the curve's domain. 
            Functions PointOn, FirstDer, SecondDer, ThirdDer,... correct parameter
            when it is outside domain.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint & pnt ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector    & fd  ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & sd  ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & td  ) const; // \ru Третья производная \en Third derivative 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения кривой. 
            Функции _PointOn, _FirstDer, _SecondDer, _ThirdDer,... не корректируют параметр
            при выходе за пределы области определения. При выходе за область определения незамкнутая
            кривая, в общем случае, продолжается по касательной, которую она имеет на соответствующем конце.
      \en \name Functions for working inside and outside the curve's domain. 
            Functions _PointOn, _FirstDer, _SecondDer, _ThirdDer,... do not correct parameter
            when it is out of domain bounds. When parameter is out of domain bounds, an unclosed
            curve is extended by tangent vector at corresponding end point in general case.
      \{ */
  virtual void       _PointOn  ( double t, MbCartPoint & p ) const;
  virtual void       _FirstDer ( double t, MbVector    & v ) const;
  virtual void       _SecondDer( double t, MbVector    & v ) const;
  virtual void       _ThirdDer ( double t, MbVector    & v ) const;
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;
  /** \} */

  /** \ru \name Функции движения по кривой
      \en \name Function of moving by curve
    \{ */
  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculation of approximation step 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации с учетом угла отклонения \en Calculation of approximation step with consideration of deviation angle 

  /** \} */
  /** \ru \name Общие функции кривой
      \en \name Common function of curve.
      \{ */
  virtual bool        IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual MbCurve	*   Offset( double rad ) const;	// \ru Смещение смещенной кривой \en Offset of the offset curve 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменение направления кривой на противоположное \en Change to the opposite direction of a curve 
  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.
  
  // BUG_54628
  // \ru Функция не работает для самопересекающейся кривой \en This function does not work for self-intersecting curve 
  // \ru Проекция точки на кривую \en Point projection on the curve 
  // virtual double      PointProjection( const MbCartPoint & pnt ) const;

  virtual MbeState    Deformation( const MbRect &, const MbMatrix & );  // \ru Деформация \en Deformation 
  // \ru Удалить часть смещенной кривой между параметрами t1 и t2 \en Delete a part of a offset curve between parameters t1 and t2 
  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 );
  // \ru Оставить часть смещенной кривой между параметрами t1 и t2 \en Save a part of a offset curve between t1 and t2 parameters 
  virtual MbeState    TrimmPart ( double t1, double t2, MbCurve *& part2 );
  virtual MbCurve *   Trimmed   ( double t1, double t2, int sense ) const;

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

          bool        Break( MbNurbs &nurbs, double t1, double t2, ptrdiff_t degree );

  virtual bool        IsBounded()    const; // \ru Признак ограниченной кривой \en Attribute of a bounded curve 
  virtual bool        IsDegenerate( double eps = Math::LengthEps ) const; // \ru Проверка вырожденности кривой \en Check for curve degeneracy 

  virtual bool        HasLength( double & length ) const;
  virtual double      GetMetricLength() const; // \ru Метрическая длина кривой \en Metric length of a curve 
  virtual double      GetLengthEvaluation() const; // \ru Оценка метрической длины кривой \en Evaluation of the metric length of the curve  

  virtual const MbCurve & GetBasisCurve() const;
  virtual       MbCurve & SetBasisCurve();

  virtual bool        GetAxisPoint( MbCartPoint & p ) const; // \ru Точка для построения оси \en A point to the axis construction 
  virtual size_t      GetCount() const; // \ru Количество разбиений для прохода в операциях \en The number of partitions for passage in the operations  

  virtual void        OffsetCuspPoint( SArray<double> & tCusps, double dist ) const; // \ru Определение особых точек офсетной кривой \en Determination of singular points of the offset curve 
  virtual double      Curvature( double t ) const; // \ru Кривизна кривой \en Curvature of the curve 
  // \ru Сдвинуть параметр t на расстояние len \en Move parameter t on the distance len 
  virtual bool        DistanceAlong( double & t1, double ln, int curveDir, double eps = Math::LengthEps,
                                     VERSION version = Math::DefaultMathVersion() ) const;
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; // \ru Подобные ли кривые для объединения (слива) \en Whether the curves are similar for merge (joining) 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

          void        SetBasisCurve( MbCurve & ); // \ru Установить базовую кривую \en Set the base curve 
          // \ru Тип смещения точек. \en The type of points offset.
          MbeOffsetType GetOffsetType() const { return type; }
          // \ru Постоянное ли смещение точек? \en Is const the offset type?
          bool        IsConstOffset() const { return ( (type == off_Empty) || (type == off_Const) ); }
          // \ru Величина смещения. \en The offset distance. 
          double      GetDistance( size_t i = 0 ) const { 
            if ( i == 1 ) return offsetTmax;
            return offsetTmin;
          }
          
          /** \brief \ru Установить величины смещения.
                     \en Set offset distances. \~  
            \param[in] d - \ru Новая величина смещения
                           \en New offset distance \~
          */
          void        SetDistance( double d, size_t i = 0 );

  const   MbRect &    GetGabarit() const { if ( rect.IsEmpty() ) CalculateGabarit( rect ); return rect; }
          void        SetDirtyGabarit() const { rect.SetEmpty(); }
  const   double &    GetDmin() const { return deltaTmin; } // \ru Дать расширение начала \en Get extension of start 
  const   double &    GetDmax() const { return deltaTmax; } // \ru Дать расширение конца \en Get extension of end 
          void        SetDmin( double d ) { deltaTmin = d; } // \ru Установить расширение начала \en Set extension of start 
          void        SetDmax( double d ) { deltaTmax = d; } // \ru Установить расширение конца \en Set extension of end 

          double      GetBegExtend() const { return deltaTmin; } // \ru Дать расширение начала \en Get extension of start 
          double      GetEndExtend() const { return deltaTmax; } // \ru Дать расширение конца \en Get extension of end 
          int         ExtendedParam( double &t ) const; // \ru Проверка, лежит ли параметр в пределах \en Check if parameter is in range 
          void        GetCurves( RPArray<MbCurve> & curves ); // \ru Дать составляющие кривые \en Get curves 

          bool        operator == ( const MbOffsetCurve & ) const; // \ru Проверка на равенство \en Check for equality 
          bool        operator != ( const MbOffsetCurve & ) const; // \ru Проверка на неравенство \en Check for inequality 

          bool        SubstrateParamOn( double &t, double &delta ) const; // \ru Находится ли параметр в пределах подложки \en Check if parameter is in the range of substrate 
          bool        IsMatrixSingle() const { return transform.IsSingle(); } ///< \ru Является ли матрица преобразования единичной. \en Whether the transformation matrix is unit. 
          const MbMatrix & GetMatrix() const { return transform; } ///< \ru Матрица преобразования. \en A transformation matrix. 

  /** \} */

private:
          // \ru Вычисление эквидистанты и её производных. \en The offset calculation and it derivatives calculation.
          double      Offset0  ( double t ) const;
          double      OffsetT  ( double t ) const;
          double      OffsetTT ( double t ) const;
          double      OffsetTTT( double t ) const;

          void        operator = ( const MbOffsetCurve & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbOffsetCurve )
}; // MbOffsetCurve

IMPL_PERSISTENT_OPS( MbOffsetCurve )

#endif // __CUR_OFFSET_CURVE_H
