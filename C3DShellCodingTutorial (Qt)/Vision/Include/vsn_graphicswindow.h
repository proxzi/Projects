////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRAPHICSWINDOW_H
#define __VSN_GRAPHICSWINDOW_H

#include "vsn_openglwindow.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Process;
class Viewport;
class SceneContent;
class GraphicsScene;
class GraphicsWindowPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Window представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Window is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS GraphicsWindow : public OpenGLWindow
{
    VSN_OBJECT(GraphicsWindow)
public:
    explicit GraphicsWindow(Window* pParent = nullptr);
    virtual ~GraphicsWindow();
public:
    /// \ru Вернуть указатель графическую сцену. \en NO TRANSLATION.
    GraphicsScene* GetGraphicsScene() const;
    /// \ru Вернуть указатель на сцену. \en NO TRANSLATION.
    std::shared_ptr<SceneContent> GetSceneContent();
    /// \ru Вернуть указатель на Viewport. \en NO TRANSLATION.
    Viewport* GetViewport() const;
    // Вернуть и обновление глобальный ограничивающий куб
    MbCube GetGlobalBoundingBox();
protected:
    virtual void DrawOpenGL();
protected:
    virtual void ResizeOpenGL(const Size& sz);
protected:
    virtual void OnMouseLButtonDownEvent(MouseEvent* event) override;
    virtual void OnMouseLButtonUpEvent(MouseEvent* event) override;
    virtual void OnMouseMButtonDownEvent(MouseEvent* event) override;
    virtual void OnMouseMButtonUpEvent(MouseEvent* event) override;
    virtual void OnMouseMoveEvent(MouseEvent* event) override;
private:
    OBVIOUS_PRIVATE_COPY(GraphicsWindow)
    VSN_DECLARE_EX_PRIVATE(GraphicsWindow)
};

VSN_END_NAMESPACE

#endif // __VSN_GRAPHICSWINDOW_H
