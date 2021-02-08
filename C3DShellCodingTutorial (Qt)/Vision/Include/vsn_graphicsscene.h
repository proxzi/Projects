////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс GraphicsScene представляет реализацию отрисовки сцены OpenGl'ем.
           \en NO TRANSLATION. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRAPHICSSCENE_H
#define __VSN_GRAPHICSSCENE_H

#include "vsn_object.h"
#include "vsn_orientationmarkerwidget.h"
#include "vsn_absvisioncomponent.h"
#include "vsn_cuttingtool.h"
#include "vsn_renderlayers.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Camera;
class Light;
class Process;
class Viewport;
class SceneContent;
class Widget3DBasic;
class GraphicsView;
class GraphicsScenePrivate;
class OrientationMarkerWidget;
//------------------------------------------------------------------------------
/** \brief \ru Класс GraphicsScene представляет собой реализацию отрисовки сцены OpenGl'ем.
           \en NO TRANSLATION. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS GraphicsScene : public AbsVisionComponent
{
    VSN_OBJECT(GraphicsScene)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GraphicsScene(Object* pParent = nullptr);
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit GraphicsScene(std::shared_ptr<SceneContent> ptrContent, Object* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GraphicsScene();
public:
    /// \ru Инициализация OpenGL. \en NO TRANSLATION. \~
    void InitializeGL();
    /// \ru Установить режим мультисэмплексное сглаживание(MSAA). \en NO TRANSLATION. \~
    void SetMultiSampleMode(bool mode);
    /// \ru Вернуть глобальный идентификатор шейдера. \en NO TRANSLATION. \~
    inline uint GetGlobalShaderId() const;
    /// \ru Установить глобальный идентификатор шейдера. \en NO TRANSLATION. \~
    void SetGlobalShaderId(uint id, const String& name);

    /// \ru Вернуть указатель на маркер ориентации для управления. \en NO TRANSLATION. \~
    OrientationMarkerWidget* GetOrientationMarker() const;
    /// \ru Вернуть указатель на содержание сцены. \en NO TRANSLATION.\~
    std::shared_ptr<SceneContent> GetSceneContent();

    /// \ru Вернуть указатель контейнер временных объектов. \en NO TRANSLATION.\~
    //[[depricated("this use RenderLayers")]]
    std::shared_ptr<RenderContainer> GetTempObjsContainer() const;

    /// \ru Вернуть указатель на Viewport. \en NO TRANSLATION. \~
    std::shared_ptr<Viewport> GetViewport();
    /// \ru Установить указатель на Viewport. \en NO TRANSLATION. \~
    void SetViewport(std::shared_ptr<Viewport> ptrViewport);

    /// \ru Вернуть указатель на основной источник света. \en NO TRANSLATION. \~
    Light* GetMainLight() const;
    /// \ru Установить двустороннее освещение. \en NO TRANSLATION. \~
    void SetDoubleSidedLighting(bool flag);

    /// \ru Вернуть список указателей на дополнительные источники освещения. \en NO TRANSLATION. \~
    std::list<Light*> GetExtraLights() const;
    /// \ru Создать дополнительный источник освещения. \en NO TRANSLATION.
    Light* CreateExtraLight();
    /// \ru Разрушить дополнительный источник освещения. \en NO TRANSLATION.
    void DestroyExtraLight(Light* pLight);

    /// \ru Вернуть и обновление глобальный ограничивающий куб.  \en NO TRANSLATION. \~
    MbCube GetGlobalBoundingBox();
    /// \ru Вернуть указатель на маркер ориентации. \en NO TRANSLATION. \~
    OrientationMarkerWidget* GetOrientationMarkerWidget() const;
    /// \ru Вернуть ссылку на инструмент динамического сечения. \en NO TRANSLATION. \~
    CuttingTool* GetCuttingTool();

    /// \ru Задать параметры слоя.  \en NO TRANSLATION. \~
    void SetRenderLayerSettings(uint32_t layer, const RenderLayerSettings &);
    /// \ru Получить параметры слоя.  \en NO TRANSLATION. \~
    const RenderLayerSettings& GetRenderLayerSettings(uint32_t layer) const;
public:
    /** \brief \ru Добавить виджет.
               \en NOT TRANSLATED. \~
        \param[in] pWidget - \ru Указатель на виджет.
                             \en NOT TRANSLATED. \~
    */
    void AddWidget(Widget3DBasic* pWidget);
public:
    void DrawGL();
    void ResizeGL(const Size& size);
protected:
    virtual void OnEngineStarting() override;
    virtual void OnInstalled() override;
    virtual void OnUninstalled() override;
    virtual std::vector<VisionWorkPtr> WorksToExecute(int64 time) override;
private:
    VSN_DISABLE_COPY(GraphicsScene);
    VSN_DECLARE_EX_PRIVATE(GraphicsScene);
    friend class PickLimitingVolumeWork;
};

VSN_END_NAMESPACE

#endif // __VSN_GRAPHICSSCENE_H
