////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Косинусоида в двумерном пространстве.
         \en Cosinusoid in two-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_COSINUSOID_H
#define __CUR_COSINUSOID_H


#include <curve.h>
#include <mb_placement.h>
#include <mb_rect.h>
#include <mb_rect1d.h>
#include <alg_diskrete_length_data.h>


class            MbRegDuplicate;
class            MbRegTransform;


//------------------------------------------------------------------------------
/** \brief \ru Косинусоида в двумерном пространстве.
           \en Cosinusoid in two-dimensional space. \~
  \details \ru Косинусоида расположена вдоль оси X локальной системы координат. \n
	  Радиус-вектор кривой в методе PointOn(double&t,MbCartPoint3D&r) описывается векторной функцией\n
    r(t) = position.origin + (position.axisX ((tmin + t) - phase) / frequency) + (amplitude cos(tmin + t) position.axisY).\n
    Косинусоида приведена на рисунке ниже. 
                t = 0                                              
      amplitude | /\            /\                                 
                |/  \          /  \                                
     t = -phase |    \ tmin  t/    \ tmax                          
         ______/|_____\|_____/______\|_____________________________
              / |      \    /        \                             
             /  |       \  /                                       
            /   |        \/                                        
     y = amplitude cos(frequency x + phase)
           \en Cosinusoid located along the X-axis of the local coordinate system. \n
	  Radius-vector of the curve in the method PointOn(double&t,MbCartPoint3D&r) is described by the vector function\n
    r(t) = position.origin + (position.axisX ((tmin + t) - phase) / frequency) + (amplitude cos(tmin + t) position.axisY).\n
    Cosinusoid is shown in the figure below. 
                t = 0                                              
      amplitude | /\            /\                                 
                |/  \          /  \                                
     t = -phase |    \ tmin  t/    \ tmax                          
         ______/|_____\|_____/______\|_____________________________
              / |      \    /        \                             
             /  |       \  /                                       
            /   |        \/                                        
     y = amplitude cos(frequency x + phase) \~
  \ingroup Curves_2D
*/
// ---
class MATH_CLASS MbCosinusoid: public MbCurve, public MbNestSyncItem {
private :
  MbPlacement    position;     ///< \ru Локальная система координат. \en Local coordinate system. 
  double         frequency;    ///< \ru Циклическая частота (angular frequency). \en Angular frequency. 
  double         phase;        ///< \ru Начальная фаза в радианах. \en Initial phase in radians. 
  double         amplitude;    ///< \ru Амплитуда. \en Amplitude. 
  double         tmin, tmax;   ///< \ru Область определения (по умолчанию - один период). \en Domain (one period by default). 
  mutable MbRect rect;         ///< \ru Габаритный прямоугольник. \en Bounding box. 
  mutable double metricLength; ///< \ru Метрическая длина. \en The metric length. 

public :
  // \ru Конструктор по амплитуде, начальной фазе и круговой частоте \en Constructor by amplitude, initial phase and angular frequency 
  MbCosinusoid( const double & am , const double & phase, const double & anf );
  // \ru Конструктор по амплитуде, начальной фазе и признаку начала параметра \en Constructor by amplitude, initial phase and attribute of the beginning of the parameter 
  // \ru ( от максимума косинуса ( x(0) = -фаза ) или от начала координат( x(0) = 0 ) ) \en ( from the maximum cosine ( x(0) = -phase ) or from the origin( x(0) = 0 ) ) 
  MbCosinusoid( const double & am , const double & phase = 0.0, bool maxBegin = true );
  // \ru Конструктор по расположению, амплитуде, начальной фазе и круговой частоте \en Constructor by location, amplitude, initial phase and angular frequency 
  MbCosinusoid( const MbPlacement & pos,
                const double      & am    = 0.0,
                const double      & phase = 0.0,
                const double      & anf   = 0.0 );
  // \ru Конструктор по расположению, амплитуде, начальной фазе и предельным параметрам \en Constructor by location, amplitude, initial phase and limit parameters 
  MbCosinusoid( const MbPlacement & pos, double am, double ph, double af, double t1, double t2 );
protected :
  MbCosinusoid( const MbCosinusoid & ); // \ru Конструктор копирования \en Copy-constructor 
public :
  virtual ~MbCosinusoid();

public:
  VISITING_CLASS( MbCosinusoid ); 

  // \ru \name Общие функции геометрического объекта. \en Common functions of a geometric object.

  virtual MbePlaneType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual bool        SetEqual  ( const MbPlaneItem & );       // \ru Сделать элементы равными \en Make the elements equal 
  virtual bool        IsBounded () const { return true; } // \ru Ограниченность кривой \en Bounded curve 
  virtual void        Transform ( const MbMatrix & matr, MbRegTransform * ireg = NULL, const MbSurface * newSurface = NULL );  // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move      ( const MbVector & to, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Сдвиг \en Translation 
  virtual void        Rotate    ( const MbCartPoint & pnt, const MbDirection & angle, MbRegTransform * = NULL, const MbSurface * newSurface = NULL ); // \ru Поворот \en Rotation 
  virtual	bool        IsSame    ( const MbPlaneItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual MbPlaneItem & Duplicate ( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void        AddYourGabaritTo( MbRect & r ) const;  // \ru Добавь свой габарит в прямой прям-к \en Add bounding box into a straight box 
  virtual void        CalculateGabarit( MbRect & r ) const;  // \ru Определить габариты кривой \en Determine the bounding box of the curve 
  virtual bool        IsVisibleInRect( const MbRect & r, bool exact = false ) const; // \ru Виден ли объект в заданном прямоугольнике \en Whether the object is visible in the given rectangle 
  using      MbCurve::IsVisibleInRect;        

  // \ru \name Общие функции кривой. \en Common functions of curve.

  virtual double      GetTMin () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool        IsClosed() const; // \ru Проверка замкнутости \en Check for closedness 
  // \ru Функции для работы внутри области определения кривой. \en Functions for working inside of the curve domain. \~
  virtual void        PointOn  ( double & t, MbCartPoint & p ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector    & v ) const; // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector    & v ) const; // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector    & v ) const; // \ru Третья производная \en Third derivative 
  // \ru Функции для работы внутри и вне области определения кривой. \en Functions for working inside and outside of the curve domain. \~
  virtual void       _PointOn  ( double t,  MbCartPoint & p ) const;
  virtual void       _FirstDer ( double t,  MbVector    & v ) const;
  virtual void       _SecondDer( double t,  MbVector    & v ) const;
  virtual void       _ThirdDer ( double t,  MbVector    & v ) const;
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint & pnt, MbVector & fir, MbVector * sec, MbVector * thir ) const;

  virtual bool        HasLength ( double & length ) const;
  virtual double      GetMetricLength() const; // \ru Метрическая длина \en The metric length 
  virtual void        Inverse( MbRegTransform * iReg = NULL );  // \ru Изменение направления кривой на противоположное \en Change to the opposite direction of a curve 

  virtual MbNurbs *   NurbsCurve( const MbCurveIntoNurbsInfo & ) const;

  virtual MbeState    DeletePart( double t1, double t2, MbCurve *& part2 ); // \ru Удалить часть кривой между параметрами t1 и t2 \en Delete a part of a curve between parameters t1 and t2 
  virtual MbeState    TrimmPart ( double t1, double t2, MbCurve *& part2 ); // \ru Оставить часть кривой между параметрами t1 и t2 \en Save a curve part between t1 and t2 parameters 

  virtual MbCurve *   Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 

  virtual void        IntersectHorizontal( double y, SArray<double> & cross ) const;  // \ru Пересечение кривой с горизонтальной прямой \en Intersection of curve with the horizontal line 
  virtual void        IntersectVertical  ( double x, SArray<double> & cross ) const;  // \ru Пересечение с вертикальной прямой \en Intersection with the vertical line 
  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculation of approximation step  
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага аппроксимации с учетом угла отклонения \en Calculation of approximation step with consideration of deviation angle 

  virtual double      PointProjection( const MbCartPoint & pnt ) const; // \ru Проекция точки на кривую \en Point projection on the curve 
  virtual bool        NearPointProjection( const MbCartPoint & pnt, double xEpsilon, double yEpsilon, 
                                           double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Проекция точки на кривую или её продолжение в области поиска проекции \en Point projection on the curve or its extension in the projection search area 

  virtual void        GetProperties( MbProperties & properties );  // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & properties );  // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisPoints( MbControlData & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
  // \ru Подобные ли кривые для объединения? \en Are the curves similar to merge? 
  virtual bool        IsSimilarToCurve( const MbCurve & curve, double precision = PARAM_PRECISION ) const; 

  const   MbPlacement & GetPlacement() const { return position; }
          MbPlacement & SetPlacement() { return position; }
          double      GetFrequency() const { return frequency; }
          double      GetPhase() const     { return phase; }
          double      GetAmplitude() const { return amplitude; }
          double      GetOwnTMin() const   { return tmin; }
          double      GetOwnTMax() const   { return tmax; }
          void        SetPlacement( const MbPlacement &pos );
          void        SetFrequency( double f ); 
          void        SetPhase    ( double p );
          void        SetAmplitude( double a );
          void        SetOwnTMin ( double t );
          void        SetOwnTMax ( double t );
  inline  void        CheckParam( double & t ) const;

          bool        IsHorizontal( double eps = Math::AngleEps ) const;  // \ru Проверка горизонтальности \en Check for horizontality 
          bool        IsVertical  ( double eps = Math::AngleEps ) const;  // \ru Проверка вертикальности \en Check for verticality 

          void        Init ( const MbCosinusoid & );
          void        Init ( double t1, double t2 ); 
          void        Init ( const MbPlacement & pos, double am, double ph, double af );
          void        Init1( CosinusoidPar & par, MbCartPoint & p1, MbCartPoint & p2, double & len, double & angle );
          void        Init2( CosinusoidPar & par, const MbCartPoint & p1, MbCartPoint & p2, const double & len, double & angle );
          void        Init3( CosinusoidPar & par, const MbCartPoint & p1, MbCartPoint & p2, double & len, const double & angle,
                             const DiskreteLengthData * = NULL );
          void        Init4( CosinusoidPar & par, MbCartPoint & p1, const MbCartPoint & p2, const double & len, double & angle );
          void        Init5( CosinusoidPar & par, MbCartPoint & p1, const MbCartPoint & p2, double & len, const double & angle,
                             const DiskreteLengthData * = NULL );
          void        Init6( CosinusoidPar & par, const MbCartPoint & p1, MbCartPoint & p2, const double & len, const double & angle );
          void        Init7( CosinusoidPar & par, MbCartPoint & p1, const MbCartPoint & p2, const double & len, const double & angle );
          void        Init8( CosinusoidPar & par, MbCartPoint & p1, MbCartPoint & p2, double & len, double & angle,
                             const DiskreteLengthData & diskrData, bool correctP1 );
          void        SpecInit( const CosinusoidPar &, const MbCartPoint & p1, double angle, double len );

private:
          void        operator = ( const MbCosinusoid & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbCosinusoid )
}; // MbCosinusoid

IMPL_PERSISTENT_OPS( MbCosinusoid )

//-------------------------------------------------------------------------------
// \ru Проверка параметра \en Check parameter 
// ---
inline void MbCosinusoid::CheckParam( double & t ) const {
  if ( t < 0 )
    t = 0;
  else if ( t > ( tmax - tmin ) )
    t = ( tmax - tmin );
}


#endif // __CUR_COSINUSOID_H
