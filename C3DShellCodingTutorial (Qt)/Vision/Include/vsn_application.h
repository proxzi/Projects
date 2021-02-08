////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Application представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Application is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_APPLICATION_H
#define __VSN_APPLICATION_H

#include "vsn_winapplication.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class ApplicationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Application представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class Application is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS Application : public WinApplication
{
    VSN_OBJECT(Application)
public:
    explicit Application();
    virtual ~Application();
public:
    static int OnExec();
protected:
    virtual bool OnProcessNotify(Object* pObject, ProcessEvent* pEvent) override;
private:
    OBVIOUS_PRIVATE_COPY(Application)
    VSN_DECLARE_EX_PRIVATE(Application)
};

VSN_END_NAMESPACE

#endif // __VSN_APPLICATION_H
