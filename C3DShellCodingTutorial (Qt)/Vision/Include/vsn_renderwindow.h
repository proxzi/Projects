////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс RenderWindow представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class RenderWindow is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_RENDERWINDOW_H
#define __VSN_RENDERWINDOW_H

#include "vsn_window.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Camera;
class Essence;
class SceneContent;
class ForwardRenderer;
class RenderWindowPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс RenderWindow представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class RenderWindow is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS RenderWindow : public Window
{
    VSN_OBJECT(RenderWindow)
public:
    explicit RenderWindow(Window* pParent = nullptr);
    virtual ~RenderWindow();
public:
    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    SceneContent* GetSceneContent() const;
    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    ForwardRenderer* GetDefaultForwardRenderer() const;
    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    Camera* GetCamera() const;
    /// \ru NO TRANSLATION. \en NO TRANSLATION.
    void SetTopAnything(Essence* pTopAnything);

protected:
    virtual void OnShowEvent(ShowEvent* event);
    virtual void OnResizeEvent(ResizeEvent* event);
private:
    friend class BaseApplicationPrivate;
    friend class RenderThread;
    VSN_DISABLE_COPY(RenderWindow)
    VSN_DECLARE_EX_PRIVATE(RenderWindow)
};

VSN_END_NAMESPACE

#endif // __VSN_RENDERWINDOW_H
