////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс Viewport определяет viewport.
         \en Viewport class defines viewport. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_VIEWPORT_H
#define __VSN_VIEWPORT_H

#include <mb_cart_point.h>
#include <mb_vector3d.h>
#include "vsn_object.h"
#include "vsn_camera.h"
#include "vsn_rendercontainer.h"
#include "vsn_opengl.h"
#include "vsn_global.h"

class MbCube;
VSN_BEGIN_NAMESPACE
class Frustum;
class SceneContent;
class SamplePlane;
class RenderObject;
class Image;
class ViewportPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс Viewport определяет viewport.
            \en Viewport class defines viewport.
    \details  \ru Класс Viewport имеет дополнительные инструменты и функционал по управлению сценой.
              \en Viewport class has additional tools and functional for scene control. \~
    \ingroup Vision_Viewport
*/
//---
class VSN_CLASS Viewport : public Object
{
    VSN_OBJECT(Viewport)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit Viewport();
    /// \ru Деструктор. \en Destructor. \~
    virtual ~Viewport();

public:
    /// \ru Вернуть указатель на камеру, ассоциированную с Viewport. \en Returns pointer to the camera associated with viewport. \~
    Camera* GetCamera() const;
    /// \ru Установить самеру ассоциированную с Viewport. \en NO TRANSLATION. \~
    void SetCamera(Camera* pCamera);

    /// \ru Вернуть размер viewport. \en Returns viewport size. \~
    Size GetViewportSize() const;
    /// \ru Вернуть размер viewport. \en Returns viewport size. \~
    void GetViewportSize( int& width, int& height ) const;
    /// \ru Установить новые размеры viewport. \en Sets new viewport sizes. \~
    void SetSizeViewport(int width, int height, bool updateViewport = true);

    /// \ru Вернуть нормализованное положение мыши с учетом размера viewport. \en Returns normalized mouse position with given viewport size. \~
    MbCartPoint NormalizedMousePosition( int x, int y );
    /// \ru Конвертировать экранные координаты мыши в экранные координаты OpenGL. \en Transforms mouse screen coordinates to OpenGL screen coordinates. \~
    MbCartPoint ScreenPointToOpenGLScreen( int x, int y );
    /// \ru Конвертировать нормализованные экранные координаты мыши в экранные координаты OpenGL. \en Transforms normalized mouse screen coordinates to OpenGL screen coordinates. \~
    MbCartPoint ScreenNormalizedToOpenGLScreen( double x, double y );
    /// \ru Вернуть вектор взгляда по данной позиции мыши. \en Returns view vector by given mouse position. \~
    MbVector3D PositionMouseToVector( GLdouble posX, GLdouble posY ) const;
    /// \ru Вернуть нормализованный вектор взгляда по данной позиции мыши. \en Returns normalized view vector by given mouse position. \~
    MbVector3D NormalizedPositionMouseToVector( double posX, double posY ) const;

    /// \ru Вернуть угол обзора камеры для этого Viewport. \en Returns the camera angle for this viewport. \~
    double GetCameraAngle() const;
    /// \ru Установить угол обзора камеры для этого Viewport. \en Sets the camera angle for this viewport. \~
    void SetCameraAngle( double angle );

    /// \ru Вернуть тангенс камеры для этого Viewport. \en Returns the camera tangent for this viewport. \~
    double GetTangentCamera() const;

    /// \ru Получить расстояние до ближайшей плоскости отсечения. \en Returns a distance to the near (or front) clipping plane. \~
    double GetDistanceToNearClippingPlane() const;
    /// \ru Установить расстояние до ближайшей плоскости отсечения. \en Sets a distance to the near (or front) clipping plane. \~
    bool SetDistanceToNearClippingPlane( double dis );

    /// \ru Получить расстояние до дальней плоскости отсечения. \en Returns a distance to the far (or back) clipping plane. \~
    double GetDistanceToFarClippingPlane() const;
    /// \ru Установить расстояние до дальней плоскости отсечения. \en Sets a distance to the far (or back) clipping plane. \~
    bool SetDistanceToFarClippingPlane( double dis );
    /// \ru Установить ближнее и дальнее отсечения по габариту. \en Sets the near and far clipping by bounding box. \~
    void SetDistanceClippingPlane( const MbCube& bBox );

    /// \ru Вернуть цвет фона порта. \en Returns port background colour. \~
    const Color& GetBackgroundColour() const;
    /// \ru Установить цвет фона viewport. \en Sets viewport background colour. \~
    void SetBackgroundColour( const Color& color );
    /// \ru Установить градиентный цвет фона viewport. \en Sets viewport gradient background colour. \~
    void SetGradientBackgroundColour(const Color& topColor, const Color& bottomColor);

    /// \ru Загрузить изображение фона viewport по имени файла. \en Loads viewport background image by file name. \~
    void LoadBackgroundImage(const std::string& imageFile);
    /// \ru Загрузить изображение фона viewport из Image. \en Loads viewport background image from Image. \~
    void LoadBackgroundImage(const Image& image);
    /// \ru Удалить изображение фона viewport. \en Deletes viewport background image. \~
    void DeleteBackgroundImage();

    /// \ru Вернуть размер ловушки для выбора. \en Returns selection area size. \~
    int GetSelectionAreaSize() const;
    /// \ru Установить размер ловушки для выбора. \en Sets selection area size. \~
    void SetSelectionAreaSize( int size );

    /// \ru Вернуть проекционную матрицу. \en Returns projection matrix. \~
    MbMatrix3D GetProjectionMatrix() const;
    /// \ru Вернуть составную матрицу (проекционная и видовая). \en Returns composite matrix(projection matrix and view matrix). \~
    MbMatrix3D GetMultipleMatrix() const;

    /// \ru Вернуть указатель на контейнер виджетов. \en Returns pointer to the widget container. \~
    RenderContainer* GetWidgetsContainer();

    /// \ru Вернуть true, если используется ортогональная проекция. \en True if orthographic projection is used. \~
    bool IsOrthographicProjection() const;
    /// \ru Установить использование ортогональной проекции. \en Orthographic projection use flag. \~
    void SetOrthographicProjection( bool bOrthographic );

    /// \ru Вернуть минимальное количество пикселей при выбранном размере. \en Returns minimum pixel count for the selected size. \~
    int GetPixelCullingSize() const;
    /// \ru Установить минимальное количество пикселей при выбранном размере. \en Sets minimum pixel count for the selected size. \~
    void SetPixelCullingSize( int size );

    /// \ru Вернуть минимальное соотношение пикселей для очистки. \en Returns minimum pixel ratio for culling. \~
    double GetStaticPixelCullingRatio() const;
    /// \ru Вернуть минимальное динамическое соотношение пикселей для очистки. \en Returns minimum dynamic pixel ratio for culling. \~
    double GetDynamicPixelCullingRatio() const;

    /// \ru Вернуть значение масштаба. \en NOT TRANSLATED. \~
    double GetScale() const;
public:
    /// \ru Инициализация OpenGL. \en Initializes OpenGL. \~
    void InitOpenGl();

    /// \ru Добавить матрицу камеры. \en Adds the camera matrix. \~
    void glMultMatrixCamera();

    /// \ru Обновить viewport и матрицу проецирования. \en Updates viewport and projection matrix. \~
    void UpdateProjectionMatrix();

    /// \ru Вернуть соотношение сторон экрана. \en Returns screen aspect ratio. \~
    double GetAspectRatio() const;

    /// \ru Установить принудительно соотношение сторон экрана. \en Sets forcibly screen aspect ratio. \~
    void SetAspectRatio( double );

    /// \ru Обновить соотношение сторон экрана. \en Updates screen aspect ratio. \~
    void UpdateAspectRatio();

    /// \ru Вернуть усеченный конус этого вида. \en Returns view frustum. \~
    const Frustum& GetFrustum() const;

    /// \ru Вернуть усеченный конус для выбора. \en Returns view frustum for selection. \~
    Frustum SelectionFrustum(int x, int y) const;

    /// \ru Преобразовать координаты окна в плоскость, параллельную экрану и проходящую через начало координат сцены. \en Transforms window coordinates to the plane parallel to the screen and passing through the scene origin. \~
    void ConvertScreenPointToParallelScreenPlane( const MbCartPoint& logPos, const MbCartPoint3D& origin, MbCartPoint3D& point );

    /// \ru Преобразование мировой точки в оконную. \en Transforms the world point to the window point. \~
    void WorldPointToScreenPoint( const MbCartPoint3D& wp, MbCartPoint3D& lp ) const;
    /// \ru Преобразование оконной точки в мировую. \en Transforms the window point to the world point. \~
    void ScreenPointToWorldPoint( const MbCartPoint3D& lp, MbCartPoint3D& wp ) const;

    /// \ru Вернуть MbCartPoint3D из экранных координат. \en Returns MbCartPoint3D from screen coordinates. \~
    MbCartPoint3D UnProject( int x, int y, uint buffer = GL_FRONT ) const;

    /// \ru Вернуть список MbCartPoint3D из экранных координат(размер этого списка должен быть кратным двум). \en Returns MbCartPoint3D list from screen coordinates. The size of this list must be multiple of two. \~
    std::vector<MbCartPoint3D> UnProject( const std::vector<int>& vectorX, uint buffer = GL_FRONT ) const;

public:
    /// \ru Отрисовать фона, если цвет задан и не oпределен SetGradientBackgroundColour или Image. \en Renders background. \~
    void ClearColor();
    /// \ru Отрисовать фон. \en Renders background. \~
    void OGLDrawBackground();
    /// \ru Отрисовать контейнер виджетов. \en Renders widget container. \~
    void OGLDrawWidgets();
public:
    /// \ru Обновить усеченный конус viewport. \en Updates view frustum for viewport. \~
    bool UpdateFrustumPlanes(MbMatrix3D* pMatrix = nullptr);

    /// \ru Добавить новые плоскости для усечения viewport. \en Adds new planes for viewport clipping. \~
    //void AddClipPlane( uint planeGlEnum, SamplePlane* pPlane );

    /// \ru Удалить плоскость усечения по идентификатору. \en Removes clipping plane by identifier. \~
    //void RemoveClipPlane(uint planeGlEnum);

    /// \ru Удалить все плоскости усечения. \en Removes all clipping planes. \~
    //void RemoveAllClipPlane();

    /// \ru Установить флаг использования отсечения. \en Sets clipping use flag. \~
    //void SetClipPlane( bool on );

    /// \ru Добавить виджит и отрисовать его. \en Adds widget and renders it. \~
    void AddWidget( RenderObject& widget );

    /// \ru Увеличить модель до размера viewport по габариту модели. \en Zooms the model to viewport size by bounding box of the model. \~
    void ZoomToFit( const MbCube& box, double factor = 1.8 );
public:
    VSN_SIGNAL(Public, RenderSelection, void RenderSelection())
    VSN_SIGNAL(Public, ViewportSizeModified, void ViewportSizeModified(const Size& size), size)
private:
    VSN_DECLARE_PRIVATE(Viewport)
};

typedef std::shared_ptr<Viewport> ViewportPtr;

VSN_END_NAMESPACE

#endif /* __VSN_VIEWPORT_H */
