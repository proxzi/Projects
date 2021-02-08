////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Контур на поверхности.
         \en Contour on surface. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __CUR_CONTOUR_ON_SURFACE_H
#define __CUR_CONTOUR_ON_SURFACE_H

#include <curve3d.h>
#include <mb_cube.h>
#include <tool_mutex.h>


class  MATH_CLASS MbMatrix;
class  MATH_CLASS MbContour;
class  MATH_CLASS MbSurface;
class  MATH_CLASS MbSurfaceCurve;
class             MbCurveIntoNurbsInfo;
class             MbSegmentsSearchTree;

//------------------------------------------------------------------------------
/** \brief \ru Контур на поверхности.
           \en Contour on surface. \~ 
  \details \ru Контур на поверхности представляет собой трёхмерную составную кривую,
    полученную движением вдоль двумерного контура MbContour,
    расположенного в пространстве параметров некоторой поверхности MbSurface. \n
    Контур на поверхности используется: 
    для описания области определения параметров поверхности.
           \en The contour on surface is a three-dimensional composite curve,
    obtained by the motion along the two-dimensional contour MbContour,
    located in the parameters space of the surface MbSurface. \n
    The contour on a surface is used: 
    to describe the domain of the surface parameters. \~
  \ingroup Curves_3D
*/
// ---
class MATH_CLASS MbContourOnSurface : public MbCurve3D, public MbSyncItem {

protected :
  MbSurface *                     surface;       ///< \ru Указатель на базовую поверхность (всегда не NULL). \en The pointer to the base surface (this value is never NULL). 
  MbContour *                     contour;       ///< \ru Указатель на 2D-контур в плоскости параметров поверхности (всегда не NULL). \en The pointer to 2D-contour in the plane of the surface parameters (this value is never NULL). 
  mutable double                  area;          ///< \ru Площадь 2D-контура со знаком. \en The area of 2D-contour with sign. 
  mutable MbCube                  cube;          ///< \ru Габаритный куб. \en Bounding box. 
  mutable double                  metricLength;  ///< \ru Метрическая длина. \en The metric length. 
  mutable MbSegmentsSearchTree *  searchTree;    ///< \ru Дерево габаритов для ускорения поиска сегментов. \en A tree of bounding boxes for segment search acceleration. 

public :
  /// \ru Конструктор по поверхности, контуру и флагу использования оригинала контура. \en Constructor by surface, contour and flag of using original contour. 
  MbContourOnSurface( const MbSurface &, const MbContour &, bool same );
  /// \ru Конструктор по поверхности и направлению обхода поверхности. \en Constructor by a surface and the traverse direction of surface 
  MbContourOnSurface( const MbSurface &, int sense );

protected:
  /// \ru Конструктор копирования. \en Copy-constructor. 
  MbContourOnSurface( const MbContourOnSurface & init, MbRegDuplicate * );
  /// \ru Конструктор копирования контура с той же поверхностью для CurvesDuplicate(). \en Constructor to copy contour with the same surface for CurvesDuplicate(). 
  explicit MbContourOnSurface( const MbContourOnSurface * );
  /// \ru Конструктор по поверхности. \en Constructor by a surface. 
  MbContourOnSurface( const MbSurface & surf );

private:
  MbContourOnSurface( const MbContourOnSurface & ); // \ru Не реализовано !!! \en Not implemented !!! 

public :
  virtual ~MbContourOnSurface();

public :
  VISITING_CLASS( MbContourOnSurface );

  // \ru Общие функции математического объекта. \en The common functions of the mathematical object. 

  virtual MbeSpaceType  IsA() const; // \ru Дать тип элемента. \en Get a type of the element. 
  virtual MbeSpaceType  Type() const; // \ru Дать тип элемента. \en Get a type of the element. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Сделать копию элемента. \en Create a copy of the element. 
  /// \ru Сделать копию на той же поверхности. \en Create a copy on the same surface. 
  virtual MbContourOnSurface & CurvesDuplicate() const;
  virtual bool        IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Определить, является ли копией данного объекта? \en Determine whether the object is copy of a given object. 
  virtual bool        SetEqual ( const MbSpaceItem & ); // \ru Сделать равным. \en Make equal. 
  virtual bool        IsSimilar( const MbSpaceItem & ) const; // \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
  virtual void        Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать элемент согласно матрице. \en Transform element according to the matrix. 
  virtual void        Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Move along a vector. 
  virtual void        Rotate   ( const MbAxis3D &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  virtual double      DistanceToPoint( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate the distance to a point. 
  virtual void        AddYourGabaritTo( MbCube &r ) const; // \ru Добавить габарит в куб. \en Add bounding box into a cube. 
  virtual void        CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.
  virtual void        Refresh(); // \ru Сбросить все временные данные. \en Reset all temporary data. 
  virtual void        PrepareIntegralData( const bool forced ) const; // \ru Рассчитать временные (mutable) данные объекта. \en Calculate temporary (mutable) data of an object.

  virtual void        GetProperties( MbProperties & ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void        SetProperties( const MbProperties & ); // \ru Записать свойства объекта. \en Set properties of the object. 
  virtual void        GetBasisItems ( RPArray<MbSpaceItem> & );  // \ru Дать базовые поверхности. \en Get base surfaces. 
  virtual void        GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void        SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.
                      
  // \ru Общие функции кривой. \en Common functions of curve. 

  virtual double      GetTMax () const; // \ru Вернуть максимальное значение параметра. \en Get the maximum value of parameter. 
  virtual double      GetTMin () const; // \ru Вернуть минимальное значение параметра. \en Get the minimum value of parameter. 
  virtual bool        IsClosed() const; // \ru Проверить замкнутость кривой. \en Check for curve closedness. 
  // \ru Функции для работы в области определения. \en Functions for working in the definition domain. 
  virtual void        PointOn  ( double & t, MbCartPoint3D & ) const; // \ru Вычислить точку на кривой. \en Calculate point on the curve. 
  virtual void        FirstDer ( double & t, MbVector3D & )    const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void        SecondDer( double & t, MbVector3D & )    const; // \ru Вычислить вторую производную. \en Calculate the second derivative. 
  virtual void        ThirdDer ( double & t, MbVector3D & )    const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Функции для работы вне области определения. \en Functions for working outside of definition domain. 
  virtual void       _PointOn  ( double t, MbCartPoint3D & )  const; // \ru Вычислить точку на расширенной кривой. \en Calculate point on the extended curve. 
  virtual void       _FirstDer ( double t, MbVector3D & )     const; // \ru Вычислить первую производную. \en Calculate the first derivative. 
  virtual void       _SecondDer( double t, MbVector3D & )     const; // \ru Вычислить вторую производную \en Calculate the second derivative 
  virtual void       _ThirdDer ( double t, MbVector3D & )     const; // \ru Вычислить третью производную по t. \en Calculate the third derivative by t. 
  // \ru Вычислить значения точки и производных для заданного параметра. \en Calculate point and derivatives of object for given parameter. \~
  virtual void        Explore( double & t, bool ext,
                               MbCartPoint3D & pnt, MbVector3D & fir, MbVector3D * sec, MbVector3D * thir ) const;

  /// \ru Изменить ориентацию контура относительно поверхности. \en Change the contour orientation relative to a surface. 
  virtual void        Inverse( MbRegTransform * iReg = NULL );

  virtual MbNurbs3D * NurbsCurve( const MbCurveIntoNurbsInfo & ) const; // \ru Установить параметры NURBS. \en Set the NURBS parameters. 

  virtual MbCurve3D * Trimmed( double t1, double t2, int sense ) const; // \ru Создать усеченную кривую. \en Create the trimmed curve. 

  virtual double      Step( double t, double sag ) const; // \ru Вычислить шаг аппроксимации. \en Calculate the approximation step. 
  virtual double      DeviationStep( double t, double angle ) const; // \ru Определить шаг по заданному углу отклонения касательной. \en Determine the step by a given angle of tangent deviation. 

  virtual double      GetMetricLength() const; // \ru Вычислить метрическую длину кривой. \en Calculate the metric length of curve. 
  virtual double      GetLengthEvaluation() const; // \ru Оценить метрическую длину кривой. \en Evaluate the metric length of curve. 
  virtual double      CalculateMetricLength() const; // \ru Вычислить метрическую длину. \en Calculate the metric length. 
  virtual void        CalculateGabarit( MbCube & ) const; // \ru Вычислить габарит кривой. \en Calculate the bounding box of curve. 

  /// \ru Сбросить рассчитанный габарит. \en Reset the calculated bounding box. 
          void        SetDirtyGabarit() const { cube.SetEmpty(); }
  /// \ru Выдать габарит кривой. \en Get the bounding box of curve. 
  const   MbCube &    GetGabarit() const { if ( cube.IsEmpty() ) CalculateGabarit( cube ); return cube; }

  /// \ru Вычислить параметрический габарит контура. \en Calculate the parametric bounding box of the contour. 
  virtual void        CalculateUVLimits( MbRect & uvRect );
  virtual void        ChangeCarrier( const MbSpaceItem & item, MbSpaceItem & init ); // \ru Изменить носителя. \en Change the carrier. 
  virtual bool        ChangeCarrierBorne( const MbSpaceItem & item, MbSpaceItem & init, const MbMatrix & matr ); // \ru Изменить носимые элементы. \en Change carrier elements. 
  /// \ru Заменить поверхность контура. \en Replace the surface of contour. 
  virtual bool        ChangeSurface( MbSurface & );
  /// \ru Заменить двумерный контур. \en Replace the two-dimensional contour. 
          void        ChangeContour( MbContour & );
  virtual bool        IsPlanar() const; // \ru Определить, является ли кривая плоской. \en Determine whether the curve is planar. 
  virtual bool        IsSmoothConnected( double angleEps ) const; // \ru Определить, является ли контур гладким. \en Define whether the contour is smooth. 
  // \ru Дать плоскую кривую и плейсмент, если пространственная кривая плоская (после использования вызывать DeleteItem на двумерную кривую). \en Get planar curve and placement if the space curve is planar (after the using call DeleteItem for two-dimensional curves) 
  virtual bool        GetPlaneCurve( MbCurve *& curve2d, MbPlacement3D & place3d, bool saveParams, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Дать поверхностную кривую, если пространственная кривая поверхностная (после использования вызывать DeleteItem на аргументы). \en Get surface curve if the space curve is surface (after the using call DeleteItem for arguments) 
  virtual bool        GetSurfaceCurve( MbCurve *& curve2d, MbSurface *& surface, VERSION version = Math::DefaultMathVersion() ) const;
  // \ru Заполнить плейсмент, если кривая плоская. \en Fill the placement if curve is planar. 
  virtual bool        GetPlacement( MbPlacement3D & place, VERSION version = Math::DefaultMathVersion() ) const;

  virtual bool        NearPointProjection( const MbCartPoint3D &, double & t, bool ext, MbRect1D * tRange = NULL ) const; // \ru Вычислить ближайшую проекцию точки на кривую. \en Calculate the nearest projection of the point on the curve. 

  virtual bool        IsStraight() const; // \ru Определить, является ли линия прямолинейной. \en Determine whether the line is straight. 

  virtual MbCurve *   GetMap( const MbMatrix3D &, MbRect1D * pRgn = NULL, 
                              VERSION version = Math::DefaultMathVersion(), bool * coincParams = NULL ) const; // \ru Дать плоскую проекцию кривой. \en Get a planar projection of curve. 
  /// \ru Найти все особые точки функции кривизны кривой. 
  /// \en Find all the special points of the curvature function of the curve.
  virtual void        GetCurvatureSpecialPoints( std::vector<c3d::DoublePair> & points ) const;
  virtual bool        IsContinuousDerivative( bool & contLength, bool & contDirect, c3d::DoubleVector * params = NULL, double epsilon = EPSILON ) const; // \ru Непрерывна ли первая производная? \en Have the first derivative the continuous?
  virtual bool        SetContinuousDerivativeLength( double epsilon = EPSILON ); // \ru Устранить разрывы первых производных по длине. \en Eliminate the discontinuities of the first derivative at length.

  // \ru Доступ к полям класса. \en Access to the fields of a class. 

  /// \ru Выдать базовую поверхность. \en Get the base surface. 
  const   MbSurface & GetSurface() const { return *surface; }
  /// \ru Выдать двумерный контур. \en Get the two-dimensional contour. 
  const   MbContour & GetContour() const { return *contour; }
  /// \ru Получить сегмент двумерного контура. \en Get the segment of the two-dimensional contour. 
  const   MbCurve *   GetSegment( size_t index ) const;
  /// \ru Выдать базовую поверхность для редактирования. \en Get the base surface for editing. 
          MbSurface & SetSurface() { return *surface; }
  /// \ru Выдать двумерный контур для редактирования. \en Get the two-dimensional contour for editing. 
          MbContour & SetContour() { return *contour; }
  /// \ru Получить сегмент двумерного контура для редактирования. \en Get the segment of the two-dimensional contour for editing. 
          MbCurve *   SetSegment( size_t index );

  /// \ru Выдать количество сегментов контура. \en Get the number of contour segments 
          size_t      GetSegmentsCount() const;
  /// \ru Выдать копию двумерного контура. \en Get a copy of the two-dimensional contour. 
          MbContour & ContourDuplicate() const;

  /// \ru Вычислить нормали к поверхности по параметру кривой. \en Calculate normals to the surface in the curve parameter. 
          void        SurfaceNormal( double t, MbVector3D & n ) const;
  /// \ru Найти сегмент контура по параметру на контуре. \en Find a segment of contour in the contour parameter. 
          ptrdiff_t   FindSegment  ( double & t, double & tSeg ) const;
  /// \ru Найти точку сегмента контура по индексу. \en Find a point of the contour segment by the index. 
          void        FindCorner   ( ptrdiff_t index, MbCartPoint & )   const;
  /// \ru Найти точку сегмента контура по индексу. \en Find a point of the contour segment by the index. 
          void        FindCorner   ( ptrdiff_t index, MbCartPoint3D & ) const;
  /// \ru Добавить сегмент в контур. \en Add a segment to the contour. 
          void        AddSegment( MbCurve & newSegment );
  /// \ru Добавить сегмент в контур. \en Add a segment to the contour. 
          void        AddSegment( MbCurve & pBasis, double t1, double t2, int sense );
  /// \ru Добавить сегмент в контур. \en Add a segment to the contour. 
          void        AddSegment( MbSurfaceCurve & newSegment );
  /// \ru Добавить сегмент в контур. \en Add a segment to the contour. 
          void        AddSegment( MbSurfaceCurve & pBasis, double t1, double t2, int sense );
  /// \ru Получить параметры поверхности по параметру на контуре. \en Get surface parameters by the parameter on the contour. 
          void        GetSurfacePar( double & t, double & u, double & v ) const;
  /// \ru Вычислить U-пары от V. \en Calculate U-pairs from V. 
          void        GetUPairs    ( double v, SArray<double> & u ) const;
  /// \ru Вычислить V-пары от U. \en Calculate V-pairs from U. 
          void        GetVPairs    ( double u, SArray<double> & v ) const;

  /// \ru Вычислить площадь и ориентация контура относительно поверхности. \en Calculate the area and the contour orientation relative to the surface. 
          double      Area() const;
  /// \ru Ориентировать контур против часовой стрелки. \en Orient the contour counterclockwise. 
          bool        NormalizeOrientation();

  /// \ru Классифицировать положение точки относительно контура. \en Classify the position of the point relative to the contour. 
          MbeItemLocation PointClassification  ( const MbCartPoint & ) const;
  /// \ru Вычислить параметрическое расстояние до ближайшей границы. \en Calculate the parametric distance to the nearest boundary. 
          double          DistanceToBorder( const MbCartPoint & pnt, double & eps ) const;
  /// \ru Определить, находится ли контур cntr в области контура (известно, что контуры не пересекаются). \en Determine whether the contour "cntr" is inside the region of the contour (contours do not intersect). 
          MbeItemLocation ContourClassification( const MbContourOnSurface & cntr, double precision = Math::metricPrecision ) const; 

  /** \brief \ru Определить точки пересечения с двумерной кривой.
             \en Determine points of intersection with two-dimensional uv-curve. \~
    \details \ru Определить точки пересечения плоской кривой и контура. \n
             \en Determine intersection points of a planar curve and the contour. \n \~
    \param[in] pCurve - \ru Кривая.
                        \en A curve. \~
    \param[out] tcontour - \ru Массив параметров на контуре.
                           \en An array of parameters on the contour. \~
    \param[out] tcurv - \ru Массив параметров на кривой.
                        \en An array of parameters on the curve. \~
    \return \ru Количество точек пересечения.
            \en The number of points. \~
  */
          size_t      SegmentIntersection( const MbCurve & pCurve, SArray<double> & tcontour, SArray<double> & tcurv, double epsilon = Math::metricEpsilon ) const;
  /** \brief \ru Определить точки пересечения с поверхностной кривой.
             \en Determine points of intersection with a spatial curve. \~
    \details \ru Определить точки пересечения кривой на поверхности и контура. \n
             \en Determine intersection points of curve on the surface and contour. \n \~
    \param[in] curv - \ru Кривая.
                      \en A curve. \~
    \param[out] tcontour - \ru Массив параметров на контуре.
                           \en An array of parameters on the contour. \~
    \param[out] tcurv - \ru Массив параметров на кривой.
                        \en An array of parameters on the curve. \~
    \return \ru Количество точек пересечения.
            \en The number of points. \~
  */
          size_t      SurfaceCurveIntersection( const MbSurfaceCurve & curv, SArray<double> & tcontour, SArray<double> & tcurv, double epsilon = Math::metricEpsilon ) const;
  /** \brief \ru Определить точки пересечения с контуром на поверхности.
             \en Determine intersection points with the contour on the surface. \~
    \details \ru Определить точки пересечения кривой с контуром на поверхности. \n
             \en Determine intersection points of a curve with the contour on the surface. \n \~
    \param[in] cntr - \ru Кривая.
                      \en A curve. \~
    \param[out] tcontour - \ru Массив параметров на контуре.
                           \en An array of parameters on the contour. \~
    \param[out] tcntr - \ru Массив параметров на кривой.
                        \en An array of parameters on the curve. \~
    \return \ru Количество точек пересечения.
            \en The number of points. \~
  */
          size_t      ContourOnSurfaceIntersection( const MbContourOnSurface & cntr, SArray<double> & tcontour, SArray<double> & tcntr, double epsilon = Math::metricEpsilon ) const;

  /// \ru Сделать равным контур. \en Make the contour equal. 
          bool        SetCurveEqual( const MbSpaceItem & );
  /// \ru Определить, являются ли объекты подобными. \en Determine whether the objects are similar. 
          bool        IsCurveEqual ( const MbSpaceItem & ) const;

  /** \brief \ru Создать и инициализировать дерево габаритных кубов сегментов контура.
             \en Create and initialize the segments bounding box tree. \~
    \details \ru Создать и инициализировать дерево габаритов сегментов контура по требованию. 
                 Инициирует поиск ближайших к точке сегментов по дереву габаритов для пространственного контура,
                 что целесообразно при выполнении многократного поиска сегментов.  \n
             \en Create and initialize the segments bounding box tree by request.
                 Initiate nearest segment to given point search by bounding boxes tree in case 3D contour,
                 that is appropriate for multiple segment search.\n \~
    \param[in] indSegmMin - \ru Минимальный индекс сегмента в наборе для построения дерева габаритов.
                            \en Minimum segment index in set for bounding box tree creation. \~
    \param[in] indSegmMax - \ru Максимальный индекс сегмента в наборе для построения дерева габаритов.
                            \en Maximum segment index in set for bounding box tree creation. \~
    \return \ru Результат создания и инициализации дерева.
            \en The result of bounding boxes tree creation. \~
  */
          bool        CreateCubeTree( const size_t & indSegmMin, const size_t & indSegmMax ) const;

protected:
  /// \ru Посчитать параметрический габарит, сбросить временные данные, проверить замкнутость контура. \en Calculate parametric bounding box, reset temporary data, check for contour closedness. 
          void        CalculateIncludePoints();

          void        DeleteCubeTree() const; // \ru Удаление дерева габаритных кубов. \en Delete bounding boxes tree.
          void        DeleteSearchTree() const; // \ru Удалить деревья габаритных кубов и прямоугольников. \en Delete bounding boxes and bounding rectangles trees. 

private:
          void        operator = ( const MbContourOnSurface & ); // \ru Не реализовано !!! \en Not implemented !!! 
          bool        CreateRectTree() const; // \ru Создать и инициализировать дерево габаритных прямоугольников сегментов контура. \en Create and initialize the segments bounding rectangles tree. 
          bool        FindNearestSegmentsByTree( const MbCartPoint & point, std::vector<size_t> & indFound ) const; /// \ru Поиск ближайших к точке сегментов с помощью дерева габаритов на плоскости. \en Nearest to point segment search with bounding box tree in 2D space. 
          bool        FindNearestSegmentsByTree3D( const MbCartPoint3D & point, const size_t & indStart, const size_t & indEnd, std::vector<size_t> & indFound ) const; /// \ru Поиск ближайших к точке сегментов с помощью дерева габаритов в пространстве. \en Nearest to point segment search with bounding box tree in 3D space. 

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbContourOnSurface )
};

IMPL_PERSISTENT_OPS( MbContourOnSurface )


#endif // __CUR_CONTOUR_ON_SURFACE_H
