////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Абстрактный базовый класс для отрисовочной геометрии.
       \en Abstract base class for rendering geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_WIREFRAMEGEOMETRY_H
#define __VSN_WIREFRAMEGEOMETRY_H

#include <set>
#include <list>
#include <unordered_map>

#include "vsn_color.h"
#include "vsn_geometry.h"
#include "vsn_namespace.h"

#include "vsn_global.h"

class MbCube;
class MbMatrix3D;
class MbCartPoint3D;

VSN_BEGIN_NAMESPACE

class Material;
class RenderState;
class Viewport;
class WireframeGeometryPrivate;
class Pen;
class Brush;

//------------------------------------------------------------------------------
/** \brief  \ru Абстрактный базовый класс для отрисовочной геометрии.
            \en Abstract base class for rendering geometry. \~
    \details  \ru Абстрактный базовый класс для отрисовочной геометрии:
                - содержит основной атрибут, который является таблицой материалов.
                - содержит ряд виртуальных функций, которые позволяют отрисовать геометрию.
                - содержит механизм отрисовки детализации заданного уровня. \n.
              \en Abstract base class for rendering geometry:
                - contains the main attribute that is material table.
                - contains virtual function row to provide rendering geometry.
                - contains rendering mechanism of set level of detail (LOD). \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS WireframeGeometry : public Geometry
{
    VSN_OBJECT(WireframeGeometry);
public:
    /// \ru Конструктор. \en Constructor.
    WireframeGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~WireframeGeometry();
public:
    /// \ru Действительна ли геометрия. \en Checks if geometry is valid.
    bool IsValid() const;
    /// \ru Задан ли материал. \en Checks if material is set.
    bool HasMaterial() const;
    /// \ru Получить первый материал из таблицы. \en Returns the first material from the table.
    Material* GetHeadMaterial() const;
    /// \ru Получить число материалов из таблицы. \en Returns material count from the table.
    size_t GetMaterialCount() const;
    /// \ru Получить указатель, соответствующий идентификатору. \en Returns the pointer corresponding to the identifier.
    Material* GetMaterialById(NodeKey id) const;
    /// \ru Получить таблицу материалов. \en Returns material table.
    std::set<Material*> GetMaterialSet() const;
    /// \ru Получить список идентификаторов материалов. \en Returns material identifier list.
    std::list<NodeKey> GetMaterialIds() const;
    /// \ru Существует ли в таблице материал с заданным идентификатором. \en Checks if the material with set identifier exists in the table.
    bool HasMaterialById(NodeKey id) const;
    /// \ru Получить габаритный куб. \en Returns bounding box.
    virtual const MbCube& GetBoundingBox() = 0;
    /// \ru Получить габаритный куб каркаса. \en Returns wireframe bounding box.
    const MbCube& GetWireBoundingBox();
    /// \ru Является ли габаритный куб допустимым. \en Checks if bounding box is valid.
    bool IsBoundingBoxValid() const;
    /// \ru Прозрачна ли геометрия. \en Checks if geometry is transparent.
    bool IsTransparent() const;
    /// \ru Имеется ли прозрачный материал в таблице. \en Checks if transparent material exists in the table.
    bool IsExistTransparentMaterials() const;
    /// \ru Задан ли цвет каждой вершины. \en Checks if color of each vertex is set.
    bool IsColorEachVertex() const;
    /// \ru Установить флаг назначения цвета для каждой вершины. \en Sets flag of setting color for each vertex.
    void SetColorEachVertex(bool bColorEachVertex);
    /// \ru Является ли геометрия каркасной. \en Checks if geometry is wireframe.
    bool IsWireframe() const;
    /// \ru Получить число граней. \en Returns face count.
    virtual size_t GetFaceCount(size_t indexLod = 0) const;
    /// \ru Получить число вершин. \en Returns vertex count.
    virtual size_t GetVertexCount() const;
    /// \ru Получить толщину линии(перегружены для удобства). \en Returns line width(functions are overloaded for convenience).
    double GetLineWidth() const;
    /// \ru Задать толщину линии(перегружены для удобства). \en Sets line width(functions are overloaded for convenience).
    void SetLineWidth(double lineWidth);
    /// \ru Получить цвет каркаса(перегружены для удобства). \en Returns wireframe color(functions are overloaded for convenience).
    Color GetWireframeColor() const;
    /// \ru Задать цвет каркаса(перегружены для удобства). \en Sets wireframe color(functions are overloaded for convenience).
    void SetWireframeColor(const Color& color);
    /// \ru Получить перо. \en Get pen.
    Pen GetPen() const;

    /// \ru Задать перо. \en Set pen.
    void SetPen(const Pen& pen);
    
    /// \ru Получить кисть. \en Get brush.
    // Brush GetBrush() const;

    /// \ru Задать кисть. \en Set brush.
    // void SetBrush(const Brush& brush);

    /// \ru Пуст ли каркас. \en Checks if wireframe is empty.
    bool IsWireframeEmpty() const;
    /// \ru Получить позиции вершин. \en Returns vertex positions.
    std::vector<float> GetWireFrameVertexPositions() const;
    /// \ru Получить число полилиний. \en Returns polyline count.
    int GetPolylineCount() const;
    /// \ru Получить смещение полилинии с заданным индексом в контейнере. \en Returns polyline offset with set index in the container.
    uint GetPolylineOffset(int index) const;
    /// \ru Получить размер полилинии с данным индексом. \en Returns size of polyline with given index.
    int GetPolylineSize(int index) const;
    /// \ru Получить объем геометрии. \en Returns geometry volume.
    virtual double GetVolume();
    /// \ru Используется ли вершинный буфер. \en Checks if vertex buffer is used.
    bool IsUsedVertexBuffer() const;
    /// \ru Нужно ли учитывать геометрию в механизме PixelCulling. \en NO TRANSLATION.
    virtual bool IsIgnorePixelCulling() const;
    /// \ru Запретить PixelCulling для этой геометрии. \en NO TRANSLATION.
    virtual void IgnorePixelCulling(bool value);
    /// \ru Преобразовать вершины сетки по матрице. \en Transforms mesh vertices by the matrix.
    virtual void TransformVerticesByMatrix(const MbMatrix3D& matrix);
public:
    /// \ru Удалить всю геометрию. \en Deletes all geometry.
    virtual void Clear();
    /// \ru Заменить основной материал. \en Replaces the main material.
    virtual void ReplaceMainMaterial(Material*);
    /// \ru Добавить материал в таблицу. \en Adds material to the table.
    void AddMaterial(Material* pMaterial);
    /// \ru Обновить число прозрачных материалов после операций с таблицей. \en Updates transparent material count after table operations.
    virtual void UpdateTransparentMaterialCount() override;
    /// \ru Инвертировать направление всех нормалей. \en Inverts direction of all vertex normals.
    virtual void InvertNormals();
    ///\ ru Задать уровень детализации в диапазоне от 0 до 100. \en Sets LOD in the range from 0 to 100.
    virtual void SetLevelDetail(int value);
    // добавить цвета
    void AddWireframeColors(const std::vector<float>& colors);
    /// \ru Добавить группу вершин и вернуть её идентификатор. \en Adds vertex group and returns its identifier.
    uint AddPoligonGroup(const std::vector<float>& vector);
    /// \ru Добавить группу вершин четырехугольной сетки и вернуть её идентификатор. \en Adds vertex quadrangle grid group and returns its identifier.
    uint AddPoligonQuadrangleGroup(const std::vector<float>& vector);
    /// \ru Задать, будет ли использоваться глобальный идентификатор. \en Sets if the global identifier will be used.
    void SetUseGlobalIdentifier(int global);
    /// \ru Скопировать буфер вершин в память. \en Copies vertex buffer into memory.
    virtual void CopyVertexBufferToClientSide();
    /// \ru Создать буфер вершин. \en Creates vertex buffer.
    virtual void ReleaseVertexBufferClientSide(bool update = false);
    /// \ru Задать, будет ли использоваться буфер вершин. \en Sets if vertex buffer will be used.
    virtual void SetUseVertexBufferObjects(bool usage);
public:
    /// \ru Выполнить отрисовку. \en Performs rendering.
    virtual void DoRender(const RenderState&);
protected:
    /// \ru Выполнить отрисовку. \en  Performs rendering.
    virtual void OGLInitGeom(const RenderState&);
    /// \ru Нарисовать каркас в одном из режимов: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES. \en Renders wireframe in one of the modes: GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP GL_LINES.
    virtual void OpenGLDraw(const RenderState&) = 0;
    void OGLDrawWireframe(const RenderState&, uint mode);
protected:
    /// \ru Очистить всю каркасную геометрию. \en Clears all wireframe.
    void ClearWireframe();
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    WireframeGeometry(WireframeGeometryPrivate& dd, Node* pParent);
    void SetWireframe(bool bWireframe);
private:
    friend class RenderContainer;
    VSN_DECLARE_EX_PRIVATE(WireframeGeometry);
};
VSN_END_NAMESPACE

#endif /* __VSN_WIREFRAMEGEOMETRY_H */
