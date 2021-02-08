////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс Fields определяет четыре поля прямоугольника.
       \en Fields class defines four rectangle fields. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_FIELDS_H
#define __VSN_FIELDS_H

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief  \ru Класс Fields определяет четыре поля прямоугольника.
            \en Fields class defines four rectangle fields. \~
    \details \ru Fields определяет набор из четырех полей: левый, верхний, правый и нижний,
                 которые описывают размеры границ, окружающих прямоугольник. Функция IsNull()
                 возвращает значение True, только если все поля равны нулю. \n
             \en Fields defines a set of four fields - left, top, right and bottom - that describe
                 size of each rectangle border. IsNull() function returns True only if a value
                 of each rectangle field is 0.  \n \~
    \ingroup Vision_Core
*/
// ---
class VSN_CLASS Fields
{
public:
    /// \ru Конструктор объекта с полями, равными 0. \en Object constructor with fields being 0.
    Fields();
    /// \ru Конструктор объекта с заданными левым, верхним, правым и нижним полями. \en Object constructor with all four fields defined (left, top, right and bottom).
    Fields(int left, int top, int right, int bottom);
public:
    /// \ru Вернуть True, если все поля равны 0, в противном случае возвращает False. \en True if values of all fields are 0, otherwise, False.
    bool IsNull() const;

    /// \ru Вернуть значение левого поля. \en Returns value of left field.
    int GetLeft() const;
    /// \ru Установить левое поле влево. \en Sets left field to the left.
    void SetLeft(int left);
    
    /// \ru Вернуть значение верхнего поля. \en Returns value of top field.
    int GetTop() const;
    /// \ru Установить верхнюю границу вверх. \en Sets top field to the top.
    void SetTop(int top);

    /// \ru Вернуть значение правого поля. \en Returns value of right field.
    int GetRight() const;
    /// \ru Установить правое поле вправо. \en Sets right field to the right.
    void SetRight(int right);

    /// \ru Вернуть значение нижнего поля. \en Returns value of bottom field.
    int GetBottom() const;
    /// \ru Установить нижнее поле вниз. \en Sets bottom field to the bottom.
    void SetBottom(int bottom);
public:
    /// \ru Добавить значение к полям этого объекта из указанного объекта и вернуть ссылку на него. \en Adds the value to the fields of the object from the specified object and returns reference to it.
    Fields& operator+=(const Fields& fields);
    /// \ru Вычесть значение из полей этого объекта и вернуть ссылку на него. \en Subtracts the value from the fields of the object and returns reference to it.
    Fields& operator-=(const Fields& fields);
    /// \ru Добавить к каждому полю этого объекта указанное значение и вернуть ссылку на него. \en Adds the specified value to each field of the object and returns reference to it.
    Fields& operator+=(int);
    /// \ru Вычесть из каждого поля этого объекта указанное значение и вернуть ссылку на него. \en Subtracts the specified value from each field of the object and returns reference to it.
    Fields& operator-=(int);
    /// \ru Умножить значение каждого поля этого объекта на коэффициент и вернуть ссылку на него. \en Multiplies the value of each object field by a factor and returns reference to it.
    Fields& operator*=(int);
    /// \ru Делить значение каждого поля этого объекта делителем и вернуть ссылку на него. \en Divides the value of each object field by a divider and returns reference to it.
    Fields& operator/=(int);
    /// \ru Умножить значение каждого поля этого объекта на коэффициент и вернуть ссылку на него. \en Multiplies the value of each object field by a factor and returns reference to it.
    Fields& operator*=(double);
    /// \ru Делить значение каждого поля этого объекта делителем и вернуть ссылку на него. \en Divides the value of each object field by a divider and returns reference to it.
    Fields& operator/=(double);
private:
    int m_left;         ///< \ru Значение левого поля. \en Left field value.
    int m_top;          ///< \ru Значение верхнего поля. \en Top field value.
    int m_right;        ///< \ru Значение правого поля. \en Right field value.
    int m_bottom;       ///< \ru Значение нижнего поля. \en Bottom field value.
    
    friend  bool operator==(const Fields &, const Fields &);
    friend  bool operator!=(const Fields &, const Fields &);
};
VSN_FUNC_EX Fields operator+(const Fields &m1, const Fields &m2);
VSN_FUNC_EX Fields operator-(const Fields &m1, const Fields &m2);


//------------------------------------------------------------------------------
/** \brief  \ru Класс Fields определяет четыре поля прямоугольника.
            \en Fields class defines four rectangle fields. \~
    \details \ru Fields определяет набор из четырех полей; левый, верхний, правый и нижний,
                 которые описывают размер границ окружающих прямоугольник. Функция IsNull ()
                 возвращает значение True, только если все поля равны нулю. \n
             \en Fields defines a set of four fields - left, top, right and bottom - that describe
                 size of each rectangle border. IsNull() function returns True only if a value
                 of each rectangle field is 0. \n \~
    \ingroup Vision_Core
*/
// ---
class VSN_CLASS DoubleFields
{
public:
    /// \ru Конструктор объекта с полями, равными 0. \en Object constructor with fields being 0.
    DoubleFields();
    /// \ru Конструктор объекта с заданными левым, верхним, правым и нижним полями. \en Object constructor with all four fields defined(left, top, right and bottom).
    DoubleFields(double left, double top, double right, double bottom);
    /// \ru Конструктор копирования. \en Copy constructor.
    DoubleFields(const Fields& fields);
public:
    bool IsNull() const;

    double GetLeft() const;
    void SetLeft(double left);

    double GetTop() const;
    void SetTop(double top);

    double GetRight() const;
    void SetRight(double right);

    double GetBottom() const;
    void SetBottom(double bottom);

public:
    /// \ru Добавить значение к полям этого объекта из указанного объекта и вернуть ссылку на него. \en Adds the value to the fields of the object from the specified object and returns reference to it.
    DoubleFields& operator+=(const DoubleFields& fields);
    /// \ru Вычесть значение из полей этого объекта и вернуть ссылку на него. \en Subtracts the value from the fields of the object and returns reference to it.
    DoubleFields& operator-=(const DoubleFields& fields);
    /// \ru Добавить к каждому полю этого объекта указанное значение и вернуть ссылку на него. \en Adds the specified value to each field of the object and returns reference to it.
    DoubleFields& operator+=(double addend);
    /// \ru Вычесть из каждого поля этого объекта указанное значение и вернуть ссылку на него. \en Subtracts the specified value from each field of the object and returns reference to it.
    DoubleFields& operator-=(double subtrahend);
    /// \ru Умножить значение каждого поля этого объекта на коэффициент и вернуть ссылку на негоо. \en Multiplies the value of each object field by a factor and returns reference to it.
    DoubleFields& operator*=(double factor);
    /// \ru Делить значение каждого поля этого объекта делителем и вернуть ссылку на него. \en Divides the value of each object field by a divider and returns reference to it.
    DoubleFields& operator/=(double divisor);
    /// \ru Преобразовать этот объект в целочисленный и вернуть новый объект. \en Converts the object to integer object and returns a new object.
    Fields ToFields() const;
private:
    double m_left;    ///< \ru Значение левого поля. \en Left field value.
    double m_top;     ///< \ru Значение верхнего поля. \en Top field value.
    double m_right;   ///< \ru Значение правого поля. \en Right field value.
    double m_bottom;  ///< \ru Значение нижнего поля. \en Bottom field value.
};
VSN_END_NAMESPACE

#endif /* __VSN_FIELDS_H */
