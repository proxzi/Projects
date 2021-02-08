////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс DiameterDimensionRep является вспомогательным классом и представляет API 
             для управления геометрией DiameterDimensionGeometry.
         \en DiameterDimensionRep class is an auxiliary class and presents API to control
             DiameterDimensionGeometry geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_DIAMETERDIMENSIONREP_H
#define __VSN_DIAMETERDIMENSIONREP_H

#include <cur_arc3d.h>
#include "vsn_dimensionrep.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru Класс DiameterDimensionRep является вспомогательным классом и представляет API 
               для управления геометрией DiameterDimensionGeometry.
           \en DiameterDimensionRep class is an auxiliary class and presents API to control
               DiameterDimensionGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS DiameterDimensionRep : public DimensionRep
{
    VSN_OBJECT(DiameterDimensionRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit DiameterDimensionRep(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~DiameterDimensionRep();
public:
    /// \ru Вернуть единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Returns default measurement units identical to model measurement units for correct converting. \~
    String GetDefaultUnits() const; 
    /// \ru Установить единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Sets default measurement units identical to model measurement units for correct converting. \~
    void SetDefaultUnits(const String& units);

    /// \ru Вернуть единицы измерения для вывода. \en Returns measurement units for output. \~
    String GetOutputUnits() const;
    /// \ru Установить единицы измерения для вывода. \en Sets measurement units for output. \~
    void SetOutputUnits(const String& units);
public:
    /// \ru Определить диаметральный размер для измерения. \en Defines diametrical size to measure. \~
    void SetMeasuredGeometry(const MbArc3D& circle);
private:
    VSN_DISABLE_COPY(DiameterDimensionRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_DIAMETERDIMENSIONREP_H */
