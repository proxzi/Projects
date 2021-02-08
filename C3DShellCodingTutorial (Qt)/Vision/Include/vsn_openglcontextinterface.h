////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс OpenGLContextInterface представляет собой собственный контекст OpenGL,
             позволяющий рендеринг OpenGL в системном окне.
         \en OpenGLContextInterface class presents own OpenGL context allowing to render
             OpenGL in a system window. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_OPENGLCONTEXTINTERFACE_H
#define __VSN_OPENGLCONTEXTINTERFACE_H

#include <list>
#include <mb_matrix3d.h>
#include "vsn_renderingareaformat.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class OpenGLContextInterface;
class OpenGLContextContainerPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс OpenGLContextContainer является контейнером OpenGLContext.
           \en OpenGLContextContainer class is a OpenGLContext container. \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS OpenGLContextContainer
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    OpenGLContextContainer();
    /// \ru Деструктор. \en Destructor. \~
    ~OpenGLContextContainer();
public:
    /// \ru Вернуть указатель на OpenGLContextContainer, соответствующий текущему контексту. \en Returns pointer to OpenGLContextContainer corresponding to the current context. \~
    static OpenGLContextContainer* GetCurrentContextContainer();
public:
    /// \ru Вернуть список указателей на OpenGLContextInterface. \en Returns pointer list to OpenGLContextInterface. \~
    std::list<OpenGLContextInterface*> GetContextList() const;
    /// \ru Добавить новый контекст OpenGL. \en Adds new OpenGL context. \~
    void AddContext(OpenGLContextInterface* pCtx);
    /// \ru Удалить контекст OpenGL. \en Removes OpenGL context. \~
    void RemoveContext(OpenGLContextInterface* pCtx);
private:
    VSN_DECLARE_PRIVATE(OpenGLContextContainer)
};

class RenderingArea;
class OpenGLFunctionListInterface;
class OpenGLExtraFunctionListInterface;
class OpenGLContextInterfacePrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс OpenGLContextInterface представляет собой собственный контекст OpenGL 
               позволяющий рендеринг OpenGL в системном окне. \n
           \en OpenGLContextInterface class presents own OpenGL context allowing to render
               OpenGL in a system window. \~
    \details \ru OpenGLContextInterface представляет состояние OpenGL для базового контекста
                 OpenGL. Для создания контекста используйте функцию CreateOpenGLContext. Используйте
                 возвращаемое значение IsValid(), чтобы проверить был ли контекст успешно создан. 
                 Для установки режима активности контексту вызовите функцию MakeCurrent. Для обновлениея
                 кадра OpenGL необходимо вызвать SwapBuffers, что приведет к смене заднего и преднего
                 буфера для дальнейшей визуализации контента. Не забывайте делать вызов MakeCurrent 
                 перед началом рендера после каждого вызова SwapBuffers. \n
             \en OpenGLContextInterface class presents OpenGL state for the basic OpenGL context.
                 To create context, use CreateOpenGLContext function. Use returnable value IsValid() to
                 check if context was successfully created. To set an activity mode of context, call
                 MakeCurrent function. To update OpenGL frame, it's necessary to call SwapBuffers,
                 what will lead to swapping the back and forward buffer for the next content visualization.
                 Don't forget to make MakeCurrent call before starting a rendering after every calling SwapBuffers. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS OpenGLContextInterface
{
public:
    /// \ru Деструктор. \en Destructor.
    virtual ~OpenGLContextInterface();
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    OpenGLContextInterface();
public:
    /// \ru Создать OpenGL контекст и вернуть указатель на его интерфейс. \en Creates OpenGL context and returns pointer to its interface. \~
    static OpenGLContextInterface* CreateOpenGLContext(const RenderingAreaFormat& format);
public:
    /// \ru Делает текущий контекст указанной поверхности. Возвращает true, если успешно. \en Makes the current context of the specified surface. Returns true if successfully. \~
    virtual bool MakeCurrent();
    /// \ru Делает текущий контекст указанной поверхности. Возвращает true, если успешно. \en Makes the current context of the specified surface. Returns true if successfully. \~
    virtual bool MakeCurrent(RenderingArea* pFrame);
    /// \ru Функция для удобства делает вызов makeCurrent с 0 поверхностью. \en Function for comfort makes makeCurrent call with null surface. \~
    virtual void DoneCurrent();
    /// \ru Поменять задний и передний буферы указанной поверхности. \en Swaps the forward and back buffers of the specified surface. \~
    virtual void SwapBuffers();
    /// \ru Поменять задний и передний буферы указанной поверхности. \en Swaps the forward and back buffers of the specified surface. \~
    virtual void SwapBuffers(RenderingArea* pFrame);

    /// \ru Возвращает формат контекста, если контекст был создан с помощью функции Create(). \en Returns context format if context was created with Create() function. \~
    virtual RenderingAreaFormat GetFormat() const;
    /// \ru Установить формат контекста, если кортекст был создан с помощью функции Create(). \en Sets context format if context was created with Create() function. \~
    virtual void SetFormat(const RenderingAreaFormat& format);

    /// \ru Это перегруженная функция. Возвращает указатель на указанную функцию. \en It's an overloaded function. Returns pointer to the specified function. \~
    virtual OpenGLFunctionListInterface* GetFunctionList() const = 0;
    /// \ru Получить дополнительный экземпляр OpenGLExFunctionList для этого контекста. \en Returns additional OpenGLExFunctionList instance for this context. \~
    virtual OpenGLExtraFunctionListInterface* GetExtraFunctionList() const = 0;
    /// \ru Это перегруженная функция. Возвращает указатель на указанную функцию. \en It's an overloaded function. Returns pointer to the specified function.  \~
    virtual FunctionPtr GetProcAddress(const std::string& procName) const = 0;
    /// \ru Возвращает true, если этот контекст является действительным, т.е. был успешно создан. \en Returns true if this context is valid, i.e. it was successfully created. \~
    virtual bool IsValid() const = 0;
    /// \ru Возвращает объект фреймбуфера по умолчанию для текущей поверхности. \en Returns the default framebuffer object for the current surface. \~
    virtual uint GetDefaultFrameBufferObject() const = 0;
    /// \ru Возвращает указатель на экран для отрисовки OpenGL. \en Returns pointer to screen for rendering OpenGL. \~
    virtual RenderingArea* GetSurface() const;
    /// \ru Возвращает список расширенных контекстов этого контекста. \en Returns list of extended contexts of this context. \~
    virtual OpenGLContextContainer* GetContextContainer() const = 0;
    /// \ru Возвращает true, если контекст является контекстом OpenGL ES. \en Returns true if context is OpenGL ES context. \~
    virtual bool IsOpenGLES() const = 0;
    /// \ru Вернуть true, если контекст разделяется с другими GL контекстами. \en Returns true if context shares with other GL contexts. \~
    virtual bool IsSharing() const;
    /// \ru Проверить, поддерживает ли устройство конкретное расширение. \en Checks if device supports a concrete extension. \~
    bool IsSupportExtansion(const std::string & name) const;
    /// \ru Являются ли одинаковыми. \en If the same. \~
    static bool IsSame(const OpenGLContextInterface* pFirst, const OpenGLContextInterface* pSecond);
public:
    /// \ru Разрешено ли освещение. \en If lighting is allowed. \~
    bool IsAllowLighting() const;

    MbMatrix3D GetModelViewMatrix() const;
    MbMatrix3D GetProjectionMatrix() const;

    virtual void oglMatrixMode(uint mode);
    virtual void oglLoadIdentity();
    virtual void oglPushMatrix();
    virtual void oglPopMatrix();
    virtual void oglLoadMatrix(const MbMatrix3D& matrix);
    virtual void oglMultMatrix(const MbMatrix3D& matrix);
    virtual void oglOrtho(double left, double right, double bottom, double top, double nearVal, double farVal);
    virtual void oglFrustum(double left, double right, double bottom, double top, double nearVal, double farVal);
    virtual bool oglAllowLighting(bool bAllow);
    virtual void UpdateVariables();
public:
    /// \ru Возвращает последний контекст, который был установлен при вызове MakeCurrent или 0, если контекст не установлен.
    /// \en Returns last context that was set when calling MakeCurrent function or 0, if context is not set. \~
    static OpenGLContextInterface* GetCurrentContext();
public:
    static OpenGLContextInterface* m_pContextInterface;
protected:
    VSN_DECLARE_PRIVATE(OpenGLContextInterface)
};

VSN_END_NAMESPACE

#endif /* __VSN_OPENGLCONTEXTINTERFACE_H */
