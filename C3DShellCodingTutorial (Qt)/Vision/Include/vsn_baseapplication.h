////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс BaseApplication представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class BaseApplication is a implementation of the window rendering using OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_BASEAPPLICATION_H
#define __VSN_BASEAPPLICATION_H

#include "vsn_namespace.h"
#include "vsn_object.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class PostEventList;
class BaseApplicationPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс BaseApplication представляет собой реализацию окна для отрисовки OpenGl'ем.
           \en Class BaseApplication is a implementation of the window rendering using OpenGL. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS BaseApplication : public Object
{
    VSN_OBJECT(BaseApplication)
public:
    explicit BaseApplication();
    virtual ~BaseApplication();
    static BaseApplication* GetInstance();
public:
    static String GetApplName();
    static void SetAppName(const String& text);
    static String GetApplVersion();
    static void SetApplVersion(const String& version);

    static int OnExec();
    static bool OnProcessSendEvent(Object* receiver, ProcessEvent* event);
    static void OnProcessPostEvent(Object* receiver, ProcessEvent* event, int priority = NormalEventPriority);
    static void OnProcessSendPostedEvents(Object* pReceiver = nullptr, int eventType = 0);
    static void OnProcessRemovePostedEvents(Object* pReceiver, int eventType = 0);
    static void OnExit(int retcode = 0);

    static bool IsQuitLockEnabled();
    static void SetQuitLockEnabled(bool bEnabled);
    static void SetAttribute(AppAttribute attribute, bool bOn = true);
    static bool IsCheckAttribute(AppAttribute attribute);
protected:
    virtual bool OnEvent(ProcessEvent* event) override;
    virtual bool OnProcessNotify(Object*, ProcessEvent*);
    virtual bool CompressEvent(ProcessEvent* pEvent, Object* pReceiver, PostEventList* pList);
public: // SLOTS
    static void OnQuit();
private:
    static bool SendSpontaneousEvent(Object* receiver, ProcessEvent* event);
    static bool NotifyInternal2(Object *receiver, ProcessEvent *);
protected:
    BaseApplication(BaseApplicationPrivate& d);
    void Initialization();
private:
    friend class WinApplication;
    friend class WinApplicationPrivate;
    OBVIOUS_PRIVATE_COPY(BaseApplication)
    VSN_DECLARE_EX_PRIVATE(BaseApplication)
};

VSN_END_NAMESPACE

#endif // __VSN_BASEAPPLICATION_H
