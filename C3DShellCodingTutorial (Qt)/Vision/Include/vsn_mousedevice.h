////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс MouseDevice отправляет события мыши на прикрепленные объекты MouseEventHandler.
         \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MOUSEDEVICE_H
#define __VSN_MOUSEDEVICE_H

#include "vsn_absinputdevice.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class MouseDevicePrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс MouseDevice отправляет события мыши на прикрепленные объекты MouseEventHandler.
            \en NOT TRANSLATED. \~
    \details \ru MouseDevice перенаправляет события мыши с настоящего устройства типа мышь на oбъекты-
                 обработчики MouseEventHandler. Чувствительностью мыши можно управлять с помощью функций
                 MouseDevice::SetSensitiveness, которая определяет скорость изменения логических координат 
                 мыши при ее реальном перемещении. \n
             \en NO TRANSLATION. \n \~

    \ingroup Vision_Input
*/
// ---
class VSN_CLASS MouseDevice : public AbsInputDevice
{
    VSN_OBJECT(MouseDevice)
    VSN_ENUM(Coordinate)
    VSN_PROP_READ_WRITE_NOTIFY(sensitiveness, GetSensitiveness, SetSensitiveness, OnSensitivenessModified)
public:
    /// \ru Координаты мыши. \en NOT TRANSLATED.
    enum Coordinate { X, Y };
public:
    /// \ru Конструктор по умолчанию с родителем. \en NOT TRANSLATED.
    explicit MouseDevice(Node* parent = nullptr);
    /// \ru Деструктор. \en NOT TRANSLATED.
    virtual ~MouseDevice();
public:
    /// \ru Вернуть количество координат, которые имеет это устройство. \en NOT TRANSLATED.
    virtual int GetCoordinateCount() const final;
    /// \ru Вернуть количество кнопок, которые есть у этого устройства. \en NOT TRANSLATED.
    virtual int GetButtonCount() const final;

    /// \ru Вернуть список имен координат устройства. \en NOT TRANSLATED.
    virtual std::vector<String> GetCoordinateNames() const final;
    /// \ru Вернуть список имен кнопок устройства. \en NOT TRANSLATED.
    virtual std::vector<String> GetButtonNames() const final;
    /// \ru Вернуть целочисленный идентификатор оси или - 1, если он не существует на этом устройстве. \en NOT TRANSLATED.
    virtual int GetCoordinateId(const String& name) const final;
    /// \ru Вернуть чувствительность мышиного устройства. \en NOT TRANSLATED.
    float GetSensitiveness() const;
public: // slots group
    /// \ru Установить чувствительность мышиного устройства. \en NOT TRANSLATED.
    VSN_SLOT  (Public, SetSensitiveness, void SetSensitiveness(float sensitiveness))
public: // signals group
    /// \ru Сигнал изменения чувствительность мышиного устройства. \en NOT TRANSLATED.
    VSN_SIGNAL(Public, OnSensitivenessModified, void OnSensitivenessModified(float sensitiveness), sensitiveness)
protected:
    void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(MouseDevice);
    VSN_DISABLE_COPY(MouseDevice);
};

VSN_END_NAMESPACE


#endif // __VSN_MOUSEDEVICE_H
