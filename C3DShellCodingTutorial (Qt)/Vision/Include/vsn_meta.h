////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_META_H
#define __VSN_META_H

#include "vsn_metainternal.h"
#include "vsn_string.h"
#include "vsn_flags.h"
#include <utility>
#include <tuple>
#include <list>
#include "vsn_global.h"


class MbMatrix;
class MbMatrix3D;
class MbCartPoint;
class MbCartPoint3D;

VSN_BEGIN_NAMESPACE

/* MetaEnum */
class VSN_CLASS MetaEnum
{
public:
    MetaEnum();
    MetaEnum(const char *name, const char *scope, bool isFlag);
public:
    bool IsFlag() const;
    bool IsValid() const;

    const char* GetKey(int index) const;
    int GetKeyCount() const;
    int GetKeyToValue(const char *key) const;
    int GetKeysToValue(const char *keys) const;

    const char* GetName() const;
    const char* GetScope() const;

    void SetData(std::map<String, int> valueMap);

    int GetValue(int index) const;
    const char* GetValueToKey(int value) const;
    String GetValueToKeys(int value) const;

private:
    const char* m_name;
    const char* m_scope;
    bool m_flag;
    std::map<String, int> m_data;
};

class AbsStorage;
class MetaObject;
class MetaMethodPrivate;
/* MetaMethod */
class VSN_CLASS MetaMethod
{
public:
    enum AccessType { Private, Protected, Public };
    enum MethodType { Method, Signal, Slot, Constructor };
    enum Attributes { Compatibility = 0x1, Cloned = 0x2, Scriptable = 0x4 };   // internal
public:
    MetaMethod(const String& typeName, const String& signature, std::list<String> paramNames,
        AccessType access, MethodType methodType, Attributes attrs, MetaObject* pObj);
    MetaMethod();
    MetaMethod(const MetaMethod& other);
    ~MetaMethod();
public:
    AccessType GetAccessType() const;
    Attributes GetAttributes() const;

    bool IsCompare(const Internal::AbsStorageFunction& method) const;
    const AbsStorage* GetStorage() const;

    const MetaObject* GetMetaObject() const;

    String GetName() const;

    int GetMethodIndex() const;
    MethodType GetMethodType() const;

    std::list<String> GetParameterNames() const;
    std::list<String> GetParameterTypes() const;

    int GetParameterCount() const;
    int GetParameterType(int index) const;

    String MethodSignature() const;
    const char* GetTypeName() const;

    int GetRevision() const;
    void SetRevision(int revision);

    void SetStorage(std::shared_ptr<const AbsStorage> pMethod);
    void SetTag(const String& data);
    String GetTag() const;
    MetaMethod& operator =(const MetaMethod& other);
private:
    friend bool operator==(const MetaMethod &m1, const MetaMethod &m2);
    friend bool operator!=(const MetaMethod &m1, const MetaMethod &m2);
    VSN_DECLARE_PRIVATE(MetaMethod);
};

class Object;
class AbsReadBase;
class AbsWriteBase;
class AbsResetBase;
class MetaPropertyPrivate;
/* MetaProperty */
class VSN_CLASS MetaProperty
{
public:
    enum PropType
    {
        READ, WRITE, RESET, NOTIFY, REVISION, DESIGNABLE, SCRIPTABLE,
        STORED, USER, CONSTANT, FINAL
    };
    MetaProperty(const char* name = 0, MetaObject* pObject = nullptr);
    MetaProperty(const MetaProperty& other);
    virtual ~MetaProperty();
public:
    bool IsReadable() const;
    bool IsWritable() const;
    bool IsResettable() const;
    bool IsDesignable(const Object* pObject = nullptr) const;
    bool IsScriptable(const Object* pObject = nullptr) const;
    bool IsStored(const Object* pObject = nullptr) const;
    bool IsUser(const Object* pObject = nullptr) const;
    bool IsConstant() const;
    bool IsFinal() const;
    bool IsValid() const;
    bool IsFlagType() const;
    bool IsEnumType() const;

    MetaEnum GetEnumerator() const;

    bool HasNotifySignal() const;
    bool HasStdCppSet() const;

    const char* GetName() const;
    MetaMethod GetNotifySignal() const;
    int GetNotifySignalIndex() const;
    int GetPropertyIndex() const;

    Variant Read(const Object* pObject) const;

    //template<class T>
    //T Read(const Object* pObject) const;

    bool Reset(Object* pObject) const;
    const char* GetTypeName() const;
    VariantType GetType() const;
    int UserType() const;
    bool Write(Object* pObject, const Variant& value) const;

    // properties
    void SetWriteMethod(std::shared_ptr<AbsWriteBase> ptrMethod);

    //template<class T>
    //void SetNotifyMethod(T method);

    //template<class T>
    //void SetResetMethod(void (T::*method)());

    void SetDesignable(AbsReadBase* pMethod);
    void SetScriptable(AbsReadBase* pMethod);
    void SetStored(AbsReadBase* pMethod);
    void SetUser(AbsReadBase* pMethod);

    MetaProperty& operator =(const MetaProperty& other);
private:
    VSN_DECLARE_PRIVATE(MetaProperty);
};

// vsn_TypeNameInternal это шаблонный класс
template <class T, class = void>
class vsn_TypeNameInternal
{
public:
    static const char* GetTypeName() { return nullptr; }
};

// vsn_TypeNameInternal<dataType,void>::typeName является методом относящимся к специализации шаблонного класса
#define VSN_REGISTER_CLASS(dataType) \
   VSN_FUNC_EX const char* vsn_TypeNameInternal<dataType, void>::GetTypeName() \
   { return #dataType; } \

// vsn_TypeNameInternal<dataType> является специализацией шаблонного класса
#define VSN_DECLARE_OUTERCLASS(dataType) \
    template <>  \
    class vsn_TypeNameInternal<dataType, void>  \
    { \
       public: \
          VSN_FUNC_EX static const char* GetTypeName(); \
    };

#define VSN_DECLARE_CLASS(dataType) \
   class dataType; \
   VSN_DECLARE_OUTERCLASS(dataType)


#define VSN_REGISTER_TYPE(dataType) \
   template <>  \
   VSN_FUNC_EX const char* vsn_TypeNameInternal<dataType,void>::GetTypeName() \
   { \
      return #dataType; \
   } \
   template const char* vsn_TypeNameInternal<dataType,void>::GetTypeName();


#define VSN_REGISTER_TEMPLATE(dataType) \
   template<class... Ts> \
   class vsn_TypeNameInternal< dataType<Ts...> >  \
   { \
      public:  \
         static const char* GetTypeName();  \
   };  \
   template<class... Ts> \
   const char * vsn_TypeNameInternal< dataType<Ts...> >::GetTypeName() \
   { \
      static String temp = String(#dataType) + "<" + vsn_GetTypeName<Ts...>() + ">";  \
      return temp.c_str(); \
   }

// методы для этих 2 классов, расположенные в vsn_meta_internal2.h вокруг строки 117
template<class E>
class vsn_TypeNameInternal<E, typename std::enable_if<std::is_enum<E>::value>::type>
{
public:
    static const char* GetTypeName();
};

template<class E>
class vsn_TypeNameInternal< Flags<E> >
{
public:
    static const char* GetTypeName();
};

/*
// Объект и дети
template<class T>
class vsn_TypeNameInternal<T, typename std::enable_if< std::is_base_of< MetaObject, typename std::remove_reference< decltype(T::GetStaticMetaObject()) >::type >::value>::type >
{
public:
static const char* GetTypeName();
};

template<class T>
inline const char *vsn_TypeNameInternal<T, typename std::enable_if< std::is_base_of< MetaObject, typename std::remove_reference< decltype(T::GetStaticMetaObject())>::type >::value>::type >::GetTypeName()
{
return T::GetStaticMetaObject().className();
}
*/

// 1 стандартные функции шаблона
class vsn_internalEmpty;

template<class T1 = vsn_internalEmpty>
const char* vsn_GetTypeName()
{
    if (std::is_same<T1, vsn_internalEmpty>::value)
        return "";
    else
    {
        static String temp = String(vsn_TypeNameInternal<T1>::GetTypeName());
        return temp.c_str();
    }
}

template<class T1, class T2, class ...Ts>
const char* vsn_GetTypeName()
{
    static String temp = String(vsn_TypeNameInternal<T1>::GetTypeName()) + "," + vsn_GetTypeName<T2, Ts...>();
    return temp.c_str();
}


// 2 специализация для указателей - классы шаблонов
template<class T>
class vsn_TypeNameInternal<T *>
{
public:
    static const char* GetTypeName();
};

template<class T>
const char *vsn_TypeNameInternal<T *>::GetTypeName()
{
    static String temp = String(vsn_GetTypeName<T>()) + "*";
    return temp.c_str();
}


// 3 специализация для константных указателей - классы шаблонов
template<class T>
class vsn_TypeNameInternal<const T *>
{
public:
    static const char* GetTypeName();
};

template<class T>
const char* vsn_TypeNameInternal<const T *>::GetTypeName()
{
    static String temp = "const " + String(vsn_GetTypeName<T>()) + "*";
    return temp.c_str();
}

// 4  специализация для ссылок - классы шаблонов
template<class T>
class vsn_TypeNameInternal<T &>
{
public:
    static const char* GetTypeName();
};

template<class T>
const char* vsn_TypeNameInternal<T &>::GetTypeName()
{
    static String temp = String(vsn_GetTypeName<T>()) + "&";
    return temp.c_str();
}

// 5  специализация для ссылок const (классы шаблона)
template<class T>
class vsn_TypeNameInternal<const T &>
{
public:
    static const char* GetTypeName();
};

template<class T>
const char *vsn_TypeNameInternal<const T &>::GetTypeName()
{
    static String temp = "const " + String(vsn_GetTypeName<T>()) + "&";
    return temp.c_str();
}

// заявить здесь, зарегистрироваться in vsn_object_private.cpp
VSN_DECLARE_CLASS(Size)
VSN_DECLARE_CLASS(Color)
VSN_DECLARE_CLASS(String)
VSN_DECLARE_CLASS(Object)

/**
template<class T>
T MetaProperty::Read(const Object* object) const
{
    if (!object || !m_readBase)
        throw std::logic_error("MetaProperty::read() Объект равен null");
    return m_readBase->run<T>(object);
}

template<class T>
void MetaProperty::SetNotifyMethod(T method)
{
    if (!method)
        return;
    m_notifyStorage = new StorageImpl<T>(method);
    m_notifyState = true;
}

template<class T>
void MetaProperty::SetResetMethod(void (T::*method)())
{
    if (!method)
        return;
    m_resetBase = new ShadeReset<T>(method);
    m_resetState = true;
}*/

VSN_DECLARE_OUTERCLASS(MbMatrix)
VSN_DECLARE_OUTERCLASS(MbMatrix3D)
VSN_DECLARE_OUTERCLASS(MbCartPoint)
VSN_DECLARE_OUTERCLASS(MbCartPoint3D)

VSN_END_NAMESPACE

#endif // __VSN_META_H
