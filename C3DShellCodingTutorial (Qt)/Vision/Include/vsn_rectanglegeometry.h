#ifndef __VSN_RECTANGLEGEOMETRY_H
#define __VSN_RECTANGLEGEOMETRY_H

#include "vsn_meshgeometry.h"

VSN_BEGIN_NAMESPACE

class RectangleGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Плоский трёхмерный прямоугольник.
           \en Rectangle in space. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS RectangleGeometry : public MeshGeometry
{
    VSN_OBJECT(RectangleGeometry);
    VSN_PROP_READ_WRITE_NOTIFY(width,  GetWidth,  SetWidth,  WidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, HeightModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    RectangleGeometry(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами. \en Default constructor.
    RectangleGeometry(double width, double height, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~RectangleGeometry();
public:
    /// \ru Выдать ширину прямоугольника. \en Get width.
    double GetWidth() const;
    /// \ru Выдать высоту прямоугольника. \en Get height.
    double GetHeight() const;
    /// \ru Задать размеры прямоугольника. \en Set rectangle parameters.
    void SetSize(double width, double height);
public:
    /// \ru Задать ширину прямоугольника. \en Set width.
    VSN_SLOT(Public, SetWidth, void SetWidth(double width))
    /// \ru Задать высоту прямоугольника. \en Set width.
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    VSN_SIGNAL(Public, WidthModified,  void WidthModified(double width), width)
    VSN_SIGNAL(Public, HeightModified, void HeightModified(double height), height)
public:
    /// \ru Выдать габаритный куб. \en Get a bounding box.
    virtual const MbCube& GetBoundingBox() override;
    /// \ru Обновить геометрию по новым данным. \en NO TRANSLATION.
    virtual void UpdateGeometry() override;
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Draw a sphere with OpenGL.
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(RectangleGeometry);
    VSN_DECLARE_EX_PRIVATE(RectangleGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_RECTANGLEGEOMETRY_H */
