////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NO TRANSLATION.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_LINEARDIMENSIONGEOMETRY_H
#define __VSN_LINEARDIMENSIONGEOMETRY_H

#include "vsn_dimensiongeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class LinearDimensionGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
  \details \ru NO TRANSLATION. \n.
           \en NO TRANSLATION. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS LinearDimensionGeometry : public DimensionGeometry
{
    VSN_OBJECT(LinearDimensionGeometry)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    LinearDimensionGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~LinearDimensionGeometry();
public:
    /// \ru Вернуть первую фиксированную точку размера. \en NO TRANSLATION. 
    MbCartPoint3D GetFirstPoint() const;
    /// \ru Вернуть вторую фиксированную точку размера. \en NO TRANSLATION. 
    MbCartPoint3D GetSecondPoint() const;
public:
    /// \ru Измерить расстояние между двумя точками. \en NO TRANSLATION.
    void SetMeasuredGeometry(const MbCartPoint3D& pnt1, const MbCartPoint3D& pnt2, const MbPlane& plane);
public:
    /// \ru Вернуть единицы измерения по умолчанию.(единицы являются модельные для правильной конвертации) \en NO TRANSLATION. \~
    virtual String GetDefaultUnits() const override;
    /// \ru Установить единицы измерения по умолчанию. (единицы являются модельные для правильной конвертации) \en NO TRANSLATION. \~
    virtual void SetDefaultUnits(const String& units) override;

    /// \ru Вернуть единицы измерения для вывода. \en NO TRANSLATION. \~
    virtual String GetOutputUnits() const override;
    /// \ru Установить единицы измерения для вывода. \en NO TRANSLATION. \~
    virtual void SetOutputUnits(const String& units) override;

    /// \ru Получить позицию текста 2D - размера. \en NO TRANSLATION.
    virtual const MbCartPoint3D GetTextPosition() const override;
    /// \ru Установить позицию текста 2D - размера. \en NO TRANSLATION.
    virtual void SetTextPosition(const MbCartPoint3D& textPos) override;
public:
    /// \ru Выдать габаритный куб. \en Get a bounding box.
    virtual const MbCube& GetBoundingBox();
    /// \ru Отрисовать размер с помощью OpenGL. \en Renders size with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& renderState);
protected:
    /// \ru Вернуть вычисленное значение измерения. \en NO TRANSLATION.
    double CalculateValue() const override;
protected:
    VSN_DECLARE_EX_PRIVATE(LinearDimensionGeometry)
};

VSN_END_NAMESPACE

#endif /* __VSN_LINEARDIMENSIONGEOMETRY_H */
