////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс Texture2D для обработки 2D-текстур. Используется для создания 
             текстур "на лету" или для изменения существующих текстурных ресурсов.
         \en Texture2D class is for processing 2D textures. The class is used
             to create textures on the fly or to change the existing texture resources. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_TEXTURE2D_H
#define __VSN_TEXTURE2D_H

#include <vsn_string.h>
#include <vsn_global.h>
#include <vsn_size.h>
#include <vsn_image.h>
#include <vsn_namespace.h>
#include <string>

VSN_BEGIN_NAMESPACE

class OpenGLContextInterface;
class Texture2DPrivate;
class Image;

//------------------------------------------------------------------------------
/** \brief \ru Класс Texture2D для обработки 2D-текстур. Используется для создания текстур "на лету" 
               или для изменения существующих текстурных ресурсов. 
           \en Texture2D class is for processing 2D textures. The class is used to create textures
               on the fly or to change the existing texture resources. \~
           \details \ru Обычная поверхностная сетка геометрии объекта дает грубое приближение формы, в то время 
                        как большая часть мелких деталей представляется текстурой. Texture2D - это стандартное 
                        растровое изображение, которое накладывается на поверхностную сетку. Вы можете придумать 
                        изображение текстуры, как если бы оно было напечатано на "резиновом листе", способном 
                        растягиваться и закрепляться на этой сетке в соответствующих положениях. Позиционирование 
                        текстуры выполняется с помощью программного обеспечения математического ядра, которое 
                        используется для создания поверхностной сетки.
                        Texture2D может импортировать текстуры из наиболее распространенных форматов файлов изображений,
                        т.е. те форматы, которые поддерживает, например, Vision::Image.
                        Texture2D обладает рядом полезных функций. Texture2D можно инициализировать двумя способами: 
                        используя image или битовую карту, кроме того, имеется возможность конвертировать текстуру 
                        в Vision::Image. \n
                    \en The ordinary surface mesh of object geometry gives a rough approximation of a form,
                        while most of minutiae is presented as a texture. Texture2D is a standard bitmap
                        image that is applied to a surface mesh. You can think of a texture image, as if it would
                        be printed on "rubber sheet" able to stretch and be fixed to this mesh in corresponding positions.
                        Positioning a texture is performed with the software of math kernel that is used to create a surface
                        mesh.
                        Texture2D can import textures from most common file formats of images, i.e. those formats
                        supported by, for example, Vision::Image.
                        Texture2D has a set of useful functions. Texture2D can be initialized in two ways:
                        using image or bit map, besides, there is a capability to convert a texture to Vision::Image. \n \~
*/
// ---
class VSN_CLASS Texture2D
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Texture2D();
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Texture2D(const Texture2D& other);
    /// \ru Конструктор для загрузки текстуры из Image. \en Constructor for loading texture from Image. \~
    Texture2D(const Image& image);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~Texture2D();
public:
    /// \ru Активировать текстуру. \en Activates texture. \~
    void OGLBindTexture();
public:
    /// \ru Инициализировать, используя Image. \en Initializes using Image. \~
    void  Init(const Image& image);
    /// \ru Инициализировать, используя битовую карту. \en Initializes using bit map. \~
    void  Init(TextureFormat format, Size size, const unsigned char * pBits);
    /// \ru Вернуть ширину текстуры. \en Returns texture width. \~
    uint  GetWidth() const;
    /// \ru Вернуть высоту текстуры. \en Returns texture height. \~
    uint  GetHeight() const;
    /// \ru Вернуть идентификатор текстуры. \en Returns texture identifier. \~
    uint  GetUniqueKey() const;
    /// \ru Узнать о наличии альфа-канала. \en Checks if alpha channel exists. \~
    bool HasAlphaChannel() const;
    /// \ru Узнать состояние текстуры. \en Checks texture state. \~
    bool IsLoaded() const;
    /// \ru Конвертировать в Image. \en Converts to Image. \~
    Image ToImage() const;
public: // texture parameters
    /// \ru Задать фильтры растеризации. \en Sets rasterization filters. \~
    void SetFilters(TextureFilter min, TextureFilter max);
    /// \ru Задать значение анизотропного фильтра. \en Sets value of anisotropic filter. \~
    void SetAnisotropic(float value);
    /// \ru Задать параметры повтора текстуры. \en Sets parameters of texture repeat. \~
    void SetWrap(TextureWrap s, TextureWrap t);
public:
    /// \ru Вернуть максимальное значение анизотропного фильтра. \en Returns maximum value of anisotropic filter. \~
    static float GetMaxAnisotropic();
    /// \ru Вернуть максимальный размер текстуры. \en Returns maximum texture size. \~
    static Size  GetMaxTextureSize();
public:
    /// \ru Оператор копирования. \en Copy operator. \~
    Texture2D& operator = (const Texture2D& other);
    /// \ru Оператор тождества. \en Assignment operator. \~
    bool operator == (const Texture2D& other) const;
private:
    VSN_DECLARE_PRIVATE(Texture2D)
};
VSN_END_NAMESPACE



#endif /* __VSN_TEXTURE2D_H */
