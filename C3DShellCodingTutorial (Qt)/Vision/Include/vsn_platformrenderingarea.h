////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс PlatformRenderingArea обеспечивает абстракцию для поверхности.
           \en PlatformRenderingArea class provides abstraction for surface. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PLATFORMRENDERINGAREA_H
#define __VSN_PLATFORMRENDERINGAREA_H

#include "vsn_string.h"
#include "vsn_rect.h"
#include "vsn_fields.h"
#include "vsn_namespace.h"
#include "vsn_renderingarea.h"
#include "vsn_renderingareaformat.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
/** \brief \ru Класс PlatformRenderingArea обеспечивает абстракцию для поверхности.
            \en PlatformRenderingArea class provides abstraction for surface. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS PlatformRenderingArea
{
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit PlatformRenderingArea(RenderingArea* pRenderingArea);
public:
    /// \ru Деструктор. \en Destructor.
    virtual ~PlatformRenderingArea();
public:
    virtual void* GetWindowId() const { return 0; }
    virtual RenderingAreaFormat GetFormat() const = 0;
    virtual void InvalidateRenderingArea();
public:
    /// \ru Вернуть указатель на поверхность отрисовки. \en Returns pointer to rendering surface.
    RenderingArea* GetRenderingArea() const;
private:
    RenderingArea* m_pRenderingArea;
    friend class PlatformWindow;
    friend class PlatformOffscreenSurface;
};

class Window;
class PlatformScreen;
class PlatformWindowPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PlatformRenderingArea обеспечивает абстракцию для поверхности.
           \en PlatformRenderingArea class provides abstraction for surface. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS PlatformWindow : public PlatformRenderingArea
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit PlatformWindow(Window* pWindow = nullptr);
    /// \ru Деструктор. \en Destructor.
    virtual ~PlatformWindow();
public:
    Window* GetWindow() const;
    PlatformWindow* GetParent() const;
    PlatformScreen* GetScreen() const;
public:
    virtual void SetVisible(bool visible);
    virtual void SetWindowFlags(WindowFlags flags);
    virtual void SetWindowState(WindowState state);
    virtual bool IsEmbedded(const PlatformWindow* parentWindow = nullptr) const;
    virtual bool IsExposed() const;
    virtual RenderingAreaFormat GetFormat() const override;
    virtual void SetWindowTitle(const String& title);
    virtual void SetGeometry(const IntRect& rect);
    virtual IntRect GetGeometry() const;

    virtual Fields GetFrameFields() const;
    virtual double GetDevicePixelRatio() const;
    virtual void InquiryUpdate();
public:
    static String FormatTitleText(const String& title, const String& separator);
    static IntRect OriginalGeometry(const Window* pWindow, const IntRect& initialGeometry, int defaultWidth, int defaultHeight);
protected:
    PlatformScreen* GetScreenForGeometry(const IntRect& newGeometry) const;
private:
    VSN_DECLARE_PRIVATE(PlatformWindow)
};


VSN_END_NAMESPACE

#endif /* __VSN_PLATFORMRENDERINGAREA_H */
