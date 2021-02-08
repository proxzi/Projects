////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru AbsCoordinateListener абстрактный базовый класс, который принимает 
               события от любого виртуального устройства.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSCOORDINATELISTENER_H
#define __VSN_ABSCOORDINATELISTENER_H

#include "vsn_node.h"

VSN_BEGIN_NAMESPACE

class AbsInputDevice;
class AbsCoordinateListenerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru AbsCoordinateListener абстрактный базовый класс, который принимает 
               события от любого виртуального устройства.
           \en NO TRANSLATION. \~
    \ingroup Vision_Interaction
*/
// ---
class AbsCoordinateListener : public Node
{
    VSN_OBJECT(AbsCoordinateListener)
    VSN_PROP_READ_WRITE_NOTIFY(pInteractionDevice, GetInteractionDevice, SetInteractionDevice, OnInteractionDeviceModified)
public:
    /// \ru Деструктор. \en Destructor. \~
    ~AbsCoordinateListener();
public:
    /// \ru Вернуть указатель на источник взаимодействия. \en NO TRANSLATION. \~
    AbsInputDevice* GetInteractionDevice() const;
public: // slots group
    /// \ru Установить источник взаимодействия. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetInteractionDevice, void SetInteractionDevice(AbsInputDevice* pInteractionDevice))
public: // signals group
    /// \ru Сигнал об изменении источника взаимодействия. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnInteractionDeviceModified, void OnInteractionDeviceModified(AbsInputDevice* pInteractionDevice), pInteractionDevice)
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION. \~
    AbsCoordinateListener(AbsCoordinateListenerPrivate& dd, Node* pParent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(AbsCoordinateListener);
    VSN_DISABLE_COPY(AbsCoordinateListener);
};

VSN_END_NAMESPACE

#endif // __VSN_ABSCOORDINATELISTENER_H
