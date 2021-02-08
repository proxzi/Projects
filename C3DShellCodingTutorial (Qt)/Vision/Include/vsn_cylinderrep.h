////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс CylinderRep является вспомогательным классом и представляет API 
             для управления геометрией CylinderGeometry.
         \en CylinderRep class is an auxiliary class and presents API to control
             CylinderGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_CYLINDERREP_H
#define __VSN_CYLINDERREP_H

#include "vsn_geometryrep.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru Класс CylinderRep является вспомогательным классом и представляет API
               для управления геометрией CylinderGeometry.
           \en CylinderRep class is an auxiliary class and presents API to control
               CylinderGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS CylinderRep : public GeometryRep    
{
    VSN_OBJECT(CylinderRep)
    VSN_PROP_READ_WRITE(polyStep, GetPolygonStep, SetPolygonStep)
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, OnRadiusModified)
    VSN_PROP_READ_WRITE_NOTIFY(height, GetHeight, SetHeight, OnHeightModified)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit CylinderRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~CylinderRep();
public:
    /// \ru Вернуть высоту цилиндра. \en Returns cylinder height.
    double GetHeight() const;
    /// \ru Вернуть радиус цилиндра. \en Returns cylinder radius.
    double GetRadius() const;
    /// \ru Вернуть шаг полигона. \en Returns polygon step.
    int GetPolygonStep() const;
    /// \ru Задать шаг полигона (должен быть больше нуля). \en Sets polygon step that must be greater than zero.
    void SetPolygonStep(int polyStep);
public:
    /// \ru Задать радиус цилиндра (должен быть больше нуля). \en Sets cylinder radius that must be greater than zero.
    VSN_SLOT(Public, SetRadius, void SetRadius(double radius))
    /// \ru Задать высоту цилиндра (должна быть больше нуля). \en Sets cylinder height that must be greater than zero.
    VSN_SLOT(Public, SetHeight, void SetHeight(double height))
public:
    /// \ru Этот синал будет сгенерирован при изменении радиуса цилиндра. \en The signal will be generated when modifying cylinder radius. \~
    VSN_SIGNAL(Public, OnRadiusModified, void OnRadiusModified(double radius), radius)
    /// \ru Этот синал будет сгенерирован при изменении высоты цилиндра. \en The signal will be generated when modifying cylinder height. \~
    VSN_SIGNAL(Public, OnHeightModified, void OnHeightModified(double height), height)
private:
    VSN_DISABLE_COPY(CylinderRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_CYLINDERREP_H */

