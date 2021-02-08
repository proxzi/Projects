////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WINDOW_H
#define __VSN_WINDOW_H

#include "vsn_object.h"
#include "vsn_rect.h"
#include "vsn_namespace.h"
#include "vsn_renderingarea.h"
#include "vsn_processevent.h"
#include "vsn_renderingareaformat.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Screen;
class OpenGLContextInterface;
class WindowPrivate;
class PlatformWindow;

//------------------------------------------------------------------------------
/** \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS Window : public Object, public RenderingArea
{
    VSN_OBJECT(Window)
public:
    enum VisibilityState
    {
        VS_Hidden,
        VS_AutoVisibility,
        VS_Windowed,
        VS_Minimized,
        VS_Maximized,
        VS_FullScreen
    };
    VSN_ENUM(VisibilityState)
public:
    explicit Window(Screen* screen = nullptr);
    explicit Window(Window* parent);
    virtual ~Window();
public:
    // созать окно
    void Create();
    // созать окно
    void Create(void* hWindow, OpenGLContextInterface* pContext);
    // созать окно
//    void Create(PlatformWindow* pPlatformWindow, OpenGLContextInterface* pContext);
    // вернуть хандл окна
    void* GetHWND() const;
    Window* GetParent() const;
    bool IsTopLevel() const;

    // вернуть формат окна
    virtual RenderingAreaFormat GetFormat() const override;
    // установить формат отрисовочному окну
    void SetFormat(const RenderingAreaFormat& format);
    RenderingAreaFormat GetQueriedFormat() const;

    void SetRenderingAreaType(RenderingAreaType areaType);
    virtual RenderingAreaType GetRenderingAreaType() const override;

    String GetTitleText() const;
    void SetTitleText(const String& title);

    Size GetMinimumSize() const;
    Size GetMaximumSize() const;

    int GetMinimumWidth() const;
    int GetMinimumHeight() const;
    int GetMaximumWidth() const;
    int GetMaximumHeight() const;

    void SetFlags(WindowFlags flags);
    WindowFlags GetFlags() const;
    WindowType GetType() const;

    WindowState GetWindowState() const;
    void SetWindowState(WindowState state);

    PlatformWindow* GetHandle() const;

    bool IsVisible() const;
    void SetVisible(bool visible);

    // Geometry functions
    void SetGeometry(int x, int y, int w, int h);
    void SetGeometry(const IntRect& rect);
    IntRect GetGeometry() const;

    // Positioning functions
    void SetPosition(const IntPoint& pnt);
    void SetPosition(int x, int y);
    IntPoint GetPosition() const;

    inline int GetWidth() const { return GetGeometry().GetWidth(); }
    inline int GetHeight() const { return GetGeometry().GetHeight(); }

    bool IsExposed() const;

    void SetSize(const Size& newSize);
    void SetSize(int w, int h);
    virtual Size GetSize() const;

    Screen* GetScreen() const;
    void SetScreen(Screen* pScreen);

    double GetDevicePixelRatio() const;

    void Destroy();
    void InquiryUpdate();
public:
    VSN_SIGNAL(Public, WindowStateModified, void WindowStateModified(WindowState windowState), windowState)
    VSN_SIGNAL(Public, VisibilityModified, void VisibilityModified(Window::VisibilityState visibility), visibility)
    VSN_SIGNAL(Public, WindowTitleModified, void WindowTitleModified(const String& title), title)
public:
    virtual PlatformRenderingArea* GetRenderingAreaHandle() const;
    virtual void Update();
    virtual void UpdateSelectionGL();
protected:
    Window(WindowPrivate& dd, Window* parent);
protected:
    virtual bool OnEvent(ProcessEvent* event);
    virtual void OnMouseLButtonDownEvent(MouseEvent* event);
    virtual void OnMouseLButtonUpEvent(MouseEvent* event);
    virtual void OnMouseRButtonDownEvent(MouseEvent* event);
    virtual void OnMouseRButtonUpEvent(MouseEvent* event);
    virtual void OnMouseMButtonDownEvent(MouseEvent* event);
    virtual void OnMouseMButtonUpEvent(MouseEvent* event);
    virtual void OnMouseMoveEvent(MouseEvent* event);
    virtual void OnShowEvent(ShowEvent* event);
    virtual void OnResizeEvent(ResizeEvent* event);
    virtual void OnExposeEvent(ExposeEvent* event);
    virtual bool OnNativeEvent(const String& eventType, void* message, long* result);
private:
    friend class BaseApplicationPrivate;
    friend class WinApplicationPrivate;
    VSN_DISABLE_COPY(Window);
    VSN_DECLARE_EX_PRIVATE(Window);
};

VSN_END_NAMESPACE

#endif // __VSN_WINDOW_H
