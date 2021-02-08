////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathGeometry представляет геометрию для последующей отрисовки, 
             которая была сгенерирована с помощью математического представления.
         \en Class MathGeometry presents geometry for next rendering that was
             generated with math representation. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_MATHGEOMETRY_H
#define __VSN_MATHGEOMETRY_H

#include <model_item.h>
#include <topology_item.h>
#include "vsn_meshgeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class MathGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс MathGeometry представляет геометрию для последующей отрисовки, которая была сгенерирована с помощью математического представления.
           \en Class MathGeometry presents geometry for next rendering that was generated with math representation. \~
    \details \ru Класс MathGeometry принимает указатель на математическое представление MbItem для последующей генерации визуального представления.
                 MbItem может представлять собой такие объекты, как MbSolid, MbMesh, MbСontour, ... которые способны генерировать самостоятельно
                 полигональную модель. Класс MathGeometry представляет ряд полезных функций. Для вычисления шага триангуляции поверхностей и граней,
                 вы можете воспользоваться функцией SetVisualSag и вызвать перегенерацию триангуляции в реальном времени, что влияет на качество 
                 отображения геометрии. С помощью функций QueryMathByGeometry и QueryGeomByMath вы можете получить идентификацию примитивов из
                 визуального представления в математическое и наоборот. Необходимо знать, что идентификаторы математического представления являются
                 хеш'ом реальных идентификаторов и пути к этим примитивам. \n.
             \en MathGeometry class takes a pointer to MbItem math representation for the next generating visual representation.
                 MbItem can presents such objects as MbSolid, MbMesh, MbСontour, etc that are able to generate a polygonal model independently.
                 MathGeometry class presents a set of useful functions. You can use SetVisualSag function to compute a triangulation step of planes and faces
                 and you can call regeneration of triangulation in real time, what influences quality of geometry display. You can get primitive identification
                 from visual representation to math one and vice versa using QueryMathByGeometry and QueryGeomByMath functions. It's necessary to know that identifiers
                 of math representation are hash of real identifiers and paths to these primitives. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS MathGeometry : public MeshGeometry
{
    VSN_OBJECT(MathGeometry);
    VSN_PROP_READ_WRITE_NOTIFY(visualSag, GetVisualSag, SetVisualSag, OnVisualSagModified);
public:
    enum BuildType { Synchronous, Threaded };
    /// \ru Структура данных при запросе индентификаторов соответствия. \en Structure of data when requesting compatibility identificators. \~
    struct InfoPrimitive
    {
        InfoPrimitive() : m_type(ObjectType::None) , m_id(-1) {}
        InfoPrimitive(ObjectType type, uint id) : m_type(type) , m_id(id) {}
        ObjectType m_type; ///< \ru Тип примитива. \en Primitive type. \~
        uint32     m_id;   ///< \ru Идентификатор примитива. \en Primitive identifier. \~
    };
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    MathGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~MathGeometry();
public: 
    /// \ru Получить тип построения сетки. \en Returns mesh building type. \~
    BuildType GetBuildType() const;
    /// \ru Задать тип построения сетки. \en Sets mesh building type. \~
    void SetBuildType(BuildType type);
    /// \ru Вернуть mаксимально допустимый прогиб кривой или поверхности в соседних точках на расстоянии шага. \en Returns the maximum permissible sag of a curve or surface at adjacent points a step away. \~
    double GetVisualSag() const;
    /// \ru Вернуть указатель на математическое точное представление MbItem. \en Returns a pointer to math precise representation of MbItem. \~
    const MbItem* GetMathItem() const;
    /// \ru Установить указатель на математическое точное представление MbItem. \en Sets a pointer to math precise representation of MbItem. \~
    void SetMathItem(const MbItem* pItem, double sag = Math::visualSag);
    /// \ru Перестроить геометрию по измененному MbItem. \en Rebuild geometry by modified MbItem. \~
    void RebuildGeometry();
    /// \ru Очистить в этой геометрии все примитивы. \en Clears all primitives of this geometry. \~
    void Clear() override;

    /// \ru Вернуть математический идентификатор примитива по уникальному идентификатору этой геометрии. \en Returns a math identifier of primitive by the unique identifier of this geometry. \~
    InfoPrimitive QueryMathByGeometry(uint geomId) const;
    /// \ru Вернуть геометрический идентификатор примитива по уникальному идентификатору математического примитива. \en Returns a geometric identifier of primitive by the unique identifier of math primitive. \~
    InfoPrimitive QueryGeomByMath(uint mathId) const;

    /// \ru Вернуть указатель на математический примитив по уникальному идентификатору математического примитива. \en NO TRANSLATION. \~
    const MbTopologyItem* QueryPrimitiveItemByMathId(uint mathId) const;
public:
    /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
    virtual const MbCube & GetBoundingBox() override;
    /// \ru Обновить геометрию по новым данным для внутреннего использования. \en Updates geometry with new data for inner using. \~
    virtual void UpdateGeometry() override;
    /// \ru True, если буфер вершин используется. \en True if vertex buffer is used. \~
    virtual void SetUseVertexBufferObjects(bool usage) override;
public:
    /// \ru Установить максимально допустимый прогиб кривой или поверхности в соседних точках на расстоянии шага.
    /// \en Sets the maximum permissible sag of a curve or surface at adjacent points a step away. \~
    VSN_SLOT(Public, SetVisualSag, void SetVisualSag(double sag))
public:
    /// \ru Сигнал модификации шага расчета триангуляции. \en Signal about modifying step of triangulation computing. \~
    VSN_SIGNAL(Public, OnVisualSagModified, void OnVisualSagModified(double sag), sag)
    /// \ru Сигнал об окончании перестроения всей геометрии. \en Signal about the end of rebuilding the whole geometry. \~
    VSN_SIGNAL(Public, OnBuildCompleted, void OnBuildCompleted())
private:
    /// \ru Перестроить тело. \en Rebuilds a solid body. \~
    void slotDataModified(const std::vector<float>& bytes);
    /// \ru Отрисовка тела. \en Renders a solid body. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(MathGeometry);
    VSN_DECLARE_EX_PRIVATE(MathGeometry);
    friend class MathGeometryBuilder;
};
VSN_END_NAMESPACE

#endif /* __VSN_MATHGEOMETRY_H */
