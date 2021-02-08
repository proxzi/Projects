////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRFINDSELECTOBJECT_H
#define __VSN_PRFINDSELECTOBJECT_H

#include "vsn_process.h"
#include "vsn_mouseevent.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class ObjectPickSelection;
class PrBasicFindSelectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrBasicFindSelect : public Process
{
    VSN_OBJECT(PrBasicFindSelect);
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrBasicFindSelect();
public:
    /// \ru Установить указатель на поиск объектов. \en NO TRANSLATION. \~
    virtual void SetPickSelection(ObjectPickSelection* pPickSelection);
protected:
    explicit PrBasicFindSelect(PrBasicFindSelectPrivate& dd, Node* parent);
private:
    VSN_DECLARE_EX_PRIVATE(PrBasicFindSelect);
};

class PrFindSelectObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrFindSelectObject : public PrBasicFindSelect
{
    VSN_OBJECT(PrFindSelectObject);
public:
    PrFindSelectObject(Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrFindSelectObject();
protected:
    /// \ru Слот принимает события от манипулятора мышь. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseDown, void slotMouseDown(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
    /// \ru Слот принимает события от манипулятора мышь. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseUp, void slotMouseUp(MouseEventObject* pMouse))
private:
    VSN_DECLARE_EX_PRIVATE(PrFindSelectObject);
};


class PrFindSelectAreaPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \details \ru NO TRANSLATION.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrFindSelectArea : public PrBasicFindSelect
{
    VSN_OBJECT(PrFindSelectArea);
public:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION. \~ 
    explicit PrFindSelectArea(Node* parent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrFindSelectArea();
public:
    // \ru Вернуть кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    std::vector<int> GetMouseButtonsActivate() const;
    // \ru Установить кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    void SetMouseButtonsActivate(const std::vector<int>& vecKey);

    /// \ru Вернуть цвет заполнения рамки. \en NO TRANSLATION. \~
    Color GetColorFillRect() const;
    /// \ru Установить цвет заполнения рамки. \en NO TRANSLATION. \~
    void SetColorFillRect(const Color& clr);

    /// \ru Вернуть цвет бордера рамки. \en NO TRANSLATION. \~
    Color GetColorRectBorder() const;
    /// \ru Установить цвет бордера рамки. \en NO TRANSLATION. \~
    void SetColorRectBorder(const Color& clr);

    /// \ru Есть ли объект под курсором мыши. \en NO TRANSLATION. \~
    bool IsObjectUnderCursor() const;

    /// \ru Вернуть расстояние для старта рисования рамки. \en NO TRANSLATION. \~
    int GetStartDragDistance() const;
    /// \ru Установить расстояние для старта рисования рамки. \en NO TRANSLATION. \~
    void SetStartDragDistance(int dis);
public:
    /// \ru Установить указатель на сцену. \en NO TRANSLATION. \~
    virtual void SetGraphicsScene(GraphicsScene* pGraphicsScene);
public:
    VSN_SIGNAL(Public, signalStartArea,  void signalStartArea(bool& bAllow), bAllow)
    VSN_SIGNAL(Public, signalFinishArea, void signalFinishArea())
public:
    /// \ru Слот для активизации и инициализации данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Public, slotActiveModified, void slotActiveModified(bool bIsActive))
protected:
    /// \ru Слот принимает события от манипулятора мышь. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
private:
    VSN_DECLARE_EX_PRIVATE(PrFindSelectArea);
};
VSN_END_NAMESPACE

#endif /* __VSN_PRFINDSELECTOBJECT_H */
