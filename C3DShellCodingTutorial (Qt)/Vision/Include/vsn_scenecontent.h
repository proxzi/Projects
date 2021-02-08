////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneContent представляет содержание сцены в виде графа.
         \en SceneContent class represents scene content as the graph. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SCENECONTENT_H
#define __VSN_SCENECONTENT_H

#include "vsn_rendercontainer.h"
#include "vsn_scenesegment.h"
#include "vsn_scsegmentref.h"
#include "vsn_scsegmentdata.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class SceneContentPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneContent представляет содержание сцены в виде графа.
           \en SceneContent class represents scene content as the graph. \~
  \ingroup Vision_SceneGraph
*/
// ---
class VSN_CLASS SceneContent
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SceneContent();
    /// \ru Конструктор по корневому сегменту сцены. \en Constructor by scene root segment.
    explicit SceneContent(SceneSegment* pSegment);
    /// \ru Конструктор копирования. \en Copy-constructor.
    SceneContent(const SceneContent& other);
    /// \ru Деструктор. \en Destructor. 
    virtual ~SceneContent();
public:
    /// \ru Вернуть габарит содержимого сцены. \en Returns bounding box of scene content. \~
    MbCube GetBoundingBox();
    /// \ru Вернуть указатель на корневой сегмент сцены. \en Returns pointer to the scene root segment. \~
    SceneSegment* GetRootSegment() const;
    /// \ru Вернуть указатель на контейнер визуальных объектов. \en Returns pointer to container of visual effects. \~
    std::shared_ptr<RenderContainer> GetContainer();
    /// \ru Вернуть количество объектов в сцене. \en Returns scene object count. \~
    size_t GetCount() const;
    /// \ru Вернуть true, если сцена пуста, иначе false. \en True if scene is empty. \~
    bool IsEmpty() const;
    /// \ru Вернуть количество граней. \en Returns face count. \~
    size_t GetFaceCount() const;
    /// \ru Вернуть количество вершин. \en Returns vertex count. \~
    size_t GetVertexCount() const;
    /// \ru Вернуть количество материалов. \en Returns material count. \~
    size_t GetMaterialCount() const;
    /// \ru Вернуть набор материалов. \en Returns set of materials. \~
    std::set<Material*> GetMaterials() const;
    /// \ru Вернуть список объектов в сцене. \en Returns scene object list. \~
    std::list<RenderObject*> GetObjects() const;
    /// \ru Вернуть список видимых объектов в сцене. \en Returns scene visible object list. \~
    std::list<RenderObject*> GetVisibleObjects() const;


    /** \brief \ru Вернуть указатель на сегмент сцены.
                \en Returns pointer to scene segment. \~ 
        \param[in] id - \ru Идентификатор сегмента.
                        \en Segment identifier. \~
        \return \ru Указатель на сегмент сцены.
                \en Pointer to scene segment. \~
    */
    SceneSegment* GetSegment(NodeKey id) const;

    /// \ru Вернуть все сегменты сцены. \en Returns all scene segments. \~
    std::list<SceneSegment*> GetSegments() const;

    /// \ru Вернуть количество сегментов. \en Returns segment count. \~
    size_t GetSegmentCount() const;

    /** \brief \ru Проверить, существует ли в контейнере сегменты с заданным идентификатором.
                \en Checks if segments with specified identifier exist in container. \~ 
        \param[in] id - \ru Идентификатор сегмента.
                        \en Segment identifier. \~
        \return \ru True, если в контейнере есть сегмент с таким идентификатором, иначе - false.
                \en True if segment with such identifier exists. \~
    */
    bool IsExistSegment(NodeKey id) const;

    /// \ru Вернуть данные сегментов. \en Returns segment data. \~
    std::list<SceneSegmentData*> GetSegmentsData() const;

    /// \ru Вернуть список указателей на ссылки. \en Returns reference pointer list. \~
    std::list<SceneSegmentRef*> GetReferenceSegments() const;

    /// \ru Вернуть количество тел. \en Returns body count. \~
    size_t GetBodyCount() const;
    /// \ru Вернуть количество представлений. \en Returns representation count. \~
    size_t GetRepCount() const;
    /// \ru Вернуть Up вектор сцены. \en Returns scene up vector. \~
    MbVector3D GetUpVector() const;
    /// \ru Вернуть количество выбранных сегментов сцены. \en Returns count of selected scene segments. \~
    size_t GetSelectionSize() const;
    /// \ru Вернуть true, если указанный указатель на сегмент является выбранным, иначе false. \en True if the specified segment pointer is selected. \~
    bool IsSelected(const SceneSegment* pSegment) const;
    /// \ru Вернуть true, если указанный идентификатор сегмента является выбранным, иначе false. \en True if the specified segment identifier is selected. \~
    bool IsSelected(NodeKey selectionId) const;
    /// \ru Вернуть список указателей выбранных сегментов. \en Returns pointer list of selected segments. \~
    std::list<SceneSegment*> GetSelectedSegments() const;
    /// \ru Вернуть минимальный список указателей выбранных сегментов. \en Returns minimum pointer list of selected segments. \~
    std::list<SceneSegment*> GetMinimumSelectedSegments() const;
    /// \ru Отсоединить корневой сегмент от сцены. \en Detaches root segment from the scene. \~
    SceneSegment* DetachRootSegment();
    /// \ru Престроить дерево видимости \en NOT TRANSLATED \~
    void RebuildFrustumTree();
public:
    /** \brief \ru Заменить корневой сегмент сцены.
                \en Replaces scene root segment. \~ 
        \param[in] pSegment - \ru Новый корневой сегмент сцены.
                                \en New scene root segment. \~
    */
    void ReplaceRootSegment( SceneSegment* pSegment );

    /// \ru Обратить нормали сцены. \en Reverses scene normals. \~
    void ReverseNormal();

    /// \ru Очистить сцену. \en Clears scene. \~
    void Clear();

    /** \brief \ru Задать имя корневого сегмента.
                \en Sets root segment name. \~ 
        \param[in] name - \ru Имя сегмента.
                            \en Segment name. \~
    */
    void SetRootSegmentName( const String& name );

    /** \brief \ru Задать сцене Up вектор.
                \en Sets 'up' vector for the scene. \~ 
        \details \ru Задать сцене Up вектор.
                    \en Sets 'up' vector for the scene. \~
        \param[in] vect - \ru Задаваемый Up вектор.
                            \en Set 'up' vector. \~
    */
    void SetUpVector(const MbVector3D& vect);

    /** \brief \ru Задать viewport сцены.
                \en Sets scene viewport. \~ 
        \param[in] pViewport - \ru Указатель на viewport.
                                \en Pointer to viewport. \~
    */
    void SetViewport(Viewport* pViewport);

    /** \brief \ru Выбрать (выделить) заданный сегмент.
                \en Selects set segment. \~ 
        \param[in] pSegment - \ru Заданный сегмент.
                              \en Set segment. \~
    */
    void SelectSegment(const SceneSegment* pSegment);

    /** \brief \ru Выбрать (выделить) сегмент по идентификатору.
               \en Selects segment by identifier. \~ 
        \param[in] segmentId - \ru Идентификатор сегмента.
                               \en Segment identifier. \~
    */
    void SelectSegment(NodeKey segmentId);

    /** \brief \ru Отменить выбор сегмента.
                \en Unselects segment. \~ 
        \param[in] segmentId - \ru Идентификатор сегмента.
                               \en Segment identifier. \~
    */
    void UnselectSegment(NodeKey segmentId);

    /// \ru Выбрать все сегменты сцены. \en Selects all scene segments. \~
    void SelectAllSegments();

    /// \ru Отменить выбор всех сегментов. \en Unselects all scene segments. \~
    void UnselectAllSegments();

    /// \ru Выбрать (выделить) все видимые сегменты сцены. \en Selects all visible scene segments. \~
    void SelectVisibleViewObjects();

    /** \brief \ru Скрыть или показать выбранные (выделенные) сегменты.
               \en Hides or shows selected segments. \~ 
        \details \ru Скрыть или показать выбранные (выделенные) сегменты. \n
                     Состояние выделенных сегментов меняется на противоположное(show/hide).
                 \en Hides or shows selected segments. Reverses state of selected segments(show/hide). \~
    */
    void ReverseSelectedSegmentsState();

    /// \ru Показать выбранные (выделенные) сегменты. \en Shows selected segments. \~
    void ShowSelectedSegments();

    /// \ru Скрыть выбранные (выделенные) сегменты. \en Hides selected segments. \~
    void HideSelectedSegments();
public:
    /** \brief \ru Оператор присваивания.
                \en Assignment operator. \~ 
        \details \ru Оператор присваивания.
                    \en Assignment operator. \~
    */
    SceneContent& operator = (const SceneContent&);

    /** \brief \ru Оператор сравнения.
               \en Comparison operator. \~ 
        \details \ru Оператор сравнения.
                 \en Comparison operator. \~
        \param[in] other - \ru Сцена для сравнения.
                            \en Scene for comparison. \~
        \return \ru True, если содержание сравниваемых сцен не отличается, иначе - false.
                \en True if compared scene contents are identical. \~
    */
    bool operator == (const SceneContent& other) const;

public:
    /** \brief \ru Отрисовать все объекты сцены.
               \en Renders all scene objects. \~ 
        \param[in] groupId - \ru Идентификатор группы.
                             \en Group identifier. \~
        \param[in] renderingMode - \ru Режим отображения геометрии.
                                   \en Geometry rendering mode. \~
    */
    void Render(uint groupId, RenderMode renderingMode = rm_Shaded);
private:
    VSN_DECLARE_PRIVATE(SceneContent)
};

typedef std::shared_ptr<SceneContent> SceneContentPtr;

VSN_END_NAMESPACE

#endif /* __VSN_SCENECONTENT_H */
