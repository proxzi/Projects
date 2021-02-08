////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru BoundingBoxGeometry является ограничивающим параллелепипедом и служит для 
             отображения информационного габарита узла в сцене по указанному сегменту.
         \en BoundingBoxGeometry is bounding box and serves for displaying
             an informational graph size in a scene by specified segment. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_BOUNDINGBOXGEOMETRY_H
#define __VSN_BOUNDINGBOXGEOMETRY_H

#include "vsn_wireframegeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class SceneSegment;
class BoundingBoxGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxGeometry является ограничивающим параллелепипедом и служит для 
               отображения информационного габарита узла в сцене по указанному сегменту.
           \en BoundingBoxGeometry is bounding parallelepiped and serves for displaying
               an informational graph size in a scene by specified segment. \~
  \details \ru BoundingBoxGeometry имеет возможность менять цвет основных осей X, Y, Z, 
               а также функцию инициализации начального сегмента для вывода его габарита. \n.
           \en BoundingBoxGeometry has an opportunity to change a color of main axes X, Y, Z
               and also a function of initializating initial segment for output of its size. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS BoundingBoxGeometry : public WireframeGeometry
{
    VSN_OBJECT(BoundingBoxGeometry);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    BoundingBoxGeometry(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~BoundingBoxGeometry();
public:
    /// \ru Вернуть ограничивающий прямоугольник сегмента. \en Returns bounding box of segment. \~
    MbCube GetSegmentBoundingBox() const;

    /// \ru Вернуть указатель на начальный сегмент. \en Returns pointer to initial segment. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Установить начальный сегмент для отображения его габарита в сцене. \en Sets initial segment for displaying its size in scene. \~
    void SetSceneSegment(const SceneSegment* pSegment);

    /// \ru Вернуть цвет заданной оси. \en Returns color of given axis. \~
    Color GetColorAxis(AxisOrientation orientation) const;
    /// \ru Установить цвет заданной оси. \en Sets color of given axis. \~
    void SetColorAxis(AxisOrientation orientation, const Color& color);
public:
    /// \ru Вернуть ограничивающий параллелепипед. \en Returns bounding box. \~
    virtual const MbCube& GetBoundingBox();
    /// \ru Блокировать PixelCulling для этой геометрии. \en Blocks PixelCulling for this geometry. \~
    virtual bool IsIgnorePixelCulling() const override;
    /// \ru Обновить геометрию по новым данным. \en Updates geometry by new data. \~
    virtual void UpdateGeometry() override;
public:
    /// \ru Сигнал будет генерирован при изменении габарита сегмента. \en Signal will be generated when modifying segment size. \~
    VSN_SIGNAL(Public, OnGeometryModified, void OnGeometryModified())
private:
    /// \ru Отрисовать параллелепипед с помощью OpenGL. \en Renders box with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
private:
    void UpdateBoundingBox();
    /// \ru Создать каркасное представление. \en Creates wireframe representation. \~
    void BuildWireFrameBox();
private:
    VSN_DECLARE_EX_PRIVATE(BoundingBoxGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_BOUNDINGBOXGEOMETRY_H */
