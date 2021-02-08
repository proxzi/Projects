////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Контроль выделения памяти под отладкой.
         \en Memory allocation control during the debugging process. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MEMORY_DEBUG_H
#define __MEMORY_DEBUG_H

//#define __DEBUG_MEMORY_ALLOCATE_FREE_
//#define __MEMSET_USED_FREE_HEAP_HEAR__
//#define __REALLOC_ARRAYS_STATISTIC_

#include <math_x.h>
#include <system_types.h>
#include <memory.h>

#ifdef C3D_DEBUG
  #if defined(C3D_MacOS) // mac
  #include <malloc/malloc.h>
  #elif defined(C3D_FreeBSD)
  #include <stdlib.h>
  #else
  #include <malloc.h>
  #endif // mac

  #ifndef __DISABLE_MEMORY_CONTROL__  // \ru Чтобы можно было отключать в других проектах \en To allow to disable it in other projects 
    #ifndef __BORLANDC__
      #define USE_REALLOC_IN_ARRAYS // no _aligned_realloc in bcc32c
    #endif
  #endif // __DISABLE_MEMORY_CONTROL__
#endif // C3D_DEBUG

#ifdef __REALLOC_ARRAYS_STATISTIC_
//#include <stdio.h>
#include <string>
#include <fstream>
#endif


#ifdef __DEBUG_MEMORY_ALLOCATE_FREE_

//------------------------------------------------------------------------------
/// \ru Проверить указатель и значение. \en Check pointer and value.  \~ \ingroup Base_Tools
// ---
inline void CheckPointerAndValue( void * ptr, size_t size )
{
#if defined (C3D_WINDOWS) && !defined(ALL_WARNINGS)  //_MSC_VER // Set warnings level
#pragma warning(disable: 4312)
#endif
  C3D_ASSERT( ptr != (ptrdiff_t *)0xEEEEEEEE );
  C3D_ASSERT( ptr != (ptrdiff_t *)0xFFFFFFFF );
#if defined (C3D_WINDOWS) && !defined(ALL_WARNINGS)  //_MSC_VER // Set warnings level
#pragma warning(default: 4312)
#endif

  if ( ptr ) {
    // \ru Надо доработать для 64-бит \en It should be adapted for the 64-bit version 
    if ( size > 11 ) {
      uint32* _ptr = (uint32 *)ptr;
      uint32 value1 = *_ptr++;
      uint32 value2 = *_ptr++;
      uint32 value3 = *_ptr;
      C3D_ASSERT( value1 != 0xEEEEEEEE || value2 != 0xEEEEEEEE || value3 != 0xEEEEEEEE );
      C3D_ASSERT( value1 != 0xFFFFFFFF || value2 != 0xFFFFFFFF || value3 != 0xFFFFFFFF );
    }
    else if ( size > 7 ) {
      uint32 * _ptr = (uint32 *)ptr;
      uint32 value1 = *_ptr++;
      uint32 value2 = *_ptr;
      C3D_ASSERT( value1 != 0xEEEEEEEE && value2 != 0xEEEEEEEE );
      C3D_ASSERT( value1 != 0xFFFFFFFF || value2 != 0xFFFFFFFF );
    }
    else if ( size > 3 ) {
      uint32 value = *(uint32 *)ptr;
      C3D_ASSERT( value != 0xEEEEEEEE );
      C3D_ASSERT( value != 0xFFFFFFFF );
    }
    else if ( size > 1 ) {
      uint16 value = *(uint16 *)ptr;
      C3D_ASSERT( value != 0xEEEE );
      C3D_ASSERT( value != 0xFFFF );
    }
  }
}

//------------------------------------------------------------------------------
/// \ru Выделить память указанного размера. \en Allocate memory of the given size.  \~ \ingroup Base_Tools
// ---
inline void * Allocate( size_t size, const char * ) // className )
{
  void * ptr = ::malloc( size );
  // \ru Дабы работал _msize: void * ptr = ::operator new( size ); \en For working of _msize: void * ptr = ::operator new( size ); 

  if ( ptr ) {
    ::memset( ptr, 0xFF, size );
  }
  return ptr;
}

//------------------------------------------------------------------------------
/// \ru Выделить память указанного размера под массив. \en Allocate memory of the given size for an array.  \~ \ingroup Base_Tools
// ---
inline void * AllocateArray( size_t size, const char * ) // className )
{
  void * ptr = ::malloc( size );
  // \ru Дабы работал _msize: void *ptr = ::operator new [] ( size ); \en For working of _msize: void *ptr = ::operator new [] ( size ); 

  if ( ptr ) {
#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
    ::memset( ptr, 0xFFFFFFFF, size );  // \ru OV - надо доработать для 64-бит \en OV - it should be adapted for the 64-bit version 
#endif // __MEMSET_USED_FREE_HEAP_HEAR__
  }
  return ptr;
}

//------------------------------------------------------------------------------
/// \ru Освободить память указанного размера. \en Free memory of the given size.  \~ \ingroup Base_Tools
// ---
inline void Free( void * ptr, size_t size, const char * ) // className )
{
  if ( ptr ) {
    ::CheckPointerAndValue( ptr, size );

#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
    size_t ptr_size = ::_msize( ptr );
    C3D_ASSERT( ptr_size > 0 && ptr_size < 0xFFFFFFFF ); // \ru Надо доработать для 64-бит. \en It should be adapted for the 64-bit version.
    if ( ptr_size ) {
      C3D_ASSERT( size <= ptr_size );
      ::memset( ptr, 0xEE, ptr_size );
    }
#endif // __MEMSET_USED_FREE_HEAP_HEAR__

    ::free( ptr );
  }
}

//------------------------------------------------------------------------------
/// \ru Освободить память, выделенную под массив. \en Free the memory allocated for the array.  \~ \ingroup Base_Tools
// ---
// \ru ЯТ можно перегрузить в классах operator delete [] ( void *, size_t ) и передать \en ЯТ it is pertinent to overload the operator delete [] ( void *, size_t ) and pass 
// \ru в эту функцию size_t size, но это будет не размер массива, а размер Type, \en to this function size_t size, but this will be not the size of an array but the size of 'Type', 
// \ru массив которых распределялся. То есть эта информация здесь не нужна (делать \en an array of which was not distribute. I.e. this information is not needed here ( 
// \ru ::memset не нее НЕЛЬЗЯ!) \en it is forbidden to do ::memset here) 
// ---
inline void FreeArray( void * ptr, const char * ) // className )
{
  if ( ptr ) {
    ::CheckPointerAndValue( ptr, 0/*size*/ );

#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
    size_t size = ::_msize( ptr );
    C3D_ASSERT( size > 0 && size < 0xFFFFFFFF );  // \ru OV - надо доработать для 64-бит \en OV - it should be adapted for the 64-bit version 
    ::CheckPointerAndValue( ptr, size );
    if ( size )
      ::memset( ptr, 0xEE, size );
#endif // __MEMSET_USED_FREE_HEAP_HEAR__

    ::free( ptr );
  }
}

#endif // __DEBUG_MEMORY_ALLOCATE_FREE_


#ifdef __REALLOC_ARRAYS_STATISTIC_

struct OneArrayTypeStatistic {
public:
  size_t reallocCountSuccess; // \ru кол-во успешных перераспределений памяти \en A number of successfully reallocations of the memory 
  size_t firstAlloc         ; // \ru кол-во первичных распределений \en the number of primary allocations 
  size_t lastAlloc          ; // \ru кол-во освобождений \en the number of releases 
  size_t realAllocIncremet  ; // \ru кол-во запросов на увеличение \en the number of requests for an increment 
  size_t realAllocDecremet  ; // \ru кол-во запросов на уменьшение \en the number of requests for a decrement 
  size_t fullLength         ; // \ru суммарный размер в байтах \en the total size in bites 
  size_t maxOneArrayLength  ; // \ru максимальный размер одного массива \en the minimal size of one array 
  size_t sumCurrLength      ; // \ru суммарный размер памяти во всех массивах этого типа в данный момент \en the total size of the memory in all arrays of this type at this moment 
  size_t maxOneTimeLength   ; // \ru максимальный одновременный размер памяти во всех массивах этого типа \en the maximum simultaneous size of the memory in all arrays of this type 
  size_t minDelta           ; // \ru минимальное приращение \en minimum increment 
  size_t maxDelta           ; // \ru максимальное приращение \en maximum increment 
public:
  OneArrayTypeStatistic() { Clear(); }
  void Clear() {
    reallocCountSuccess = 0;
    firstAlloc          = 0;
    lastAlloc           = 0;
    realAllocIncremet   = 0;
    realAllocDecremet   = 0;
    fullLength          = 0;
    maxOneArrayLength   = 0;
    sumCurrLength       = 0;
    maxOneTimeLength    = 0;
    minDelta            = SYS_MAX_T; // \ru минимальное приращение \en minimum increment 
    maxDelta            = 0;         // \ru максимальное приращение \en maximum increment 
  }
};

const size_t STAT_ARRAY_COUNT = 6;
static OneArrayTypeStatistic statisticArray[STAT_ARRAY_COUNT]
  = { OneArrayTypeStatistic(), OneArrayTypeStatistic(), OneArrayTypeStatistic(),
      OneArrayTypeStatistic(), OneArrayTypeStatistic(), OneArrayTypeStatistic() };

static size_t allReallocCount = 0;

//------------------------------------------------------------------------------
// \ru Уменьшение uint с проверкой \en A decrement of uint with the check 
// ---
inline void DecrementUint( size_t & val, size_t delta ) {
  val = (delta < val) ? (val - delta) : 0;
}

//------------------------------------------------------------------------------
/// \ru Статистика изменений размера массива. \en Statistics of array size changes.  \~ \ingroup Base_Tools
// arrayType : 
// \ru 0 - SArray (или наследники), \en 0 -SAray (or inheritors) 
// \ru 1 - RParray (или наследники), \en 1 -RPAray (or inheritors) 
// 2 - Array2,
// 3 - LiSArray,
// 4 - CcArray,
// \ru 5 - неопознанные (вообще-то, такого не должно быть) \en 5 - not defined (it should not happen) 
// ---
inline void ReallocArrayStatistic( void * oldParr, size_t oldSize, 
                                   void * newParr, size_t newSize, 
                                   uint arrayType ) 
{
  if ( oldParr || newSize ) {
    allReallocCount++;

    // \ru найдем статистическую запись про данный тип массива \en find a statistic record about the given type of array 
    size_t index = (size_t)arrayType;
    if ( index >= STAT_ARRAY_COUNT )
      index = STAT_ARRAY_COUNT - 1;
    OneArrayTypeStatistic & stat = statisticArray[index];

    if ( newSize > stat.maxOneArrayLength )
      stat.maxOneArrayLength = newSize;

    if ( !oldParr ) {                // \ru первичное распределение \en primary allocation 
      stat.firstAlloc++;
      stat.fullLength    += newSize; // \ru общее кол-во байт в этом типе массива \en the total number of bites in this type of an array 
      stat.sumCurrLength += newSize; // \ru суммарный размер памяти во всех массивах этого типа в данный момент \en the total size of the memory in all arrays of this type at this moment 
    }

    if ( oldParr && !newSize ) {     // \ru полное освобождение \en full release 
      stat.lastAlloc++;
      // \ru максимальный одновременный размер памяти во всех массивах этого типа \en the maximum simultaneous size of the memory in all arrays of this type 
      if ( stat.sumCurrLength > stat.maxOneTimeLength )
        stat.maxOneTimeLength = stat.sumCurrLength;
      // \ru суммарный размер памяти во всех массивах этого типа в данный момент \en the total size of the memory in all arrays of this type at this moment 
      ::DecrementUint( stat.sumCurrLength, oldSize );
    }

    if ( oldParr && newSize > oldSize ) { // \ru запрос на увеличение \en a request to increase 
      stat.realAllocIncremet++;
      size_t delta = newSize - oldSize;
      stat.fullLength    += delta; // \ru общее кол-во байт в этом типе массива \en the total number of bites in this type of an array 
      stat.sumCurrLength += delta; // \ru суммарный размер памяти во всех массивах этого типа в данный момент \en the total size of the memory in all arrays of this type at this moment 

      if ( delta < stat.minDelta )
        stat.minDelta = delta; // \ru минимальное приращение \en minimum increment 
      if ( delta > stat.minDelta )
        stat.maxDelta = delta; // \ru максимальное приращение \en maximum increment 
    }

    if ( oldParr && newSize && newSize < oldSize ) { // \ru запрос на уменьшение \en a request to decrease 
      stat.realAllocDecremet++;
      // \ru максимальный одновременный размер памяти во всех массивах этого типа \en the maximum simultaneous size of the memory in all arrays of this type 
      if ( stat.sumCurrLength > stat.maxOneTimeLength )
        stat.maxOneTimeLength = stat.sumCurrLength;
      // \ru суммарный размер памяти во всех массивах этого типа в данный момент \en the total size of the memory in all arrays of this type at this moment 
      ::DecrementUint( stat.sumCurrLength, oldSize - newSize );
    }

#ifdef USE_REALLOC_IN_ARRAYS
    if ( oldParr && oldParr == newParr && newSize != oldSize )
      stat.reallocCountSuccess++;
#endif // USE_REALLOC_IN_ARRAYS
  }
}


//------------------------------------------------------------------------------
/// \ru Отчет по статистике изменений размера массива. \en A report by the statistics of array size changes.  \~ \ingroup Base_Tools
// ---
inline void ReallocReport( bool clear, const char * title = NULL )
{
  std::string text( title );

  if ( text.length() > 0 )
    text.append( "\n" );

  char buf[256];
  ::sprintf( buf, "Общее кол-во realloc %d", ::LoUint32( allReallocCount ) );
  text.append( buf );

  for ( size_t i = 0; i < STAT_ARRAY_COUNT; i++ ) {
    OneArrayTypeStatistic & stat = statisticArray[i];

    // \ru если данных нет, то и писать про них не будем \en if there is no data then we will not write about it 
    if ( stat.firstAlloc || stat.lastAlloc || stat.realAllocIncremet || stat.realAllocDecremet ) {

      switch ( i ) {
        case 0 : text.append( "\n\n SArray  (или наследники)" );  break;
        case 1 : text.append( "\n\n RParray (или наследники)" );  break;
        case 2 : text.append( "\n\n Array2" );                    break;
        case 3 : text.append( "\n\n LiSArray (или наследники)" ); break;
        case 4 : text.append( "\n\n CcArray" );                   break;
        case 5 : text.append( "\n\n неопознанные" );              break;
      }

      ::sprintf( buf, "\n всего байт \t %d", ::LoUint32( stat.fullLength ) );
      text.append( buf );
      ::sprintf( buf, "\n макс.размер \t %d", ::LoUint32( stat.maxOneArrayLength ) );
      text.append( buf );
      ::sprintf( buf, "\n первичных \t %d", ::LoUint32( stat.firstAlloc ) );
      text.append( buf );
      ::sprintf( buf, "\n освобождений \t %d", ::LoUint32( stat.lastAlloc ) );
      text.append( buf );
      if ( stat.realAllocIncremet ) {
        ::sprintf( buf, "\n на увеличение \t %d", ::LoUint32( stat.realAllocIncremet ) );
        text.append( buf );
      }
      if ( stat.realAllocDecremet ) {
        ::sprintf( buf, "\n на уменьшение \t %d", ::LoUint32( stat.realAllocDecremet ) );
        text.append( buf );
      }
#ifdef USE_REALLOC_IN_ARRAYS
      if ( stat.reallocCountSuccess ) {
        ::sprintf( buf, "\n удачных realloc \t %d", ::LoUint32( stat.reallocCountSuccess ) );
        text.append( buf );
      }
#endif
      ::sprintf( buf, "\n max одновременно %d", ::LoUint32( stat.maxOneTimeLength ) );
      text.append( buf );
      if ( stat.realAllocIncremet ) {
        ::sprintf( buf, "\n Delta (min, max) \t %d, %d", ::LoUint32( stat.minDelta ), ::LoUint32( stat.maxDelta ) );
        text.append( buf );
      }
    }
  }

  {
    const char * outName = "C:\\Logs\\ADRAFT_TTEST.txt";
    std::ofstream out( outName, std::ios::out|std::ios::app );
    out << "\n Статистика использования памяти \n";
    //out << text;
    out << "\n";
  }

  if ( clear ) {
    // \ru очистить, чтобы в следующий раз цифры были новые, а не накопленные \en clear to renew numbers 
    allReallocCount = 0;
    for ( size_t i = 0; i < STAT_ARRAY_COUNT; i++ )
      statisticArray[i].Clear();
  }
}

#endif // __REALLOC_ARRAYS_STATISTIC_


//------------------------------------------------------------------------------
// \ru Использовать realloc для изменения размера массивов \en Use realloc to change arrays sizes 
// \ru (если не определено, то по-старому, через new и delete) \en (if it is not defined then use new and delete operators) 
//---
#ifdef USE_REALLOC_IN_ARRAYS

#ifdef C3D_DEBUG

#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
//------------------------------------------------------------------------------
/// \ru Функция перезахватов памяти в массивах. \en Function of memory reallocation in arrays.  \~ \ingroup Base_Tools
// ---
inline void * ReallocArraySize( void * arr_parr, size_t newBytesCount, bool clear )
#else // __MEMSET_USED_FREE_HEAP_HEAR__
//------------------------------------------------------------------------------
/// \ru Функция перезахватов памяти в массивах. \en Function of memory reallocation in arrays.  \~ \ingroup Base_Tools
// ---
inline void * ReallocArraySize( void * arr_parr, size_t newBytesCount, bool )
#endif // __MEMSET_USED_FREE_HEAP_HEAR__
{
#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
  if ( newBytesCount == 0 || clear ) {
    size_t arr_parr_size = ::_msize( arr_parr );
    C3D_ASSERT( arr_parr ? (arr_parr_size > 0 && arr_parr_size < 0xFFFFFFFF) : true ); // \ru OV - надо доработать для 64-бит \en OV - it should be adapted for the 64-bit version 
    if ( arr_parr_size )
      ::memset( arr_parr, 0xEE, arr_parr_size );
  }
#endif // __MEMSET_USED_FREE_HEAP_HEAR__

#if defined( _AFXDLL ) && defined( C3D_DEBUG )
  void * tmp_parr = _realloc_dbg( arr_parr, newBytesCount, _NORMAL_BLOCK, __FILE__, __LINE__ );
#else
  void * tmp_parr = ::realloc( arr_parr, newBytesCount );
#endif

  PRECONDITION( newBytesCount == 0 || tmp_parr != NULL ); // \ru проверка на нехватку памяти в массивах \en check the memory deficit in arrays  

#ifdef __MEMSET_USED_FREE_HEAP_HEAR__
  if ( clear ) {
    size_t tmp_parr_size = ::_msize( tmp_parr );
    C3D_ASSERT( tmp_parr ? (tmp_parr_size > 0 && tmp_parr_size < 0xFFFFFFFF) : true ); // \ru OV - надо доработать для 64-бит \en OV - it should be adapted for the 64-bit version 
    if ( tmp_parr_size )
      ::memset( tmp_parr, 0xEE, tmp_parr_size );
  }
#endif // __MEMSET_USED_FREE_HEAP_HEAR__

  return tmp_parr;
}

#define REALLOC_ARRAY_SIZE(p,s,c) ::ReallocArraySize((p),(s),(c))
#else // C3D_DEBUG
#define REALLOC_ARRAY_SIZE(p,s,c) ::realloc((p),(s))
#endif // C3D_DEBUG

#endif // USE_REALLOC_IN_ARRAYS


#endif  // __MEMORY_DEBUG_H
