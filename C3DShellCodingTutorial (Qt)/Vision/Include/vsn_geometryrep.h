////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru 3D представление геометрии.
       \en 3D geometry representation. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMETRYREP3D_H
#define __VSN_GEOMETRYREP3D_H

#include <set>
#include <mb_cube.h>

#include "vsn_wireframegeometry.h"
#include "vsn_geometrybuilder.h"
#include "vsn_absgeometryrep.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

class Material;
class GeometryRepPrivate;
//------------------------------------------------------------------------------
/** \brief \ru 3D представление геометрических данных.
           \en 3D geometry data representation. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeometryRep : public AbsGeometryRep
{
    VSN_OBJECT(GeometryRep);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit GeometryRep(Node* pParent = nullptr);
    /// \ru Конструктор по геометрическим параметрам объекта. \en Constructor by geometry parameters of the object.
    GeometryRep(WireframeGeometry* pGeometry, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~GeometryRep();
public:
    GeometryBuilderPtr GetGeometryBuilder() const;
    void SetGeometryBuilder(const GeometryBuilderPtr& builder);

    TypeTriangulation GetPrimitiveType() const;
    void SetPrimitiveType(TypeTriangulation primitiveType);

    /// \ru Вернуть тип представления геометрических данных. \en Returns representation type of geometry data.
    virtual int GetRepType() const;

    /// \ru Вернуть геометрические данные по уникальному ключу. \en Returns geometry data by unique key.
    WireframeGeometry* GetGeomByKey(NodeKey key) const;
    /// \ru Вернуть геометрические данные по индексу. \en Returns geometry data by index.
    WireframeGeometry* GetGeomAt(size_t index) const;
    /// \ru Вернуть список геометрических данных. \en Returns geometry data list.
    const std::list<WireframeGeometry*>* GetGeometryList() const;
    /// \ru Вернуть количество тел. \en Returns body count.
    size_t GetGeometryCount() const;

    /// \ru Вернуть true, если массив представлений пуст. \en True if representation array is empty.
    virtual bool IsEmpty() const;

    /// \ru Вернуть true, если ограничивающий габарит правильный. \en True if bounding box is valid.
    bool IsBoundingBoxValid() const;
    /// \ru Вернуть габарит представления. \en Returns bounding box of representation.
    MbCube GetBoundingBox() const;

    /// \ru Вернуть true, если представление содержит геометрические данные. \en True if representation contains geometry data.
    bool IsGeometryInRep(WireframeGeometry* pGeom);

    /// \ru Вернуть количество граней. \en Returns face count.
    size_t GetFaceCount() const;
    /// \ru Вернуть количество вершин. \en Returns vertex count.
    size_t GetVertexCount() const;
    /// \ru Вернуть количество материалов. \en Returns material count.
    size_t GetMaterialCount() const;

    /// \ru Вернуть набор материалов. \en Returns set of materials.
    std::set<Material*> GetMaterials() const;

    /// \ru Вернуть объем представления. \en Returns representation volume.
    double GetVolume() const;
public:
    /// \ru Добавить геометрические данные в представление. \en Adds geometry data to the representation.
    void AddGeometry(WireframeGeometry* pGeom);
    /// \ru Удалить пустые геометрические данные и обновить материалы. \en Deletes empty geometry data and update materials.
    void DeleteEmptyGeometry();
    /// \ru Сменить направление нормалей геометрии на противоположное. \en Reverses direction of all geometry normals.
    void ReverseNormals();
    /// \ru Заменить представление. \en Replaces the representation.
    virtual void ReplaceRep(AbsGeometryRep* pRep);
    /// \ru Заменить указанный материал. \en Replaces the specified material.
    void ReplaceMaterialById( NodeKey oldKey, Material* pMaterial);
    /// \ru Переложить геометрические данные из заданного представления. \en Shifts geometry data from the set representation.
    void ShiftGeometryFromRep(GeometryRep* pSource);
    /// \ru Сделать копию буфера вершин (VBO) на сторону клиента. \en Duplicates Vertex Buffer Object (VBO) to the client side.
    void DuplicateVertexBufferToClientSide();
    /// \ru Сформировать буфер вершин (VBO). \en Creates Vertex Buffer Object (VBO).
    void CreateVertexBufferClientSide(bool update = false);
    /// \ru Преобразовать вершины сетки по данной матрице. \en Transforms mesh vertices by given matrix.
    void TransformGeometriesByMatrix(const MbMatrix3D& matrix);
    /// \ru Установить признак использования буфера вершин. \en Sets flag of Vertex Buffer Object (VBO) usage.
    void SetUseVertexBufferObjects(bool usage);
public:
    /// \ru Оператор присваивания. \en Assignment operator.
    virtual GeometryRep& operator = (const GeometryRep&);
public:
    VSN_SLOT(Public, DetachGeometry, void DetachGeometry(Geometry* pGeometry))
protected:
    /// \ru Приватный конструктор для наследников. \en Private construсtor for inheritors.
    GeometryRep(GeometryRepPrivate& dd, Node* parent = nullptr);
protected:
    /// \ru Эта функция вызывается, если произошли какие-либо изменения в сцене. \en The function is called in case of scene being modified.
    virtual void SceneModificationEvent(const std::shared_ptr<SceneModification>& modification) override;
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DECLARE_EX_PRIVATE(GeometryRep);
//    VSN_DISABLE_COPY(GeometryRep)
};
VSN_END_NAMESPACE


#endif /* __VSN_GEOMETRYREP3D_H */
