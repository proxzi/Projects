///////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс WaitCondition является классом синхронизации, который может быть 
               использован для блокирования потока или нескольких потоков одновременно
               пока не произойдет какое-нибудь событие.
           \en NO TRANSLATION. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_WAITCONDITION_H
#define __VSN_WAITCONDITION_H

#include <limits.h>
#include <vsn_global.h>

VSN_BEGIN_NAMESPACE
class Mutex;
class WaitConditionPrivate;
//----------------------------------------------------------------------------
//
/** \brief \ru Класс WaitCondition является классом синхронизации, который может быть 
               использован для блокирования потока или нескольких потоков одновременно,
               пока не произойдет любое из событий:
               1) будет получено извещение из другого потока.
               2) выйдет тайм-аут
               3) произойдет пробуждение
           \en NO TRANSLATION. \~
    \details \ru Любой поток, который намерен ждать WaitCondition должен сначала быть заблокирован. 
                 Операция ожидания атомарно освобождает мьютекс и приостанавливает выполнение потока. 
                 Когда переменная условия уведомляется, поток пробуждается, и мьютекс снова разблокируется.
             \en NO TRANSLATION. \n \~
    \ingroup Vision_Thread
*/
// ---
class VSN_CLASS WaitCondition
{
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    WaitCondition();
    /// \ru Деструктор. \en Destructor.
    ~WaitCondition();
public:
    /**
    \brief \ru Wait вызывает текущий поток, чтобы блокировать его до тех пор 
               пока переменная условия будет уведомлена или произойдет пробуждение. 
           \en NO TRANSLATION.  \~
        \param[in] pMutex - \ru блокирующий мютекс.
                            \en NO TRANSLATION. \~
        \param[in] realTime - \ru время ожидания.
                              \en NO TRANSLATION. \~
    */
    bool Wait(Mutex* pMutex, unsigned long realTime = ULONG_MAX);
    /// \ru Пробудить один потоки. \en Destructor.
    void NotifyOne();
    /// \ru Пробудить все потоки. \en Destructor.
    void NotifyAll();
private:
    std::shared_ptr<WaitConditionPrivate> m_ptr;
};

VSN_END_NAMESPACE

#endif // __VSN_WAITCONDITION_H
