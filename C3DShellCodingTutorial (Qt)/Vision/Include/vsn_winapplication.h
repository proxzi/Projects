////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс WinApplication представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class WinApplication is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WINAPPLICATION_H
#define __VSN_WINAPPLICATION_H

#include "vsn_baseapplication.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Screen;
class Window;
class WinApplicationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс WinApplication представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class WinApplication is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS WinApplication : public BaseApplication
{
    VSN_OBJECT(WinApplication)
public:
    explicit WinApplication();
    virtual ~WinApplication();
public:
    static bool GetQuitOnLastWindowClosed();
    static void SetQuitOnLastWindowClosed(bool bQuit);
    static std::list<Window*> GetAllWindows();
    static std::list<Window*> GetTopLevelWindows();
    /// \ru Вернуть указатель на основной экранн (первый в списке). \en NO TRANSLATION.
    static Screen* GetFirstScreen();
    /// \ru Вернуть список всех экранов, связанных с оконнай системой приложения. \en NO TRANSLATION.
    static std::list<Screen*> GetScreens();
    double GetDevicePixelRatio() const;
protected:
    WinApplication(WinApplicationPrivate& d);
private:
    OBVIOUS_PRIVATE_COPY(WinApplication)
    VSN_DECLARE_EX_PRIVATE(WinApplication)
};

VSN_END_NAMESPACE

#endif // __VSN_WINAPPLICATION_H
