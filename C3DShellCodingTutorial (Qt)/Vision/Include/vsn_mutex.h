///////////////////////////////////////////////////////////////////////////////
/**
    \file
        \brief \ru Класс Mutex представляет как нерекурсивную семантику владения, так и рекурсивную.
                   Класс MutexLocker - это класс для удобства, который упрощает блокировку и разблокировку мьютексов.
               \en Mutex class presents non-recursive semantics of ownership and recursive one as well.
                   MutexLocker class is a class for comfort that simplifies blocking and unlocking mutexes. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_MUTEX_H
#define __VSN_MUTEX_H

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class MutexPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс Mutex является примитивом синхронизации, который может использоваться для
               защиты разделяемых данных от одновременного доступа нескольких потоков. В случае
               recursive класс Mutex может быть использован для защиты общих данных от одновременного 
               доступа нескольких потоков. \n
           \en Mutex class is a synchronization primitive that can be used to protect the shared data
               from simultaneous access of several streams. In case of recursive one, Mutex class
               can be used to protect the common data from simultaneous access of several streams. \~
  \details \ru Если нерекурсивная семантика владения (recursive равно false):
               * Вызывающий поток владеет мьютексом со времени успешного вызова Lock или Trylock 
                 и до момента вызова Unlock.
               * Пока поток владеет мьютексом, все остальные потоки при попытке завладения им 
                 блокируются на вызове Lock или получают значение false при вызове Trylock.
               * Вызывающий поток не должен владеть мьютексом до вызова Lock или Trylock.

               Если рекурсивная семантика владения (recursive равно true):
               * Вызывающий поток владеет recursive_mutex за определенный период времени, который начинается, 
                 когда он успешно вызывает либо Lock или Trylock. В течение этого периода поток может сделать 
                 дополнительные вызовы Lock или Trylock. Период владения заканчивается, когда поток делает 
                 соответствующее количество обращений к Unlock.
               * Когда поток владеет mutex, все остальные потоки будут блокированы (при вызове Lock) или 
                 возвращать значение false при вызове Trylock. \n
           \en If non-recursive semantics of ownership (recursive is equal to false):
               * The calling stream owns mutex since successful calling Lock and Trylock and till calling Unlock.
               * While the stream owns mutex, all the rest of streams are blocked, if an attempt of owning it, 
                 when calling Lock or get false value when calling Trylock.
               * The calling stream mustn't own mutex before calling Lock or Trylock.

               If recursive semantics of ownership (recursive is equal to true):
               * The calling stream owns recursive_mutex for a certain period that starts when it calls successfully
                 Lock or Trylock. For this period the stream can make additional calls of Lock and Trylock.
                 Period of ownership finishes when the stream makes the corresponding request quantity to Unlock.
               * When the stream owns mutex, all the rest of streams will be blocked (when calling Lock) or return 
                 false value when calling Trylock. \n \~
    \ingroup Vision_Thread
*/
// ---
class VSN_CLASS Mutex
{
public:
    enum RecursionMode { NonRecursive, Recursive };
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit Mutex(RecursionMode mode = NonRecursive);
    /// \ru Деструктор. \en Destructor. \~
    ~Mutex();
public:
    /// \ru Вернуть признак рекурсии. \en Returns recursion flag.
    bool IsRecursive();
    /// \ru Блокировать мьютекс - выполнение останавливается, если мьютекс недоступен. \en Blocks mutex. Performing stops if mutex is not available. \~
    void Lock();
    /// \ru Блокировать мьютекс - выполнение останавливается, если мьютекс недоступен. \en Blocks mutex. Perfoming stops if mutex is not available. \~
    void lock();
    /// \ru Пытается заблокировать мьютекс, возвращается, если мьютекс недоступен. \en Tries to block mutex. Returned if mutex is not available. \~
    bool TryLock();
    /// \ru Разблокировать мьютекс. \en Unlocks mutex. \~
    void Unlock();
    /// \ru Разблокировать мьютекс. \en Unlocks mutex. \~
    void unlock();

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;
private:
    std::shared_ptr<MutexPrivate> m_ptrData;

};

//----------------------------------------------------------------------------
//
/** \brief \ru Класс MutexLocker является оболочкой мьютекса, которая обеспечивает удобный механизм владением 
               мьютексом на протяжении области видимости.
           \en MutexLocker class is a mutex wrapper that provides convenient ownership mechanism of mutex
               throughout the scope. \~
  \details \ru Когда MutexLocker создан, он берет на себя ответственность мьютекса. Когда управление покидает область, 
               в которой MutexLocker был создан, MutexLocker разрушается и мьютекс освобождается. \n
           \en When MutexLocker is created, it takes mutex responsibility. When control leaves area, in which
               MutexLocker was created, MutexLocker destroys and mutex is released. \n \~
  \ingroup Vision_Thread
*/
// ---
class VSN_CLASS MutexLocker
{
public:
    /// \ru Конструктор по умолчанию. Блокирует мьютекс. \en Default constructor that blocks mutex. \~
    inline explicit MutexLocker(Mutex* pMutex = nullptr) : m_bOwns(false), m_pMutex(pMutex) 
    { if (m_pMutex) m_pMutex->Lock(); if (m_pMutex) m_bOwns = true;  }
    /// \ru Деструктор. \en Destructor. \~
    inline ~MutexLocker() { if (m_pMutex && m_bOwns) m_pMutex->Unlock(); }
public:
    /// \ru Разблокировать мьютекс. \en Unlocks mutex. \~
    inline void Unlock() { if (!m_pMutex || !m_bOwns) { VSN_ASSERT(false); return; } m_pMutex->Unlock(); m_bOwns = false; }
    /// \ru Блокировать мьютекс - выполнение останавливается, если мьютекс недоступен. \en Blocks mutex. Performing stops if mutex is not available. \~
    inline void Relock() { if (m_pMutex) m_pMutex->Lock(); m_bOwns = true; }
    /// \ru Вернуть указатель на мьютекс. \en Returns pointer to mutex. \~
    inline Mutex* GetMutex() const { return m_pMutex; }
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    MutexLocker& operator=(MutexLocker&& other)
    {
        if (this != &other)
        {
            if (m_bOwns)
                Unlock();
            m_pMutex = other.m_pMutex;
            m_bOwns = other.m_bOwns;
            other.m_pMutex = 0;
            other.m_bOwns = false;
        }
        return (*this);
    }

    MutexLocker(const MutexLocker&) = delete;
    MutexLocker& operator=(const MutexLocker&) = delete;
private:
    bool m_bOwns;
    Mutex* m_pMutex;
};

VSN_END_NAMESPACE

#endif // QMUTEX_H
