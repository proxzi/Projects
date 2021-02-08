////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс SelectionManager управляет списком выбранных элементов.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __SELECTIONMANAGER_H
#define __SELECTIONMANAGER_H

#include "vsn_object.h"
#include "vsn_scenecontent.h"
#include "vsn_objectpickselection.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class SelectionManager;
//------------------------------------------------------------------------------
/** \brief  \ru Класс SelectionItem является определением интерфейса для выбранного элемента.
            \en NO TRANSLATION. \~
    \details \ru Это абстрактный базовый класс для элементов выбора, который содержится в списке класса SelectionManager. 
                 Определяет набор функций для SelectionManager и операторов для взаимодействия в момент выбора. Используйте 
                 этот класс в качестве базового класса, если вы хотите реализовать новые типы классов элементов выбора. 
                 Примечание: вы не можете создать экземпляр этого класса, т.к. он содержит чистые виртуальные функции, 
                 которые не имеют реализацию. \n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SelectionItem
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    SelectionItem(const NodeKey& key, SelectionManager* pManager);
    /// \ru Деструктор \en Destructor. \~
    virtual ~SelectionItem();
public:
    /// \ru Вернуть уникальный ключ \en NO TRANSLATION. \~
    virtual NodeKey GetNodeKey() const { return m_key; };
    /// \ru Вернуть тип объекта \en NO TRANSLATION. \~
    virtual ObjectType GetType() const { return m_type; }
    /// \ru Подсветить элемент \en NO TRANSLATION. \~
    virtual bool Highlight() = 0;
    /// \ru Снять подсветку элемента \en NO TRANSLATION. \~
    virtual bool UnHighlight() = 0;
    /// \ru Выбрать элемент \en NO TRANSLATION. \~
    virtual bool Select() = 0;
    /// \ru Снять выбор с элемента \en NO TRANSLATION. \~
    virtual bool UnSelect() = 0;
    /// \ru Вернуть true, когда два элемента выбора равны \en NO TRANSLATION. \~
    virtual bool IsEquals(const SelectionItem* pItem) const;
public:
    /// \ru Вернуть указатель сегмента графа \en NO TRANSLATION. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Вернуть указатель на математический объект. Может быть равен нулю. \en NO TRANSLATION. \~
    const MbItem* GetMathItem() const;

    SelectionManager* GetParent() const;
protected:
    ObjectType        m_type;
    NodeKey           m_key;
    SelectionManager* m_pManager;
    Filter              m_filter;
private:
    friend class SelectionManager;
    VSN_DISABLE_COPY(SelectionItem);
};

//------------------------------------------------------------------------------
/** \brief  \ru InstSelectionItem - элемент выбора, который имеет реализацию функций.
            \en NO TRANSLATION. \~
    \details \ru Эта реализация класса InstSelectionItem обрабатывает выбор сущностей (грани, ребра, вершины, ...). 
                 Реализация устанавливает цвет дополнительному материалу, чтобы распознать выбранные объекты. 
                 InstSelectionItem также имеет функции, которые выдают уникальные идентификаторы объектов сцены
                 и идентификаторы соответствия первичного представления, т.e. математического, если оно имеется. \n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS InstSelectionItem : public SelectionItem
{
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    InstSelectionItem(const NodeKey& key, SelectionManager* pManager, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Деструктор \en Destructor. \~
    virtual ~InstSelectionItem();
public:
    /// \ru Вернуть индекс тела в геометрии \en NO TRANSLATION. \~
    virtual int GetIndexBody() const;
    /// \ru Вернуть идентификатор примитива в геометрии \en NO TRANSLATION. \~
    virtual uint GetPrimitiveId() const;
    /// \ru Вернуть уникальный путь до математического объекта \en NO TRANSLATION. \~
    virtual MbPath GetMathPath() const;
    /// \ru Вернуть уникальный идентификатор математического объекта \en NO TRANSLATION. \~
    virtual uint32 GetMathPrimitive() const;

    /// \ru Подсветить элемент \en NO TRANSLATION. \~
    virtual bool Highlight() override;
    /// \ru Снять подсветку элемента \en NO TRANSLATION. \~
    virtual bool UnHighlight() override;
    /// \ru Выбрать элемент \en NO TRANSLATION. \~
    virtual bool Select() override;
    /// \ru Снять выбор с элемента \en NO TRANSLATION. \~
    virtual bool UnSelect() override;
    /// \ru Вернуть true, когда два элемента выбора равны \en NO TRANSLATION. \~
    virtual bool IsEquals(const SelectionItem* pItem) const;
public:
    /// \ru Вернуть указатель на математический примитив. Может быть равен нулю. \en NO TRANSLATION. \~
    const MbTopologyItem* GetPrimitiveItem() const;
protected:
    /// \ru Уникальные идентификаторы визуальных объектов \en NO TRANSLATION. \~
    int  m_currenyindexBody;   ///< \ru Индекс тела \en NO TRANSLATION. \~
    uint m_currentPrimitiveId; ///< \ru Уникальный идентификатор примитива \en NO TRANSLATION. \~
private:
    VSN_DISABLE_COPY(InstSelectionItem);
};


class ObjectPickSelection;
class SelectManagerPrivate;
class SelectionManagerPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс SelectionManager управляет списком выбранных элементов.
            \en NO TRANSLATION. \~
    \details \ru SelectionManager создает и сохраняет список геометрических примитивов или сегментов Vision. 
                 Класс имеет функции добавления и удаления отдельных и нескольких SelectionItem для списка. 
                 SelectionManager инкапсулирует определеную логику с проверками, выбран ли элемент. Все 
                 элементы, которые выбраны (т.е. находящиеся  в списке), будут выделены в сцене 
                 указанным цветом с помощью функции SetSelectionColor. Также имеется поддержка управления 
                 режимом выделения и стилем выделения. Примечание: SelectionManager может работать, 
                 как самостоятельно, так и в паре с инструментом ObjectPickSelection. С помощью функций 
                 SetMouseButtonsSelection и SetKeyboardButtonsMultiSelection пользователь может настроить
                 активность выбора объекта для режимов SingleSelection, MultiSelection. \n
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS SelectionManager : public Object
{
    VSN_OBJECT(SelectionManager);
    VSN_ENUM(SelectionManager::SelectionMode)
    VSN_PROP_READ_WRITE(dynamicHighlighting, IsDynamicHighlighting, SetDynamicHighlighting)
    VSN_PROP_READ_WRITE(selectionMode, GetSelectionMode, SetSelectionMode)
public:
    /// \ru Конструктор по умолчанию \en Default constructor. \~
    explicit SelectionManager();
    /// \ru Деструктор \en Destructor. \~
    virtual ~SelectionManager();
public:
    enum SelectionMode 
    {
        NoSelection,
        SingleSelection,
        MultiSelection,
    };
    enum ActivateMethod 
    { 
        Pressed = 0, 
        Released = 1, 
    };
public:
    /// \ru Вернуть указатель на содержание сцены \en NO TRANSLATION. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Установить указатель на содержание сцены \en NO TRANSLATION. \~
    void SetSceneContent(SceneContentPtr ptrSceneContent);
    /// \ru Вернуть указатель на инструмент поиска объектов \en NO TRANSLATION. \~
    ObjectPickSelection* GetObjectPickSelection() const;
    /// \ru Установить указатель на инструмент поиска объектов \en NO TRANSLATION. \~
    void SetObjectPickSelection(ObjectPickSelection* pPickSelection);

    /// \ru Вернуть способ активации выбора объектов с помощью мыши. \en NO TRANSLATION. \~
    ActivateMethod GetMouseActivateSelection() const;
    /// \ru Установить способ активации выбора объектов с помощью мыши. \en NO TRANSLATION. \~
    void SetMouseActivateSelection(ActivateMethod method);

    /** \brief \ru Вернуть кнопки мыши для выбора объектов.
               \en NO TRANSLATION. \~
        \return \ru Вернуть массив кодов клавиш.
                \en NO TRANSLATION. \~
    */
    std::vector<int> GetMouseButtonsSelection() const;
    /** \brief \ru Установить кнопки мыши для выбора объектов. Можно назначить кнопки:
                   mb_LButton; mb_MButton; mb_RButton.
               \en NO TRANSLATION. \~
        \param[in] vecKey - \ru Массив кодов клавиш.
                            \en TRANSLATION. \~
    */
    void SetMouseButtonsSelection(const std::vector<int>& vecKey);

    /** \brief \ru Вернуть кнопки клавиатуры для выбора объектов в режиме MultiSelection.
               \en NO TRANSLATION. \~
        \return \ru Вернуть массив кодов клавиш.
                \en NO TRANSLATION. \~
    */
    std::vector<int> GetKeyboardButtonsMultiSelection() const;
    /** \brief \ru Установить кнопки клавиатуры для выбора объектов в режиме MultiSelection. Можно назначить кнопки:
                   mb_Control; mb_Shift; mb_Alt.
               \en NO TRANSLATION. \~
        \param[in] vecKey - \ru Массив кодов клавиш.
                            \en TRANSLATION. \~
    */
    void SetKeyboardButtonsMultiSelection(const std::vector<int>& vecKey);

    /// \ru Вернуть true, если динамическое выделение включено или false, если оно выключено \en NO TRANSLATION. \~
    bool IsDynamicHighlighting() const;
    /// \ru Включить или отключить динамическое выделение для геометрии в сцене \en NO TRANSLATION. \~
    void SetDynamicHighlighting(bool state);

    /// \ru Вернуть режим выбора объектов в сцене \en NO TRANSLATION. \~
    SelectionManager::SelectionMode GetSelectionMode() const;
    /// \ru Установить режим выбора объектов в сцене \en NO TRANSLATION. \~
    void SetSelectionMode(SelectionManager::SelectionMode mode);
public:
    /// \ru Вернуть указатель на подсвеченный объект \en NO TRANSLATION. \~
    virtual SelectionItem* GetHighlightItem() const;
    /// \ru Вернуть список указателей SelectionItem \en NO TRANSLATION. \~
    virtual std::list<SelectionItem*> GetSelectionList() const;

    /// \ru Вернуть true, если элемент находится в списке выбранных \en NO TRANSLATION. \~
    virtual bool IsSelected(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Добавляет элемент в список выбора \en NO TRANSLATION. \~
    virtual void Select(const NodeKey& key);
    /// \ru Добавляет элемент в список выбора \en NO TRANSLATION. \~
    virtual void Select(const NodeKey& key, int currenyindexBody, uint currentPrimitiveId);
    /// \ru Удалить элемент из списка выбора \en NO TRANSLATION. \~
    virtual void Unselect(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Удаляет все элементы из списка, чтобы они больше не были выделены \en NO TRANSLATION. \~
    virtual void UnselectAll();

    /// \ru Подсветить элемент, имеющий уникальный ключ \en NO TRANSLATION. \~
    virtual void Highlight(const NodeKey& key, int currenyindexBody = -1, uint currentPrimitiveId = 0);
    /// \ru Снять подсветку с элемента \en NO TRANSLATION. \~
    virtual void Unhighlight();

    /// \ru Вернуть длину списка выбора \en NO TRANSLATION. \~
    int GetSelectedObjectCount() const;
    /// \ru Сбросить список выбора в нуль \en NO TRANSLATION. \~
    virtual void ResetSelect();
    /// \ru Сбросить подсвеченный элемент в нуль \en NO TRANSLATION. \~
    virtual void ResetHighlight();

    /// \ru Вернуть цвет для подсветки элемента \en NO TRANSLATION. \~
    virtual Color GetHighlightColor() const;
    /// \ru Установить цвет для подсветки элемента \en NO TRANSLATION. \~
    virtual void SetHighlightColor(const Color& clr);

    /// \ru Вернуть цвет для выбора элемента \en NO TRANSLATION. \~
    virtual Color GetSelectionColor() const;
    /// \ru Установить цвет для выбора элемента \en NO TRANSLATION. \~
    virtual void SetSelectionColor(const Color& clr);

    /// \ru Вернуть значение фильтра объектов (вызывает функцию у ObjectPickSelection, прописано для удобства). \en NO TRANSLATION. \~
    Filter GetFilterObject() const;

    /// \ru Вернуть true, если установлен флаг поиска сегмента \en NO TRANSLATION. \~
    virtual bool IsBodySelectionEnabled() const;
    /// \ru Установить флаг для поиска сегмента \en NO TRANSLATION. \~
    virtual void SetBodySelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска граней \en NO TRANSLATION. \~
    virtual bool IsFaceSelectionEnabled() const;
    /// \ru Установить флаг для поиска граней \en NO TRANSLATION. \~
    virtual void SetFaceSelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска ребер \en NO TRANSLATION. \~
    virtual bool IsEdgeSelectionEnabled() const;
    /// \ru Установить флаг для поиска ребер \en NO TRANSLATION. \~
    virtual void SetEdgeSelectionEnabled(bool bSelect);

    /// \ru Вернуть true, если установлен флаг поиска вершин \en NO TRANSLATION. \~
    virtual bool IsVertexSelectionEnabled() const;
    /// \ru Установить флаг для поиска вершин \en NO TRANSLATION. \~
    virtual void SetVertexSelectionEnabled(bool bSelect);
public:
    VSN_SIGNAL(Public, signalItemSelectModified, void signalItemSelectModified())
    VSN_SIGNAL(Public, signalItemsSelectModified, void signalItemsSelectModified())
    VSN_SIGNAL(Public, signalUnselectAll, void signalUnselectAll())
    VSN_SIGNAL(Public, signalStateModified, void signalStateModified())
protected:
    /// \ru При нажатии клавиши мыши сигнал становится активным. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotObjectPressed, virtual void slotObjectPressed(std::shared_ptr<PickSelectionEvent>))
    /// \ru При отпускании клавиши мыши сигнал становится активным. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotObjectReleased, virtual void slotObjectReleased(std::shared_ptr<PickSelectionEvent>))
    /// \ru При движении мыши сигнал становится активным. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotObjectHoverMove, virtual void slotObjectHoverMove(std::shared_ptr<PickSelectionEvent>))
    /// \ru При выборе объектов рамкой слот будет вызван. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotObjectPickArea, virtual void slotObjectPickArea(std::shared_ptr<PickAreaSelectionEvent>, bool))
private:
    VSN_DISABLE_COPY(SelectionManager);
    VSN_DECLARE_EX_PRIVATE(SelectionManager);
};

typedef std::shared_ptr<SelectionManager> SelectionManagerPtr;

VSN_END_NAMESPACE

#endif // __SELECTIONMANAGER_H
