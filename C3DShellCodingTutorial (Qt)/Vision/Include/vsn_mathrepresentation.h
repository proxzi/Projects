////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathRepresentation является вспомогательным классом и представляет 
             API для управления геометрией.
         \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHREPRESENTATION_H
#define __VSN_MATHREPRESENTATION_H

#include "vsn_mathgeometry.h"
#include "vsn_geometryrep.h"
#include "vsn_global.h"

class MbItem;

VSN_BEGIN_NAMESPACE
class MathRepresentationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathRepresentation является вспомогательным классом и представляет API для управления геометрией.
           \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~
  \details \ru MathRepresentation создает MathGeometry и содержит его указатель на протяжение всей своей жизни.
               MathRepresentation представляет ряд полезных функций для управления своей геометрией. \n.
           \en MathRepresentation class creates MathGeometry and contains its pointer during its whole existing.
               MathRepresentation class presents a set of useful functions to control its geometry. \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathRepresentation : public GeometryRep
{
    VSN_OBJECT(MathRepresentation);
    VSN_PROP_READ_WRITE_NOTIFY(visualSag, GetVisualSag, SetVisualSag, OnVisualSagModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    MathRepresentation(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~MathRepresentation();
public:
    /// \ru Получить тип построения сетки. \en Get a build type. \~
    MathGeometry::BuildType GetBuildType() const;
    /// \ru Задать тип построения сетки. \en Change a build type. \~
    void SetBuildType(MathGeometry::BuildType type);

    /// \ru Вернуть точность для вычисления шага при триангуляции поверхностей и граней. \en Returns accuracy to calculate step when triangulating surfaces and faces. \~
    double GetVisualSag() const;
    /// \ru Вернуть  указатель на математическое точное представление MbItem. \en Returns a pointer to math precise representation of MbItem. \~
    const MbItem* GetMathItem() const;
    /// \ru Установить указатель на математическое точное представление MbItem. \en Sets a pointer to math precise representation of MbItem. \~
    void SetMathItem(const MbItem* pItem, double sag = Math::visualSag);
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
public:
    /// \ru Установить точность для вычисления шага при триангуляции поверхностей и граней. \en Returns accuracy to calculate step when triangulating surfaces and faces. \~
    VSN_SLOT(Public, SetVisualSag, void SetVisualSag(double sag))
public:
    /// \ru Сигнал модификации шага расчета триангуляции. \en Signal about modifying step of triangulation computing. \~
    VSN_SIGNAL(Public, OnVisualSagModified, void OnVisualSagModified(double sag), sag)
    /// \ru Сигнал об окончании перестроения всей геометрии. \en Signal about the end of rebuilding the whole geometry. \~
    VSN_SIGNAL(Public, OnBuildCompleted, void OnBuildCompleted())
protected:
    /// \ru Эта функция вызывается, если произошли какие-либо изменения в сцене (для внутреннего использования). \en The function is called if the scene was modified, for inner using. \~
    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
private:
    VSN_DECLARE_EX_PRIVATE(MathRepresentation);
};
VSN_END_NAMESPACE

#endif /* __VSN_MATHREPRESENTATION_H */
