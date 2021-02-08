////////////////////////////////////////////////////////////////////////////////
/**
\file
  \brief \ru Класс DimensionRep является вспомогательным классом и представляет API
             для управления геометрией DimensionGeometry.
         \en DimensionRep class is an auxiliary class and presents API to control
             DimensionGeometry geometry. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_DIMENSIONREP_H
#define __VSN_DIMENSIONREP_H

#include "vsn_geometryrep.h"
#include "vsn_dimensiongeometry.h"

VSN_BEGIN_NAMESPACE
//------------------------------------------------------------------------------
/** \brief \ru Класс DimensionRep является вспомогательным классом и представляет API
               для управления геометрией DimensionGeometry.
           \en DimensionRep class is an auxiliary class and presents API to control
               DimensionGeometry geometry. \~
    \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS DimensionRep : public GeometryRep
{
    VSN_OBJECT(DimensionRep)
//    VSN_PROP_READ_WRITE(polyStep, GetPolygonStep, SetPolygonStep)
    VSN_PROP_READ_WRITE_NOTIFY(orientation,  GetTextOrientation, SetTextOrientation, OnTextOrientationModified)
    VSN_PROP_READ_WRITE_NOTIFY(vertPosition, GetTextVPosition,   SetTextVPosition,   OnTextVPositionModified)
    VSN_PROP_READ_WRITE_NOTIFY(horzPosition, GetTextHPosition,   SetTextHPosition,   OnTextHPositionModified)
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit DimensionRep(DimensionGeometry* pGeometry, Node* pParent);
public:
    /// \ru Деструктор. \en Destructor. 
    virtual ~DimensionRep();
public:
    /// \ru Вернуть ориентацию текста на размерной линии. \en Returns text orientation on dimension line.
    DimensionGeometry::TextOrientation GetTextOrientation() const;
    /// \ru Вернуть вертикальное выравнивание текста. \en Returns vertical alignment of text.
    DimensionGeometry::TextVPosition GetTextVPosition() const;
    /// \ru Вернуть горизонтальное выравнивание текста. \en Returns horizontal alignment of text.
    DimensionGeometry::TextHPosition GetTextHPosition() const;
    /// \ru Изменить размер шрифта. \en Set the font size. \~
    void SetFontSize(uint size);
    /// \ru Получить размер шрифта. \en Get the font size. \~
    uint GetFontSize() const;
    /// \ru Установить цвет текста размера. \en Sets color of dimension text. \~
    void SetLabelColor(const Color& color);
    /// \ru Вернуть цвет текста размера. \en Returns color of dimension text. \~
    Color GetLabelColor() const;
    /// \ru Вернуть цвет размера. \en Returns color of dimension. \~
    Color GetDimensionColor() const;
    /// \ru Установить цвет размера. \en Sets color of dimension. \~
    void SetDimensionColor(const Color& color);
public:
    /// \ru Устанановить ориентацию текста на размерной линии. \en Sets text orientation on dimension line.
    VSN_SLOT(Public, SetTextOrientation, void SetTextOrientation(DimensionGeometry::TextOrientation orientation))
    /// \ru Устанановить вертикальное выравнивание текста. \en Sets vertical alignment of text.
    VSN_SLOT(Public, SetTextVPosition, void SetTextVPosition(DimensionGeometry::TextVPosition vertPosition))
    /// \ru Устанановить горизонтальное выравнивание текста. \en Sets horizontal alignment of text.
    VSN_SLOT(Public, SetTextHPosition, void SetTextHPosition(DimensionGeometry::TextHPosition horzPosition))
public:
    /// \ru Сигнал будет сгенерирован при модификации ориентации текста. \en Signal will be generated when modifying text orientation. \~
    VSN_SIGNAL(Public, OnTextOrientationModified, void OnTextOrientationModified(DimensionGeometry::TextOrientation orientation), orientation)
    /// \ru Сигнал будет сгенерирован при модификации положения текста по вертикали. \en Signal will be generated when modifying text position vertically. \~
    VSN_SIGNAL(Public, OnTextVPositionModified,   void OnTextVPositionModified(DimensionGeometry::TextVPosition vertPosition), vertPosition)
    /// \ru Сигнал будет сгенерирован при модификации положения текста по горизонтали. \en Signal will be generated when modifying text position horizontally. \~
    VSN_SIGNAL(Public, OnTextHPositionModified,   void OnTextHPositionModified(DimensionGeometry::TextHPosition horzPosition), horzPosition)
private:
    VSN_DISABLE_COPY(DimensionRep)
};

VSN_END_NAMESPACE

#endif /* __VSN_CYLINDERREP_H */
