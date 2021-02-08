#ifndef __VSN_METAINTERNAL_H
#define __VSN_METAINTERNAL_H

#include <initializer_list>
#include <functional>
#include <memory>
#include <stdexcept>
#include <tuple>

#include "vsn_variant.h"
#include "vsn_flags.h"
#include "vsn_global.h"

#pragma warning( push )
#pragma warning( disable : 4250 )

VSN_BEGIN_NAMESPACE

class Object;
class MetaObject;

template <typename T>
struct MetaTypeId { enum { Defined = 0 }; };

template <typename T>
struct MetaTypeId2 
{
    enum { Defined = MetaTypeId<T>::Defined };
    static inline int vsn_metatype_id() {
        return MetaTypeId<T>::vsn_metatype_id();
    }
};


template<class T1>
const char* vsn_GetTypeName();

/* Argument */
template <typename T>
class Argument
{
public:
    Argument(const T& data);
    Argument(const T& data, const char* pTypeName);
public:
    T GetData() const;
    const char* GetTypeName() const;
private:
    T m_data;
    const char* m_pTypeName;
};

template <typename T>
Argument<T>::Argument(const T &data)
    : m_data(data)
    , m_pTypeName(vsn_GetTypeName<T>())
{
}

template <typename T>
Argument<T>::Argument(const T& data, const char* pTypeName)
    : m_data(data)
    , m_pTypeName(pTypeName)
{
}

template <typename T>
T Argument<T>::GetData() const
{
    return m_data;
}

template <typename T>
const char* Argument<T>::GetTypeName() const
{
    return m_pTypeName;
}

inline const char* vsn_GetArgumentName()
{
    return "";
}

template <typename T>
const char *vsn_GetArgumentName(const Argument<T> &data)
{
    return data.GetTypeName();
}

template<class T1, class T2, class ...Ts>
const char* vsn_GetArgumentName(const Argument<T1> &data1, const Argument<T2> &data2, const Argument<Ts> &... dataX)
{
    static String temp = String(vsn_GetArgumentName(data1)) + "," + vsn_GetArgumentName(data2, dataX...);
    return temp.c_str();
}

/* ArgReturnCommon */
class ArgReturnCommon
{
public:
    virtual ~ArgReturnCommon();
};

inline ArgReturnCommon::~ArgReturnCommon()
{
}

template <typename T>
class ArgReturn : public ArgReturnCommon
{
public:
    ArgReturn(T& data);
public:
    T GetData() const;
    void SetData(const T& data);
private:
    typename std::remove_const<T>::type& m_data;
};

template <typename T>
ArgReturn<T>::ArgReturn(T &data)
    : m_data(data)
{
}

template <typename T>
T ArgReturn<T>::GetData() const
{
    return m_data;
}

template <typename T>
void ArgReturn<T>::SetData(const T &data)
{
    m_data = data;
}

template <>
class ArgReturn<void> : public ArgReturnCommon
{
public:
    ArgReturn();
public:
    void SetData(Internal::VSNVoidReturn data);
};

inline ArgReturn<void>::ArgReturn()
{
}

inline void ArgReturn<void>::SetData(Internal::VSNVoidReturn)
{
}

// регистрация перечислений и флагов
template<class T>
struct IsEnumOrFlag : public std::is_enum<T> {
};

template<class T>
struct IsEnumOrFlag<Flags<T>> : public std::integral_constant<bool, true>{
};

template<class T>
struct vsn_UnderlyingType : public std::underlying_type<T> 
{
};

template<class T>
struct vsn_UnderlyingType<Flags<T>> : public std::underlying_type<T>
{
};

// Variant
template < class T, class = void, class = typename std::enable_if < !std::is_constructible<Variant, T>::value >::type >
Variant vsn_ConvertToVariant(T /*data*/)
{
    return Variant();
}

template<class T, class = typename std::enable_if<std::is_constructible<Variant, T>::value>::type>
Variant vsn_ConvertToVariant(T data)
{
    return Variant(data);
}

template < class T, class = void, class = void, class = typename std::enable_if < (!IsEnumOrFlag<T>::value) && !MetaTypeId2<T>::Defined >::type >
std::pair<T, bool> ConvertFromVariant(Variant data)
{
    // Параметр T не является перечислением, флагом или встроенным типом данных
    return std::make_pair(T{}, false);
}

template < class T, class = void, class = typename std::enable_if < (!IsEnumOrFlag<T>::value) && MetaTypeId2<T>::Defined >::type >
std::pair<T, bool> ConvertFromVariant(Variant data)
{
    // T не является перечислением, так же не флагом. T является только встроенным типом данны
    return std::make_pair(data.Get<T>(), true);
}

template<class T, class = typename std::enable_if<IsEnumOrFlag<T>::value>::type>
std::pair<T, bool> ConvertFromVariant(Variant data)
{
    // T - это перечисление или флаг
    using intType = typename vsn_UnderlyingType<T>::type;

    intType temp = 0;
    bool retval = true;

    VariantType dataType = data.GetType();

    if (dataType == VAR_INT /*|| dataType == Variant::LongLong || dataType == Variant::UInt || dataType == Variant::ULongLong*/)
    {
        // поддерживаемый целочисленные типы
        temp = data.GetInt();
    }
    else if (dataType == VAR_STRING)
    {
        _ASSERT(false);
/*
        // enum или flag
         MetaEnum obj = MetaObjectPrivate::FindEnum<T>();
         if (obj.isValid())
            temp = obj.GetKeyToValue(data.GetString().c_str());
         else
            retval = false;
*/
    }
    else
    {
        // не является строкой или цифра
        _ASSERT(false); // необходима ф-ция MetaTypeIdQuery
/*
        int enumMetaTypeId = 0;//MetaTypeIdQuery<T>();
        if ((enumMetaTypeId == 0) || (MAX_VAR_TYPES != enumMetaTypeId) || !data.GetVoidPtr())
            retval = false; // несоответствие, не удалось преобразовать
        else
            temp = *reinterpret_cast<const intType *>(data.GetVoidPtr());
*/
    }
    return std::make_pair(static_cast<T>(temp), retval);
}


/* AbsReadBase */
class AbsReadBase
{
public:
    virtual ~AbsReadBase() {}
public:
    virtual Variant runV(const Object *) const = 0;
    template<class R>
    R run(const Object *) const;
};


template<class R>
class AbsRead : public AbsReadBase
{
public:
    virtual R Call(const Object* obj) const = 0;
};


template<class T, class R>
class ShadeRead : public AbsRead<R>
{
public:
    ShadeRead(R(*func)());
    ShadeRead(R(T::*method)() const);
public:
    Variant runV(const Object* obj) const override;
    R Call(const Object* obj) const override;
private:
    R(T::*m_method)() const;
    R(*m_func)();
};

template<class R>
R AbsReadBase::run(const Object* obj) const
{
    // пользователь использовал правильный тип данных
    if (const AbsRead<R>* pCheck = dynamic_cast<const AbsRead<R> *>(this))
        return pCheck->Call(obj);
    else
        throw std::logic_error("Object::property() Несоответствия типа в чтении");
}

template<class T, class R>
ShadeRead<T, R>::ShadeRead(R(*func)())
{
    m_func = func;
    m_method = nullptr;
}

template<class T, class R>
ShadeRead<T, R>::ShadeRead(R(T::*method)() const)
{
    m_func = nullptr;
    m_method = method;
}

template<class T, class R>
Variant ShadeRead<T, R>::runV(const Object *obj) const
{
    Variant retval;

    if (m_func)
        retval = vsn_ConvertToVariant(m_func());
    else
    {
        const T* testObj = dynamic_cast< const T *>(obj);
        if (!testObj)
            return Variant();
        retval = vsn_ConvertToVariant(((testObj)->*(m_method))());
    }

    return retval;
}

template<class T, class R>
R ShadeRead<T, R>::Call(const Object *obj) const
{
    if (m_func)
    {
        return m_func();
    }
    else
    {
        // is the passed obj the correct class
        const T* testObj = dynamic_cast< const T *>(obj);
        if (!testObj)
            throw std::logic_error("Can not read a property in an object of the wrong class");
        return ((testObj)->*(m_method))();
    }
}



/* AbsWriteBase */
class AbsWriteBase
{
public:
    virtual ~AbsWriteBase() {}
    virtual bool runV(Object *, Variant data) const = 0;

    template<class V>
    bool run(const Object *, V data) const;
};

template<class V>
class AbsWrite : public AbsWriteBase
{
public:
    virtual bool call(Object *, V data) const = 0;
};

template<class T, class V>
class ShadeWrite : public AbsWrite<V>
{
public:
    ShadeWrite(void (T::*method)(V));
public:
    bool runV(Object* obj, Variant data) const override;
    bool call(Object* obj, V data) const override;
private:
    void (T::*m_method)(V);
};

template<class T, class V>
ShadeWrite<T, V>::ShadeWrite(void (T::*method)(V))
{
    m_method = method;
}

template<class T, class V>
bool ShadeWrite<T, V>::runV(Object *obj, Variant data) const
{
    T* testObj = dynamic_cast<T *>(obj);
    if (!testObj)
        return false;
    // отделим const и &, если они существуют
    using bareType = typename std::remove_const<typename std::remove_reference<V>::type>::type;
    // конвертировать данные в тип V
    std::pair<bareType, bool> retval = ConvertFromVariant<bareType>(data);
    if (retval.second)
        ((testObj)->*(m_method))(retval.first);
    return retval.second;
}

template<class T, class V>
bool ShadeWrite<T, V>::call(Object *obj, V data) const
{
    // заданный класс obj является  правильным классом
    T* testObj = dynamic_cast<T *>(obj);

    if (!testObj)
        return false;

    ((testObj)->*(m_method))(data);
    return true;
}


// ** RESET
class AbsResetBase
{
public:
    virtual ~AbsResetBase() {}
public:
    virtual bool runV(Object *) const = 0;
};

class AbsReset : public AbsResetBase {};

template<class T>
class ShadeReset : public AbsReset
{
public:
    ShadeReset(void (T::*method)());
public:
    bool runV(Object *) const override;
private:
    void (T::*m_method)();
};

template<class T>
ShadeReset<T>::ShadeReset(void (T::*method)())
{
    m_method = method;
}

template<class T>
bool ShadeReset<T>::runV(Object *obj) const
{
    T* testObj = dynamic_cast<T *>(obj);
    if (!testObj)
        return false;
    ((testObj)->*(m_method))();
    return true;
}

/*

MetaObject::activate() создает объект StorageTupleData для хранения данных слота

// реальный код
StorageTupleData<SignalArgTypes...> dataPack{Vs...};

Пример SignalArgTypes is <int,bool>

class AbsStorageTuple
class StorageImpl<>                   наследуется от AbsStorageTuple
class StorageImpl<std::tuple<>>       наследуется от Teacup<>
class StorageImpl<int>                наследуется от Teacup<std::tuple<>>
class StorageImpl<std::tuple<int>>    наследуется от Teacup<int>
class StorageImpl<int,bool>           наследуется от Teacup<std::tuple<int>>
class StorageImpl<int,bool>           наследуется от Teacup<int,bool>

*/

// указатель метода хранилища для сигналов и слотов
class AbsStorage : public virtual Internal::AbsStorageFunction
{
public:
    using Internal::AbsStorageFunction::Invoke;
    virtual void Invoke(Object* receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const = 0;
    virtual bool CheckReturnType(ArgReturnCommon& retval) const = 0;
};

template<class T>
class StorageImpl : public AbsStorage, public Internal::StorageFunction<T>
{
public:
    StorageImpl(T ptr);

    std::unique_ptr<Internal::AbsStorageFunction> Duplicate() const override;
    using Internal::StorageFunction<T>::Invoke;
    void Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const override;
    bool CheckReturnType(ArgReturnCommon &retval) const override;
};

template<class FunctionReturn, class ...FunctionArgs>
class StorageImpl<FunctionReturn(*)(FunctionArgs...)> : public AbsStorage, public Internal::StorageFunction<FunctionReturn(*)(FunctionArgs...)>
{
public:
    StorageImpl(FunctionReturn(*ptr)(FunctionArgs...));

    std::unique_ptr<Internal::AbsStorageFunction> Duplicate() const override;
    using Internal::StorageFunction<FunctionReturn(*)(FunctionArgs...)>::Invoke;
    void Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const override;
    bool CheckReturnType(ArgReturnCommon &retval) const override;
};

template<class MethodClass, class...MethodArgs>
class StorageImpl<void(MethodClass::*)(MethodArgs...)> : public AbsStorage, public Internal::StorageFunction<void(MethodClass::*)(MethodArgs...)>
{
public:
    StorageImpl(void(MethodClass::*ptr)(MethodArgs...));

    std::unique_ptr<Internal::AbsStorageFunction> Duplicate() const override;

    using Internal::StorageFunction<void(MethodClass::*)(MethodArgs...)>::Invoke;
    void Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const override;
    bool CheckReturnType(ArgReturnCommon& retval) const override;
};

template<class MethodClass, class MethodReturn, class...MethodArgs>
class StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)> : public AbsStorage, public Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>
{
public:
    StorageImpl(MethodReturn(MethodClass::*ptr)(MethodArgs...));

    std::unique_ptr<Internal::AbsStorageFunction> Duplicate() const override;

    using Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>::Invoke;
    void Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const override;
    bool CheckReturnType(ArgReturnCommon& retval) const override;
};

// специализация - указатель на const метод
template<class MethodClass, class MethodReturn, class...MethodArgs>
class StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const> : public AbsStorage, public Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>
{
public:
    StorageImpl(MethodReturn(MethodClass::*ptr)(MethodArgs...) const);

    std::unique_ptr<Internal::AbsStorageFunction> Duplicate() const override;

    using Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>::Invoke;
    void Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval = 0) const override;
    bool CheckReturnType(ArgReturnCommon &retval) const override;
};


// (1) лямбда
template<class T>
StorageImpl<T>::StorageImpl(T lambda)
    : Internal::StorageFunction<T>(lambda)
{
}

template<class T>
std::unique_ptr<Internal::AbsStorageFunction> StorageImpl<T>::Duplicate() const
{
    return Internal::make_unique<StorageImpl<T>>(*this);
}

template<class T>
void StorageImpl<T>::Invoke(Object *receiver, const Internal::AbsStorageTuple* dataPack, ArgReturnCommon *retval) const
{
    // T должен быть классом иначе будет ошибка компилятора в противном случае
    auto methodPtr = &T::operator();
    this->Invoke_internal(dataPack, methodPtr);
}

template<class T>
bool StorageImpl<T>::CheckReturnType(ArgReturnCommon &retval) const
{
    // возвращаемый тип лямбда-выражения не требуется
    return !!dynamic_cast<ArgReturn<void> *>(&retval);
}

// (2) специализация - указатель функции
template<class FunctionReturn, class ...FunctionArgs>
StorageImpl<FunctionReturn(*)(FunctionArgs...)>::StorageImpl(FunctionReturn(*ptr)(FunctionArgs...))
    : Internal::StorageFunction<FunctionReturn(*)(FunctionArgs...)>(ptr)
{
}

template<class FunctionReturn, class ...FunctionArgs>
std::unique_ptr<Internal::AbsStorageFunction> StorageImpl<FunctionReturn(*)(FunctionArgs...)>::Duplicate() const
{
    return Internal::make_unique<StorageImpl<FunctionReturn(*)(FunctionArgs...)>>(*this);
}

template<class FunctionReturn, class ...FunctionArgs>
void StorageImpl<FunctionReturn(*)(FunctionArgs...)>::Invoke(Object *, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval) const
{
    // нет необходимости проверять приемник сообщений, так как он не используется
    // dynamic cast вернет действительный ptr, если слот имеет равные или меньшие параметры
    const Internal::StorageTuple<FunctionArgs...> *teaCup = dynamic_cast<const Internal::StorageTuple<FunctionArgs...> *>(dataPack);

    if (teaCup) 
    {
        // расширенный аргументы
        std::tuple<FunctionArgs...> args = teaCup->GetData();

        ArgReturn<FunctionReturn> *returnData = dynamic_cast<ArgReturn<FunctionReturn> *>(retval);

        if (returnData) 
        {
            // распакуйте кортеж затем вызовите метод или слот
            returnData->SetData(Internal::vsn_UnpackFunctionArgs(this->m_methodPtr, args));
        }
        else 
        {
            // returnData - может быть nullptr, если retval был нулевым или неправильным, 
            // предполагается, что пользователь не хочет иметь возвращаемое значение
            // распакуйте кортеж затем вызовите метод или слот
            Internal::vsn_UnpackFunctionArgs(this->m_methodPtr, args);
        }
    }
}

template<class FunctionReturn, class ...FunctionArgs>
bool StorageImpl<FunctionReturn(*)(FunctionArgs...)>::CheckReturnType(ArgReturnCommon &retval) const
{
    if (dynamic_cast<ArgReturn<FunctionReturn> *>(&retval)) {
        return true;
    }

    if (dynamic_cast<ArgReturn<void> *>(&retval)) {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (33) specialization, method pointer
template<class MethodClass, class...MethodArgs>
StorageImpl<void(MethodClass::*)(MethodArgs...)>::StorageImpl(void(MethodClass::*ptr)(MethodArgs...))
    : Internal::StorageFunction<void(MethodClass::*)(MethodArgs...)>(ptr)
{
}

template<class MethodClass, class...MethodArgs>
std::unique_ptr<Internal::AbsStorageFunction> StorageImpl<void(MethodClass::*)(MethodArgs...)>::Duplicate() const
{
    return Internal::make_unique<StorageImpl<void(MethodClass::*)(MethodArgs...)>>(*this);
}

template<class MethodClass, class ...MethodArgs>
void StorageImpl<void(MethodClass::*)(MethodArgs...)>::Invoke(Object* receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval) const
{
    if (receiver == nullptr)
        return;
    if (MethodClass* t_receiver = dynamic_cast<MethodClass*>(receiver))
    {
        // нет необходимости проверять приемник сообщений, так как он не используется
        // dynamic cast вернет действительный ptr, если слот имеет равные или меньшие параметры
        const Internal::StorageTuple<MethodArgs...> *teaCup = dynamic_cast<const Internal::StorageTuple<MethodArgs...> *>(dataPack);

        if (teaCup)
        {
            // расширенный аргументы
            std::tuple<MethodArgs...> args = teaCup->GetData();
            ArgReturn<void> *returnData = dynamic_cast<ArgReturn<void> *>(retval);
            if (returnData)
            {
                // Распаковывает кортеж, затем вызывает метод или слот
                returnData->SetData(Internal::vsn_UnpackMethodArgs_1(t_receiver, this->m_methodPtr, args));
            }
            else
            {
                // returnData - может быть nullptr, если retval был нулевым или неправильным, 
                // предполагается, что пользователь не хочет иметь возвращаемое значение
                // распакуйте кортеж затем вызовите метод или слот
                Internal::vsn_UnpackMethodArgs_1(t_receiver, this->m_methodPtr, args);
            }
        }
    }
}

template<class MethodClass, class ...MethodArgs>
bool StorageImpl<void(MethodClass::*)(MethodArgs...)>::CheckReturnType(ArgReturnCommon &retval) const
{
    if (dynamic_cast<ArgReturn<void> *>(&retval)) {
        return true;
    }
    return false;
}

// (3) specialization, method pointer
template<class MethodClass, class MethodReturn, class...MethodArgs>
StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)>::StorageImpl(MethodReturn(MethodClass::*ptr)(MethodArgs...))
    : Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>(ptr)
{
}

template<class MethodClass, class MethodReturn, class...MethodArgs>
std::unique_ptr<Internal::AbsStorageFunction> StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)>::Duplicate() const
{
    return Internal::make_unique<StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)>>(*this);
}

template<class MethodClass, class MethodReturn, class ...MethodArgs>
void StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)>::Invoke(Object* receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval) const
{
    if (receiver == nullptr)
        return;
    if (MethodClass* t_receiver = dynamic_cast<MethodClass*>(receiver))
    {
        // нет необходимости проверять приемник сообщений, так как он не используется
        // dynamic cast вернет действительный ptr, если слот имеет равные или меньшие параметры
        const Internal::StorageTuple<MethodArgs...> *teaCup = dynamic_cast<const Internal::StorageTuple<MethodArgs...> *>(dataPack);

        if (teaCup)
        {
            // расширенный аргументы
            std::tuple<MethodArgs...> args = teaCup->GetData();
            ArgReturn<MethodReturn> *returnData = dynamic_cast<ArgReturn<MethodReturn> *>(retval);
            if (returnData)
            {
                // Распаковывает кортеж, затем вызывает метод или слот
                returnData->SetData(Internal::vsn_UnpackMethodArgs(t_receiver, this->m_methodPtr, args));
            }
            else
            {
                // returnData - может быть nullptr, если retval был нулевым или неправильным, 
                // предполагается, что пользователь не хочет иметь возвращаемое значение
                // распакуйте кортеж затем вызовите метод или слот
                Internal::vsn_UnpackMethodArgs(t_receiver, this->m_methodPtr, args);
            }
        }
    }
}

template<class MethodClass, class MethodReturn, class ...MethodArgs>
bool StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...)>::CheckReturnType(ArgReturnCommon &retval) const
{
    if (dynamic_cast<ArgReturn<MethodReturn> *>(&retval)) {
        return true;
    }

    if (dynamic_cast<ArgReturn<void> *>(&retval)) {
        return true;
    }

    return false;
}

// (4) specialization, pointer to const method
template<class MethodClass, class MethodReturn, class...MethodArgs>
StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const>::StorageImpl(MethodReturn(MethodClass::*ptr)(MethodArgs...) const)
    : Internal::StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>(ptr)
{
}

template<class MethodClass, class MethodReturn, class...MethodArgs>
std::unique_ptr<Internal::AbsStorageFunction> StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const>::Duplicate() const
{
    return Internal::make_unique<StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const>>(*this);
}

template<class MethodClass, class MethodReturn, class ...MethodArgs>
void StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const>::Invoke(Object *receiver, const Internal::AbsStorageTuple *dataPack, ArgReturnCommon *retval) const
{
    if (receiver == nullptr)
        return;
    if (MethodClass* t_receiver = dynamic_cast<MethodClass *>(receiver))
    {
        // dynamic_cast будет возвращать допустимый указатель, если слот имеет равные или меньше параметров
        // получить указатель в хранителе объекта, который содержит данные
        if (const Internal::StorageTuple<MethodArgs...>* storageTuple = dynamic_cast<const Internal::StorageTuple<MethodArgs...> *>(dataPack))
        {
            // развернуть аргументы
            std::tuple<MethodArgs...> args = storageTuple->GetData();
            if (ArgReturn<MethodReturn>* returnData = dynamic_cast<ArgReturn<MethodReturn> *>(retval))
            {
                // распаковывает кортеж затем вызывает метод или слот
                returnData->SetData(Internal::vsn_UnpackMethodArgs(t_receiver, this->m_methodPtr, args));
            }
            else 
            {
                // returnData является нулевым указателем, поэтому retval был NULL или неправильного типа
                // распаковывает кортеж затем вызывает метод или слот
                Internal::vsn_UnpackMethodArgs(t_receiver, this->m_methodPtr, args);
            }
        }
    }
}

template<class MethodClass, class MethodReturn, class ...MethodArgs>
bool StorageImpl<MethodReturn(MethodClass::*)(MethodArgs...) const>::CheckReturnType(ArgReturnCommon &retval) const
{
    return !!dynamic_cast<ArgReturn<MethodReturn> *>(&retval) || !!dynamic_cast<ArgReturn<void> *>(&retval);
}

VSN_END_NAMESPACE

#pragma warning( pop ) // C4250


#endif // __VSN_METAINTERNAL_H

