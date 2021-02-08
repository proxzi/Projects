////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Итератор с произвольным доступом.
           \en Iterator with an arbitrary access. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ITERATOR_H
#define __VSN_ITERATOR_H

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

//------------------------------------------------------------------------------
/** \brief \ru Итератор с произвольным доступом.
           \en Iterator with an arbitrary access. \~
    \ingroup Vision_Base
*/
// ---
template <class T> struct RandomAccessIterator
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RandomAccessIterator() : m_ptr(0) {}
    /// \ru Конструктор с указателем на объект. \en Constructor with pointer to object. \~
    explicit RandomAccessIterator(T* ptr) : m_ptr(ptr) {}
public:
    /// \ru Указатель на объект. \en Pointer to object. \~
    T* operator ->() const { return m_ptr; }
    /// \ru Ссылка на объект. \en Reference to object. \~
    T& operator *() const { return *m_ptr; }
    /// \ru Преинкремент указателя. \en Pointer preincrement. \~
    RandomAccessIterator<T>& operator ++() { ++m_ptr; return *this; }
    /// \ru Постинкремент указателя. \en Pointer post-increment. \~
    RandomAccessIterator<T> operator ++(int) { RandomAccessIterator<T> it = *this; ++m_ptr; return it; }
    /// \ru Предекремент указателя. \en Pointer pre-decrement. \~
    RandomAccessIterator<T>& operator --() { --m_ptr; return *this; }
    /// \ru Постдекремент указателя. \en Pointer postdecrement. \~
    RandomAccessIterator<T> operator --(int) { RandomAccessIterator<T> it = *this; --m_ptr; return it;}
    /// \ru Добавить смещение к указателю. \en Adds offset to pointer. \~
    RandomAccessIterator<T>& operator +=(int value) { m_ptr += value; return *this; }
    /// \ru Вычесть смещение от указателя. \en Subtracts offset from pointer. \~
    RandomAccessIterator<T>& operator -=(int value) { m_ptr -= value; return *this; }

    /// \ru Добавить смещение к указателю. \en Adds offset to pointer. \~
    RandomAccessIterator<T> operator +(int value) const { return RandomAccessIterator<T>(m_ptr + value); }
    /// \ru Вычесть смещение от указателя. \en Subtracts offset from pointer. \~
    RandomAccessIterator<T> operator -(int value) const { return RandomAccessIterator<T>(m_ptr - value); }
    /// \ru Вычислить смещение на другой итератор. \en Calculates offset to another iterator. \~
    int operator -(const RandomAccessIterator& rhs) const { return (int)(m_ptr - rhs.m_ptr); }
    /// \ru Проверить равенство с другим итератором. \en Checks equality to another iterator. \~
    bool operator ==(const RandomAccessIterator& rhs) const { return m_ptr == rhs.m_ptr; }
    /// \ru Проверить неравенство с другим итератором. \en Checks inequality to another iterator. \~
    bool operator !=(const RandomAccessIterator& rhs) const { return m_ptr != rhs.m_ptr; }
    /// \ru Проверить, итератор меньшее, чем другой итератор. \en Checks if iterator is less than another iterator. \~
    bool operator <(const RandomAccessIterator& rhs) const { return m_ptr < rhs.m_ptr; }
    /// \ru Проверить, итератор большее, чем другой итератор. \en Checks if iterator is greater than another iterator. \~
    bool operator >(const RandomAccessIterator& rhs) const { return m_ptr > rhs.m_ptr; }
    /// \ru Проверить, итератор меньшее или равен другому итератору. \en Checks if iterator is less than or equal to another iterator. \~
    bool operator <=(const RandomAccessIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
    /// \ru Проверить, итератор больше или равен другому итератору. \en Checks if iterator is greater than or equal to another iterator. \~
    bool operator >=(const RandomAccessIterator& rhs) const { return m_ptr >= rhs.m_ptr; }

        T* m_ptr; ///< \ru Указатель на объект. \en Pointer to object.
};

/// Итератор с произвольным доступом.
template <class T> struct RandomAccessConstIterator
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    RandomAccessConstIterator() : m_ptr(0) {}
    /// \ru Конструктор с указателем на объект. \en Constructor with an object pointer. \~
    explicit RandomAccessConstIterator(T* ptr) : m_ptr(ptr) {}
    /// \ru Конструктор c const iterator. \en Constructor with const iterator. \~
    RandomAccessConstIterator(const RandomAccessIterator<T>& rhs) : m_ptr(rhs.m_ptr) {}
public:
    /// \ru Присвоить const iterator. \en Assigns to const iterator. \~
    RandomAccessConstIterator<T>& operator =(const RandomAccessIterator<T>& rhs) { m_ptr = rhs.m_ptr; return *this; }
    /// \ru Указатель на объект. \en Pointer to object. \~
    const T* operator ->() const { return m_ptr; }
    /// \ru Разыменовать указатель. \en Dereferences pointer. \~
    const T& operator *() const { return *m_ptr; }
    /// \ru Преинкремент указателя. \en Pointer preincrement. \~
    RandomAccessConstIterator<T>& operator ++() { ++m_ptr; return *this; }
    /// \ru Постинкремент указателя. \en Pointer post-increment. \~
    RandomAccessConstIterator<T> operator ++(int) { RandomAccessConstIterator<T> it = *this; ++m_ptr; return it; }
    /// \ru Предекремент указателя. \en Pointer pre-decrement. \~
    RandomAccessConstIterator<T>& operator --() { --m_ptr; return *this; }
    /// \ru Постдекремент указателя. \en Pointer postdecrement. \~
    RandomAccessConstIterator<T> operator --(int) { RandomAccessConstIterator<T> it = *this; --m_ptr; return it; }
    /// \ru Добавить смещение к указателю. \en Adds offset to pointer. \~
    RandomAccessConstIterator<T>& operator +=(int value) { m_ptr += value; return *this; }
    /// \ru Вычесть смещение от указателя. \en Subtracts offset from pointer. \~
    RandomAccessConstIterator<T>& operator -=(int value) { m_ptr -= value; return *this; }
    /// \ru Добавить смещение к указателю. \en Adds offset to pointer. \~
    RandomAccessConstIterator<T> operator +(int value) const { return RandomAccessConstIterator<T>(m_ptr + value); }
    /// \ru Вычесть смещение от указателя. \en Subtracts offset from pointer. \~
    RandomAccessConstIterator<T> operator -(int value) const { return RandomAccessConstIterator<T>(m_ptr - value); }
    /// \ru Вычислить смещение к другому итератору. \en Calculates offset to another iterator. \~
    int operator -(const RandomAccessConstIterator& rhs) const { return (int)(m_ptr - rhs.m_ptr); }
    /// \ru Проверить равенство с другим итератором. \en Checks equality with another iterator. \~
    bool operator ==(const RandomAccessConstIterator& rhs) const { return m_ptr == rhs.m_ptr; }
    /// \ru Проверить неравенство с другим итератором. \en Checks inequality with another iterator. \~
    bool operator !=(const RandomAccessConstIterator& rhs) const { return m_ptr != rhs.m_ptr; }
    /// \ru Проверить, итератор меньшее, чем другой итератор. \en Checks if iterator is less than another iterator. \~
    bool operator <(const RandomAccessConstIterator& rhs) const { return m_ptr < rhs.m_ptr; }
    /// \ru Проверить, итератор большее, чем другой итератор. \en Checks if iterator is greater than another iterator. \~
    bool operator >(const RandomAccessConstIterator& rhs) const { return m_ptr > rhs.m_ptr; }
    /// \ru Проверить, итератор меньшее или равен другому итератору. \en Checks if iterator is less than or equal to another iterator. \~
    bool operator <=(const RandomAccessConstIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
    /// \ru Проверить, итератор больше или равен другому итератору. \en Checks if iterator is greater than or equal to another iterator. \~
    bool operator >=(const RandomAccessConstIterator& rhs) const { return m_ptr >= rhs.m_ptr; }

        T* m_ptr; ///< \ru Указатель на объект. \en Pointer to object.
};

VSN_END_NAMESPACE

#endif // __VSN_ITERATOR_H

