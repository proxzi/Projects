////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WIDGET3DBASIC_H
#define __VSN_WIDGET3DBASIC_H

#include "vsn_essence.h"
#include "vsn_geometryrep.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

/// \ru NOT TRANSLATED. \en NOT TRANSLATED.
enum ItemDataRole
{
    dt_Type = 0,
    dt_NodeKey = 1,
    dt_Color = 2,
    // Reserved
    dr_User = 0x0100
};

//----------------------------------------------------------------------------
//
/** \brief \ru Класс AbstractRenderModel предоставляет абстрактный интерфейс для классов моделей виджитов.
           \en NOT TRANSLATED. \~
    \details \ru NOT TRANSLATED.
             \en NOT TRANSLATED. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS AbstractRenderModel : public Object
{
    VSN_OBJECT(AbstractRenderModel);
public:
    /// \ru Деструктор. \en Destructor.
    virtual ~AbstractRenderModel();
public:
    /// \ru Построение модели. \en NOT TRANSLATED.
    virtual void BuildModel() = 0;
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit AbstractRenderModel(Object* pParent = nullptr);
private:
//    VSN_DECLARE_EX_PRIVATE(AbstractRenderModel);
    VSN_DISABLE_COPY(AbstractRenderModel);
};


class RenderObject;
class Widget3DBasicPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \details \ru NOT TRANSLATED. 
             \en NOT TRANSLATED. \n \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS Widget3DBasic : public Essence
{
    VSN_OBJECT(Widget3DBasic);
public:
    /// \ru Деструктор. \en Destructor.
    virtual ~Widget3DBasic();
public:
    /// \ru Вернуть признак видимости Widget. \en NOT TRANSLATED.
    bool IsVisible() const;
    /// \ru Установить видимость Widget. \en NOT TRANSLATED.
    void SetVisible(bool bVisible);

    /// \ru Вернуть указатель на Viewport. \en NOT TRANSLATED.
    Viewport* GetViewport() const;
    /// \ru Установить Viewport. \en NOT TRANSLATED.
    void SetViewport(Viewport* pViewport);

    /// \ru Вернуть указатель на модель предсавления виджета. \en NOT TRANSLATED.
    AbstractRenderModel* GetModel() const;
    /// \ru Установить модель для представления виджета. \en NOT TRANSLATED.
    virtual void SetModel(AbstractRenderModel* model);

    /// \ru Добавить геометрическое представление. \en NOT TRANSLATED.
    void AddObject(RenderObject* object);
    /// \ru Удалить все объекты представления. Объекты будут разрушены. \en NOT TRANSLATED.
    void RemoveAllObjects();
protected:
    /// \ru Конструктор с заданием родителя и приватных данных. \en NOT TRANSLATED.
    explicit Widget3DBasic(Widget3DBasicPrivate& dd, Node* pParent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(Widget3DBasic);
    VSN_DISABLE_COPY(Widget3DBasic);
};

VSN_END_NAMESPACE

#endif /* __VSN_WIDGET3DBASIC_H */
