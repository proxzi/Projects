////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Реализация блокировок на базе системных механизмов синхронизации 
          и OpenMP блокировок.
         \en Locks implementation on base of system synchronization mechanisms
         and OpenMP locks. \~
  details \ru Реализация блокировок (в том числе блокировки в области видимости) 
          на базе системных механизмов синхронизации и OpenMP блокировок.\n
          \en Implementation of locks (including scoped lock) on base of 
          system synchronization mechanisms and OpenMP locks.\n \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __TOOL_MUTEX_H
#define __TOOL_MUTEX_H

#include <math_define.h>


////////////////////////////////////////////////////////////////////////////////
//
// \ru Управление блокировками.
// \en Locks management. \~
//
// \ru Переменная C3D_NATIVE_LOCK включает использование блокировок на базе
// \ru системных механизмов синхронизации вместо OpenMP,
// \ru что позволяет использование механизмов распараллеливания, отличных от OpenMP.
//
// \en The variable C3D_NATIVE_LOCK enables using locks on base of system
// \en synchronization mechanisms instead of OpenMP, that allows
// \en use of parallelization frameworks, other than OpenMP. \~
//
////////////////////////////////////////////////////////////////////////////////
#define C3D_NATIVE_LOCK


#ifdef C3D_NATIVE_LOCK
class ToolLock;

//------------------------------------------------------------------------------
/** \brief \ru Класс блокировки. \en Lock class. \~
    \details \ru Класс блокировки (реализация на базе системных механизмов синхронизации).
             \en Lock class (implementation on base of system synchronization mechanisms). \~
    \ingroup Base_Tools
*/
// ---
class MATH_CLASS CommonMutex
{
  ToolLock* m_lock;
public:
  CommonMutex();
  ~CommonMutex();

  void lock();
  void unlock();

private:
  // \ru Запрет копирования. \en Copy forbidden.
  CommonMutex ( const CommonMutex& );
  CommonMutex& operator = ( const CommonMutex& );
};

//------------------------------------------------------------------------------
/** \brief \ru Одинаковая реализация CommonMutex и CommonRecursiveMutex.
           \en Same implementation of CommonMutex and CommonRecursiveMutex. \~
    \ingroup Base_Tools
*/
#define CommonRecursiveMutex CommonMutex

#else // C3D_NATIVE_LOCK

//------------------------------------------------------------------------------
/** \brief \ru Класс блокировки.
           \en Lock class. \~
    \details \ru Класс блокировки на базе OpenMP lock.
           \en Lock class on base of OpenMP lock. \~
    \ingroup Base_Tools
*/
// ---
class MATH_CLASS CommonMutex
{
  omp_lock_t m_lock;
public:
  // For correct work, CommonMutex implementation should be encapsulated in cpp.
  CommonMutex();
  ~CommonMutex();
  void lock();
  void unlock();
};

//------------------------------------------------------------------------------
/** \brief \ru Класс блокировки на базе вложенного OpenMP lock.
           \en Wrapper for nested OpenMP lock. \~
    \ingroup Base_Tools
*/
// ---
class MATH_CLASS CommonRecursiveMutex
{
  omp_nest_lock_t m_lock;
public:
  // For correct work, CommonRecursiveMutex implementation should be encapsulated in cpp.
  CommonRecursiveMutex();
  ~CommonRecursiveMutex();
  void lock();
  void unlock();
};

#endif // C3D_NATIVE_LOCK


////////////////////////////////////////////////////////////////////////////////
//
// \ru Поддержка многопоточности при использовании произвольного параллельного фреймворка
// \ru в пользовательском приложении.
// \ru Чтобы использовать интерфейсы ядра в нескольких потоках,
// \ru для ядра должен быть установлен режим многопоточных вычислений не ниже mtm_SafeItems.
//
// \ru При использовании параллельных механизмов, отличных от OpenMP, пользовательское приложение
// \ru обязано нотифицировать ядро о входе в каждый параллельный регион и выходе из него.
// \ru Для этого могут быть использованы класс ParallelRegionGuard (защитник параллельного региона
// \ru в области видимости), функции EnterParallelRegion и ExitParallelRegion
// или макросы ENTER_PARALLEL и EXIT_PARALLEL.
// \ru Примеры:
//  {
//    ParallelRegionGuard l;
//    std::thread t1( function1 );
//    std::thread t2( function2 );
//    t1.join();
//    t2.join();
//  }
//  {
//    EnterParallelRegion();
//    std::thread t1( function1 );
//    std::thread t2( function2 );
//    t1.join();
//    t2.join();
//    ExitParallelRegion();
//  }
//
//
// \en Support of multithreading when using an arbitrary parallel framework in user application.
//
// \en For using the kernel interfaces in several threads, the multithreading mode mtm_SafeItems
// \en or higher should be defined for the kernel.
//
// \en When using a parallel framework other than OpenMP in user code, the application must notify
// \en the kernel about entering and exiting a parallel region.
// \en For that, the class ParallelRegionGuard (a scoped guard of parallel region),
// \en the functions EnterParallelRegion and ExitParallelRegion, 
// or macros ENTER_PARALLEL and EXIT_PARALLEL could be used.
// \en Examples:
//  {
//    ParallelRegionGuard l;
//    std::thread t1( function1 );
//    std::thread t2( function2 );
//    t1.join();
//    t2.join();
//  }
//  {
//    EnterParallelRegion();
//    std::thread t1( function1 );
//    std::thread t2( function2 );
//    t1.join();
//    t2.join();
//    ExitParallelRegion();
//  }
//
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
/** \brief \ru Защитник параллельного региона в области видимости.
           \en Scoped guard of parallel region. \~
  \details \ru Класс защищает регион кода, выполняющийся параллельно.
           Работает в области видимости.
           Должен использоваться для защиты параллельного кода,
           если используются средства распараллеливания, отличные от OpenMP.
           Пример использования:
             {
               ParallelRegionGuard l;
               std::thread t1( function1 );
               std::thread t2( function2 );
               t1.join();
               t2.join();
             }
           \en The class guards a code region running in parallel.
           Works in scope.
           Should be used to protect parallel code if parallel framework other than OpenMP is used.
           Example of use:
             {
               ParallelRegionGuard l;
               std::thread t1( function1 );
               std::thread t2( function2 );
               t1.join();
               t2.join();
             }
   \ingroup Base_Tools
*/
// ---
class MATH_CLASS ParallelRegionGuard
{
public:
  ParallelRegionGuard();
  ~ParallelRegionGuard();
};

//------------------------------------------------------------------------------
/** \brief \ru Функция нотифицирует ядро о входе в параллельный блок кода.
           Вызов функции должен стоять перед началом параллельного блока.
           \en The function notifies the kernel about entering a parallel region.
           The function call should be placed before the start of a parallel block
*/
// ---
MATH_FUNC( void ) EnterParallelRegion();

//------------------------------------------------------------------------------
/** \brief \ru Функция нотифицирует ядро о выходе из параллельного блока кода.
           Вызов функции должен стоять после окончания параллельного блока.
           \en The function notifies the kernel about exiting a parallel region.
           The function call should be placed after the end of the parallel block.
*/
// ---
MATH_FUNC( void ) ExitParallelRegion();


//------------------------------------------------------------------------------
// \ru Макросы для нотификации о входе и выходе из параллельного цикла.
// Вызов макросов при использовании OpenMP не обязателен, однако значительно ускоряет 
// выполнение параллельного цикла.
// Вызов ENTER_PARALLEL должен стоять перед началом параллельного блока.
// Вызов EXIT_PARALLEL должен стоять после окончания параллельного блока.
// Пример использования:
//   bool useParallel = Math::CheckMultithreadedMode( mtm_Items );
//   ENTER_PARALLEL( useParallel );
//   #pragma omp parallel for
//   for ( ptrdiff_t i = 0; i < count; ++i ) {
//     /* Cycle body */
//   }
//   EXIT_PARALLEL( useParallel );
//
/// \ru Macros for notification of entering and exiting a parallel block.
// Calling the macros when using OpenMP is not required, but significantly speeds up  
// the execution of parallel cycle.
// The call ENTER_PARALLEL should be placed before the start of a parallel block.
// The call EXIT_PARALLEL should be placed after the end of the parallel block.
// Example of use:
//   bool useParallel = Math::CheckMultithreadedMode( mtm_Items );
//   ENTER_PARALLEL( useParallel );
//   #pragma omp parallel for
//   for ( ptrdiff_t i = 0; i < count; ++i ) {
//     /* Cycle body */
//   }
//   EXIT_PARALLEL( useParallel );
// ---

//------------------------------------------------------------------------------
/** \brief \ru Если useParallel == true, нотифицирует ядро о входе в параллельный блок кода.
           \en If useParallel == true, notifies the kernel about entering a parallel region.
  \details \ru Если useParallel == true, нотифицирует ядро о входе в параллельный блок кода.
           Вызов должен стоять перед началом параллельного блока (перед прагмой OpenMP).
           Использование макроса значительно ускоряет параллельные циклы OpenMP.
           \en If useParallel == true, notifies the kernel about entering a parallel region.
           The call should be placed before the start of a parallel block (before OpenMP pragma).
           Using a macro speeds up parallel OpenMP cycles significantly.
*/
// ---
#define ENTER_PARALLEL(useParallel) if ( useParallel ) EnterParallelRegion();

//------------------------------------------------------------------------------
/** \brief \ru Если useParallel == true, нотифицирует ядро о выходе из параллельного блока кода.
           \en If useParallel == true, notifies the kernel about exiting a parallel region.
  \details \ru Если useParallel == true, нотифицирует ядро о выходе из параллельного блока кода.
           Вызов должен стоять после окончания параллельного блока.
           Использование макроса значительно ускоряет параллельные циклы OpenMP.
           \en If useParallel == true, notifies the kernel about exiting a parallel region.
           The call should be placed after the end of the parallel block.
           Using a macro speeds up parallel OpenMP cycles significantly.
*/
// ---
#define EXIT_PARALLEL(useParallel)  if ( useParallel ) ExitParallelRegion();

//------------------------------------------------------------------------------
/** \brief \ru Функция определяет, выполняется ли код параллельно.
           \en The function determines whether the code is executed in parallel.
*/
// ---
MATH_FUNC( bool ) IsInParallel();

////////////////////////////////////////////////////////////////////////////////
//
// \ru Блокировки и другие средства синхронизации.
// \en Locks and other synchronization objects. \~

// \ru В качестве блокировок должны использоваться CommonMutex и CommonRecursiveMutex
// \ru (OpenMP lock не должны использоваться напрямую).
//
// \en CommonMutex and CommonRecursiveMutex should be used as locks
// \en (OpenMP locks should not be used directly).
//
////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
/** \brief \ru Блокировка в области видимости. Может принимать нулевой указатель на мьютекс.
           Блокировка происходит, если указатель на мьютекс ненулевой и код выполняется параллельно.
           \en Scoped lock. Can accept a null pointer to a mutex.
           Locking occurs if the pointer to the mutex is nonzero and the code runs in parallel. \~
    \ingroup Base_Tools
*/
// ---
class MATH_CLASS ScopedLock
{
  CommonMutex* m_mutex;
public:
  ScopedLock( CommonMutex* mutex, bool parallelCheck = true );
  ~ScopedLock();

  // \ru Выполнена ли реальная блокировка. \en Whether a real locking performed.
  bool IsLocked();

private:
  ScopedLock();
  ScopedLock ( const ScopedLock& );
  ScopedLock& operator = ( const ScopedLock& );
};

//------------------------------------------------------------------------------
/** \brief \ru Рекурсивная блокировка в области видимости. Может принимать нулевой указатель на мьютекс.
           Блокировка происходит, если указатель на мьютекс ненулевой и код выполняется параллельно.
           \en Recursive scoped lock. Can accept a null pointer to a mutex.
           Locking occurs if the pointer to the mutex is nonzero and the code runs in parallel. \~
\ingroup Base_Tools
*/
// ---
class MATH_CLASS ScopedRecursiveLock
{
  CommonRecursiveMutex* m_mutex;
public:
  ScopedRecursiveLock( CommonRecursiveMutex* mutex, bool parallelCheck = true );
  ~ScopedRecursiveLock();

  // \ru Выполнена ли реальная блокировка. \en Whether a real locking performed.
  bool IsLocked();

private:
  ScopedRecursiveLock();
  ScopedRecursiveLock ( const ScopedRecursiveLock& );
  ScopedRecursiveLock& operator = ( const ScopedRecursiveLock& );
};

//------------------------------------------------------------------------------
/** \brief \ru Базовый объект синхронизации с отложенной инициализацией.
           \en Base synchronization object with lazy initialization. \~
    \details \ru Базовый объект, предоставляющий средства синхронизации и создающий блокировку при необходимости. \n
             \en Base object which provides means of synchronization and creates a lock when needed. \n \~
\ingroup Base_Tools
*/  
// ---  
class MATH_CLASS MbSyncItem {
protected:
  mutable CommonMutex * m_comLock;  // \ru Критическая секция для монопольного доступа к объекту. \en The critical section for exclusive access to the object.
  mutable bool          m_locked;

public:
  MbSyncItem();
  virtual ~MbSyncItem();

  // \ru Включить блокировку (блокировка происходит только при наличии параллельности).
  // \en Switch lock on (locking happens only in parallel region).
  void Lock() const;
  // \ru Снять блокировку, если она была установлена.
  // \en Switch lock off if locking has been set.
  void Unlock() const;

  // \ru Выдать указатель на объект мьютекса. Возращает NULL, если параллельности нет. Для использования в ScopedLock.
  // \en Get a pointer to the mutex object. Return NULL if no parallelism. For use in ScopedLock.
  CommonMutex * GetLock() const;
};

//------------------------------------------------------------------------------
/** \brief \ru Базовый объект синхронизации с отложенной инициализацией, поддерживающий множественные блокировки.
           \en Base synchronization object with lazy initialization which supports nested locks. \~
    \details \ru Базовый объект синхронизации, поддерживающий множественные блокировки и создающий блокировку при необходимости. \n
             \en Base synchronization object with support of nested locks which creates a lock if necessary. \n \~
\ingroup Base_Tools
*/  
// ---  
class MATH_CLASS MbNestSyncItem {
protected:
  mutable CommonRecursiveMutex * m_comLock;  // \ru Критическая секция для монопольного доступа к объекту. \en The critical section for exclusive access to the object.
  mutable bool                   m_locked;

public:
  MbNestSyncItem();
  virtual ~MbNestSyncItem();

  // \ru Включить блокировку (блокировка происходит только при наличии параллельности).
  // \en Switch lock on (locking happens only in parallel region).
  void Lock() const;
  // \ru Снять блокировку, если она была установлена.
  // \en Switch lock off if locking has been set.
  void Unlock() const;

  // \ru Выдать указатель на объект мьютекса. Возращает NULL, если параллельности нет. Для использования в ScopedLock.
  // \en Get a pointer to the mutex object. Return NULL if no parallelism. For use in ScopedLock.
  CommonRecursiveMutex * GetLock() const;
};

//------------------------------------------------------------------------------
/** \brief \ru Базовый объект, предоставляющий средства синхронизации.
           \en Base object providing means of synchronization. \~
  \details \ru Базовый объект, предоставляющий средства синхронизации. \n
           \en Base object providing means of synchronization. \n \~
\ingroup Base_Tools
*/
// ---  
class MATH_CLASS MbPersistentSyncItem {
protected:
  mutable CommonMutex m_comLock;  // \ru Критическая секция для монопольного доступа к объекту. \en The critical section for exclusive access to the object.

public:
  MbPersistentSyncItem();
  virtual ~MbPersistentSyncItem();

  void Lock() const;
  void Unlock() const;
};

//------------------------------------------------------------------------------
/** \brief \ru Базовый объект синхронизации, поддерживающий множественные блокировки.
           \en Base synchronization object with support of nested locks. \~
  \details \ru Базовый объект синхронизации, поддерживающий множественные блокировки. \n
           \en Base synchronization object with support of nested locks. \n \~
\ingroup Base_Tools
*/
// ---  
class MATH_CLASS MbPersistentNestSyncItem {
protected:
  mutable CommonRecursiveMutex m_comLock;  // \ru Критическая секция для монопольного доступа к объекту. \en The critical section for exclusive access to the object.

public:
  MbPersistentNestSyncItem();
  virtual ~MbPersistentNestSyncItem();

  void Lock() const;
  void Unlock() const;
};


//------------------------------------------------------------------------------
// \ru Установлен ли режим безопасной многопоточности (используется в CacheManager).
//  \en Whether is enabled a safe multithreading mode (used in CacheManager).
// ---
MATH_FUNC(bool) IsSafeMultithreading();

//------------------------------------------------------------------------------
// \ru Получить идентификатор текущего потока.
//  \en Get a current thread identifier.
// ---
MATH_FUNC( unsigned int ) GetThreadKey();

//------------------------------------------------------------------------------
// \ru Получить указатель на глобальный мьютекс (используется в CacheManager).
// \en Get a pointer to the global mutex (used in CacheManager).
// ---
MATH_FUNC( CommonMutex* ) GetGlobalLock();

//------------------------------------------------------------------------------
// \ru Получить указатель на глобальный рекурсивный мьютекс (используется для операций выделения и освобождения памяти).
// \en Get a pointer to the global recursive mutex (used for memory allocation and deallocation operations).
// ---
MATH_FUNC( CommonRecursiveMutex* ) GetGlobalRecursiveLock();

//------------------------------------------------------------------------------
// \ru Установить блокировку в области видимости для операций выделения и освобождения памяти.
// \en Set scoped lock for memory allocation and deallocation operations.
// ---
#define SET_MEMORY_SCOPED_LOCK ScopedRecursiveLock memScopedLock( GetGlobalRecursiveLock() );

#endif // __TOOL_MUTEX_H
