///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс IntPoint и DblPoint определяет точку на плоскости и использует целочисленную точность.
         \en IntPoint and DblPoint class defines point on the plane using integer precision. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_POINT_H
#define __VSN_POINT_H

#include "vsn_mathdefs.h"
#include "vsn_mathfunctions.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//----------------------------------------------------------------------------
//
/** \brief \ru Класс IntPoint определяет точку на плоскости и использует целочисленную точность.
           \en IntPoint class defines point on the plane using integer precision. \~
    \details \ru Точка задается координатами х и у, которые можно получить с помощью функций GetX() и GetY(). 
                 Функция IsNull() возвращает истину, если обе координаты х и у равны 0. Координаты могут быть установлены или изменены 
                 с помощью функций SetX() и SetY() или в качестве альтернативы функциями InitX() и InitY(), которые возвращают ссылки на координаты. \n
             \en IntPoint is defined with X- and Y-coordinates that can be returned with GetX() and GetY() functions.
                 IsNull() function returns True, if both X- and Y-coordinates are 0. The coordinates can be set or changed
                 with SetX() and SetY() functions, or alternatively InitX() and InitY() functions that return coordinate references. \n \~
    \ingroup Vision_Base
*/
// ---
class VSN_CLASS IntPoint
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    IntPoint();
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates. \~
    IntPoint(int x, int y);
    /// \ru Конструктор копирования. \en Сonstructor. \~
    IntPoint(const IntPoint& other);
public:
    /// \ru Вернуть true, если обе координаты х и у равны 0, в противном случае возвращает false. \en True if both X- and Y-coordinates are 0. \~
    bool IsNull() const;

    /// \ru Вернуть координату х. \en Returns X-coordinate. \~
    int GetX() const;
    /// \ru Установить координату х. \en Sets X-coordinate. \~
    void SetX(int x);

    /// \ru Вернуть координату y. \en Returns Y-coordinate. \~
    int GetY() const;
    /// \ru Установить координату y. \en Sets Y-coordinate. \~
    void SetY(int y);

    /// \ru Инициализация координаты х. \en Initializes X-coordinate. \~
    int& InitX();
    /// \ru Инициализация координаты y. \en Initializes Y-coordinate. \~
    int& InitY();
    /// \ru Вернуть сумму абсолютных значений x и y. Это вектора от начала координат до точки. \en NO TRANSLATION. \~
    int GetVectorLength() const;

    /// \ru Добавить указанную точку в эту точку и вернуть ссылку на эту точку. \en Adds the specified point to the given point and returns point reference. \~
    IntPoint& operator += (const IntPoint& p);
    /// \ru Вычесть указанную точку из этой точки и вернуть ссылку на эту точку. \en Subtracts the specified point from the given point and returns point reference. \~
    IntPoint& operator -= (const IntPoint& p);
    /// \ru Вернуть true, если указанная точка и эта точка равны, в противном случае возвращает false. \en True if the specified point and the given point are equal. \~
    bool operator == (const IntPoint& p);
    /// \ru Вернуть true если указанная точка и эта точка не равны, в противном случае возвращает false. \en True if the specified point and the given point are not equal. \~
    bool operator != (const IntPoint& p);
    const IntPoint operator + (const IntPoint& p);
    const IntPoint operator - (const IntPoint& p);
private:
    int m_xPnt; ///< \ru Координата x точки. \en IntPoint X-coordinate. \~ 
    int m_yPnt; ///< \ru Координата y точки. \en IntPoint Y-coordinate. \~ 
};

inline IntPoint::IntPoint() : m_xPnt(0), m_yPnt(0) {}
inline IntPoint::IntPoint(int x, int y) : m_xPnt(x), m_yPnt(y) {}
inline IntPoint::IntPoint(const IntPoint& other) : m_xPnt(other.m_xPnt), m_yPnt(other.m_yPnt) {}

inline bool IntPoint::IsNull() const { return m_xPnt == 0 && m_yPnt == 0; }

inline int IntPoint::GetX() const { return m_xPnt; }
inline void IntPoint::SetX(int x) { m_xPnt = x; }

inline int IntPoint::GetY() const { return m_yPnt; }
inline void IntPoint::SetY(int y) {  m_yPnt = y; }

inline int& IntPoint::InitX() { return m_xPnt; }
inline int& IntPoint::InitY() { return m_yPnt; }

inline int IntPoint::GetVectorLength() const
{ return abs(m_xPnt) + abs(m_yPnt); }

inline IntPoint& IntPoint::operator += (const IntPoint& p) { m_xPnt += p.m_xPnt; m_yPnt += p.m_yPnt; return *this; }
inline IntPoint &IntPoint::operator -= (const IntPoint& p) { m_xPnt -= p.m_xPnt; m_yPnt -= p.m_yPnt; return *this; }

inline bool IntPoint::operator == ( const IntPoint& p ) { return m_xPnt == p.m_xPnt && m_yPnt == p.m_yPnt; }
inline bool IntPoint::operator != (const IntPoint& p) { return m_xPnt != p.m_xPnt || m_yPnt != p.m_yPnt; }
inline const IntPoint IntPoint::operator + (const IntPoint& p) { return IntPoint(m_xPnt + p.m_xPnt, m_yPnt + p.m_yPnt); }
inline const IntPoint IntPoint::operator - (const IntPoint& p) { return IntPoint(m_xPnt - p.m_xPnt, m_yPnt - p.m_yPnt); }


//----------------------------------------------------------------------------
//
/** \brief \ru Класс DblPoint определяет точку на плоскости и использует двойноую точность.
           \en IntPoint class defines point on the plane using double-precision. \~
    \details \ru Точка задается координатами х и у, которые можно получить с помощью функций GetX() и GetY().
                 Функция IsNull() возвращает истину, если обе координаты х и у равны 0. Координаты могут быть установлены или изменены
                 с помощью функций SetX() и SetY() или в качестве альтернативы функциями InitX() и InitY(), которые возвращают ссылки на координаты. \n
             \en DblPoint is defined with X- and Y-coordinates that can be returned with GetX() and GetY() functions.
                 IsNull() function returns True, if both X- and Y-coordinates are 0. The coordinates can be set or changed
                 with SetX() and SetY() functions, or alternatively InitX() and InitY() functions that return coordinate references. \n \~
    \ingroup Vision_Base
*/
// ---
class VSN_CLASS DblPoint
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    DblPoint();
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates.
    DblPoint(const IntPoint& other);
    /// \ru Специальный конструктор для инициализации координат x и y. \en Special constructor for initialization X- and Y-coordinates.
    DblPoint(double x, double y);
public:
    /// \ru Вернуть true, если обе координаты х и у равны 0, в противном случае возвращает false. \en True if both X- and Y-coordinates are 0.
    inline bool IsNull() const;
    /// \ru Вернуть координату х. \en Returns X-coordinate.
    inline double GetX() const;
    /// \ru Установить координату х. \en Sets X-coordinate.
    inline void SetX(double x);
    /// \ru Вернуть координату y. \en Returns Y-coordinate.
    inline double GetY() const;
    /// \ru Установить координату y. \en Sets Y-coordinate.
    inline void SetY(double y);
    /// \ru Инициализация координаты х. \en Initializes X-coordinate.
    inline double& InitX();
    /// \ru Инициализация координаты y. \en Initializes Y-coordinate.
    inline double& InitY();
    inline IntPoint ToPoint() const;

    inline DblPoint &operator+=(const DblPoint &p);
    inline DblPoint &operator-=(const DblPoint &p);
    inline DblPoint &operator*=(double c);
    inline DblPoint &operator/=(double c);

    friend inline bool operator==(const DblPoint &, const DblPoint &);
    friend inline bool operator!=(const DblPoint &, const DblPoint &);

    friend inline const DblPoint operator+(const DblPoint &, const DblPoint &);
    friend inline const DblPoint operator-(const DblPoint &, const DblPoint &);
    friend inline const DblPoint operator+(const DblPoint &);
    friend inline const DblPoint operator-(const DblPoint &);
    friend inline const DblPoint operator/(const DblPoint &, double);
    friend inline const DblPoint operator*(double, const DblPoint &);
    friend inline const DblPoint operator*(const DblPoint &, double);
private:
    double m_xPnt; ///< \ru Координата x точки. \en DblPoint X-coordinate.
    double m_yPnt; ///< \ru Координата y точки. \en DblPoint Y-coordinate.
};

inline DblPoint::DblPoint() : m_xPnt(0), m_yPnt(0) { }
inline DblPoint::DblPoint(double x, double y) : m_xPnt(x), m_yPnt(y) { }
inline DblPoint::DblPoint(const IntPoint& other) : m_xPnt(other.GetX()), m_yPnt(other.GetY()) { }

inline bool DblPoint::IsNull() const { return IsEqual(m_xPnt, 0.0, 0.00001) && IsEqual(m_yPnt, 0.0, 0.00001); }

inline double DblPoint::GetX() const { return m_xPnt;}
inline void DblPoint::SetX(double xpos) { m_xPnt = xpos; }

inline double DblPoint::GetY() const { return m_yPnt;}
inline void DblPoint::SetY(double ypos) { m_yPnt = ypos; }

inline double& DblPoint::InitX() { return m_xPnt; }
inline double& DblPoint::InitY() { return m_yPnt; }

inline IntPoint DblPoint::ToPoint() const { return IntPoint(vRound(m_xPnt), vRound(m_yPnt)); }

inline DblPoint& DblPoint::operator+=(const DblPoint& other) { m_xPnt += other.m_xPnt; m_yPnt += other.m_yPnt; return *this; }
inline DblPoint& DblPoint::operator-=(const DblPoint& other) { m_xPnt -= other.m_xPnt; m_yPnt -= other.m_yPnt; return *this; }
inline DblPoint& DblPoint::operator*=(double cof) { m_xPnt *= cof; m_yPnt *= cof; return *this; }

inline bool operator==(const DblPoint& pnt1, const DblPoint& pnt2) { return IsEqual(pnt1.m_xPnt - pnt2.m_xPnt, 0.0, 0.00001) && IsEqual(pnt1.m_yPnt - pnt2.m_yPnt, 0.0, 0.00001); }
inline bool operator!=(const DblPoint& pnt1, const DblPoint& pnt2) { return !IsEqual(pnt1.m_xPnt - pnt2.m_xPnt, 0.0, 0.00001) || !IsEqual(pnt1.m_yPnt - pnt2.m_yPnt, 0.0, 0.00001);}

inline const DblPoint operator+(const DblPoint& pnt1, const DblPoint& pnt2) { return DblPoint(pnt1.m_xPnt + pnt2.m_xPnt, pnt1.m_yPnt + pnt2.m_yPnt);}
inline const DblPoint operator-(const DblPoint& pnt1, const DblPoint& pnt2) { return DblPoint(pnt1.m_xPnt - pnt2.m_xPnt, pnt1.m_yPnt - pnt2.m_yPnt); }
inline const DblPoint operator*(const DblPoint& other, double cof) { return DblPoint(other.m_xPnt*cof, other.m_yPnt*cof); }
inline const DblPoint operator*(double cof, const DblPoint& other) { return DblPoint(other.m_xPnt*cof, other.m_yPnt*cof); }
inline const DblPoint operator+(const DblPoint& other) { return other; }
inline const DblPoint operator-(const DblPoint& other) { return DblPoint(-other.m_xPnt, -other.m_yPnt); }
inline DblPoint &DblPoint::operator/=(double divisor) { m_xPnt /= divisor; m_yPnt /= divisor; return *this; }
inline const DblPoint operator/(const DblPoint& other, double divisor) { return DblPoint(other.m_xPnt / divisor, other.m_yPnt / divisor); }


VSN_END_NAMESPACE

#endif /*__VSN_POINT_H*/
