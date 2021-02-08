#ifndef __VSN_POINTCLOUDGEOMETRY_H
#define __VSN_POINTCLOUDGEOMETRY_H

#include "vsn_wireframegeometry.h"

VSN_BEGIN_NAMESPACE

class PointCloudGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS PointCloudGeometry : public WireframeGeometry
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    PointCloudGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~PointCloudGeometry();
public:
    /// \ru Выдать габаритный куб. \en Get a bounding box.
    virtual const MbCube& GetBoundingBox() override;
    /// \ru Определить, является ли объект пустым. \en Determine whether the object is empty.
    bool IsEmpty() const;
public:
    /// \ru Добавить массив точек для построения облака точек и вернуть идентификатор этой группы точек. \en NO TRANSLATION.
    uint AddPoints(const std::vector<float>& data);
    /// \ru Добавить массив точек для построения облака точек и вернуть идентификатор этой группы точек. \en NO TRANSLATION.
    uint AddPoints(const std::vector<MbCartPoint3D>& points);
    /// \ru Добавить массив точек для построения облака точек и вернуть идентификатор этой группы точек. \en NO TRANSLATION.
    uint AddPoints(const std::vector<MbFloatPoint3D>& points);
    /// \ru Добавить цвет для каждой точки. \en NO TRANSLATION.
    void AddColors(const std::vector<float>& data);
    /// \ru Добавить цвет для каждой точки. \en NO TRANSLATION.
    void AddColors(const std::vector<Color>& colors);
    /// \ru Очистить содержимое полигона и сделать его пустым. \en Clear the object.
    void Clear();
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION.
    PointCloudGeometry(PointCloudGeometryPrivate& dd, Node* pParent);
protected:
     /// \ru Отрисовать облако точек. \en NO TRANSLATION.
    virtual void OpenGLDraw(const RenderState& renderState) override;
private:
    VSN_DISABLE_COPY(PointCloudGeometry);
    VSN_DECLARE_EX_PRIVATE(PointCloudGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_POINTCLOUDGEOMETRY_H */
