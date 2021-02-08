////////////////////////////////////////////////////////////////////////////////
/**
  \file 
  \brief \ru Класс Object является базовым классом для всех объектов сцены.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_OBJECTDEFS_H
#define __VSN_OBJECTDEFS_H

#include <typeindex>
#include <unordered_map>
#include <atomic>
#include "vsn_global.h"
#include <iostream>

#ifndef VSN_PRINTABLE
#  define VSN_PRINTABLE(str)  String(str)
#endif

#define VSN_DEF_VALUE_ZERO              0
#define VSN_DEF_VALUE_NUMBER            255
#define VSN_SYMBOL_INSERT1(a,b)         a ## b
#define VSN_SYMBOL_INSERT2(a,b)         VSN_SYMBOL_INSERT1(a,b)

template<int Num> struct VSN_VALUE_NUMBER : public VSN_VALUE_NUMBER<Num - 1> { static const int value = Num; };
template<> struct VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO> { static const int value = VSN_DEF_VALUE_ZERO; };

// ** расшифровать тип возвращаемого метода
template<class T>
struct vsn_returnType;

template<class T, class R>
struct vsn_returnType<R(T::*)() const> { using type = R; };

template<class T>
struct vsn_argType;

template<class T, class R, class Val>
struct vsn_argType<R(T::*)(Val)> { using type = Val; };


#define V_STATIC_META_OBJECT_IMPL(class_name) \
    static const VSN::TMetaObjectImpl<class_name>& GetStaticMetaObject() \
    { \
        static std::shared_ptr<VSN::TMetaObjectImpl<class_name>> createdMetaObject(nullptr); \
        if (createdMetaObject) \
            return *createdMetaObject.get(); \
        /*first mutex*/\
        VSN::MutexLocker lock(&m_metaObjectMutex()); \
        /*if (std::atomic_load(&createdMetaObject)) \
        { \
            return *createdMetaObject.get(); \
        } */\
        static VSN::Mutex secondMutex; \
        VSN::MutexLocker secondLock(&secondMutex);\
        if (createdMetaObject) \
            return *createdMetaObject.get(); \
        std::unordered_map<std::type_index, VSN::MetaObject*>& metaMap = GetMetaObjectsMap(); \
        std::unordered_map<std::type_index, VSN::MetaObject*>::iterator it = metaMap.find(typeid(vsn_class)); \
        VSN::TMetaObjectImpl<class_name>* pNewMeta = nullptr; \
        if (it == metaMap.end()) \
        { \
            pNewMeta = new VSN::TMetaObjectImpl<class_name>();  \
            metaMap[std::type_index(typeid(vsn_class))] = pNewMeta; \
            /*std::atomic_store(&createdMetaObject, std::shared_ptr<VSN::TMetaObjectImpl<class_name>>(pNewMeta)); */\
            createdMetaObject.reset( pNewMeta );\
            pNewMeta->PostBuild(); \
            return *pNewMeta; \
        } \
        else \
        { \
            pNewMeta = dynamic_cast<VSN::TMetaObjectImpl<class_name> *> (it->second); \
            /*std::atomic_store(&createdMetaObject, std::shared_ptr<VSN::TMetaObjectImpl<class_name>>(pNewMeta));*/ \
            createdMetaObject.reset( pNewMeta );\
            return *pNewMeta; \
        } \
    } \

// vsn_object
#define VSN_OBJECT_BASE(class_name) \
   public: \
      static const char* vsn_className() { return #class_name; } \
      template<int Num> static void vsn_Overload(VSN_VALUE_NUMBER<Num>) {} \
      static const VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO> VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO>)   \
      { \
         return VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO>{};   \
      } \
      friend VSN::TMetaObjectImpl<class_name>; \
      V_STATIC_META_OBJECT_IMPL(class_name) \
      virtual const VSN::MetaObject* GetMetaObject() const  \
      { \
         return &GetStaticMetaObject(); \
      } \
    private: \
      static const char* vsn_classname() \
      { \
         static const char* value = #class_name; \
         return value; \
      } \

#define VSN_OBJECT(class_name) \
   public: \
      typedef vsn_class vsn_parent; \
      typedef class_name vsn_class; \
      VSN_OBJECT_BASE(class_name) \
   private:


// SIGNAL
#define VSIGNAL(...) \
   #__VA_ARGS__

// SLOT
#define VSLOT(...) \
   #__VA_ARGS__

// enum
#define VSN_ENUM(name) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>        \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)    \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) +1 >{};         \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
      {  \
         vsn_namespace_register_enum<vsn_class>(#name, typeid(name), vsn_classname());  \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
      }

// properties
#define VSN_PROPERTY_READ(name, method) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>        \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)    \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{}; \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
      {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject())   \
            .BindPropRead(#name, vsn_GetTypeName< vsn_returnType<decltype(&vsn_class::method)>::type> (),  \
            std::make_shared<ShadeRead<vsn_class, vsn_returnType< decltype(&vsn_class::method) >::type>> (&vsn_class::method));  \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
      }


#define VSN_PROPERTY_WRITE(name, method) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>        \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)    \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{}; \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
      {  \
          const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()) \
            .BindPropWrite(#name, std::make_shared<ShadeWrite<vsn_class, \
            vsn_argType< decltype(&vsn_class::method) >::type>> (&vsn_class::method));  \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
      }

#define VSN_PROPERTY_READ_WRITE(name, rMethod, wMethod) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1> \
    VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
    {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{}; \
    }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
    {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject())   \
            .BindPropRead(#name, vsn_GetTypeName< vsn_returnType<decltype(&vsn_class::rMethod)>::type> (),  \
            std::make_shared<ShadeRead<vsn_class, vsn_returnType< decltype(&vsn_class::rMethod) >::type>> (&vsn_class::rMethod));  \
       \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()) \
            .BindPropWrite(#name, std::make_shared<ShadeWrite<vsn_class, \
            vsn_argType< decltype(&vsn_class::wMethod) >::type>> (&vsn_class::wMethod));  \
       \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
    }


#define VSN_PROPERTY_NOTIFY(name, method) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>        \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)    \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) +1 >{};         \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
      {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindPropNotify(#name, &vsn_class::method); \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
      }


#define VSN_PROPERTY_READ_NOTIFY(name, rMethod, nMethod) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1> \
    VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
   {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{}; \
   }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
   {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject())   \
            .BindPropRead(#name, vsn_GetTypeName< vsn_returnType<decltype(&vsn_class::rMethod)>::type> (),  \
            std::make_shared<ShadeRead<vsn_class, vsn_returnType< decltype(&vsn_class::rMethod) >::type>> (&vsn_class::rMethod));  \
       \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindPropNotify(#name, &vsn_class::nMethod); \
       \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
    }


#define VSN_PROPERTY_READ_WRITE_NOTIFY(name, rMethod, wMethod, nMethod) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1> \
    VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
   {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{}; \
   }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>)  \
   {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject())   \
            .BindPropRead(#name, vsn_GetTypeName< vsn_returnType<decltype(&vsn_class::rMethod)>::type> (),  \
            std::make_shared<ShadeRead<vsn_class, vsn_returnType< decltype(&vsn_class::rMethod) >::type>> (&vsn_class::rMethod));  \
       \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()) \
            .BindPropWrite(#name, std::make_shared<ShadeWrite<vsn_class, \
            vsn_argType< decltype(&vsn_class::wMethod) >::type>> (&vsn_class::wMethod));  \
       \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindPropNotify(#name, &vsn_class::nMethod); \
       \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
    }

// invoke
#define VSN_INVOKABLE_METHOD_1(access, ...) \
   __VA_ARGS__; \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype( VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}) )::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>  \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
            {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1 >{};      \
            }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
            {  \
         const char* va_args = #__VA_ARGS__;    \
         MetaMethod::AccessType accessType = MetaMethod::access; \
         const int cntValue = VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__);



#define VSN_INVOKABLE_METHOD_2(methodName) \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethod(  \
            #methodName, &vsn_class::methodName, MetaMethod::Method, va_args, accessType); \
         \
         vsn_Overload(VSN_VALUE_NUMBER<cntValue + 1>{} );  \
            }

//  slots
#define VSN_SLOT_IMPL_1(access, ...) \
   __VA_ARGS__; \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype(VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}))::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>  \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{};      \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
      {  \
         const char* va_args = #__VA_ARGS__;    \
         MetaMethod::AccessType accessType = MetaMethod::access; \
         const int cntValue = VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__);

#define VSN_SLOT_IMPL_2(slotName) \
        const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethod(  \
        #slotName, &vsn_class::slotName, MetaMethod::Slot, va_args, accessType); \
        \
        vsn_Overload(VSN_VALUE_NUMBER<cntValue + 1>{} ); \
    }


#define VSN_SLOT_IMPL(access, memberFxn, ...) \
   __VA_ARGS__; \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype(VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}))::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>  \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
    {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{};      \
    }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
    {  \
         const char* va_args = #__VA_ARGS__;    \
         MetaMethod::AccessType accessType = MetaMethod::access; \
         const int cntValue = VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__); \
    const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethod( \
            #memberFxn, &vsn_class::memberFxn, MetaMethod::Slot, va_args, accessType); \
        \
        vsn_Overload(VSN_VALUE_NUMBER<cntValue + 1>{}); \
    } \



// signals
#define VSN_SIGNAL_IMPL_1(access, ...) \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype(VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}))::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>  \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)   \
      {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{};        \
      }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
      {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethodBegin(  \
            #__VA_ARGS__, MetaMethod::access, MetaMethod::Signal);  \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
      }  \
    __VA_ARGS__ {   \
      if (this->IsSignalsBlocked()) { \
         return; \
      }


#define VSN_SIGNAL_IMPL_2(signalName, ...) \
      PrivateTrigger(*this, &vsn_class::signalName, ##__VA_ARGS__); \
      }  \
   static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
            decltype(VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}))::value; \
   static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>     \
            VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>) \
            {  \
         return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) +1 >{};      \
            }  \
   static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
            {  \
         const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethodEnd(  \
            #signalName, &vsn_class::signalName, MetaMethod::Signal);   \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
            }  \


#define VSN_SIGNAL_IMPL(accessType, memberFxn, prototypeFxn, ...) \
    static constexpr int VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) =  \
        decltype(VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_DEF_VALUE_NUMBER>{}))::value; \
    static constexpr VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>  \
    VSN_NUM_COUNTER(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>)   \
    {  \
        return VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{};        \
    }  \
    static void vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__)>) \
    {  \
        const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethodBegin(  \
            #prototypeFxn, MetaMethod::accessType, MetaMethod::Signal);  \
    \
        vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
        const_cast<VSN::TMetaObjectImpl<vsn_class>&>(vsn_class::GetStaticMetaObject()).BindMethodEnd(  \
            #memberFxn, &vsn_class::memberFxn, MetaMethod::Signal);   \
         \
         vsn_Overload(VSN_VALUE_NUMBER<VSN_SYMBOL_INSERT2(VSN_NUM_VALUE_COUNTER, __LINE__) + 1>{} ); \
    }  \
    prototypeFxn { \
        if (this->IsSignalsBlocked()) { \
            return; \
        } \
        PrivateTrigger(#memberFxn, *this, &vsn_class::memberFxn, ##__VA_ARGS__); \
    }  \



#define VSN_SLOT_1(access, ...)                                    VSN_SLOT_IMPL_1(access, __VA_ARGS__)
#define VSN_SLOT_2(slotName)                                       VSN_SLOT_IMPL_2(slotName)
#define VSN_SLOT(access, slotName, ...)                               VSN_SLOT_IMPL(access, slotName, __VA_ARGS__)

#define VSN_SIGNAL_1(access, ...)                                  VSN_SIGNAL_IMPL_1(access, __VA_ARGS__)
#define VSN_SIGNAL_2(signalName, ...)                              VSN_SIGNAL_IMPL_2(signalName, ## __VA_ARGS__)
#define VSN_SIGNAL(access, memberFxn, prototypeFxn, ...)           VSN_SIGNAL_IMPL(access, memberFxn, prototypeFxn, ## __VA_ARGS__)


#define VSN_DECLARE_INVOKABLE_METHOD_1(access, ...)                VSN_INVOKABLE_METHOD_1(access, __VA_ARGS__)
#define VSN_DECLARE_INVOKABLE_METHOD_2(methodName)                 VSN_INVOKABLE_METHOD_2(methodName)

#define VSN_PROP_READ(name, method)                                   VSN_PROPERTY_READ(name, method)
#define VSN_PROP_WRITE(name, method)                               VSN_PROPERTY_WRITE(name, method)
#define VSN_PROP_NOTIFY(name, method)                              VSN_PROPERTY_NOTIFY(name, method)

#define VSN_PROP_READ_NOTIFY(name, rMethod, nMethod)                 VSN_PROPERTY_READ_NOTIFY(name, rMethod, nMethod)
#define VSN_PROP_READ_WRITE(name, rMethod, wMethod)                  VSN_PROPERTY_READ_WRITE(name, rMethod, wMethod)
#define VSN_PROP_READ_WRITE_NOTIFY(name, rMethod, wMethod, nMethod) VSN_PROPERTY_READ_WRITE_NOTIFY(name, rMethod, wMethod, nMethod)


#endif // __VSN_OBJECTDEFS_H

