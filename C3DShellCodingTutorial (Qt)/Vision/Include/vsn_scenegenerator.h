////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс SceneGenerator представляет фабрику представлений геометрических
             объектов, а также генерацию готовой сцены для последующей отрисовки.
         \en SceneGenerator class presents a factory of geometric object representations and
             also generates a prepared scene for next rendering. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SCENEGENERATOR_H
#define __VSN_SCENEGENERATOR_H

#include "model.h"
#include "model_item.h"
#include "vsn_object.h"
#include "vsn_sphererep.h"
#include "vsn_conerep.h"
#include "vsn_boxrep.h"
#include "vsn_cylinderrep.h"
#include "vsn_rectanglerep.h"
#include "vsn_lineardimensionrep.h"
#include "vsn_angledimensionrep.h"
#include "vsn_commentrep.h"
#include "vsn_diameterdimensionrep.h"
#include "vsn_radialdimensionrep.h"
#include "vsn_mathrepresentation.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class ProgressBuildPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс ProgressBuild служит для определения конца и шага генерации полигональной модели.
           \en ProgressBuild class is necessary to define the end and step of generating polygonal model. \~
    \details \ru Класс ProgressBuild имеет ряд функций, а также сигналов, с помощью которых пользователь 
                 может узнать состояние генерации тел и примитивов, а также ее окончание. Важно знать, что
                 ProgressBuild применяется только при генерации математических объектов. \n.
             \en ProgressBuild class has a set of functions and also signals that user
                 can use to know a state of solid body and primitive generation and also generation end.
                 It's important to know ProgressBuild class is applied only when generating math objects. \n \~
    \ingroup Vision_Node
*/
// ---
class VSN_CLASS ProgressBuild : public Object
{
    VSN_OBJECT(ProgressBuild);
    VSN_PROP_READ(minimum, GetMinimum);
    VSN_PROP_READ(maximum, GetMaximum);
    VSN_PROP_READ_NOTIFY(value, GetValue, ValueModified);
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit ProgressBuild();
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~ProgressBuild();
public:
    /// \ru Является ли процесс построения запущенным. \en NO TRANSLATION. \~
    bool IsRunning() const;
    /// \ru Является ли процесс построения приостановленным. \en NO TRANSLATION. \~
    bool IsCancel() const;
    /// \ru Вернуть текущее значение перестраиваемой геометрии. \en Returns a current value of rebuilding geometry. \~
    int GetValue() const;
    /// \ru Вернуть минимальное значение перестраиваемой геометрии. \en Returns the minimum value of rebuilding geometry. \~
    int GetMinimum() const;
    /// \ru Вернуть максимальное значение количества перестраиваемой геометрии. \en Returns the maximum value of rebuilding geometry quantity. \~
    int GetMaximum() const;
public:
    /// \ru Прервать процесс построения. \en NO TRANSLATION. \~
    VSN_SLOT(Public, CancelBuild, void CancelBuild())
public:
    /// \ru Сигнал об окончании перестроения конкретной геометрии. \en Signal about the end of rebuilding a particular geometry. \~
    VSN_SIGNAL(Public, ValueModified, void ValueModified(int val), val)
    /// \ru Сигнал об окончании перестроения всей геометрии. \en Signal about the end of rebuilding the whole geometry. \~
    VSN_SIGNAL(Public, BuildAllCompleted, void BuildAllCompleted())
private:
    VSN_DISABLE_COPY(ProgressBuild)
    VSN_DECLARE_EX_PRIVATE(ProgressBuild)
    friend class SceneGenerator;
    friend class SceneGeneratorPrivate;
};

class SceneSegment;
class SceneGeneratorPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс SceneGenerator представляет фабрику представлений геометрических
               объектов, а также генерацию готовой сцены для последующей отрисовки.
           \en SceneGenerator class presents a space of geometric object representations and
               also generates a prepared scene for next rendering. \~
  \details \ru SceneGenerator имеет две группы функций. Первая группа работает непосредственно с математическими
               объектами и тем самым обеспечивает глубокую интеграцию с математическим ядром. Вторая группа
               генерирует представления простых объектов, таких как куб, цилиндр, сфера и др., т.е. где 
               полигональная модель рассчитывается не с помощью математического ядра, а самими визуальными
               объектами. \n.
           \en SceneGenerator class has two function groups. The first one directly works with math objects
               providing deep integration with math kernel. The second one generates representations
               of such simple objects as cube, cylinder, sphere, etc., i.e. polygonal model is computed
               with not a math kernel, but visual objects themselves. \n \~
    \ingroup Vision_Node
*/
// ---
class VSN_CLASS SceneGenerator : public Object
{
    VSN_OBJECT(SceneGenerator);
public:
    /// \ru Получить экземпляр фабрики. \en Returns factory instance. \~
    static SceneGenerator* Instance();
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~SceneGenerator();
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit SceneGenerator();
public: /// \ru Группа функций, работающая с математическим ядром. \en Function groups working with a math kernel. \~
    /// \ru Создать прогресс построения геометрии. \en Creates progress of rebuilding geometry. \~
    ProgressBuild* CreateProgressBuild();
    /// \ru Загрузить модель из памяти. \en Loads model from memory. \~
    MbModel* LoadModel(const char* pMemory, size_t length);
    /// \ru Создать граф сцены из MbModel. \en Creates scene graph from MbModel. \~
    SceneSegment* CreateSceneSegment(const MbModel* pModel, SceneSegment* pParent = nullptr);
    /// \ru Получить графическое представление с MbItem. \en Returns graphic representation with MbItem. \~
    GeometryRep* CreateMathRep(const MbItem* pItem, SceneSegment* pParent = nullptr, MathGeometry::BuildType buildType = MathGeometry::Threaded,  double sag = Math::visualSag);
public:
    /// \ru Сигнал об окончании перестроения конкретной геометрии. \en Signal about the end of rebuilding a particular geometry. \~
    VSN_SIGNAL(Public, CreateSegment, void CreateSegment(SceneSegment* newSeg, SceneSegment* parentSeg), newSeg, parentSeg)

public: /// \ru Группа функций, генерирущая простые представления вручную. \en Function groups generating simple representations manually. \~
    /// \ru Создать представление сферы. \en Creates sphere representation. \~
    SphereRep* CreateSphere(double radius, Node* pParent = nullptr) const;
    /// \ru Создать представление конуса. \en Creates cone representation. \~
    ConeRep* CreateCone(double radius, double height,  Node* pParent = nullptr) const;
    /// \ru Создать представление цилиндра. \en Creates cylinder representation. \~
    CylinderRep* CreateCylinder(double radius, double height, Node* pParent = nullptr) const;
    /// \ru Создать представление параллелепипеда. \en Creates parallelepiped representation. \~
    BoxRep* CreateBox(double width, double length, double height, Node* pParent = nullptr) const;
    /// \ru Создать представление прямоугольника. \en Creates rectangle representation. \~
    RectangleRep* CreateRectangle(double width, double height, Node* pParent = nullptr) const;
    /// \ru Создать линейный размер. \en Creates linear size. \~
    LinearDimensionRep* CreateLinearDimension(Node* pParent = nullptr) const;
    /// \ru Создать угловой размер. \en Creates angle size. \~
    AngleDimensionRep* CreateAngleDimension(Node* pParent = nullptr) const;
    /// \ru Создать комментарий. \en Creates Comment. \~
    CommentRep * CreateComment(const std::wstring & text, Node* pParent = nullptr) const;
    /// \ru Создать диаметральный размер. \en Creates diameter. \~
    DiameterDimensionRep* CreateDiameterDimension(Node* pParent = nullptr) const;
    /// \ru Создать радиальный размер. \en Creates radius. \~
    RadialDimensionRep*  CreateRadialDimension(Node* pParent = nullptr) const;
    /// \ru Создать оси системы координат. \en Create axes of the coordinate system.
    SceneSegment * CreateTriadGeometry( SceneSegment * parent = nullptr) const;
private:
    VSN_DISABLE_COPY(SceneGenerator)
    VSN_DECLARE_PRIVATE(SceneGenerator)
    friend class MathRepresentation;
};
VSN_END_NAMESPACE

#endif /* __VSN_SCENEGENERATOR_H */
