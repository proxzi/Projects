#ifndef __VSN_POINTGEOMETRYP_H
#define __VSN_POINTGEOMETRYP_H

#include "vsn_pointcloudgeometry.h"

VSN_BEGIN_NAMESPACE

class PointGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS PointGeometry : public PointCloudGeometry
{
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    PointGeometry(Node* pParent = nullptr);
    /// \ru Конструктор по параметам. \en NO TRANSLATION.
    PointGeometry(const MbCartPoint3D& pnt, Node* pParent = nullptr);
    /// \ru Конструктор по параметам. \en NO TRANSLATION.
    PointGeometry(double x, double y, double z, Node* pParent = nullptr);
public:
    /// \ru Вернуть координаты. \en NO TRANSLATION.
    MbCartPoint3D GetCoordinate() const;
    /// \ru Установить координаты. \en NO TRANSLATION.
    void SetCoordinate(const MbCartPoint3D& pnt);
    /// \ru Установить координаты. \en NO TRANSLATION.
    void SetCoordinate(double x, double y, double z);

    /// \ru Вернуть размер точки. \en NO TRANSLATION.
    float GetPointSize() const;
    /// \ru Установить размер точки. \en NO TRANSLATION.
    void SetPointSize(float size);

    /// \ru Вернуть размер точки для процесса селектирования. \en Return a size of point for selection process.
    float GetTrapSize() const;
    /// \ru Установить размер точки для процесса селектирования. \en Set a size of point for selection process.
    void  SetTrapSize(float size);
private:
    /// \ru Отрисовать точку. \en NO TRANSLATION.
    virtual void OpenGLDraw(const RenderState& renderState) override;
private:
    VSN_DISABLE_COPY(PointGeometry);
    VSN_DECLARE_EX_PRIVATE(PointGeometry);
};

VSN_END_NAMESPACE

#endif // __VSN_POINTGEOMETRYP_H

