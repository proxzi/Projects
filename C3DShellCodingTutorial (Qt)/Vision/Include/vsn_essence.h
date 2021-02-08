////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Essence - подкласс узла, который может агрегировать несколько экземпляров сущностей для определения их поведения.
           \en Essence is a node subclass aggregating several instances of features for behavior definition.  \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ESSENCE_H
#define __VSN_ESSENCE_H

#include "vsn_node.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Feature;
class EssencePrivate;
typedef std::vector<Feature*> FeatureVector;
//------------------------------------------------------------------------------
/** \brief   \ru Essence - подкласс узла, который может агрегировать несколько экземпляров сущностей для определения их поведения.
             \en Essence is a node subclass aggregating several instances of features for behavior definition. \~
    \details \ru Сам по себе класс Essence является пустой оберткой. Поведение объекта Essence определяется объектами Component,
                 на которые он ссылается. Каждая часть (feature) будет способна интерпретировать и обрабатывать Essence, зная из каких
                 сущностей он состоит. Например, feature может решать такие задачи, как трансформация объекта или в то же время может
                 осуществлять ввод с клавиатуры и т.д. \n
             \en Essence class is an empty wrapper in itself. The behavior of Essence object is defined by Component objects it refers to.
                 Each feature, knowing features Essence consists of, will be able to interpret and process that class. The feature can solve such
                 problems as object transformation and at the same time perform keyboard input and so on. \n \~
    \ingroup Vision_Nodes
*/
// ---
class VSN_CLASS Essence : public Node
{
    VSN_OBJECT(Essence);
public:
    /// \ru Конструктор по умолчанию с заданием узла родителя. \en Default constructor setting parent node.
    explicit Essence(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~Essence();
public:
    /// \ru Добавить новый указатель на Feature. \en Adds new pointer to Feature.
    void AddFeature(Feature* pFeature);
    /// \ru Удалить указанный указатель на Feature. \en Removes specified pointer to Feature.
    void RemoveFeature(Feature* pFeature);
    /// \ru Вернуть список экземпляров компонента, на которые ссылается Essence. \en Returns feature instance list to which Essence refers.
    FeatureVector GetFeatures() const;
    /// \ru Вернуть указатель на родительский экземпляр Essence. \en Returns pointer to Essence parent instance.
    Essence* GetParentEssence() const;
public:
//    VSN_SLOT(Public, ClearFeature, void ClearFeature())
protected:
    /// \ru Конструктор с заданием узла родителя и приватных данных. \en Constructor setting parent node and private data.
    explicit Essence(EssencePrivate& dd, Node* parent = nullptr);
private:
    NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(Essence);
};

typedef std::shared_ptr<Essence> EssencePtr;

VSN_END_NAMESPACE

#endif // __VSN_ANYTHING_H
