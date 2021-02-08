////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс BoxGeometry представляет геометрию в виде параллелепипеда.
         \en BoxGeometry class presents geometry as a box. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_BOXGEOMETRY_H
#define __VSN_BOXGEOMETRY_H

#include "vsn_meshgeometry.h"

VSN_BEGIN_NAMESPACE

class BoxGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс BoxGeometry представляет геометрию в виде параллелепипеда,
               который строится по заданным параметрам: ширина, высота и длина.
           \en BoxGeometry class presents geometry as a box built by given parameters:
               width, height and length. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS BoxGeometry : public MeshGeometry
{
    VSN_OBJECT(BoxGeometry);
    VSN_PROP_READ_WRITE_NOTIFY(width,  GetWidth,  SetWidth,  OnWidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(length, GetLength, SetLength, OnLengthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    BoxGeometry(Node* pParent = nullptr);
    /// \ru Конструктор по ширине, длине и высоте. \en Сonstructor by width, length and height. \~
    BoxGeometry(double width, double length, double height, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~BoxGeometry();
public:
    /// \ru Вернуть ширину параллелепипеда. \en Returns box width. \~
    double GetWidth() const;
    /// \ru Вернуть длину параллелепипеда. \en Returns box length. \~
    double GetLength() const;
    /// \ru Вернуть высоту параллелепипеда. \en Returns box height. \~
    double GetHeight() const;
public:
    /// \ru Установить ширину параллелепипеда. \en Sets box width. \~
    VSN_SLOT(Public, SetWidth, void SetWidth(double width))
    /// \ru Установить длину параллелепипеда. \en Sets box length.
    VSN_SLOT(Public, SetLength, void SetLength(double length))
    /// \ru Установить высоту параллелепипеда. \en Sets box height. \~
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    /// \ru Модификация ширины параллелепипеда. \en Modifies box width. \~
    VSN_SIGNAL(Public, OnWidthModified, void OnWidthModified(double width), width)
    /// \ru Модификация длины параллелепипеда. \en Modifies box length. \~
    VSN_SIGNAL(Public, OnLengthModified, void OnLengthModified(double length), length)
    /// \ru Модификация высоты параллелепипеда. \en Modifies box height. \~
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(double height), height)
public:
    /// \ru Вернуть ограничивающий параллелепипед. \en Returns bounding box. \~
    virtual const MbCube& GetBoundingBox() override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Renders sphere with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(BoxGeometry);
    VSN_DECLARE_EX_PRIVATE(BoxGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_BOXGEOMETRY_H */
