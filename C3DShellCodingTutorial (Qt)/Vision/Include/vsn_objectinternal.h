#ifndef __VSN_OBJECT_INTERNAL_H
#define __VSN_OBJECT_INTERNAL_H

//#include "vsn_bugcheck.h"

//-----------------------------------------------------------------------------
// signal & slot method ptr
// ---
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool Object::Connect(const Sender* pSender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, SlotReturn (SlotClass::*slotMethod)(SlotArgs...), ConnectionType type)
{      
   if (pSender == nullptr)
   {
      vsnWarning("Object::Connect() Can not connect, because sender is null.");
      return false;
   }

   if (receiver == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, receiver is null");
      return false;
   }

   if (signalMethod == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, signal is null");
      return false;
   }

   if (slotMethod == nullptr) 
   {
      vsnWarning("Object::Connect() Can not connect, slot is null");
      return false;
   }
   
   // получить сигнал MetaMethod
   const MetaObject* pSenderMetaObject = pSender->GetMetaObject();
   MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);

   const char* pSenderClass = pSenderMetaObject->GetMetaClassName();

   String signature = signalMetaMethod.MethodSignature();
   const char* signalName = signature.c_str();

   if (signature.IsEmpty())  
   {
//      vsn_Warning("%s%s%s", "Object::connect() ", pSenderClass, "::<Invalid Signal> ");
      return false;
   }

   // является ли signalMethod сигналом
   if (signalMetaMethod.GetMethodType() != MetaMethod::Signal ) 
   {
//      vsn_Warning("%s%s%s%s%s", "Object::connect() ", pSenderClass, "::", signalName, "was not a valid signal");
      return false;
   }  

   ConnectionInner kind;
   bool uniqueConnection = false;

   if (type & UniqueConnection)
      uniqueConnection = true;

   kind = static_cast<ConnectionInner>(type & ~UniqueConnection);

   PrivateConnect(*pSender, signalMethod, *receiver, slotMethod, kind, uniqueConnection);
   pSender->OnConnectNotify(signalMetaMethod);
   return true;
}

// signal method ptr, slot lambda
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool Object::Connect(const Sender *sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* receiver, T slotLambda, ConnectionType type)
{
   static_assert(std::is_base_of<Object, Sender>::value, "Sender must inherit from Object");  
   if (sender == nullptr) 
   {
      vsnWarning("Object::connect() Can not connect, sender is null");
      return false;
   }

   if (receiver == nullptr) 
   {
      vsnWarning("Object::connect() Can not connect, receiver is null");
      return false;
   }

   if (signalMethod == nullptr) 
   {
      vsnWarning("Object::connect() Can not connect, signal is null");
      return false;
   }

   // получить сигнал MetaMethod
   const MetaObject* pSenderMetaObject = sender->GetMetaObject();
   MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);

   const char* pSenderClass = pSenderMetaObject->GetMetaClassName();

   String signature = signalMetaMethod.MethodSignature();
   const char *signalName  = signature.c_str();

   if (signature.IsEmpty())
   {
//      vsn_Warning("%s%s%s", "Object::connect() ", pSenderClass, "::<Invalid Signal> ");
      return false;
   }

   // является ли сигналом для сигнала
   if (signalMetaMethod.GetMethodType() != MetaMethod::Signal ) 
   {
//      vsn_Warning("%s%s%s%s%s", "Object::connect() ", pSenderClass, "::", signalName, "was not a valid signal");
      return false;
   }  
   
   ConnectionInner kind;
   bool uniqueConnection = false;

   if (type & UniqueConnection)
      uniqueConnection = true;

   // преобразовать тип
   kind = static_cast<ConnectionInner>(type & ~UniqueConnection);

   PrivateConnect(*sender, signalMethod, *receiver, slotLambda, kind, uniqueConnection);
   sender->OnConnectNotify(signalMetaMethod);
   return true;
}

// 
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class SlotClass, class ...SlotArgs, class SlotReturn>
bool Object::Disconnect(const Sender* pSnder, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* pReceiver, SlotReturn (SlotClass::*slotMethod)(SlotArgs...))
{
   static_assert(std::is_base_of<Object, Sender>::value, "Sender must inherit from Object");  
   if (pSnder == nullptr || (pReceiver == nullptr && slotMethod != nullptr))
   {
      vsnWarning("Object::Disconnect() Unexpected null parameter");
      return false;
   }
   bool retval = PrivateDisconnect(*pSnder, signalMethod, *pReceiver, slotMethod);
   if (retval) 
   {
      if (const MetaObject* pSenderMetaObject = pSnder->GetMetaObject())
      {
          MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);
          const_cast<Sender *>(pSnder)->OnDisconnectNotify(signalMetaMethod);
      } 
   }
   return retval;
}

// 
template<class Sender, class SignalClass, class ...SignalArgs, class Receiver, class T>
bool Object::Disconnect(const Sender* sender, void (SignalClass::*signalMethod)(SignalArgs...), const Receiver* pReceiver, T slotMethod)
{
    bool retval = PrivateDisconnect(*sender, signalMethod, *pReceiver, slotMethod);
    if (retval)
    {
        if (const MetaObject* pSenderMetaObject = sender->GetMetaObject())
        {
            MetaMethod signalMetaMethod = pSenderMetaObject->Method(signalMethod);
            const_cast<Sender *>(sender)->OnDisconnectNotify(signalMetaMethod);
        }
    }
    return retval;
}
#endif // __VSN_OBJECT_INTERNAL_H
