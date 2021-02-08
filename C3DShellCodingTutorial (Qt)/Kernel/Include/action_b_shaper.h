////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Методы преобразования полигональных геометрических объектов в объекты BRep.
         \en Functions for conversion of the polygonal geometric object to BRep objects. \~
  \details \ru Методы преобразования полигональных геометрических объектов в объекты BRep.
           \en Functions for conversion of the polygonal geometric object to BRep objects. \~ 

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_B_SHAPER_H
#define __ACTION_B_SHAPER_H


#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mesh.h>
#include <mb_enum.h>
#include <mb_operation_result.h>
#include <m2b_mesh_curvature.h>
#include <vector>


class  MATH_CLASS  MbPlacement3D;
class  MATH_CLASS  MbMesh;
class  MATH_CLASS  MbCurve3D;
class  MATH_CLASS  MbSurface;
class  MATH_CLASS  MbSNameMaker;
class  MATH_CLASS  MbFace;
class  MATH_CLASS  MbCollection;


//------------------------------------------------------------------------------
/** \brief \ru Режим распознавания поверхностей.
           \en Surface reconstruction mode. \~
  \details \ru Режим распознавания поверхностей.
           \en Surface reconstruction mode. \~
  \ingroup Polygonal_Objects
*/
// ---
enum MbeSurfReconstructMode
{
  srm_All          = 0,           ///< \ru Строить все поверхности. \en Build all surfaces.
  srm_NoGrids      = 1,           ///< \ru Не строить поверхности на базе триангуляции. \en Not build surfaces based on triangulation.
  srm_CanonicOnly  = 2,           ///< \ru Строить только элементарные поверхности. \en Build elementary surfaces only.
  srm_Default      = srm_NoGrids  ///< \ru Режим по умолчанию. \en Default mode.
};


//------------------------------------------------------------------------------
/** \brief \ru Параметры построения оболочки тела по полигональной сетке.
           \en Parameters of BRep shell construction from polygonal mesh. \~
  \ingroup Polygonal_Objects
*/
// ---
class MATH_CLASS MbMeshProcessorValues {
public:

  /** \brief \ru Использовать относительную точность (true).
             \en Use relative tolerance (true). \~
    \details \ru При использовании относительной точности отклонение граней тела от сетки проверяется относительно размера модели.
             \en While use of relative tolerance distance from shell to mesh is checked relative to model size. \~
  */
  bool useRelativeTolerance;

  /** \brief \ru Точность.
             \en Tolerance. \~
    \details \ru Точность работы метода: допустимое отклонение граней тела от вершин сетки.
             \en Tolerance: maximum distance from BRep faces to mesh vertices. \~
  */
  double tolerance;

  /** \brief \ru Режим распознавания поверхностей.
             \en Surface reconstruction mode. \~
  */
  MbeSurfReconstructMode surfReconstructMode;

  /// \ru Конструктор по умолчанию. \en Default constructor.
  explicit MbMeshProcessorValues( bool useRelTol = true, double tol = 0.01, MbeSurfReconstructMode mode = srm_Default )
    : useRelativeTolerance( useRelTol )
    , tolerance           ( tol       )
    , surfReconstructMode ( mode      )
  {}
};


//------------------------------------------------------------------------------
/** \brief \ru Класс для создания оболочки в граничном представлении по полигональной сетке.
           \en Class for creating a BRep shell by polygonal mesh. \~
  \details \ru Предоставить интерфейс для управления преобразованием сетки в
               оболочку в граничном представлении. \n
           \en Provide an interface for managing of "Mesh to BRep" conversion. \n \~
  \ingroup Polygonal_Objects
*/
// ---
class MATH_CLASS MbMeshProcessor : public MbRefItem
{
protected:
  /// \ru Конструктор. \en Constructor. 
  MbMeshProcessor();

public:
  /** \brief \ru Создать экземпляр процессора по коллекции.
             \en Create mesh processor by collection. \~
    \details \ru Создать экземпляр процессора по коллекции. Пользователь должен сам удалить объект.
             \en Create mesh processor by collection. User must delete created object. \~
    \param[in] collection - \ru Входная коллекция, содержащая треугольную сетку. \n
                            \en Input collection containing triangle mesh. \~
    \return \ru Возвращает указатель на созданный объект.
            \en Returns pointer to created object. \~
    \ingroup Polygonal_Objects
  */
  static MbMeshProcessor * Create( const MbCollection & collection );

  /// \ru Деструктор. \en Destructor. 
  virtual ~MbMeshProcessor();

  /** \brief \ru Установить относительную точность.
             \en Set relative tolerance. \~
    \details \ru Установить относительную точность по габаритам текущей сетки.
             \en Set relative tolerance by current mesh box. \~
    \param[in] tolerance - \ru Относительная точность. \n
                           \en Relative tolerance to set. \~
    \ingroup Polygonal_Objects
  */
  virtual void SetRelativeTolerance( double tolerance ) = 0;

  /** \brief \ru Установить точность.
             \en Set tolerance. \~
    \details \ru Установить точность распознавания поверхностей и расширения сегментов сетки.
                 Метод должен быть вызван перед вызовом SegmentMesh.
                 Точность по умолчанию равна 0.1.
             \en Set tolerance of surface reconstruction and segments extension.
                 Method should be called before call to SegmentMesh.
                 Default tolerance is 0.1. \n \~
    \param[in] tolerance - \ru Точность. \n
                           \en Tolerance to set. \~
    \ingroup Polygonal_Objects
  */
  virtual void SetTolerance( double tolerance ) = 0;

  /** \brief \ru Получить точность.
             \en Get tolerance. \~
    \details \ru Получить текущую точность, используемую при распознавании поверхностей и расширения сегментов сетки.
             \en Get current tolerance used in surface reconstruction and segments extension. \~
    \return \ru Возвращает абсолютную точность.
            \en Returns absolute tolerance. \~
    \ingroup Polygonal_Objects
  */
  virtual double GetTolerance() const = 0;

  //------------------------------------------------------------------------------
  /** \brief \ru Установить режим распознавания поверхностей.
             \en Set the surfaces reconstruction mode. \~
    \details \ru Задать типы поверхностей, генерируемых на сегментах. Поверхности неподдерживаемых типов строиться не будут. \n
             \en Set types of surfaces which will be generated on segments. The surfaces of unsupoprted type will not be built. \n \~
    \param[in]  mode  - \ru Режим распознавания поверхностей.
                        \en Surface reconstruction mode.
    \ingroup Polygonal_Objects
  */
  virtual void SetReconstructionMode( MbeSurfReconstructMode mode ) = 0;

  //------------------------------------------------------------------------------
  /** \brief \ru Установить флаг сглаживания входной сетки.
             \en Set flag to use smoothing of input mesh. \~
    \details \ru Установить флаг сглаживания входной сетки. Если флаг установлен в true,
                 то перед запуском основного алгоритма сегментации будет выполнено сглаживание входной сетки.
                 Рекомендуется использовать сглаживание на неточных сетках, например, полученных методом сканирования. \n
             \en Set flag to use smoothing of input mesh. If the flag set to true, then run smoothing of input mesh
                 before main segmentation algorithm start.
                 It is recommended to use mesh smoothing on inexact meshes, e.g. meshes obtained by scanning. \n \~
    \param[in]  useSmoothing  - \ru Флаг использования сглаживания входной сетки. По-умолчанию false.
                                \en The flag to use smoothing of input mesh. Default false.
    \ingroup Polygonal_Objects
  */
  // ---
  virtual void SetUseMeshSmoothing( bool useSmoothing ) = 0;

  /** \brief \ru Получить исправленную (упрощенную) копию входной полигональной сетки.
             \en Get fixed (simplified) copy of the input mesh. \~
    \details \ru Получить исправленную копию входной сетки, на которой выполняются операции MbMeshProcessor:
                 подсчет кривизн, сегментация, построение оболочки. Все индексы в выходных данных соответствуют
                 индексам вершин и треугольников упрощенной сетки, возвращаемой данным методом. \n
             \en Get fixed copy of the input mesh. All further operations of MbMehsProcessor are
                 performed for simplified mesh: curvature calculation, segmentation, shell creation.
                 All indices in the output of these operations corresponds to indices of vertices and
                 triangles of the simplified mesh returned from this function. \n \~
    \return \ru Возвращает исправленную версию входной полигональной сетки.
            \en Returns a fixed version of the input mesh. \~
    \ingroup Polygonal_Objects
  */
  virtual const MbCollection & GetSimplifiedMesh() = 0;

  /** \brief \ru Получить сегментированную копию входной полигональной сетки.
             \en Get segmented copy of the input mesh. \~
    \details \ru Получить сегменитрованную копию входной сетки, на которой выполняются операции MbMeshProcessor:
                 подсчет кривизн, сегментация, построение оболочки.
                 Сегментация доступна внутри коллекции. \n
             \en Get segmented copy of the input mesh. All further operations of MbMehsProcessor are
                 performed for simplified mesh: curvature calculation, segmentation, shell creation.
                 Segmentation is stored inside collection. \n \~
    \return \ru Возвращает сегментированную версию входной полигональной сетки.
              \en Returns a segmented version of the input mesh. \~
    \ingroup Polygonal_Objects
  */
  virtual const MbCollection & GetSegmentedMesh() = 0;

  /** \brief \ru Рассчитать главные кривизны и главные направления изменения кривизн в точках сетки.
             \en Calculate the principal curvatures and principal curvature directions at mesh points. \~
    \details \ru Рассчитать главные кривизны и главные направления изменения кривизн в точках сетки. \n
             \en Calculate the principal curvatures and principal curvature directions at mesh points. \n \~
    \return \ru Возвращает главные кривизны и главные направления в точках сетки.
            \en Returns principal curvatures and principal curvature directions at mesh points. \~
    \ingroup Polygonal_Objects
  */
  virtual const std::vector<MbCurvature> & CalculateCurvatures() = 0;

  /** \brief \ru Сегментровать полигональную сетку.
             \en Segment a polygonal mesh. \~
    \details \ru Выполнить сегментацию полигональной сетки. \n
             \en Perform segmentation of a polygonal mesh. \n \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \param[in] createSurfaces - \ru Создавать ли поверхности на сегментах.
                                \en Create surfaces on segments or not. \~
    \ingroup Polygonal_Objects
  */
  virtual MbResultType SegmentMesh( bool createSurfaces = true ) = 0;

  /** \brief \ru Создать оболочку.
             \en Create shell. \~
    \details \ru Создать оболочку в граничном представлении, соответствующее модели, заданной полигональной сеткой.
                 Используется текущая сегментация.
                 Если сегментация не была вычислена, но вычисляется автоматическая сегментация (с параметрами по умолчанию). \n
             \en Create BRep shell that represents input mesh model.
                 Current segmentation is used.
                 If segmentation is not computed yet, then automatic segmentation is performed (with default paramters). \n \~
    \param[out] pShell - \ru Указатель на созданную оболочку.
                          \en The pointer to created shell. \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \ingroup Polygonal_Objects
  */
  virtual MbResultType CreateBRepShell( MbFaceShell *& pShell ) = 0;

  /** \brief \ru Вписать поверхность.
             \en Fit surface to segment . \~
    \details \ru Распознать поверхность по сегменту сетки с заданным индексом.
                 Распознанная поверхность может быть получена с помощью метода GetSegmentSurface. \n
             \en Recognize surface for mesh segment with a given index.
                 Recognized surface is available through GetSegmentSurface method. \n \~
    \param[in] idxSegment - \ru Индекс сегмента полигональной сетки.
                            \en Index of a mesh segment. \~
    \ingroup Polygonal_Objects
  */
  virtual void FitSurfaceToSegment( size_t idxSegment ) = 0;

  /** \brief \ru Вписать поверхность заданного типа.
             \en Fit surface of a given type to a segment. \~
    \details \ru Построить поверхность заданного типа, аппроксимирующиую сегмент сетки с заданным индексом.
                 Распознанная поверхность может быть получена с помощью метода GetSegmentSurface. \n
             \en Find surface of a given type approximating mesh segment with a given index.
                 Recognized surface is available through GetSegmentSurface method. \n \~
    \param[in] idxSegment  - \ru Индекс сегмента полигональной сетки.
                             \en Index of a mesh segment. \~
    \param[in] surfaceType - \ru Тип вписываемой поверхности.
                             \en Type of fitted surface. \~
    \ingroup Polygonal_Objects
  */
  virtual void FitSurfaceToSegment( size_t idxSegment, MbeSpaceType surfaceType ) = 0;

  /** \brief \ru Получить поверхность для сегмента.
             \en Get surface of segment. \~
    \details \ru Получить поверхность, вписанную в сегмент.
                 Чтобы поверхность была определена предварительно должны быть вызваны методы
                 SegmentMesh или FitSurfaceToSegment.
                 Распознанная поверхность с помощью метода GetSegmentSurface. \n
             \en Get surface that approximates segment.
                 To fit surface use corresponding methods SegmentMesh or FitSurfaceToSegment. \n \~
    \param[in] idxSegment - \ru Индекс сегмента полигональной сетки.
                            \en Index of a mesh segment. \~
    \return  \ru Возвращает указатель на поверхность для сегмента, если поверхность определена, иначе - NULL.
             \en Returns pointer to segment surface if it exists, else - NULL. \~
    \ingroup Polygonal_Objects
  */
  virtual const MbSurface * GetSegmentSurface( size_t idxSegment ) const = 0;

  /** \brief \ru Очистить сегментацию полигональной сетки.
             \en Reset segmentation of the polygonal mesh. \~
    \details \ru Очистить сегментацию полигональной сетки, хранящуюся внутри MbMeshProcessor. \n
             \en Reset segmentation of the polygonal mesh stored inside MbMeshProcessor. \n \~
    \ingroup Polygonal_Objects
  */
  virtual void ResetSegmentation() = 0;

  /** \brief \ru Найти ближайший путь между двумя вершинами коллекции.
             \en Find shortest path between two vertices. \~
    \details \ru Найти ближайший путь, проходящий по вершинам и ребрам коллекции, соединяющий две заданные вершины. \n
             \en Find shortest path between two vertices. The path should pass through collection vertices and edges. \n \~
    \param[in]  v1   - \ru Индекс первой вершины.
                       \en The index of first vertex. \~
    \param[in]  v2   - \ru Индекс второй вершины.
                       \en The index of second vertex. \~
    \param[out] path - \ru Путь из первой вершины во вторую.
                           Массив содержит последовательные индексы всех вершин пути.
                       \en The path from the first vertex to the second one.
                           The array contains successive indices of path vertices. \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \ingroup Polygonal_Objects
  */
  virtual bool FindShortestVertexPath( uint v1, uint v2, std::vector<uint> & path ) = 0;

private: // UNDER DEVELOPMENT
  /** \} */
  /** \ru \name Функции для работы с разбиением сетки на сегменты и распознаванием поверхностей для сегментов.
      \en \name Functions for editting of mesh segmentation and reconstruction of surfaces for the segments.
      \{ */

  /** \brief \ru Объединить два сегмента в текущей сегментации.
             \en Unite two segments in current segmentation. \~
    \details \ru Объединение сегментов в текущей сегментации.
                 Результат объединения доступен через коллекцию, возвращаемую методом GetSegmentedMesh. \n
             \en Union of segments in current mesh segmentation.
                 Result segmentation is available through collection returned by GetSegmentedMesh. \n \~
    \param[in] firstSegmentIdx - \ru Индекс первого сегмента для объединения. \n
                                 \en Index of the first segment for union. \~
    \param[in] secondSegmentIdx - \ru Индекс второго сегмента для объединения. \n
                                  \en Index of the second segment for union. \~
    \ingroup Polygonal_Objects
  */
  virtual void UniteSegments( size_t firstSegmentIdx, size_t secondSegmentIdx ) = 0;

  /** \brief \ru Сегментровать полигональную сетку по разделителям сегментов.
             \en Segment a polygonal mesh by segment separators. \~
    \details \ru Выполнить сегментацию полигональной сетки по заданным разделителям сегментов. \n
             \en Perform segmentation of a polygonal mesh by segment separators. \n \~
    \param[in]  separators  - \ru Массив разделителей.
                                  Каждый разделитель содержит путь по вершинам сетки, ребра которого разделяют сегменты.
                              \en The array of segment separators.
                                  Each separator contains a path by mesh vertices. Edges of that path split mesh to segments. \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \ingroup Polygonal_Objects
  */
  virtual MbResultType SegmentMeshBySeparators( const std::vector<std::vector<uint>> & separators ) = 0;

  OBVIOUS_PRIVATE_COPY( MbMeshProcessor )
};


//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку по полигональной сетке c автоматическим распознаванием поверхностей.
           \en Create shell from mesh with automatic surface reconstruction. \~
    \details \ru Создать оболочку в граничном представлении, соответствующее модели, заданной полигональной сеткой.
                 Алгоритм в автоматическом режиме распознает и реконструирует грани, соответствующие элементарным
                 поверхностям (плоскость, цилиндр, сфера, конус, тор). \n
             \en Create BRep shell that represents input mesh model.
                 Algorithm automatically detect and reconstruct faces based on elementary surfaces (plane, cylinder, sphere, cone, torus). \n \~
    \param[in]  mesh      - \ru Входная сетка.
                            \en The input mesh. \~
    \param[out] shell     - \ru Указатель на созданную оболочку.
                            \en The pointer to created shell. \~
    \param[in]  params    - \ru Параметры построения оболочки тела.
                            \en Parameters of BRep shell construction. \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC( MbResultType ) ConvertMeshToShell( MbMesh & mesh, MbFaceShell *& shell, const MbMeshProcessorValues & params = MbMeshProcessorValues() );


//------------------------------------------------------------------------------
/** \brief \ru Создать оболочку по коллекции, содержащей полигональную сетку c автоматическим распознаванием поверхностей.
           \en Create shell from collection with automatic surface reconstruction. \~
    \details \ru Создать оболочку в граничном представлении, соответствующую модели, заданной полигональной сеткой.
                 Алгоритм в автоматическом режиме распознает и реконструирует грани, соответствующие элементарным
                 поверхностям (плоскость, цилиндр, сфера, конус, тор). \n
             \en Create BRep shell that represents input mesh model from collection.
                 Algorithm automatically detect and reconstruct faces based on elementary surfaces (plane, cylinder, sphere, cone, torus). \n \~
    \param[in]  collection  - \ru Коллекция, содержащая входную сетку.
                              \en The input collection. \~
    \param[out] shell       - \ru Указатель на созданную оболочку.
                              \en The pointer to created shell. \~
    \param[in]  params      - \ru Параметры построения оболочки тела.
                              \en Parameters of BRep shell construction. \~
    \return  \ru Возвращает код результата операции.
             \en Returns operation result code. \~
    \ingroup Polygonal_Objects
*/
// ---
MATH_FUNC( MbResultType ) ConvertCollectionToShell( MbCollection & collection, MbFaceShell *& shell, const MbMeshProcessorValues & params = MbMeshProcessorValues() );

#endif // __ACTION_B_SHAPER_H
