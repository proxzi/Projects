////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс OpenGLWindow представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class OpenGLWindow is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_OPENGLWINDOW_H
#define __VSN_OPENGLWINDOW_H

#include "vsn_drawdevicewindow.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class OpenGLWindowPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс OpenGLWindow представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class OpenGLWindow is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS OpenGLWindow : public DrawDeviceWindow
{
    VSN_OBJECT(OpenGLWindow)
public:
    explicit OpenGLWindow(Window* pParent = nullptr);
    virtual ~OpenGLWindow();
public:
    bool IsValid() const;
    void MakeCurrent();
    void DoneCurrent();
public:
    VSN_SIGNAL(Public, sigOpenGLSwapped, void sigOpenGLSwapped());
protected:
    virtual void InitOpenGL();
    virtual void DrawOpenGL();
    virtual void ResizeOpenGL(const Size& sz);
protected:
    OpenGLWindow(OpenGLWindowPrivate& dd, Window* pParent = nullptr);
protected:
    virtual void OnDrawEvent(DrawEvent* event) override;
    virtual void OnResizeEvent(ResizeEvent* event) override;
private:
    VSN_DISABLE_COPY(OpenGLWindow)
    VSN_DECLARE_EX_PRIVATE(OpenGLWindow)
};

VSN_END_NAMESPACE

#endif // __VSN_OPENGLWINDOW_H
