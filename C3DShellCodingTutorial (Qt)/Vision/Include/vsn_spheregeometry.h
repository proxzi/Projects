#ifndef __VSN_SPHEREGEOMETRY_H
#define __VSN_SPHEREGEOMETRY_H

#include "vsn_meshgeometry.h"

VSN_BEGIN_NAMESPACE

class SphereGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Сфера.
           \en Sphere. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS SphereGeometry : public MeshGeometry
{
    VSN_OBJECT(SphereGeometry);
    VSN_PROP_READ_WRITE(deviation, GetDeviation, SetDeviation);
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, RadiusModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    SphereGeometry(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами. \en Default constructor.
    SphereGeometry(double radius, int sag = 60, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~SphereGeometry();
public:
    /// \ru Вернуть радиус сферы. \en Set radius.
    double GetRadius() const;
    /// \ru Вернуть отклонение для расчета полигона. \en Set polygon deviation.
    int GetDeviation() const;
public:
    /// \ru Задать радиус сферы. \en Set radius.
    VSN_SLOT(Public, SetRadius, void SetRadius(double radius))
    /// \ru Задать отклонение для расчета полигона. \en Set polygon deviation.
    VSN_SLOT(Public, SetDeviation, void SetDeviation(int deviation))
public:
    VSN_SIGNAL(Public, RadiusModified, void RadiusModified(double radius), radius)
public:
    /// \ru Выдать габаритный куб. \en Get a bounding box.
    virtual const MbCube& GetBoundingBox() override;
    /// \ru Обновить геометрию по новым данным. \en NO TRANSLATION.
    virtual void UpdateGeometry() override;
protected:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Draw a sphere with OpenGL.
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(SphereGeometry);
    VSN_DECLARE_EX_PRIVATE(SphereGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_SPHEREGEOMETRY_H */
