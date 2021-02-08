////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс MouseEventHandler предоставляет уведомление о событии мыши.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MOUSEEVENTHANDLER_H
#define __VSN_MOUSEEVENTHANDLER_H

#include "vsn_feature.h"
//#include "vsn_mouseevent.h"

VSN_BEGIN_NAMESPACE

class MouseDevice;
class MouseEventObject;
class WheelEventObject;
class MouseEventHandlerPrivate;

//------------------------------------------------------------------------------
/** \brief \ru Класс MouseEventHandler предоставляет уведомление о событии мыши.
           \en NO TRANSLATION. \~
    \details  \ru Предоставляет средство уведомления о событиях мыши при подключении к экземпляру MouseDevice.
                  Надо помнить, что MouseEventHandler не должен использоваться совместно в нескольких задачах
                  (shared) это может привести к непредсказуемому результату. \n.
              \en NO TRANSLATION. \n \~
    \ingroup Vision_NONE
*/
// ---
class VSN_CLASS MouseEventHandler : public Feature
{
    VSN_OBJECT(MouseEventHandler)
    VSN_PROP_READ_WRITE_NOTIFY(sourceDevice, GetInteractionDevice, SetInteractionDevice, InteractionDeviceModified);
    VSN_PROP_READ_NOTIFY(includesMouse, IsIncludesMouse, IncludesMouseModified)
public:
    /// \ru Конструктор по умолчанию с родителем. \en NO TRANSLATION. \~
    explicit MouseEventHandler(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~MouseEventHandler();
public:
    /// \ru Вернуть указатель на текущее устройство - источник мыши экземпляра MouseEventHandler. \en NO TRANSLATION. \~
    MouseDevice* GetInteractionDevice() const;
    /** \brief \ru Вернуть признак использования в настоящее время мыши.
               \en NO TRANSLATION. \~
        \return \ru Вернуть ture, если в настоящее время MouseEventHandler содержит устройства мышь.
                \en NO TRANSLATION. \~
    */
    bool IsIncludesMouse() const;
public:
    /// \ru Установить устройство мыши для экземпляра MouseEventHandler. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetInteractionDevice, void SetInteractionDevice(MouseDevice* pMouseDevice))
public:
    VSN_SIGNAL(Public, InteractionDeviceModified, void InteractionDeviceModified(MouseDevice* pMouseDevice), pMouseDevice)
    VSN_SIGNAL(Public, IncludesMouseModified, void IncludesMouseModified(bool includesMouse), includesMouse)
public:
    /// \ru Сигнал выдается при нажатии кнопки мыши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, MouseDown, void MouseDown(MouseEventObject* pMouse), pMouse)
    /// \ru Сигнал выдается при изменении положения мыши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, MouseMove, void MouseMove(MouseEventObject* pMouse), pMouse)
    /// \ru Сигнал выдается при отпускании кнопки мыши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, MouseUp, void MouseUp(MouseEventObject* pMouse), pMouse)
    /// \ru Сигнал выдается при использовании колеса мыши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, MouseWheel, void MouseWheel(WheelEventObject* pWheel), pWheel)
    /// \ru Сигнал выдается при двойном нажатии кнопки мыши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, MouseDblClicked, void MouseDblClicked(MouseEventObject* pMouse), pMouse)
protected:
    void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
    void SetIncludesMouse(bool bIncludes);
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(MouseEventHandler);
    VSN_DISABLE_COPY(MouseEventHandler);
};

VSN_END_NAMESPACE
#endif // __VSN_MOUSEEVENTHANDLER_H
