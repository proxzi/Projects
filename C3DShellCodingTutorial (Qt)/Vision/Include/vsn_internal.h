#ifndef __VSN_INTERNAL_H
#define __VSN_INTERNAL_H

#include <memory>
#include <tuple>
#include <utility>
#include <functional>
#include <type_traits>
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class BasicObject;
namespace Internal
{
    // 1
    template<class T, class U, class = void>
    class vsn_TestConnectAargs : public vsn_TestConnectAargs<T, decltype(&U::operator())>
    {
    };

    // 2 слот - это func ptr, первый сигнал и параметры первого слота соответствуют
    template<class T, class ...ArgsX, class ...ArgsY>
    class vsn_TestConnectAargs<void(*)(T, ArgsX...), void(*)(T, ArgsY...)> 
        : public vsn_TestConnectAargs<void(*) (ArgsX...), void(*) (ArgsY...)>
    {
    };

    // slot - это func ptr, слот не имеет параметров
    template<class ...ArgsX>
    class vsn_TestConnectAargs<void(*)(ArgsX...), void(*)()> 
        : public std::integral_constant<bool, true>
    {
    };

    // слот - func ptr сигнал имеет такое же количество парметров, что и слот и типы несоответствия
    template<class ...ArgsX, class ...ArgsY>
    class vsn_TestConnectAargs < void(*)(ArgsX...), void(*)(ArgsY...),
        typename std::enable_if < sizeof...(ArgsX) == sizeof...(ArgsY) &&
        !std::is_same<std::tuple<ArgsX...>, std::tuple<ArgsY...>>::value >::type >
        : public std::integral_constant<bool, false>
    {
    };
    
    // слот является func ptr, сигнал имеет меньшее количество парм, чем слот
    /*
    template<class ...ArgsX, class ...ArgsY>
    class vsn_TestConnectAargs < void (*)(ArgsX...), void (*)(ArgsY...),
    typename std::enable_if<sizeof...(ArgsX) < sizeof...(ArgsY)>::type >
    : public std::integral_constant<bool, false>
    {
    };
    */
    template<class ...ArgsX, class ...ArgsY>
    class vsn_TestConnectAargs < void(*)(ArgsX...), void(*)(ArgsY...), typename std::enable_if<sizeof...(ArgsX) < sizeof...(ArgsY)> >
        : public std::integral_constant<bool, false>
    {
    };


    // 3 слот - это метод ptr
    template<class T, class...ArgsX, class...ArgsY>
    class vsn_TestConnectAargs<void(*)(ArgsX...), void (T::*)(ArgsY...) >
        : public vsn_TestConnectAargs<void(*)(ArgsX...), void(*) (ArgsY...)>
    {
    };

    // slot - это метод const ptr
    template<class T, class...ArgsX, class...ArgsY>
    class vsn_TestConnectAargs<void(*)(ArgsX...), void (T::*)(ArgsY...) const>
        : public vsn_TestConnectAargs<void(*)(ArgsX...), void(*) (ArgsY...)>
    {
    };

    // тесты времени компиляции
    template<class Sender, class SignalClass>
    void vsn_TestConnectSenderSignal()
    { static_assert(std::is_base_of<SignalClass, Sender>::value, "Signal is not defined in the sender class"); }

    template<class Slot_LambdaType, class ...SignalArgs>
    void vsn_TestConnectSignalSlotArgs_1()
    { static_assert(vsn_TestConnectAargs<void(*)(SignalArgs...), Slot_LambdaType>::value, "Incompatible signal/slot arguments"); }

    template<class SlotClass, class Receiver>
    void vsn_TestConnectReceiverSlot()
    { static_assert(std::is_base_of<SlotClass, Receiver>::value, "Slot is not defined in the receiver class"); }

    template<class Signal_ArgType, class Slot_ArgType>
    void vsn_TestConnectSignalSlotArgs_2()
    { static_assert(vsn_TestConnectAargs<Signal_ArgType, Slot_ArgType>::value, "Incompatible signal/slot arguments");}

    // доступно на C++ 14
    template <class T, class... Args>
    std::unique_ptr<T> make_unique(Args &&... args) { return std::unique_ptr<T>(new T(std::forward<Args>(args)...)); }

    // маркер для функции, которая возвращает void
    class VSNVoidReturn {};

    // индексная последовательность (доступна в C++ 14
    // сгенерировать список целых чисел, соответствующих количеству типов данных в пакете параметров
    template<size_t...Ks>
    class IndexSequence
    {
    };

    template<size_t S, class K1, class K2>
    class ConcatSequence;

    template<size_t S, size_t ...M, size_t ...N>
    class ConcatSequence<S, IndexSequence<M...>, IndexSequence<N...>>
    {
    public:
        using type = IndexSequence < M..., (N + S)... >;
    };

    template<size_t N>
    class MakeIndexSequence 
    {
    public:
        using type = typename ConcatSequence < (N / 2), typename MakeIndexSequence < (N / 2) >::type,
            typename MakeIndexSequence < (N - (N / 2)) >::type >::type;
    };

    template<>
    class MakeIndexSequence<0> { public: using type = IndexSequence<>; };

    template<>
    class MakeIndexSequence<1> { public: using type = IndexSequence<0>; };

    template<class ...Ts>
    class IndexSequenceFor { public: using type = typename MakeIndexSequence<sizeof ...(Ts)>::type; };


    // unpack_function
    // использует IndexSequence Class для распаковки кортежа в аргументы для указателя функции
    template<typename ...FunctionArgTypes, typename FunctionReturn, typename ...TupleTypes, size_t ...Ks>
    FunctionReturn vsn_UnpackFunctionArgsPrivate(FunctionReturn(*functionPtr)(FunctionArgTypes...),
        const std::tuple<TupleTypes...> &data, IndexSequence<Ks...>)
    {
        return functionPtr(std::get<Ks>(data)...);
    }

    // указатель функции специализации
    template<typename ...FunctionArgTypes, typename FunctionReturn, typename ...TupleTypes>
    FunctionReturn vsn_UnpackFunctionArgs(FunctionReturn(*functionPtr)(FunctionArgTypes...), const std::tuple<TupleTypes...> &data)
    {
        return vsn_UnpackFunctionArgsPrivate(functionPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
    }

    // для специального указателя на метод, возвращаемый тип void
    template<typename ...FunctionArgTypes, typename ...TupleTypes>
    VSNVoidReturn vsn_UnpackFunctionArgs_1(void(*functionPtr)(FunctionArgTypes...), const std::tuple<TupleTypes...> &data)
    {
        vsn_UnpackFunctionArgsPrivate(functionPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
        return VSNVoidReturn{};
    }

    // unpack_function
    // использует класс IndexSequence для распаковки кортежа в аргументы для указателя метода
    template<typename MethodClass, class MethodReturn, typename ...MethodArgTypes, typename ...TupleTypes, size_t ...Ks>
    MethodReturn vsn_UnpackMethodArgsPrivate(MethodClass* obj, MethodReturn(MethodClass::*methodPtr)(MethodArgTypes...), const std::tuple<TupleTypes...>& data, IndexSequence<Ks...>)
    {
        return (obj->*methodPtr)(std::get<Ks>(data)...);
    }

    // Указатель на метод специализации
    template<typename MethodClass, class MethodReturn, typename ...MethodArgTypes, typename ...TupleTypes>
    MethodReturn vsn_UnpackMethodArgs(MethodClass* obj, MethodReturn(MethodClass::*methodPtr)(MethodArgTypes...), const std::tuple<TupleTypes...>& data)
    {
        return vsn_UnpackMethodArgsPrivate(obj, methodPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
    }

    // для специального указателя на метод, возвращаемый тип void
    template<typename MethodClass, typename ...MethodArgTypes, typename ...TupleTypes>
    VSNVoidReturn vsn_UnpackMethodArgs_1(MethodClass* obj, void (MethodClass::*methodPtr)(MethodArgTypes...), const std::tuple<TupleTypes...>& data)
    {
        vsn_UnpackMethodArgsPrivate(obj, methodPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
        return VSNVoidReturn{};
    }


    // использует класс IndexSequence для распаковки кортежа в аргументы для указателя метода const
    template<typename MethodClass, class MethodReturn, typename ...MethodArgTypes, typename ...TupleTypes, size_t ...Ks>
    MethodReturn vsn_UnpackMethodArgsPrivate(const MethodClass *obj, MethodReturn(MethodClass::*methodPtr)(MethodArgTypes...) const, const std::tuple<TupleTypes...>& data, IndexSequence<Ks...>)
    {
        return (obj->*methodPtr)(std::get<Ks>(data)...);
    }

    // специализация для указателя метода const
    template<typename MethodClass, class MethodReturn, typename ...MethodArgTypes, typename ...TupleTypes>
    MethodReturn vsn_UnpackMethodArgs(const MethodClass *obj, MethodReturn(MethodClass::*methodPtr)(MethodArgTypes...) const, const std::tuple<TupleTypes...>& data)
    {
        return vsn_UnpackMethodArgsPrivate(obj, methodPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
    }

    // для специального указателя на метод, возвращаемый тип void
    template<typename MethodClass, typename ...MethodArgTypes, typename ...TupleTypes>
    VSNVoidReturn vsn_UnpackMethodArgs_1(const MethodClass* obj, void (MethodClass::*methodPtr)(MethodArgTypes...) const, const std::tuple<TupleTypes...>& data)
    {
        vsn_UnpackMethodArgsPrivate(obj, methodPtr, data, typename IndexSequenceFor<TupleTypes...>::type{});
        return VSNVoidReturn{};
    }


    // шаблонные классы используемые для добавления или удаления типов в кортеж
    template <class T1, class T2>
    class Prepend
    {
        // требуемый класс для использования специализации
    };

    template <class T, class ...Ts>
    class Prepend<T, std::tuple<Ts...>>
    {
    public:
        using type = typename std::tuple<T, Ts...>;
    };

    template <class T1>
    class Band
    {
    public:
        // ничего не содержит
        using type = typename std::tuple<>;
    };

    template <class T1, class T2, class ...Ts>
    class Band<std::tuple<T1, T2, Ts...>>
    {
    public:
        using type = typename Prepend<T1, typename Band<std::tuple<T2, Ts...> >::type>::type;
    };

    // шаблонные классы для генерации типа данных из пакета параметров
    template<unsigned int ...Vs>
    class IntValues
    {
    };

    template<unsigned int Max, unsigned int ...Vs>
    class MakeIntValues : public MakeIntValues <Max - 1, Max - 1, Vs...>
    {
    };

    template<unsigned int ...Vs>
    class MakeIntValues<0, Vs...> : public IntValues<Vs...>
    {
    };

    // шаблонный класс, чтобы удалить последний тип данных из «типа данных кортежа»
    template <class ...Ts>
    class RemoveLastType
    {
    public:
        using type = typename Band< std::tuple<Ts...> >::type;
    };

    // шаблонные функции, чтобы удалить последний элемент данных из кортежа
    template<unsigned int ...Vs, class ...Ts>
    typename RemoveLastType<Ts...>::type internalRemoveData(IntValues<Vs...>, std::tuple<Ts...> tupleValue)
    {
        return std::forward_as_tuple(std::get<Vs>(tupleValue)...);
    }

    template<class ...Ts>
    typename RemoveLastType<Ts...>::type funcRemoveData(std::tuple<Ts...> tupleValue)
    {
        return internalRemoveData(MakeIntValues<sizeof...(Ts)-1>(), tupleValue);
    }

    // класс для хранения данных слотов в кортеже
    class AbsStorageTuple
    {
    public:
        virtual ~AbsStorageTuple() {}
    };

    // 1
    template<class ...Ts>
    class StorageTuple : public StorageTuple< typename RemoveLastType<Ts...>::type>
    {
    public:
        template<class T>
        explicit StorageTuple(T lambda);
    public:
        std::tuple<Ts...> GetData() const;
    private:
        std::function<std::tuple<Ts...>()> m_lambda;
    };

    template<class ...Ts> template<class T>
    StorageTuple<Ts...>::StorageTuple(T lambda)
        : StorageTuple< typename RemoveLastType<Ts...>::type >([this]() { return funcRemoveData(m_lambda()); }),
        m_lambda(std::move(lambda))
    {
    }

    template<class ...Ts>
    std::tuple<Ts...> StorageTuple<Ts...>::GetData() const
    {
        return m_lambda();
    }

    // 2 специализация без аргументов
    template<>
    class StorageTuple<> : public AbsStorageTuple
    {
    public:
        template<class T>
        explicit StorageTuple(T lambda);

        std::tuple<> GetData() const;
    };

    template<class T>
    StorageTuple<>::StorageTuple(T)
    {
    }

    inline std::tuple<> StorageTuple<>::GetData() const
    {
        // пустой tuple
        return std::tuple<> {};
    }

    // 3 специализация, кортеж с args
    template<class ...Ts>
    class StorageTuple< std::tuple<Ts...> > : public StorageTuple<Ts...>
    {
    public:
        template<class T>
        explicit StorageTuple(T lambda);
    };

    template<class ...Ts>
    template<class T>
    StorageTuple<std::tuple<Ts...>>::StorageTuple(T lambda)
        : StorageTuple<Ts...>(std::move(lambda))
    {
    }

    // функции шаблона используют IndexSequence для преобразования кортежа в R
    template<class R, class T, size_t ...Ks>
    R ConvertTuplePrivate(T &data, IndexSequence<Ks...>)
    {
        return R{ std::get<Ks>(data)... };
    }

    template<class R, class ...Ts>
    R ConvertTuple(std::tuple<Ts...> &data)
    {
        return ConvertTuplePrivate<R>(data, typename IndexSequenceFor<Ts...>::type{});
    }

    // шаблон используемый для хранения данных для сигналов
    template<class ...Ts>
    class StorageTupleData : public StorageTuple<Ts...>
    {
    public:
        StorageTupleData(bool needs_copying, Ts...);
        std::tuple<Ts...> GetData() const;
    private:
        std::shared_ptr< std::tuple<typename std::remove_reference<Ts>::type...> > m_copyOfData;
        std::tuple<Ts...> m_data;
    };

    template<class ...Ts>
    StorageTupleData<Ts...>::StorageTupleData(bool needs_copying, Ts...Vs)
        : StorageTuple<Ts...>([this]() { return m_data; }),
        m_copyOfData(needs_copying ? new std::tuple<typename std::remove_reference<Ts>::type...>(Vs...) : nullptr),
        m_data(needs_copying ? ConvertTuple<std::tuple<Ts...>>(*m_copyOfData) : std::tuple<Ts...>(Vs...))
    {
    }

    template<class ...Ts>
    std::tuple<Ts...> StorageTupleData<Ts...>::GetData() const
    { return m_data; }

    // класс для хранения указателя метода для сигналов и слотов
    class AbsStorageFunction
    {
    public:
        virtual ~AbsStorageFunction() {}

        virtual bool operator ==(const AbsStorageFunction &right) const = 0;
        bool operator !=(const AbsStorageFunction &right) const;

        virtual void Invoke(BasicObject* receiver, const AbsStorageTuple *dataPack) const = 0;
        virtual std::unique_ptr<AbsStorageFunction> Duplicate() const = 0;
    };

    inline bool AbsStorageFunction::operator !=(const AbsStorageFunction &right) const
    { return !(*this == right); }

    template<class T>
    class StorageFunction : public virtual AbsStorageFunction
    {
    public:
        StorageFunction(T ptr);
    public:
        bool operator ==(const AbsStorageFunction& right) const override;

        void Invoke(BasicObject* receiver, const AbsStorageTuple* dataPack) const override;
        std::unique_ptr<AbsStorageFunction> Duplicate() const override;

        template<class MethodReturn, class ...MethodArgs>
        void InvokeInternal(const AbsStorageTuple* dataPack, MethodReturn(T::*methodPtr)(MethodArgs...) const) const;

        template<class MethodReturn, class ...MethodArgs>
        void InvokeInternal(const AbsStorageTuple* dataPack, MethodReturn(T::*methodPtr)(MethodArgs...)) const;
        T m_lambda;
    };

    template<class FunctionReturn, class ...FunctionArgs>
    class StorageFunction<FunctionReturn(*)(FunctionArgs...)> : public virtual AbsStorageFunction
    {
    public:
        StorageFunction(FunctionReturn(*ptr)(FunctionArgs...));
    public:
        bool operator ==(const AbsStorageFunction &right) const override;

        std::unique_ptr<AbsStorageFunction> Duplicate() const override;
        void Invoke(BasicObject* receiver, const AbsStorageTuple* dataPack) const override;

        FunctionReturn(*m_methodPtr)(FunctionArgs...);
    };

    template<class MethodClass, class MethodReturn, class...MethodArgs>
    class StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)> : public virtual AbsStorageFunction
    {
    public:
        StorageFunction(MethodReturn(MethodClass::*ptr)(MethodArgs...));

        bool operator ==(const AbsStorageFunction &right) const override;
        void Invoke(BasicObject *receiver, const AbsStorageTuple *dataPack) const override;
        std::unique_ptr<AbsStorageFunction> Duplicate() const override;

        MethodReturn(MethodClass::*m_methodPtr)(MethodArgs...);
    };

    // специализация, указатель метода const
    template<class MethodClass, class MethodReturn, class...MethodArgs>
    class StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const> : public virtual AbsStorageFunction
    {
    public:
        StorageFunction(MethodReturn(MethodClass::*ptr)(MethodArgs...) const);

        bool operator ==(const AbsStorageFunction &right) const override;

        void Invoke(BasicObject *receiver, const AbsStorageTuple *dataPack) const override;
        std::unique_ptr<AbsStorageFunction> Duplicate() const override;

        MethodReturn(MethodClass::*m_methodPtr)(MethodArgs...) const;
    };

    // (1) lambda
    template<class T>
    StorageFunction<T>::StorageFunction(T lambda)
        : m_lambda(lambda)
    {
    }

    template<class T>
    std::unique_ptr<AbsStorageFunction> StorageFunction<T>::Duplicate() const
    {
        return Internal::make_unique<StorageFunction<T>>(*this);
    }


    template<class T>
    bool StorageFunction<T>::operator ==(const AbsStorageFunction& right) const
    {
        bool bRetval = false;
        const StorageFunction<T>* pStorageFunctionRight = dynamic_cast<const StorageFunction<T> *>(&right);
        const StorageFunction<T>* pStorageFunctionLeft = dynamic_cast<const StorageFunction<T> *>(this);
        if (pStorageFunctionLeft && pStorageFunctionRight)
        {
            auto ptr1 = (std::function<void()>)(pStorageFunctionLeft->m_lambda);
            auto ptr2 = (std::function<void()>)(pStorageFunctionRight->m_lambda);
            if (ptr1 && ptr1)
                bRetval = (ptr1.target_type() == ptr2.target_type());
        }
        return bRetval;
        // не может сравнивать две лямбды функции
//        return false;
    }

    template<class T>
    void StorageFunction<T>::Invoke(BasicObject*, const AbsStorageTuple *dataPack) const
    {
        // T должен быть классом или он будет ошибкой компилятора
        auto methodPtr = &T::operator();
        this->InvokeInternal(dataPack, methodPtr);
    }

    template<class T>
    template<class MethodReturn, class ...MethodArgs>
    void StorageFunction<T>::InvokeInternal(const AbsStorageTuple *dataPack, MethodReturn(T::*methodPtr)(MethodArgs...) const) const
    {
        // обрабатывает non-mutable захваченные переменные const

        // dynamic_cast вернет действительный ptr, если слот имеет равные или меньшие параметры
        // извлечения ptr в объект pStorageTuple, который содержит данные
        if (const StorageTuple<MethodArgs...>* pStorageTuple = dynamic_cast<const StorageTuple<MethodArgs...> *>(dataPack))
        {
            // расширить аргументы
            std::tuple<MethodArgs...>&& args = pStorageTuple->GetData();
            // распаковывает кортеж, затем вызывает methodPtr
            vsn_UnpackMethodArgs(&m_lambda, methodPtr, args);
        }
    }

    template<class T>
    template<class MethodReturn, class ...MethodArgs>
    void StorageFunction<T>::InvokeInternal(const AbsStorageTuple *dataPack, MethodReturn(T::*methodPtr)(MethodArgs...)) const
    {
        // dynamic_cast вернет действительный ptr, если слот имеет равные или меньшие параметры
        // извлечения ptr в объект pStorageTuple, который содержит данные
        if (const StorageTuple<MethodArgs...>* pStorageTuple = dynamic_cast<const StorageTuple<MethodArgs...> *>(dataPack))
        {
            // расширить аргументы
            std::tuple<MethodArgs...>&& args = pStorageTuple->GetData();
            auto object = const_cast<typename std::remove_const<T>::type *>(&m_lambda);
            // распаковывает кортеж, затем вызывает methodPtr
            vsn_UnpackMethodArgs(object, methodPtr, args);
        }
    }

    // (2) специализация - указатель функций
    template<class FunctionReturn, class ...FunctionArgs>
    StorageFunction<FunctionReturn(*)(FunctionArgs...)>::StorageFunction(FunctionReturn(*ptr)(FunctionArgs...))
        : m_methodPtr(ptr)
    {
    }

    template<class FunctionReturn, class ...FunctionArgs>
    std::unique_ptr<AbsStorageFunction> StorageFunction<FunctionReturn(*)(FunctionArgs...)>::Duplicate() const
    {
        return Internal::make_unique<StorageFunction<FunctionReturn(*)(FunctionArgs...)>>(*this);
    }

    template<class FunctionReturn, class ...FunctionArgs>
    bool StorageFunction<FunctionReturn(*)(FunctionArgs...)>::operator ==(const AbsStorageFunction& right) const
    {
        bool bRetval = false;
        if (const StorageFunction<FunctionReturn(*)(FunctionArgs...)>* pStorageFunction = 
            dynamic_cast<const StorageFunction <FunctionReturn(*)(FunctionArgs...)> *>(&right))
            bRetval = (this->m_methodPtr == pStorageFunction->m_methodPtr);
        return bRetval;
    }

    template<class FunctionReturn, class ...FunctionArgs>
    void StorageFunction<FunctionReturn(*)(FunctionArgs...)>::Invoke(BasicObject *, const AbsStorageTuple *dataPack) const
    {
        // нет необходимости проверять приемник (slotBase *), поскольку он не используется

        // dynamic_cast вернет действительный ptr, если слот имеет равные или меньшие параметры
        // извлечения ptr в объект pStorageTuple, который содержит данные
        if (const StorageTuple<FunctionArgs...>* pStorageTuple = dynamic_cast<const StorageTuple<FunctionArgs...> *>(dataPack))
        {
            // расширить аргументы
            std::tuple<FunctionArgs...>&& args = pStorageTuple->GetData();
            // распаковывает кортеж, затем вызывает methodPtr
            vsn_UnpackFunctionArgs(m_methodPtr, args);
        }
    }


    // (3) специализация - указатель на метода
    template<class MethodClass, class MethodReturn, class...MethodArgs>
    StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>::StorageFunction(MethodReturn(MethodClass::*ptr)(MethodArgs...))
        : m_methodPtr(ptr)
    {
    }

    template<class MethodClass, class MethodReturn, class...MethodArgs>
    std::unique_ptr<AbsStorageFunction> StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>::Duplicate() const
    {
        return Internal::make_unique<StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>>(*this);
    }

    template<class MethodClass, class MethodReturn, class...MethodArgs>
    bool StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>::operator ==(const AbsStorageFunction& right) const
    {
        bool bRetval = false;
        if (const StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>* pStorageFunction =
            dynamic_cast<const StorageFunction <MethodReturn(MethodClass::*)(MethodArgs...)> *> (&right))
            bRetval = (this->m_methodPtr == pStorageFunction->m_methodPtr);
        return bRetval;
    }

    template<class MethodClass, class MethodReturn, class ...MethodArgs>
    void StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...)>::Invoke(BasicObject* receiver, const AbsStorageTuple *dataPack) const
    {
        if (receiver == nullptr)
            return;
        if (MethodClass* _pReceiver = dynamic_cast<MethodClass*>(receiver))
        {
            // dynamic_cast вернет действительный ptr, если слот имеет равные или меньшие параметры
            // извлечения ptr в объект pStorageTuple, который содержит данные
            if (const StorageTuple<MethodArgs...>* pStorageTuple = dynamic_cast<const StorageTuple<MethodArgs...> *>(dataPack))
            {
                // расширить аргументы
                std::tuple<MethodArgs...>&& args = pStorageTuple->GetData();
                // распаковывает кортеж, затем вызывает methodPtr
                vsn_UnpackMethodArgs(_pReceiver, m_methodPtr, args);
            }
        }
    }

    // (4) специализация - указатель на метод const
    template<class MethodClass, class MethodReturn, class...MethodArgs>
    StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>::StorageFunction(MethodReturn(MethodClass::*ptr)(MethodArgs...) const)
        : m_methodPtr(ptr)
    {
    }

    template<class MethodClass, class MethodReturn, class...MethodArgs>
    std::unique_ptr<AbsStorageFunction> StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>::Duplicate() const
    {
        return Internal::make_unique<StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>>(*this);
    }

    template<class MethodClass, class MethodReturn, class...MethodArgs>
    bool StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>::operator ==(const AbsStorageFunction &right) const
    {
        bool bRetval = false;
        if (const StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>* pStorageFunction = 
            dynamic_cast<const StorageFunction <MethodReturn(MethodClass::*)(MethodArgs...) const> *> (&right))
            bRetval = (this->m_methodPtr == pStorageFunction->m_methodPtr);
        return bRetval;
    }

    template<class MethodClass, class MethodReturn, class ...MethodArgs>
    void StorageFunction<MethodReturn(MethodClass::*)(MethodArgs...) const>::Invoke(BasicObject *receiver, const AbsStorageTuple *dataPack) const
    {
        if (receiver == nullptr)
            return;
        if (MethodClass* t_receiver = dynamic_cast<MethodClass *>(receiver))
        {
            // dynamic_cast вернет действительный ptr, если слот имеет равные или меньшие параметры
            // извлечения ptr в объект pStorageTuple, который содержит данные
            if (const StorageTuple<MethodArgs...>* pStorageTuple = dynamic_cast<const StorageTuple<MethodArgs...> *>(dataPack))
            {
                // расширять аргументы
                std::tuple<MethodArgs...>&& args = pStorageTuple->GetData();
                // распаковывает кортеж, затем вызывает  methodPtr
                vsn_UnpackMethodArgs(t_receiver, m_methodPtr, args);
            }
        }
    }

    template<typename T> struct remove_const { typedef T type; };
    template<typename T> struct remove_const<T const> { typedef T type; };
    template<typename T> struct remove_volatile { typedef T type; };
    template<typename T> struct remove_volatile<T volatile> { typedef T type; };
    template<typename T> struct remove_const_volatile
    { typedef typename remove_const<typename remove_volatile<T>::type>::type type; };

    template<typename T> struct remove_pointer { typedef T type; };
    template<typename T> struct remove_pointer<T*> { typedef T type; };
    template<typename T> struct remove_pointer<T* const> { typedef T type; };
    template<typename T> struct remove_pointer<T* volatile> { typedef T type; };
    template<typename T> struct remove_pointer<T* const volatile> 
    { typedef T type; };

} // namespace Internal

VSN_END_NAMESPACE


#endif // __VSN_INTERNAL_H