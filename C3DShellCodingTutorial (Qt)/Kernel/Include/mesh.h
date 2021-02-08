////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Полигональный геометрический объект (фасетный объект).
         \en The polygonal geometric object - Mesh. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MESH_H
#define __MESH_H


#include <mesh_grid.h>
#include <mesh_polygon.h>
#include <model_item.h>


class MATH_CLASS MbMesh;
namespace c3d // namespace C3D
{
typedef SPtr<MbMesh>                          MeshSPtr;
typedef SPtr<const MbMesh>                    ConstMeshSPtr;

typedef std::vector<MbMesh *>                 MeshesVector;
typedef std::vector<const MbMesh *>           ConstMeshesVector;

typedef std::vector<MeshSPtr>                 MeshesSPtrVector;
typedef std::vector<ConstMeshSPtr>            ConstMeshesSPtrVector;
} // namespace C3D


//------------------------------------------------------------------------------
/** \brief \ru Полигональный объект модели - фасетный объект.
           \en The polygonal geometric object - Mesh. \~
  \details \ru Фасетный объект - это объект геометрической модели, наследник MbItem, являющийся
  множеством примитивов #MbPrimitive, аппроксимирующих некоторый 
  геометрический объект для ускорения визуализации, вычисления инерционных 
  характеристик, определения столкновений и других расчетов.\n

    Например, сетку можно построить на основе множества точек, полученных замерами 
  реального физического тела. Полигональный объект содержит множество точек, являющимися
  узлами (вершинами) в таких структурах данных:
    множество указателей на триангуляции MbGrid (наборы стыкующихса треугольных и четырёхугольных пластин),
    множество указателей на полигоны MbPolygon3D (наборы точек, описывающих ломаные линии), 
    множество указателей на апексы MbApex3D (точки, описывающие положение вершин или объектов-точек).\n

           \en Mesh is an object of geometric model (subclass MbItem) which is
  the set of primitives #MbPrimitive which approximate some 
  geometric object for speed up rendering, calculation of inertial 
  characteristics, collision detection and other calculations.\n

    For example, the mesh can be create on the basis of a point set obtained measurements 
  of the real physical solid. Polygonal object contains a set of points which are
  nodes (vertices) in the data structures:
    a set of pointers to triangulations MbGrid (sets of mating triangular and quadrangular plates),
    a set of pointers to polygons MbPolygon3D (sets of points which describe the polylines), 
    a set of pointers to apexes MbApex3D (points wich describe the position of vertices or objects-points). \n \~ 

  \par \ru Применение
    Полигональный объект используется для представления геометрических объектов в упрощенном виде, \n
    для визуализации геометрических объектов, \n 
    для расчетов столкновений геометрических объектов, \n 
    для вычисления масс-инерционных характеристик. \n 
    Если фасетный объект аппроксимирует тело #MbSolid, то фасетный объект, как тело, может быть
    замкнутым или незамкнутым.\n
    Граничные точки разных триангуляций для замкнутого объекта совпадают, но имеют в них разные нормали. 

       \en Usage
    The mesh is used to represent geometric objects in a polygonal form, \n
    for visualization of geometric objects, \n 
    for calculations of geometry objects collisions, \n 
    for calculation of the mass-inertial properties. \n 
    If the mesh approximates the solid #MbSolid then polygonal object as a solid can be
    closed or unclosed. \n \~ 
  \ingroup Model_Items
*/ 
// ---
class MATH_CLASS MbMesh : public MbItem 
{
private:
  RPArray<MbGrid>      grids;  ///< \ru Множество указателей на триангуляции. \en A set of pointers to triangulations. 
  RPArray<MbPolygon3D> wires;  ///< \ru Множество указателей на полигоны. \en A set of pointers to polygons. 
  RPArray<MbApex3D>    peaks;  ///< \ru Множество указателей на апексы. \en A set of pointers to apexes. 
  const MbRefItem *    item;   ///< \ru Источник сетки. \en Source of mesh. 
  MbeSpaceType         type;   ///< \ru Тип сетки отражает характер, но не связан напрямую с item. \en A mesh type describes the character but it is not related to "item". 
  bool                 closed; ///< \ru Замкнутость указывает на отсутствие края в триангуляции. \en Closedness indicates the absence of edge in the triangulation. 
  bool                 exact;  ///< \ru Объекты построены на числах double. \en Objects builded on double data. 

  /** \brief \ru Габаритный куб объекта. 
             \en Bounding box of object. \~
      \details \ru Габаритный куб объекта расчитывается только при запросе габарита объекта. Габаритный куб в конструкторе объекта и после модификации объекта принимает неопределенное значение.
               \en Bounding box of object is calculated only at the request. Bounding box of object is undefined after object constructor and after object modifications \n \~
  */
  mutable MbCube       cube; 

private:
  // \ru Объявление конструктора копирования без реализации, чтобы не было копирования по умолчанию. \en The copy constructor without implementation prevents from copying by default. 
  MbMesh( const MbMesh & );
  /// \ru Конструктор копирования с регистратором. \en Copy constructor with registrator. 
  explicit MbMesh( const MbMesh & other, MbRegDuplicate * iReg );

public:
  /// \ru Конструктор без параметров. \en Constructor without parameters. 
  MbMesh( bool _exact = false );
  /// \ru Деструктор \en Destructor 
  virtual ~MbMesh();

public: 
  VISITING_CLASS( MbMesh ); 
  
  // \ru Общие функции геометрического объекта. \en Common functions of a geometric object. 

  virtual MbeSpaceType  IsA()  const; // \ru Тип объекта. \en Type of the object. 
  virtual MbSpaceItem & Duplicate( MbRegDuplicate * = NULL ) const; // \ru Создать копию. \en Create a copy. 
  virtual void    Transform( const MbMatrix3D &, MbRegTransform * = NULL ); // \ru Преобразовать согласно матрице. \en Transform according to the matrix. 
  virtual void    Move     ( const MbVector3D &, MbRegTransform * = NULL ); // \ru Сдвинуть вдоль вектора. \en Translate along a vector. 
  virtual void    Rotate   ( const MbAxis3D   &, double angle, MbRegTransform * = NULL ); // \ru Повернуть вокруг оси. \en Rotate around an axis. 
  virtual bool    IsSame   ( const MbSpaceItem & other, double accuracy = LENGTH_EPSILON ) const; // \ru Являются ли объекты равными? \en Determine whether objects are equal. 
  virtual bool    SetEqual ( const MbSpaceItem & init );   // \ru Сделать объекты равным. \en Make equal objects. 
  virtual double  DistanceToPoint ( const MbCartPoint3D & ) const; // \ru Вычислить расстояние до точки. \en Calculate the distance to a point. 
  virtual void    AddYourGabaritTo( MbCube & r ) const; // \ru Добавь свой габарит в куб. \en Add bounding box into a cube. 
  virtual void    CalculateLocalGabarit( const MbMatrix3D & into, MbCube & cube ) const; // \ru Рассчитать габарит в локальной системы координат. \en Calculate bounding box in the local coordinate system. 
  virtual void    CalculateMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; // \ru Построить полигональную копию mesh. \en Build polygonal copy mesh.

  virtual MbProperty & CreateProperty( MbePrompt n ) const;     // \ru Создать собственное свойство. \en Create own property. 
  virtual void    GetProperties( MbProperties & properties ); // \ru Выдать свойства объекта. \en Get properties of the object. 
  virtual void    SetProperties( const MbProperties & properties ); // \ru Установить свойства объекта. \en Set properties of object. 
  virtual void    GetBasisPoints( MbControlData3D & ) const; // \ru Выдать контрольные точки объекта. \en Get control points of object.
  virtual void    SetBasisPoints( const MbControlData3D & ); // \ru Изменить объект по контрольным точкам. \en Change the object by control points.

  // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a polygonal copy of the given object. 
  virtual MbItem* CreateMesh( const MbStepData & stepData, const MbFormNote & note, MbRegDuplicate * iReg ) const; 
  // \ru Добавить себя в присланный полигональный объект mesh без копирования. \en Add itself to the given polygonal object "mesh" without copying. 
  virtual bool    AddYourMesh( const MbStepData & stepData, const MbFormNote & note, MbMesh & mesh ) const; 
  // \ru Разрезать полигональный объект одной или двумя параллельными плоскостями. \en Cut polygonal form of an object by one or two parallel planes. 
  virtual MbItem* CutMesh( const MbPlacement3D & cutPlace, double distance ) const; 
  // \ru Найти ближайший объект или имя ближайшего объекта. \en Find the nearest object or name of nearest object.
  // \note \ru В многопоточном режиме выполняется параллельно. \en In multithreaded mode runs in parallel. \~
  virtual bool    NearestMesh( MbeSpaceType sType, MbeTopologyType tType, MbePlaneType pType, 
                               const MbAxis3D & axis, double maxDistance, bool gridPriority, double & t, double & dMin, 
                               MbItem *& find, SimpleName & findName,
                               MbRefItem *& element, SimpleName & elementName,
                               MbPath & path, MbMatrix3D & from ) const; 

  /** \ru \name Функции полигонального объекта.
      \en \name Function of polygonal object.
      \{ */
          /// \ru Является ли полигональный объект аппроксимацией точки? \en Whether the polygonal object is approximation of point. 
          bool    IsAPointMesh  () const; 
          /// \ru Является ли полигональный объект аппроксимацией кривой? \en Whether the polygonal object is approximation of curve. 
          bool    IsACurveMesh  () const;
          /// \ru Является ли полигональный объект аппроксимацией поверхности? \en Whether the polygonal object is approximation of surface. 
          bool    IsASurfaceMesh() const;
          /// \ru Является ли полигональный объект аппроксимацией твёрдого тела? \en Whether the polygonal object is approximation of solid. 
          bool    IsASolidMesh  () const;
          /// \ru Содержат ли контейнеры сетки данные? \en Whether containers of mesh contain data. 
          bool    IsComplete() const { return (grids.size() > 0) || (wires.size() > 0) || (peaks.size() > 0); }
          /// \ru Зарезервировать место для пластин. \en Reserve space for the plates. 
          void    GridsReserve(size_t cnt, bool fill = false );
          /// \ru Зарезервировать место для полигонов. \en Reserve space for the polygons. 
          void    PolygonsReserve( size_t cnt ) { wires.Reserve( cnt ); }
          /// \ru Зарезервировать место для апексов. \en Reserve space for the apexes. 
          void    ApexReserve( size_t cnt )     { peaks.Reserve( cnt ); }
          /// \ru Обнулить данные объекта. \en Set object data to null. 
          void    Flush(); 
          /// \ru Освободить лишнюю память. \en Free the unnecessary memory. 
          void    Adjust() { grids.Adjust(); wires.Adjust(); peaks.Adjust(); } 

          /// \ru Выдать количество триангуляций. \en Get the number of triangulations. 
          size_t  GridsCount() const { return grids.size(); } 
          /// \ru Добавить триангуляцию. \en Add triangulation. 
          void    AddGrid( MbGrid & gr ); 
          /// \ru Добавить новую пустую триангуляцию и выдать её для заполнения. \en Add new empty triangulation and give it to fill. 
          MbGrid * AddGrid(); 
          /// \ru Отсоединить триангуляцию с заданным номером. \en Detach triangulation with a given number. 
          MbGrid * DetachGrid( size_t i ); 
          /// \ru Отсоединить все триангуляции. \en Detach all triangulations. 
          template <class GridsVector>
          void    DetachAllGrids( GridsVector & gridsVector ) {
            gridsVector.reserve( gridsVector.size() + grids.size() );
            for( size_t i = 0, iCount = grids.size(); i < iCount; ++i ) {
              MbGrid * gr = grids[i];
              if ( gr != NULL ) {
                gr->DecRef();
                gridsVector.push_back( gr );
              }
              grids.clear();
#ifdef STANDARD_C11
              grids.shrink_to_fit();
#endif
              cube.SetEmpty();
            }
          } 
          /// \ru Вернуть указатель на триангуляцию по её номеру. \en Return pointer to triangulation by it number. 
  const   MbGrid * GetGrid( size_t i ) const { return ( (i < grids.size()) ? grids[i]: NULL ); }
          /// \ru Вернуть указатель на триангуляцию по её номеру для модификации. \en Return the pointer to triangulation by its number to be modified. 
          MbGrid * SetGrid( size_t i )       { return ( (i < grids.size()) ? grids[i]: NULL ); }
          /// \ru Получить указатели на триангуляции. \en Get pointers to triangulations.
          template <class GridsVector>
          void    GetGrids( GridsVector & gridsVector ) const {
            size_t gridsCnt = grids.size();
            gridsVector.reserve( gridsVector.size() + gridsCnt );
            for ( size_t k = 0; k < gridsCnt; ++k ) {
              const MbGrid * grid = grids[k];
              gridsVector.push_back( grid );
            }
          }
          /// \ru Выдать количество полигонов. \en Get the number of polygons. 
          size_t  PolygonsCount() const { return wires.size(); }
          /// \ru Добавить полигон. \en Add polygon. 
          void    AddPolygon( MbPolygon3D & );
          /// \ru Добавить новый пустой полигон и выдать его для заполнения. \en Add new empty polygon and give it to fill. 
          MbPolygon3D * AddPolygon();
          /// \ru Отсоединить полигон с заданным номером. \en Detach polygon with a given number. 
          MbPolygon3D * DetachPolygon( size_t i ); 
          /// \ru Отсоединить все полигоны. \en Detach all polygons. 
          template <class PolygonsVector>
          void    DetachAllPolygons( PolygonsVector & polyVector ) {
            polyVector.reserve( polyVector.size() + wires.size() );
            for( size_t i = 0, iCount = wires.size(); i < iCount; ++i ) {
              MbPolygon3D * pl = wires[i];
              if ( pl != NULL ) {
                pl->DecRef();
                polyVector.push_back( pl );
              }
              wires.clear();
#ifdef STANDARD_C11
              wires.shrink_to_fit();
#endif
              cube.SetEmpty();
            }
          }
          /// \ru Вернуть указатель на полигон по его номеру. \en Return the pointer to polygon by its number. 
  const   MbPolygon3D * GetPolygon( size_t i ) const { return ( (i < wires.size()) ? wires[i]: NULL ); }
          /// \ru Вернуть указатель на полигон по его номеру. \en Return the pointer to polygon by its number. 
          MbPolygon3D * SetPolygon( size_t i )       { return ( (i < wires.size()) ? wires[i]: NULL ); }
          /// \ru Получить указатели на полигоны. \en Get pointers to polygons.
          template <class PolygonsVector>
          void    GetPolygons( PolygonsVector & polyVector ) const {
            size_t polyCnt = wires.size();
            polyVector.reserve( polyVector.size() + polyCnt );
            for ( size_t k = 0; k < polyCnt; ++k ) {
              const MbPolygon3D * poly = wires[k];
              polyVector.push_back( poly );
            }
          }
          /// \ru Выдать количество апексов. \en Get the number of apexes. 
          size_t  ApexesCount() const { return peaks.size(); } 
          /// \ru Добавить новый апекс. \en Add new apex. 
          void    AddApex( MbApex3D & ap ); 
          /// \ru Добавить новый пустой апекс и выдать его для заполнения. \en Add new empty apex and give it to fill. 
          MbApex3D * AddApex();
          /// \ru Отсоединить апекс с заданным номером. \en Detach apex with a given number. 
          MbApex3D * DetachApex( size_t i ); 
          /// \ru Отсоединить все вершины. \en Detach all apexes. 
          template <class ApexesVector>
          void    DetachAllApexes( ApexesVector & peakVector ) {
            peakVector.reserve( peakVector.size() + peaks.size() );
            for( size_t i = 0, iCount = peaks.size(); i < iCount; ++i ) {
              MbApex3D * peak = peaks[i];
              if ( peak != NULL ) {
                peak->DecRef();
                peakVector.push_back( peak );
              }
              peaks.clear();
#ifdef STANDARD_C11
              peaks.shrink_to_fit();
#endif
              cube.SetEmpty();
            }
          } 
          /// \ru Вернуть указатель на апекс по его номеру. \en Return the pointer to apex by its number. 
  const   MbApex3D * GetApex( size_t i ) const { return ( (i < peaks.size()) ? peaks[i]: NULL ); }
          /// \ru Вернуть указатель на апекс по его номеру для модификации. \en Return the pointer to apex by its number to be modified. 
          MbApex3D * SetApex( size_t i )       { return ( (i < peaks.size()) ? peaks[i]: NULL ); } 
          /// \ru Получить указатели на вершины. \en Get pointers to apexes.
          template <class ApexesVector>
          void    GetApexes( ApexesVector & peakVector ) const {
            size_t peaksCnt = peaks.size();
            peakVector.reserve( peakVector.size() + peaksCnt );
            for ( size_t k = 0; k < peaksCnt; ++k ) {
              const MbApex3D * peak = peaks[k];
              peakVector.push_back( peak );
            }
          }

          // \ru Создать полигональный объект - упрощенную копию данного объекта. \en Create a polygonal object - a polygonal copy of the given object. 
          MbMesh *  CreateMeshByExistingItem( const MbRefItem & ) const; 

          /// \ru Инициализировать объект. \en Initialize an object. 
          void    InitMesh( const MbMesh & );
          /// \ru Добавить объекты сетки из присланной сетки. \en Add objects of mesh from a given mesh. 
          bool    AddMesh( const MbMesh &, bool checkSamePointers );

          /// \ru Получить пространственный объект, для которого построен полигональный объект. \en Get a spatial object for which a polygonal object is constructed. 
  const   MbSpaceItem * SpaceItem() const { return ((item != NULL && item->RefType() == rt_SpaceItem) ? (const MbSpaceItem *)item : NULL); }
          /// \ru Получить двумерный объект, для которого построен полигональный объект. \en Get a two-dimensional object for which a polygonal object is constructed. 
  const   MbPlaneItem * PlaneItem() const { return ((item != NULL && item->RefType() == rt_PlaneItem) ? (const MbPlaneItem *)item : NULL); }
          /// \ru Получить объект геометрической модели, для которого построен полигональный объект. \en Get a model geometric object for which a polygonal object is constructed. 
  const   MbItem * Item() const
          {
            const MbItem * modelItem = NULL;
            if ( item != NULL ) {
              MbeRefType refType = item->RefType();
              if ( refType == rt_SpaceItem ) {
                if ( static_cast<const MbSpaceItem *>(item)->Family() == st_Item )
                  modelItem = static_cast<const MbItem *>(item);
              }
            }
            return modelItem;
          }
          /// \ru Получить объект, для которого построен полигональный объект. \en Get an object for which a polygonal object is constructed. 
  const   MbRefItem * GetRefItem() const { return item; }
          /// \ru Запомнить объект, для которого построен полигональный объект. \en Remember an object for which a polygonal object is constructed. 
          void    SetRefItem( const MbRefItem * g ) { item = g; }  
          /// \ru Сбросить все запомненные объекты. \en Reset all reference objects. 
          void    ResetRefItems();
          /// \ru Установить тип полигонального объекта. \en Set a type of polygonal object. 
          void    SetMeshType( MbeSpaceType t ) { type = t; }
          /// \ru Дать тип полигонального объекта. \en Get a type of polygonal object. 
          MbeSpaceType GetMeshType() const { return type; }

          /// \ru Установить имя всем триангуляциям. \en Set the name of all triangulations. 
          void    SetGridName( SimpleName n ); 
          /// \ru Установить имя всем полигонам. \en Set the name of all polygons. 
          void    SetPolygonName( SimpleName n );
          /// \ru Установить имя всем апексам. \en Set the name of all apexes. 
          void    SetApexName( SimpleName n );

          /// \ru Замкнутость объекта. \en Object closedness. 
          bool    IsClosed() const    { return closed; }
          /// \ru Установить (не)замкнутость объекта. \en Set object (un-) closedness. 
          void    SetClosed( bool c ) { closed = c;    }
          /// \ru Объекты на числах double. \en Objects on double data. 
          bool    IsExact() const { return exact; }

          /** 
            \brief \ru Определить положение объекта относительно плоскости.
                   \en Define the object position relative to the plane. \~
            \details \ru Определить положение объекта относительно плоскости XY локальной системы координат.
                     \en Define the object position relative to the plane XY of a local coordinate system. \~
            \param[in] pl - \ru Локальная система координат, задающая плоскость.
                            \en A local coordinate system which defines a plane. \~
            \param[in] eps - \ru Метрическая точность.
                             \en A metric tolerance. \~
            \param[in] onlyInItem - \ru Интересует только положение объекта над плоскостью XY локальной системы координат.
                                    \en Whether the object position relative to the XY-plane of a local coordinate system is interested only. \~
            \return \ru iloc_OnItem - объект пересекает плоскость XY локальной системы координат,\n
                    iloc_InItem - объект расположен над плоскостью XY локальной системы координат,\n
                    iloc_OutOfItem - объект расположен под плоскостью XY локальной системы координат.
                    \en Iloc_OnItem - object intersects the XY-plane of a local coordinate system,\n
                    iloc_InItem - object is located over the XY plane of a local coordinate system,\n
                    iloc_OutOfItem - object is located under the XY plane of a local coordinate system. \~
          */
          MbeItemLocation GetLocation( const MbPlacement3D & pl, double eps, bool onlyInItem = false ) const; 

          /** 
            \brief \ru Определить положение объекта относительно трубы.
                   \en Define the object position relative to the tube. \~
            \details \ru Определить, расположен ли объект внутри трубы прямоугольного сечения, 
              заданного прямоугольником в плоскости XY локальной системы координат.
                     \en Define whether the object is inside the tube of rectangular section, 
              given by a rectangle in the XY plane of a local coordinate system. \~
            \param[in] place - \ru Локальная система координат, в в плоскости XY которой лежит сечение трубы.
                               \en A local coordinate system in the XY plane of which a tube section is located. \~
            \param[in] rect - \ru Прямоугольник, задающая сечение трубы.
                              \en A rectangle which defines a tube section. \~
            \param[in] eps - \ru Метрическая точность.
                             \en A metric tolerance. \~
            \param[in] onlyInItem - \ru Интересует только положение объекта внутри трубы.
                                    \en Whether the object position relative to the tube is interested only. \~
            \return \ru true, если объект расположен внутри трубы.
                    \en Returns true if the object is inside the tube. \~
          */
          bool    InsideLocation( const MbPlacement3D & place, MbRect & rect, double eps ) const; 

          /// \ru Перевести все объекты в треугольники и уравнять число точек и нормалей. \en Convert all objects to triangles and equalize the number of points and normals. 
          void    ConvertAllToTriangles();  
          /// \ru Общее количество всех треугольников. \en The total number of all (adjacent and nonadjacent) triangles. 
          size_t  AllTrianglesCount() const;   
          /// \ru Общее количество всех четырёхугольников. \en The total number of all (adjacent and nonadjacent) quadrangles. 
          size_t  AllQuadranglesCount() const; 
          /// \ru Общее количество всех точек триангуляций. \en The total number of all points of triangulations. 
          size_t  AllPointsCount() const; 
          /// \ru Общее количество всех нормалей триангуляций. \en The total number of all normals of triangulations. 
          size_t  AllNormalsCount() const; 
          /// \ru Общее количество всех параметров триангуляций. \en The total number of all parameters of triangulations. 
          size_t  AllParamsCount() const; 
          /// \ru Общее количество всех точек полигонов. \en The total number of all points of poligons. 
          size_t  AllPolyPointsCount() const; 
  /** \} */

          /** \brief \ru Найти пересечение прямой линии и полигонального объекта.
                     \en Find the intersection of a straight line with the polygonal object. \~
            \details \ru Для всех треугольников определяется пересечение с прямой линии и вычисляется минимальное значение 
              параметра точки пересечения на секущей прямой линии. \n
                     \en For all the triangles the intersection with the straight line is determined and the minimum value of 
              the intersection point parameter on the secant straight line is calculated. \n \~
            \param[in] line - \ru Прямая линия, для которой вычисляется пересечение с  и полигонального объекта.
                              \en Straight line to calculate the intersection of triangulation with. \~
            \param[out] crossPnt - \ru Точка пересечения.
                                   \en The intersection point. \~
            \param[out] tRes - \ru Параметр точки пересечения на линии.
                               \en Parameter of the intersection point on the line. \~
            \return \ru Найдено ли пересечение (true - В случае успеха).
                    \en Whether the intersection is found (true if success). \~
          */
          bool    LineIntersection( const MbFloatAxis3D &  line,
                                          MbFloatPoint3D & crossPnt,
                                          float         &  tRes );

private:
          // \ru Объявление оператора присваивания без реализации, чтобы не было присваивания по умолчанию. \en The declaration of the assignment operator without implementation to prevent an assignment by default. 
          MbMesh & operator = ( const MbMesh & );

  DECLARE_PERSISTENT_CLASS_NEW_DEL( MbMesh ) 
}; // MbMesh

IMPL_PERSISTENT_OPS( MbMesh )

#endif // __MESH_H
