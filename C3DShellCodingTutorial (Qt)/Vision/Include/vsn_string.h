////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Общий класс строк на основе стандарта Unicode.
           \en General String class based on Unicode standard.  \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_STRING_H
#define __VSN_STRING_H

#include <string>
#include <vector>
#include <list>
#include "vsn_iterator.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE


//------------------------------------------------------------------------------
/** \brief   \ru 8-битный char array с завершающим нулем.
             \en 8 bit zero terminated char array. \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS CharArray
{
public:
    CharArray();
    CharArray(size_t size, char c);
    explicit CharArray(const char* str);

public:
    CharArray GetLeft(int len)  const;
    CharArray Mid(int pos, int len = -1) const;
    bool StartsWith(const char *str) const;
    int IndexOf(const char *c, int from = 0) const;
    int IndexOf(char ch, int from = 0) const;
    std::list<CharArray> Split(char sep) const;

    char&       operator[](size_t i);
    const char& operator[](size_t i) const;

    void        resize(size_t size);
    void        push_back(char c);
    size_t      size() const;
    void        Clear();

    const char* ptr() const;
    char*       ptr();

protected:
    std::vector<char> m_data;
};

inline void CharArray::Clear()
{
    m_data.clear();
}

static const int CONVERSION_BUFFER_LENGTH = 128;
static const int MATRIX_CONVERSION_BUFFER_LENGTH = 256;

class WString;
//------------------------------------------------------------------------------
/** \brief   \ru Общий класс строк на основе стандарта Unicode.
             \en General String class based on Unicode standard. \~
        \details \ru Класс String поддерживает преобразование в/из std::string, std::wstring, const char*, const wchar_t*.
                     Отдельный класс CharArray используется для поддержки метода ToAscii () (преобразование
                     в const char* string). \n
                 \en The String class supports conversion to and from std::string, std::wstring, const char*, const wchar_t*.
                     A separate CharArray class is used to support the ToAscii() method for conversion
                     to a const char* string. \n \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS String
{
public:
    typedef RandomAccessIterator<char> Iterator;
    typedef RandomAccessConstIterator<char> ConstIterator;

    /// \ru Конструктор по умолчанию. Создает пустой String. \en Default constructor creating an empty String.
    String();
    /// \ru Конструктор копирования из другого объекта String. \en Copy constructor from another String object.
    String(const String& str);
    /// \ru Конструктор по заданному указателю на const char. \en Constructor by defined pointer to const char.
    String(const char* str);
    /// \ru Конструктор по заданному указателю на char. \en Constructor by defined pointer to char.
    String(char* str);
    /// \ru Конструктор по заданному указателю на const char и заданной длине. \en Constructor by defined pointer to const char and by length.
    String(const char* str, unsigned length);
    /// \ru Конструктор по заданному указателю на const wchar_t с null-terminated. \en Constructor by defined pointer to null-terminated const wchar_t.
    String(const wchar_t* str);
    /// \ru Конструктор по заданному указателю на wchar_t с null-terminated. \en Constructor by defined pointer to null-terminated wchar_t.
    String(wchar_t* str);
    /// \ru Конструктор по WString. \en Constructor by WString.
    String(const WString& str);

    /// \ru Конструктор по integer. \en Constructor by integer.
    explicit String(int value);
    /// \ru Конструктор по short integer. \en Constructor by short integer.
    explicit String(short value);
    /// \ru Конструктор по long integer. \en Constructor by long integer.
    explicit String(long value);
    /// \ru Конструктор по long long integer. \en Constructor by long long integer.
    explicit String(long long value);
    /// \ru Конструктор по unsigned integer. \en Constructor by unsigned integer.
    explicit String(unsigned value);
    /// \ru Конструктор по unsigned short integer. \en Constructor by unsigned short integer.
    explicit String(unsigned short value);
    /// \ru Конструктор по unsigned long integer. \en Constructor by unsigned long integer.
    explicit String(unsigned long value);
    /// \ru Конструктор по unsigned long long integer. \en Constructor by unsigned long long integer.
    explicit String(unsigned long long value);
    /// \ru Конструктор по float. \en Constructor by float.
    explicit String(float value);
    /// \ru Конструктор по double. \en Constructor by double.
    explicit String(double value);
    /// \ru Конструктор по bool. \en Constructor by bool.
    explicit String(bool value);
    /// \ru Конструктор по character. \en Constructor by character.
    explicit String(char value);
    /// \ru Конструктор по character и длине. \en Constructor by character and length.
    explicit String(char value, unsigned length);

    /// \ru Конструктор по произвольному типу. \en Constructor by arbitrary type.
    template <class T> explicit String(const T& value) 
        : m_length(0)
        , m_capacity(0)
        , m_buffer(&m_endZero)
    {
        *this = value.ToString();
    }

    /// \ru Деструктор. \en Destructor.
    ~String();

    /// \ru Присвоить String. \en Assigns String.
    String& operator =(const String& rhs)
    {
        Resize(rhs.m_length);
        CopyChars(m_buffer, rhs.m_buffer, rhs.m_length);
        return *this;
    }

    /// \ru Присвоить указанный указатель на const char. \en Assigns the specified pointer to const char.
    String& operator =(const char* rhs)
    {
        unsigned rhsLength = CStringLength(rhs);
        Resize(rhsLength);
        CopyChars(m_buffer, rhs, rhsLength);
        return *this;
    }

    /// \ru Присвоить и добавить указанный String. \en Assigns and add the specified String.
    String& operator +=(const String& rhs)
    {
        unsigned oldLength = m_length;
        Resize(m_length + rhs.m_length);
        CopyChars(m_buffer + oldLength, rhs.m_buffer, rhs.m_length);
        return *this;
    }

    /// \ru Присвоить и добавить указанный указатель на const char. \en Assigns and adds the specified ponter to const char.
    String& operator +=(const char* rhs)
    {
        unsigned rhsLength = CStringLength(rhs);
        unsigned oldLength = m_length;
        Resize(m_length + rhsLength);
        CopyChars(m_buffer + oldLength, rhs, rhsLength);
        return *this;
    }

    /// \ru Присвоить и добавить указанный символ. \en Assigns and adds the specified char.
    String& operator +=(char rhs)
    {
        unsigned oldLength = m_length;
        Resize(m_length + 1);
        m_buffer[oldLength] = rhs;
        return *this;
    }

    /// \ru Присвоить и добавить integer (конкатенировать как строку). \en Assigns and adds integer, with concatenation as a string.
    String& operator +=(int rhs);
    /// \ru Присвоить и добавить short integer(конкатенировать как строку). \en Assigns and adds short integer, with concatenation as a string.
    String& operator +=(short rhs);
    /// \ru Присвоить и добавить long integer(конкатенировать как строку). \en Assigns and adds long integer, with concatenation as a string.
    String& operator +=(long rhs);
    /// \ru Присвоить и добавить long long integer(конкатенировать как строку). \en Assigns and adds long long integer, with concatenation as a string.
    String& operator +=(long long rhs);
    /// \ru Присвоить и добавить unsigned integer(конкатенировать как строку). \en Assigns and adds unsigned integer, with concatenation as a string.
    String& operator +=(unsigned rhs);
    /// \ru Присвоить и добавить unsigned unsigned integer(конкатенировать как строку). \en Assigns and adds unsigned unsigned integer, with concatenation as a string.
    String& operator +=(unsigned short rhs);
    /// \ru Присвоить и добавить unsigned long unsigned integer(конкатенировать как строку). \en Assigns and adds unsigned long unsigned integer, with concatenation as a string.
    String& operator +=(unsigned long rhs);
    /// \ru Присвоить и добавить long long unsigned integer(конкатенировать как строку). \en Assigns and adds long long unsigned integer, with concatenation as a string.
    String& operator +=(unsigned long long rhs);
    /// \ru Присвоить и добавить float(конкатенировать как строку). \en Assigns and adds float, with concatenation as a string.
    String& operator +=(float rhs);
    /// \ru Присвоить и добавить bool(конкатенировать как строку). \en Assigns and adds bool, with concatenation as a string.
    String& operator +=(bool rhs);

    /// \ru Присвоить и добавить произвольный тип(конкатенировать как строку). \en Assigns and adds arbitrary type, with concatenation as a string.
    template <class T> String operator +=(const T& rhs) { return *this += rhs.ToString(); }

    /// \ru Добавить String. \en Adds String.
    String operator +(const String& rhs) const
    {
        String ret;
        ret.Resize(m_length + rhs.m_length);
        CopyChars(ret.m_buffer, m_buffer, m_length);
        CopyChars(ret.m_buffer + m_length, rhs.m_buffer, rhs.m_length);
        return ret;
    }

    /// \ru Добавить массив const char. \en Adds const char array.
    String operator +(const char* rhs) const
    {
        unsigned rhsLength = CStringLength(rhs);
        String ret;
        ret.Resize(m_length + rhsLength);
        CopyChars(ret.m_buffer, m_buffer, m_length);
        CopyChars(ret.m_buffer + m_length, rhs, rhsLength);
        return ret;
    }

    /// \ru Проверить равенство с другой строкой. \en Checks equality to another string.
    bool operator ==(const String& rhs) const { return strcmp(c_str(), rhs.c_str()) == 0; }

    /// \ru Проверить неравенство с другой строкой. \en Checks inequality to another string.
    bool operator !=(const String& rhs) const { return strcmp(c_str(), rhs.c_str()) != 0; }

    /// \ru Проверить, что строка меньше другой строки. \en Checks if string is less than another string.
    bool operator <(const String& rhs) const { return strcmp(c_str(), rhs.c_str()) < 0; }

    /// \ru Проверить, что строка больше другой строки. \en Checks if string is more than another string.
    bool operator >(const String& rhs) const { return strcmp(c_str(), rhs.c_str()) > 0; }

    /// \ru Проверить соответствие со строкой const char. \en Checks conformance to const char string.
    bool operator ==(const char* rhs) const { return strcmp(c_str(), rhs) == 0; }

    /// \ru Проверить неравенство указанного массива. \en Checks inequality of specified array.
    bool operator !=(const char* rhs) const { return strcmp(c_str(), rhs) != 0; }

    /// \ru Проверить, что строка меньше строки const char. \en Checks if string is less than const char string.
    bool operator <(const char* rhs) const { return strcmp(c_str(), rhs) < 0; }

    /// \ru Проверить, что строка больше строки const char. \en Checks if string is more than const char string.
    bool operator >(const char* rhs) const { return strcmp(c_str(), rhs) > 0; }
        
    inline bool operator>=(String s) const { return !operator<(s); }

    /// \ru Вернуть символ по индексу. \en Returns char by index.
    char& operator [](unsigned index);

    /// \ru Вернуть const символ по индексу. \en Returns const char by index.
    const char& operator [](unsigned index) const;

    /// \ru Вернуть символ по индексу. \en Returns char by index.
    char& At(unsigned index);
    /// \ru Вернуть const символ по индексу. \en Returns const char by index.
    const char& At(unsigned index) const;

    /// \ru Заменить все вхождения символа. \en Replaces all occurrences of char.
    void Replace(char replaceThis, char replaceWith, bool caseSensitive = true);
    /// \ru Заменить все вхождения указанных строк. \en Replaces all occurrences of specified strings.
    void Replace(const String& replaceThis, const String& replaceWith, bool caseSensitive = true);
    /// \ru Заменить подстроку. \en Replaces substring.
    void Replace(unsigned pos, unsigned length, const String& replaceWith);
    /// \ru Заменить подстроку по указателю const char. \en Replaces substring by const char pointer.
    void Replace(unsigned pos, unsigned length, const char* replaceWith);
    /// \ru Заменить подстроку по итератору. \en Replaces substring by iterator.
    Iterator Replace(const Iterator& start, const Iterator& end, const String& replaceWith);
    /// \ru Вернуть строку со всеми входящими символами. \en Returns string with all occurred chars.
    String Replaced(char replaceThis, char replaceWith, bool caseSensitive = true) const;
    /// \ru Вернуть строку со всеми входящими строками. \en Returns string with all occurred strings.
    String Replaced(const String& replaceThis, const String& replaceWith, bool caseSensitive = true) const;
    /// \ru Добавить указанную строку. \en Adds specified string.
    String& Append(const String& str);
    /// \ru Добавить указанный массив const char. \en Adds specified const char array.
    String& Append(const char* str);
    /// \ru Добавить указанный символ. \en Adds specified char.
    String& Append(char c);
    /// \ru Добавить указанный массив const char определенной длины. \en Adds specified const char array of defined length.
    String& Append(const char* str, unsigned length);
    /// \ru Вставить строку в указанную позицию. \en Inserts string to specified position.
    void Insert(unsigned pos, const String& str);
    /// \ru Вставить символ в указанную позицию. \en Inserts char to specified position.
    void Insert(unsigned pos, char c);
    /// \ru Вставить строку по итератору. \en Inserts string by iterator.
    Iterator Insert(const Iterator& dest, const String& str);
    /// \ru Вставить строку частично с помощью итератора. \en Inserts string particularly by iterator.
    Iterator Insert(const Iterator& dest, const Iterator& start, const Iterator& end);
    /// \ru Вставить символ по итератору. \en Inserts char by iterator.
    Iterator Insert(const Iterator& dest, char c);
    /// \ru Удалить символ. \en Removes char.
    void Remove(char c);
    /// \ru Стереть указанную позицию определенной длины. \en Erases specified position of defined length.
    void Erase(unsigned pos, unsigned length = 1);
    /// \ru Стереть символ по итератору. \en Erases char by iterator.
    Iterator Erase(const Iterator& it);
    /// \ru Стереть символы по итераторам. \en Erases chars by iterators.
    Iterator Erase(const Iterator& start, const Iterator& end);
    /// \ru Изменить размер строки. \en Changes string size.
    void Resize(unsigned newLength);
    /// \ru Установить новый запас по символам. \en Sets new char capacity.
    void Reserve(unsigned newCapacity);
    /// \ru Перераспределить память. \en Compacts memory.
    void Compact();
    /// \ru Очистить строку. \en Clears string.
    void Clear();
    /// \ru Обмен с другой строкой. \en Swaps with another string.
    void Swap(String& str);

    /// \ru Вернуть начальный итератор. \en Returns initial iterator.
    Iterator Begin() { return Iterator(m_buffer); }
    /// \ru Вернуть начальный const итератор. \en Returns initial const iterator.
    ConstIterator Begin() const { return ConstIterator(m_buffer); }

    /// \ru Вернуть конечный итератор. \en Returns finite iterator.
    Iterator End() { return Iterator(m_buffer + m_length); }

    /// \ru Вернуть const конечный итератор. \en Returns finite const iterator.
    ConstIterator End() const { return ConstIterator(m_buffer + m_length); }

        /// \ru Вернуть первый символ или 0, если строка пустая. \en Returns the first char or 0 if string is empty.
    char Front() const { return m_buffer[0]; }
        /// \ru Вернуть последний символ или 0, если строка пустая. \en Returns last char or 0 if string is empty.
    char Back() const { return m_length ? m_buffer[m_length - 1] : m_buffer[0]; }

    /// \ru Вернуть подстроку от указанной позиции до конца. \en Returns substring from specified position to end of substring.
    String Substring(unsigned pos) const;
    /// \ru Вернуть подстроку определенной длины от указанной позиции. \en Returns substring from specified position of defined length.
    String Substring(unsigned pos, unsigned length) const;
    /// \ru Вернуть строку с удаленными с начала и конца строки пробелами. \en Returns string with leading and trailing spaces removed.
    String Trimmed() const;
    /// \ru Вернуть строку в верхнем регистре. \en Returns string with all uppercase letters.
    String ToUpper() const;
    /// \ru Вернуть строку в нижнем регистре. \en Returns string with all lowercase letters.
    String ToLower() const;
    /// \ru Вернуть строки, разделенные указанными символами. По умолчанию не возвращает пустые строки. \en Returns strings split by specified chars. The function does not return empty strings by default.
    std::vector<String> Split(char separator, bool keepEmptyStrings = false) const;
    /// \ru Присоединить указанный вектор к существующей строке. \en Joins specified vector to existing string.
    void Join(const std::vector<String>& subStrings, const String& glue);
    /// \ru Вернуть индекс первого вхождения в строке. Если не найдено, тогда вернуть NPOS. \en Returns index of the first occurrence in string. If not found, returns NPOS.
    unsigned Find(const String& str, unsigned startPos = 0, bool caseSensitive = true) const;
    /// \ru Вернуть индекс первого вхождения в строке, если не найдено, вернуть NPOS. \en Returns index of the first occurrence in string. If not found, returns NPOS.
    unsigned Find(char c, unsigned startPos = 0, bool caseSensitive = true) const;
    /// \ru Вернуть индекс последнего вхождения в строке, если не найдено, вернуть NPOS. \en Returns index of the last occurrence in string. If not found, returns NPOS.
    unsigned FindLast(const String& str, unsigned startPos = NPOS, bool caseSensitive = true) const;
    /// \ru Вернуть индекс последнего вхождения в строке, если не найдено, вернуть NPOS. \en Returns index of the last occurrence in string. If not found, returns NPOS.
    unsigned FindLast(char c, unsigned startPos = NPOS, bool caseSensitive = true) const;
    /// \ru Вернуть True, если строка имеет начало указанной. \en True if string begins as specified string.
    bool StartsWith(const String& str, bool caseSensitive = true) const;
    /// \ru Вернуть True, если строка имеет конец указанной. \en True if string ends as specified string.
    bool EndsWith(const String& str, bool caseSensitive = true) const;

    /// \ru Вернуть указатель на const массив. \en Returns pointer to const array.
    const char* c_str() const { return m_buffer; }

    /// \ru Вернуть длину строки. \en Returns string length.
    unsigned Length() const { return m_length; }

    /// \ru Вернуть объем буфера. \en Returns buffer capacity.
    unsigned Capacity() const { return m_capacity; }

    /// \ru Вернуть True, если строка пустая. \en True if string is empty.
    bool IsEmpty() const { return m_length == 0; }

    /// \ru Вернуть True, если строки совпадают. \en True if strings are identical.
    int Compare(const String& str, bool caseSensitive = true) const;
    /// \ru Вернуть True, если символы совпадают. \en True if chars are identical.
    int Compare(const char* str, bool caseSensitive = true) const;

    /// \ru Вернуть True, если есть вхождение указанной строки. \en True if there is an occurrence of specified string.
    bool Contains(const String& str, bool caseSensitive = true) const { return Find(str, 0, caseSensitive) != NPOS; }

    /// \ru Вернуть True, если есть вхождение указанного символа. \en True if there is an occurrence of specified char.
    bool Contains(char c, bool caseSensitive = true) const { return Find(c, 0, caseSensitive) != NPOS; }

    /// \ru Построить содержимое строки в формате UTF8 с Latin1. \en Builds string content in UTF8 format with Latin1 standard.
    void SetUTF8FromLatin1(const char* str);
    /// \ru Построить содержимое строки в формате UTF8 из указанных символов. \en Builds string content in UTF8 format from specified chars.
    void SetUTF8FromWChar(const wchar_t* str);
    /// \ru Вычислить количество символов в содержимом UTF8. \en Counts chars in UTF8 content.
    unsigned LengthUTF8() const;
    /// \ru Вернуть смещение байта в char в содержимом UTF8. \en Returns byte offset in char in UTF8 content.
    unsigned ByteOffsetUTF8(unsigned index) const;
    /// \ru Вернуть следующий символ Unicode из содержимого UTF8. \en Returns the next Unicode char from UTF8 content.
    unsigned NextUTF8Char(unsigned& byteOffset) const;
    /// \ru Вернуть символ по индексу из содержимого UTF8. \en Returns char by index from UTF8 content.
    unsigned AtUTF8(unsigned index) const;
    /// \ru Заменить символ по индексу в содержимом UTF8. \en Replaces char by index in UTF8 content.
    void ReplaceUTF8(unsigned index, unsigned unicodeChar);
    /// \ru Добавить Unicode символ в конец содержимого UTF8. \en Adds Unicode char to end of UTF8 content.
    String& AppendUTF8(unsigned unicodeChar);
    /// \ru Вернуть подстроку UTF8 от указанной позиции до конца строки. \en Returns UTF8 substring from specified position to end of string.
    String SubstringUTF8(unsigned pos) const;
    /// \ru Вернуть подстроку UTF8 от указанной позиции определенной длины. \en Returns UTF8 substring from specified position of defined length.
    String SubstringUTF8(unsigned pos, unsigned length) const;

    /// \ru Вернуть хеш-значение для HashSet и HashMap. \en Returns hash value for HashSet and HashMap.
    unsigned ToHash() const;
    int ToInt(bool* ok = nullptr) const;
    uint ToUInt(bool* ok = nullptr) const;
    int64 ToInt64(bool* ok = nullptr) const;
    double ToDouble(bool* ok = nullptr) const;

    /// \ru Вернуть строки, разделенные указаными символами. По умолчанию не возвращает пустые строки.\en Returns strings splitted by specified chars. The function does not return empty strings by default.
    static std::vector<String> Split(const char* str, char separator, bool keepEmptyStrings = false);
    /// \ru Объединить все элементы массива в строку и вернуть строку. \en Joins all elements of an array into a string and returns the string.
    static String Joined(const std::vector<String>& subStrings, const String& glue);
    /// \ru Кодирует символ Unicode в UTF8, при этом указатель будет увеличен. \en Encodes Unicode char to UTF8. Please note, that the pointer will be increased.
    static void EncodeUTF8(char*& dest, unsigned unicodeChar);
    /// \ru Декодирует символ Unicode из UTF8, при этом указатель будет увеличен. \en Decodes Unicode char from UTF8. Please note, that the pointer will be increased.
    static unsigned DecodeUTF8(const char*& src);
#ifdef _WIN32
    /// \ru Кодирует символ Unicode в UTF16. Указатель будет увеличен. \en Encodes Unicode char to UTF16. Please note, that the pointer will be increased.
    static void EncodeUTF16(wchar_t*& dest, unsigned unicodeChar);
    /// \ru Декодирует символ Unicode из UTF16. Указатель будет увеличен. \en Decodes Unicode char from UTF16. Please note, that the pointer will be increased.
    static unsigned DecodeUTF16(const wchar_t*& src);
#endif
    /// \ru Вернуть длину строки. \en Returns string length.
    static unsigned CStringLength(const char* str) { return str ? (unsigned)strlen(str) : 0; }

    /// \ru Добавить строку с использованием форматирования. \en Appends string using formatting.
    String& AppendWithFormat(const char* formatString, ...);
    /// \ru Добавить строку с использованием форматирования и переменных. \en Appends string using formatting and variables.
    String& AppendWithFormatArgs(const char* formatString, va_list args);

    /// \ru Сравнить две строки. \en Compares two strings.
    static int Compare(const char* str1, const char* str2, bool caseSensitive);

    static const unsigned NPOS;              ///< \ru Для позиции. \en For position.
    static const unsigned MIN_CAPACITY = 8;  ///< \ru Начальный размер распределения. \en Initial capacity.
    static const String EMPTY;               ///< \ru Пустая строка. \en Empty string.

private:
    /// \ru Перемещение буфера символов внутри строки. \en Moves char buffer inside of string.
    void MoveRange(unsigned dest, unsigned src, unsigned count);
    /// \ru Копирование символов из одного буфера в другой. \en Copies chars from buffer to another buffer.
    static void CopyChars(char* dest, const char* src, unsigned count);
    /// \ru Заменить подстроку на другую подстроку. \en Replaces string with another string.
    void Replace(unsigned pos, unsigned length, const char* srcStart, unsigned srcLength);

    unsigned m_length;        ///< \ru Длина строки. \en String length.
    unsigned m_capacity;    ///< \ru Размер выделенной памяти. Размер равен нулю, если память под буфер не выделена. \en Size of the allocated storage. Size is 0 if buffer memory is not allocated.
    char* m_buffer;            ///< \ru Буфер строки равен нулю, если не выделена память. \en String buffer is NULL if memory is not allocated.
    static char m_endZero;    ///< \ru Пустые строки, оканчивающиеся нулем. \en Null-terminated empty strings.
};

/// Add a string to a C string.
inline String operator +(const char* lhs, const String& rhs)
{
    String ret(lhs);
    ret += rhs;
    return ret;
}

/// Add a string to a wide char C string.
inline String operator +(const wchar_t* lhs, const String& rhs)
{
    String ret(lhs);
    ret += rhs;
    return ret;
}


//------------------------------------------------------------------------------
/** \brief  \ru Общий класс строк на основе стандарта Unicode для преобразования строки.
            \en General String class based on Unicode standard and used for converting string. \~
    \ingroup Vision_Common
*/
// ---
class VSN_CLASS WString
{
public:
    /// \ru Конструктор по умолчанию. Создает пустой String. \en Default constructor creating an empty String.
    WString();
    /// \ru Конструктор копирование из другого объекта String. \en Copy constructor from another String object.
    WString(const String& str);
    /// \ru Конструктор копирование из другого объекта WString. \en Copy constructor from another WString object.
    WString(const WString& str);
    /// \ru Деструктор. \en Destructor.
    ~WString();


    WString & operator = (const WString & str);
public:
    /// \ru Вернуть символ по индексу. \en Returns char by index.
    wchar_t& operator [](unsigned index);
    /// \ru Вернуть const символ по индексу. \en Returns const char by index.
    const wchar_t& operator [](unsigned index) const;

    /// \ru Вернуть символ по индексу. \en Returns char by index.
    wchar_t& At(unsigned index);
    /// \ru Вернуть const символ по индексу. \en Returns const char by index.
    const wchar_t& At(unsigned index) const;

    /// \ru Изменить размер строки. \en Changes string size.
    void Resize(unsigned newLength);

    /// \ru Вернуть true, если строка пустая. \en True if string is empty.
    bool IsEmpty() const { return m_length == 0; }
    /// \ru Вернуть длину строки. \en Returns string length.
    unsigned Length() const { return m_length; }

    /// \ru Вернуть указатель на const массив. \en Returns pointer to const array.
    const wchar_t* c_str() const { return m_buffer; }
private:
    unsigned m_length; ///< \ru Длина строки. \en String length.
    wchar_t* m_buffer; ///< \ru Буфер строки равен нулю, если не выделена память. \en String buffer is NULL if memory is not allocated.
};

VSN_END_NAMESPACE

#endif /* __VSN_STRING_H */
