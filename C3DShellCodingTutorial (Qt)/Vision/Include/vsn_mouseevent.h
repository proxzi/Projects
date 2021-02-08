////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс MouseEventObject предоставляет параметры, которые описывает событие мыши.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MOUSEEVENT_H
#define __VSN_MOUSEEVENT_H

#include <memory>
#include "vsn_namespace.h"
#include "vsn_processevent.h"
#include "vsn_object.h"

VSN_BEGIN_NAMESPACE


//------------------------------------------------------------------------------
/** \brief \ru Класс MouseEventObject предоставляет параметры, которые описывает событие мыши.
           \en NO TRANSLATION. \~
    \details  \ru События мыши происходят, когда нажали на мышь, когда перемещаем мышь или 
                  отпускаем кнопку мыши. \n.
              \en NO TRANSLATION. \n \~
    \ingroup Vision_NONE
*/
// ---
class VSN_CLASS MouseEventObject : public Object
{
    VSN_OBJECT(MouseEventObject)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION. \~
    explicit MouseEventObject(const MouseEvent &e);
    /// \ru Деструктор. \en Destructor. \~
    ~MouseEventObject();
public:
    /// \ru Вернуть координату X. \en NO TRANSLATION. \~
    int GetX() const;
    /// \ru Вернуть координату Y. \en NO TRANSLATION. \~
    int GetY() const;
    /// \ru Вернуть координаты XY. \en NO TRANSLATION. \~
    IntPoint GetPoint() const;
    /// \ru True, если левая кнопка мыши нажата. \en True if the left mouse button is pressed.
    bool LButton() const;
    /// \ru True, если средняя кнопка мыши нажата. \en True if the middle mouse button is pressed.
    bool MButton() const;
    /// \ru True, если правая кнопка мыши нажата. \en True if the right mouse button is pressed.
    bool RButton() const;

    /// \ru True, если клавиша Ctrl сейчас нажата. \en True if Ctrl key is currently pressed.
    bool Control() const;
    /// \ru True, если клавиша Shift сейчас нажата. \en True if Shift key is currently pressed.
    bool Shift() const;
    /// \ru True, если клавиша Alt сейчас нажата. \en True if Alt key is currently pressed.
    bool Alt() const;
    /// \ru True, если левая клавиша Alt нажата. \en True if the left Alt key is pressed.
    bool LeftAlt() const;
    /// \ru True, если левая клавиша Ctrl нажата. \en True if the left Ctrl key is pressed.
    bool LeftControl() const;
    /// \ru True, если левая клавиша Shift нажата. \en True if the left Shift key is pressed.
    bool LeftShift() const;
    /// \ru True, если правая клавиша Alt нажата. \en True if the right Alt key is pressed.
    bool RightAlt() const;
    /// \ru True, если правая клавиша Ctrl нажата. \en True if the right Ctrl key is pressed.
    bool RightControl() const;
    /// \ru True, если правая клавиша Shift нажата. \en True if the right Shift key is pressed.
    bool RightShift() const;

    /// \ru Возвращает бит ProcessEvent флагов, таких как mb_LButton, для специальных событий клавиш Shift, Ctrl и левая, средняя и правая кнопки мыши. \en Returns ProcessEvent bit flags like mb_LButton for special events of Shift and Ctrl keys as well as left, middle and right mouse buttons.
    unsigned int GetFlags() const;

    /// \ru Вернуть тип события. \en NO TRANSLATION.
    ProcessEvent::EventType GetType() const;
    void SetApplied(bool bApplied) { m_event.SetApplied(bApplied); }
    bool IsApplied() const { return m_event.IsApplied(); }
private:
    MouseEvent m_event;
};

typedef std::shared_ptr<MouseEventObject> MouseEventObjectPtr;

//------------------------------------------------------------------------------
/** \brief \ru Класс WheelEventObject предоставляет параметры, описывающие событие колеса мыши.
           \en NO TRANSLATION. \~
    \details  \ru События колеса мыши происходят, когда колесико мыши вращается. \n.
              \en NO TRANSLATION. \n \~
    \ingroup Vision_NONE
*/
// ---
class VSN_CLASS WheelEventObject : public Object
{
    VSN_OBJECT(WheelEventObject)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION. \~
    explicit WheelEventObject(const WheelEvent& e);
    /// \ru Деструктор. \en Destructor. \~
    ~WheelEventObject();
public:
    /// \ru Вернуть координату X. \en NO TRANSLATION. \~
    int GetX() const;
    /// \ru Вернуть координату Y. \en NO TRANSLATION. \~
    int GetY() const;
    /// \ru Вернуть угол поворота колеса мыши. \en NO TRANSLATION. \~
    int GetDelta() const;
    /// \ru Вернуть тип события. \en NO TRANSLATION. \~
    ProcessEvent::EventType GetType() const;
private:
    WheelEvent m_event;
};

typedef std::shared_ptr<WheelEventObject> WheelEventObjectPtr;
VSN_END_NAMESPACE

#endif /* __VSN_MOUSEEVENT_H */
