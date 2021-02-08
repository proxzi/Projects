////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс MathRepresentation является вспомогательным классом и представляет
             API для управления геометрией.
         \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_ANGLEDIMENSIONREP_H
#define __VSN_ANGLEDIMENSIONREP_H

#include "vsn_dimensionrep.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru Класс AngleDimensionRep является вспомогательным классом и представляет API для управления геометрией.
           \en MathRepresentation class is an auxiliary class and represents API to control geometry. \~
    \details \ru AngleDimensionRep создает AngleDimensionGeometry и содержит его указатель на протяжении всей своей жизни.
                 AngleDimensionRep представляет ряд полезных функций для управления геометрией углового размера. \n.
             \en AngleDimensionRep class creates AngleDimensionGeometry and contains its pointer during its whole existing.
                 AngleDimensionRep class presents a set of useful functions to control geometry of angular size. \n \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS AngleDimensionRep : public DimensionRep
{
    VSN_OBJECT(AngleDimensionRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit AngleDimensionRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~AngleDimensionRep();
public:
    /// \ru Вернуть единицы измерения по умолчанию, являющиеся идентичными едницам измерения модели для правильной конвертации.
    /// \en Returns default measurement units identical to model measurement units for correct converting. \~
    String GetDefaultUnits() const;
    /// \ru Установить единицы измерения по умолчанию, являющиеся идентичными едницам измерения модели для правильной конвертации.
    /// \en Sets default measurement units identical to model measurement units for correct converting. \~
    void SetDefaultUnits(const String& units);

    /// \ru Вернуть единицы измерения для вывода. \en Returns measurement units for output. \~
    String GetOutputUnits() const;
    /// \ru Установить единицы измерения для вывода. \en Sets measurement units for output. \~
    void SetOutputUnits(const String& units);
public:
    /// \ru Измерить угол по трем точкам. \en Measures angle by three points.
    void SetMeasuredGeometry(const MbCartPoint3D& center, const MbCartPoint3D& pnt1, const MbCartPoint3D& pnt2);
private:
    VSN_DISABLE_COPY(AngleDimensionRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_ANGLEDIMENSIONREP_H */
