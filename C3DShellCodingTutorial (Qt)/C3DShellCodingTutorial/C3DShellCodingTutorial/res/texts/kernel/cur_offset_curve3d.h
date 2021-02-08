////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Эквидистантная кривая в трехмерном пространстве.
         \en Offset curve in three-dimensional space. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_OFFSET_CURVE3D_H
#define __CUR_OFFSET_CURVE3D_H


#include <curve3d.h>
#include <mb_axis3d.h>
#include <mb_cube.h>


class  MATH_CLASS MbSpine;


//------------------------------------------------------------------------------
/** \brief \ru Эквидистантная кривая в трехмерном пространстве.
           \en Offset curve in three-dimensional space. \~
  \details \ru Эквидистантная кривая строится смещением точек базовой кривой вдоль некоторого вектора, 
    направление которого может меняться вдоль кривой. \n
    Вектор offset задаёт смещение начальной точки базовой криаой.
    В процессе движения вдоль кривой вектор offset сохраняет своё положение в движущейся локальной системе координат,
    начало которой совпадает с текущей точкой базовой кривой.
    Одна из осей движущейся локальной системы координат всегда совпадает с касательной базовой кривой, 
    а две другие оси ортогональны ей.
    Базовой кривой для эквидистантной кривой не может служить другая эквидистантная кривая.
    В подобной ситуации выполняется переход к первичной базовой кривой.
           \en Offset curve is constructed by shifting points of the base curve along some vector, 
    direction of which can be changed along the curve. \n
    Vector "offset" sets the offset of start point of the base curve.
    While moving along a curve the vector "offset" keeps the position in the moving local coordinate system,
    origin coincides with the current point of the base curve.
    One of the axes of the moving local coordinate system is always the same as the tangent of the base curve, 
    and the other two axes are orthogonal to it.
    Base curve for offset curve can not be other offset curve.
    In this situation it changes to the initial base curve. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbOffsetCurve3D : public MbCurve3D {
protected :
  MbSpine     *  basisCurve; ///< \ru Базовая кривая. \en The base curve. 
  double         tmin;       ///< \ru Начальный параметр basisCurve. \en Start parameter of basisCurve. 
  double         tmax;       ///< \ru Конечный  параметр basisCurve. \en End parameter of basisCurve. 
  bool           closed;     ///< \ru Замкнутость basisCurve. \en Closedness of basisCurve. 
  MbVector3D     offset;     ///< \ru Смещение в начальной точке. \en Offset in start point. 
  double         factorTmin; ///< \ru Множитель смещения offset в точке tmin базовой кривой. \en The offset multiplier in point tmin of base curve. 
  double         factorTmax; ///< \ru Множитель смещения offset в точке tmax базовой кривой. \en The offset multiplier in point tmax of base curve. 
  MbeOffsetType  type;       ///< \ru Тип смещения: константный, линейный или кубический. \en The type of offset: constant, or linear, or cubic.
  double         deltaTmin;  ///< \ru Увеличение tmin параметра базовой кривой. \en Increase of tmin of base curve parameter. 
  double         deltaTmax;  ///< \ru Увеличение tmax параметра базовой кривой. \en Increase of tmax of base curve parameter. 
  mutable MbCube cube;       ///< \ru Габаритный куб. \en Bounding box. 

public :
  /** \brief \ru Конструктор.
             \en Constructor. \~    
    \details \ru Конструктор эквидистантной кривой по спайну и вектору.\n
             \en Constructor by a curve and offset vector in start point.\n \~
    \param[in] c    - \ru Базовая кривая. \en The base curve. \~
    \param[in] off  - \ru Вектор смещения начальной точки кривой. \en Offset in start point. \~
    \param[in] same - \ru Использовать присланную кривую (true) или ее копию (false).
                      \en Use same curve (true) or copy (false). \~
    \param[in] ort  - \ru Ортогонализовать вектор к касательной кривой в начальной точке.
                      \en Ortogonalize offset vector (true) or same vector (false). \~
  */
  MbOffsetCurve3D( const MbCurve3D & c, const MbVector3D & off, bool same, bool ort, VERSION version = Math::DefaultMathVersion() );
private :
  MbOffsetCurve3D( const MbOffsetCurve3D & ); // \ru Не реализовано. \en Not implemented. 
protected:
  MbOffsetCurve3D( const MbOffsetCurve3D & init, MbRegDuplicate * ireg );

public :
  virtual ~MbOffsetCurve3D();

public:
  VISITING_CLASS( MbOffsetCurve3D );

          /** \brief \ru Инициализация по смещению и приращениям параметров.
                     \en Initialization by offset and increments of parameters. \~  
            \details \ru Смещение задано на краях параметрической области базовой кривой и может изменяться по константному, линейному и кубическому законам.\n  
              Приращение параметров нужно использовать для изменения области определения кривой относительно базовой кривой.
                     \en The offset displacement is defined in the begin and the end of the parametric region of the base curve and can be changed by constant, linear and cubic laws.\n  
              Increment of parameters needs to be used for change of curve domain relative to base curve. \~          
            \param[in] d1 -  \ru Смещение в точке Tmin базовой кривой.
                             \en Offset distance on point Tmin of base curve. \~
            \param[in] d2 -  \ru Смещение в точке Tmax базовой кривой.
                             \en Offset distance on point Tmax of base curve. \~
            \param[in] t  -  \ru Тип смещения точек: константный, линейный или кубический.
                             \en The offset type: constant, or linear, or cubic. \~
            \param[in] dt1 - \ru Изменение tmin параметра
                             \en The change of tmin parameter \~
            \param[in] dt2 - \ru Изменение tmax параметра
                             \en The change of tmax parameter \~
          */
          void        Init( double d1, double d2, MbeOffsetType t, double dt1, double dt2 );  

  // \ru Общие функции математического объекта \en Common functions of the mathematical object 

  virtual MbeSpaceType  IsA() const; // \ru Тип элемента \en Type of element 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual	bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const;
  virtual bool        SetEqual ( const MbSpaceItem & );       // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * ireg ); // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * ireg ); // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * ireg ); // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual void        Refresh  (); // \ru Сбросить все временные данные \en Reset all temporary data 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.
  virtual void        AddYourGabaritTo( MbCube & ) const; // \ru Добавь свой габарит в куб \en Add bounding box into a cube 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems  ( RPArray<MbSpaceItem> & );  // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Общие функции кривой \en Common functions of curve 

  virtual double      GetTMin() const;
  virtual double      GetTMax() const;
  virtual bool        IsClosed() const; // \ru Замкнутость кривой \en A curve closedness 
  virtual double      GetPeriod() const; // \ru Период кривой \en Curve period 
  // \ru Функции кривой для работы в области определения параметрической кривой \en Functions of curve for working at parametric curve domain 
  virtual void        PointOn  ( double & t, MbCartPoint3D & p ) const; // \ru Точка на кривой \en Point on curve 
  virtual void        FirstDer ( double & t, MbVector3D & fd ) const;     // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector3D & sd ) const;     // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector3D & td ) const;     // \ru Третья производная по t \en Third derivative with respect to t 

  // \ru ЗАКОМЕНТАРЕНО в связи с необходимостью использовать строгое продолжение по касательной \en COMMENTED because it is necessary to use a strong extension by the tangent  
  //virtual void       _PointOn  ( double t, MbCartPoint3D &p ) const;    // \ru Точка на расширенной кривой \en Point on the extended curve 
  //virtual void       _FirstDer ( double t, MbVector3D &fd ) const;      // \ru Первая производная \en The first derivative 
  //virtual void       _SecondDer( double t, MbVector3D &sd ) const;      // \ru Вторая производная \en The second derivative 
  //virtual void       _ThirdDer ( double t, MbVector3D &td ) const;      // \ru Третья производная по t \en The third derivative with respect to t 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  virtual double      Step( double t, double sag ) const; // \ru Вычисление шага аппроксимации \en Calculation of approximation step 
  virtual double      DeviationStep( double t, double angle ) const;

  virtual const MbCurve3D & GetBasisCurve() const;
  virtual       MbCurve3D & SetBasisCurve();
//virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 

  virtual size_t      GetCount() const;
  virtual void        ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 
  virtual bool        IsStraight() const; // \ru Является ли линия прямолинейной \en Whether the line is straight 
  virtual bool        IsPlanar  () const; // \ru Является ли кривая плоской \en Whether a curve is planar 

  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const; // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if curve is planar 

  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

  /// \ru Смещение в начальной точке. \en Offset in the start point. 
  const MbVector3D &  GetOffsetVector() const { return offset; } 
          // \ru Тип смещения точек. \en The type of points offset.
          MbeOffsetType GetOffsetType() const { return type; }
          // \ru Постоянное ли смещение точек? \en Is const the offset type?
          bool        IsConstOffset() const { return ( (type == off_Empty) || (type == off_Const) ); }
          // \ru Множитель смещения. \en The offset multiplier. 
          double      GetFactor( size_t i = 0 ) const { 
            if ( i == 1 ) return factorTmax;
            return factorTmin;
          }
          
          /** \brief \ru Установить множитель смещения. \en Set offset multiplier. \~  
            \param[in] d - \ru Новый множитель смещения. \en New offset multiplier. \~
          */
          void        SetFactor( double d, size_t i = 0 );
          // \ru Проверить факторы и тип. \en Check factors and typr.
          void        CheckFactor();

  const   MbCube &    GetGabarit() const { if ( cube.IsEmpty() ) CalculateGabarit( cube ); return cube; } // \ru Выдать габарит кривой \en Get the bounding box of curve 
          bool        IsSelfIntersect() const;
          /** \brief \ru Поиск точек излома оффсетной кривой.
                     \en Search of break points of the offset curve. \~
          \details \ru Для нахождения точек точек излома используется характеристическая функция Ratio(),
                   представляющая собой разность аналитически и численно посчитанной производной деленную 
                   на модуль аналитической производной и величину шага, использованного для численного рассчета производной. 
                   Увеличение этой функции на порядок по сравнению с ее значением в гладкой области означает точку излома. \n
                   \en To find the break points using the characteristic function Ratio(),
                   which represents a difference between the analytical and numerical calculated derivative divided 
                   by module of analytical derivative and step used for numerical calculation of the derivative. 
                   Increase of this function on the order in comparison with its value in smooth region is a break point. \n \~
          \param[out] breakParams - \ru Массив параметров точек излома
                                    \en Parameter array of break points \~
          */
          void        FindBreakParams( SArray<double> & breakParams ) const;
          int         ExtendedParam( double &t ) const; // \ru Проверка, лежит ли параметр в пределах \en Check if parameter is in range 

private:
          // \ru Вычисление множителя смещения и его производных. \en The offset multiplier and it derivatives.
          double      Factor0  ( double t ) const;
          double      FactorT  ( double t ) const;
          double      FactorTT ( double t ) const;
          double      FactorTTT( double t ) const;

          void        operator = ( const MbOffsetCurve3D & ); // \ru Не реализовано. \en Not implemented. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbOffsetCurve3D )
};

IMPL_PERSISTENT_OPS( MbOffsetCurve3D )


#endif // __CUR_OFFSET_CURVE3D_H
