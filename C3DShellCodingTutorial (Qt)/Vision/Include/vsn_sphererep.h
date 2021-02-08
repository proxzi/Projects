#ifndef __VSN_SPHEREREP_H
#define __VSN_SPHEREREP_H

#include "vsn_geometryrep.h"

VSN_BEGIN_NAMESPACE

/* SphereRep */
class VSN_CLASS SphereRep : public GeometryRep
{
    VSN_OBJECT(SphereRep);
    VSN_PROP_READ_WRITE(deviation, GetDeviation, SetDeviation);
    VSN_PROP_READ_WRITE_NOTIFY(radius, GetRadius, SetRadius, RadiusModified);
public:
    explicit SphereRep(Node* pParent = nullptr);
    virtual ~SphereRep();
public:
    /// \ru Вернуть радиус сферы. \en Set radius.
    double GetRadius() const;
    /// \ru Вернуть отклонение для расчета полигона. \en Set polygon deviation.
    double GetDeviation() const;
public:
    /// \ru Задать радиус сферы. \en Set radius.
    VSN_SLOT(Public, SetRadius, void SetRadius(double radius))
    /// \ru Задать отклонение для расчета полигона. \en Set polygon deviation.
    VSN_SLOT(Public, SetDeviation, void SetDeviation(double deviation))
public:
    VSN_SIGNAL(Public, RadiusModified, void RadiusModified(double radius), radius)
private:
    VSN_DISABLE_COPY(SphereRep);
};

VSN_END_NAMESPACE

#endif /* __VSN_SPHEREREP_H */

