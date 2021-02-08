////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru AbsInputDevice - это базовый класс, используемый Vision для взаимодействия
               с произвольными устройствами ввода.
           \en AbsInputDevice class is a base class used by Vision to interact with arbitrary input devices. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSPHYSICALDEVICE_H
#define __VSN_ABSPHYSICALDEVICE_H

#include "vsn_node.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class CoordTuning;
class InputDevicesVision;
class AbsInputDevicePrivate;

//------------------------------------------------------------------------------
/** \brief  \ru Базовый класс, используемый Vision для взаимодействия с произвольными устройствами ввода.
            \en AbsInputDevice class is a base class used by Vision to interact with arbitrary input devices. \~
    \ingroup Vision_Input
*/
// ---
class VSN_CLASS AbsInputDevice : public Node
{
    VSN_OBJECT(AbsInputDevice);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit AbsInputDevice(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    ~AbsInputDevice();
public:
    /// \ru Вернуть количество координат, которое есть у этого устройства. \en Returns coordinate quantity this device has. \~
    virtual int GetCoordinateCount() const;
    /// \ru Вернуть количество кнопок, которые есть у этого устройства. \en Returns button quantity this device has. \~
    virtual int GetButtonCount() const;
    /// \ru Вернуть список имен координат устройства. \en Returns list of device coordinate names. \~
    virtual std::vector<String> GetCoordinateNames() const;
    /// \ru Вернуть список имен кнопок устройства. \en Returns list of device button names. \~
    virtual std::vector<String> GetButtonNames() const;

    /// \ru Вернуть целочисленный идентификатор координаты или - 1, если он не существует на этом устройстве. \en Returns integer coordinate identifier or -1 if it doesn't exist on this device. \~
    virtual int GetCoordinateId(const String& name) const;
    /// \ru Вернуть целочисленный идентификатор имени кнопки или -1, если он не существует на этом устройстве. \en Returns integer button name identifier or -1 if it doesn't exist on this device. \~
    virtual int GetButtonId(const String& name) const;
public:
    /// \ru Добавить координату CoordTuning к этому устройству. \en Adds CoordTuning coordinate to this device. \~
    void AddCoordinateSetting(CoordTuning* pCoordTuning);
    /// \ru Удалить функцию CoordTuning для этого устройства. \en Removes CoordTuning function for this device. \~
    void RemoveCoordinateSetting(CoordTuning* pCoordTuning);
    /// \ru Вернуть привязки CoordTuning связанные с этим устройством. \en Returns CoordTuning snaps related to this device. \~
    std::vector<CoordTuning*> GetCoordinateSettings() const;
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for inner using. \~
    AbsInputDevice(AbsInputDevicePrivate& dd, Node* pParent = nullptr);
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
protected:
    VSN_DECLARE_EX_PRIVATE(AbsInputDevice);
};

VSN_END_NAMESPACE


#endif // __VSN_ABSPHYSICALDEVICE_H

