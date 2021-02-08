////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Шаблонный класс Flags представляет типобезопасный способ хранения OR-комбинаций значений перечисления.
           \en Flags template class presents a type-safe method of storing OR-combinations of enumeration values. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_FLAGS_H
#define __VSN_FLAGS_H

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Flag
{
public:
    inline Flag(int _i) : i(_i) {};
    inline operator int() const { return i; }
private:
    int i;
};


//------------------------------------------------------------------------------
/** \brief  \ru Flags<Enum> является классом шаблона, где Enum - это перечисляемый тип. Flags используется в C3D Vision для хранения комбинаций значений перечисления.
            \en Flags<Enum> is a template class where Enum is an enumarated type. Flags is used to store enumeration value combinations in C3D Vision. \~
    \details \ru Традиционный подход C++ для хранения OR-комбинаций значений Enum должен использовать переменную типа int или uint.
                 Неудобство этого подхода заключается в том, что нет проверки типа вообще; любое значение перечисления может быть OR-операцией
                 с любым другим значением перечисления и передаваться в функции, которая принимает int или uint. \n
             \en С++ conventional approach for storing Enum value OR-combinations defines using int or uint variables.
                 The inconvenience of that approach is an absence of type checking. Any value of enumeration can be OR-operation with another value of enumeration
                 and it can be passed in function taking int or uint variables. \n \~
    \ingroup Vision_Сore
*/
// ---
template<typename Enum>
class Flags
{
public:
    typedef void **Zero;
    typedef Enum enum_type; ///< \ru Typedef для типа шаблона Enum. \en Typedef for Enum template type.
    /// \ru Конструктор копирования объекта Flags. \en Copy constructor of Flags object.
    inline Flags(const Flags& f) : i(f.i) {}
    /// \ru Конструктор объекта Flags с параметром флага для хранения данных. \en Flags object constructor with flag parameter for storing data.
    inline Flags(Enum f) : i(f) {}
    /// \ru Конструктор объекта Flags без определенных флагов. \en Flags object constructor with no defined flags.
    inline Flags(Zero = 0) : i(static_cast<Enum>(0)) {}
    /// \ru Конструктор объекта Flags, инициализированный заданным целочисленным значением. \en Flags object constructor initialized by integer value.
    inline Flags(Flag f) : i(f) {}
public:
    /// \ru Скопировать все флаги в объект и вернуть ссылку на этот объект. \en Copies all flags to object and returns reference to that object.
    inline Flags& operator=(const Flags &f) 
    {
        i = f.i;
        return *this;
    }
    /// \ru Выполняет битовую AND-операцию с маской и сохраняет результат в этом объекте Flags. Вернуть ссылку на этот объект. \en Performs bitwise AND-operation with mask and saves result in Flags object. Returns reference to the object.
    inline Flags& operator&=(int mask)  
    {
        i &= mask;
        return *this;
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags& operator&=(uint mask) 
    {
        i &= mask;
        return *this;
    }
    /// \ru Выполняет побитовую OR-операцию с другим объектом и сохраняет результат в этом объекте Flags. Вернуть ссылку на этот объект. \en Performs bitwise OR-operation with another object and saves result in Flags object. Returns reference to the object.
    inline Flags& operator|=(Flags f)
    {
        i |= f.i;
        return *this;
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags& operator|=(Enum f) 
    {
        i |= f;
        return *this;
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags& operator|=(int f)
    {
        i |= f;
        return *this;
    }
    /// \ru Выполняет побитовую XOR-операцию с другим объектом Flags и сохраняет результат в этом объекте Flags. Вернуть ссылку на этот объект. \en Performs bitwise XOR-operation with another Flags object and saves result in Flags object. Returns reference to the object.
    inline Flags& operator^=(Flags f)
    {
        i ^= f.i;
        return *this;
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags& operator^=(Enum f) 
    {
        i ^= f;
        return *this;
    }
    /// \ru Вернуть значение, сохраненное в объекте Flags в виде целого числа. \en Returns integer value saved in Flags object.
    inline operator int() const
    {
        return i;
    }
    /// \ru Вернуть объект Flags, содержащий результат побитовой OR-операции над этим объектом. \en Returns Flags object containing result of bitwise OR-operation on the object.
    inline Flags operator|(Flags f) const 
    {
        return Flags(Enum(i | f.i));
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags operator|(Enum f) const
    {
        return Flags(Enum(i | f));
    }
    /// \ru Вернуть объект Flags, содержащий результат побитовой XOR-операции над этим объектом. \en Returns Flags object containing result of bitwise XOR-operation on the object.
    inline Flags operator^(Flags f) const 
    {
        return Flags(Enum(i ^ f.i));
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags operator^(Enum f) const
    {
        return Flags(Enum(i ^ f));
    }
    /// \ru Вернуть объект Flags, содержащий результат выполнения AND-операции. \en Returns Flags object containing result of AND-operation performed.
    inline Flags operator&(int mask) const
    {
        return Flags(Enum(i & mask));
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags operator&(uint mask) const 
    {
        return Flags(Enum(i & mask));
    }
    /// \ru Это перегруженная функция. \en Оverloaded function.
    inline Flags operator&(Enum f) const 
    {
        return Flags(Enum(i & f));
    }
    /// \ru Вернуть объект Flags, содержащий побитовое отрицание этого объекта. \en Returns Flags object containing bitwise complement of the object.
    inline Flags operator~() const 
    {
        return Flags(Enum(~i));
    }
    /// \ru Вернуть значение True, если флаг установлен (т.е. если значение, хранящееся в Flags объекта, равно 0), в противном случае возвращает False. \en True if flag is set, i.e. if value stored in Flags object is 0, otherwise, False.
    inline bool operator!() const 
    {
        return !i;
    }
    /// \ru Вернуть True, если флаг установлен, в противном случае false. \en True if flag is set.
    inline bool checkFlag(Enum f) const 
    {
        return (i & f) == f && (f != 0 || i == int(f));
    }
private:
    int i;
};

#define VSN_DECLARE_FLAGS(flags, Enum) \
typedef Flags<Enum> flags;

VSN_END_NAMESPACE

#endif // __VSN_FLAGS_H
