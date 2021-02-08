///////////////////////////////////////////////////////////////////////////////
/**
    \file
        \brief \ru Базовый класс для изменений, которые могут быть отправлены и получены системой уведомлений об изменениях C3D Vision.
               \en The base class for all changes that can be sent and received by C3D Vision change notification system. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_SCENEMODIFICATION_H
#define __VSN_SCENEMODIFICATION_H

#include <memory>
#include "vsn_flags.h"
#include "vsn_nodekey.h"
#include "vsn_flags.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//----------------------------------------------------------------------------
//
/** \brief \ru Типы изменений, которые могут быть отправлены и получены системой уведомлений об изменениях C3D Vision.
           \en Modification types that can be sent and received by C3D Vision change notification system. \~
    \ingroup Vision_Modification
*/
// ---
enum ModificationFlag
{
    NodeCreated             = 1 << 0, ///> \ru Создать новый экземпляр подкласса Node. \en Creates new instance of Node subclass.
    NodeDeleted             = 1 << 1, ///> \ru Удалить экземпляр подкласса Node. \en Deletes instance of Node subclass.
    PropNAdded              = 1 << 2, ///> \ru Node был добавлен в сцену. \en Node is added to scene.
    PropNRemoved            = 1 << 3, ///> \ru Node был удален из сцены. \en Node is removed from scene.
    PropUpdated             = 1 << 4, ///> \ru Свойство Node было обновлено. \en Node property is updated.
    FeatureAdded            = 1 << 5, ///> \ru Компонент был добавлен в something. \en Feature is added to something.
    FeatureRemoved          = 1 << 6, ///> \ru Компонент был удален из something. \en Feature is removed from something.
    AllModifications        = 0xFFFF  ///> \ru Флаг может быть применен для всех модификаций. \en Flag can be used for all modifications.
};
VSN_DECLARE_FLAGS(ModificationFlags, ModificationFlag)

class SceneModificationPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Базовый класс для изменений, которые могут быть отправлены и получены системой уведомлений об изменениях Vision.
           \en The base class for changes that can be sent and received by Vision change notification system. \~
    \ingroup Vision_Modification
*/
// ---
class SceneModification
{
public:
    enum SupplyFlag
    {
        InternalNodes = 0x0001,
        ExternalNodes = 0x0002,
        SupplyAll     = InternalNodes | ExternalNodes,
        NoSupply
    };
    VSN_DECLARE_FLAGS(SupplyFlags, SupplyFlag)
    /// \ru Деструктор. \en Destructor.
    virtual ~SceneModification();
public:
    /// \ru Вернуть тип модификации сцены. \en Returns scene modification type.
    ModificationFlag GetType() const;
    /// \ru Установить флаги модификации. \en Sets modification flags.
    void SetSupplyFlags(SupplyFlags flags);
    /// \ru Вернуть флаги модификации. \en Returns modification flags.
    SupplyFlags GetSupplyFlags() const;
    /// \ru Вернуть ключ объекта модификации. \en Returns key of object being modified.
    NodeKey GetObjectKey() const;
protected:
    /// \ru Конструктор с типом и уникальным ключом. \en Constructor with type and unique key.
    explicit SceneModification(ModificationFlag type, NodeKey objectKey);
    /// \ru Конструктор с типом и уникальным ключом. \en Constructor with type and unique key.
    explicit SceneModification(SceneModificationPrivate &dd, ModificationFlag type, NodeKey objectKey);
protected:
    VSN_DECLARE_PRIVATE(SceneModification);
private:
    VSN_DISABLE_COPY(SceneModification)
};

VSN_END_NAMESPACE

#endif /* __VSN_SCENEMODIFICATION_H */
