////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Color определяет цвет на основе значений RGB, HSV или CMYK.
           \en Color class defines color based on RGB, HSV, or CMYK values. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_COLOR_H
#define __VSN_COLOR_H

#include <system_types.h>
#include "vsn_global.h"

typedef unsigned short ushort;
typedef uint32 COLORREF;

typedef unsigned int vRgb;     // RGB triplet

inline vRgb vsn_Rgba(int r, int g, int b, int a)// set RGBA value
{
    return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

//------------------------------------------------------------------------------
// \ru Дать значение красного цвета в пределах от 0 до 255. \en Returns red color value in the range from 0 to 255. 
// ---
inline uint8 rValue(COLORREF rgb_color)
{
    return (uint8)(rgb_color);
}

//------------------------------------------------------------------------------
// \ru Дать значение зелёного цвета в пределах от 0 до 255. \en Returns green color value in the range from 0 to 255. 
// ---
inline uint8 gValue(COLORREF rgb_color)
{
    return (uint8)(rgb_color >> 8);
}

//------------------------------------------------------------------------------
// \ru Дать значение синего цвета в пределах от 0 до 255. \en Returns blue color value in the range from 0 to 255. 
// ---
inline uint8 bValue(COLORREF rgb_color)
{
    return (uint8)(rgb_color >> 16);
}


VSN_BEGIN_NAMESPACE
class ColorPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс Color определяет цвет на основе значений RGB или HSV, или CMYK.
           \en Color class defines color based on RGB or HSV, or CMYK values. \~
    \details \ru Цвет обычно определяется в терминах RGB (красный, зеленый и синий) компонентов, но его также можно задать с помощью HSV (оттенок, насыщенность и значение)
                 или CMYK(голубой, пурпурный, желтый и черный) компонентов. Кроме того, цвет может быть определен с помощью названия цвета. \n
             \en Color is often determined in terms of RGB components (red, green and blue), but it can also be set with HSV components (hue, saturation and value)
                 or CMYK components (cyan, magenta, yellow and key color, or black). Besides, color can be determined using the color name. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS Color
{
public:
    /// \ru Перечисление установок типов цветов. \en Enumeration of settings color types.
    enum ColorType
    {
        Invalid,
        Rgb,
        Hsv,
        Cmyk,
        Hsl
    };

public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    Color();
    /// \ru Специальный конструктор для задания всех компонентов. \en Special constructor for setting all components.
    Color(int red, int green, int blue, int alpha = 255);
    /// \ru Специальный конструктор для задания всех компонентов. \en Special constructor for setting all components.
    Color(float red, float green, float blue, float alpha = 1.0);
    /// \ru Конструктор копирования. \en Copy constructor.
    Color(const Color& other);
    /// \ru Деструктор. \en Destructor.
    virtual ~Color();
    /// Define сolor.
    static const Color DEFINE_WHITE;
public:
    /// \ru Вернуть true, если все компоненты инициализированы. \en True if all components are initialized.
    bool IsValid() const;

    /// \ru Вернуть компонент альфа этого цвета. \en Returns the alpha component of given color.
    int GetAlpha() const;
    /// \ru Установить компонент альфа этого цвета. \en Sets the alpha component of given color.
    void SetAlpha(int alpha);

    /// \ru Вернуть компонент альфа этого цвета. \en Returns the alpha component of given color.
    float GetAlphaF() const;
    /// \ru Установить  компонент альфа этого цвета. \en Sets the alpha component of given color.
    void SetAlphaF(float alpha);

    /// \ru Вернуть красный компонент этого цвета. \en Returns the red component of given color.
    int GetRed() const;
    /// \ru Установить красный компонент этого цвета. \en Sets the red component of given color.
    void SetRed(int red);

    /// \ru Вернуть зеленый компонент этого цвета. \en Returns the green component of given color.
    int GetGreen() const;
    /// \ru Установить зеленый компонент этого цвета. \en Sets the green component of given color.
    void SetGreen(int green);

    /// \ru Вернуть синий компонент этого цвета. \en Returns the blue component of given color.
    int GetBlue() const;
    /// \ru Установить синий компонент этого цвета. \en Sets the blue component of given color.
    void SetBlue(int blue);

    /// \ru Вернуть красный компонент этого цвета. \en Returns the red component of given color.
    float GetRedF() const;
    /// \ru Установить красный компонент этого цвета. \en Sets the red component of given color.
    void SetRedF(float red);

    /// \ru Вернуть зеленый компонент этого цвета. \en Returns the green component of given color.
    float GetGreenF() const;
    /// \ru Установить зеленый компонент этого цвета. \en Sets the green component of given color.
    void SetGreenF(float green);

    /// \ru Вернуть синий компонент этого цвета. \en Returns the blue component of given color.
    float GetBlueF() const;
    /// \ru Установить синий компонент этого цвета. \en Sets the blue component of given color.
    void SetBlueF(float blue);

    /// \ru Вернуть все значения компонентов цвета. \en Returns all values of color components.
    void GetRgb(int* r, int* g, int* b, int* a = 0) const;
    /// \ru Установить все компоненты цвета. \en Sets all color components.
    void SetRgb(int r, int g, int b, int a = 255);

    /// \ru Вернуть указатели на все компоненты. \en Returns pointers to all components.
    void GetRgbF(float* r, float* g, float* b, float* a = 0) const;
    /// \ru Установить указатели на все компоненты. \en Sets pointers to all components.
    void SetRgbF(float r, float g, float b, float a = 1.0);

    /// \ru Вернуть значение RGB для этого цвета, в том числе и альфа компонент. \en Returns RGB value of given color including the alpha component.
    vRgb GetRgba() const;

    static Color FromRgbF(float r, float g, float b, float a = 1.0);

    /// \ru Создать и вернуть RGB цвет на основе этого цвета. \en Creates and returns RGB color based on given color.
    Color ToRgb() const;
    Color ToHsv() const;
    Color ToCmyk() const;
    Color ToHsl() const;

    Color GetLight(int f = 150) const;
    Color GetLighter(int f = 150) const;
    Color GetDark(int f = 200) const;
    Color GetDarker(int f = 200) const;

    Color ConvertTo(ColorType colorSpec) const;

    /// \ru Оператор копирования. \en Copy constructor.
    Color& operator = (const Color& other);
    /// \ru Вернуть true, если этот цвет имеет те же RGB и альфа значения, как в указанном цвете. \en True if the color has such RGB and alpha values as specified color.
    bool operator == (const Color& c) const;
    /// \ru Вернуть true, если этот цвет имеет отличные RGB и альфа значения от указанного цвета. \en True if the color has different RGB and alpha values from the specified color.
    bool operator != (const Color& c) const;
private:
    VSN_DECLARE_PRIVATE(Color)
};

VSN_END_NAMESPACE


#endif /* __VSN_COLOR_H */
