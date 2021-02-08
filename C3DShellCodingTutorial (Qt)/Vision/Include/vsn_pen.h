////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Описание пера и предопределенных стилей
           \en Pen devinition and predefined styles
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_PEN_H
#define __VSN_PEN_H


#include <vsn_global.h>
#include <vsn_color.h>

VSN_BEGIN_NAMESPACE

class Color;
class PenPrivate;

//------------------------------------------------------------------------------
/** \brief \ru Предустановленные стили пера
           \en NOT TRANSLATED  \~
    \details \ru Стили определяющие толщину и размер штрихов пера
             \en NOT TRANSLATED \~
    \ingroup
*/
// ---
enum class PenStyle
{
    solid,     // основная
    axial,     // осевая
    dashed,    // штриховая
    divide,    // штрих-пунктир с 2 точками
    axialFat,  // осевая толстая
    dashedFat, // штриховая толстая
    custom,    // пользовательская
};

//------------------------------------------------------------------------------
/** \brief \ru Класс Pen - описатель пера
    \en NOT TRANSLATED  \~
    \details \ru Определяет как следует рисовать кривые и контуры объектов
                 Стиль пера - идентификатор предопределенного стиля или пользовательского.
                 Толщина - задает толщину линии. Паттерн - описание штриховки. 
                 Задается как ширина заполненой части, затем пропуска и т.д. 
                 Число элементов должно быть четным.
             \en NOT TRANSLATED \~
    \ingroup
*/
// ---
class VSN_CLASS Pen
{
public:
    /// \ru Конструктор по умолчанию(ширина - 1, стиль - сплошной, цвет - черный). \en Constructor by default(width - 1, style - solid, color - black).
    Pen();
    /// \ru Конструктор по цвету(ширина - 1, стиль - сплошной). \en Constructor by color(width - 1, style - solid).
    Pen(const Color& color);
    /// \ru Конструктор по предопределенному стилю(ширина по стилю, цвет черный) \en Constructor by predefined style(width - 1, color - black).
    Pen(PenStyle style);
    /// \ru Конструктор по ширине, стилю и цвету. \en Constructor by width, style and color.
    Pen(float width, PenStyle style = PenStyle::solid, const Color& color = Color(0, 0, 0));
    /// \ru Конструктор копирования. \en Copy constructor.
    Pen(const Pen& other);
    /// \ru Деструктор. \en Destructor.
    ~Pen();

    /// \ru Оператор присваения. \en Assignment operator.
    Pen& operator=(const Pen& other);

    /// \ru Получить ширину пера. \en NOT TRANSLATED
    float GetWidth() const;
    /// \ru Задать ширину пера. \en NOT TRANSLATED
    void SetWidth(float width);

    /// \ru Получить цвет пера. \en NOT TRANSLATED
    Color GetColor() const;
    /// \ru Задать цвет пера. \en NOT TRANSLATED
    void SetColor(const Color& color);

    /// \ru Получить паттерн штриховки. \en NOT TRANSLATED
    std::vector<float> DashPattern() const;
    /// \ru Задать паттерн штриховки. \en NOT TRANSLATED
    void SetDashPattern(const std::vector<float>& pattern);
    
    /// \ru Получить предопределенный стиль пера. \en NOT TRANSLATED
    PenStyle GetStyle() const;
    /// \ru Задать предопределенный стиль пера. \en NOT TRANSLATED
    void SetStyle(PenStyle);

    /// \ru Оператор равенства. \en Equal operator.
    bool operator==(const Pen& p) const;
    /// \ru Оператор не равенства. \en Not equal operator.
    inline bool operator!=(const Pen& p) const { return !(operator==(p)); }
private:
    VSN_DECLARE_PRIVATE(Pen)
};

VSN_END_NAMESPACE

#endif // __VSN_PEN_H