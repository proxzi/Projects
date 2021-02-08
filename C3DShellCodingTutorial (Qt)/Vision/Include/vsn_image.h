////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Image обеспечивает аппаратно-независимое изображение.
           \en Image class provides a device-independent image. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_IMAGE_H
#define __VSN_IMAGE_H

#include "vsn_global.h"
#include <iostream>
#include <string>

VSN_BEGIN_NAMESPACE

class ImagePrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс Image предоставляет инструменты для загрузки/сохранения разных форматов изображений.
            \en Image class provides tolls for loading/saving different image formats. \~
    \details \ru Класс Image обычно содержит несжатые данные изображения и является одним из объектов, 
                 которые могут быть загружены в текстуру. Как правило, объект Image используется для загрузки 
                 текстуры, когда необходимо выполнить дополнительную обработку изображения до его 
                 загрузки или когда вы хотите разбить существующую текстуру. Image имеет ряд полезных функций,
                 а также дает возможность прямого доступа к пикселям битовой карты изображения. \n
             \en Image class often contains uncompressed data of an image and is one of the objects that can be
                 uploaded to a texture. As a rule, Image object is used to load a texture, when it's necessary
                 to perform an additional processing of an image before its loading or when you want to split
                 the existing texture. Image has a set of useful functions and also gives an opportunity
                 of direct access to pixels of image bit map. \n \~
    \ingroup Vision_Image
*/
// ---
class VSN_CLASS Image
{
public:
    enum class Format
    {
        None, 
        //not compressed
        UINT8,  // 8 bit,  alpha
        UINT24, // 24 bit, RGB
        UINT32, // 32 bit, RGBA
        // compressed
        DXT1,
        DXT2,
        DXT3,
    };
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Image();
    /// \ru Конструктор перемещения. \en Move constructor. \~
    Image(Image&& image);
    /// \ru Конструктор копирования. \en Copy constructor. \~
    Image(const Image& image);

    /** \brief \ru Конструктор для чтения из потока.
               \en Constructor for reading from stream. \~
        \param[in] in - \ru Поток для чтения изображения.
                        \en Stream for reading image. \~
    */
    Image(std::istream& in);

    /// \ru Оператор копирования. \en Copy constructor. \~
    Image operator = (const Image &) = delete;

    /// \ru Деструктор. \en Destructor. \~
    virtual ~Image();
public:
    /// \ru Вернуть признак сжатого изображения. \en Returns flag of compressed image. \~
    bool IsCompressed() const;
    /// \ru Вернуть ширину изображения. \en Returns image width. \~
    uint GetWidth() const;
    /// \ru Вернуть высоту изображения. \en Returns image height. \~
    uint GetHeight() const;
    /// \ru Вернуть формат изображения. \en Returns image format. \~
    Format GetFormat() const;
    /// \ru Вернуть указатель на данные (может быть null). \en Returns pointer to data that can be null. \~
    unsigned char* GetBits() const;
    /// \ru Узнать, содержит ли изображение данные. \en Checks if image contains data. \~
    bool IsValid() const;
public:
    /** \brief \ru Загрузить изображение из файла.
               \en Loads image from file. \~
        \param[in] fileName - \ru Имя файла.
                              \en File name. \~
    */
    void Init(const std::string& fileName);

    /** \brief \ru Загрузить изображение из потока.
               \en Loads image from stream. \~
        \param[in] in - \ru Поток для чтения изображения.
                        \en Stream for reading image. \~
    */
    void Init(std::istream& in);

    /** \brief \ru Инициализировать Image параметрами.
               \en Initializes Image with parameters. \~
        \param[in] w - \ru Ширина изображения.
                       \en Image width. \~
        \param[in] h - \ru Высота изображения.
                       \en Image height. \~
        \param[in] f - \ru Формат изображения.
                       \en Image format. \~
        \param[in] mem - \ru Указатель на массив информации цветов.
                         \en Pointer to array of color info. \~
    */
    void Init( uint w, uint h, Format f, std::unique_ptr<unsigned char[]> mem );

    /** \brief \ru Инициализировать Image параметрами.
               \en Initializes Image with parameters. \~
        \param[in] w - \ru Ширина изображения. 
                       \en Image width. \~
        \param[in] h - \ru Высота изображения. 
                       \en Image height. \~
        \param[in] f - \ru Формат изображения. 
                       \en Image format. \~
        \param[in] mem - \ru Указатель на массив информации цветов. 
                         \en Pointer to array of color info. \~
    */
    void Init(uint w, uint h, Format f, const unsigned char* mem );

    /// \ru Инициализировать Image параметрами другого image. \en Initializes Image with parameters of another image. \~
    void Init(const Image& other);

    /** \brief \ru Сохранить изображение в поток (в формате PNG).
               \en Saves image in stream in PNG format. \~
        \param[in] out - \ru Ссылка на поток записи в формате PNG. 
                         \en Reference to PNG stream. \~
    */
    void SavePNG(std::ostream& out);

    /** \brief \ru Сохранить изображение в файл (в формате PNG).
               \en Saves image in stream in PNG format. \~
        \param[in] fileName - \ru Имя файла. 
                              \en File name. \~
    */
    void SavePNG(const std::string& fileName);

    /// \ru Удалить данные изображения. \en Deletes image data. \~
    void Clear();

    /** \brief \ru Создать копию изображения с другими размерами.
               \en Creates copy of image with other sizes. \~
               \param[in] sw - \ru Новое значение ширины. 
                               \en New width value. \~
               \param[in] sh - \ru Новое значение высоты. 
                               \en New height value. \~
    */
    Image Scale(uint sw, uint sh) const;

    /** \brief \ru Возвращает скопированную часть изображения.
               \en Returns copied image part. \~
               \param[in] x - \ru Позиция левой стороны нового изображения относительно левой стороны исходного.
                              \en Position of the left side of new image concerning the left side of initial one. \~
               \param[in] y - \ru Позиция нижней стороны нового изображения относительно нижней стороны исходного.
                              \en Position of the bottom side of new image concerning the bottom side of initial one. \~
               \param[in] w - \ru Ширина нового изображения.
                              \en New image width. \~
               \param[in] h - \ru Высота нового изображения.
                              \en New image height. \~
    */
    Image SubImage(uint x, uint y, uint w, uint h);
private:
    VSN_DECLARE_PRIVATE(Image);
};

VSN_END_NAMESPACE

#endif // __VSN_IMAGE_H
