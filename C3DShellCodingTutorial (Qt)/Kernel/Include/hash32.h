﻿////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Хэш.
         \en Hash. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __HASH32_H
#define __HASH32_H

#include <io_define.h>
#include <tool_cstring.h>


class writer;
class reader;


////////////////////////////////////////////////////////////////////////////////
//
// \ru Oпределение простого имени \en Definition of simple name 
//
////////////////////////////////////////////////////////////////////////////////

// Activate to check compilation // #define SIMPLENAME_AS_CLASS

#ifndef SIMPLENAME_AS_CLASS

//------------------------------------------------------------------------------
/** \brief \ru Определение простого имени.
           \en Definition of simple name. \~
  \details \ru Определение простого имени. \n
           \en Definition of simple name. \n \~
  \ingroup Base_Tools
*/
// ---
typedef uint32 SimpleName;

//------------------------------------------------------------------------------
/** \brief \ru Сравнить простые имена.
           \en Compare simple names. \~
    \ingroup Base_Tools
*/
// ---
inline int SimpleNameCompare( const SimpleName & h1, const SimpleName & h2 ) { return ( (h1 > h2) ? 1 : ( (h1 < h2) ? -1 : 0 ) ); }


//------------------------------------------------------------------------------
/** \brief \ru Проверить валидность простого имени.
           \en Check the simple name correctness. \~
    \ingroup Base_Tools
*/
// ---
inline
bool IsGoodSimpleName( const SimpleName & s ) {
  return (bool)(s > 0);
}

#else // SIMPLENAME_AS_CLASS 

// \ru При активации этой ветки обязательно собрать проект с активацией максимального уровеня предупреждений \en When this branch is activated, the project must be rebuilt with the highest level of warnings activated 

class  SimpleName {
protected:
  size_t body;

public:
  // \ru конструкторы \en constructors 
  SimpleName()                           : body( SYS_MAX_UINT32 ) {}
  SimpleName( const SimpleName & other ) : body( SYS_MAX_UINT32 ) { body = other.body; }
  SimpleName( size_t other )             : body( SYS_MAX_UINT32 ) { body = other; }

  // \ru операторы копирования \en copy operators 
  SimpleName &  operator = ( const SimpleName & other ) { body = other.body; return *this; }
  SimpleName &  operator = ( size_t other )             { body = other;      return *this; }

// \ru операторы сравнения \en compare operators 
  bool          operator == ( const SimpleName & other ) const { return Сompare( other.body ) == 0; }
  bool          operator != ( const SimpleName & other ) const { return Сompare( other.body ) != 0; }
  bool          operator >  ( const SimpleName & other ) const { return Сompare( other.body ) >  0; }
  bool          operator >= ( const SimpleName & other ) const { return Сompare( other.body ) >= 0; }
  bool          operator <  ( const SimpleName & other ) const { return Сompare( other.body ) <  0; }
  bool          operator <= ( const SimpleName & other ) const { return Сompare( other.body ) <= 0; }

  SimpleName    operator +  ( size_t other )             const { return SimpleName( body + (size_t)other ); }
  SimpleName    operator *  ( size_t other )             const { return SimpleName( body * (size_t)other ); }
  SimpleName &  operator += ( size_t other )                   { body += (size_t)other;      return *this; }
  SimpleName &  operator *= ( size_t other )                   { body *= (size_t)other;      return *this; }
  SimpleName &  operator |= ( size_t other )                   { body |= (size_t)other;      return *this; }
	SimpleName &  operator ++ ()                                 { ++body;                     return *this; } // pre increment
	SimpleName    operator ++ ( int )                            { size_t _tmp = body; ++body; return _tmp;  } // post increment

  // \ru доступ к данным \en access to data 
                operator bool  () const { return body != 0 && body != SYS_MAX_UINT32; }
                operator size_t() const { return (size_t)body; }
  // service
  int           Сompare( const SimpleName & other ) const { return Сompare( other.body ); }  // return value [-1; 0; +1]
protected:
  int           Сompare( size_t other ) const { return ((body > other) ? 1 : ( (body < other) ? -1 : 0 )); }
protected:
  friend  void        WriteSimpleName( writer &, const SimpleName & s );
  friend  SimpleName  ReadSimpleName ( reader & );
};

inline int  SimpleNameCompare( const SimpleName & h1, const SimpleName & h2 ) { return h1.Сompare( h2 ); }
inline bool IsGoodSimpleName( const SimpleName & s ) { return (bool)s; }
inline void SwapIT( SimpleName & a, SimpleName & b ) { SimpleName tmp = a; a = b; b = a; }

#endif // SIMPLENAME_AS_CLASS 


/** \addtogroup Base_Tools
    \{
*/

//------------------------------------------------------------------------------
/** \brief  \ru Максимально допустимое простое имя. 
            \en Maximum allowable simple name. \~
*/ 
//---
const SimpleName SIMPLENAME_MAX = SYS_MAX_UINT32;

//------------------------------------------------------------------------------
/** \brief  \ru Значение используемое, в качестве "неопределенного", еще не назначенного имени. 
            \en A value is used as "undefined", not yet assigned name. \~
*/
//---
const SimpleName UNDEFINED_SNAME = SYS_MAX_UINT32;

//------------------------------------------------------------------------------
/** \brief \ru Начальное число для хэш-функции.
           \en The initial value for the hash-function. \~
*/
// ---
const SimpleName INIT_HASH32_VAL = 31415926;


//------------------------------------------------------------------------------
/** \brief \ru Золотое сечение - произвольное число для хэш-функции.
           \en Golden section - an arbitrary number for hash-function. \~
*/
// ---
#define GOLDENRATIO  0x9e3779b9 

/**
  \}
*/


////////////////////////////////////////////////////////////////////////////////
//
// \ru hash-функция с вероятностью совпадения значений 1/(2^^32) \en hash-function with probability of values coincidence 1/(2^32) 
//
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// \ru Обратимая 32-битная смесь для любых трёх 32-битных чисел a, b, c. \en Invertible 32-bit mixture for any three 32-bit numbers a, b, c. 
// \ru Вероятность изменения значений в любом случае равна как минимум одной четвёртой. \en In any case the probability of values modification is equal to 1/4 at least. 
// ---
static void mix( uint & a, uint & b, uint & c ) 
{ 
  a -= b; a -= c; a ^= (c >> 13); 
  b -= c; b -= a; b ^= (a << 8 ); 
  c -= a; c -= b; c ^= (b >> 13); 
  a -= b; a -= c; a ^= (c >> 12);  
  b -= c; b -= a; b ^= (a << 16); 
  c -= a; c -= b; c ^= (b >> 5 ); 
  a -= b; a -= c; a ^= (c >> 3 );  
  b -= c; b -= a; b ^= (a << 10); 
  c -= a; c -= b; c ^= (b >> 15); 
}


//------------------------------------------------------------------------------
/** \brief \ru Хэш-функция.
           \en Hash-function. \~
  \details \ru Хэш по последовательности байти и предыдущему хэшу. \n
    Каждый бит k влияет на возвращаемое значение. \n
    Функция плохо подходит для использования в криптографии. \n
    k      - Указатель на начало последовательности байт. \n
    length - Количество байт в последовательности. \n
    _c     - Предыдущий hash или произвольное значение. \n
           \en Hash by sequence of bytes and the previous hash. \n
    Each byte k influences on the return value. \n
    The function is bad for use in the cryptography. \n
    k       - A pointer to the beginning of the bytes sequence. \n
    length - Number of bytes in the sequence. \n
    _c     - The previous hash or an arbitrary value. \n \~
  \return \ru Возвращает 32-битное число.
          \en Returns 32-bit number. \~
  \ingroup Base_Tools
*/
// ---
inline SimpleName Hash32( uint8 * k, size_t length, SimpleName _c = INIT_HASH32_VAL )
{
  PRECONDITION( HiUint32( length ) == 0 );

  // \ru Установка внутреннего значения. \en Setting of the internal value. 
  size_t len = length;

#ifndef SIMPLENAME_AS_CLASS
  uint c = _c;
#else // SIMPLENAME_AS_CLASS
  uint c = LoUint32( (size_t)_c );
#endif // SIMPLENAME_AS_CLASS
  uint b = GOLDENRATIO;  // \ru Золотое сечение (произвольное значение) \en Golden ratio (an arbitrary value) 
  uint a = GOLDENRATIO;  // \ru Золотое сечение (произвольное значение) \en Golden ratio (an arbitrary value) 

  // handle most of the key
  while ( len >= 12 )
  {
    a += ((uint)k[0] + ((uint)k[1]<<8) + ((uint)k[2] <<16) + ((uint)k[3] <<24));
    b += ((uint)k[4] + ((uint)k[5]<<8) + ((uint)k[6] <<16) + ((uint)k[7] <<24));   //-V112
    c += ((uint)k[8] + ((uint)k[9]<<8) + ((uint)k[10]<<16) + ((uint)k[11]<<24));
    mix ( a, b, c );
    k   += 12; 
    len -= 12;
  }

  // \ru Значение последних одиннадцати байт. \en The values of the last eleven bytes. 
  c += LoUint32( length ); // \ru Первый байт с резервируется для length \en The first byte c is reserved for 'length' 
  switch ( len ) // \ru Случаи \en Cases  
  {
    case 11: c += ((uint)k[10]<<24);
    case 10: c += ((uint)k[9] <<16);
    case 9 : c += ((uint)k[8] <<8 );
    // \ru Первый байт с резервируется для length \en The first byte c is reserved for 'length' 
    case 8 : b += ((uint)k[7] <<24);
    case 7 : b += ((uint)k[6] <<16);
    case 6 : b += ((uint)k[5] <<8 );
    case 5 : b += ((uint)k[4]);       //-V112
    case 4 : a += ((uint)k[3] <<24);
    case 3 : a += ((uint)k[2] <<16);
    case 2 : a += ((uint)k[1] <<8 );
    case 1 : a += ((uint)k[0]);
    // \ru case 0: Ничего не добавляем. \en case 0: Add nothing.  
  }

  mix( a, b, c );

  _c = (uint)c;
  return _c;
}


#undef GOLDENRATIO


//------------------------------------------------------------------------------
/** \brief \ru Хэш указателя.
           \en Hash of the pointer. \~
  \details \ru Хэш указателя. \n
           \en Hash of the pointer. \n \~
  \ingroup Base_Tools
*/
// ---
template<typename T>
SimpleName Hash32Ptr( T * k ) { return ::Hash32( reinterpret_cast<uint8 *>(&k), sizeof(T*) ); }


//------------------------------------------------------------------------------
/** \brief \ru Хэш строки.
           \en Hash of the string. \~
  \details \ru Хэш строки. \n
           \en Hash of the string. \n \~
  \ingroup Base_Tools
*/
// ---
inline SimpleName HashStr( const c3d::string_t & str ) {
  return ::Hash32( (uint8*)str.c_str(), str.length() * sizeof(TCHAR) );
}


//------------------------------------------------------------------------------
/** \brief \ru Хэш строки.
           \en Hash of the string. \~
  \details \ru Хэш строки. \n
           \en Hash of the string. \n \~
  \ingroup Base_Tools
*/
// ---
inline
SimpleName HashStr( const char * c_str )
{
  PRECONDITION( c_str );
  return ::Hash32( (uint8*)c_str, strlen(c_str) * sizeof(char) );
}


//------------------------------------------------------------------------------
/** \brief \ru Хэш строки.
           \en Hash of the string. \~
  \details \ru Хэш строки. \n
           \en Hash of the string. \n \~
  \ingroup Base_Tools
*/
// ---
inline
SimpleName HashStr( const wchar_t * w_str )
{
  PRECONDITION( w_str );
#ifndef __MOBILE_VERSION__
  return ::Hash32( (uint8*)w_str, wcslen(w_str) * sizeof(wchar_t) );
#else // __MOBILE_VERSION__
  uint16 * hashBuf = Ucs4ToUtf16((uint32*)w_str);
  uint16 * hashBufPointer = hashBuf;
  SimpleName hash = ::Hash32( (uint8*)hashBufPointer, wcslen(w_str) * 2 );
  delete[] hashBuf;
  return hash;
#endif // __MOBILE_VERSION__
}


//------------------------------------------------------------------------------
/** \brief \ru Хэш с типом строки.
           \en Hash with a string type. \~
  \details \ru Хэш с типом строки-источника. \n
    Класс введен для идентификации хэша, взятого с char строки и хеша, взятого с той же wchar_t строки.
           \en Hash with type of source string. \n
    The class is introduced for identification of the hash taken from char of the string and from hash taken with the same wchar_t of the string. \~
  \ingroup Base_Tools
*/
// ---
class  StrHash {
public:
  /// \ru Тип строки-источника имени. \en Type of the source string of name. 
  enum StrHashType {
    htp_undef = 0,   ///< \ru Тип источника неизвестен. \en The source type is unknown. 
    htp_char  = 1,   ///< \ru Тип источника char. \en The source type is char. 
    htp_wchar = 2    ///< \ru Тип источника wchar. \en The source type is wchar. 
  };
private:
  SimpleName m_val;  ///< \ru Простое имя. \en Simple name. 
  uint8      m_type; ///< \ru Тип строки-источника имени. \en Type of the source string of name. 

public:
  /// \ru Конструктор по имени и типу его происхождения. \en Constructor by name and type of its origin. 
  StrHash( SimpleName val, uint8 type ) 
    : m_val ( val  )
    , m_type( type )
  {}
  /// \ru Конструктор по строке. \en Constructor by string. 
  StrHash ( const char    * str )
    : m_val ( ::HashStr(str) )
    , m_type( htp_char      )
  {}
  /// \ru Конструктор по строке. \en Constructor by string. 
  StrHash ( const wchar_t * str )
    : m_val ( ::HashStr(str) )
    , m_type( htp_wchar     )
  {}

  SimpleName  GetVal()  const { return m_val;  } ///< \ru Получить значение. \en Get the value. 
  uint8       GetType() const { return m_type; } ///< \ru Получить тип. \en Get type. 

  int     operator == ( const StrHash & with ) const; ///< \ru Оператор равенства. \en Equality operator. 
  int     operator == ( const char    * with ) const; ///< \ru Оператор равенства. \en Equality operator. 
  int     operator == ( const wchar_t * with ) const; ///< \ru Оператор равенства. \en Equality operator. 

  // \ru Чтение-запись \en Reading-writing 
  friend writer & operator << ( writer &, const StrHash & strHash ); ///< \ru Оператор записи. \en Write operator. 
  friend reader & operator >> ( reader &,       StrHash & strHash ); ///< \ru Оператор чтения. \en Read operator. 
};


//------------------------------------------------------------------------------
/** \brief \ru Хэш пустой строки.
           \en Hash of the empty string. \~
  \details \ru Хэш пустой строки. \n
           \en Hash of the empty string. \n \~
  \ingroup Base_Tools
*/
// ---
#define NullStrHash  StrHash(  0, StrHash::htp_undef )


//------------------------------------------------------------------------------
/** \brief \ru Хэш при отсутствии строки.
           \en Hash for the string absence. \~
  \details \ru Хэш при отсутствии строки. \n
           \en Hash for the string absence. \n \~
  \ingroup Base_Tools
*/
// ---
#define UndefStrHash StrHash( -1, StrHash::htp_undef )


//------------------------------------------------------------------------------
/** \brief \ru Хэш двух простых имен.
           \en Hash of two simple names. \~
  \details \ru Хэш двух простых имен. \n
    Часто встречающаяся комбинация - hash от двух SimpleName (uint32).
           \en Hash of two simple names. \n
    Frequently occurring combination - hash of two SimpleName (uint32). \~
  \ingroup Base_Tools
*/
// ---
inline SimpleName Hash32SN( SimpleName k1, SimpleName k2 )
{
  //SimpleName array[] = { k1, k2 };
  uint arr[2];
#ifndef SIMPLENAME_AS_CLASS
  arr[0] = k1;
  arr[1] = k2;
#else // SIMPLENAME_AS_CLASS
  arr[0] = LoUint32( (size_t)k1 );
  arr[1] = LoUint32( (size_t)k2 );
#endif // SIMPLENAME_AS_CLASS
  return ::Hash32( (uint8*)arr, 2 * sizeof(uint) ); // \ru длина - 4 * 2 = 8 \en length - 4 * 2 = 8 
}


//------------------------------------------------------------------------------
// \ru Проверка на равенство \en The check for equality 
//---
inline int StrHash::operator == ( const StrHash & with ) const
{ 
  PRECONDITION(m_type == with.m_type); // \ru должны быть одного типа, иначе сравнение не имеет смысла \en must be of the same type, otherwise the comparison is senseless 
  return ::SimpleNameCompare( m_val, with.m_val );
}


//------------------------------------------------------------------------------
// \ru Проверка на равенство char строкой \en Check for equality of char by string 
//---
inline int StrHash::operator == ( const char * with ) const
{
  PRECONDITION( false ); // \ru по идее использоваться не должна \en should not be used 
  PRECONDITION( m_type != htp_undef );

  // \ru Если у нас хеш с wchar_t \en If we have hash with wchar_t, 
  if ( m_type == htp_wchar ) // \ru то что прислали нужно перевести в wchar_t \en then the input data should be converted to wchar_t 
    return *this == StrHash( wcsbuf(with) );
  else
    return *this == StrHash( with );
}


//------------------------------------------------------------------------------
// \ru Проверка на равенство с wchar_t строкой \en Check for equality with wchar_t by string 
//---
inline int StrHash::operator == ( const wchar_t * with ) const
{
  PRECONDITION( m_type != htp_undef );

  // \ru Если у нас хеш с char \en If we have hash with char, 
  if ( m_type == htp_char ) // \ru то что прислали нужно перевести в char \en then the input data should be converted to char 
    return *this == StrHash( strbuf(with) );
  else
    return *this == StrHash( with );
}


#endif // __HASH32_H

