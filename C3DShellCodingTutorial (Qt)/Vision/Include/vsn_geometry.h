////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Geometry является базовым для всех геометрических объектов.
         \en Geometry class is the base class for all geometric objects. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GEOMETRY_H
#define __VSN_GEOMETRY_H

#include "vsn_node.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class GeometryTraits;
class GeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Geometry является базовым для всех геометрических объектов.
           \en Geometry class is the base class for all geometric objects. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS Geometry : public Node
{
    VSN_OBJECT(Geometry);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~ 
    Geometry(Node* pParent = nullptr);
    /// \ru Конструктор. \en Constructor. \~
    Geometry(NodeKey id, const String& name);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~Geometry();
public:
    /// \ru Вернуть список данных геометрии из этого объекта. \en Returns list of geometry data from this object. \~
    std::vector<GeometryTraits*> GetGeometryTraits() const;
    /// \ru Добавить группу данных о геометрическом теле. \en Adds data group of geometric solid body. \~
    void AddGeometryTraits(GeometryTraits* pTraits);
    /// \ru Удалить группу данных о геометрическом теле. \en Removes data group of geometric solid body. \~
    void RemoveGeometryTraits(GeometryTraits* pTraits);
    /// \ru Разрешить двустороннее освещение. \en Set double side lighting. \~
    void SetDoubleSidedLighting( bool value );
    /// \ru Проверить использует ли геометрия двусторонее освещение. \en Does geometry use double sided lighting.
    bool IsDoubleSidedLighting() const;
public:
    /// \ru Проверить является ли геометрия аннатационным. \en NO TRANSLATION. \~
    virtual bool IsAnnotation() const;
    /// \ru Обновить число прозрачных материалов после операций с таблицей. \en Updates transparent material count after table operations. \~
    virtual void UpdateTransparentMaterialCount();
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry();
public:
    VSN_SIGNAL(Public, OnGeometryDestroyed, void OnGeometryDestroyed(Geometry* pGeometry), pGeometry)
protected:
    /// \ru Конструктор для внутреннего использования. \en Constructor for internal use.
    Geometry(GeometryPrivate& dd, Node* pParent);
private:
    virtual NCreatedModificationBasicPtr CreateNodeModification() const override;
private:
    VSN_DISABLE_COPY(Geometry);
    VSN_DECLARE_EX_PRIVATE(Geometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_GEOMETRY_H */
