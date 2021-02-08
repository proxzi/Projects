////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Контейнер для визуальных объектов, который содержит таблицу
             визуальных объектов, а также таблицу связей c шейдерами.
         \en Container for visual objects that includes visual object map
             and shader linking map. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_RENDERCONTAINER_H
#define __VSN_RENDERCONTAINER_H

#include <unordered_map>
#include "vsn_renderobject.h"
#include "vsn_light.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Viewport;
class Frustum;
class SpacePartitioning;
class RenderContainerPrivate;

using  RenderContainerIterator = std::map<NodeKey, RenderObject*>::const_iterator;
//------------------------------------------------------------------------------
/** \brief \ru Контейнер для визуальных объектов.
           \en Container for visual objects. \~
    \details \ru Содержит таблицу визуальных объектов.
             \en Contains visual object map. \~
    \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS RenderContainer
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit RenderContainer();
    /// \ru Деструктор. \en Destructor. 
    virtual ~RenderContainer();
public:
    /** \brief  \ru Является ли контейнер пустым.
                \en Checks if container is empty. \~ 
        \return \ru Вернуть true, если контейнер пустой.
                \en True if container is empty. \~
    */
    bool IsEmpty() const;

    /** \brief  \ru Вернуть размер контейнера объектов сцены.
                \en Returns container size of scene objects. \~ 
        \return \ru Размер контейнера.
                \en Container size. \~
    */
    size_t GetSize() const;

    /** \brief  \ru Вернуть все RenderObject из контейнера сцены.
                \en Returns all RenderObject from the scene container. \~ 
        \return \ru Список всех RenderObject в контейнере сцены.
                \en List of all RenderObject in the scene container. \~
    */
    std::list<RenderObject*> GetObjects();

    /** \brief  \ru Вернуть видимые RenderObject из контейнера сцены.
                \en Returns all visible RenderObject from the scene container. \~ 
        \return \ru Список всех видимых RenderObject в контейнере сцены.
                \en List of all visible RenderObject in the scene container. \~
    */
    std::list<RenderObject*> GetVisibleObjects();

    /** \brief \ru Вернуть указатель на RenderObject по идентификатору из контейнера, если этот объект есть.
               \en Returns pointer to RenderObject by identifier from the container, if this object exists. \~ 
        \param[in] objKey - \ru Идентификатор объекта.
                            \en Object identifier. \~
        \return \ru Указатель на объект, может быть равен null.
                \en Pointer to object. It can be null. \~
    */
    RenderObject* GetObjectById(NodeKey objKey);

    /** \brief  \ru Вернуть габаритный куб всех видимых объектов.
                \en Returns bounding box of all visible objects. \~ 
        \param[in] allObjects - \ru Если true, то вернуть габаритный куб только видимых объектов, в противном случае- всех объектов.
                                \en If true, returns bounding box of only visible objects. Otherwise, returns bounding box of all objects. \~
        \return \ru Объединённый габаритный куб.
                \en Union bounding box. \~
    */
    MbCube GetBoundingBox(bool allObjects = false);

    /** \brief  \ru Вернуть количество выбранных объектов.
                \en Returns count of selected objects. \~ 
    \return \ru Количество выбранных объектов.
            \en Count of selected objects. \~
    */
    size_t GetSelectionCount() const;

    /** \brief  \ru Вернуть таблицу выбранных объектов.
                \en Returns map of selected objects. \~ 
        \return \ru Таблица объектов.
                \en Object map. \~
    */
    std::map<NodeKey, RenderObject*>* GetSelection();

    /** \brief  \ru Вернуть true, если объект есть в контейнере объектов сцены.
                \en True if object exists in scene object container. \~ 
        \param[in] objKey - \ru Идентификатор объекта.
                            \en Object identifier. \~
        \return \ru True, если объект есть в контейнере.
                \en True if object exists in container. \~
    */
    bool IsExistViewObject3D(NodeKey objKey) const;

    /** \brief  \ru Вернуть true, если элемент выделен.
                \en True if element is selected. \~ 
        \param[in] objKey - \ru Идентификатор объекта.
                            \en Object identifier. \~
        \return \ru True, если объект выделен.
                \en True if object is selected. \~
    */
    bool IsSelected(NodeKey objKey) const;

    /** \brief  \ru Вернуть состояние видимости.
                \en Returns visibility state. \~ 
        \details    \ru Вернуть состояние видимости, рассчитанное механизмом оптимизации.
                    \en Returns visibility state computed by optimization mechanism. \~
        \return \ru True, если объект видим.
                \en True if object is visible. \~
    */
    bool GetShowState() const;

    /** \brief  \ru Вернуть количество видимых объектов.
                \en Returns count of visible objects. \~ 
        \return \ru Количество видимых объектов.
                \en Count of visible objects. \~
    */
    int GetShowObjectsCount() const;

    /** \brief \ru Вернуть true, если используется пространственное разбиение.
               \en True if space partitioning is used. \~
        \return \ru True, если пространственное разбиение используется.
                \en True if space partitioning is used. \~
    */
    bool IsSpacePartitioningUsed() const;

    /** \brief  \ru Вернуть указатель на пространственное разбиение (Octree).
                \en Returns pointer to space partitioning (Octree). \~ 
        \return \ru Указатель на пространственное разбиение.
                \en Pointer to space partitioning. \~
    */
    const std::shared_ptr<SpacePartitioning> GetSpacePartitioning() const;

    /** \brief  \ru Вернуть true, если контейнер видимый.
                \en True if container is visible. \~
        \return \ru True, если контейнер видимый.
                \en True if container is visible. \~
    */
    bool IsVisible() const;


    /** \brief  \ru Установить состояние видимости контейнера.
                \en Sets visibility state for container. \~ 
        \param[in] bVisible - \ru Флаг видимости.
                              \en Visibility flag. \~
    */
    void SetVisible( bool bVisible );
public:
    /** \brief  \ru Добавить визуальный объект в контейнер.
                \en Adds visual object to container. \~ 
        \param[in] obj - \ru Добавляемый объект.
                         \en Added object. \~
        \param[in] shaderId - \ru Идентификатор шейдера.
                              \en Shader identifier. \~
        \return \ru True, если операция прошла успешно.
                \en True if operation was successfully done. \~
    */
    bool AddObject(const RenderObject& obj, uint shaderId = 0);

    /** \brief  \ru Удалить объект из контейнера.
                \en Removes object from container. \~ 
        \details \ru Удалить объект из контейнера, а также убрать все связи с ним.
                 \en Removes object from container and removes all links with it. \~
        \param[in] objId - \ru Удаляемый объект.
                           \en Removable object. \~
        \return \ru True, если операция прошла успешно.
                \en True if operation was successfully done. \~
    */
    bool RemoveViewObject(NodeKey objId);

    /** \brief \ru Удалить все объекты из контейнера.
                \en Removes all objects from container. \~ 
    */
    void Clear();

    /** \brief  \ru Выбрать объект по идентификатору.
                \en Selects object by identifier. \~ 
        \param[in] objKey - \ru Идентификатор объекта.
                            \en Object identifier. \~
        \param[in] primitive - \ru Флаг выбора примитивов.
                               \en Primitive selection flag. \~
        \return \ru True, если операция выполнена успешно.
                \en True if operation was successfully done. \~
    */
    bool SetSelectObject(NodeKey objKey, bool primitive = false);

    /** \brief  \ru Выбрать все объекты.
                \en Selects all objects. \~ 
        \param[in] allShowState - \ru Установить статус выбора.
                                  \en Sets selection state. \~
    */
    void SelectAll(bool allShowState = false);

    /** \brief  \ru Cнять выбор с объекта по идентификатору.
                \en Unselects object by identifier. \~ 
        \param[in] objKey - \ru Визуальный объект.
                            \en Visual object. \~
        \return \ru True, если операция выполнена успешно.
                \en True if operation was successfully done. \~
    */
    bool UnselectObject(NodeKey objKey);

    /** \brief \ru Снять выбор со всех объектов.
                \en Unselects all objects. \~ 
    */
    void UnselectAll();

    /** \brief  \ru Установить режим для отрисовки полигона.
                \en Sets mode for rendering polygon. \~ 
        \param[in] face - \ru Указывает, к лицевой, тыльной или к обеим сторонам применяется опция, заданная вторым параметром. Может применять значения GL_FRONT, GL_BACK и GL_FRONT_AND_BACK.
                          \en Specifies that mode is applied to front, back sides or both of them. It must be GL_FRONT, GL_BACK and GL_FRONT_AND_BACK. \~
        \param[in] mode - \ru Указывает, как будет рисоваться полигон. Он принимает значения: GL_POINT(рисует только точки), GL_LINE(рисует линии) и GL_FILL(рисует заполненные полигоны).
                          \en Specifies how polygon will be rendered. It accepts values: GL_POINT(renders only points), GL_LINE(renders lines) and GL_FILL(renders filled polygons). \~
    */
    void SetPolygonModeForAll(uint face, uint mode);

    /** \brief  \ru Установить видимость объекта по идентификатору.
                \en Sets object visibility by identifier. \~ 
        \param[in] objKey - \ru Визуальный объект.
                            \en Visual object. \~
        \param[in] bVisible - \ru Флаг видимости.
                              \en Visibility flag. \~
    */
    void SetVisibleObject(NodeKey objKey, bool bVisible);

    /** \brief \ru Сделать все объекты в контейнере видимыми.
               \en Makes all objects visible in container. \~ 
    */
    void SetVisibleAll();

    /** \brief \ru Сделать все объекты в контейнере невидимыми.
               \en Makes all objects invisible in container. \~ 
    */
    void SetInvisibleAll();

    /** \brief \ru Изменить состояние видимости объектов в контейнере на противоположное.
               \en Switches object visibility in container to opposite state(visible/invisible). \~ 
    */
    void SwitchVisibleState();

    /** \brief \ru Вернуть признак использования LOD.
               \en Returns flag of LOD usage. \~ 
        \return \ru True, если используются LOD.
                \en True if LOD is used. \~
    */
    bool IsLevelOfDetailEnabled() const;

    /** \brief  \ru Установить использование LOD.
                \en Sets LOD usage. \~ 
        \param[in] bEnabled - \ru Флаг использования LOD.
                              \en Flag of LOD usage. \~
        \param[in] pView -  \ru Viewport.
                            \en Viewport. \~
    */
    void SetLevelOfDetailEnabled(bool bEnabled, Viewport* pView);

    /** \brief \ru Связать пространственное разбиение с контейнером объектов.
                \en Links space partitioning with object container. \~
        \param[in] pSpacePartitioning - \ru Пространственное разбиение.
                                        \en Space partitioning. \~
    */
    void SetLinkSpatialSplit(std::shared_ptr<SpacePartitioning> pSpacePartitioning);

    /** \brief \ru Отсоединить пространственное разбиение от контейнера объектов.
                \en Unlinks space partitioning from object container. \~ 
    */
    void UnlinkSpacePartitioning();

    /** \brief \ru Установить признак использования пространственного разбиения.
               \en Sets flag of space partitioning usage. \~
        \param[in] bSpacePartitioning - \ru Флаг использования пространственного разбиения.
                                        \en Flag of space partitioning usage. \~
    */
    void SetSpatialSplitUsage(bool bSpacePartitioning);


    /** \brief  \ru Обновить видимость объектов в усеченном конусе.
                \en Updates object visibility in view frustum. \~ 
        \param[in] pViewport - \ru Указатель на Viewport.
                               \en A pointer to Viewport. \~
        \param[in] pMatrix - \ru Новая матрица в усеченном конусе.
                             \en New matrix in view frustum. \~
    */
    void UpdateObjectVisibleState(Viewport* pViewport, MbMatrix3D* pMatrix = nullptr);

    /** \brief \ru Обновить видимость по указанному усеченному конусу.
               \en Updates visibility by specified view frustum. \~
        \param[in] frustum - \ru Источник усечения.
                             \en Frustum source. \~
    */
    void UpdateObjectVisibleState(const Frustum& frustum);

    /** \brief  \ru Установить контейнеру viewport.
                \en Sets viewport for container. \~
        \param[in] pViewport - \ru Указатель на viewport.
                               \en Pointer to viewport. \~ 
    
    */
    void SetViewport(Viewport* pViewport);

    /** \brief  \ru Установить флаг использования VBO.
                \en Sets flag of Vertex Buffer Object (VBO) usage. \~ 
        \param[in] usage - \ru Флаг использования VBO.
                           \en Flag of VBO usage. \~
    */
    void SetUseVertexBufferObjects(bool usage);

public:
    /** \brief  \ru Отрисовка групп контейнера.
                \en Renders container groups. \~ 
        \param[in] groupId - \ru Идентификатор группы.
                             \en Group identifier. \~
        \param[in] renderingMode - \ru Способ отрисовки.
                                   \en Rendering mode. \~
        \param[in] viewport      - \ru Параметры отображения.
                                   \en Rendering parameters. \~
    */
    void DoRender(uint groupId, RenderMode renderingMode, Viewport* viewport = nullptr);


    RenderContainerIterator begin() const;
    RenderContainerIterator end() const;
private:
    VSN_DECLARE_PRIVATE(RenderContainer)
    friend class CuttingToolPrivate;
};

VSN_END_NAMESPACE

#endif /* __VSN_RENDERCONTAINER_H */
