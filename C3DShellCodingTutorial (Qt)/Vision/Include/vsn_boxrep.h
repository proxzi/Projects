////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс BoxRep является вспомогательным классом и представляет API 
             для управления геометрией BoxGeometry.
         \en BoxRep class is an auxiliary class and presents API to control
             BoxGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BOXREP_H
#define __VSN_BOXREP_H

#include "vsn_geometryrep.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru Класс BoxRep является вспомогательным классом и представляет API 
               для управления геометрией BoxGeometry.
           \en BoxRep class is an auxiliary class and presents API to control
               BoxGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS BoxRep : public GeometryRep
{
    VSN_OBJECT(BoxRep);
    VSN_PROP_READ_WRITE_NOTIFY(width,  GetWidth,  SetWidth,  OnWidthModified);
    VSN_PROP_READ_WRITE_NOTIFY(length, GetLength, SetLength, OnLengthModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    explicit BoxRep(Node* pParent = nullptr);
    virtual ~BoxRep();
public:
    /// \ru Вернуть ширину параллелепипеда. \en Returns box width.
    double GetWidth() const;
    /// \ru Вернуть длину параллелепипеда. \en Returns box length.
    double GetLength() const;
    /// \ru Вернуть высоту параллелепипеда. \en Returns box height.
    double GetHeight() const;
public:
    /// \ru Задать ширину параллелепипеда. \en Sets box width.
    VSN_SLOT(Public, SetWidth, void SetWidth(double width))
    /// \ru Задать длину параллелепипеда. \en Sets box length.
    VSN_SLOT(Public, SetLength, void SetLength(double length))
    /// \ru Задать высоту параллелепипеда. \en Sets box height.
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    /// \ru Модификация ширины параллелепипеда. \en Modifies box width.
    VSN_SIGNAL(Public, OnWidthModified,  void OnWidthModified(double width), width)
    /// \ru Модификация длины параллелепипеда. \en Modifies box length.
    VSN_SIGNAL(Public, OnLengthModified, void OnLengthModified(double length), length)
    /// \ru Модификация высоты параллелепипеда. \en Modifies box height.
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(double height), height)
private:
    VSN_DISABLE_COPY(BoxRep);
};

VSN_END_NAMESPACE

#endif /* __VSN_BOXREP_H */

