////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Feature представляет базовый тип C3D Vision для создания 3D-Features.
             Базовый класс узла сцены, который может агрегировать экземплярами Essence как компонент.
         \en Feature presents the C3D Vision base type for creating 3D Features.
             It is the basic scene node class that can aggregate with Essence instances like a feature. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_FEATURE_H
#define __VSN_FEATURE_H

#include <vector>

#include "vsn_node.h"
#include "vsn_essence.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class FeaturePrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Базовый класс узла сцены, которые может агрегировать экземплярами Essence, как компонент.
            \en It is the basic scene node class that can aggregate with Essence instances like a component. \~
    \details  \ru Feature обеспечивает поведение объекта, который может быть назначен с помощью Essence объектов.
                  Подклассы Component часто объединяются в группы, которые передают полезное поведение через агрегирующие сущности (essences).
                  Например, если объект отрисовочный, Essence, скорее всего, будет содержать в себе матрицу трансформации,
                  полигональную модель и материал компонентов. \n.
              \en Feature provides behavior of the object being set with Essence objects.
                  Feature subclasses are often combined as groups that pass useful behavior throughout aggregating essences.
                  For example, if object is renderable, Essence will most probably contain transformation matrix, polygonal model and component material. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS Feature : public Node
{
    VSN_OBJECT(Feature)
    VSN_PROPERTY_READ(bShareable, IsShareable);
    VSN_PROPERTY_WRITE(bShareable, SetShareable);
    VSN_PROPERTY_NOTIFY(bShareable, ShareableModified)
public:
    /// \ru Конструктор. \en Constructor.
    Feature(Node* pParent = nullptr);
    /// \ru Конструктор с уникальным ключом и именем. \en Constructor with name and unique key.
    Feature(NodeKey key, const String& name);
    /// \ru Деструктор. \en Destructor.
    virtual ~Feature();
public:
    VSN_SLOT(Public, SetShareable, void SetShareable(bool bShareable))
    VSN_SIGNAL(Public, ShareableModified, void ShareableModified(bool bShareable), bShareable)
public:
    /// \ru Вернуть значение флага, при этом Feature может быть общим для нескольких сущностей (essences). \en Returns flag value. Component can be common for several essences.
    bool IsShareable() const;
    /// \ru Вернуть вектор, содержащий все сущности, ссылающиеся на этот Feature. \en Returns vector containing all essences with reference to the Feature.
    std::vector<Essence*> GetEssences() const;
protected:
    /// \ru Приватный конструктор для наследников. \en Private construсtor for inheritors.
    Feature(FeaturePrivate& dd, Node* parent = nullptr);
private:
    friend class Node;
    VSN_DECLARE_EX_PRIVATE(Feature)
};
VSN_END_NAMESPACE

#endif /* __VSN_FEATURE_H */
