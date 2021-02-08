////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Набор макросов и шаблонов, реализующих простую и портативную систему RTTI.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#include "vsn_object.h"

#ifndef __VSN_METAOBJECT_H
#define __VSN_METAOBJECT_H

#include <map>
#include <typeindex>
#include <string>

#include "vsn_meta.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

class Object;
/* MetaClassInfo */
class VSN_CLASS MetaClassInfo
{
public:
    MetaClassInfo(const char* pName, const char* pValue);
public:
    const char* GetName() const;
    const char* GetValue() const;
private:
    const char* m_pName;
    const char* m_pValue;
};

class MetaObjectPrivate;
/* MetaObject */
class VSN_CLASS MetaObject
{
public:
    MetaObject();
    virtual ~MetaObject();
public:
    virtual MetaClassInfo GetMetaClassInfo(size_t index) const = 0;
    virtual size_t GetClassInfoCount() const = 0;
    virtual const char* GetMetaClassName() const = 0;
    virtual const MetaObject* GetSuperClass() const = 0;
    size_t GetClassInfoOffset() const;
    bool IsInherits(const MetaObject* pMetaObject) const;
    Object* Cast(Object* pObj) const;
    const Object* Cast(const Object* pObj) const;

    virtual int GetMethodCount() const = 0;
    virtual MetaMethod GetMethodByIndex(int index) const = 0;
    MetaMethod GetMethodByStorage(const AbsStorage& temp) const;
    int GetMethodOffset() const;

    virtual MetaEnum GetEnumByIndex(int index) const = 0;
    virtual int GetEnumCount() const = 0;
    int GetEnumOffset() const;

    int GetIndexMethod(const char* method) const;
    int GetIndexEnumerator(const char* pName) const;
    int GetIndexSignal(const char* signal) const;
    int GetIndexSlot(const char* slot) const;

    int GetIndexProp(const char* pName) const;
    virtual MetaProperty GetPropByIndex(int index) const = 0;
    virtual int GetPropCount() const = 0;
    int GetPropOffset() const;

    template<class MethodClass, class... MethodArgs>
    MetaMethod Method(void (MethodClass::*methodPtr)(MethodArgs...)) const;
protected:
    std::shared_ptr<MetaObjectPrivate> m_ptrMetaObject;
    friend class MetaObjectPrivate;
};

template<class MethodClass, class... MethodArgs>
MetaMethod MetaObject::Method(void (MethodClass::*methodPtr)(MethodArgs...)) const
{
    MetaMethod result;
    StorageImpl<void (MethodClass::*)(MethodArgs...)> storage = methodPtr;
    for (int index = 0, count = GetMethodCount(); index < count; ++index)
    {
        MetaMethod metaMethod = GetMethodByIndex(index);
        if (metaMethod.IsCompare(storage))
        {
            // найдено совпадение MetaMethod
            result = metaMethod;
            break;
        }
    }
    return result;
}


class MetaObjectImplPrivate;
/* MetaObjectImpl */
class VSN_CLASS MetaObjectImpl : public MetaObject
{
public:
    MetaObjectImpl();
public:
    void SetClassInfo(const char* pName, const char* value);
    MetaClassInfo GetMetaClassInfo(size_t index) const override;
    size_t GetClassInfoCount() const override;

    MetaEnum GetEnumByIndex(int index) const override;
    int GetEnumCount() const override;

    MetaMethod GetMethodByIndex(int index) const override;
    int GetMethodCount() const override;

    MetaProperty GetPropByIndex(int index) const override;
    int GetPropCount() const override;

    int SetEnum(const char* pName, std::type_index id, const char* scope);
public:
    void BindMethodBegin(const char* pName, MetaMethod method);
    void BindMethodBegin(const char* pName, MetaMethod::AccessType access, MetaMethod::MethodType type);
    // properties
    int BindPropRead(const char* pName, const char* dataType, std::shared_ptr<AbsReadBase> ptrMethod);
    int BindPropWrite(const char* pName, std::shared_ptr<AbsWriteBase> ptrMethod);
    int BindPropBool(const char* pName, AbsReadBase* method, MetaProperty::PropType type);
    void BindPropInt(const char* pName, int value, MetaProperty::PropType type);
protected:
    static int CalcCountStorage(const char* va_args);
    std::vector<std::string> InstallMetaMethod(const char* pName, MetaMethod::MethodType type, const char* va_args, MetaMethod::AccessType access);
    std::vector<std::string> InsertMetaMethodByName(const String& className, const char* pName, MetaMethod::MethodType type);
    bool InsertMetaMethodByType(MetaMethod::MethodType type, const String& tokenKey, const MetaMethod& data);
    void InsertUpdateProp(const char* pName, std::shared_ptr<AbsStorage> ptrStorageMethod);
    std::map<std::string, MetaMethod>& GetMapMethodByType(MetaMethod::MethodType type) const;
    std::map<std::string, MetaProperty>& GetMapProperties();
protected:
    std::shared_ptr<MetaObjectImplPrivate> m_ptrObjectImpl;
};

/* TMetaObjectImpl */
template<class T>
class TMetaObjectImpl : public MetaObjectImpl
{
public:
    TMetaObjectImpl();
public:
    void PostBuild();
    const char* GetMetaClassName() const override;
    const char* GetInterface_iid() const;
    const MetaObject* GetSuperClass() const override;
public:
    // signals
    template<class M>
    void BindMethodEnd(const char* pName, M method, MetaMethod::MethodType type);
    // slots, invokables
    template<class M>
    void BindMethod(const char* pName, M method, MetaMethod::MethodType type, const char* va_args, MetaMethod::AccessType access);
    // properties
    template<class M>
    void BindPropNotify(const char* pName, M method);
};

template<class T>
TMetaObjectImpl<T>::TMetaObjectImpl()
{
}

template<class T>
void TMetaObjectImpl<T>::PostBuild()
{
    // вызывает перегруженную версию, чтобы обеспечить обработку других перегрузок
    T::vsn_Overload(VSN_VALUE_NUMBER<VSN_DEF_VALUE_ZERO>());
}

template<class T>
const char* TMetaObjectImpl<T>::GetMetaClassName() const
{
    return T::vsn_className();
}

template<class T>
inline const char* vobject_interface_iid();

template<class T>
const char* TMetaObjectImpl<T>::GetInterface_iid() const
{
    return vobject_interface_iid<T *>();
}

template<class T>
const MetaObject* TMetaObjectImpl<T>::GetSuperClass() const
{
    return &T::vsn_parent::GetStaticMetaObject();
}

template<>
inline const MetaObject* TMetaObjectImpl<Object>::GetSuperClass() const
{
    return 0;
}

template<class T> template<class M>
void TMetaObjectImpl<T>::BindMethodEnd(const char* pName, M method, MetaMethod::MethodType type)
{
    // обновить основную карту
    std::map<std::string, MetaMethod>& map = GetMapMethodByType(type);
    std::vector<std::string> keys = InsertMetaMethodByName(T::GetStaticMetaObject().GetMetaClassName(), pName, type);

    for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::string strKey = (*it);
        if (strKey.empty())
            continue;
        map.at(strKey).SetStorage(std::make_shared<StorageImpl<M>>(method));
    }
}

template<class T> template<class M>
void TMetaObjectImpl<T>::BindMethod(const char* pName, M method, MetaMethod::MethodType type, const char* va_args, MetaMethod::AccessType access)
{
    // обновить основную карту
    std::map<std::string, MetaMethod>& map = GetMapMethodByType(type);
    std::vector<std::string> keys = InstallMetaMethod(pName, type, va_args, access);
    for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        std::string strKey = (*it);
        if (strKey.empty())
            continue;
        map.at(strKey).SetStorage(std::make_shared<StorageImpl<M>>(method));
    }
}

template<class T> template<class M>
void TMetaObjectImpl<T>::BindPropNotify(const char* pName, M method)
{
    InsertUpdateProp(pName, std::make_shared<StorageImpl<M>>(method));
}

template<class T>
void vsn_namespace_register_enum(const char* name, std::type_index id, const char* scope)
{
    const_cast<TMetaObjectImpl<T>&>(T::GetStaticMetaObject()).SetEnum(name, id, scope);
}

VSN_END_NAMESPACE

#endif /* __VSN_METAOBJECT_H */
