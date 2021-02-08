////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Контур в трёхмерном пространстве.
         \en Contour in three-dimensional space. \~ 

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CONTOUR3D_H
#define __CUR_CONTOUR3D_H


#include <templ_rp_array.h>
#include <templ_sptr.h>
#include <curve3d.h>
#include <cur_line_segment3d.h>
#include <mb_cube.h>


class  SimpleNameArray;


class  MATH_CLASS MbContour3D;
namespace c3d // namespace C3D
{
typedef SPtr<MbContour3D>                       SpaceContourSPtr;
typedef SPtr<const MbContour3D>                 ConstSpaceContourSPtr;

typedef std::vector<MbContour3D *>              SpaceContoursVector;
typedef std::vector<const MbContour3D *>        ConstSpaceContoursVector;

typedef std::vector<SpaceContourSPtr>           SpaceContoursSPtrVector;
typedef std::vector<ConstSpaceContourSPtr>      ConstSpaceContoursSPtrVector;
}


//------------------------------------------------------------------------------
/** \brief \ru Контур в трёхмерном пространстве.
           \en Contour in three-dimensional space. \~ 
  \details \ru Контур представляет собой составную кривую, в которой начало каждого последующего сегмента стыкуется с концом предыдущего.
    Контур является замкнутым, если конец последнего сегмента стыкуется с началом первого сегмента.\n
    Если сегменты составной кривой стыкуются не гладко, то составная кривая будет иметь изломы. 
    В общем случае в местах стыковки сегментов производные составной кривой терпят разрыв по длине и направлению. \n
      Начальное значение параметра составной кривой равно нулю. 
    Параметрическая длина составной кривой равна сумме параметрических длин составляющих её сегментов. \n
    При вычислении радиуса-вектора составной кривой сначала определяется сегмент, 
    которому соответствует значение параметра составной кривой, и соответствующее значение собственного параметра этого сегмента. 
    Далее вычисляется радиус-вектор сегмента, который и будет радиусом-вектором составной кривой. \n
      В качестве сегментов составной кривой не используются другие составные кривые. 
    Если составную кривую нужно построить на основе других составных кривых, 
    то последние должны рассматриваться как совокупность составляющих их кривых, а не как единые кривые.\n 
    Трёхмерный контур используется для пространственного моделирования, например, для описания траекторий движения.\n
           \en Contour is a composite curve in which the beginning of each subsequent segment is joined to the end of the previous one.
    Contour is closed if the end of last segment is joined to the beginning of the first segment.\n
    If the segments of a composite curve are not smoothly joined then the composite curve will have breaks. 
    In general case in places of joining segments derivatives of a composite curve have discontinuity along the length and direction. \n
      The initial value of the composite curve is equal to zero. 
    The parametric length of a composite curve is equal to the sum of the parametric lengths of components of its segments. \n
    When the calculation of the radius-vector of a composite curve segment is determined at first, 
    the value of composite curve parameter and the corresponding value of the own parameters of this segment corresponds to this segment. 
    Then computes the radius-vector of the segment which will be the radius-vector of the composite curve. \n
      Other composite curves are not used as segments of the composite curve. 
    If it is required to create a composite curve based on other composite curves, 
    then the latter must be regarded as a set of their curves, and not as single curves. \n 
    The three-dimensional contour is used for space modeling e.g. for describing trajectories. \n \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbContour3D : public MbCurve3D {
protected :
  RPArray<MbCurve3D> segments;    ///< \ru Множество сегментов контура. \en A set of contour segments. 
  bool               closed;      ///< \ru Признак замкнутости кривой. \en An attribute of curve closedness. 
  double             paramLength; ///< \ru Параметрическая длина контура. \en Parametric length of a contour. 

public :
  MbContour3D(); ///< \ru Пустой контур. \en Empty contour. 
  /// \ru Конструктор по набору кривых. \en Constructor by curves. 
  template <class CurvesVector>
  MbContour3D( const CurvesVector & initSegments, bool sameCurves ); // \ru sameCurves - кривые или их копии \en SameCurves - curves or their copies 
protected:
  MbContour3D( const MbContour3D &, MbRegDuplicate * ); ///< \ru Конструктор копирования. \en Copy constructor.
public :
  virtual ~MbContour3D();

public:
  VISITING_CLASS( MbContour3D );

  /** \ru \name Общие функции геометрического объекта.
      \en \name Common functions of a geometric object.
      \{ */

  virtual MbeSpaceType  IsA()  const; // \ru Тип элемента \en Type of element 
  virtual MbeSpaceType  Type() const; // \ru Групповой тип элемента \en Group element type 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента \en Create a copy of the element 
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Является ли объект копией \en Whether the object is a copy 
  virtual bool        SetEqual ( const MbSpaceItem & );       // \ru Сделать равным \en Make equal 
  virtual bool        IsSimilar( const MbSpaceItem & ) const; // \ru Являются ли объекты подобными \en Whether the objects are similar 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL );   // \ru Преобразовать элемент согласно матрице \en Transform element according to the matrix 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL );   // \ru Сдвиг \en Translation 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL );   // \ru Повернуть вокруг оси \en Rotate about an axis 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const;             // \ru Расстояние до точки \en Distance to a point 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual bool        IsSpaceSame( const MbSpaceItem & item, double eps = METRIC_REGION ) const; // \ru Являются ли объекты идентичными в пространстве \en Are the objects identical in space? 

  // \ru Общие функции кривой \en Common functions of curve 

  /** \} */
  /** \ru \name Функции описания области определения кривой.
      \en \name Functions describing the domain of a curve.
      \{ */
  virtual double      GetTMin () const; // \ru Вернуть минимальное значение параметра \en Get the minimum value of parameter 
  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра \en Get the maximum value of parameter 
  virtual bool        IsClosed() const; // \ru Проверка замкнутости кривой \en Check for curve closedness 
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Являются ли стыки контура\кривой гладкими? \en Whether the joints of contour\curve are smooth. 
  virtual bool        IsStraight() const; // \ru Признак прямолинейности кривой \en An attribute of curve straightness 
  /** \} */

  /** \ru \name Функции для работы в области определения кривой. 
            Функции PointOn, FirstDer, SecondDer, ThirdDer,... корректируют параметр
            при выходе его за пределы области определения.
      \en \name Functions for working in the domain of a curve. 
            Functions: PointOn, FirstDer, SecondDer, ThirdDer,... correct the parameter
            when it is outside domain.
      \{ */
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Точка на кривой \en Point on the curve 
  virtual void        FirstDer ( double & t, MbVector3D & ) const;    // \ru Первая производная \en First derivative 
  virtual void        SecondDer( double & t, MbVector3D & ) const;    // \ru Вторая производная \en Second derivative 
  virtual void        ThirdDer ( double & t, MbVector3D & ) const;    // \ru Третья производная по t \en Third derivative with respect to t 
  virtual void        Normal( double  & t, MbVector3D & ) const;      // \ru Вычислить вектор главной нормали. \en Calculate main normal vector. 
  /** \} */

  /** \ru \name Функции для работы внутри и вне области определения кривой. 
            Функции _PointOn, _FirstDer, _SecondDer, _ThirdDer,... не корректируют параметр
            при выходе за пределы области определения. При выходе за область определения незамкнутая
            кривая, в общем случае, продолжается по касательной, которую она имеет на соответствующем конце.
      \en \name Function for working inside and outside of the curve domain. 
            Function _PointOn, _FirstDer, _SecondDer, _ThirdDer,... do not correct a parameter
            when it is outside domain. When parameter is out of domain bounds, an unclosed
            curve is extended by tangent vector at corresponding end point in general case.
      \{ */
  virtual void       _PointOn  ( double t, MbCartPoint3D & ) const; // \ru Точка на расширенной кривой \en Point on the extended curve 
  virtual void       _FirstDer ( double t, MbVector3D & ) const;    // \ru Первая производная \en First derivative 
  virtual void       _SecondDer( double t, MbVector3D & ) const;    // \ru Вторая производная \en Second derivative 
  virtual void       _ThirdDer ( double t, MbVector3D & ) const;    // \ru Третья производная по t \en Third derivative with respect to t 
  virtual void       _Normal( double  t, MbVector3D & ) const;      // \ru Вычислить вектор главной нормали. \en Calculate main normal vector. 
  /** \} */

  /** \ru \name Функции доступа к группе данных для работы внутри и вне области определения параметра кривой.
      \en \name Functions for get of the group of data inside and outside the curve's domain of parameter.
      \{ */
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;
  /** \} */

  /** \ru \name Функции движения по кривой
      \en \name Functions of the motion along the curve
    \{ */
  virtual double      Step         ( double t, double sag ) const; // \ru Вычисление шага по стрелке прогиба. \en Calculation of parameter step by the sag.
  virtual double      DeviationStep( double t, double angle ) const; // \ru Вычисление шага по углу отклонения нормали. \en Calculation of parameter step by the deviation angle.   
  virtual double      MetricStep   ( double t, double length ) const; // \ru Вычисление шага параметра по длине. \en Calculation of parameter step by the given length. 
  /** \} */
  /** \ru \name Общие функции кривой
      \en \name Common functions of curve
      \{ */

  /// \ru Вычислить кривизну кривой. \en Calculate curvature of curve. 
  virtual double  Curvature( double t ) const;
  // \ru Преобразование в NURBS кривую \en Transform to NURBS-curve 
  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const;
  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создание усеченной кривой \en Creation of a trimmed curve 
  virtual void        Inverse( MbRegTransform * iReg = NULL ); // \ru Изменить направление \en Change direction 
  /// \ru Подобные ли кривые для объединения (слива). \en Whether the curves to union (joining) are similar. 
  virtual bool        IsSimilarToCurve( const MbCurve3D & other, double precision = METRIC_PRECISION ) const;

  // \ru Все проекции точки на кривую \en All point projections on the curve 
  // \ru Ближайшая проекция точки на кривую \en The nearest point projection to the curve 
  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const;

  virtual double      CalculateMetricLength() const;      // \ru Посчитать метрическую длину \en Calculate the metric length 
  virtual double      CalculateLength( double t1, double t2 ) const;
  virtual bool        DistanceAlong( double & t, double len, int curveDir, double eps = Math::metricPrecision,
                                     VERSION version = Math::DefaultMathVersion() ) const; 

  virtual void        CalculateLocalGabarit( const MbMatrix3D &, MbCube & ) const; // \ru Рассчитать габарит относительно л.с.к. \en Calculate bounding box relative to the local coordinate system. 
  virtual void        CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой \en Calculate the bounding box of curve 
  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                            VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой \en Get a planar projection of curve 
  virtual size_t      GetCount() const;
  virtual void        ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменение носителя \en Changing of carrier 
  virtual double      GetRadius() const; // \ru Дать физический радиус объекта или ноль, если это невозможно. \en Get the physical radius of the object or null if it impossible.

  virtual bool        IsPlanar  () const; // \ru Является ли кривая плоской \en Whether the curve is planar? 
  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const; // \ru Заполнить плейсемент, ести кривая плоская \en Fill the placement if curve is planar 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую) \en Give a planar curve and placement, if the spatial curve is planar (after using the DeleteItem must be called on a three-dimensional curve) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  /// \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы). \en Get surface curve if the space curve is surface (after the using call DeleteItem for arguments) 
  virtual bool        GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;
  virtual void        GetWeightCentre( MbCartPoint3D & ) const;
  virtual void        GetCentre      ( MbCartPoint3D & ) const;

  virtual void        CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.
  virtual void        Refresh(); // \ru Сбросить все временные данные \en Reset all temporary data 

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта \en Get properties of the object 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта \en Set properties of the object 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & ); // \ru Дать базовые объекты \en Get the basis objects 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  /** \brief \ru Непрерывна ли первая производная кривой по длине и направлению?
              \en Have the first derivative of the curve the continuous length and direction?
    \details \ru Отсутствуют ли разрывы производной по длине и направлению в стыках сегментов контура? \n
              \en Are absent any discontinuities of the derivative at length or at direction in the junction of path segments? \n \~
    \param[out] contLength - \ru Непрерывность длины (да/нет).
                              \en The length is continuous (true/false). \~
    \param[out] contDirect - \ru Непрерывность направления (да/нет).
                              \en The direction of the first derivative is continuous (true/false). \~
    \param[out] params    - \ru Параметры точек, в которых происходит разрыв направления.
                              \en The parameters of the points at which the direction break occurs. \~
    \param[in]  epsilon    - \ru Погрешность вычисления.
                              \en The accuracy of the calculation. \~
  */
  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const;

  /** \brief \ru Устранить разрывы производных по длине в стыках сегментов.
              \en Eliminate the discontinuities of the derivatives of the length of the joints of the segments.
    \details \ru Устранить разрывы производных по длине в стыках сегментов. \n
              \en Eliminate the discontinuities of the derivatives of the length of the joints of the segments. \n \~
    \param[in]  epsilon    - \ru Погрешность вычисления.
                              \en The accuracy of the calculation. \~
  */
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON );

  /// \ru Найти все особые точки функции кривизны кривой. \en Find all the special points of the curvature function of the curve.
  virtual void    GetCurvatureSpecialPoints( std::vector<c3d::DoublePair> & points ) const;

  /** \} */
  /** \ru \name Функции работы с сегментами контура
      \en \name Function for working with segments of contour
      \{ */

          /// \ru Инициализация по набору кривых (sameCurves - кривые или их копии). \en Initialize by curves (sameCurves - curves or their copies). 
          template <class CurvesVector>
          bool        Init( const CurvesVector & initSegments, bool sameCurves, bool cls );
          /// \ru Инициализация по набору кривых (замкнутый контур). \en Initialize by curves (closed contour). 
          template <class PointsVector>
          bool        Init( const PointsVector & points );

          ptrdiff_t   FindSegment( double & t, double & tSeg ) const; ///< \ru Нахождение сегмента контура. \en Finding of a contour segment. 
          size_t      GetSegmentsCount() const { return segments.size(); } ///< \ru Выдать количество сегментов контура. \en Get the number of contour segments. 
          template <class CurvesVector>
          void        GetSegments( CurvesVector & curves ) const; ///< \ru Получить кривые контура. \en Get contour segments. 
          void        DetachSegments(); ///< \ru Отцепить все сегменты контура. \en Detach all segments of contour. 
          void        DeleteSegments(); ///< \ru Отсоединить используемые сегменты и удалить остальные. \en Delete used segments and remove other segments. 
          void        DeleteSegment( size_t ind ); ///< \ru Удалить сегмент контура. \en Delete the segment of contour. 
          MbCurve3D * DetachSegment( size_t ind ); ///< \ru Отцепить сегмент контура. \en Detach the segment of contour. 
  const   MbCurve3D * GetSegment( size_t ind ) const { return segments[ind];  } ///< \ru Выдать сегмент контура по индексу. \en Get contour segment by the index.
          MbCurve3D * SetSegment( size_t ind )       { return segments[ind];  } ///< \ru Выдать сегмент контура по индексу. \en Get contour segment by the index. 
          void        SetSegment     ( MbCurve3D & newSegment, size_t ind, bool same ); ///< \ru Заменить сегмент в контуре. \en Replace a segment in the contour. 
          void        AddSegment     ( MbCurve3D & newSegment,             bool same ); ///< \ru Добавить сегмент в контур. \en Add a segment to the contour. 
          void        AddAtSegment   ( MbCurve3D & newSegment, size_t ind, bool same ); ///< \ru Добавить сегмент в контур перед сегментом с индексом ind. \en Add a segment to the contour before the segment with index ind. 
          void        AddAfterSegment( MbCurve3D & newSegment, size_t ind, bool same ); ///< \ru Добавить сегмент в контур после сегмента с индексом ind. \en Add a segment to the contour after the segment with index ind. 
          MbCurve3D * AddSegment( MbCurve3D & pBasis, double t1, double t2, int sense );
          void        SegmentsAdd( MbCurve3D & newSegment, bool calculateParamLength = true ); ///< \ru Добавить сегмент в контур без проверки. \en Add a segment to the contour without checking. 
          bool        GetCornerAngle( size_t index, MbCartPoint3D & origin, MbVector3D & axis, MbVector3D & tau, double & angle,
                                      double angleEps ) const;
          /// \ru Cбросить переменные кэширования. \en Reset variables caching.
          void        Clear() {
            CalculateParamLengthAndClosed(); // \ru Параметрическая длина контура. \en Parametric length of a contour. 
          }
          bool        IsSimple() const; ///< \ru Состоит ли контур из отрезков и дуг? \en Whether the contour consists of the segments and arcs? 
          /// \ru Управление распределением памяти в массиве segments. \en Control of memory allocation in the array "segments". 
          void        SegmentsReserve( size_t additionalSpace ) { segments.Reserve( additionalSpace ); } ///< \ru Зарезервировать место. \en Reserve space.  
          void        SegmentsAdjust ()                         { segments.Adjust();                   } ///< \ru Удалить лишнюю память. \en Free the unnecessary memory. 
          /// \ru Добавить новый элемент в начало или конец контура. \en Add the new element to the beginning or end of contour. 
          bool        AddCurveWithRuledCheck( MbCurve3D &, double absEps, bool toEndOnly = false, bool checkSame = true,
                                              VERSION version = Math::DefaultMathVersion() );
          /// \ru Проверка непрерывности контура. \en Check for contour continuity. 
          bool        CheckConnection( double eps = METRIC_PRECISION ) const;
          void        CalculateParamLength(); ///< \ru Рассчитать параметрическую длину. \en Calculate parametric length. 
          void        CheckClosed( double eps ); ///< \ru Установить признак замкнутости контура. \en Set the closedness attribute of contour. 
          /// \ru Содержат ли контура идентичные сегменты \en Whether contours contains identical segments. 
          bool        IsSameSegments( const MbContour3D & ) const;
          void        FindCorner( size_t index, MbCartPoint3D & ) const;

  /** \} */
  /** \ru \name Функции работы с именами контура.
      \en \name Functions for working with names of contours.
      \{ */

          /** \brief \ru Дать имена сегментов.
                     \en Get names of segments. \~
            \details \ru Дать имена сегментов контура.\n
                     \en Get names of contour segments. \n \~
            \param[out] names - \ru Имена сегментов.
                                \en Names of segments \~
          */
          void        GetSegmentsNames(       SimpleNameArray & names ) const;

          /** \brief \ru Установить имена сегментов.
                     \en Set names of segments. \~
            \details \ru Установить имена сегментов контура по массиву имен.\n
                     \en Set names of contour segments by array of names. \n \~
            \param[in] names - \ru Набор имен.
                               \en A set of names. \~
          */
          void        SetSegmentsNames( const SimpleNameArray & names );

  /** \} */

private:
          void        SetClosed(); // \ru Проверить и установить признак замкнутости контура. \en Check and set closedness attribute of contour. 
          void        CalculateParamLengthAndClosed();  // \ru Посчитать параметрическую длину и признак замкнутости \en Calculate parametric length and closedness attribute 
          ptrdiff_t  _FindSegment( double & t, double & tSeg ) const; // \ru Нахождение сегмента контура \en Finding of a contour segment 

DECLARE_PERSISTENT_CLASS_NEW_DEL( MbContour3D )
OBVIOUS_PRIVATE_COPY( MbContour3D )
};

IMPL_PERSISTENT_OPS( MbContour3D )


//------------------------------------------------------------------------------
// \ru Конструктор по набору кривых. \en Constructor by curves. 
// ---
template <class CurvesVector>
MbContour3D::MbContour3D( const CurvesVector & initSegments, bool sameCurves )
  : MbCurve3D  (                        )
  , segments   ( initSegments.size(), 1 )
  , closed     ( false                  )
  , paramLength( 0.0                    ) // параметрическая длина контура не рассчитана 
{
  const size_t count = initSegments.size();

  if ( count > 0 ) {
    MbRegDuplicate * ireg = NULL;
    MbAutoRegDuplicate autoreg( ireg );
    for ( size_t i = 0; i < count; ++i ) {
      const MbCurve3D * initSegment = initSegments[i];
      MbCurve3D * segment = sameCurves ? const_cast<MbCurve3D *>(initSegment) : static_cast<MbCurve3D *>(&initSegment->Duplicate(ireg));
      segments.push_back( segment );
      segment->AddRef();
    }
    CalculateParamLengthAndClosed();
  }
}

//------------------------------------------------------------------------------
// \ru Инициализация по набору кривых. \en Initialize by curves. 
// ---
template <class CurvesVector>
bool MbContour3D::Init( const CurvesVector & initSegments, bool sameCurves, bool cls )
{
  size_t count = initSegments.size();

  if ( count > 0 ) {
    ::AddRefItems( initSegments );
    DeleteSegments();
    for ( size_t i = 0; i < count; ++i ) {
      if ( initSegments[i] != NULL ) {
        MbCurve3D * initSegment = &const_cast<MbCurve3D &>( *initSegments[i] );
        MbCurve3D * segment = sameCurves ? initSegment : static_cast<MbCurve3D *>(&initSegment->Duplicate());
        segments.push_back( segment );
        segment->AddRef();
      }
    }
    ::DecRefItems( initSegments );
    CalculateParamLength();
    closed = cls;
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
// \ru Инициализация по набору точек. \en Initialize by points. 
// ---
template <class PointsVector>
bool MbContour3D::Init( const PointsVector & points )
{
  size_t count = points.size();

  if ( count > 1 ) {
    DeleteSegments();
    segments.reserve( count );
    for ( size_t i = 0; i < count; ++i ) {
      MbLineSegment3D * seg = new MbLineSegment3D( points[i], points[ (i + 1) % count ] );
      segments.push_back( seg );
      seg->AddRef();
    }
    CalculateParamLength();
    closed = true;
    return true;
  }

  return false;
}

//------------------------------------------------------------------------------
// \ru Получить кривые контура. \en Get contour segments. 
// ---
template <class CurvesVector>
void MbContour3D::GetSegments( CurvesVector & curves ) const
{
  size_t segmentsCnt = segments.size();
  curves.reserve( curves.size() + segmentsCnt );
  SPtr<MbCurve3D> curve;
  for ( size_t k = 0; k < segmentsCnt; ++k ) {
    curve = const_cast<MbCurve3D *>(segments[k]);
    if ( curve != NULL ) {
      curves.push_back( curve );
      ::DetachItem( curve );
    }
  }
}


//------------------------------------------------------------------------------
/** \brief \ru Усечь контур.
           \en Trim a contour. \~
    \details \ru Усечь контур. Расширенная версия функции контура Trimmed
             \en Trim a contour. This function is extended version of contour's function Trimmed. \~
    \param[in] t1    - \ru Параметр, соответствующий началу усеченной кривой.
                       \en Parameter corresponding to start of a trimmed curve. \~
    \param[in] t2    - \ru Параметр, соответствующий концу усеченной кривой.
                       \en Parameter corresponding to end of a trimmed curve. \~
    \param[in] sense - \ru Направление усеченной кривой относительно исходной.\n
                       sense =  1 - направление кривой сохраняется.
                       sense = -1 - направление кривой меняется на обратное.
                       \en Direction of a trimmed curve in relation to an initial curve.
                       sense =  1 - direction does not change.
                       sense = -1 - direction changes to the opposite value. \~
    \param[in] useTrimmedOnly - \ru При усечении создавать кривые MbTrimmedCurve3D.
                                \en A truncated segment is always curve MbTrimmedCurve3D. \~
    \result \ru Построенная усеченная кривая.
            \en A constructed trimmed curve. \~
    \ingroup Curves_3D
  */
// ---
MATH_FUNC (MbCurve3D *) TrimContour( const MbContour3D & cntr, double t1, double t2, int sense,
                                     bool useTrimmedOnly );

#endif // __CUR_CONTOUR3D_H
