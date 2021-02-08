////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс AngleDimensionGeometry служит для построения углового размера.
         \en AngleDimensionGeometry class serves for building an angular size. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_ANGLEDIMENSIONGEOMETRY_H
#define __VSN_ANGLEDIMENSIONGEOMETRY_H

#include "vsn_dimensiongeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class AngleDimensionGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс AngleDimensionGeometry служит для построения углового размера.
           \en AngleDimensionGeometry class serves for building an angular size. \~
  \details \ru AngleDimensionGeometry можно построить по трем точкам задав центр и две вершины. 
               В случае трех точек размерная плоскость (на которой построено представление размера) 
               может быть вычислена однозначно, так как через три определенные точки можно построить 
               только одну плоскость. Поэтому, если пользовательская плоскость отличается от этой, 
               размер не может быть построен.\n.
           \en AngleDimensionGeometry can be built by three points by setting a center and two vertexes.
               In case of three points, a dimension plane, on which size representation is built,
               can be computed uniquely, as only a plane can be built using three points.
               So if the user's plane is different from this the size cannot be built. \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS AngleDimensionGeometry : public DimensionGeometry
{
    VSN_OBJECT(AngleDimensionGeometry)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    AngleDimensionGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~AngleDimensionGeometry();
public:
    /// \ru Tип угла. \en Angle type.\~
    enum TypeAngle
    {
        ta_Internal, ///< \ru Угол между двумя линиями. \en Angle between two lines. \~
        ta_Exterior  ///< \ru Угол равный 2_PI (минус внутренний угол). \en Angle is 2_PI (minus inner angle). \~
    };
public:
    /// \ru Измеряет угол, определяемый тремя точками. \en Measures angle defined by three points. \~
    void SetMeasuredGeometry(const MbCartPoint3D& center, const MbCartPoint3D& pnt1, const MbCartPoint3D& pnt2);
public:
    /// \ru Вернуть значение первой точки, образующей угол. \en Returns value of the first point creating an angle. \~
    const MbCartPoint3D& GetFirstPoint() const;
    /// \ru Вернуть значение второй точки, образующей угол. \en Returns value of the second point creating an angle. \~
    const MbCartPoint3D& GetSecondPoint() const;
    /// \ru Вернуть значение центра, образующего угол. \en Returns value of the center creating an angle. \~
    const MbCartPoint3D& GetCenterPoint() const;
public:
    /// \ru Вернуть единицы измерения по умолчанию, являющиеся идентичными едницам измерения модели для правильной конвертации.
    /// \en Returns default measurement units identical to model measurement units for correct converting. \~
    virtual String GetDefaultUnits() const override;
    /// \ru Установить единицы измерения по умолчанию, являющиеся идентичными едницам измерения модели для правильной конвертации.
    /// \en Sets default measurement units identical to model measurement units for correct converting. \~
    virtual void SetDefaultUnits(const String& units) override;

    /// \ru Вернуть единицы измерения для вывода. \en Returns measurement units for output. \~
    virtual String GetOutputUnits() const override;
    /// \ru Установить единицы измерения для вывода. \en Sets measurement units for output. \~
    virtual void SetOutputUnits(const String& units) override;

    /// \ru Получить позицию текста 2D - размера. \en Returns text position of 2D size. \~
    virtual const MbCartPoint3D GetTextPosition() const override;
    /// \ru Установить позицию текста 2D - размера. \en Sets text position of 2D size. \~
    virtual void SetTextPosition(const MbCartPoint3D& textPos) override;
public:
    /// \ru Выдать габаритный куб. \en Returns bounding box. \~
    virtual const MbCube& GetBoundingBox();
protected:
    /// \ru Вернуть вычисленное значение измерения. \en Returns calculated value of measurement. \~
    double CalculateValue() const override;

    /// \ru Отрисовать размер с помощью OpenGL. \en Renders size with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& renderState);
protected:
    VSN_DECLARE_EX_PRIVATE(AngleDimensionGeometry)
};

VSN_END_NAMESPACE

#endif /* __VSN_ANGLEDIMENSIONGEOMETRY_H */
