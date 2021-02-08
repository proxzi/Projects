#ifndef __VSN_LINEARDIMENSIONREP_H
#define __VSN_LINEARDIMENSIONREP_H

#include "vsn_dimensionrep.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS LinearDimensionRep : public DimensionRep
{
    VSN_OBJECT(LinearDimensionRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit LinearDimensionRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~LinearDimensionRep();
public:
    /// \ru Вернуть первую фиксированную точку размера. \en NO TRANSLATION. 
    MbCartPoint3D GetFirstPoint() const;
    /// \ru Вернуть вторую фиксированную точку размера. \en NO TRANSLATION. 
    MbCartPoint3D GetSecondPoint() const;

    /// \ru Вернуть единицы измерения по умолчанию.(единицы являются модельные для правильной конвертации) \en NO TRANSLATION. \~
    String GetDefaultUnits() const;
    /// \ru Установить единицы измерения по умолчанию. (единицы являются модельные для правильной конвертации) \en NO TRANSLATION. \~
    void SetDefaultUnits(const String& units);

    /// \ru Вернуть единицы измерения для вывода. \en NO TRANSLATION. \~
    String GetOutputUnits() const;
    /// \ru Установить единицы измерения для вывода. \en NO TRANSLATION. \~
    void SetOutputUnits(const String& units);
public:
    /// \ru Измерить расстояние между двумя точками. \en NO TRANSLATION.
    void SetMeasuredGeometry(const MbCartPoint3D& pnt1, const MbCartPoint3D& pnt2, const MbPlane& plane);
private:
    VSN_DISABLE_COPY(LinearDimensionRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_LINEARDIMENSIONREP_H */
