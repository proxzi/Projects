////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс DiameterDimensionGeometry служит для построения диаметрального размера.
         \en DiameterDimensionGeometry class serves for building a diametrical size. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_DIAMETERDIMENSIONGEOMETRY_H
#define __VSN_DIAMETERDIMENSIONGEOMETRY_H

#include "vsn_dimensiongeometry.h"
#include "vsn_global.h"

class MbArc3D;
VSN_BEGIN_NAMESPACE
class DiameterDimensionGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс DiameterDimensionGeometry служит для построения диаметрального размера.
           \en DiameterDimensionGeometry class serves for building a diametrical size. \~
  \details \ru DiameterDimensionGeometry можно создать на основе MbArc3D т.е. задав размерную 
               плоскость тоже с помощью MbArc3D. Диаметральный размер считается не действительным, 
               если опорная точка и центр окружности не лежат на этом планаре, а также если опорная
               точка совпадает с центром окружности, т.е. радиус окружности равен нулю. В случае,
               если диаметральный размер построен на произвольном геометрическом объекте, не содержащем
               MbArc3D, то также диаметральный размер считается не действительным. \n.
           \en DiameterDimensionGeometry class can be created based on MbArc3D, i.e. setting
               a dimension plane with MbArc3D too. The diametrical size is not valid if a reference point
               and a circle center don't lie on this plane, and also if a reference point coincides with
               a circle center, i.e. a circle radius is 0. In case a diametrical size is built on
               an arbitrary geometric object not containing MbArc3D, then the diametrical size
               is also not valid. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS DiameterDimensionGeometry : public DimensionGeometry
{
    VSN_OBJECT(DiameterDimensionGeometry)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    DiameterDimensionGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~DiameterDimensionGeometry();
public:
    /// \ru Инициализация диаметрального размера. \en Initializes diametrical size. \~
    void SetMeasuredGeometry(const MbArc3D& circle);
public:
    /// \ru Получить точку фиксации на круге для размера диаметра. \en Returns fixation point on circle for diametrical size. \~
    MbCartPoint3D GetFixPoint() const;

public:
    /// \ru Вернуть единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Returns default measurement units identical to model measurement units for correct converting. \~
    virtual String GetDefaultUnits() const override;
    /// \ru Установить единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Sets default measurement units identical to model measurement units for correct converting. \~
    virtual void SetDefaultUnits(const String& units) override;

    /// \ru Вернуть единицы измерения для вывода. \en Returns measurement units for output. \~
    virtual String GetOutputUnits() const override;
    /// \ru Установить единицы измерения для вывода. \en Sets measurement units for output. \~
    virtual void SetOutputUnits(const String& units) override;

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
    VSN_DECLARE_EX_PRIVATE(DiameterDimensionGeometry)
};

VSN_END_NAMESPACE

#endif /* __VSN_DIAMETERDIMENSIONGEOMETRY_H */
