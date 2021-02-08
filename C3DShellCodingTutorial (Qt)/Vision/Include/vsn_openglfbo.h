////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс OpenGLFramebufferObject инкапсулирует объект framebuffer OpenGL.
           \en OpenGLFramebufferObject class encapsulates framebuffer OpenGL object. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_OPENGLFRAMEBUFFER_H
#define __VSN_OPENGLFRAMEBUFFER_H

#include "vsn_global.h"
#include "vsn_size.h"
#include "vsn_image.h"

typedef unsigned int GLuint;

VSN_BEGIN_NAMESPACE

class OpenGLFramebufferObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru OpenGLFramebufferObject инкапсулирует объект framebuffer OpenGL.
           \en OpenGLFramebufferObject class encapsulates framebuffer OpenGL object. \~
    \details \ru OpenGLFramebufferObject представляет некую поверхность рендренга, на которой можно также и рисовать с помощью
                 вызовов функций OpenGL. Эта поверхность может быть привязана и использована, как обычная текстура в вашем
                 собственном коде для рисования OpenGL. По умолчанию класс OpenGLFramebufferObject генерирует 2D-текстуру
                 OpenGL и использует GL_TEXTURE_2D, которая используется внутри рендринга. При создании OpenGLFramebufferObject  
                 необходимо оперировать флагами depth и stencil, чтобы иметь правильное отображение. Чтобы примитивы отображались
                 сглаженными, необходимо при задании формата OpenGL установить SetSamples. \n.
             \en OpenGLFramebufferObject class presents some surface of rendering on which you can also render with calling
                 OpenGL functions. This surface can be linked and used as ordinary texture in your own code for rendering OpenGL.
                 OpenGLFramebufferObject class generates by default OpenGL 2D texture and uses GL_TEXTURE_2D used inside rendering.
                 When creating OpenGLFramebufferObject it's necessary to operate with depth and stencil flags to have a correct display.
                 To display primitives antialised, it's necessary to set SetSamples when setting OpenGL format. \n \~
    \note    \ru При создании объекта OpenGLFramebuffer важно иметь текущий контекст OpenGL, иначе инициализация завершится неудачно.
             \en When creating OpenGLFramebuffer object, it's important to know the current OpenGL context. Otherwise initialization will fail. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class VSN_CLASS OpenGLFramebufferObject
{
public:
    /** \brief \ru Конструктор.
               \en Constructor. \~
        \param[in] width - \ru Ширина.
                           \en Width. \~
        \param[in] height - \ru Высота.
                            \en Height. \~
        \param[in] multisample - \ru Уровень сглаживания.
                                 \en Level of antialiasing. \~
        \param[in] depth - \ru Создавать буфер глубины или нет.
                           \en Creates depth buffer or not. \~
        \param[in] stencil - \ru Создавать буфер трафарета или нет.
                             \en Creates stencil buffer or not. \~
    */
    OpenGLFramebufferObject(int width, int height, int multisample = 0, bool depth = false, bool stencil = false);
    /** \brief \ru Конструктор.
               \en Constructor. \~
        \param[in] size - \ru Размеры буфера.
                          \en Buffer size. \~
        \param[in] multisample - \ru Уровень сглаживания.
                                 \en Level of antialiasing. \~
        \param[in] depth - \ru Создавать буфер глубины или нет.
                           \en Creates depth buffer or not. \~
        \param[in] stencil - \ru Создавать буфер трафарета или нет.
                             \en Creates stencil buffer or not. \~
    */
    OpenGLFramebufferObject(const Size& size, int multisample = 0, bool depth = false, bool stencil = false);
    /// \ru Деструктор. \en Destructor. 
    virtual ~OpenGLFramebufferObject();
public:
    /// \ru Привязать Framebuffer. \en Binds Framebuffer. \~
    void Bind();
    /// \ru Oтвязать Framebuffer. \en Releases Framebuffer. \~
    void Release();
    /// \ru Изменить размеры. \en Changes sizes. \~
    void Update(int width, int height);
    /// \ru Получить ширину Framebuffer. \en Returns Framebuffer width. \~
    int  GetWidth() const;
    /// \ru Получить высоту Framebuffer. \en Returns Framebuffer height. \~
    int  GetHeight() const;
    /// \ru Проверить состояние буфера. \en Checks buffer state. \~
    bool IsValid() const;
    /// \ru Сохранить в image. \en Saves in image. \~
    Image MakeImage();
    /// \ru Перекладывает содержимое буфера в текстуру (текстуру удалять не нужно). \en Makes texture from buffer content. Texture doesn't need to be deleted. \~
    GLuint MakeTexture() const;
    /// \ru Отобразить содержимое буфера в заданном прямоугольнике. \en Displays buffer content in given rectangle. \~
    void RenderImage(float left, float bottom, float width, float height);
private:
    VSN_DECLARE_PRIVATE(OpenGLFramebufferObject)
    VSN_DISABLE_COPY(OpenGLFramebufferObject)
};

VSN_END_NAMESPACE

#endif /*__VSN_OPENGLFRAMEBUFFER_H*/
