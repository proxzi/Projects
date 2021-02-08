////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс RadialDimensionGeometry служит для построения радиального размера.
         \en RadialDimensionGeometry class serves for building a radial dimension. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RADIALDIMENSIONGEOMETRY_H
#define __VSN_RADIALDIMENSIONGEOMETRY_H

#include "vsn_dimensiongeometry.h"
#include "vsn_global.h"

class MbArc3D;
VSN_BEGIN_NAMESPACE
class RadialDimensionGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс RadialDimensionGeometry служит для построения радиального размера.
           \en RadialDimensionGeometry class serves for building a diametrical size. \~
  \details \ru RadialDimensionGeometry можно создать на основе MbArc3D т.е. задав размерную 
               плоскость тоже с помощью MbArc3D. Диаметральный размер считается не действительным, 
               если опорная точка и центр окружности не лежат на этом планаре, а также если опорная
               точка совпадает с центром окружности, т.е. радиус окружности равен нулю. В случае,
               если диаметральный размер построен на произвольном геометрическом объекте, не содержащем
               MbArc3D, то также диаметральный размер считается не действительным. \n.
           \en RadialDimensionGeometry class can be created based on MbArc3D, i.e. setting
               a dimension plane with MbArc3D too. The diametrical size is not valid if a reference point
               and a circle center don't lie on this plane, and also if a reference point coincides with
               a circle center, i.e. a circle radius is 0. In case a diametrical size is built on
               an arbitrary geometric object not containing MbArc3D, then the diametrical size
               is also not valid. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS RadialDimensionGeometry : public DimensionGeometry
{
    VSN_OBJECT(RadialDimensionGeometry)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RadialDimensionGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~RadialDimensionGeometry();
public:
    /// \ru Инициализация диаметрального размера. \en Initializes diametrical size. \~
    void SetMeasuredGeometry(const MbArc3D& circle);
public:
    /// \ru Получить точку фиксации на круге для размера диаметра. \en Returns fixation point on circle for diametrical size. \~
    MbCartPoint3D GetFixPoint() const;

public:
    /// \ru Вернуть позицию текста 2D - размера. \en Returns position of 2D size text. \~
    virtual const MbCartPoint3D GetTextPosition() const override;
    /// \ru Установить позицию текста 2D - размера. \en Sets position of 2D size text. \~
    virtual void SetTextPosition(const MbCartPoint3D& textPos) override;
public:
    /// \ru Вернуть габаритный куб. \en Returns bounding box. \~
    virtual const MbCube& GetBoundingBox() override;
protected:
    virtual void OpenGLDraw(const RenderState& renderState) override;
protected:
    /// \ru Вернуть вычисленное значение измерения. \en Returns calculated measurement value. \~
    double CalculateValue() const override;
protected:
    VSN_DECLARE_EX_PRIVATE(RadialDimensionGeometry)
};

VSN_END_NAMESPACE

#endif /* __VSN_RADIALDIMENSIONGEOMETRY_H */
