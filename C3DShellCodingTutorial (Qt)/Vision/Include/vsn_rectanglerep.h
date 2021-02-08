#ifndef __VSN_RECTANGLEREP_H
#define __VSN_RECTANGLEREP_H

#include "vsn_geometryrep.h"

VSN_BEGIN_NAMESPACE
/* RectangleRep */
class VSN_CLASS RectangleRep : public GeometryRep
{
    VSN_OBJECT(RectangleRep);
    VSN_PROP_READ_WRITE_NOTIFY(width, GetWidth, SetWidth, WidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, HeightModified);
public:
    explicit RectangleRep(Node* pParent = nullptr);
    virtual ~RectangleRep();
public:
    /// \ru Выдать ширину прямоугольника. \en Get width.
    double GetWidth() const;
    /// \ru Выдать высоту прямоугольника. \en Get height.
    double GetHeight() const;
public:
    /// \ru Задать ширину прямоугольника. \en Set width.
    VSN_SLOT(Public, SetWidth, void SetWidth(double width))
    /// \ru Задать высоту прямоугольника. \en Set width.
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    VSN_SIGNAL(Public, WidthModified, void WidthModified(double width), width)
    VSN_SIGNAL(Public, HeightModified, void HeightModified(double height), height)
private:
    VSN_DISABLE_COPY(RectangleRep);
};

VSN_END_NAMESPACE

#endif /* __VSN_RECTANGLEREP_H */

