////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Управление параллельной обработкой данных.
       \en Managing of parallel data processing. \~
\details \ru Управление параллельной обработкой данных.\n
        \en Managing of parallel data processing. \n \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __TOOL_MULTITHREADING_H
#define __TOOL_MULTITHREADING_H

#include <system_dependency.h>
#include <tool_mutex.h>

//------------------------------------------------------------------------------
/**
\brief \ru Режимы многопоточных вычислений.
       \en Multithreading modes. \~
\details \ru Режимы многопоточных вычислений. \n
         \en Multithreading modes. \n \~
\ingroup Data_Structures
*/
//---
enum MbeMultithreadedMode {
  // \ru Многопоточность ядра отключена. \en Kernel multithreading is off. 
  mtm_Off         = 0,
  // \ru Включена многопоточность ядра при обработке независимых объектов (без общих данных).
  // \en Kernel multithreading is ON for independent objects (without common data).
  mtm_Standard    = 1,
  // \ru Обеспечивается потокобезопасность объектов типа MbItem. Выключена многопоточность ядра при обработке объектов, имеющих общие данные.
  // \en Ensured thread-safety of objects MbItem. Kernel multithreading is OFF for objects with shared data.
  mtm_SafeItems   = 2,
  // \ru Обеспечивается потокобезопасность объектов типа MbItem. Включена многопоточность ядра при обработке объектов с общими данными.
  // \en Ensured thread-safety of objects MbItem. Kernel multithreading is ON for objects with shared data.
  mtm_Items       = 3,
  // \ru Включена максимальная многопоточность ядра. \en Maximal kernel multithreading is ON.
  mtm_Max         = 31
};

//------------------------------------------------------------------------------
/**
  \brief \ru Базовый класс для объектов, требующих сборки мусора.
         \en Base class for objects which require a garbage collection. \~
\details \ru Базовый класс для объектов, требующих сборки мусора.
         Класс, наследующий от CacheCleaner, должен реализовать метод ResetCacheData,
         который будет вызываться для сборки мусора.
         \en Base class for objects which require a garbage collection.
         A class, inheriting from CacheCleaner, should implement the method ResetCacheData,
         which will be called for garbage collection. \~
\ingroup Base_Tools
*/
//---
class MATH_CLASS CacheCleaner
{
  int  subscribed;
public:
  CacheCleaner();
  virtual ~CacheCleaner();

  /** \brief \ru Подписан ли объект на сборку мусора.
             \en Whether the object is subscribed for garbage collection. \~
  */
  bool IsSubscribed() { return subscribed > 0;  }

  /** \brief \ru Очистить кэшированные данные. Возвращает true, если объект был отписан от сборки мусора.
             \en Reset cached data. Return true if the object was unsubscribed from garbage collection.\~
  */
  virtual bool ResetCacheData() = 0;

  /** \brief \ru Подписаться на сборку мусора.
             \en Subscribe for garbage collection. \~
  */
  void SubcribeOnCleaning();

  /** \brief \ru Отписаться от сборки мусора.
             \en Unsubscribe from garbage collection. \~
  */
  void UnsubcribeOnCleaning();
};

//------------------------------------------------------------------------------
/**
  \brief \ru Сборщик мусора в объектах, использующих кэширование данных.
         \en Garbage collector in objects which use data caching. \~
\details \ru Сборщик мусора. По требованию очищает кэши в зарегистрированных объектах CacheCleaner,
         вызывая метод ResetCacheData каждого объекта. \n
         \en Garbage collector. At request clears caches in registered CacheCleaner objects
         by calling the method ResetCacheData of each object. \n \~
\ingroup Base_Tools
*/
//---
class MATH_CLASS MbGarbageCollection
{
public:

  /** \brief \ru Подписать объект на сборку мусора.
             \en Subscribe the object for garbage collection. \~
  */
  static void Subscribe( CacheCleaner * obj );

  /** \brief \ru Отписать объект от сборки мусора.
             \en Unsubscribe the object from garbage collection. \~
  */
  static void Unsubscribe( CacheCleaner * obj );

  /** \brief   \ru Выполнить сборку мусора. \en Perform garbage collection.
      \details \ru Выполнить сборку мусора. Должна вызываться в последовательном участке кода.
               При вызове в параллельном регионе ничего не делает.
               \en Perform garbage collection. Should be called in sequential code.
               When called in a parallel region, does nothing.
      \param[in] force - \ru Если false, то инициируется сборка мусора в кэшах, созданных для потоков, которые уже завершены,
                         если true, то инициируется принудительная сборка мусора во всех кэшах.
                         \en If false, then run garbage collection in caches created for threads which are finished,
                         if true, then force garbage collection in all caches.
      \return \ru Возвращает TRUE, если сборка проведена. \en Returns TRUE if the garbage collection is done. \~
  */
  static bool Run( bool force = false );

  /** \brief \ru Активировать/деактивировать сбор данных для проведения сборки мусора.
             По умолчанию, сбор данных для сборки мусора активирован.
             \en Enable/disable collecting data for garbage collection.
             By default, collecting data for garbage collection is enabled. \~
  */
  static void Enable( bool allow = true );
};

//------------------------------------------------------------------------------
// \ru Принудительно вернуть освобожденную динамическую память операционной системе.
//     Может быть полезна после выполнения операций с интенсивным использованием памяти.
// \en Force to return freed heap memory to the operating system.
//     May be useful after performing memory-intensive operations.
// ---
MATH_FUNC( void ) ReleaseMemory();

//------------------------------------------------------------------------------
/**
\brief \ru Родительский класс данных для менеджера параллельной обработки.
       \en Parent class of data for manager of parallel processing. \~
\details \ru Родительский класс для данных, которые могут обрабатываться параллельно
         с помощью менеджера кэшей.
         \en Parent class for data which could be processed in parallel using the cache manager. \~
  \ingroup Base_Tools
*/
// ---
class AuxiliaryData {
public:
  AuxiliaryData() {}
  AuxiliaryData( const AuxiliaryData & ) {}
  virtual ~AuxiliaryData() {}
};

//#define CACHE_DELETE_LOCK
//------------------------------------------------------------------------------
/**
\brief \ru Менеджер параллельной обработки данных (менеджер кэшей).
       \en Manager for parallel data processing (the cache manager). \~
\details \ru Менеджер кэшей представляет шаблон, содержащий:
       longTerm - данные главного потока при последовательном выполнении и
       список кэшей tcache - данные, которые используются при параллельном выполнении.
       Каждый поток по идентификатору threadKey использует только свою копию данных.
       Для многопоточной обработки зависимых (имеющих общие данные) объектов должен
       использоваться режим многопоточных вычислений не ниже mtm_SafeItems. \n
       \en The cache manager is a template which contains:
       longTerm - data of the main thread in sequential execution, and
       a list of caches 'tcache' which are used in parallel execution. 
       Each thread uses its own copy of data according to threadKey.
       For multithreaded processing of dependent (with shared data) objects,
       the mtm_SafeItems or higher multithreading mode should be used. \n \~
*/
// ---
template<class T>
class CacheManager : public CacheCleaner {
  struct List
  {
    unsigned int _id;
    T*           _data;
    List*        _next;
    bool         _valid;
    List( unsigned int id, T* data ) :
      _id( id ),
      _data( data != NULL ? data : new T() ), // Always _data != NULL.
      _next( NULL ),
      _valid( true ) {}
    ~List() {
      if ( _data != NULL )
        delete _data;
      _data = NULL;
      if ( _next != NULL ) // Also deletes linked List.
        delete _next;
      _next = NULL;
    }
  private:
    List() : _id( 0 ), _data( NULL ), _next( NULL ) {}
  };

private:
  T*            longTerm; // \ru Данные главного потока при последовательном выполнении. \en Data of the main thread in sequential execution.
  List*         tcache;   // \ru Данные, которые используются при параллельном выполнении. \en Caches which are used in parallel execution.
  CommonMutex*  lock;     // \ru Блокировка для операций с кэшами. \en Lock for operations with caches.

public:
#ifdef CACHE_DELETE_LOCK
  CacheManager( bool createLock = false );
#else
  CacheManager( bool createLock = true );
#endif
  CacheManager( const CacheManager & );
  ~CacheManager();

  /** \brief \ru Оператор (). Возвращает указатель на кэш (данные) текущего потока. Всегда возвращает ненулевое значение.
             \en Operator (). Returns a pointer to the cache (data) of the current thread. Always returns non-null value. \~
  */
  T *   operator ()();

  /** \brief \ru Удалить данные в кэшах. Если resetLongTerm == true, удалить также данные кэша главного потока.
             \en Delete caches data. If resetLongTerm == true, also delete data of the main thread cache.
  */
  void  Reset    ( bool resetLongTerm = false );

  /** \brief \ru Получить указатель на кэш (данные) главного потока. Всегда возвращает ненулевое значение.
                 Все операции с кэшем главного потока должны быть защищены блокировкой кэша.
             \en Get a pointer to cache (data) of the main thread. Always returns non-null value.
                 All operations with the main thread cache should be protected by the cache lock. \~
  */
  T *   LongTerm ();

  /** \brief \ru Получить указатель на блокировку для операций с кэшем главного потока, учитывая, исполняется ли код параллельно
             Может возвращать нулевое значение (удобно для использования с ScopedLock).
             \en Get a pointer to the lock for operations with the main thread cache, considering whether the code runs in parallel.
             Can return null value (good for use with ScopedLock). \~
  */
  CommonMutex* GetLock() { if ( IsInParallel() ) return GetLockHard();  return lock; }

  /** \brief \ru Функция очистки, используемая сборщиком мусора.
             \en Cleaning function, used by the garbage collector. \~
  */
  virtual bool ResetCacheData() { CleanAll(); return true; }

private:
  /** \brief \ru Удалить все кэши и отписаться от сборки мусора. Должна вызываться в последовательном участке кода.
             \en Delete all caches and unsubscribe from the garbage collection. Should be called in sequential code. \~
  */
  void CleanAll();
  
  /** \brief \ru Получить указатель на блокировку для операций с кэшем главного потока. Всегда возвращает ненулевое значение.
             \en Get a pointer to the lock for operations with the main thread cache. Always returns non-null value. \~
  */
  CommonMutex* GetLockHard();

  CacheManager & operator = ( const CacheManager & ); // \ru Не разрешен. \en Not allowed.
};


//------------------------------------------------------------------------------
// \ru Конструктор. \en Constructor. 
// ---
template<class T>
inline CacheManager<T>::CacheManager( bool createLock )
  : longTerm  ( NULL )
  , tcache    ( NULL ) 
  , lock      ( NULL )
{
  if ( createLock )
    lock = new CommonMutex();
}


#define C3D_NULLKEY 0

//------------------------------------------------------------------------------
// \ru Конструктор. \en Constructor. 
// ---
template<class T>
inline CacheManager<T>::CacheManager( const CacheManager<T> & item )
  : longTerm  ( NULL )
  , tcache    ( NULL )
  , lock      ( NULL )
{
  if ( item.longTerm != NULL )
    longTerm = new T( *item.longTerm );
#ifndef CACHE_DELETE_LOCK
  lock = new CommonMutex();
#endif
}


//------------------------------------------------------------------------------
// \ru Деструктор. \en Destructor. 
// ---
template<class T>
inline CacheManager<T>::~CacheManager()
{ 
  CleanAll();
  if ( longTerm != NULL )
    delete longTerm;
  if ( lock != NULL )
    delete lock;
}

//------------------------------------------------------------------------------
// \ru Получить указатель на кэш главного потока. Всегда возвращает ненулевое значение.
//     Все операции с кэшем главного потока должны быть защищены блокировкой кэша.
// \en Get a pointer to the main thread cache. Always returns non-null value.
//     All operations with the main thread cache should be protected by the cache lock.
// ---
template<class T>
inline T* CacheManager<T>::LongTerm ()
{
  if ( longTerm == NULL )
    longTerm = new T();
  return longTerm;
}

//------------------------------------------------------------------------------
// \ru Получить указатель на блокировку для операций с кэшем главного потока. Всегда возвращает ненулевое значение.
// \en Get a pointer to the lock for operations with the main thread cache. Always returns non-null value.
// ---
template<class T>
inline CommonMutex* CacheManager<T>::GetLockHard()
{
  if ( lock == NULL ) {
    CommonMutex* ll = GetGlobalLock();
    ll->lock();
    if ( lock == NULL )
      lock = new CommonMutex();
    ll->unlock();
  }
  return lock;
}

//------------------------------------------------------------------------------
// \ru Оператор (). Возвращает указатель на кэш текущего потока (всегда ненулевое значение).
// \en Operator (). Returns a pointer to the current thread cache (always non-null value).
// ---
template<class T>
inline T * CacheManager<T>::operator()()
{
// \ru Создать данные по данным кэша главного потока. \en Create data using the data of the main thread cache.
#define INIT_BY_LONGTERM  ( longTerm != NULL ? new T( *longTerm ) : new T() )

  if ( !IsSafeMultithreading() || !IsInParallel() ) {
    if ( tcache != NULL ) {
      if ( IsSubscribed() )  // \ru Отписаться от сборки мусора. \en Unsubscribe from garbage collection.
        UnsubcribeOnCleaning();
      // \ru Удалить все кэши, кроме кэша главного потока. \en Delete all caches excepting the main thread cache.
      delete tcache;
      tcache = NULL;
    }
   
#ifdef CACHE_DELETE_LOCK
    if ( lock != NULL ) { // \ru Удалить блокировку. \en Delete the lock.
      delete lock;
      lock = NULL;
    }
#endif
    return LongTerm();
  }

  T * res = NULL;
  unsigned int threadKey = GetThreadKey();

  if ( tcache == NULL ) {
    // \ru Подписаться на сборку мусора, так как используются многопоточные кэши.
    // \en Subscribe on garbage collection because using multithreaded caches.
    SubcribeOnCleaning();
    {
      // \ru Используется блокировка при изменении списка кэшей. \en Use lock when changing the cache list.
      ScopedLock sl( GetLock(), false );
      if ( tcache == NULL ) {
        tcache = new List( threadKey, INIT_BY_LONGTERM );
        return tcache->_data;
      }
    }
  }

  List* entry = tcache;
  while( entry != NULL ) {
    if ( entry->_id == threadKey ) {
      if ( !entry->_valid ) {
        delete entry->_data;
        entry->_data = INIT_BY_LONGTERM;
        entry->_valid = true;
      }
      return entry->_data;
    }
    // \ru Если кэш не найден в списке, 'entry' содержит последний (на данный момент) элемент в списке.
    // \en If cache not found in the list, 'entry' contains the last element in the list (at that point).
    if ( entry->_next == NULL )
      break; 
    entry = entry->_next;
  }
  res = INIT_BY_LONGTERM;
  List* newList = new List( threadKey, res );
  {
    // \ru Используется блокировка при изменении списка кэшей. \en Use lock when changing the cache list.
    ScopedLock sl( GetLock(), false );
    // \ru На данный момент, entry может быть не последним элементом в списке.
    // \en At that point, entry could be not a last element in the list.
    while ( entry->_next != NULL ) {
      entry = entry->_next;
    }
    entry->_next = newList;
  } // ScopedLock

  return res;

}


//------------------------------------------------------------------------------
// \ru Удалить данные в кэшах. Если resetLongTerm == true, удалить также данные кэша главного потока.
// \en Delete caches data. If resetLongTerm == true, also delete data of the main thread cache.
// ---
template<class T>
inline void CacheManager<T>::Reset( bool resetLongTerm )
{
  if ( tcache != NULL ) {
    ScopedLock sl( GetLock() );
    List* entry = tcache;
    while ( entry != NULL ) {
      entry->_valid = false;
      entry = entry->_next;
    }
  }
  if ( resetLongTerm ) {
    ScopedLock sl( GetLock() );
    delete longTerm;
    longTerm = NULL;
    // \ru Если нет параллельности, удаляется блокировка. \en If no parallelism, delete the lock.
#ifdef CACHE_DELETE_LOCK
    if ( !sl.IsLocked() ) {
      if ( lock != NULL )
        delete lock;
      lock = NULL;
    }
#endif
  }
}

//------------------------------------------------------------------------------
// \ru Удалить все кэши и отписаться от сборки мусора. Должна вызываться в последовательном участке кода.
// \en Delete all caches and unsubscribe from the garbage collection.Should be called in sequential code.
// ---
template<class T>
inline void CacheManager<T>::CleanAll()
{
  if ( tcache != NULL ) {
    if ( IsSubscribed() )
      UnsubcribeOnCleaning();
    delete tcache;
    tcache = NULL;
  }
#ifdef CACHE_DELETE_LOCK
  if ( lock != NULL ) {
    delete lock;
    lock = NULL;
  }
#endif
}

#endif // __TOOL_MULTITHREADING_H
