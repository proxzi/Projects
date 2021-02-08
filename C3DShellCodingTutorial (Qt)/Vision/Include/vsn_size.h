////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс Size описывает размер и использует целочисленную точность.
         \en Size class describes a size and uses an integer precision. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SIZE_H
#define __VSN_SIZE_H

#include "vsn_mathfunctions.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE


//----------------------------------------------------------------------------
//
/** \brief \ru Класс Size описывает размер и использует целочисленную точность.
           \en Size class describes a size and uses an integer precision. \~
    \details \ru Size определяет ширину и высоту. Он может быть инициализирован в конструкторе 
                 или изменен с помощью функций SetWidth(), SetHeight(), а также использует 
                 арифметические операторы. Size можно управлять, непосредственно изменив 
                 его значения путем получения ссылок на ширину и высоту. Ширину 
                 и высоту можно инициализировать функциями или через конструктор. Метод IsValid() определяет 
                 правильный размер: у правильного размер ширина и высота должны быть больше нуля.
                 Функция IsEmpty() возвращает true, если ширина и высота меньше или равны нулю, 
                 а функция IsNull() возвращает true, если ширина и высота равны нулю.\n
             \en Size class defines a width and height. It can be initialized in constructor
                 or changed with SetWidth(), SetHeight() functions, and also uses the arithmetic operators.
                 Size can be managed directly changing its values by receiving the references to width and
                 heights. The width and height can be initialized with functions or with constructor.
                 IsValid() method defines the correct size: the correct size must have a width and height
                 greater than 0. IsEmpty() function returns true if the width and height are less than or
                 equal to 0, and IsNull() function returns true if the width and height are 0. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS Size
{
public:
    /// \ru Конструктор по умолчанию. Создает недопустимый размер, т. е. IsValid() возвращает false. \en Default constructor that creates invalid size, i.e. IsValid() returns false. \~
    Size();
    /// \ru Конструктор с заданием ширины и высоты. \en Constructor with setting width and height. \~
    Size(int w, int h);
public:
    /// \ru Возвращает true, если ширина и высота равны 0, в противном случае возвращает false. \en Returns true if width and height are 0 otherwise returns false. \~
    bool IsNull() const; 
    /// \ru Возвращает true, если ширина и высота меньше или равны 0, в противном случае возвращает false.\en Returns true if width and height are less than or equal to 0 otherwise returns false. \~
    bool IsEmpty() const;
    /// \ru Возвращает true, если ширина и высота равны или больше 0, в противном случае возвращает false. \en Returns true if width and height are greater than or equal to 0 otherwise returns false. \~
    bool IsValid() const;

    /// \ru Возвращает ширину. \en Returns width. \~
    int GetWidth() const;
    /// \ru Возвращает высоту. \en Returns height. \~
    int GetHeight() const;
  
    /// \ru Установить ширину. \en Sets width. \~
    void SetWidth(int w);
    /// \ru Установить высоту. \en Sets height. \~
    void SetHeight(int h);

    /// \ru Возвращает ссылку на ширину. \en Returns reference to width. \~
    int& InitWidth();
    /// \ru Возвращает ссылку на высоту. \en Returns reference to height. \~
    int& InitHeight();

    /// \ru Добавляет указанный размер к этому размеру и возвращает ссылку на этот размер. \en Adds the specified size to this size and returns reference to this size. \~
    Size& operator += (const Size&);
    /// \ru Вычитает заданный размер из этого размера и возвращает ссылку на этот размер. \en Subtracts the given size from this size and returns reference to this size. \~
    Size& operator -= (const Size&);
    /// \ru Умножает размер на указанное число. \en Multiplies size by the specified number. \~
    const Size operator *= (double);

    /// \ru Возвращает true, если указанный размер и этот равны, в противном случае возвращает false. \en Returns true if the specified size and this one are equal otherwise returns false. \~
    bool operator == (const Size&);
    /// \ru Возвращает true, если указанный размер и этот отличны, в противном случае возвращает false. \en Returns true if the specified size and this one are different otherwise returns false. \~
    bool operator != (const Size&);

    /// \ru Возвращает сумму указанного размера и этого, каждый компонент добавляется отдельно. \en Returns sum of the specified size and this one. Each component is added separately. \~
    const Size operator + (const Size&);
    /// \ru Возвращает разность из этого размера и указанного, каждый компонент вырезается отдельно. \en Returns difference between this size and the specified one. Each component is subtracted separately. \~
    const Size operator - (const Size&);
    /// \ru Возвращает произведение двух размеров с указанным числом. \en Returns composition of two sizes with the specified number. \~
    //  const Size operator * (double);
    friend VSN_FUNC_EX const Size operator * (const Size &s, double c);
private:
    int m_width;  ///< \ru Ширина размера. \en Size width.
    int m_height; ///< \ru Высота размера. \en Size height.
};


inline Size::Size() 
  : m_width(-1)
  , m_height(-1) 
{
}

inline Size::Size(int w, int h) 
  : m_width(w)
  , m_height(h) 
{
}

inline bool Size::IsNull() const
{ 
  return m_width == 0 && m_height == 0; 
}

inline bool Size::IsEmpty() const
{ 
  return m_width < 1 || m_height < 1; 
}

inline bool Size::IsValid() const
{ 
  return m_width >= 0 && m_height >= 0; 
}

inline int Size::GetWidth() const
{ 
  return m_width; 
}

inline int Size::GetHeight() const
{ 
  return m_height; 
}

inline void Size::SetWidth(int w)
{ 
  m_width = w; 
}

inline void Size::SetHeight(int h)
{ 
  m_height = h; 
}

inline int& Size::InitWidth()
{ 
  return m_width; 
}

inline int &Size::InitHeight()
{ 
  return m_height; 
}

inline Size &Size::operator += (const Size &s)
{ 
  m_width += s.m_width; 
  m_height += s.m_height; 
  return *this; 
}

inline Size& Size::operator-=(const Size &s)
{ 
  m_width -= s.m_width; 
  m_height -= s.m_height; 
  return *this; 
}

inline bool Size::operator == (const Size &s)
{ 
  return m_width == s.m_width && m_height == s.m_height; 
}

inline bool Size::operator != (const Size &s)
{ 
  return m_width != s.m_width || m_height != s.m_height; 
}

inline const Size Size::operator + (const Size & s)
{ 
  return Size(m_width + s.m_width, m_height + s.m_height); 
}

inline const Size Size::operator - (const Size& s)
{ 
  return Size(m_width - s.m_width, m_height - s.m_height); 
}



//----------------------------------------------------------------------------
//
/** \brief \ru Класс Size описывает размер и использует точность с плавающей точкой.
           \en Size class describes a size and uses an floating precision. \~
    \details \ru Size определяет ширину и высоту. Он может быть инициализирован в конструкторе 
                 или изменен с помощью функций SetWidth(), SetHeight(), а также использует
                 арифметические операторы. Size также можно управлять, непосредственно изменив 
                 его значения путем получения ссылок на ширину и высоту. Ширину 
                 и высоту можно инициализировать функциями или через конструктор. Метод IsValid() определяет 
                 правильный размер (у правильного размер ширина и высота должны быть больше нуля). 
                 Функция IsEmpty() возвращает true, если ширина и высота меньше или равны нулю, 
                 а функция IsNull() возвращает true, если ширина и высота равны нулю.\n
             \en Size class defines a width and height. It can be initialized in constructor
                 or changed with SetWidth(), SetHeight() functions, and also uses the arithmetic operators.
                 Size can be managed directly changing its values by receiving the references to width and
                 heights. The width and height can be initialized with functions or with constructor.
                 IsValid() method defines the correct size: the correct size must have a width and height
                 greater than 0. IsEmpty() function returns true if the width and height are less than or
                 equal to 0, and IsNull() function returns true if the width and height are 0. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS DoubleSize
{
public:
    /// \ru Конструктор по умолчанию. Создает недопустимый размер, т. е. IsValid() возвращает false. \en Default constructor that creates invalid size, i.e. IsValid() returns false. \~
    DoubleSize();
    /// \ru Конструктор с заданием размера ширины и высоты с целочисленной точностью. \en Constructor with setting size width and height with integer precision. \~
    DoubleSize(const Size& sz);
    /// \ru Конструктор с заданием ширины и высоты с плавающей точностью. \en Constructor with setting size width and height with floating precision. \~
    DoubleSize(double w, double h);
public:
    /// \ru Возвращает значение true, если ширина и высота равны 0.0, в противном случае возвращает false. \en Returns true if width and height are 0.0 otherwise returns false. \~
    inline bool IsNull() const;
    /// \ru Возвращает true, если ширина и высота меньше или равны 0, в противном случае возвращает false. \en Returns true if width and height are less than or equal to 0 otherwise returns false. \~
    inline bool IsEmpty() const;
    /// \ru Возвращает true, если ширина и высота равны или больше 0, в противном случае возвращает false. \en Returns true if width and height are greater than or equal to 0 otherwise returns false. \~
    inline bool IsValid() const;

    /// \ru Возвращает ширину. \en Returns width. \~
    inline double GetWidth() const;
    /// \ru Возвращает высоту. \en Returns height . \~
    inline double GetHeight() const;

    /// \ru Установить ширину. \en Sets width. \~
    inline void SetWidth(double w); 
    /// \ru Установить высоту. \en Sets height. \~
    inline void SetHeight(double h);

    /// \ru Возвращает ссылку на ширину. \en Returns reference to width. \~
    inline double& InitWidth();
    /// \ru Возвращает ссылку на высоту. \en Returns reference to height. \~
    inline double& InitHeight();

    /// \ru Добавляет указанный размер к этому размеру и возвращает ссылку на этот размер. \en Adds the specified size to this size and returns reference to this size. \~
    inline DoubleSize& operator+=(const DoubleSize&);
    /// \ru Ввычитает заданный размер из этого размера и возвращает ссылку на этот размер. \en Subtracts the given size from this size and returns reference to this size. \~
    inline DoubleSize& operator-=(const DoubleSize&);
    /// \ru Умножает ширину и высоту на заданную величину и возвращает ссылку на размер. \en Multiplies width and height by the given value, and returns reference to size. \~
    inline DoubleSize& operator*=(double c);
    /// \ru Делит ширину и высоту на заданный делитель и возвращает ссылку на размер. \en Divides width and height by the given divider and returns reference to size. \~
    inline DoubleSize& operator/=(double c);

    /// \ru Возвращает true, если указанный размер и этот равны, в противном случае возвращает false. \en Returns true if the specified size and this one are equal otherwise returns false. \~
    friend inline bool operator==(const DoubleSize&, const DoubleSize&);
    /// \ru Возвращает true, если указанный размер и этот отличны, в противном случае возвращает false. \en Returns true if the specified size and this one are different otherwise returns false. \~
    friend inline bool operator!=(const DoubleSize&, const DoubleSize&);
    /// \ru Возвращает сумму указанного размера и этого, каждый компонент добавляется отдельно. \en Returns sum of the specified size and this one. Each component is added separately. \~
    friend inline const DoubleSize operator+(const DoubleSize&, const DoubleSize&);
    /// \ru Возвращает разность из этого размера и указанного, каждый компонент вырезается отдельно. \en Returns difference between this size and the specified one. Each component is subtracted separately. \~
    friend inline const DoubleSize operator-(const DoubleSize&, const DoubleSize&);
    /// \ru Умножает данный размер на заданное значение и возвращает результат. \en Multiplies the given size by the given value and returns result. \~
    friend inline const DoubleSize operator*(const DoubleSize&, double);
    /// \ru Умножает данный размер на заданное значение и возвращает результат. \en Multiplies the given size by the given value and returns result. \~
    friend inline const DoubleSize operator*(double, const DoubleSize&);
    /// \ru Делит данный размер на данный делитель и возвращает результат. \en Divides the given size by the given divider and returns result. \~
    friend inline const DoubleSize operator/(const DoubleSize&, double);
private:
  double m_dbWidth;   ///< \ru Ширина размера. \en Size width. \~
  double m_dbHeight;  ///< \ru Высота размера. \en Size height. \~
};

inline DoubleSize::DoubleSize() : m_dbWidth(-1.0), m_dbHeight(-1.0) {}

inline DoubleSize::DoubleSize(const Size& sz) : m_dbWidth(sz.GetWidth()), m_dbHeight(sz.GetHeight()) {}

inline DoubleSize::DoubleSize(double w, double h) : m_dbWidth(w), m_dbHeight(h) {}

inline bool DoubleSize::IsNull() const
{ return IsEqual(m_dbWidth, 0.0, 0.00001) && IsEqual(m_dbHeight, 0.0, 0.00001); }

inline bool DoubleSize::IsEmpty() const
{ return m_dbWidth <= 0.0 || m_dbHeight <= 0.0; }

inline bool DoubleSize::IsValid() const
{ return m_dbWidth >= 0.0 && m_dbHeight >= 0.0; }

inline double DoubleSize::GetWidth() const 
{ return m_dbWidth; }

inline double DoubleSize::GetHeight() const
{ return m_dbHeight; }

inline void DoubleSize::SetWidth(double w)
{ m_dbWidth = w; }

inline void DoubleSize::SetHeight(double h)
{ m_dbHeight = h; }

inline double& DoubleSize::InitWidth()
{ return m_dbWidth; }

inline double& DoubleSize::InitHeight()
{ return m_dbHeight; }

inline DoubleSize &DoubleSize::operator+=(const DoubleSize &s)
{ m_dbWidth += s.m_dbWidth; m_dbHeight += s.m_dbHeight; return *this; }

inline DoubleSize &DoubleSize::operator-=(const DoubleSize &s)
{ m_dbWidth -= s.m_dbWidth; m_dbHeight -= s.m_dbHeight; return *this; }

inline DoubleSize &DoubleSize::operator *= (double c)
{ m_dbWidth *= c; m_dbHeight *= c; return *this; }

inline bool operator==(const DoubleSize& s1, const DoubleSize& s2)
{ return IsEqual(s1.m_dbWidth, s2.m_dbWidth, 0.00001) && IsEqual(s1.m_dbHeight, s2.m_dbHeight, 0.00001); }

inline bool operator!=(const DoubleSize &s1, const DoubleSize &s2)
{ return !IsEqual(s1.m_dbWidth, s2.m_dbWidth, 0.00001) || !IsEqual(s1.m_dbHeight, s2.m_dbHeight, 0.00001); }

inline const DoubleSize operator+(const DoubleSize& s1, const DoubleSize& s2)
{ return DoubleSize(s1.m_dbWidth + s2.m_dbWidth, s1.m_dbHeight + s2.m_dbHeight); }

inline const DoubleSize operator-(const DoubleSize& s1, const DoubleSize& s2)
{ return DoubleSize(s1.m_dbWidth-s2.m_dbWidth, s1.m_dbHeight-s2.m_dbHeight); }

inline const DoubleSize operator*(const DoubleSize &s, double c)
{ return DoubleSize(s.m_dbWidth*c, s.m_dbHeight*c); }

inline const DoubleSize operator*(double c, const DoubleSize &s)
{ return DoubleSize(s.m_dbWidth * c, s.m_dbHeight * c); }

inline DoubleSize &DoubleSize::operator/=(double c)
{
  PRECONDITION(!IsEqual(c, 0.0, 0.00001));
  m_dbWidth = m_dbWidth / c; m_dbHeight = m_dbHeight / c;
  return *this;
}

inline const DoubleSize operator/(const DoubleSize& s, double c)
{
  PRECONDITION(!IsEqual(c, 0.0, 0.00001));
  return DoubleSize(s.m_dbWidth / c, s.m_dbHeight / c);
}

VSN_END_NAMESPACE

#endif // __VSN_SIZE_H
