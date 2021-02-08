////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс ConeGeometry представляет геометрию конуса.
         \en ConeGeometry class presents cone geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_CONEGEOMETRY_H
#define __VSN_CONEGEOMETRY_H

#include "vsn_meshgeometry.h"

VSN_BEGIN_NAMESPACE

class ConeGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс ConeGeometry представляет геометрию конуса.
           \en ConeGeometry class presents cone geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS ConeGeometry : public MeshGeometry
{
    VSN_OBJECT(ConeGeometry);
    VSN_PROP_READ_WRITE(polyStep, GetPolygonStep, SetPolygonStep);
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, OnRadiusModified);
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    ConeGeometry(Node* pParent = nullptr);
    /// \ru Конструктор с параметрами. \en Default constructor. \~
    ConeGeometry(double radius, double height, int sag = 60, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~ConeGeometry();
public:
    /// \ru Вернуть высоту конуса. \en Returns cone height. \~
    double GetHeight() const;
    /// \ru Вернуть радиус конуса. \en Returns cone radius. \~
    double GetRadius() const;
    /// \ru Вернуть шаг полигона. \en Returns polygon step. \~
    int GetPolygonStep() const;
    /// \ru Задать шаг полигона (должен быть больше нуля). \en Sets a polygon step that must be greater than zero. \~
    void SetPolygonStep(int polyStep);
public:
    /// \ru Задать радиус конуса (должен быть больше нуля). \en Sets cone radius that must be greater than zero. \~
    VSN_SLOT(Public, SetRadius, void SetRadius(double radius))
    /// \ru Задать высоту конуса (должна быть больше нуля). \en Sets cone height that must be greater than zero. \~
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    /// \ru Этот сигнал будет сгенерирован при изменении радиуса основания конуса. \en The signal will be generated when modifying cone base radius. \~
    VSN_SIGNAL(Public, OnRadiusModified, void OnRadiusModified(double radius), radius)
    /// \ru Этот сигнал будет сгенерирован при изменении высоты конуса. \en The signal will be generated when modifying cone height. \~
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(double height), height)
public:
    /// \ru Вернуть габаритный куб. \en Returns bounding box.
    virtual const MbCube& GetBoundingBox() override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data.
    virtual void UpdateGeometry() override;
private:
    /// \ru Отрисовать сферу с помощью OpenGL. \en Renders sphere with OpenGL.
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    VSN_DISABLE_COPY(ConeGeometry);
    VSN_DECLARE_EX_PRIVATE(ConeGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_CONEGEOMETRY_H */
