////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс Command cвязывает набор AbsInputCommand, запускающий одно и то же событие.
         \en Command class links AbsInputCommand set running the same event. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_COMMAND_H
#define __VSN_COMMAND_H

#include "vsn_node.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class CommandPrivate;
class AbsInputCommand;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс Command cвязывает набор AbsInputCommand, запускающий одно и то же событие.
           \en Command class links AbsInputCommand set running the same event. \~
    \ingroup Vision_Interaction
*/
// ---
class VSN_CLASS Command : public Node
{
    VSN_OBJECT(Command)
    VSN_PROP_READ_NOTIFY(active, IsActive, OnActiveModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit Command(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~Command();
public:
    /// \ru Вернуть признак активности команды. \en Returns a flag of command activity. \~
    bool IsActive() const;
    /// \ru Вернуть список инициаторов ввода команды, которые могут вызвать действия. \en Returns a list of command input initiators that can call actions. \~
    std::vector<AbsInputCommand*> GetInputs() const;
    /// \ru Добавить инициаторов команды AbsInputCommand в список инициаторов, которые могут вызвать это действие. \en Adds AbsInputCommand command initiators to initiator list that can call this action. \~
    void AddInput(AbsInputCommand* pInput);
    /// \ru Удалить инициаторов команды AbsInputCommand из списка инициаторов, которые могут вызвать это действие. \en Removes AbsInputCommand command initiators from initiator list that can call this action. \~
    void RemoveInput(AbsInputCommand* pInput);
public: // signals group
    /// \ru Этот сигнал будет генерирован при модификации устройства взаимодействия. \en The signal will be generated when modifying interaction device. \~
    VSN_SIGNAL(Public, OnActiveModified, void OnActiveModified(bool bIsActive), bIsActive)
protected:
    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(Command)
    VSN_DISABLE_COPY(Command)
};


VSN_END_NAMESPACE

#endif // __VSN_COMMAND_H
