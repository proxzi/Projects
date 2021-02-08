////////////////////////////////////////////////////////////////////////////////
/**
  \file 
  \brief \ru Класс Object является базовым классом для всех объектов сцены.
         \en Object class is the base class for all scene objects. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_OBJECT_H
#define __VSN_OBJECT_H

#include "vsn_basicobject.h"
#include "vsn_objectdefs.h"
#include "vsn_metaobject.h"
#include "vsn_namespace.h"
#include "vsn_mutex.h"

VSN_BEGIN_NAMESPACE

#ifndef VSN_NO_EMIT
#define emit
#endif

// ---
VSN_FUNC(Object*) vsnFindChild(const Object* pParent, const String& objName, const MetaObject& mObject, VSN::ChildFindingPolicies policies);
VSN_FUNC(void) vsnFindChildren(const Object* pParent, const String& objName, const MetaObject& mObject, std::vector<void*>* pVec, VSN::ChildFindingPolicies policies);


class Thread;
class ProcessEvent;
class ObjectPrivate;
class Mutex;
//------------------------------------------------------------------------------
/** \brief \ru Класс Object является базовым классом для всех объектов сцены.
           \en Object class is the base class for all scene objects. \~
    \ingroup Vision_Base
*/
// ---
class VSN_CLASS Object : public BasicObject
{
protected:
    typedef Object vsn_class;
private:
    VSN_OBJECT_BASE(Object);
    VSN_PROPERTY_READ(objectName, GetObjectName);
    VSN_PROPERTY_WRITE(objectName, SetObjectName);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Object(const String& name = String());
    /// \ru Конструктор c родителем. \en Constructor with parent. \~
    Object(Object* pParent);
    /// \ru Деструктор. \en Destructor.
    virtual ~Object();
public:
    /// \ru Установить родителя для объекта. \en NO TRANSLATION. \~
    void SetParent(Object* pParent);
    /// \ru Мьютекс объекта. \en Object mutex. \~
    Mutex* GetMutex();
    /// \ru Получить имя объекта. \en Returns name. \~
    String GetObjectName() const;
    /// \ru Установить имя объекту. \en Sets name. \~
    void SetObjectName(const String& name);
    /// \ru Вернуть тип объекта. \en TRANSLATION. \~
    bool IsControlType() const;
    /// \ru Вернуть указатель на родителя. \en NO TRANSLATION. \~
    Object* GetParent() const;
    /// \ru Вернуть вариант свойства по имени. \en NO TRANSLATION. \~
    Variant GetProperty(const char* name) const;

    bool Connect(const Object* sender, const char* signalMethod, const char* location, const char* slotMethod, ConnectionType type = AutoConnection);
    static bool Connect(const Object* sender, const char* signalMethod, const char* location, const Object* receiver, const char* slotMethod, ConnectionType type = AutoConnection);
    static bool Connect(const Object* sender, const char* signalMethod, const Object* receiver, const char* slotMethod, ConnectionType type = AutoConnection, const char* location = nullptr);
    static bool Connect(const Object* sender, const MetaMethod& signalMethod, const Object* receiver, const MetaMethod& slotMethod, ConnectionType type = AutoConnection);
    bool Connect(const Object* sender, const char* signalMethod, const char* slotMethod, ConnectionType type = AutoConnection);

    static bool Disconnect(const Object* sender, const char* signalMethod, const Object *receiver, const char* slotMethod);
    static bool Disconnect(const Object* sender, const MetaMethod& signalMethod, const Object* receiver, const MetaMethod& slotMethod);
    static bool Disconnect(const Object* sender, const char* signalMethod, const char* location, const Object* receiver, const char* slotMethod);
    static bool Disconnect(const Object* sender, int signal_index, const Object* receiver, int method_index);
    bool Disconnect(const char* signalMethod = nullptr, const Object* receiver = nullptr, const char *slotMethod = nullptr) const;
    bool Disconnect(const char* signalMethod, const char* lineNumber, const Object* receiver = nullptr, const char *slotMethod = nullptr) const;
    bool Disconnect(const Object* receiver, const char* slotMethod = nullptr) const;

    // signal/slot method ptr
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
    static bool Connect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, SlotReturn(SlotClass::*slotMethod)(SlotArgs...), ConnectionType type = AutoConnection);
    // функция ptr или лямбда
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
    static bool Connect(const Sender *sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, T slot, ConnectionType type = AutoConnection);
    // signal/slot method ptr
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
    static bool Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver *receiver, SlotReturn(SlotClass::*slotMethod)(SlotArgs...));
    // функция ptr или лямбда
    template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
    static bool Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver *receiver, T slot);

    /// \ru Вернуть признак блокировки сигналов этого объекта. \en NO TRANSLATION. \~
    bool IsSignalsBlocked() const;
    /// \ru Установить признак блокировки сигналов этого объекта. \en NO TRANSLATION. \~
    bool SetBlockSignals(bool bBlock);

    /// \ru Добавить слушателя событий. \en NO TRANSLATION. \~
    void AddEventListener(Object* obj);
    /// \ru Удалить слушателя событий. \en NO TRANSLATION. \~
    void RemoveEventListener(Object* obj);
    /// \ru Вернуть указатель на объект, который с генерировал сигнал. \en NO TRANSLATION. \~
    Object* GetSender() const;
public:
    VSN_SIGNAL(Public, ObjectNameModified, void ObjectNameModified(const String& objectName), objectName)
    VSN_SIGNAL(Public, Destroyed, void Destroyed(Object* object = nullptr), object)
    VSN_SLOT  (Public, DeferredDelete, void DeferredDelete())
public:
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    Thread* GetThread() const;
    /// \ru Связывание c потоком. \en NO TRANSLATION. \~
    void BindWithThread(Thread* thread);
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    int StartTimer(int interval, TimerType timerType = tt_CoarseTimer);
    /// \ru NO TRANSLATION. \en NO TRANSLATION. \~
    void KillTimer(int id);
    /// \ru Вернуть список указателей детей. \en NO TRANSLATION.
    const std::vector<Object*>& GetChildren() const;
    /// \ru Вернуть указателей на ребенка. \en NO TRANSLATION.
    template<typename T>
    inline T FindChild(const String& objName = String(), VSN::ChildFindingPolicies policies = VSN::FindAllNestedChildren) const;
    /// \ru Вернуть список указателей детей. \en NO TRANSLATION.
    template<typename T>
    inline std::vector<T> FindChildren(const String& objName = String(), VSN::ChildFindingPolicies policies = VSN::FindAllNestedChildren) const;
public:
    virtual bool OnEvent(ProcessEvent* event);
    virtual bool OnEventFilter(Object* object, ProcessEvent* event);
protected:
    virtual void OnCustomEvent(ProcessEvent* event);
protected:
    static std::unordered_map<std::type_index, MetaObject *>& GetMetaObjectsMap();
    static Mutex& m_metaObjectMutex();
protected:
    virtual void OnConnectNotify(const char* pSignal) const;
    virtual void OnDisconnectNotify(const char* pSignal) const;
    virtual void OnConnectNotify(const MetaMethod& signalMethod) const;
    virtual void OnDisconnectNotify(const MetaMethod& signal) const;
protected:
    Object(ObjectPrivate& d, Object* pParent = nullptr);
protected:
    friend class MetaObject;
    friend class ThreadData;
    friend class BaseApplication;
    friend class BaseApplicationPrivate;
    friend class ApplicationPrivate;
    friend class Application;
    VSN_DECLARE_PRIVATE(Object);
};

// ---
template<typename T>
inline T Object::FindChild(const String& objName, VSN::ChildFindingPolicies policies) const
{
    typedef typename Internal::remove_const_volatile<typename Internal::remove_pointer<T>::type>::type ObjType;
    return static_cast<T>(vsnFindChild(this, objName, ObjType::GetStaticMetaObject(), policies));
}
// ---
template<typename T>
inline std::vector<T> Object::FindChildren(const String& objName, VSN::ChildFindingPolicies policies) const
{
    typedef typename Internal::remove_const_volatile<typename Internal::remove_pointer<T>::type>::type ObjType;
    std::vector<T> vec;
    vsnFindChildren(this, objName, ObjType::GetStaticMetaObject(), reinterpret_cast<std::vector<void *> *>(&vec), policies);
    return vec;
}

// ---
template <class T>
inline T vobject_cast(Object* object) { return dynamic_cast<T>(object); }
// ---
template <class T>
inline T vobject_cast(const Object* object) { return dynamic_cast<T>(object); }
// ---
template <class T>
inline const char* vobject_interface_iid() { return 0; }

#include "vsn_objectinternal.h"

VSN_END_NAMESPACE

#endif // __VSN_OBJECT_H
