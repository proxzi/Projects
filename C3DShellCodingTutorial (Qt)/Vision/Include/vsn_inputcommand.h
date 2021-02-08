////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru InputCommand хранит устройства ввода, а также код кнопок, которые в 
             дальнейшем будут использоватся, как события.
         \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_INPUTCOMMAND_H
#define __VSN_INPUTCOMMAND_H

#include "vsn_absinputcommand.h"

VSN_BEGIN_NAMESPACE

class AbsInputDevice;
class InputCommandPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru InputCommand хранит устройства ввода, а также код кнопок, которые в дальнейшем 
                будут использоватся, как события.
            \en NO TRANSLATION. \~
    \details \ru InputCommand взаимодействует с настоящим устройством и обрабатывают заказанные 
                 кнопки с последующей генерации действия. Кроме того действия могут быть вызваны
                 не одной кнопкой устройства, а несколькими. Например, кнопки от устройства мыши 
                 или клавиатуры.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Interaction
*/
// ---
class InputCommand : public AbsInputCommand
{
    VSN_OBJECT(InputCommand)
    VSN_PROPERTY_READ_WRITE_NOTIFY(pDevice, GetInteractionDevice, SetInteractionDevice, OnInteractionDeviceModified)
    VSN_PROPERTY_READ_WRITE_NOTIFY(buttons, GetButtons, SetButtons, OnButtonsModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit InputCommand(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    ~InputCommand();
public:
    /// \ru Вернуть указатель на текущее устройство взаимодействия входной команды. \en NO TRANSLATION. \~
    AbsInputDevice* GetInteractionDevice() const;
    /// \ru Содержит кнопки, которые могут вызвать эту команду. \en NO TRANSLATION. \~
    std::vector<int> GetButtons() const;
public: // slots group
    /// \ru Установить текущее устройства взаимодействия. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetInteractionDevice, void SetInteractionDevice(AbsInputDevice* pDevice))
    /// \ru Установить кнопки для запуска экземпляра команды ввода на кнопки. \en NO TRANSLATION. \~
    VSN_SLOT(Public, SetButtons, void SetButtons(const std::vector<int>& buttons))
public: // signals group
    /// \ru Этот сигнал будет генерирован при модификации устройства взоимодействия. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnInteractionDeviceModified, void OnInteractionDeviceModified(AbsInputDevice* pDevice), pDevice)
    /// \ru Этот сигнал будет генерирован при модификации состоянии кнопок связанных с этой командой. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnButtonsModified, void OnButtonsModified(const std::vector<int>& buttons), buttons)
private:
    VSN_DECLARE_EX_PRIVATE(InputCommand)
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
};

VSN_END_NAMESPACE

#endif // __VSN_INPUTCOMMAND_H
