////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Системозависимые атомарные операции.
         Если требуются атомарные операции, должен использоваться этот файл (<atomic> не использовать!!!).
         \en System-dependent atomic operations.
         If atomic operations are required, this file should used (<atomic> must not be used!!!).\~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __SYSTEM_ATOMIC_H
#define __SYSTEM_ATOMIC_H

#include <system_types.h>
#include <system_cpp_standard.h>
#include <tool_mutex.h>

//------------------------------------------------------------------------------
// \ru Использование атомарных операций согласно стандарту C++11.
// \en Using atomic operations according to C++11 standard.
//     
//---

#ifdef STANDARD_C11
#ifndef _NOT_USE_ATOMIC
#define STANDARD_C11_ATOMIC
#endif
#endif

#ifdef STANDARD_C11_ATOMIC

#include <atomic>

typedef std::atomic_ptrdiff_t use_count_type; // \ru Потокобезопасный тип счётчика ссылок. \en Thread-safe references count type.
typedef std::atomic_size_t    serial_type;    // \ru Потокобезопасный тип счётчика ссылок. \en Thread-safe references count type.
typedef std::atomic<bool>     atomic_bool;    // \ru Потокобезопасный логический тип. \en Thread-safe boolean type.

//------------------------------------------------------------------------------
/** \ru Получить значение. \en Get value.
*/
//---
template <class AtomicType, class Type>
Type LoadTypeValue( const AtomicType & v ) {
  return v.load();
}

//------------------------------------------------------------------------------
/** \ru Установить значение. \en Get value.
*/
//---
template <class AtomicType>
void StoreTypeValue( const AtomicType & src, AtomicType & dst ) {
  dst.store( src.load() );
}

//------------------------------------------------------------------------------
/** \ru Установить значение. \en Get value.
*/
//---
template <class AtomicType, class Type>
void StoreTypeValue( const Type src, AtomicType & dst ) {
  dst.store( src );
}

//------------------------------------------------------------------------------
/** \ru Получить значение. \en Get value.
*/
//---
inline serial_type SerialTypeValue( const serial_type & v ) {
  return v.load();
}
inline use_count_type UseCountValue( const use_count_type & v ) {
  return v.load();
}

#else

//------------------------------------------------------------------------------
// \ru Шаблонный класс, работающий с целочисленными типами данных. Базовый класс для потокобезопасных счётчиков. 
// \en Template class working with integer data types. Base class for thread-safe counters.
//--
template< class Type >
class atomic_itype
{
protected:
  CommonMutex m_lock;
  Type        m_value;
public:
  atomic_itype() {}
  atomic_itype( const atomic_itype & t ) : m_value( t.m_value ) {}
  atomic_itype( const Type t ) : m_value( t ) {}

  // \ru Операторы присваивания. \en Assignment operators.
  atomic_itype & operator = ( const atomic_itype & t ) { ScopedLock l( &m_lock ); m_value = t.m_value; return *this; }
  atomic_itype & operator = ( Type t ) { ScopedLock l( &m_lock ); m_value = t; return *this; }

  // \ru Операторы инкремента и декремента. \en Increment and decrement operators.
  atomic_itype & operator ++ () { ScopedLock l( &m_lock ); ++m_value; return *this; } // prefix ++
  atomic_itype & operator -- () { ScopedLock l( &m_lock ); --m_value; return *this; } // prefix --
  Type operator ++ ( int ) { // postfix ++
    Type t = m_value;
    {
      ScopedLock l( &m_lock );
      ++m_value;
    }
    return t;
  }
  Type operator -- ( int ) { // postfix --
    Type t = m_value;
    {
      ScopedLock l( &m_lock );
      --m_value;
    }
    return t;
  }

  // \ru Операторы сравнения. \en Comparison operators.
  bool operator == ( const atomic_itype & t ) const { return m_value == t.m_value; }
  bool operator != ( const atomic_itype & t ) const { return m_value != t.m_value; }
  bool operator < ( const atomic_itype & t )  const { return m_value < t.m_value; }
  bool operator > ( const atomic_itype & t )  const { return m_value > t.m_value; }
  bool operator <= ( const atomic_itype & t ) const { return m_value <= t.m_value; }
  bool operator >= ( const atomic_itype & t ) const { return m_value >= t.m_value; }

  // \ru Доступ к данным. \en Data access.
  Type operator()() const { return m_value; }

};

//------------------------------------------------------------------------------
// \ru Потокобезопасный логический тип. \en Thread-safe boolean type.
//--
class atomic_bool : public atomic_itype<int>
{
public:
  atomic_bool() {}

  atomic_bool( const atomic_bool & t ) : atomic_itype<int>( t.m_value ) {}
  atomic_bool( const bool t ) : atomic_itype<int>( t ? 1 : 0 ) {}
  atomic_bool( const int t ) : atomic_itype<int>( t != 0 ? 1 : 0 ) {}

  // \ru Операторы присваивания. \en Assignment operators.
  atomic_bool & operator = ( const atomic_bool & t ) { ScopedLock l( &m_lock ); m_value = t.m_value; return *this; }
  atomic_bool & operator = ( bool t ) { ScopedLock l( &m_lock ); m_value = t ? 1 : 0; return *this; }
  atomic_bool & operator = ( int t ) { ScopedLock l( &m_lock ); m_value = t != 0 ? 1 : 0; return *this; }

  bool operator && ( bool t ) { return t == !!m_value; }
  bool operator || ( bool t ) { return t || !!m_value; }

  // \ru Доступ к данным. \en Data access.
  bool operator()() const { return !!m_value; }

private:
  // \ru Операторы инкремента и декремента не разрешены. \en Increment and decrement operators not allowed.
  atomic_bool & operator ++ ();
  atomic_bool & operator -- ();
  bool operator ++ ( int );
  bool operator -- ( int );
};

typedef atomic_itype<size_t>     serial_type;    // \ru Потокобезопасный тип счётчика ссылок. \en Thread-safe references count type.
typedef atomic_itype<ptrdiff_t>  use_count_type; // \ru Потокобезопасный тип счётчика ссылок. \en Thread-safe references count type.

//------------------------------------------------------------------------------
/** \ru Получить значение. \en Get value.
*/
//---
template <class AtomicType, class Type>
Type LoadTypeValue( const AtomicType & v ) {
  return v();
}

//------------------------------------------------------------------------------
/** \ru Установить значение. \en Get value.
*/
//---
template <class AtomicType>
void StoreTypeValue( const AtomicType & src, AtomicType & dst ) {
  dst = src;
}

//------------------------------------------------------------------------------
/** \ru Установить значение. \en Get value.
*/
//---
template <class AtomicType, class Type>
void StoreTypeValue( const Type src, AtomicType & dst ) {
  dst = src;
}

//------------------------------------------------------------------------------
/** \ru Получить значение. \en Get value.
*/
//---
inline size_t SerialTypeValue( const serial_type & v ) {
  return v();
}
inline ptrdiff_t UseCountValue( const use_count_type & v ) {
  return v();
}

#endif // STANDARD_C11_ATOMIC


#endif // __SYSTEM_ATOMIC_H
