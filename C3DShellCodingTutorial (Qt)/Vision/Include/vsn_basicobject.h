////////////////////////////////////////////////////////////////////////////////
/**
  \file 
  \brief \ru Класс BasicObject является базовым классом для всех объектов.
         \en BasicObject class is the base class for all objects. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_BASICOBJECT_H
#define __VSN_BASICOBJECT_H

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <tuple>
#include <set>
#include <unordered_set>
#include <vector>
#include <exception>

#include "vsn_internal.h"
#include "vsn_mutex.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
enum class ConnectionInner
{
    AutoConnection,
    DirectConnection,
    QueuedConnection,
    BlockingQueuedConnection,
    InternalDisconnected
};

class BasicObject;
/* ExpectedSlot */
class VSN_CLASS ExpectedSlot
{
public:
    ExpectedSlot(const ExpectedSlot&) = delete;
    explicit ExpectedSlot(BasicObject* pSender, std::unique_ptr<Internal::AbsStorageFunction> signal, BasicObject* pReceiver,
        std::unique_ptr<Internal::AbsStorageFunction> slot, std::unique_ptr<Internal::AbsStorageTuple> tupleData);
public:
    BasicObject* GetSender() const { return m_pSender; }
    BasicObject* GetReceiver() const { return m_pReceiver; }

    std::unique_ptr<Internal::AbsStorageFunction> GetMoveSlot() { return std::move(m_slot); }
    std::unique_ptr<Internal::AbsStorageTuple> GetMoveTupleData() { return std::move(m_tupleData); }
    void operator()() const;
private:
    BasicObject* m_pSender;
    std::unique_ptr<Internal::AbsStorageFunction>  m_signal;
    BasicObject* m_pReceiver;
    std::unique_ptr<Internal::AbsStorageFunction>  m_slot;
    std::unique_ptr<Internal::AbsStorageTuple> m_tupleData;
};

class BasicObjectPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс BasicObject является базовым классом для всех объектов.
           \en BasicObject class is the base class for all scene objects. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS BasicObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    BasicObject();
    /// \ru Деструктор. \en Destructor.
    virtual ~BasicObject();
public: // Slot
    BasicObject* GetSender() const;
protected: // Signal
    static Internal::AbsStorageFunction*& GetThreadLocalCurrentSignal();
    int GetConnections(const BasicObject* pReceiver, const Internal::AbsStorageFunction& signalMethod) const;
    std::set<BasicObject *> GetReceiverList(const Internal::AbsStorageFunction& signalMethod) const;
private: // Signal
    struct ConnectData
    {
        std::unique_ptr<const Internal::AbsStorageFunction> signalMethod;
        const BasicObject* pReceiver;
        std::unique_ptr<const Internal::AbsStorageFunction> slotMethod;
        ConnectionInner type;
    };
    // часть деструктора
    static Mutex& GetMutexBeingDestroyed();
    static std::unordered_set<const BasicObject*>& GetBeingDestroyed();

    virtual void HandleException(std::exception_ptr data);
    void AddConnection(std::unique_ptr<const Internal::AbsStorageFunction> signalMethod, const BasicObject*, std::unique_ptr<const Internal::AbsStorageFunction> slotMethod, ConnectionInner type) const;
    void DestroySignals();

    template<class Sender, class SignalClass, class ...SignalArgTypes, class ...Ts>
    friend void PrivateTrigger(const char*, Sender &sender, void (SignalClass::*signal)(SignalArgTypes...), Ts &&... Vs);

    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
    friend bool PrivateConnect(const Sender& sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver& receiver, SlotReturn(SlotClass::*slotMethod)(SlotArgs...), ConnectionInner type, bool uniqueConnection);

    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
    friend bool PrivateConnect(const Sender& sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver& receiver, T slotLambda, ConnectionInner type, bool uniqueConnection);

    template<class Sender, class Receiver>
    friend bool PrivateConnect(const Sender& sender, std::unique_ptr<Internal::AbsStorageFunction> signalMethod, const Receiver& receiver, std::unique_ptr<Internal::AbsStorageFunction> slotMethod, ConnectionInner type, bool uniqueConnection);

    template<class Sender, class Receiver>
    friend bool PrivateDisconnect(const Sender& sender, const Internal::AbsStorageFunction* pSignal, const Receiver* pReceiver, const Internal::AbsStorageFunction* pSlot);
protected: // Slot
    std::set<BasicObject*> GetSenderList() const;
private: // Slot
    static BasicObject*& GetThreadLocalCurrentSender();
    virtual bool IsSameThreads() const;
    virtual void AsyncSlot(ExpectedSlot* pData, ConnectionInner type);
    void DestroySlots();
public:
    mutable Mutex m_signalMutex;
private:
    // Signal
    mutable Mutex m_mutexConnectList;
    // список подключений от моего сигнала к некоторому приемнику
    mutable std::vector<ConnectData> m_connectList;
    // часть разъединения
    mutable int m_activateBusy = 0;
    mutable int m_raceCount = 0;
    // Slot
    // список возможных отправителей для этого приемника
    mutable std::vector<const BasicObject*> m_possibleSenders;
    mutable Mutex m_mutexPossibleSenders;
    std::shared_ptr<BasicObjectPrivate> m_dPtr;
};

//-----------------------------------------------------------------------------
//
// ---
template<class Sender, class SignalClass, class ...SignalArgTypes, class ...Ts>
void PrivateTrigger(const char*, Sender& sender, void (SignalClass::*signal)(SignalArgTypes...), Ts &&... Vs)
{
    // обеспечить передачу сигналов args
    static_assert(std::is_convertible<std::tuple<Ts...>, std::tuple<SignalArgTypes...>>::value,
        "PrivateTrigger():  Signal parameter mismatch.");

    Internal::StorageFunction<void (SignalClass::*)(SignalArgTypes...)> signalStorage(signal);

    // сохранить адреса отправителя
    const BasicObject* senderPtr = &sender;

    // в очередь queuedConnections
    MutexLocker senderLock { &sender.m_mutexConnectList };

    // хранить данные сигнала, если false означает, что данные не будут скопированы
    Internal::StorageTupleData<SignalArgTypes...> dataPack(false, std::forward<Ts>(Vs)...);

    bool raceHappened = false;
    int maxCount = static_cast<int>(sender.m_connectList.size());
    BasicObject* priorSender = BasicObject::GetThreadLocalCurrentSender();
    BasicObject::GetThreadLocalCurrentSender() = &sender;

    Internal::AbsStorageFunction* priorSignal = BasicObject::GetThreadLocalCurrentSignal();
    BasicObject::GetThreadLocalCurrentSignal() = &signalStorage;
    for (int k = 0; k < maxCount; ++k)
    {
        const BasicObject::ConnectData& connection = sender.m_connectList[k];

        if (*(connection.signalMethod) != signalStorage)
            continue; // нет совпадения в connectionList для этого сигнала

        if (connection.type == ConnectionInner::InternalDisconnected)
            continue; // соединение отмечено для удаления

        BasicObject* pReceiver = const_cast<BasicObject *>(connection.pReceiver);

        // const ссылается на unique_ptr
        const std::unique_ptr<const Internal::AbsStorageFunction>& slotStorage = connection.slotMethod;

        bool receiverInSameThread = pReceiver->IsSameThreads();

        int old_activateBusy = sender.m_activateBusy;
        int old_raceCount = sender.m_raceCount;

        sender.m_activateBusy++;
        senderLock.Unlock();

        try
        {
            if ((connection.type == ConnectionInner::AutoConnection && !receiverInSameThread) || (connection.type == ConnectionInner::QueuedConnection))
            {
                // передача true указывает, что данные будут скопированы (сохранены в куче)
                ExpectedSlot tempObj(&sender, signalStorage.Duplicate(), pReceiver, slotStorage->Duplicate(), Internal::make_unique<Internal::StorageTupleData<SignalArgTypes...>>(true, std::forward<Ts>(Vs)...));
        //            pReceiver->AsyncSlot(std::move(tempObj), ConnectionInner::QueuedConnection);
                pReceiver->AsyncSlot(&tempObj, ConnectionInner::QueuedConnection);
            }
            else if (connection.type == ConnectionInner::BlockingQueuedConnection)
            {
                // передача false указывает, что данные не будут скопированы
                ExpectedSlot tempObj(&sender, signalStorage.Duplicate(), pReceiver, slotStorage->Duplicate(), Internal::make_unique<Internal::StorageTupleData<SignalArgTypes...>>(false, std::forward<Ts>(Vs)...));
        //            pReceiver->AsyncSlot(std::move(tempObj), ConnectionInner::BlockingQueuedConnection);
                pReceiver->AsyncSlot(&tempObj, ConnectionInner::BlockingQueuedConnection);
            }
            else if (connection.type == ConnectionInner::DirectConnection || connection.type == ConnectionInner::AutoConnection)
            {
                // прямая связь
                // invoke вызовы по фактическому методу
                slotStorage->Invoke(pReceiver, &dataPack);
            }

            MutexLocker lock(&BasicObject::GetMutexBeingDestroyed());   // необходимо заблокировать чтение
            if (BasicObject::GetBeingDestroyed().count(senderPtr))
            {
                // отправитель был уничтожен
                BasicObject::GetThreadLocalCurrentSender() = priorSender;
                BasicObject::GetThreadLocalCurrentSignal() = priorSignal;
                if (old_activateBusy == 0)
                    BasicObject::GetBeingDestroyed().erase(senderPtr);
                return;
            }
        }
        catch (...)
        {
            BasicObject::GetThreadLocalCurrentSender() = priorSender;
            BasicObject::GetThreadLocalCurrentSignal() = priorSignal;

            MutexLocker lock(&BasicObject::GetMutexBeingDestroyed()); // необходимо заблокировать чтение

            if (BasicObject::GetBeingDestroyed().count(senderPtr))
            {
                // отправитель уничтожен - все сделано
                if (old_activateBusy == 0)
                    BasicObject::GetBeingDestroyed().erase(senderPtr);
                return;
            }
            else 
            {
                sender.HandleException(std::current_exception());
                BasicObject::GetThreadLocalCurrentSender() = &sender;
            }
        }

        try
        {
            senderLock.Relock();
            sender.m_activateBusy--;
        }
        catch (std::exception &)
        {
            BasicObject::GetThreadLocalCurrentSender() = priorSender;
            BasicObject::GetThreadLocalCurrentSignal() = priorSignal;
            //         std::throw_with_nested(std::invalid_argument("activate(): Не удалось получить блокировку отправителя"));
        }

        if (old_raceCount != sender.m_raceCount)
        {
            // connectionList изменен
            raceHappened = true;
            maxCount = static_cast<int>(sender.m_connectList.size());
            // connect() может добавить запись в конец списка
            // disconnect() может отметить соединение как ожидающее удаление
        }
    }

    BasicObject::GetThreadLocalCurrentSender() = priorSender;
    BasicObject::GetThreadLocalCurrentSignal() = priorSignal;

    if (raceHappened && sender.m_activateBusy == 0) 
    {
        // завершить очистку для разъединения
        sender.m_connectList.erase(std::remove_if(sender.m_connectList.begin(), sender.m_connectList.end(),
            [](const BasicObject::ConnectData & tmp) { return tmp.type == ConnectionInner::InternalDisconnected; }),
            sender.m_connectList.end());
    }
}

//-----------------------------------------------------------------------------
// signal & slot method ptr
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool PrivateConnect(const Sender& sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver& receiver,
    SlotReturn(SlotClass::*slotMethod)(SlotArgs...), ConnectionInner type, bool uniqueConnection)
{
    /*
    // является отправителем ссылки rvalue
    static_assert(! std::is_rvalue_reference<Sender &&>::value, "PrivateConnect():  Sender can not be an rvalue");
    // является приемником для ссылки rvalue
    static_assert(! std::is_rvalue_reference<Receiver &&>::value, "PrivateConnect():  Receiver can not be an rvalue");
    */
    // Отправитель должен быть тем же классом, что и SignalClass или отправитель - ребенок SignalClass
    static_assert(std::is_base_of<SignalClass, Sender>::value, "PrivateConnect():  Signal was not a child class of Receiver");
    // Приемник должен быть того же класса, что и SlotClass или приемник - ребенок SlotClass
    static_assert(std::is_base_of<SlotClass, Receiver>::value, "PrivateConnect():  Slot was not a child class of Receiver");
    // сравнить сигнал и список параметров слота
    static_assert(Internal::vsn_TestConnectAargs<void(*)(SignalArgs...), void(*)(SlotArgs...) >::value, "connect():  Incompatible signal/slot arguments");

    if (signalMethod == nullptr)
        throw std::invalid_argument("PrivateConnect() Can not connect, signal is null");

    if (slotMethod == nullptr)
        throw std::invalid_argument("PrivateConnect(): Can not connect, slot is null");

    std::unique_ptr<Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)>>
        newSignalMethod(new Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)>(signalMethod));

    std::unique_ptr<Internal::StorageFunction<void (SlotClass::*)(SlotArgs...)>>
        newSlotMethod(new Internal::StorageFunction<void (SlotClass::*)(SlotArgs...)>(slotMethod));

    MutexLocker senderLock { &sender.m_mutexConnectList };
    if (uniqueConnection)
    {
        // убедимся, что соединение не добавлено дважды
        for (auto &item : sender.m_connectList)
        {
            if (item.pReceiver != &receiver)
                continue;

            if (*(item.signalMethod) != *(newSignalMethod))
                continue;

            if (*(item.slotMethod) != *(newSlotMethod))
                continue;
            // соединение уже существует
            return false;
        }
    }
    sender.AddConnection(std::move(newSignalMethod), &receiver, std::move(newSlotMethod), type);
    return true;
}

//-----------------------------------------------------------------------------
// сигнал метод ptr, слот лямбда
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool PrivateConnect(const Sender &sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver &receiver, T slotLambda, ConnectionInner type, bool uniqueConnection)
{
    // Отправитель должен быть тем же классом, что и SignalClass, а Sender - дочерним элементом SignalClass
    Internal::vsn_TestConnectSenderSignal<Sender, SignalClass>();
    // сравнить сигнал и список параметров слота
    Internal::vsn_TestConnectSignalSlotArgs_1<T, SignalArgs...>();

    if (signalMethod == nullptr)
        throw std::invalid_argument("Connect(): Can not connect, the signal is zero");

    std::unique_ptr<Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)>>
        newSignalMethod(new Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)>(signalMethod));

    std::unique_ptr<Internal::StorageFunction<T>> newSlotLambda(new Internal::StorageFunction<T>(slotLambda));
    MutexLocker senderLock { &sender.m_mutexConnectList };
    if (uniqueConnection)
    {
        // проверить, что соединение не добавлено дважды
        for (auto &item : sender.m_connectList)
        {
            if (item.pReceiver != &receiver)
                continue;
            if (*(item.signalMethod) != *(newSignalMethod))
                continue;
            // не удалось проверить, прошел ли пройденный slotLambda = newSlotLambda
            // соединение уже существует
            return false;
        }
    }
    sender.AddConnection(std::move(newSignalMethod), &receiver, std::move(newSlotLambda), type);
    return true;
}

//-----------------------------------------------------------------------------
// signal & slot
// ---
template<class Sender, class Receiver>
bool PrivateConnect(const Sender &sender, std::unique_ptr<Internal::AbsStorageFunction> signalMethod, const Receiver& receiver,
    std::unique_ptr<Internal::AbsStorageFunction> slotMethod, ConnectionInner type, bool uniqueConnection)
{
    MutexLocker senderLock { &sender.m_mutexConnectList };
    if (uniqueConnection)
    {
        // убедитесь, что соединение не добавлено дважды
        for (auto &item : sender.m_connectList)
        {
            if (item.pReceiver != &receiver)
                continue;
            if (*(item.signalMethod) != *(signalMethod))
                continue;
            if (*(item.slotMethod) != *(slotMethod))
                continue;
            // соединение уже существует
            return false;
        }
    }
    sender.AddConnection(std::move(signalMethod), &receiver, std::move(slotMethod), type);
    return true;
}

//-----------------------------------------------------------------------------
// сигнал и слот метод ptr
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool PrivateDisconnect(const Sender& sender, void (SignalClass::*inSignalMethod)(SignalArgs...), const Receiver& receiver,
    SlotReturn(SlotClass::*inSlotMethod)(SlotArgs...))
{
    // Отправитель должен быть тем же классом, что и SignalClass, а Sender - дочерним элементом SignalClass
    Internal::vsn_TestConnectSenderSignal<Sender, SignalClass>();

    // Приемник должен быть того же класса, что и SlotClass, а Receiver - дочерний элемент SlotClass
    Internal::vsn_TestConnectReceiverSlot<SlotClass, Receiver>();

    // аргументы сигнала и слота не согласованы
    Internal::vsn_TestConnectSignalSlotArgs_2< void(*)(SignalArgs...), void(*)(SlotArgs...) >();

    Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)> signalMethod(inSignalMethod);
    Internal::StorageFunction<void (SlotClass::*)(SlotArgs...)> slotMethod(inSlotMethod);
    return PrivateDisconnect(sender, &signalMethod, &receiver, &slotMethod);
}

//-----------------------------------------------------------------------------
// сигнальный метод ptr, slot лямбда или функция ptr
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool PrivateDisconnect(const Sender& sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver &receiver, T slotMethod)
{
    // lambda, ошибка компиляции
    //    static_assert(std::is_convertible<decltype*slotMethod == slotMethod), bool>::value, "disconnect():  Недопустимый аргумент слота или вызов разъединения с помощью лямбда");
    // функция ptr
    Internal::StorageFunction<void (SignalClass::*)(SignalArgs...)> signalMethodStorage(signalMethod);
    Internal::StorageFunction<T> slotMethodStorage(slotMethod);
    if (!PrivateDisconnect(sender, &signalMethodStorage, &receiver, &slotMethodStorage))
        return false;
    return true;
}

//-----------------------------------------------------------------------------
// сигнальные и слотовые объекты
// ---
template<class Sender, class Receiver>
bool PrivateDisconnect(const Sender& sender, const Internal::AbsStorageFunction* pStorageSignal, const Receiver* pReceiver, const Internal::AbsStorageFunction* pStorageSlot)
{
    bool retval = false;
    bool isDone = false;
    MutexLocker senderLock { &sender.m_mutexConnectList };
    MutexLocker receiverLock;

    if (pReceiver != nullptr)
        receiverLock = MutexLocker { &pReceiver->m_mutexPossibleSenders };

    for (int k = 0; k < static_cast<int>(sender.m_connectList.size()); ++k)
    {
        BasicObject::ConnectData &temp = sender.m_connectList[k];
        if (temp.type == ConnectionInner::InternalDisconnected)
            continue; // отмеченные, как отключенные

        bool bIsCoincidence = false;
        if (pStorageSignal == nullptr && pReceiver == nullptr)
        {
            bIsCoincidence = true; // удалить все соединения в Sender
        }
        else if (pReceiver != nullptr)
        {
            if (pReceiver == temp.pReceiver)
            {
                if (pStorageSignal == nullptr && (pStorageSlot == nullptr || *pStorageSlot == *temp.slotMethod))
                    bIsCoincidence = true;
                else if (pStorageSignal != nullptr && *pStorageSignal == *temp.signalMethod && (pStorageSlot == nullptr || *pStorageSlot == *temp.slotMethod))
                    bIsCoincidence = true;
            }

        }
        else if (pStorageSignal != nullptr)
        {
            // приемник должен быть пустым, поэтому слот равен null
            if (*pStorageSignal == *temp.signalMethod)
                bIsCoincidence = true;
        }

        if (bIsCoincidence)
        {
            // удалить возможного отправителя в приемнике
            retval = true;
            if (pReceiver == nullptr)
            {
                // нет приемника, блокировка temp.pReceiver сейчас
                receiverLock = MutexLocker { &temp.pReceiver->m_mutexPossibleSenders };
                auto &senderList = temp.pReceiver->m_possibleSenders;
                senderList.erase(std::find(senderList.rbegin(), senderList.rend(), &sender).base() - 1);
                receiverLock.Unlock();
            }
            else
            {
                auto& senderList = temp.pReceiver->m_possibleSenders;
                senderList.erase(std::find(senderList.rbegin(), senderList.rend(), &sender).base() - 1);
            }

            if (sender.m_activateBusy != 0)
            {
                if (!isDone)
                {
                    // activate() изменился список подключений
                    sender.m_raceCount++;
                    isDone = true;
                }
                // отметьте соединение для удаления, activate () завершит очистку
                temp.type = ConnectionInner::InternalDisconnected;
            }
            else
            {
                // удалить соединение в отправителе
                sender.m_connectList.erase(sender.m_connectList.begin() + k);
                // да, это необходимо
                k = k - 1;
            }
        }
    }
    return retval;
}

VSN_END_NAMESPACE

#endif // __VSN_BASICOBJECT_H
