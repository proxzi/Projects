///////////////////////////////////////////////////////////////////////////////
/**
    \file
        \brief \ru Уникальный ключ для Node.
               \en Node unique key. \~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_NODEKEY_H
#define __VSN_NODEKEY_H

#include <vector>
#include "vsn_string.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE


//----------------------------------------------------------------------------
//
/** \brief \ru Уникальный ключ для Node.
           \en Node unique key. \~
\ingroup Vision_Nodes
*/
// ---
class VSN_CLASS NodeKey
{
public:
    /// \ru Конструктор c заданием значения ключа. \en Constructor setting key value.
    explicit NodeKey(uint64 customKey);
public:
    /// \ru Конструктор по умолчанию. Значение ключа равно нулю. \en Default constructor. Key value is 0.
    NodeKey();
    static const NodeKey ZERO;
    static NodeKey GenerationKey();
public:
    /// \ru Вернуть True, если значение ключа равно нулю. \en True if key value is 0.
    bool IsNull() const;
    /// \ru Вернуть True, если значения ключей равны. \en True if key values are equal.
    bool operator ==(NodeKey other) const;
    /// \ru Вернуть True, если значения ключей не равны. \en True if key values are not equal.
    bool operator !=(NodeKey other) const;
    /// \ru Вернуть True, если значение ключа (<). \en True if key value is (<).
    bool operator < (NodeKey other) const;
    /// \ru Вернуть True, если значение ключа (>). \en True if key value is (>).
    bool operator >(NodeKey other) const;
    /// \ru Вернуть значение ключа. \en Returns key value.
    uint64 GetKey() const;
    /// \ru Вернуть True, если значение ключа не равно нулю. \en True if key value is not 0.
//    operator bool() const;
    /// \ru Вернуть хэш-значение для HashSet & HashMap. \en Returns hash value for HashSet & HashMap.
    unsigned ToHash() const;
    /// \ru Вернуть значение ключа в представлении String. \en Returns key value as a String.
    String ToString() const;
private:
    uint64 m_key;
    friend class Viewport;
    friend class ObjectPickSelectionPrivate;
};

typedef std::vector<NodeKey> NodeKeyVector;
struct NodeKeyHasher
{
    unsigned operator()(const String& t) const
    { return t.ToHash(); }
};

VSN_END_NAMESPACE


#endif // __VSN_NODEKEY_H
