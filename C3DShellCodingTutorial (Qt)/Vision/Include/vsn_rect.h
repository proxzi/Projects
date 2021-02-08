////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Класс IntRect описывает прямоугольник в плоскости и использует целочисленную точность.
         \en IntRect class defines rectangle in the plane using integer precision. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_RECT_H
#define __VSN_RECT_H

#include "vsn_fields.h"
#include "vsn_point.h"
#include "vsn_size.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class Fields;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс IntRect описывает прямоугольник в плоскости и использует целочисленную точность.
           \en IntRect class defines rectangle in the plane using integer precision. \~
    \details \ru Прямоугольник, как правило, выражается в виде верхнего левого угла и размера. 
                 Прямоугольник может быть построен с помощью целочисленных координат слева, сверху, ширины и высоты, или при помощи классов IntPoint и Size. 
                 Класс IntRect предоставляет набор функций, которые возвращают необходимые координаты прямоугольника и позволяют их инициализировать. 
                 Класс IntRect также предоставляет функции, которые дают возможность перемещать прямоугольник относительно его координат и т.д. \n
             \en Rectangle is typically expressed as top-left angle and size.
                 Rectangle can be constructed with integer coordinates of left, top, width and height, or with IntPoint and Size classes.
                 IntRect class provides a set of functions that return necessary coordinates of the rectangle and allow initializing them. 
                 IntRect class also provides functions for moving the rectangle about its coordinates, etc. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS IntRect
{
public:
  /// \ru Конструктор по умолчанию. Создает пустой прямоугольник. \en Default constructor for creating empty rectangle.
  IntRect();
  /// \ru Специальный конструктор прямоугольника с заданием верхнего левого и нижнего правого угла. \en Special rectangle constructor with setting the top-left and bottom-right angle.
  IntRect(const IntPoint& topleft, const IntPoint& bottomright);
  /// \ru Специальный конструктор прямоугольника с заданием координат верхнего левого угла и размера прямоугольника. \en Special rectangle constructor with setting top-left angle coordinates and rectangle size.
  IntRect(const IntPoint& topleft, const Size& size);
  /// \ru Специальный конструктор прямоугольника с заданием координат верхнего левого угла и размера прямоугольника. \en Special rectangle constructor with setting top-left angle coordinates and rectangle size.
  IntRect(int left, int top, int width, int height);

public:
  /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
             \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~ 
  */
  void Init(int x, int y, int w, int h);

  /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
             \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
  */
  void InitCoords(int x1, int y1, int x2, int y2);

  /** \brief \ru Возвращает true, если прямоугольник пустой, в противном случае возвращает false.
             \en True if rectangle is empty. \~ 
      \details \ru Нулевой прямоугольник имеет ширину и высоту, которые равны 0 (т.е. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1). 
                   Нулевой прямоугольник также является пустым и, следовательно, не является действительным.
               \en Null rectangle has width and height that equal 0, i.e. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1.
                   Null rectangle is also empty and hence not valid.  \~ 
    \return \ru True, если прямоугольник пустой.
            \en True if rectangle is empty. \~
  */
  bool IsNull() const;
  /** \brief \ru Возвращает true, если прямоугольник пустой в противном случае возвращает false.
             \en True if rectangle is empty. \~ 
      \details \ru Пустой прямоугольник имеет GetLeft() > GetRight() или GetTop() > GetBottom(). Пустой прямоугольник не является действительным, т.е. значение функции IsEmpty() не равно значению функции IsValid().
               \en Empty rectangle has GetLeft() > GetRight() or GetTop() > GetBottom(). Empty rectangle is not valid, i.e. IsEmpty() function value is not equal to IsValid() function value. \~ 
      \note  \ru Используйте функцию Normalize(), чтобы получить правильный прямоугольник.
             \en Use Normalize() function to get regular rectangle. \~ 
    \return \ru True, если прямоугольник пустой.
            \en True if rectangle is empty. \~
  */
  bool IsEmpty() const;
  /** \brief \ru Возвращает true, если прямоугольник действительный в противном случае возвращает ложь.
             \en True if rectangle is valid. \~ 
      \details \ru Действительный прямоугольник имеет GetLeft() < GetRight() и GetTop() < GetBottom().  
                   Действительный прямоугольник не пуст, т.е. значение функции IsValid() не равно значению функции IsEmpty().
               \en Valid rectangle has GetLeft() < GetRight() and GetTop() < GetBottom().
                   Valid rectangle is not empty, i.e. IsValid() function value is not equal to IsEmpty() function value. \~ 
      \note  \ru Обратите внимание, что операции, например, пересечения не выполняются, если прямоугольник является недействительным.
             \en Please note that operations like intersection are not performed if rectangle is invalid. \~ 
    \return \ru True, если прямоугольник действителен.
            \en True if rectangle is valid. \~
  */
  bool IsValid() const;

  /** \brief \ru Возвращает X-координату левого края прямоугольника. Эквивалент GetX().
             \en Returns X-coordinate of the left rectangle edge. It is the equivalent of GetX() function. \~ 
    \return \ru X-координата левого края прямоугольника. 
            \en X-coordinate of the left rectangle edge. \~
  */
  int GetLeft() const;
  /** \brief \ru Возвращает Y-координату левого края прямоугольника. Эквивалент GetY().
             \en Returns Y-coordinate of the left rectangle edge. It is the equivalent of GetY() function. \~ 
    \return \ru Y-координата левого края прямоугольника.
            \en Y-coordinate of the left rectangle edge. \~
  */
  int GetTop() const;
  /** \brief \ru Возвращает X-координату правого края прямоугольника.
             \en Returns X-coordinate of the right rectangle edge. \~ 
    \return \ru X-координата правого края прямоугольника.
            \en X-coordinate of the right rectangle edge. \~
  */
  int GetRight() const;
  /** \brief \ru Возвращает Y-координату нижнего края прямоугольника.
             \en Returns Y-coordinate of the bottom rectangle edge. \~ 
    \return \ru Y-координата нижнего края прямоугольника.
            \en Y-coordinate of the bottom rectangle edge. \~
  */
  int GetBottom() const;

  /** \brief \ru Возвращает нормализованный прямоугольник, т.е. прямоугольник, который не имеет отрицательную ширину и высоту.
             \en Returns normalized rectangle, i.e. the rectangle has no negative width and height. \~ 
      \note \ru Если GetWidth() < 0, функция меняет местами левый и правый углы, а также, если GetHeight() < 0, то она меняет местами верхний и нижний углы. 
            \en If GetWidth() < 0, then function swaps the left and right angles. If GetHeight() < 0, then it swaps the top and bottom angles. \~ 
    \return \ru Нормализованный прямоугольник.
            \en Normalized rectangle. \~
  */
  IntRect Normalized() const;

  /** \brief \ru Возвращает X-координату левого края прямоугольника. Эквивалент GetLeft().
             \en Returns X-coordinate of the left rectangle edge. It is the equivalent of GetLeft() function. \~ 
    \return \ru X-координату левого края прямоугольника.
            \en X-coordinate of the left rectangle edge. \~
  */
  int GetX() const;

  /** \brief \ru Возвращает Y-координату верхнего края прямоугольника. Эквивалент GetTop().
             \en Returns Y-coordinate of the top rectangle edge. It is the equivalent of GetTop() function. \~ 
    \return \ru Y-координату верхнего края прямоугольника.
            \en Y-coordinate of the top rectangle edge. \~
  */
  int GetY() const;

  /** \brief \ru Устанавливает левый край прямоугольника в заданную X-координату. 
                 Может изменить ширину, но не меняет координату правого края прямоугольника. Эквивалент SetX().
             \en Sets the left rectangle edge to the given X-coordinate.
                 Changes width, but it does not change coordinate of the right rectangle edge. It is the equivalent of SetX() function. \~ 
  */
  void SetLeft(int left);

  /** \brief \ru Устанавливает верхний край прямоугольника в заданную Y-координату. 
                 Может изменить высоту, но не меняет координату нижнего края прямоугольника. Эквивалент SetY().
             \en Sets the top rectangle edge to the given Y-coordinate.
                 Changes height, but it does not change coordinate of the bottom rectangle edge. It is the equivalent of SetY() function. \~ 
  */
  void SetTop(int top);

  /** \brief \ru Устанавливает правый край прямоугольника в заданную X-координату. 
                 Может изменить ширину, но не меняет координату левого края прямоугольника.
             \en Sets the right rectangle edge to the given X-coordinate.
                 Changes width, but it does not change coordinate of the left rectangle edge. \~ 
  */
  void SetRight(int right);


  /** \brief \ru Устанавливает нижний край прямоугольника в заданную Y-координату. 
                 Может изменить высоту, но не меняет координату верхнего края прямоугольника.
             \en Sets the bottom rectangle edge to the given Y-coordinate.
                 Changes height, but it does not change coordinate of the top rectangle edge. \~ 
  */
  void SetBottom(int bottom);

  /** \brief \ru Устанавливает левый край прямоугольника в заданную X-координату. 
                 Может изменить ширину, но не меняет координату правого края прямоугольника. Эквивалент SetLeft().
             \en Sets the left rectangle edge to the given X-coordinate.
                 Changes width, but it does not change coordinate of the right rectangle edge. It is the equivalent of SetLeft() function. \~ 
  */
  void SetX(int x);

  /** \brief \ru Устанавливает верхний край прямоугольника в заданную Y-координату. 
                 Может изменить высоту, но не меняет координату нижнего края прямоугольника. Эквивалент SetTop().
             \en Sets the top rectangle edge to the given Y-coordinate.
                 Changes height, but it does not change coordinate of the bottom rectangle edge. It is the equivalent of SetTop() function. \~ 
  */
  void SetY(int y);

  /** \brief \ru Устанавливает верхний левый угол прямоугольника в заданную позицию. 
                 Может изменить размер, но не меняет нижний правый угол прямоугольника.
             \en Sets the top-left rectangle angle to the given position.
                 Changes size, but it does not change the bottom-right rectangle angle. \~ 
  */
  void SetTopLeft(const IntPoint& p);

  /** \brief \ru Устанавливает нижний правый угол прямоугольника в заданную позицию. 
                 Может изменить размер, но не меняет верхний левый угол прямоугольника.
             \en Sets the bottom-right rectangle angle to the given position.
                 Changes size, but it does not change the top-left rectangle angle. \~ 
  */
  void SetBottomRight(const IntPoint& p);

  /** \brief \ru Устанавливает верхний правый угол прямоугольника в заданную позицию. 
                 Может изменить размер, но не меняет нижний левый угол прямоугольника.
             \en Sets the top-right rectangle angle to the given position.
                 Changes size, but it does not change the bottom-left rectangle angle. \~ 
  */
  void SetTopRight(const IntPoint& p);

  /** \brief \ru Устанавливает нижний левый угол прямоугольника в заданную позицию. 
                 Может изменить размер, но не меняет верхний правый угол прямоугольника.
             \en Sets the bottom-left rectangle angle to the given position.
                 Changes size, but it does not change the top-right rectangle angle. \~ 
  */
  void SetBottomLeft(const IntPoint& p);

  /** \brief \ru Возвращает позицию верхнего левого угла прямоугольника.
             \en Returns position of the top-left rectangle angle. \~ 
    \return \ru Позиция левого верхнего угла прямоугольника.
            \en Position of the top-left rectangle angle. \~
  */
  IntPoint GetTopLeft() const;

  /** \brief \ru Возвращает позицию правого нижнего угла прямоугольника.
             \en Returns position of the bottom-right rectangle angle. \~ 
    \return \ru Позиция правого нижнего угла прямоугольника.
            \en Position of the bottom-right rectangle angle. \~
  */
  IntPoint GetBottomRight() const;

  /** \brief \ru Возвращает позицию правого верхнего угла прямоугольника.
             \en Returns position of the top-right rectangle angle. \~ 
    \return \ru Позиция правого верхнего угла прямоугольника.
            \en Position of the top-right rectangle angle. \~
  */
  IntPoint GetTopRight() const;

  /** \brief \ru Возвращает позицию левого нижнего угла прямоугольника.
             \en Returns position of the bottom-left rectangle angle. \~ 
    \return \ru Позиция левого нижнего угла прямоугольника.
            \en Position of the bottom-left rectangle angle. \~
  */
  IntPoint GetBottomLeft() const;

  /** \brief \ru Возвращает центральную точку прямоугольника.
             \en Returns the rectangle center point. \~ 
    \return \ru Центральная точка прямоугольника.
            \en Rectangle center point. \~
  */
  IntPoint GetCenter() const;

  /** \brief \ru Перемещает прямоугольник на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции. 
             \en Moves the rectangle on "dx" value along X-axis and "dy" value along Y-axis. It is all about the current position. \~ 
  */
  inline void Offset(int dx, int dy);

  /** \brief \ru Это перегруженная функция. Перемещает прямоугольник p.GetX() вдоль оси х и p.GetY() вдоль оси y относительно текущей позиции.
             \en Overloaded function. It moves the rectangle p.GetX() along X-axis and p.GetY() along Y-axis, all about the current position. \~ 
  */
  inline void Offset(const IntPoint &p);

  /** \brief \ru Возвращает копию прямоугольника, который перемещается на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции. 
                 Положительные значения перемещают прямоугольник вправо и вниз.
             \en Returns copy of the rectangle that is moved on "dx" value along X-axis and "dy" value along Y-axis, all about the current position.
                 All positive values move the rectangle to right and down. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
  */
  inline IntRect Offseted(int dx, int dy) const;

  /** \brief \ru Это перегруженная функция. Возвращает копию прямоугольника, который перемещается на величину p.GetX() вдоль оси х и 
                 на величину p.GetY() вдоль оси у относительно текущей позиции. Положительные значения перемещают прямоугольник вправо и вниз.
             \en Overloaded function. It returns copy of the rectangle that is moved p.GetX() along X-axis and 
                 p.GetY() along Y-axis, all about the current position. Positive values move the rectangle to right and down. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
  */
  inline IntRect Offseted(const IntPoint &p) const;

  /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданном положении (х, у). Размер прямоугольника не изменяется.
             \en Moves the rectangle by shifting the top-left angle at the defined position (х, у). Rectangle size is not changed. \~ 
  */
  inline void MoveToXY(int x, int t);

  /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданную позицию.
             \en Moves the rectangle by shifting the top-left angle at the defined position. \~ 
  */
  inline void MoveToXY(const IntPoint &p);

  /** \brief \ru Добавляет x1, y1, x2 и y2 к имеющимся координатам прямоугольника.
             \en Adds x1, y1, x2, and y2 values to existing rectangle coordinates. \~ 
  */
  inline void Inflate(int x1, int y1, int x2, int y2);

  /** \brief \ru Возвращает новый прямоугольник с x1, y1, x2 и y2, добавленными к имеющимся координатам этого прямоугольника.
             \en Returns new rectangle with x1, y1, x2, and y2 values, added to existing rectangle coordinates. \~ 
    \return \ru Новый прямоугольник.
            \en New rectangle. \~
  */
  inline IntRect Inflated(int x1, int y1, int x2, int y2) const;

  /** \brief \ru Возвращает размер прямоугольника.
             \en Returns rectangle size. \~ 
    \return \ru Размер прямоугольника.
            \en Rectangle size. \~
  */
  Size GetSize() const;

  /** \brief \ru Возвращает ширину прямоугольника.
             \en Returns rectangle width. \~ 
    \return \ru Ширина прямоугольника.
            \en Rectangle width. \~
  */
  int GetWidth() const;

  /** \brief \ru Возвращает высоту прямоугольника.
             \en Returns rectangle height. \~ 
    \return \ru Высота прямоугольника.
            \en Rectangle height. \~
  */
  int GetHeight() const;

  /** \brief \ru Устанавливает заданную ширину прямоугольнику. Правый край изменяется, а левый нет.
             \en Sets the defined width for the rectangle by changing its right edge. The left rectangle edge is not changed. \~ 
  */
  void SetWidth(int w);

  /** \brief \ru Устанавливает заданную высоту прямоугольнику. Нижний край изменяется, а верхний нет.
             \en Sets the defined height for the rectangle by changing its bottom edge. Top edge is not changed. \~ 
  */
  void SetHeight(int h);

  /** \brief \ru Устанавливает новый размер прямоугольнику. Верхний левый угол не перемещается.
             \en Sets the new size for the rectangle. Top-left angle is not moved. \~ 
  */
  void SetSize(const Size& s);

  /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
             \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
  */
  IntRect operator | (const IntRect& other) const;

  /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника. Возвращает пустой прямоугольник, если нет пересечения.
             \en Returns intersection of the given rectangle and the defined rectangle. It returns empty rectangle if no intersection. \~ 
    \return \ru Пересечение этого прямоугольника и заданного прямоугольника.
            \en Intersection of the given rectangle and the defined rectangle. \~
  */
  IntRect operator & (const IntRect& other) const;

  /** \brief \ru Объединить этот прямоугольник с заданным прямоугольником.
             \en Union of the given rectangle with the defined rectangle. \~ 
  */
  inline IntRect& operator |= (const IntRect& other);


  /** \brief \ru Пересекает этот прямоугольник с заданным прямоугольником.
             \en Intersection of the given rectangle with the defined rectangle. \~ 
  */
  inline IntRect& operator &= (const IntRect& other);

  /** \brief \ru Это перегруженная функция.
                 Возвращает true, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false. 
                 Возвращает true, если прямоугольник целиком внутри этого прямоугольника, а не на краю.
             \en Overloaded function.
                 True if the defined rectangle is inside the given rectangle.
                 True if the defined rectangle is wholly inside the given rectangle, not on the edge.  \~ 
    \return \ru True, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
            \en True if the defined rectangle is inside the given rectangle. \~
  */
  bool RectInRect(const IntRect& other, bool proper = false) const;

  /** \brief \ru Возвращает true, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false. 
                 Возвращает true, если данная точка находится внутри прямоугольника, т.е. не на краю. 
             \en True if the given point is inside the rectangle or on the edge.
                 True if the given point is inside the rectangle, i.e. not on the edge. \~ 
    \return \ru True, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
            \en True if the given point is inside the rectangle or on the edge. \~
  */
  bool PntInRect(const IntPoint& p, bool proper = false) const;

  /** \brief \ru Это перегруженная функция.
                 Возвращает true, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false. 
             \en Overloaded function.
                 True if point (х, у) is inside the rectangle. \~ 
    \return \ru True, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false. 
            \en True if point (х, у) is inside the rectangle. \~
  */
  bool PntInRect(int x, int y) const;

  /** \brief \ru Это перегруженная функция.
                 Возвращает true, если данная точка (x, y) находится внутри или на краю прямоугольника в противном случае возвращает false.
                 Возвращает true, если данная точка (x, y) находится внутри прямоугольника, т.е. не на краю. 
             \en Overloaded function.
                 True if the given point (x, y) is inside the rectangle or on the edge.
                 True if the given point (x, y) is inside the rectangle, i.e. not on the edge. \~ 
    \return \ru True, если данная точка (x, y) находится внутри или на краю прямоугольника в противном случае возвращает false.
            \en True if the given point (x, y) is inside the rectangle or on the edge. \~
  */
  bool PntInRect(int x, int y, bool proper) const;

  /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника. 
             \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
  */
  IntRect United(const IntRect& other) const;

  /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника.
             \en Returns intersection of the given rectangle and the defined rectangle. \~ 
    \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
            \en Bounding rectangle of the given rectangle and the defined rectangle. \~
  */
  inline IntRect Intersected(const IntRect& other) const;

  /** \brief \ru Возвращает true, если этот прямоугольник пересекается с заданным прямоугольником (то есть, есть по меньшей мере один пиксель, 
                 который находится внутри обоих прямоугольников) в противном случае возвращает false.
             \en True if the given rectangle intersects with the defined rectangle. It means that at least one pixel, inside both rectangles, exists. \~ 
    \return \ru True, если этот прямоугольник пересекается с заданным прямоугольником в противном случае возвращает false.
            \en True if the given rectangle intersects with the defined rectangle. \~
  */
  bool Intersects(const IntRect& r) const;

  IntRect FieldsRemoved(const Fields& fields) const;

  inline IntRect &operator+=(const Fields& fields);

  /** \brief \ru Возвращает true, если этот прямоугольник равен указанному, в противном случае возвращает false. 
             \en True if the given rectangle is equal to the specified rectangle. \~ 
    \return \ru True, если этот прямоугольник равен указанному, в противном случае возвращает false.
            \en True if the given rectangle is equal to the specified rectangle. \~
  */
  bool operator == (const IntRect&);

  /** \brief \ru Возвращает true, если этот прямоугольник отличается от указанного, в противном случае возвращает false. 
             \en True if the given rectangle is different from the specified rectangle. \~ 
    \return \ru True, если этот прямоугольник отличается от указанного, в противном случае возвращает false.
            \en True if the given rectangle is different from the specified rectangle. \~
  */
  bool operator != (const IntRect&);

  friend VSN_FUNC_EX bool operator==(const IntRect &, const IntRect &);
  friend VSN_FUNC_EX bool operator!=(const IntRect &, const IntRect &);

  static const IntRect ZERO;   ///< \ru Нулевой прямоугольник. \en Zero rect. 

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
};

VSN_FUNC_EX bool operator==(const IntRect &, const IntRect &);
VSN_FUNC_EX bool operator!=(const IntRect &, const IntRect &);

inline IntRect::IntRect() : m_x1(0) , m_y1(0) , m_x2(-1) , m_y2(-1) {}
inline IntRect::IntRect(int left, int top, int width, int height) : m_x1(left) , m_y1(top) , m_x2(left + width) , m_y2(top + height) {}
inline IntRect::IntRect(const IntPoint& GetTopLeft, const IntPoint& bottomRight) : m_x1(GetTopLeft.GetX()) , m_y1(GetTopLeft.GetY()) , m_x2(bottomRight.GetX()) , m_y2(bottomRight.GetY()) {}
inline IntRect::IntRect(const IntPoint& GetTopLeft, const Size& size) : m_x1(GetTopLeft.GetX()), m_y1(GetTopLeft.GetY()), m_x2(GetTopLeft.GetX() + size.GetWidth()) , m_y2(GetTopLeft.GetY() + size.GetHeight()) {}
inline void IntRect::Init(int x, int y, int w, int h) { m_x1 = x; m_y1 = y; m_x2 = (x + w); m_y2 = (y + h); }
inline void IntRect::InitCoords(int x1, int y1, int x2, int y2) { m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2; }
inline bool IntRect::IsNull() const { return m_x2 == m_x1 && m_y2 == m_y1; }
inline bool IntRect::IsEmpty() const { return m_x1 > m_x2 || m_y1 > m_y2; }
inline bool IntRect::IsValid() const { return m_x1 <= m_x2 && m_y1 <= m_y2; }

inline int IntRect::GetLeft() const { return m_x1; }
inline int IntRect::GetTop() const { return m_y1; }
inline int IntRect::GetRight() const { return m_x2; }
inline int IntRect::GetBottom() const { return m_y2; }

inline int IntRect::GetX() const { return m_x1; }
inline int IntRect::GetY() const { return m_y1; }

inline void IntRect::SetLeft(int pos) { m_x1 = pos; }
inline void IntRect::SetTop(int pos) { m_y1 = pos; }

inline void IntRect::SetRight(int pos) { m_x2 = pos; }
inline void IntRect::SetBottom(int pos) { m_y2 = pos; }

inline void IntRect::SetTopLeft(const IntPoint& p) { m_x1 = p.GetX(); m_y1 = p.GetY(); }
inline void IntRect::SetBottomRight(const IntPoint& p) { m_x2 = p.GetX(); m_y2 = p.GetY(); }
inline void IntRect::SetTopRight(const IntPoint& p) { m_x2 = p.GetX(); m_y1 = p.GetY(); }
inline void IntRect::SetBottomLeft(const IntPoint& p) { m_x1 = p.GetX(); m_y2 = p.GetY(); }

inline void IntRect::SetX(int x) { m_x1 = x; }
inline void IntRect::SetY(int y) { m_y1 = y; }

inline IntPoint IntRect::GetTopLeft() const { return IntPoint(m_x1, m_y1); }
inline IntPoint IntRect::GetBottomRight() const { return IntPoint(m_x2, m_y2); }
inline IntPoint IntRect::GetTopRight() const { return IntPoint(m_x2, m_y1); }
inline IntPoint IntRect::GetBottomLeft() const { return IntPoint(m_x1, m_y2); }
inline IntPoint IntRect::GetCenter() const { return IntPoint((m_x1 + m_x2) / 2, (m_y1 + m_y2) / 2); }

inline int IntRect::GetWidth() const { return  m_x2 - m_x1; }
inline int IntRect::GetHeight() const { return  m_y2 - m_y1; }

inline Size IntRect::GetSize() const { return Size(GetWidth(), GetHeight()); }
inline void IntRect::Offset(int dx, int dy) { m_x1 += dx; m_y1 += dy; m_x2 += dx; m_y2 += dy; }
inline void IntRect::Offset(const IntPoint& pnt) { m_x1 += pnt.GetX(); m_y1 += pnt.GetY(); m_x2 += pnt.GetX(); m_y2 += pnt.GetY(); }
inline IntRect IntRect::Offseted(int dx, int dy) const { return IntRect(IntPoint(m_x1 + dx, m_y1 + dy), IntPoint(m_x2 + dx, m_y2 + dy)); }
inline IntRect IntRect::Offseted(const IntPoint& p) const { return IntRect(IntPoint(m_x1 + p.GetX(), m_y1 + p.GetY()), IntPoint(m_x2 + p.GetX(), m_y2 + p.GetY())); }

inline void IntRect::MoveToXY(int x, int y) { m_x2 += x - m_x1; m_y2 += y - m_y1; m_x1 = x; m_y1 = y; }
inline void IntRect::MoveToXY(const IntPoint& p) { m_x2 += p.GetX() - m_x1; m_y2 += p.GetY() - m_y1; m_x1 = p.GetX(); m_y1 = p.GetY(); }
inline IntRect IntRect::Inflated(int x1, int y1, int x2, int y2) const { return IntRect(IntPoint(m_x1 + x1, m_y1 + y1), IntPoint(m_x2 + x2, m_y2 + y2)); }
inline void IntRect::Inflate(int x1, int y1, int x2, int y2) { m_x1 += x1; m_y1 += y1; m_x2 += x2; m_y2 += y2; }

inline void IntRect::SetWidth(int w) { m_x2 = (m_x1 + w); }
inline void IntRect::SetHeight(int h) { m_y2 = (m_y1 + h); }
inline void IntRect::SetSize(const Size& sz) { m_x2 = (sz.GetWidth() + m_x1); m_y2 = (sz.GetHeight() + m_y1); }

inline bool IntRect::PntInRect(int x, int y, bool aproper) const { return PntInRect(IntPoint(x, y), aproper); }
inline bool IntRect::PntInRect(int x, int y) const { return PntInRect(IntPoint(x, y), false); }

inline IntRect& IntRect::operator|=(const IntRect& other) { *this = *this | other; return *this; }
inline IntRect& IntRect::operator&=(const IntRect& other) { *this = *this & other; return *this; }

inline bool IntRect::operator == (const IntRect& other) { return m_x1 == other.m_x1 && m_x2 == other.m_x2 && m_y1 == other.m_y1 && m_y2 == other.m_y2; }

inline bool IntRect::operator != (const IntRect& other) { return m_x1 != other.m_x1 || m_x2 != other.m_x2 || m_y1 != other.m_y1 || m_y2 != other.m_y2; }

inline IntRect operator+(const IntRect& rectangle, const Fields& fields)
{
    return IntRect(IntPoint(rectangle.GetLeft() - fields.GetLeft(), rectangle.GetTop() - fields.GetTop()),
        IntPoint(rectangle.GetRight() + fields.GetRight(), rectangle.GetBottom() + fields.GetBottom()));
}


//----------------------------------------------------------------------------
//
/** \brief \ru Класс DblRect описывает прямоугольник в плоскости и использует двойную точность.
           \en DblRect class defines rectangle in the plane using double-precision. \~
    \details \ru Прямоугольник, как правило, выражается в виде верхнего левого угла и размера.
                 Прямоугольник может быть построен с помощью целочисленных координат слева, сверху, ширины и высоты, или при помощи классов DblRect и DblSize.
                 Класс IntRect предоставляет набор функций, которые возвращают необходимые координаты прямоугольника и позволяют их инициализировать.
                 Класс IntRect также предоставляет функции, которые дают возможность перемещать прямоугольник относительно его координат и т.д. \n
             \en Rectangle is typically expressed as top-left angle and size.
                 Rectangle can be constructed with integer coordinates of left, top, width and height, or with DblPoint and Size classes.
                 IntRect class provides a set of functions that return necessary coordinates of the rectangle and allow initializing them.
                 IntRect class also provides functions for moving the rectangle about its coordinates, etc. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS DblRect
{
public:
    /// \ru Конструктор по умолчанию. Создает пустой прямоугольник. \en Default constructor for creating empty rectangle.
    DblRect() : m_x(0.0), m_y(0.0), m_width(0.0), m_height(0.0) {}
    DblRect(const DblPoint& topleft, const DoubleSize& size);
    DblRect(const DblPoint& topleft, const DblPoint& bottomRight);
    DblRect(double left, double top, double width, double height);
    DblRect(const IntRect& rect);
public:
    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
               \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
    */
    void Init(double x, double y, double w, double h);
    /** \brief \ru Инициализация прямоугольника с заданием координат верхнего левого угла и размера прямоугольника.
               \en Initializes the rectangle with setting top-left angle coordinates and rectangle size. \~
    */
    void InitCoords(double x1, double y1, double x2, double y2);

    /** \brief \ru Возвращает true, если прямоугольник пустой, в противном случае возвращает false.
               \en True if rectangle is empty. \~
        \details \ru Нулевой прямоугольник имеет ширину и высоту, которые равны 0 (т.е. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1).
                     Нулевой прямоугольник также является пустым и, следовательно, не является действительным.
                 \en Null rectangle has width and height that equal 0, i.e. GetRight() == GetLeft() - 1 и GetBottom() == GetTop() - 1.
                     Null rectangle is also empty and hence not valid.  \~
        \return \ru True, если прямоугольник пустой.
                \en True if rectangle is empty. \~
    */
    bool IsNull() const;
    bool IsEmpty() const;
    bool IsValid() const;
    /** \brief \ru Возвращает нормализованный прямоугольник, т.е. прямоугольник, который не имеет отрицательную ширину и высоту.
               \en Returns normalized rectangle, i.e. the rectangle has no negative width and height. \~
        \note \ru Если GetWidth() < 0, функция меняет местами левый и правый углы, а также, если GetHeight() < 0, то она меняет местами верхний и нижний углы.
              \en If GetWidth() < 0, then function swaps the left and right angles. If GetHeight() < 0, then it swaps the top and bottom angles. \~
        \return \ru Нормализованный прямоугольник.
                \en Normalized rectangle. \~
    */
    DblRect Normalized() const;

    double GetLeft() const{ return m_x; }
    double GetTop() const{ return m_y; }
    double GetRight() const{ return m_x + m_width; }
    double GetBottom() const{ return m_y + m_height; }

    inline double GetX() const;
    inline double GetY() const;
    inline void SetLeft(double pos);
    inline void SetTop(double pos);
    inline void SetRight(double pos);
    inline void SetBottom(double pos);

    inline void SetX(double pos) { SetLeft(pos); }
    inline void SetY(double pos) { SetTop(pos); }

    /** \brief \ru Возвращает позицию верхнего левого угла прямоугольника.
               \en Returns position of the top-left rectangle angle. \~
        \return \ru Позиция левого верхнего угла прямоугольника.
                \en Position of the top-left rectangle angle. \~
    */
    inline DblPoint GetTopLeft() const{ return DblPoint(m_x, m_y); }
    inline DblPoint GetBottomRight() const{ return DblPoint(m_x + m_width, m_y + m_height); }
    inline DblPoint GetTopRight() const{ return DblPoint(m_x + m_width, m_y); }
    inline DblPoint GetBottomLeft() const{ return DblPoint(m_x, m_y + m_height); }
    inline DblPoint GetCenter() const;

    /** \brief \ru Устанавливает верхний левый угол прямоугольника в заданную позицию.
                   Может изменить размер, но не меняет нижний правый угол прямоугольника.
               \en Sets the top-left rectangle angle to the given position.
                   Changes size, but it does not change the bottom-right rectangle angle. \~
    */
    inline void SetTopLeft(const DblPoint& p);
    /** \brief \ru Устанавливает нижний правый угол прямоугольника в заданную позицию.
                   Может изменить размер, но не меняет верхний левый угол прямоугольника.
               \en Sets the bottom-right rectangle angle to the given position.
                   Changes size, but it does not change the top-left rectangle angle. \~
    */
    inline void SetBottomRight(const DblPoint& p);
    inline void SetTopRight(const DblPoint& p);
    inline void SetBottomLeft(const DblPoint& p);

    /** \brief \ru Перемещает прямоугольник на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции.
                \en Moves the rectangle on "dx" value along X-axis and "dy" value along Y-axis. It is all about the current position. \~
    */
    void Offset(double dx, double dy);
    /** \brief \ru Это перегруженная функция. Перемещает прямоугольник p.GetX() вдоль оси х и p.GetY() вдоль оси y относительно текущей позиции.
               \en Overloaded function. It moves the rectangle p.GetX() along X-axis and p.GetY() along Y-axis, all about the current position. \~
    */
    void Offset(const DblPoint &p);

    /** \brief \ru Возвращает копию прямоугольника, который перемещается на величину dx вдоль оси х и на величину dy вдоль оси у относительно текущей позиции.
                   Положительные значения перемещают прямоугольник вправо и вниз.
               \en Returns copy of the rectangle that is moved on "dx" value along X-axis and "dy" value along Y-axis, all about the current position.
                   All positive values move the rectangle to right and down. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    DblRect Offseted(double dx, double dy) const;
    /** \brief \ru Это перегруженная функция. Возвращает копию прямоугольника, который перемещается на величину p.GetX() вдоль оси х и
                   на величину p.GetY() вдоль оси у относительно текущей позиции. Положительные значения перемещают прямоугольник вправо и вниз.
               \en Overloaded function. It returns copy of the rectangle that is moved p.GetX() along X-axis and
                   p.GetY() along Y-axis, all about the current position. Positive values move the rectangle to right and down. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    inline DblRect Offseted(const DblPoint& p) const;

    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданном положении (х, у). Размер прямоугольника не изменяется.
               \en Moves the rectangle by shifting the top-left angle at the defined position (х, у). Rectangle size is not changed. \~
    */
    inline void MoveToXY(double x, double y);
    /** \brief \ru Перемещает прямоугольник, перенося верхний левый угол в заданную позицию.
               \en Moves the rectangle by shifting the top-left angle at the defined position. \~
    */
    inline void MoveToXY(const DblPoint& p);

    /** \brief \ru Добавляет x1, y1, x2 и y2 к имеющимся координатам прямоугольника.
               \en Adds x1, y1, x2, and y2 values to existing rectangle coordinates. \~
    */
    inline void Inflate(double x1, double y1, double x2, double y2);
    /** \brief \ru Возвращает новый прямоугольник с x1, y1, x2 и y2, добавленными к имеющимся координатам этого прямоугольника.
               \en Returns new rectangle with x1, y1, x2, and y2 values, added to existing rectangle coordinates. \~
        \return \ru Новый прямоугольник.
                \en New rectangle. \~
    */
    inline DblRect Inflated(double x1, double y1, double x2, double y2) const;

    inline DoubleSize GetSize() const;
    inline double GetWidth() const;
    inline double GetHeight() const;
    inline void SetWidth(double w);
    inline void SetHeight(double h);
    inline void SetSize(const DoubleSize& other);

    DblRect operator|(const DblRect& rc) const;
    DblRect operator&(const DblRect& rc) const;
    inline DblRect& operator|=(const DblRect& rc);
    inline DblRect& operator&=(const DblRect& rc);

    /** \brief \ru Это перегруженная функция.
                   Возвращает true, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
                   Возвращает true, если прямоугольник целиком внутри этого прямоугольника, а не на краю.
                \en Overloaded function.
                    True if the defined rectangle is inside the given rectangle.
                    True if the defined rectangle is wholly inside the given rectangle, not on the edge.  \~
        \return \ru True, если данный прямоугольник находится внутри этого прямоугольника в противном случае возвращает false.
                \en True if the defined rectangle is inside the given rectangle. \~
    */
    bool RectInRect(const DblRect& other) const;
    /** \brief \ru Возвращает true, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
                   Возвращает true, если данная точка находится внутри прямоугольника, т.е. не на краю.
               \en True if the given point is inside the rectangle or on the edge.
                   True if the given point is inside the rectangle, i.e. not on the edge. \~
        \return \ru True, если данная точка находится внутри или на краю прямоугольника в противном случае возвращает false.
                \en True if the given point is inside the rectangle or on the edge. \~
    */
    bool PntInRect(const DblPoint& p) const;
    /** \brief \ru Это перегруженная функция.
                   Возвращает true, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false.
               \en Overloaded function.
                   True if point (х, у) is inside the rectangle. \~
        \return \ru True, если точка (х, у) находится внутри этого прямоугольника, в противном случае возвращает false.
                \en True if point (х, у) is inside the rectangle. \~
    */
    bool PntInRect(double x, double y) const;

    /** \brief \ru Возвращает ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
               \en Returns bounding rectangle of the given rectangle and the defined rectangle. \~
        \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
                \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    DblRect United(const DblRect& other) const;

    /** \brief \ru Возвращает пересечение этого прямоугольника и заданного прямоугольника.
               \en Returns intersection of the given rectangle and the defined rectangle. \~
        \return \ru Ограничивающий прямоугольник этого прямоугольника и заданного прямоугольника.
                \en Bounding rectangle of the given rectangle and the defined rectangle. \~
    */
    DblRect Intersected(const DblRect& other) const;

    /** \brief \ru Возвращает true, если этот прямоугольник пересекается с заданным прямоугольником (то есть, есть по меньшей мере один пиксель,
                   который находится внутри обоих прямоугольников) в противном случае возвращает false.
                \en True if the given rectangle intersects with the defined rectangle. It means that at least one pixel, inside both rectangles, exists. \~
        \return \ru True, если этот прямоугольник пересекается с заданным прямоугольником в противном случае возвращает false.
                \en True if the given rectangle intersects with the defined rectangle. \~
    */
    bool Intersects(const DblRect& other) const;

    inline DblRect FieldsAdded(const DoubleFields& fields) const;
    inline DblRect FieldsRemoved(const DoubleFields& fields) const;
    inline DblRect &operator+=(const DoubleFields &fields);
    inline DblRect &operator-=(const DoubleFields &fields);

    friend inline bool operator==(const DblRect &, const DblRect &);
    friend inline bool operator!=(const DblRect &, const DblRect &);

    inline IntRect ToRect() const;
    IntRect ToSmallestRect() const;
private:
    double m_x;
    double m_y;
    double m_width;
    double m_height;
};

inline bool operator==(const DblRect& , const DblRect& );
inline bool operator!=(const DblRect& , const DblRect& );

inline DblRect::DblRect(double left, double top, double width, double height) : m_x(left), m_y(top), m_width(width), m_height(height) {}
inline DblRect::DblRect(const DblPoint& topLeft, const DoubleSize& size) : m_x(topLeft.GetX()), m_y(topLeft.GetY()), m_width(size.GetWidth()), m_height(size.GetHeight()) {}
inline DblRect::DblRect(const DblPoint& topLeft, const DblPoint& bottomRight) : m_x(topLeft.GetX()), m_y(topLeft.GetY()), m_width(bottomRight.GetX() - topLeft.GetX()), m_height(bottomRight.GetY() - topLeft.GetY()){}
inline DblRect::DblRect(const IntRect& other) : m_x(other.GetX()), m_y(other.GetY()), m_width(other.GetWidth()), m_height(other.GetHeight()) {}

inline void DblRect::Init(double x, double y, double w, double h) { m_x = x; m_y = y; m_width = w; m_height = h; }
inline void DblRect::InitCoords(double x1, double y1, double x2, double y2) { m_x = x1; m_y = y1; m_width = x2 - x1; m_height = y2 - y1; }

inline bool DblRect::IsNull() const { return m_width == 0. && m_height == 0.; }
inline bool DblRect::IsEmpty() const { return m_width <= 0. || m_height <= 0.; }
inline bool DblRect::IsValid() const { return m_width > 0. && m_height > 0.; }
inline double DblRect::GetX() const { return m_x; }
inline double DblRect::GetY() const { return m_y; }

inline void DblRect::SetLeft(double pos) { double diff = pos - m_x; m_x += diff; m_width -= diff; }
inline void DblRect::SetRight(double pos) { m_width = pos - m_x; }
inline void DblRect::SetTop(double pos) { double diff = pos - m_y; m_y += diff; m_height -= diff; }
inline void DblRect::SetBottom(double pos) { m_height = pos - m_y; }

inline void DblRect::SetTopLeft(const DblPoint& p) { SetLeft(p.GetX()); SetTop(p.GetY()); }
inline void DblRect::SetTopRight(const DblPoint& p) { SetRight(p.GetX()); SetTop(p.GetY()); }
inline void DblRect::SetBottomLeft(const DblPoint& p) { SetLeft(p.GetX()); SetBottom(p.GetY()); }
inline void DblRect::SetBottomRight(const DblPoint &p) { SetRight(p.GetX()); SetBottom(p.GetY()); }
inline DblPoint DblRect::GetCenter() const { return DblPoint(m_x + m_width * 0.5, m_y + m_height * 0.5); }

inline double DblRect::GetWidth() const { return m_width; }
inline void DblRect::SetWidth(double w) { m_width = w; }
inline double DblRect::GetHeight() const { return m_height; }
inline void DblRect::SetHeight(double h) { m_height = h; }
inline DoubleSize DblRect::GetSize() const { return DoubleSize(m_width, m_height); }

inline void DblRect::Offset(double dx, double dy) { m_x += dx; m_y += dy; }
inline void DblRect::Offset(const DblPoint &p) { m_x += p.GetX(); m_y += p.GetY(); }

inline void DblRect::MoveToXY(double x, double y) { m_x = x; m_y = y; }
inline void DblRect::MoveToXY(const DblPoint& p) { m_x = p.GetX(); m_y = p.GetY(); }

inline DblRect DblRect::Offseted(double dx, double dy) const { return DblRect(m_x + dx, m_y + dy, m_width, m_height); }
inline DblRect DblRect::Offseted(const DblPoint& p) const { return DblRect(m_x + p.GetX(), m_y + p.GetY(), m_width, m_height); }

inline void DblRect::Inflate(double x1, double y1, double x2, double y2) { m_x += x1; m_y += y1; m_width += x2 - x1; m_height += y2 - y1; }
inline DblRect DblRect::Inflated(double x1, double y1, double x2, double y2) const { return DblRect(m_x + x1, m_y + y1, m_width + x2 - x1, m_height + y2 - y1); }

inline void DblRect::SetSize(const DoubleSize& sz) { m_width = sz.GetWidth(); m_height = sz.GetHeight(); }

inline DblRect& DblRect::operator|=(const DblRect& r) { *this = *this | r; return *this; }
inline DblRect& DblRect::operator&=(const DblRect &r) { *this = *this & r; return *this; }

inline bool operator==(const DblRect& rc1, const DblRect& rc2)
{
    return Compare(rc1.m_x, rc2.m_x) && Compare(rc1.m_y, rc2.m_y)
        && Compare(rc1.m_width, rc2.m_width) && Compare(rc1.m_height, rc2.m_height);
}

inline bool operator!=(const DblRect &r1, const DblRect &r2)
{
    return !Compare(r1.m_x, r2.m_x) || !Compare(r1.m_y, r2.m_y)
        || !Compare(r1.m_width, r2.m_width) || !Compare(r1.m_height, r2.m_height);
}

inline IntRect DblRect::ToRect() const
{
    return IntRect(vRound(m_x), vRound(m_y), vRound(m_width), vRound(m_height));
}

inline DblRect operator+(const DblRect& lhs, const DoubleFields& rhs)
{
    return DblRect(DblPoint(lhs.GetLeft() - rhs.GetLeft(), lhs.GetTop() - rhs.GetTop()),
        DoubleSize(lhs.GetWidth() + rhs.GetLeft() + rhs.GetRight(), lhs.GetHeight() + rhs.GetTop() + rhs.GetBottom()));
}

inline DblRect operator+(const DoubleFields &lhs, const DblRect &rhs)
{
    return DblRect(DblPoint(rhs.GetLeft() - lhs.GetLeft(), rhs.GetTop() - lhs.GetTop()),
        DoubleSize(rhs.GetWidth() + lhs.GetLeft() + lhs.GetRight(), rhs.GetHeight() + lhs.GetTop() + lhs.GetBottom()));
}

inline DblRect operator-(const DblRect &lhs, const DoubleFields &rhs)
{
    return DblRect(DblPoint(lhs.GetLeft() + rhs.GetLeft(), lhs.GetTop() + rhs.GetTop()),
        DoubleSize(lhs.GetWidth() - rhs.GetLeft() - rhs.GetRight(), lhs.GetHeight() - rhs.GetTop() - rhs.GetBottom()));
}

inline DblRect DblRect::FieldsAdded(const DoubleFields& fields) const
{
    return DblRect(DblPoint(m_x - fields.GetLeft(), m_y - fields.GetTop()),
        DoubleSize(m_width + fields.GetLeft() + fields.GetRight(), m_height + fields.GetTop() + fields.GetBottom()));
}

inline DblRect DblRect::FieldsRemoved(const DoubleFields& fields) const
{
    return DblRect(DblPoint(m_x + fields.GetLeft(), m_y + fields.GetTop()),
        DoubleSize(m_width - fields.GetLeft() - fields.GetRight(), m_height - fields.GetTop() - fields.GetBottom()));
}

inline DblRect& DblRect::operator+=(const DoubleFields& fields)
{
    *this = FieldsAdded(fields);
    return *this;
}

inline DblRect& DblRect::operator-=(const DoubleFields& fields)
{
    *this = FieldsRemoved(fields);
    return *this;
}

VSN_END_NAMESPACE

#endif /* __VSN_RECT_H */
