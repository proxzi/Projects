////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneSegment является базовым классом для всех сегментов в графе сцены.
         \en SceneSegment class is the base class for all segments in the scene graph. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SCENESEGMENT_H
#define __VSN_SCENESEGMENT_H

#include <set>
#include <mb_cube.h>

#include "vsn_essence.h"
#include "vsn_scsegmentdata.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class SceneDescriptor;
class Material;
class RenderState;
class SceneSegmentRef;
class SceneSegmentPrivate;


//------------------------------------------------------------------------------
/** \brief \ru Класс SceneSegment является базовым классом для всех сегментов в графе сцены.
           \en SceneSegment class is the base class for all segments in the scene graph.  \~
  \details \ru Класс SceneSegment может быть использован как контейнер сегментов. Входящие сегменты добавляются с помощью функций AddSegment() и InsertSegment().
               Порядок сегментов является важным, так как геометрические сегменты отрисовываются в соответствии с их положением в графе сцены.

               Сегменты графа сцены содержат механизм, который описывает, какие части сцены изменились.
               Он включает в себя комбинированные матрицы, изменения в иерархии сегментов и т.д.
           \en The SceneSegment class can be used as a segment container. Entering segments are added with the AddSegment() and InsertSegment() functions. 
               The order of segments is very important as geometry segments are rendered according to their position in the scene graph. \n

               The scene graph segments contains a mechanism to describe which parts of the scene has changed. It includes the combined matrixes, 
               changes in the segment hierarchy, and so on. \~
  \ingroup Vision_Scenegraph
*/
// ---
class VSN_CLASS SceneSegment : public Essence
{
    VSN_OBJECT(SceneSegment);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SceneSegment(SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с данными для сегмента.
               \en Special constructor with segment data. \~ 
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(NodeKey key, SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с данными для сегмента.
                \en Special constructor with segment data. \~ 
        \param[in] pSegmentData - \ru Сегмент графа данных сцены.
                                  \en Scene data graph segment. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
        \param[in] pDescriptor - \ru Описание сцены.
                                 \en Scene description. \~
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
    */
    SceneSegment(SceneSegmentData* pSegmentData, SceneSegment* pParent = nullptr, SceneDescriptor* pDescriptor = nullptr, uint shaderId = 0);

    /** \brief \ru Специальный конструктор с данными для сегмента и идентификатором сегмента.
                \en Special constructor with segment data and segment identifier. \~ 
        \param[in] pSegmentData - \ru Данные сегмента графа сцены.
                                  \en Scene graph segment data. \~
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pDescriptor - \ru Описание сцены.
                                 \en Scene description. \~
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
    */
    SceneSegment(SceneSegmentData* pSegmentData, NodeKey key, SceneDescriptor* pDescriptor = nullptr, uint shaderId = 0);

    /** \brief \ru Специальный конструктор с представлением.
                \en Special constructor with representation. \~ 
        \param[in] pRep - \ru Представление геометрии.
                          \en Geometry representation. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(GeometryRep* pRep, SceneSegment* pParent = nullptr);

    /** \brief \ru Специальный конструктор с представлением.
                \en Special constructor with representation. \~ 
        \param[in] pRep - \ru Представление геометрии.
                          \en Geometry representation. \~
        \param[in] key - \ru Идентификатор сегмента.
                         \en Segment identifier. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    SceneSegment(GeometryRep* pRep, NodeKey key, SceneSegment* pParent = nullptr);

    /// \ru Деструктор. \en Destructor. 
    virtual ~SceneSegment();

public:
    /// \ru Вернуть имя сегмента. \en Returns segment name. \~
    const String GetDataName() const;

    /** \brief \ru Установить имя сегменту.
               \en Sets segment name. \~ 
        \param[in] name - \ru Имя сегмента.
                          \en Segment name. \~
    */
    void SetDataName(const String& name);

    /** \brief \ru Вернуть абсолютную матрицу сегмента.
               \en Returns absolute matrix of segment. \~ 
        \details \ru Вернуть абсолютную матрицу сегмента.
                 \en Returns absolute matrix of segment. \~
        \return \ru Абсолютная матрица сегмента.
                \en Absolute matrix of segment. \~
    */
    const MbMatrix3D& GetAbsoluteMatrix() const;

    /** \brief \ru Вернуть относительную матрицу сегмента.
               \en Returns relative matrix of segment. \~ 
        \return \ru Относительная матрица сегмента.
                \en Relative matrix of segment. \~
    */
    MbMatrix3D GetRelativeMatrix() const;

    /** \brief \ru Является ли сегмент сиротой.
               \en Checks if segment is orphan. \~ 
        \return \ru True, если нет родителя.
                \en True if no parent. \~
    */
    bool IsOrphan() const;

    /** \brief \ru Есть ли у сегмента родитель.
               \en Checks if segment has parent. \~ 
        \return \ru True, если есть родитель.
                \en True if segment has parent. \~
    */
    bool HasParent() const;

    /** \brief \ru Есть ли у сегмента представление.
               \en Checks if segment has representation. \~ 
        \return \ru True, если есть представление.
                \en True if segment has representation. \~
    */
    bool HasRep() const;

    /** \brief \ru Есть ли у сегмента RenderObject.
               \en Checks if segment has RenderObject. \~ 
        \return \ru True, если в сегменте есть RenderObject.
                \en True if segment has RenderObject. \~
    */
    bool HasViewObject3D() const;

    /// \ru Вернуть указатель на данные сегмента. \en Returns pointer to segment data. \~
    SceneSegmentData* GetSegmentData() const;

    /// \ru Вернуть указатель на ссылку сегмента сцены. \en Returns pointer to scene segment reference. \~
    SceneSegmentRef* GetSegmentRef() const;

    /// \ru Вернуть количество сегментов в данном сегменте. \en Returns count of segments in this segment. \~
    size_t GetCountOfSegment() const;

    /// \ru Вернуть признак наличия подсегментов. \en True if segment has subsegments. \~
    bool HasSegments() const;

    /** \brief \ru Признак возможности добавить данный сегмент в массив сегментов.
               \en Checks if segment can be added to segment array. \~ 
        \param[in] pSegment - \ru Сегмент.
                              \en Segment. \~
        \return \ru True, если данный сегмент может быть добавлен в массив сегментов.
                \en True if segment can be added to segment array. \~
    */
    bool CanInsertToSegment(SceneSegment* pSegment) const;

    /// \ru Вернуть указатель на родительский сегмент. \en Returns pointer to parent segment. \~
    SceneSegment* GetParentSegment() const;

    /// \ru Вернуть всех предков данного сегмента. \en Returns all parents for segment. \~
    std::list<SceneSegment*> GetAncestorsSegment() const;

    /** \brief \ru Вернуть указатель на сегмент сцены по индексу.
               \en Returns pointer to scene segment by index. \~ 
        \param[in] index - \ru Индекс сегмента.
                           \en Segment index. \~
        \return \ru Указатель на сегмент сцены, если такой есть.
                \en Returns pointer to scene segment if available. \~
    */
    SceneSegment* GetSegmentAt(size_t index) const;

    /// \ru Вернуть массив сегментов сцены. \en Returns array of scene segments. \~
    std::list<SceneSegment*> GetSegments() const;

    /// Return immediate child scene nodes.
    virtual std::list<Node*> GetChildren() const;

    /// \ru Вернуть массив всех сегментов сцены данного узла. \en Returns array of all subsegments for this segment. \~
    std::list<SceneSegment*> GetSubSegments() const;

    /// \ru Вернуть количество граней представления этого сегмента. \en Returns count of representation faces for this segment. \~
    size_t GetFaceCount() const;

    /// \ru Вернуть количество вершин представления этого сегмента. \en Returns count of representation vertexes for this segment. \~
    size_t GetVertexCount() const;

    /// \ru Вернуть количество материалов представления этого сегмента. \en Returns count of representation materials for this segment. \~
    size_t GetMaterialCount() const;

    /// \ru Вернуть массив материалов представления этого сегмента. \en Returns array of representation materials for this segment. \~
    std::set<Material*> GetMaterials() const;

    ///  \ru Установить цвет материалу представления \en NOT TRANSLATED \~
    void SetColorPresentationMaterial(const Color& color);

    /// \ru Получить состояние видимости сегмента с учотом родительских элементов. \en Get the visibility state of the segment considering the parent elements. \~
    bool IsVisible() const;

    /// \ru Вернуть габаритный куб сегмента. \en Returns bounding box of segment. \~
    MbCube GetBoundingBox() const;

    /// \ru Вернуть число вхождений этого сегмента. \en Returns count of segments in this segment. \~
    size_t GetSegmentCount() const;

    /// \ru Вернуть указатель на состояние отрисовки. \en Returns pointer to rendering state. \~
    const RenderState* GetRenderState() const;

    /// \ru Вернуть количество сегментов, входящих в этот сегмент. \en Returns count of subsegments in this segment. \~
    size_t GetCountSegmentsOfLine() const;

    /// \ru Вернуть указатель на описание сцены этого сегмента. \en Returns pointer to scene description for this segment. \~
    SceneDescriptor* GetSceneDescriptor() const;

    /// \ru Вернуть массив ссылок этого сегмента. \en Returns array of references for this segment. \~
    std::set<SceneSegmentRef*> GetChildrenReferences() const;

    /** \brief \ru Вернуть все указатели на ссылочную геометрию указанного сегмента.
               \en Returns all pointers to reference geometry for the specified segment. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru Массив указателей на ссылки.
                \en Array of pointers to references. \~
    */
    static std::set<SceneSegmentRef*> GetSegmentReferences( const SceneSegment* pSegment );

    /// \ru Вернуть признак самостоятельного создания RenderObject. \en Returns flag for independent creation of RenderObject. \~
    bool IsIndependentCreationObject3D() const;

    /** \brief \ru Установить признак автоматического создания RenderObject.
               \en Sets flag for automatic creation of RenderObject. \~ 
        \param[in] bIndependent - \ru Значение признака.
                                  \en Value of flag. \~
    */
    void SetIndependentCreateViewObject( bool bIndependent );

    /// \ru Вернуть true, если сегмент является плавающим, иначе false. \en True if floating segment. \~
    bool IsFloating() const;

    /** \brief \ru Вернуть индекс данного сегмента в массиве указанного сегмента.
                \en Returns index of segment in array of specified segment. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru Индекс.
                \en Index. \~
    */
    ptrdiff_t GetIndexOf(const SceneSegment* pSegment) const;

    /** \brief \ru Вернуть признак существования указанного сегмента в данном сегменте.
               \en Returns flag for existence of specified segment in this segment. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru True, если в этом сегменте содержится указанный сегмент.
                \en True if segment has the specified segment. \~
    */
    bool ExistSegment( const SceneSegment* pSegment ) const;

public:
    /// \ru Обновить абсолютную матрицу. \en Refreshes absolute matrix. \~
    SceneSegment* RefreshAbsoluteMatrix();

    /** \brief \ru Обновить абсолютную матрицу внутренних подсегментов.
               \en Refreshes absolute matrix of internal subsegments. \~ 
        \details \ru Обновить абсолютную матрицу внутренних подсегментов.
                 \en Refreshes absolute matrix of internal subsegments. \~
        \return \ru Сегмент сцены.
                \en Scene segment. \~
    */
    SceneSegment* RefreshSubSegmentAbsoluteMatrix();

    /** \brief \ru Добавить новый сегмент в сцену.
               \en Adds new segment to scene. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
    */
    void AddSegment(SceneSegment* pSegment);

    /** \brief \ru Вставить новый сегмент в указанную позицию.
               \en Inserts new segment to defined position. \~ 
        \param[in] index - \ru Индекс позиции.
                           \en Positon index. \~
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
    */
    void InsertSegment(int index, SceneSegment* pSegment);

    /** \brief \ru Создать и добавить новый сегмент с указанными данными.
               \en Creates and adds a new segment with shown data. \~ 
        \param[in] pSegmentData - \ru Сегмент данных графа сцены.
                                  \en Scene graph data segment. \~
        \return \ru Созданный сегмент сцены.
                \en Created scene segment. \~
    */
    SceneSegment* AddSegment(SceneSegmentData* pSegmentData);

    /// \ru Сделать сегмент самостоятельным. \en Makes an independent segment. \~
    void DoSegmentAlone();

    /** \brief \ru Удалить указанный сегмент из массива узлов.
                \en Removes specified segment from segment array. \~ 
        \param[in] pSegment - \ru Сегмент сцены.
                              \en Scene segment. \~
        \return \ru True, если сегмент найден и удален.
                \en True if segment is found and removed. \~
    */
    bool RemoveSegment(SceneSegment* pSegment);

    /// \ru Удалить всех детей. \en Remove all children. \~
    void RemoveChildren();

    /// \ru Сделать обращение нормалей сегмента. \en Makes reverse of the segment normals. \~
    void ReverseNormalsOfSegment();

    /** \brief \ru Создать RenderObject для этого сегмента.
               \en Creates RenderObject for this segment. \~ 
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
        \return \ru True, если RenderObject создан.
                \en True if RenderObject is created. \~
    */
    bool CreateViewObject3D( uint shaderId = 0 );

    /// \ru Удалить RenderObject этого сегмента. \en Removes RenderObject for this segment. \~
    bool RemoveViewObject();

    /** \brief \ru Установить описание сцены.
               \en Sets scene description. \~ 
        \param[in] pDescriptor - \ru Описание сцены.
                                 \en Scene description. \~
    */
    void SetSceneDescriptor( SceneDescriptor* pDescriptor );

    /** \brief \ru Установить количество вхождений этого сегмента.
               \en Sets count of subsegments. \~ 
        \param[in] count - \ru Количество вхождений сегмента.
                           \en Count of subsegments.\~
    */
    void SetSegmentCount( uint count );

    /** \brief \ru Обновить количество вхождений этого сегмента.
               \en Refreshes count of subsegments. \~ 
        \param[in] count - \ru Количество вхождений сегмента.
                           \en Count of subsegments. \~
        \return \ru Обновленное количество вхождений сегмента.
                \en Refreshed count of subsegments. \~
    */
    uint UpdateSegmentCount( uint count );

    /** \brief \ru Установить видимость.
               \en Sets visibility. \~ 
        \param[in] bVisible - \ru Признак видимости.
                              \en Flag of visibility. \~
    */
    void SetVisible(bool bVisible);

    /** \brief \ru Получть значение видимости.
               \en Get visibility value. \~ 
    */
    bool GetVisible() const;

    /** \brief \ru Установить состояние отрисовки сегмента.
               \en Sets rendering state for segment. \~ 
        \param[in] renderState - \ru Состояние отрисовки.
                                 \en Rendering state. \~
    */
    void SetRenderStates(const RenderState& renderState);

    /// \ru Удалить пустые сегменты. \en Removes empty segments. \~
    void RemoveEmptySubSegment();

    /** \brief \ru Создать новую относительную матрицу.
               \en Creates new relative matrix. \~ 
        \details \ru Создать относительную матрицу по указанной с удалением старой.
                 \en Creates relative matrix by given one with removing old matrix. \~
        \param[in] relativeMatrix - \ru Указанная относительная матрица.
                                    \en Given relative matrix. \~
    */
    void CreateRelativeMatrix(const MbMatrix3D& relativeMatrix);

    /// \ru Удалить относительную матрицу сегмента. \en Removes relative matrix of segment. \~
    void RemoveRelativeMatrix();

    /** \brief \ru Поменять местами i-й и j-й сегменты.
               \en Swaps i-th and j-th segments. \~ 
        \param[in] i - \ru Номер сегмента.
                       \en Number of segment. \~
        \param[in] j - \ru Номер сегмента.
                       \en Number of segment. \~
    */
    void SwapSegment(size_t i, size_t j);

    /// \ru Добавить новый указатель на GeometryRep. \en Adds new pointer to GeometryRep.
    void SetRepresentation(GeometryRep* pRepresentation);

    /// \ru Задать сегменту слой. \n \en Set layer to scene segment \~
    void     SetRenderLayer(uint32_t, bool andSubSegments = true);
    /// \ru Узнать слой сегмента. \n \en Get scene segment layer \~
    uint32_t GetRenderLayer() const;
    /// \ru Исключить из мезанихма поиска объектов. \n \en Exclude from process find objects \~
    void SetIgnoreForPick(bool value);
    /// \ru Являеться ли объект исключенным из механизма поиска объектов. \n \en Check the object is excluded from process find object \~
    bool IsIgnoreForPick() const;
private:
    VSN_DECLARE_EX_PRIVATE(SceneSegment);
};

VSN_END_NAMESPACE

#endif /* __VSN_SCENESEGMENT_H */
