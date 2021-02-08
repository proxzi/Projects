///////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс NCreatedModificationBasic является базовым классом для всех событий ModificationFlag::NodeCreated SceneModification.
           \en NCreatedModificationBasic class is the base class for all ModificationFlag::NodeCreated SceneModification events. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_NODEMODIFICATION_H
#define __VSN_NODEMODIFICATION_H

#include "vsn_scenemodification.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Node;
class MetaObject;
class NCreatedModificationBasicPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru Класс NCreatedModificationBasic является базовым классом для всех событий ModificationFlag::NodeCreated SceneModification.
             \en NCreatedModificationBasic class is the base class for all ModificationFlag::NodeCreated SceneModification events. \~
    \details \ru Класс NCreatedModificationBasic является базовым классом для всех событий SceneModification,
                 у которых есть GetType(), например, изменения NCreatedModification. Поэтому не нужно создавать экземпляр этого класса.
                 Обычно вы должны использовать один из своих подклассов, например NCreatedModification. Также есть возможность
                 классифицировать это, чтобы создать свои собственные типы обновления узлов для связи между подклассами Node. \n
             \en NCreatedModificationBasic class is the base class for all ModificationFlag::NodeCreated SceneModification events
                 that have GetType() function, for example, NCreatedModification modifications. So you do not need to create the instance of this class.
                 Usually, you should use one of the subclasses like NCreatedModification class. You also have an opportunity to classify it,
                 in order to create your own node update types for linking Node subclasses. \n \~
    \ingroup Vision_Modification
*/
// ---
class NCreatedModificationBasic : public SceneModification
{
public:
    /// \ru Конструктор с указателем узла. \en Constructor with node pointer.
    explicit NCreatedModificationBasic(const Node* pNode);
    /// \ru Деструктор. \en Destructor.
    ~NCreatedModificationBasic();
public:
    /// \ru Вернуть уникальный ключ родителя. \en Returns unique parent key.
    NodeKey GetParentKey() const;
    /// \ru Вернуть указатель на мета-объект. \en Returns pointer to Meta-Object.
    const MetaObject* GetMetaObject() const;
    /// \ru Вернуть признак доступа к узлу. \en Returns flag of node access.
    bool IsNodeEnabled() const;
protected:
    /// \ru Конструктор для внутреннего использования с указателем узла. \en Constructor with node pointer for internal use.
    NCreatedModificationBasic(NCreatedModificationBasicPrivate& dd, const Node* node);
private:
    VSN_DECLARE_EX_PRIVATE(NCreatedModificationBasic)
};

typedef std::shared_ptr<NCreatedModificationBasic> NCreatedModificationBasicPtr;

//------------------------------------------------------------------------------
/** \brief  \ru Класс NCreatedModification используется для уведомления изменения сцены.
            \en NCreatedModification class is used to notify on scene modifications. \~
    \ingroup Vision_Modification
*/
// ---
template<typename T>
class NCreatedModification : public NCreatedModificationBasic
{
public:
    explicit NCreatedModification(const Node* pNode)
        : NCreatedModificationBasic(pNode)
        , data()
    {
    }
public:
    T data;
};

template<typename T>
using NCreatedModificationPtr = std::shared_ptr<NCreatedModification<T>>;

struct NodeKeyTypePair;
class NDestroyedModificationPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Используется для уведомления при уничтожении узла.
            \en Used to notify about destroying a node. \~
    \ingroup Vision_Modification
*/
// ---
class NDestroyedModification : public SceneModification
{
public:
    /// \ru Конструктор с указателем узла и с парой типа и уникального ключя. \en Constructor with a pointer of node, type pair and a unique key.
    explicit NDestroyedModification(const Node* pNode, const std::vector<NodeKeyTypePair>& graphNodeKeysTypes);
    /// \ru Деструктор. \en Destructor.
    ~NDestroyedModification();
public:
    /// \ru Вернуть вектор пары типа и уникального ключя узла графа. \en Returns vector of type pair and unique key of graph node.
    std::vector<NodeKeyTypePair> GetGraphNodeKeysTypes() const;
private:
    VSN_DECLARE_EX_PRIVATE(NDestroyedModification);
};

VSN_END_NAMESPACE

#endif /*__VSN_NODEMODIFICATION_H */
