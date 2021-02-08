///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс RenderingAreaFormat представляет собой формат RenderingArea.
         \en RenderingAreaFormat class represents RenderingArea format. \~

*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GLSURFACEFORMAT_H
#define __VSN_GLSURFACEFORMAT_H

#include <utility>
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class RenderingAreaFormatPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс RenderingAreaFormat представляет собой формат RenderingArea.
           \en RenderingAreaFormat class represents RenderingArea format. \~
  \details \ru Формат включает в себя размер буферов цвета: красного, зеленого и синего; размер альфа-буфера; 
               размер глубины и трафаретов, а также число пикселей для сглаживания изображения(multisampling). 
               Кроме того, формат содержит параметры конфигурации поверхности, такие как настройка OpenGL и его версию. 
               Включен ли буфер стереорежима. \n
           \en Format includes color buffer size: red, green and blue; alpha buffer size;
               size of depth and stencil buffers, and also pixel count for multisampling.
               Besides, format contains such surface configuration parameters as OpenGL settings and its version.
               Checks if stereo mode buffer is enabled. \n \~
*/
// ---
class VSN_CLASS RenderingAreaFormat
{
public:
    enum FormatOption 
    {
        StereoBuffers            = 0x0001, // not implemented
        DebugContext             = 0x0002, // not implemented
        DeprecatedFunctions      = 0x0004, // not implemented
        ResetNotification        = 0x0008  // not implemented
    };

    enum SwapBehavior 
    {
        DefaultSwapBehavior,
        SingleBuffer,         // not implemented
        DoubleBuffer,         // not implemented 
        TripleBuffer          // not implemented
    };

    enum OpenGLContextProfile 
    {
        NoProfile,
        KernelProfile,        // not implemented
        CompatibilityProfile  // not implemented
    };

    enum RenderableType 
    {
        DefaultRenderableType = 0x0,
        OpenGL                = 0x1,
        OpenGLES              = 0x2, // not implemented
        OpenVG                = 0x4  // not implemented
    };

public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    RenderingAreaFormat();
    /// \ru Конструктор c заданным форматом. \en Constructor with set format.
    RenderingAreaFormat(uint8 formatOptions);
    /// \ru Конструктор копирования. \en Copy constructor.
    RenderingAreaFormat(const RenderingAreaFormat& other);
    RenderingAreaFormat &operator = (const RenderingAreaFormat& other);
    ~RenderingAreaFormat();

public:
    /// \ru Вернуть размер буфера глубины. \en Returns depth buffer size.
    int GetDepthBufferSize() const;
    /// \ru Установить минимальный размер буфера глубины. \en Sets the minimum depth buffer size.
    void SetDepthBufferSize(int size);

    /// \ru Вернуть размер буфера трафарета в битах. \en Returns stencil buffer size in bits.
    int GetStencilBufferSize() const;
    /// \ru Установить размер буфера трафарета в битах. \en Sets stencil buffer size in bits.
    void SetStencilBufferSize(int size);

    /// \ru Вернуть размер буфера красного цвета в битах. \en Returns the size of red color buffer in bits.
    int GetRedBufferSize() const; 
    /// \ru Установить размер буфера красного цвета в битах. \en Sets the size of red color buffer in bits.
    void SetRedBufferSize(int size);

    /// \ru Вернуть размер буфера зеленого цвета в битах. \en Returns the size of green color buffer in bits.
    int GetGreenBufferSize() const;
    /// \ru Установить размер буфера зеленого цвета в битах. \en Sets the size of green color buffer in bits.
    void SetGreenBufferSize(int size);

    /// \ru Вернуть размер буфера синего цвета в битах. \en Returns the size of blue color buffer in bits.
    int GetBlueBufferSize() const;
    /// \ru Установить размер буфера синего цвета в битах. \en Sets the size of blue color buffer in bits.
    void SetBlueBufferSize(int size);

    /// \ru Вернуть размер альфа канала буфера цвета в битах. \en Returns the size of alpha channel of color buffer in bits.
    int GetAlphaBufferSize() const;
    /// \ru Установить размер альфа канала буфера цвета в битах. \en Sets the size of alpha channel of color buffer in bits.
    void SetAlphaBufferSize(int size);

    /// \ru Вернуть количество пикселей для сглаживания изображения(multisampling). По умолчанию сглаживание(multisampling) отключено. \en Returns pixel count for multisampling. Multisampling is disabled by default.
    int GetSamples() const;

    /** \brief \ru Установить желаемое количество пикселей для сглаживания изображения(multisampling).
               \en Sets the preferred pixel count for multisampling. \~

      \details \ru Если numSamples не равен 0, то сглаживание включено. По умолчанию сглаживание отключено.
               \en Checks if numSamples is not 0, that is multisampling enabled. Multisampling is disabled by default. \~
      \param[in] numSamples - \ru Количество пикселей.
                              \en Pixel count. \~
    */
    void SetSamples(int numSamples);

    /// \ru Вернуть поведение подкачки поверхности. \en Returns the swap behavior of the surface.
    SwapBehavior GetSwapBehavior() const;         // not implemented
    /// \ru Установить поведение подкачки поверхности. \en Sets the swap behavior of the surface.
    void SetSwapBehavior(SwapBehavior behavior);  // not implemented

    /// \ru Вернуть интервал подкачки. \en Returns the swap interval.
    int GetSwapInterval() const;                  // not implemented

    /** \brief \ru Установить интервал подкачки.
               \en Sets the swap interval. \~

      \details \ru Интервал определяет минимальное количество смены видеокадров. Он может быть использован для синхронизации swap buffer OpenGL для отображения в окне,
                  т.е. интервал имеет отношение к вертикальной синхронизации экрана. По умолчанию интервал равен 1.
               \en Interval defines the minimum count of video frames. It can be used for OpenGL swap buffer synchronization for rendering in window,
                   i.e. interval is related to vertical sync of the screen. The default interval value is 1. \~
      \param[in] interval - \ru Интервал.
                            \en Interval. \~
    */
    void SetSwapInterval(int interval);           // not implemented

    /// \ru Вернуть true, если размер альфа буфера не равен нулю (Это означает, что поверхность может использовать полупрозрачные эффекты). \en True if alpha buffer size is not 0. It means that surface can be used with transparent effects.
    bool IsAlpha() const;

    /// \ru Вернуть тип визуализации. \en Returns visualization type.
    RenderableType GetRenderableType() const;
    /// \ru Установить тип визуализации. \en Sets visualization type.
    void SetRenderableType(RenderableType type);

    /// \ru Вернуть конфигурацию профиля контекста OpenGL. /note Этот параметр игнорируется, если запрашиваемая версия OpenGL ниже 3.2. \en Returns OpenGL context profile configuration. /note The parameter is ignored if requested OpenGL version is under 3.2. 
    OpenGLContextProfile GetProfile() const;
    /// \ru Установить конфигурацию профиля контекста OpenGL. /note Этот параметр игнорируется, если запрашиваемая версия OpenGL ниже 3.2. \en Sets OpenGL context profile configuration. /note The parameter is ignored if requested OpenGL version is under 3.2.
    void SetProfile(OpenGLContextProfile profile);

    /// \ru Вернуть мажорную версию OpenGL (по умолчанию версия 2.0). \en Returns OpenGL major version. The default version is 2.0.
    int GetMajorVersion() const;                 // not implemented
    /// \ru Установить мажорную версию OpenGL(по умолчанию версия 2.0). \en Sets OpenGL major version. The default version is 2.0.
    void SetMajorVersion(int majorVersion);      // not implemented 

    /// \ru Вернуть минорную версию OpenGL. \en Returns OpenGL minor version.
    int GetMinorVersion() const;                 // not implemented  
    /// \ru Установить минорную версию OpenGL. \en Sets OpenGL minor version.
    void SetMinorVersion(int minorVersion);      // not implemented

    // \ru Вернуть std::pair<int, int> версию OpenGL. \en Returns OpenGL std::pair<int, int> version.
    std::pair<int, int> GetVersion() const;      // not implemented   
    // \ru Установить std::pair<int, int> версию OpenGL. \en Sets OpenGL std::pair<int, int> version.
    void SetVersion(int major, int minor);       // not implemented

    bool IsEnabledStereo() const;           // not implemented
    void SetEnabledStereo(bool enable);     // not implemented

    /// \ru Установить новые опции формата. \en Sets new format options.
    void SetOptions(uint8 formatOptions);
    /// \ru Устанавливает параметр формата. Если true, включить FormatOption, в противном случае выключить. \en Sets format option. If True, turns FormatOption on. 
    void SetOption(FormatOption option, bool on = true);

    /// \ru Вернуть true, если опция формата была установлена, в противном случае возвращает false. \en True if format option is set.
    bool CheckOption(FormatOption option) const;
    /// \ru Вернуть текущие параметры формата. \en Returns the current format options.
    uint8 GetOptions() const;

    // \ru Вернуть формат поверхности по умолчанию. \en Returns the default surface format.
    static RenderingAreaFormat GetDefaultFormat();
    // \ru Установить формат поверхности по умолчанию. \en Sets the default surface format.
    static void SetDefaultFormat(const RenderingAreaFormat& format);

protected:
    VSN_DECLARE_PRIVATE(RenderingAreaFormat)

private:
    friend VSN_FUNC_EX bool operator==(const RenderingAreaFormat&, const RenderingAreaFormat&);
    friend VSN_FUNC_EX bool operator!=(const RenderingAreaFormat&, const RenderingAreaFormat&);
};

// \ru Вернуть true, если варианты двух объектов формата RenderingArea равны.  \en True if options of two objects in RenderingArea format are equal.
VSN_FUNC_EX bool operator==(const RenderingAreaFormat&, const RenderingAreaFormat&);
// \ru Вернуть false, если все варианты двух объектов формата RenderingArea не равны, в противном случае возвращает true. \en False if all options of two objects in RenderingArea format are not equal.
VSN_FUNC_EX bool operator!=(const RenderingAreaFormat&, const RenderingAreaFormat&);

VSN_END_NAMESPACE

#endif /* __VSN_GLSURFACEFORMAT_H */
