////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс GeomFTTextObject генерирует строку текста для вывода ее на экран.
         \en GeomFTTextObject class generates text string for outputting on the screen. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_TEXTSAMPLES_H
#define __VSN_TEXTSAMPLES_H

#include "vsn_meshgeometry.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

class GeomFTTextObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс GeomFTTextObject генерирует строку текста для вывода ее на экран.
           \en GeomFTTextObject class generates text string for outputting on the screen. \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS GeomFTTextObject : public WireframeGeometry 
{
public:
    /**
        \brief \ru Специальный конструктор для чтения шрифта из файла.
                \en Special constructor for reading text font from the file. \~
        \details \ru Специальный конструктор необходим для чтения шрифта из файла, а также установки флага ошибки.
                    \en Special constructor is needed for reading text font from the file and setting error flag. \~
        \param[in] fontFilePath - \ru Путь к файлу шрифта.
                                    \en Font file path. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~

    */
    GeomFTTextObject(const char* fontFilePath, Node* pParent = nullptr);
    /// \ru Конструктор по умолчанию. \en Default constructor.
    /**
        \brief \ru Специальный конструктор для чтения шрифта из буфера памяти.
                \en Special constructor for reading text font from memory buffer. \~
        \details \ru Специальный конструктор необходим для чтения шрифта из буфера памяти, а также установки флага ошибки.
                        Буфер принадлежит пользователю и не копируется. Указатель должен быть действителен для использования.
                 \en Special constructor is needed for reading text font from memory buffer and setting error flag.
                     Buffer cannot be copied. It belongs to user. Pointer must be valid for use. \~
        \param[in] pBufferBytes - \ru Указатель на буфер данных.
                                  \en A pointer to data buffer. \~
        \param[in] bufferSizeInBytes - \ru Длина буфера в байтах.
                                       \en Buffer length in bytes. \~
        \param[in] pParent - \ru Указатель на родительский объект.
                             \en A pointer to parent. \~
    */
    GeomFTTextObject(const unsigned char* pBufferBytes, size_t bufferSizeInBytes, Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~GeomFTTextObject();

public:
    /// \ru Вернуть текст. \en Returns text. 
    std::wstring GetText() const;
    /// \ru Установить текст. \en Sets text. 
    void SetText(const std::wstring& text);

    /// \ru Вернуть цвет текста. \en Returns text color. 
    Color GetColorText() const;
    /// \ru Установить цвет текста. \en Sets text color. 
    void SetColorText(const Color& clrText);

    /// \ru Вернуть максимальную длину строки для форматированного текста. \en Returns the maximum string length for formatted text.
    /**
        \return \ru Текущая длина строки. \en The current string length. \~
    */
    float GetLineLength() const;
    /// \ru Максимальная длина строки для форматированного текста. \en The maximum string length for formatted text.
    /**
        \param[in] lineLength - \ru Новая длина строки. \en New string length. \~
    */
    void SetLineLength(float lineLength);

    /// \ru Вернуть текущий размер шрифта в точках(1/72 дюйма). \en Returns the current font size in points (1/72 inch).
    /**
        \return \ru Размер шрифта. \en Font size. \~
    */
    uint GetFaceSize() const;

    /// \ru Установить размер символа для текущего шрифта. \en Sets symbol size for the current font.
    /**
        \param[in] size - \ru Размер шрифта в точках (1/72 дюйма). \en Font size in points (1/72 inch). \~
        \param[in] res  - \ru Разрешение устройства. \en Device resolution. \~
        \return \ru True, если размер установлен корректно. \en True if font size is correctly set. \~
    */
    bool SetFaceSize(uint size, uint res = 72);

    /// \ru Вернуть ограничивающий прямоугольник отформатированной строки. \en Returns bounding box of formatted string.
    /**
        \param[in] string - \ru Строка. \en String. \~
        \param[in] len - \ru Длина строки. \en String length. \~
        \param[in] position - \ru Позиция пера для первого символа. \en Pen position for the first symbol. \~
        \return \ru Соответствующий ограничивающий прямоугольник. \en The corresponding bounding box. \~
    */
    MbCube GetFormattedBoundingBox(const wchar_t* string, int len = -1, MbCartPoint3D position = MbCartPoint3D()) const;

    /// \ru Вернуть ограничивающий прямоугольник строки. \en Returns string bounding box.
    /**
        \param[in] string - \ru Строка. \en String. \~
        \param[in] len - \ru Длина строки. \en String length. \~
        \param[in] position - \ru Позиция пера для первого символа. \en Pen position for the first symbol. \~
        \param[in] spacing - \ru Вектор смещения для каждого символа. \en Offset vector for each symbol. \~
        \return \ru Соответствующий ограничивающий прямоугольник. \en The corresponding bounding box. \~
    */
    MbCube GetBoundingBox(const wchar_t* string, int len = -1, MbCartPoint3D position = MbCartPoint3D(), MbCartPoint3D spacing = MbCartPoint3D()) const;
    
    /// \ru Вернуть ограничивающий прямоугольник для символа. \en NOT TRANSLATED.
    /**
       \return \ru Соответствующий ограничивающий прямоугольник. \en The corresponding bounding box. \~
    */
    MbCube GetBoxCharacter();

    /// \ru Установило положение. \en NOT TRANSLATED.
    /**
        \param[in] val - \ru положение. \en position. \~
    */
    void SetPosition(const MbCartPoint3D& val);
    /// \ru Вернуть положение. \en NOT TRANSLATED.
    /**
        \return \ru Положение \en position. \~
    */
    const MbCartPoint3D& GetPosition() const;
    /// \ru Установить отступы для ограничевающего прямоугольника. \en NOT TRANSLATED.
    /**
       \param[in] v - \ru значение оступа. \en NOT TRANSLATED. \~
    */
    void SetBoxLineSpacing(double v);
    
public:
    /// \ru Выдать габаритный куб. \en Returns bounding box.
    virtual const MbCube& GetBoundingBox();
    /// \ru Является ли объект пустым. \en Checks if object is empty.
    bool isEmpty() const;

public:
    /// \ru Очистить содержимое и сделать его пустым. \en Clears content and makes it empty.
    void Clear();
    /// \ru Оператор копирования. \en Copy operator.
//    GeomFTTextObject& operator = ( const GeomFTTextObject& other );

protected:
    /// \ru Отрисовать текст. \en Renders text.
    virtual void OpenGLDraw(const RenderState& state) override;
private:
  VSN_DECLARE_PRIVATE(GeomFTTextObject)
};


VSN_END_NAMESPACE


#endif /* __VSN_TEXTSAMPLES_H */
