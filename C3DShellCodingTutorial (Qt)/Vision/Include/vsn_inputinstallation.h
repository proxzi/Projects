////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс InputInstallation содержит указатель на объект источника события.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_INPUTINSTALLATION_H
#define __VSN_INPUTINSTALLATION_H

#include "vsn_feature.h"

VSN_BEGIN_NAMESPACE

class InputInstallationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс InputInstallation содержит указатель на объект источника события.
           \en NO TRANSLATION. \~
    \details \ru Компонент InputInstallation должен быть установлен как компонент корневой сущности сцены. 
                 Он хранит указатель на объект, который действует как источник входных событий, 
                 обрабатываемых различными входными классами. Например, Window может быть источником событий.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Input
*/
// ---
class InputInstallation : public Feature
{
    VSN_OBJECT(InputInstallation)
    VSN_PROP_READ_WRITE_NOTIFY(eventTranslator, GetEventTranslator, SetEventTranslator, EventTranslatorModified)
public:
    explicit InputInstallation(Node* parent = nullptr);
    ~InputInstallation();
public:
    Object* GetEventTranslator() const;
public:
    VSN_SLOT  (Public, SetEventTranslator, void SetEventTranslator(Object* pTranslator))
    VSN_SIGNAL(Public, EventTranslatorModified, void EventTranslatorModified(Object* pObject), pObject)
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
    void eventSourceDestroyed();
private:
    VSN_DECLARE_EX_PRIVATE(InputInstallation);
};

VSN_END_NAMESPACE

#endif // __VSN_INPUTINSTALLATION_H
