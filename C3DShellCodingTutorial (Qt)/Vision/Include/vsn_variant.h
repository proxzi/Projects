////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс Variant имеет реализацию объединения для наиболее распространенных 
               типов данных в Vision и поддерживает фиксированный набор типов.
           \en Variant class implements union of most common data types in Vision
               and supports fixed set of types. \~
*/
////////////////////////////////////////////////////////////////////////////////
#include "vsn_object.h"

#ifndef __VSN_VARIANT_H
#define __VSN_VARIANT_H

#include <map>
#include <mb_cart_point.h>
#include <mb_matrix3d.h>
#include <mb_vector3d.h>
#include <model_item.h>
#include "vsn_size.h"
#include "vsn_nodekey.h"
#include "vsn_rect.h"
#include "vsn_color.h"
#include "vsn_string.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE
class Object;
///< \ru Поддерживаемые типы Variant. \en Supported Variant types.
enum VariantType
{
    VAR_NONE = 0,
    VAR_INT,
    VAR_BOOL,
    VAR_FLOAT,
    VAR_VECTOR2,
    VAR_VECTOR3,
    VAR_VECTOR4,
    VAR_COLOR,
    VAR_STRING,
    VAR_VOIDPTR,
    VAR_OBJECTPTR,
    VAR_VARIANTVECTOR,
    VAR_INTVECTOR,
    VAR_FLOATVECTOR,
    VAR_INTRECT,
    VAR_PTR,
    VAR_SHAREDPTR,
    VAR_MATRIX4,
    VAR_DOUBLE,
    VAR_STRINGVECTOR,
    VAR_MBITEM,
    VAR_NODE_KEY,
    MAX_VAR_TYPES
};

//----------------------------------------------------------------------------
//
/** \brief \ru VariantValue - объединение возможных значений.
           \en VariantValue is a union of possible values. \~
    \ingroup Vision_Common
*/
// ---
struct VariantValue
{
    union
    {
        int int_;
        bool bool_;
        float float_;
        double double_;
        void* ptr_;
    };

    union
    {
        int int2_;
        float float2_;
        double double2_;
        void* ptr2_;
    };

    union
    {
        int int3_;
        float float3_;
        double double3_;
        void* ptr3_;
    };

    union
    {
        int int4_;
        float float4_;
        double double4_;
        void* ptr4_;
    };
};

class Variant;
typedef std::vector<Variant> VariantVector; ///< \ru Вектор вариантов. \en Variant vector.
typedef std::vector<String>  StringVector;  ///< \ru Вектор strings.   \en String vector.
typedef std::vector<int>     IntVector;     ///< \ru Вектор Integer.   \en Integer vector.
typedef std::vector<float>   FloatVector;   ///< \ru Вектор Float.     \en Float vector.

//----------------------------------------------------------------------------
//
/** \brief \ru Класс Variant имеет реализацию объединения для наиболее распространенных 
               типов данных C3D Vision и поддерживает фиксированный набор типов.
           \en Variant class implements union of most common data types in C3D Vision
               and supports fixed set of types. \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS Variant
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    Variant() : m_type(VAR_NONE) {}
    /// \ru Конструктор с integer значением. \en Constructor with integer value. \~
    Variant(int value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с unsigned integer значением. \en Constructor with unsigned integer value. \~
    Variant(unsigned value) : m_type(VAR_NONE) { *this = (int)value; }
    /// \ru Конструктор с bool значением. \en Constructor with bool value. \~
    Variant(bool value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с float значением. \en Constructor with float value. \~
    Variant(float value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с double значением. \en Constructor with double value. \~
    Variant(double value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с MbVector3D значением. \en Constructor with MbVector3D value. \~
    Variant(const MbVector3D& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с NodeKey значением. \en Constructor with NodeKey value. \~
    Variant(const NodeKey& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с MbHomogeneous3D значением. \en Constructor with MbHomogeneous3D value. \~
    Variant(const MbHomogeneous3D& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с Color значением. \en Constructor with Color value. \~
    Variant(const Color& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с String значением. \en Constructor with String value.
    Variant(const String& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с указателем на char значение. \en Constructor with a pointer to char value. \~
    Variant(const char* value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с указателем на MbItem. \en Constructor with a pointer to MbItem. \~
    Variant(MbItem* value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с указателем на void значение. \en Constructor with a pointer to void value. \~
    Variant(void* value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с VariantVector значением. \en Constructor with VariantVector value. \~
    Variant(const VariantVector& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с StringVector значением. \en Constructor with StringVector value. \~
    Variant(const StringVector& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с IntVector значением. \en Constructor with IntVector value. \~
    Variant(const IntVector& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с FloatVector значением. \en Constructor with FloatVector value. \~
    Variant(const FloatVector& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с integer rect значением. \en Constructor with integer rect value. \~
    Variant(const IntRect& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с MbMatrix3D значением. \en Constructor with MbMatrix3D value. \~
    Variant(const MbMatrix3D& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с заданием типа и инициализации значения. \en Constructor with setting type and value initialization. \~
    Variant(const String& type, const String& value) : m_type(VAR_NONE) { FromString(type, value); }
    /// \ru Конструктор с заданием типа и инициализации значения. \en Constructor with setting type and value initialization. \~
    Variant(VariantType type, const String& value) : m_type(VAR_NONE) { FromString(type, value); }
    /// \ru Конструктор с заданием типа и инициализации значения. \en Constructor with setting type and value initialization. \~
    Variant(const char* type, const char* value) : m_type(VAR_NONE) { FromString(type, value); }
    /// \ru Конструктор с заданием типа и инициализации значения. \en Constructor with setting type and value initialization. \~
    Variant(VariantType type, const char* value) : m_type(VAR_NONE) { FromString(type, value); }
    /// \ru Конструктор копирования по другому варианту. \en Copy constructor by another variant. \~
    Variant(const Variant& value) : m_type(VAR_NONE) { *this = value; }
    /// \ru Конструктор с указателем на std::shared_ptr<T> значением. \en Constructor with a pointer to std::shared_ptr<T> value. \~
    template<typename T>
    Variant(std::shared_ptr<T> value) : m_type(VAR_SHAREDPTR) { *this = value; }
    /// \ru Деструктор. \en Destructor. \~
    ~Variant() { SetType(VAR_NONE); }

public:
    /// \ru Очистить вариант от значения и типа. \en Clears variant from value and type. \~
    void Clear() { SetType(VAR_NONE); }
    /// \ru Присвоить значение и тип из другого варианта. \en Assigns value and type from another variant. \~
    Variant& operator =(const Variant& other);
    /// \ru Присвоить значение из integer. \en Assigns value from integer. \~
    Variant& operator =(int other) { SetType(VAR_INT); m_value.int_ = other; return *this; }
    /// \ru Присвоить значение из целых чисел без знака. \en Assigns value from unsighed integer. \~
    Variant& operator =(unsigned other) { SetType(VAR_INT); m_value.int_ = (int)other; return *this; }
    /// \ru Присвоить значение из bool. \en Assigns value from bool. \~
    Variant& operator =(bool other) { SetType(VAR_BOOL); m_value.bool_ = other; return *this; }
    /// \ru Присвоить значение из float. \en Assigns value from float. \~
    Variant& operator =(float other) { SetType(VAR_FLOAT); m_value.float_ = other; return *this; }
    /// \ru Присвоить значение из double. \en Assigns value from double. \~
    Variant& operator = (double other) { SetType(VAR_DOUBLE); *(reinterpret_cast<double*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из MbVector3D. \en Assigns value from MbVector3D. \~
    Variant& operator =(const MbVector3D& other) { SetType(VAR_VECTOR3); *(reinterpret_cast<MbVector3D*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из NodeKey. \en Assigns value from NodeKey. \~
    Variant& operator =(const NodeKey& other) { SetType(VAR_NODE_KEY); *(reinterpret_cast<NodeKey*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из MbHomogeneous3D. \en Assigns value from MbHomogeneous3D. \~
    Variant& operator =(const MbHomogeneous3D& other) { SetType(VAR_VECTOR4); *(reinterpret_cast<MbHomogeneous3D*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из color. \en Assigns value from color. \~
    Variant& operator =(const Color& other) { SetType(VAR_COLOR); *(reinterpret_cast<Color*>(m_value.ptr_)) = other; return *this; }
    /// \ru Присвоить значение из string. \en Assigns value from string. \~
    Variant& operator =(const String& other) { SetType(VAR_STRING); *(reinterpret_cast<String*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из указателя на char. \en Assigns value from pointer to char. \~
    Variant& operator =(const char* other) { SetType(VAR_STRING); *(reinterpret_cast<String*>(&m_value)) = String(other); return *this; }
    /// \ru Назначить значение из адреса указателя на void. \en Sets value from pointer address to void. \~
    Variant& operator =(void* other) { SetType(VAR_VOIDPTR); m_value.ptr_ = other; return *this; }
    /// \ru Назначить значение из адреса указателя на MbItem. \en Sets value from pointer address to MbItem. \~
    Variant& operator =(MbItem* other);
    /// \ru Назначить значение из адреса указателя на Object. \en Sets value from pointer address to Object. \~
    Variant& operator =(Object* other) { SetType(VAR_OBJECTPTR); m_value.ptr_ = other; return *this; }
    /// \ru Назначить значение из вектора вариантов. \en Sets value from variant vector. \~
    Variant& operator =(const VariantVector& other) { SetType(VAR_VARIANTVECTOR); *(reinterpret_cast<VariantVector*>(&m_value)) = other; return *this; }
    /// \ru Назначить значение из вектора string. \en Sets value from string vector. \~
    Variant& operator =(const StringVector& other) { SetType(VAR_STRINGVECTOR); *(reinterpret_cast<StringVector*>(&m_value)) = other; return *this; }
    /// \ru Назначить значение из вектора вариантов. \en Sets value from variant vector. \~
    Variant& operator =(const IntVector& other) { SetType(VAR_INTVECTOR); *(reinterpret_cast<IntVector*>(&m_value)) = other; return *this; }
    /// \ru Назначить значение из вектора вариантов. \en Sets value from variant vector. \~
    Variant& operator =(const FloatVector& other) { SetType(VAR_FLOATVECTOR); *(reinterpret_cast<FloatVector*>(&m_value)) = other; return *this; }
    /// \ru Присвоить значение из целочисленного прямоугольника. \en Assigns value from integer rectangle. \~
    Variant& operator =(const IntRect& other) { SetType(VAR_INTRECT); *(reinterpret_cast<IntRect*>(&m_value)) = other; return *this;}
    /// \ru Присвоить значение из MbMatrix3D. \en Assigns value from MbMatrix3D. \~
    Variant& operator =(const MbMatrix3D& other) { SetType(VAR_MATRIX4); *(reinterpret_cast<MbMatrix3D*>(m_value.ptr_)) = other; return *this; }
    /// \ru Присвоить значение из std::shared_ptr<T>. \en Assigns value from std::shared_ptr<T>. \~
    template<typename T> Variant& operator =(std::shared_ptr<T> other) { SetType(VAR_SHAREDPTR); sptr_ = std::static_pointer_cast<void>(other); return *this; }

    /// \ru Проверить равенство с другим вариантом. Вернет true, если вариант равен этому.
    /// \en Checks equality with another variant. Returns true if variant is equal to this one. \~
    bool operator ==(const Variant& other) const;
    /// \ru Проверить равенство с целым числом. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with integer. Returns true if there is coincidence of type and value. \~
    bool operator ==(int other) const { return m_type == VAR_INT ? m_value.int_ == other : false; }
    /// \ru Проверить равенство с целым числом без знака. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with unsigned integer. Returns true if there is coincidence of type and value. \~
    bool operator ==(unsigned other) const { return m_type == VAR_INT ? m_value.int_ == (int)other : false; }
    /// \ru Проверить равенство с bool. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with bool. Returns true if there is coincidence of type and value. \~
    bool operator ==(bool other) const { return m_type == VAR_BOOL ? m_value.bool_ == other : false; }
    /// \ru Проверить равенство с float. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with float. Returns true if there is coincidence of type and value. \~
    bool operator ==(float other) const { return m_type == VAR_FLOAT ? m_value.float_ == other : false; }
    /// \ru Проверить равенство с double. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with double. Returns true if there is coincidence of type and value. \~
    bool operator ==(double other) const { return m_type == VAR_DOUBLE ? *(reinterpret_cast<const double*>(&m_value)) == other : false; }
    /// \ru Проверить равенство с MbVector3D. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with MbVector3D. Returns true if there is coincidence of type and value. \~
    bool operator ==(const MbVector3D& other) const { return m_type == VAR_VECTOR3 ? *(reinterpret_cast<const MbVector3D*>(&m_value)) == other : false; }
    /// \ru Проверить равенство с NodeKey. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with NodeKey. Returns true if there is coincidence of type and value. \~
    bool operator ==(const NodeKey& other) const { return m_type == VAR_NODE_KEY ? *(reinterpret_cast<const NodeKey*>(&m_value)) == other : false; }
    /// \ru Проверить равенство с MbHomogeneous3D. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with MbHomogeneous3D. Returns true if there is coincidence of type and value. \~
    bool operator ==(const MbHomogeneous3D& other) const { return m_type == VAR_VECTOR4 ? *(reinterpret_cast<const MbHomogeneous3D*>(&m_value)) == other : false; }
    /// \ru Проверить равенство с color. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with color. Returns true if there is coincidence of type and value. \~
    bool operator ==(const Color& other) const { return m_type == VAR_COLOR ? *(reinterpret_cast<const Color*>(&m_value.ptr_)) == other : false; }
    /// \ru Проверить равенство с string. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with string. Returns true if there is coincidence of type and value. \~
    bool operator ==(const String& other) const { return m_type == VAR_STRING ? *(reinterpret_cast<const String*>(&m_value)) == other : false; }
    /// \ru Проверить равенство с указателем на void. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with pointer to void. Returns true if there is coincidence of type and value. \~
    bool operator ==(void* other) const { if (m_type == VAR_VOIDPTR) return m_value.ptr_ == other; else return false; }
    /// \ru Проверить равенство с указателем на void. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with pointer to MbItem. Returns true if there is coincidence of type and value. \~
    bool operator ==(MbItem* other) const { if (m_type == VAR_MBITEM) return m_value.ptr_ == other; else return false; }
    /// \ru Проверить равенство с указателем на Object. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with pointer to Object. Returns true if there is coincidence of type and value. \~
    bool operator ==(Object* other) const { if (m_type == VAR_OBJECTPTR) return m_value.ptr_ == other; else return false; }
    /// \ru Проверка на равенство с вариантным вектором. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with variant vector. Returns true if there is coincidence of type and value. \~
    bool operator ==(const VariantVector& other) const
    { return m_type == VAR_VARIANTVECTOR ? *(reinterpret_cast<const VariantVector*>(&m_value)) == other : false; }
    /// \ru Проверка на равенство со строковым вектором. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with string vector. Returns true if there is coincidence of type and value. \~
    bool operator ==(const StringVector& other) const
    { return m_type == VAR_STRINGVECTOR ? *(reinterpret_cast<const StringVector*>(&m_value)) == other : false; }
    /// \ru Проверка на равенство с Integer вектором. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with integer vector. Returns true if there is coincidence of type and value. \~
    bool operator ==(const IntVector& other) const { return m_type == VAR_INTVECTOR ? *(reinterpret_cast<const IntVector*>(&m_value)) == other : false; }
    /// \ru Проверка на равенство с Float вектором. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with float vector. Returns true if there is coincidence of type and value. \~
    bool operator ==(const FloatVector& other) const { return m_type == VAR_FLOATVECTOR ? *(reinterpret_cast<const FloatVector*>(&m_value)) == other : false; }
    /// \ru Проверка на равенство с целочисленным прямоугольником. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with integer rectangle. Returns true if there is coincidence of type and value. \~
    bool operator ==(const IntRect& other) const { return m_type == VAR_INTRECT ? *(reinterpret_cast<const IntRect*>(&m_value)) == other : false; }
    /// \ru Проверка на равенство с MbMatrix3D. Вернет true, если есть совпадение по типу и значению.
    /// \en Checks equality with MbMatrix3D. Returns true if there is coincidence of type and value. \~
    bool operator ==(const MbMatrix3D& other) const { return m_type == VAR_MATRIX4 ? *(reinterpret_cast<const MbMatrix3D*>(m_value.ptr_)) == other : false; }

    /// \ru Проверка неравенства с другим вариантом. \en Checks inequality with another variant. \~
    bool operator !=(const Variant& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с целым числом. \en Checks inequality with integer. \~
    bool operator !=(int other) const { return !(*this == other); }
    /// \ru Проверка неравенства с целым числом без знака. \en Checks inequality with unsigned integer. \~
    bool operator !=(unsigned other) const { return !(*this == other); }
    /// \ru Проверка неравенства с bool. \en Checks inequality with bool. \~
    bool operator !=(bool other) const { return !(*this == other); }
    /// \ru Проверка неравенства с float. \en Checks inequality with float. \~
    bool operator !=(float other) const { return !(*this == other); }
    /// \ru Проверка неравенства с double. \en Checks inequality with double. \~
    bool operator !=(double other) const { return !(*this == other); }
    /// \ru Проверка неравенства с MbVector3D. \en Checks inequality with MbVector3D. \~
    bool operator !=(const MbVector3D& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с NodeKey. \en Checks inequality with NodeKey. \~
    bool operator !=(const NodeKey& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с MbHomogeneous3D. \en Checks inequality with MbHomogeneous3D. \~
    bool operator !=(const MbHomogeneous3D& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с string. \en Checks inequality with string. \~
    bool operator !=(const String& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с указателем на void. \en Checks inequality with pointer to void. \~
    bool operator !=(void* other) const { return !(*this == other); }
    /// \ru Проверка неравенства с указателем на MbItem. \en Checks inequality with pointer to MbItem. \~
    bool operator !=(MbItem* other) const { return !(*this == other); }
    /// \ru Проверка неравенства с вектором вариантов. \en Checks inequality with variant vector. \~
    bool operator !=(const VariantVector& other) const { return !(*this == other); }
    /// \ru Проверка неравенства со строковым вектором. \en Checks inequality with string vector. \~
    bool operator !=(const StringVector& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с integer  вектором. \en Checks inequality with integer vector. \~
    bool operator !=(const IntVector& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с float  вектором. \en Checks inequality with float vector. \~
    bool operator !=(const FloatVector& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с Variant Map. \en Checks inequality with Variant Map. \~
//    bool operator !=(const VariantMap& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с целочисленным прямоугольником. \en Checks inequality with integer rectangle. \~
    bool operator !=(const IntRect& other) const { return !(*this == other); }
    /// \ru Проверка неравенства с MbMatrix3D. \en Checks inequality with MbMatrix3D. \~
    bool operator !=(const MbMatrix3D& other) const { return !(*this == other); }

    /// \ru Установить из строки тип и значение. Указатели будут установлены в нуль, а тип VariantMap не поддерживается.
    /// \en Sets type and value from a string. Pointers will be set to 0 and VariantMap type is not supported. \~
    void FromString(const String& type, const String& value);
    /// \ru Установить из строковых символов и строк значений. Указатели будут установлены в нуль, а тип VariantMap не поддерживается.
    /// \en Sets from a string chars and string values. Pointers will be set to 0 and VariantMap type is not supported. \~
    void FromString(const char* type, const char* value);
    /// \ru Установить из типа и строки. Указатели будут установлены в нуль, а тип VariantMap не поддерживается.
    /// \en Sets from type and string. Pointers will be set to 0 and VariantMap type is not supported. \~
    void FromString(VariantType type, const String& value);
    /// \ru Установить из типа и строки. Указатели будут установлены в нуль, а тип VariantMap не поддерживается.
    /// \en Sets from type and string. Pointers will be set to 0 and VariantMap type is not supported. \~
    void FromString(VariantType type, const char* value);

    /// \ru Возвращает int или нуль при несоответствии типа. Floats и doubles конвертирует. \en Returns integer or 0 if type mismatch. Floats and doubles are converted. \~
    int GetInt() const
    {
        if (m_type == VAR_INT)
            return m_value.int_;
        else if (m_type == VAR_FLOAT)
            return (int)m_value.float_;
        else if (m_type == VAR_DOUBLE)
            return (int)*reinterpret_cast<const double*>(&m_value);
        else
            return 0;
    }

    /// \ru Возвращает целое число без знака или ноль при несоответствии типа. Floats и doubles конвертирует. \en Returns unsigned integer or 0 if type mismatch. Floats and doubles are converted. \~
    unsigned GetUInt() const
    {
        if (m_type == VAR_INT)
            return m_value.int_;
        else if (m_type == VAR_FLOAT)
            return (unsigned)m_value.float_;
        else if (m_type == VAR_DOUBLE)
            return (unsigned)*reinterpret_cast<const double*>(&m_value);
        else
            return 0;
    }

    /// \ru Возвращает bool или false при несоответствии типа. \en Returns bool or false if type mismatch. \~
    bool GetBool() const { return m_type == VAR_BOOL ? m_value.bool_ : false; }

    /// \ru Вернуть float или ноль при несоответствии типа. \en Returns float or 0 if type mismatch. \~
    float GetFloat() const
    {
        if (m_type == VAR_FLOAT)
            return m_value.float_;
        else if (m_type == VAR_DOUBLE)
            return (float)*reinterpret_cast<const double*>(&m_value);
        else if (m_type == VAR_INT)
            return (float)m_value.int_;
        else
            return 0.0f;
    }

    /// \ru Вернуть double или ноль при несоответствии типа. \en Returns double or 0 if type mismatch. \~
    double GetDouble() const
    {
        if (m_type == VAR_DOUBLE)
            return *reinterpret_cast<const double*>(&m_value);
        else if (m_type == VAR_FLOAT)
            return (double)m_value.float_;
        else if (m_type == VAR_INT)
            return (double)m_value.int_;
        else
            return 0.0;
    }

    /// \ru Вернуть MbVector3D или ноль при несоответствии типа. \en Returns MbVector3D or 0 if type mismatch. \~
    const MbVector3D& GetVector3() const
    { return m_type == VAR_VECTOR3 ? *reinterpret_cast<const MbVector3D*>(&m_value) : MbVector3D::zero; }
    /// \ru Вернуть NodeKey или ноль при несоответствии типа. \en Returns NodeKey or 0 if type mismatch. \~
    const NodeKey& GetNodeKey() const { return m_type == VAR_NODE_KEY ? *reinterpret_cast<const NodeKey*>(&m_value) : NodeKey::ZERO; }
    /// \ru Вернуть MbHomogeneous3D или ноль при несоответствии типа. \en Returns MbHomogeneous3D or 0 if type mismatch. \~
    const MbHomogeneous3D& GetVector4() const { return m_type == VAR_VECTOR4 ? *reinterpret_cast<const MbHomogeneous3D*>(&m_value) : MbHomogeneous3D::zero; }
    /// \ru Вернуть color или просто белый цвет при несоответствии типа. \en Returns color or just white color if type mismatch. \~
    const Color& GetColor() const { return (m_type == VAR_COLOR || m_type == VAR_VECTOR4) ? *reinterpret_cast<const Color*>(m_value.ptr_) : Color::DEFINE_WHITE; }
    /// \ru Вернуть строку или пустую строку при несоответствии типа. \en Returns string or empty string if type mismatch. \~
    const String& GetString() const { return m_type == VAR_STRING ? *reinterpret_cast<const String*>(&m_value) : String::EMPTY; }
    /// \ru Вернуть указатель на void или на null при несоответствии типа. \en Returns pointer to void or null if type mismatch. \~
    void* GetVoidPtr() const { return m_type == VAR_VOIDPTR ? m_value.ptr_ : nullptr; }
    /// \ru Вернуть указатель на MbItem или на null при несоответствии типа. \en Returns pointer to void or null if type mismatch. \~
    MbItem* GetMbItemPtr() const { return m_type == VAR_MBITEM ? (MbItem*)m_value.ptr_ : nullptr; }
    /// \ru Вернуть указатель на Object или на null при несоответствии типа. \en Returns pointer to Object or null if type mismatch. \~
    Object* GetObjectPtr() const { return m_type == VAR_OBJECTPTR ? (Object*)m_value.ptr_ : nullptr; }
    /// \ru Вернуть вектор вариантов или пустой вектор, если тип не соответствует. \en Returns variant vector or empty vector if type mismatch. \~
    const VariantVector& GetVariantVector() const { return m_type == VAR_VARIANTVECTOR ? *reinterpret_cast<const VariantVector*>(&m_value) : emptyVariantVector; }
    /// \ru Вернуть строковый вектор или пустой вектор, если тип не соответствует. \en Returns string vector or empty vector if type mismatch. \~
    const StringVector& GetStringVector() const { return m_type == VAR_STRINGVECTOR ? *reinterpret_cast<const StringVector*>(&m_value) : emptyStringVector; }
    /// \ru Вернуть Float вектор или пустой вектор, если тип не соответствует. \en Returns Float vector or empty vector if type mismatch. \~
    const IntVector& GetIntVector() const { return m_type == VAR_INTVECTOR ? *reinterpret_cast<const IntVector*>(&m_value) : emptyIntVector; }
    /// \ru Вернуть Float вектор или пустой вектор, если тип не соответствует. \en Returns Float vector or empty vector if type mismatch. \~
    const FloatVector& GetFloatVector() const { return m_type == VAR_FLOATVECTOR ? *reinterpret_cast<const FloatVector*>(&m_value) : emptyFloatVector; }
    /// \ru Вернуть целочисленный прямоугольник или пустой прямоугольник, если тип не соответствует. \en Returns integer rectangle or empty rectangle if type mismatch. \~
    const IntRect& GetIntRect() const { return m_type == VAR_INTRECT ? *reinterpret_cast<const IntRect*>(&m_value) : IntRect::ZERO; }
    /// \ru Вернуть MbMatrix3D или единичную матрицу, если тип не соответствует. \en Returns MbMatrix3D or unitary matrix if type mismatch. \~
    const MbMatrix3D& GetMatrix4() const { return m_type == VAR_MATRIX4 ? *(reinterpret_cast<const MbMatrix3D*>(m_value.ptr_)) : MbMatrix3D::identity; }
    /// \ru Вернуть указатель на void или пустой указатель, если тип не соответствует. \en Returns pointer to void or empty pointer if type mismatch. \~
    const std::shared_ptr<void> GetSharedPtr() const { return m_type == VAR_SHAREDPTR ? sptr_ : std::shared_ptr<void>(); }

    /// \ru Вернуть тип варианта. \en Returns variant type. \~
    VariantType GetType() const { return m_type; }
    /// \ru Вернуть имя типа варианта. \en Returns variant type name. \~
    String GetTypeName() const;
    /// \ru Преобразование значения в строку. Указатели возвращаются как null, а VariantMap не поддерживается и возвращается пустым.
    /// \en Converts a value to string. Pointers are returned as null, and VariantMap is not supported, and returned as empty. \~
    String ToString() const;
    /// \ru Вернуть true, когда значение варианта считается нулевым в соответствии с его фактическим типом.
    /// \en Returns true, when variant value is 0 in conformance with its actual type. \~
    bool IsZero() const;
    /// \ru Вернуть true, когда вариант пуст (т. е. еще не инициализирован). \en Returns true, when variant is empty, i.e. isn't initialized yet. \~
    bool IsEmpty() const { return m_type == VAR_NONE; }
    /// \ru Вернуть значение шаблонной версии. \en Returns value of pattern version. \~
    template <class T> T Get() const;

    /// \ru Возвращает указатель на изменяемый вариант вектора или null при несоответствии типов. \en Returns pointer to modified variant of vector or null if type mismatch. \~
    VariantVector* GetVariantVectorPtr() { return m_type == VAR_VARIANTVECTOR ? reinterpret_cast<VariantVector*>(&m_value) : 0; }
    /// \ru Возвращает указатель на изменяемый вектор строки или null при несоответствии типов. \en Returns pointer to modified string vector or null if type mismatch. \~
    StringVector* GetStringVectorPtr() { return m_type == VAR_STRINGVECTOR ? reinterpret_cast<StringVector*>(&m_value) : 0; }
    /// \ru Возвращает указатель на изменяемый вариант integer или null при несоответствии типов. \en Returns pointer to modified integer variant or null if type mismatch. \~
    IntVector* GetIntVectorPtr() { return m_type == VAR_INTVECTOR ? reinterpret_cast<IntVector*>(&m_value) : 0; }
    /// \ru Возвращает указатель на изменяемый вариант float или null при несоответствии типов. \en Returns pointer to modified float variant or null if type mismatch. \~
    FloatVector* GetFloatVectorPtr() { return m_type == VAR_FLOATVECTOR ? reinterpret_cast<FloatVector*>(&m_value) : 0; }

    /// \ru Вернуть имя для типа варианта. \en Returns name for variant type. \~
    static String GetTypeName(VariantType type);
    /// \ru Вернуть тип варианта по типу имени. \en Returns variant type by name type. \~
    static VariantType GetTypeFromName(const String& typeName);
    /// \ru Вернуть тип варианта по типу имени. \en Returns variant type by name type. \~
    static VariantType GetTypeFromName(const wchar_t* typeName);

    static const Variant EMPTY;                    ///< \ru Пустой вариант. \en Empty variant. \~
    static const VariantVector emptyVariantVector; ///< \ru Пустой вектор варианта. \en Empty variant vector. \~
    static const StringVector emptyStringVector;   ///< \ru Пустой вектор строк. \en Empty string vector. \~
    static const IntVector emptyIntVector;         ///< \ru Пустой вектор integer. \en Empty integer vector. \~
    static const FloatVector emptyFloatVector;     ///< \ru Пустой вектор float. \en Empty float vector. \~
private:
    /// \ru Установить новый тип и выделить или освободить память по мере необходимости. \en Sets new type and allocates or frees up memory, as necessary. \~
    void SetType(VariantType newType);
private:
    std::shared_ptr<void> sptr_;
    VariantType m_type;   ///< \ru Тип варианта. \en Variant type.
    VariantValue m_value; ///< \ru Значение варианта. \en Variant value.
};

/// \ru Вернуть тип варианта. \en Returns variant type.
template <typename T> VariantType GetVariantType();

/// \ru Вернуть тип варианта по заданному конкретному типу. \en Returns variant type by defined specific type.
template <> inline VariantType GetVariantType<int>()                { return VAR_INT; }
template <> inline VariantType GetVariantType<unsigned>()           { return VAR_INT; }
template <> inline VariantType GetVariantType<bool>()               { return VAR_BOOL; }
template <> inline VariantType GetVariantType<float>()              { return VAR_FLOAT; }
template <> inline VariantType GetVariantType<double>()             { return VAR_DOUBLE; }
template <> inline VariantType GetVariantType<MbVector3D>()         { return VAR_VECTOR3; }
template <> inline VariantType GetVariantType<NodeKey>()            { return VAR_NODE_KEY; }
template <> inline VariantType GetVariantType<MbHomogeneous3D>()    { return VAR_VECTOR4; }
template <> inline VariantType GetVariantType<Color>()              { return VAR_COLOR; }
template <> inline VariantType GetVariantType<String>()             { return VAR_STRING; }
template <> inline VariantType GetVariantType<VariantVector>()      { return VAR_VARIANTVECTOR; }
template <> inline VariantType GetVariantType<StringVector>()       { return VAR_STRINGVECTOR; }
template <> inline VariantType GetVariantType<IntVector>()          { return VAR_INTVECTOR; }
template <> inline VariantType GetVariantType<FloatVector>()        { return VAR_FLOATVECTOR; }
template <> inline VariantType GetVariantType<IntRect>()            { return VAR_INTRECT; }
template <> inline VariantType GetVariantType<MbMatrix3D>()         { return VAR_MATRIX4; }

// Специализация для Variant::Get<T>
template <> int                     Variant::Get<int>() const;
template <> unsigned                Variant::Get<unsigned>() const;
template <> bool                    Variant::Get<bool>() const;
template <> float                   Variant::Get<float>() const;
template <> double                  Variant::Get<double>() const;
template <> const MbVector3D&       Variant::Get<const MbVector3D&>() const;
template <> const NodeKey&          Variant::Get<const NodeKey&>() const;
template <> const MbHomogeneous3D&  Variant::Get<const MbHomogeneous3D&>() const;
template <> const Color&            Variant::Get<const Color&>() const;
template <> const String&           Variant::Get<const String&>() const;
template <> const IntRect&          Variant::Get<const IntRect&>() const;
template <> void*                   Variant::Get<void*>() const;
template <> MbItem*                 Variant::Get<MbItem*>() const;
template <> const MbMatrix3D&       Variant::Get<const MbMatrix3D&>() const;
template <> VariantVector           Variant::Get<VariantVector>() const;
template <> StringVector            Variant::Get<StringVector>() const;
template <> IntVector               Variant::Get<IntVector>() const;
template <> FloatVector             Variant::Get<FloatVector>() const;
template <> MbVector3D              Variant::Get<MbVector3D>() const;
template <> NodeKey                 Variant::Get<NodeKey>() const;
template <> MbHomogeneous3D         Variant::Get<MbHomogeneous3D>() const;
template <> Color                   Variant::Get<Color>() const;
template <> String                  Variant::Get<String>() const;
template <> IntRect                 Variant::Get<IntRect>() const;
template <> MbMatrix3D              Variant::Get<MbMatrix3D>() const;

VSN_END_NAMESPACE

#endif // __VSN_VARIANT_H
