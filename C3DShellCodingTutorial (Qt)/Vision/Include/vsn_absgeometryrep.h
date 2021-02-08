////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Абстрактный класс представления.
           \en Abstract representation class. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ABSGEOMETRYREP_H
#define __VSN_ABSGEOMETRYREP_H

#include "vsn_string.h"
#include "vsn_feature.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class AbsGeometryRepPrivate;
//------------------------------------------------------------------------------
/** \brief   \ru Абстрактный класс представления.
             \en Abstract representation class. \~
    \ingroup Vision_Geometry
*/
//---
class VSN_CLASS AbsGeometryRep : public Feature
{
    VSN_OBJECT(AbsGeometryRep);
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    AbsGeometryRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~AbsGeometryRep();
public:
    /// \ru Является ли ссылка пустой. \en Checks if reference is empty.
    bool IsReferenceEmpty() const;
    /// \ru Вернуть тип представления. \en Returns representation type.
    virtual int GetRepType() const = 0;
    /// \ru Задать имя представления. \en Sets representation name.
    void SetNameRep(const String& name);
    /// \ru Вернуть имя представления. \en Returns representation name.
    const String& GetNameRep() const;
    /// \ru Является ли представление пустым. \en Checks if representation is empty.
    virtual bool IsEmpty() const = 0;
    /// \ru Является ли представление загруженным. \en Checks if representation is loaded.
    bool IsLoaded() const;
public:
    /// \ru Оператор присваивания. \en Assignment operator.
    virtual AbsGeometryRep &operator = (const AbsGeometryRep&);
    /// \ru Являются ли представления одинаковыми. \en Checks if representations are equal.
    bool operator == (const AbsGeometryRep& rep);
public:
    /// \ru Заменить представление. \en Replaces representation.
    virtual void ReplaceRep(AbsGeometryRep*) = 0;
protected:
    /// \ru Приватный конструктор для наследников. \en Private construсtor for inheritors.
    AbsGeometryRep(AbsGeometryRepPrivate& dd, Node* parent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(AbsGeometryRep);
};

VSN_END_NAMESPACE

#endif /* __VSN_ABSGEOMETRYREP_H */
