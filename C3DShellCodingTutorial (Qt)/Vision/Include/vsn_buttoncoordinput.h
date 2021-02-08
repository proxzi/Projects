////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Значение координат управляется кнопками.
           \en NOT TRANSLATED. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BUTTONCOORDINPUT_H
#define __VSN_BUTTONCOORDINPUT_H

#include "vsn_abscoordinatelistener.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class ButtonCoordInputPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Значение координат управляется кнопками.
           \en NO TRANSLATION. \~
    \ingroup Vision_Interaction
*/
// ---
class ButtonCoordInput : public AbsCoordinateListener
{
    VSN_OBJECT(ButtonCoordInput)
    VSN_PROP_READ_WRITE_NOTIFY(scale, GetScale, SetScale, OnScaleModified)
    VSN_PROP_READ_WRITE_NOTIFY(buttons, GetButtons, SetButtons, OnButtonsModified)
    VSN_PROP_READ_WRITE_NOTIFY(acceleration, GetAcceleration, SetAcceleration, OnAccelerationModified)
    VSN_PROP_READ_WRITE_NOTIFY(deceleration, GetDeceleration, SetDeceleration, OnDecelerationModified)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION. \~
    explicit ButtonCoordInput(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~ButtonCoordInput();
public:
    /// \ru Вернуть масштаб значение координат. \en NO TRANSLATION. \~
    float GetScale() const;
    /// \ru Вернуть коды кнопок, которые необходимы для управления координатой. \en NO TRANSLATION. \~
    std::vector<int> GetButtons() const;
    /// \ru Вернуть величину значение скорости по координате при удержании клавиши. \en NO TRANSLATION. \~
    float GetAcceleration() const;
    /// \ru Вернуть величину скорость с которой значение оси возвращается в нормальное состояние при отпускании кнопки. \en NO TRANSLATION. \~
    float GetDeceleration() const;
public: // slots group
    /// \ru Вернуть масштаб значение координат. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetScale, void SetScale(float scale))
    /// \ru Установить коды клавишь для управления координатой. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetButtons, void SetButtons(const std::vector<int>& buttons))
    /// \ru Установить величину значение скорости по координате при удержании клавиши. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetAcceleration, void SetAcceleration(float acceleration))
    /// \ru Установить скорость с которой значение оси возвращается в нормальное состояние при отпускании кнопки. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetDeceleration, void SetDeceleration(float deceleration))
public: // signals group
    /// \ru Сигнал об изменении масштаба. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnScaleModified, void OnScaleModified(float scale), scale)
    /// \ru Сигнал об изменении вектора ключей. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnButtonsModified, void OnButtonsModified(const std::vector<int>& buttons), buttons)
    /// \ru Сигнал об изменении скорости изменения при удержании клавиши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnAccelerationModified, void OnAccelerationModified(float acceleration), acceleration)
    /// \ru Сигнал об изменении скорости изменения при отпускании клавиши. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnDecelerationModified, void OnDecelerationModified(float deceleration), deceleration)
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(ButtonCoordInput)
    VSN_DISABLE_COPY(ButtonCoordInput)
};

VSN_END_NAMESPACE

#endif // __VSN_BUTTONCOORDINPUT_H
