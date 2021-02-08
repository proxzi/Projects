////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru DimensionGeometry является базовым классом геометрий для двумерных 
             представлений линейных, радиальных, угловых размеров.
         \en DimensionGeometry class is the base class of geometry for two-dimensional
             representations of linear, radial, angular sizes. \~
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_DIMENSIONGEOMETRY_H
#define __VSN_DIMENSIONGEOMETRY_H

#include <mb_cart_point3d.h>
#include <surf_plane.h>
#include "vsn_annotationgeometry.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

#define UNITS_LENGTH_MM  "mm"
#define UNITS_LENGTH_M   "m"
#define UNITS_ANGLE_RAD  "rad"
#define UNITS_ANGLE_GRAD "grad"

class DimensionGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief \ru DimensionGeometry является базовым классом геометрий для двумерных представлений линейных, радиальных, угловых размеров.
           \en DimensionGeometry class is the base class of geometry for two-dimensional representations of linear, radial, angular sizes. \~
  \details \ru DimensionGeometry обеспечивает измерение величин, таких как длина, радиус или плоские углы. Измерение размера выполняется
               в пространстве всей модели. Значения измерения представлены в единицах модели, указанных пользователем. 
               Во время отображения измеренное значение преобразуется из единицы модели в единицу отображения. Для отрисовки DimensionGeometry 
               состоит из следующих примитивов:
               - основные точки привязок - точки, которыми размер крепится на размерной плоскости;
               - основная размерная линия, которая простирается от точек привязок в направлении вверх
                 и содержит метку с текстом расчитанного значения, например, длины;
               - выносные линии - линии, которые содержат точки крепления с основной размерной линией;
               - линии расширения - линии, использующиеся для расширения основной размерной 
                 линии в случаях, когда текст или стрелки не вписываются в основную размерную 
                 линию из-за их размера;
               - стрелки, обозначающие конец основной размерной линии.  

               Как правило, в 2D-чертежах размеры создаются на размерной плоскости, которую можно рассматривать как местоположение (placement) 
               для построения представления размера, представляющее собой начало отсчета координат и направленные оси. Соответственно, основная размерная 
               линия будет представлена вдоль оси X, а выносные линии - вдоль оси Y. Это помогает пользователю представить, как размер будет расположен 
               и ориентирован в пространстве модели.
               Ориентация размерной линии в пространстве относительно опорной фигуры определяется с помощью выносных линий. Вычисления указывают 
               длину выносных линий и их ориентацию относительно точек крепления на рабочей плоскости.
               Для линейного размера: направление выносных линий определяется направлением главной размерной линии, т.е. вектором от первой точки крепления до второй 
               точки крепления и нормалью размерной плоскости.
               Для углового размера: вылеты определяются векторами от центральной точки до точек привязки. Эти направления векторов должны быть положительными 
               направлениями выносных линий. Отрицательные направления вылета означают, что эти векторы должны быть развернуты.

               Размерная плоскость может быть построена автоматически приложением (где это возможно, все зависит от измеряемой геометрии).
               Также размерная плоскость может быть установлена пользователем. Если же пользовательская плоскость не соответствует геометрии измерения,
               т.е. точки крепления не принадлежат ей, размер не может быть построен. Если невозможно вычислить автоматическую плоскость, например, 
               в случае длины между двумя точками, то пользователь должен указать пользовательскую плоскость самостоятельно. \n.
           \en DimensionGeometry class provides measuring such values as length, radius or flat angles. Measuring a size is performed
               in the space of a whole model. Measurement values are presented in units of model, specified by the user.
               When displaying the measured value is converted from a model unit to a display unit. To render DimensionGeometry
               consists of the following primitives:
               - the main snap points - points fixing a size to a dimension plane;
               - the main dimension line extending from snap points to up direction
                 and contains a label of calculated value, for example, of length;
               - the extension lines - lines containing fixation points to the main dimension line;
               - the extension lines - lines used to extend the main dimension line
                 in cases a text or arrows don't fit in the main dimension line because of their sizes.
               - the arrows denoting the end of main dimension line.

               As a rule, in 2D drawings sizes are created on a dimension plane that can be considered as a placement
               for creating a size representation presenting the origin and the directed axis. Respectively, the main dimension
               line will be presented along X-axis, and the extension lines along Y-axis. It helps the user imagine
               how a size will be placed and oriented in a space of model.
               The dimension line orientation in a space about a supporting figure is defined with the extension lines.
               Calculations specify a length of extension lines and their orientation about fixation points to a working plane.
               For a linear size: direction of extension lines is defined by a direction of the main dimension line, i.e. by a vector
               from the first fixation point to the second one and a normal of a dimension plane.
               For an angular size: radii are defined by vectors from the central point to snap points. These directions of vectors must be
               the positive directions of extension lines. The negative directions of radius mean these vectors must be expanded.

               The dimension plane can be built automatically by an application (if possible, it depends on computed geometry).
               Also a dimension plane can be set by the user. If the user's plane doesn't match a measurement geometry,
               i.e. fixation points doesn't belong to it, a size cannot be built. If impossible to compute automatic plane,
               for example, in case length between two points, then the user should specify the user's plane on his own. \n \~
  \ingroup Vision_Geometry
*/
// ---
class VSN_CLASS DimensionGeometry : public AnnotationGeometry
{
    VSN_OBJECT(DimensionGeometry)
    VSN_ENUM(DimensionGeometry::TextOrientation)
    VSN_ENUM(DimensionGeometry::TextVPosition)
    VSN_ENUM(DimensionGeometry::TextHPosition)
    VSN_PROP_READ_WRITE_NOTIFY(orientation,  GetTextOrientation, SetTextOrientation, OnTextOrientationModified)
    VSN_PROP_READ_WRITE_NOTIFY(vertPosition, GetTextVPosition,   SetTextVPosition,   OnTextVPositionModified)
    VSN_PROP_READ_WRITE_NOTIFY(horzPosition, GetTextHPosition,   SetTextHPosition,   OnTextHPositionModified)
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    DimensionGeometry();
public:
    /// \ru Деструктор. \en Destructor. \~
    virtual ~DimensionGeometry();
public:
    enum ValueType
    {
        vt_Calculated,
        vt_UserDouble,
        vt_UserText
    };

    enum TextOrientation
    {
        to_Freeze,     ///< \ru В плоскости размера. \en In size plane. \~
        to_ScreenOnly, ///< \ru В плоскости экрана. \en In screen plane. \~
        to_Readable,   ///< \ru В плоскости размера с поворотом по вектору взгляда. \en In dimension plane with a turn by view vector. \~
    };

    ///< \ru Положение текста по горизонтали. \en Position of text horizontally. \~
    enum TextHPosition
    {
        hpos_Left,
        hpos_Right,
        hpos_Center,
        hpos_Auto
    };
    ///< \ru Положение текста по вертикали. \en Position of text vertically. \~
    enum TextVPosition 
    {
        vpos_Above,
        vpos_Below,
        vpos_Center
    };
    ///< \ru Ориентация стрелок размера. \en Arrow orientation of size. \~
    enum ArrowOrientation
    {
        orient_Internal,
        orient_External,
        orient_Auto
    };
public:
    /// \ru Вернуть ориентацию текста на размерной линии. \en Returns orientation of text on dimension line. \~
    DimensionGeometry::TextOrientation GetTextOrientation() const;
    /// \ru Получить вертикальное выравнивание текста. \en Returns vertical alignment of text. \~
    TextVPosition GetTextVPosition() const;
    /// \ru Получить горизонтальное выравнивание текста. \en Returns horizontal alignment of text. \~
    TextHPosition GetTextHPosition() const;

    /// \ru Вернуть true, если размер полностью определен. \en Returns true if size is completely determined. \~
    bool IsValid() const;
    /// \ru Вернуть цвет текста размера. \en Returns color of dimension text. \~
    Color GetLabelColor() const;
    /// \ru Установить цвет текста размера. \en Sets color of dimension text. \~
    void SetLabelColor(const Color& color);

    /// \ru Вернуть цвет размера. \en Returns color of dimension. \~
    Color GetDimensionColor() const;
    /// \ru Установить цвет размера. \en Sets color of dimension. \~
    void SetDimensionColor(const Color& color);

    /// \ru Вернуть высоту выносной линии. \en Returns height of extension line. \~
    double GetExtensionLineHeight() const;
    /// \ru Установить высоту выносной линии. \en Sets height of extension line. \~
    void SetExtensionLineHeight(double extHeight);

    /// \ru Вернуть измеренное значение. \en Returns calculated value. \~
    double GetValue() const;

    /// \ru Установить шрифт по умолчанию. \en Sets default font. \~
    static void SetDefaultFont(const String& str);

    /// \ru Изменить размер шрифта. \en Set the font size. \~
    void SetFontSize(uint size);
    /// \ru Получить размер шрифта. \en Get the font size. \~
    uint GetFontSize() const;
public:
    /// \ru Установить ориентацию текста на размерной линии. \en Sets text orientation on dimension line. \~
    VSN_SLOT(Public, SetTextOrientation, void SetTextOrientation(TextOrientation orientation))
    /// \ru Установить вертикальное выравнивание текста. \en Sets vertical alignment of text. \~
    VSN_SLOT(Public, SetTextVPosition,   void SetTextVPosition(TextVPosition vertPosition))
    /// \ru Установить горизонтальное выравнивание текста. \en Sets horizontal alignment of text. \~
    VSN_SLOT(Public, SetTextHPosition, void SetTextHPosition(TextHPosition horzPosition))
public:
    /// \ru Сигнал будет сгенерирован при модификации ориентации текста. \en Signal will be generated when modifying text orientation. \~
    VSN_SIGNAL(Public, OnTextOrientationModified, void OnTextOrientationModified(TextOrientation orientation), orientation)
    /// \ru Сигнал будет сгенерирован при модификации положения текста по вертикали. \en Signal will be generated when modifying text position vertically. \~
    VSN_SIGNAL(Public, OnTextVPositionModified,   void OnTextVPositionModified(TextVPosition vertPosition),    vertPosition)
    /// \ru Сигнал будет сгенерирован при модификации положения текста по горизонтали. \en Signal will be generated when modifying text position horizontally. \~
    VSN_SIGNAL(Public, OnTextHPositionModified,   void OnTextHPositionModified(TextHPosition horzPosition),    horzPosition)
public:
    /// \ru Получить плоскость размера, в которой вычисляется представление 2D - размера. \en Returns dimension plane in which 2D size representation is computed. \~
    const MbPlane& GetPlane() const;
    /// \ru Установить плоскость размера, в которой будет вычисляться представление 2D - размера. \en Sets dimension plane in which 2D size representation is computed. \~
    virtual void SetPlane(const MbPlane& plane);

    /// \ru Выдать габаритный куб. \en Returns bounding box. \~
    virtual const MbCube& GetBoundingBox() override;

    /// \ru Вернуть единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Returns default measurement units identical to model measurement units for correct converting. \~
    virtual String GetDefaultUnits() const;
    /// \ru Установить единицы измерения по умолчанию, являющиеся идентичными единицам измерения модели для правильной конвертации. \en Sets default measurement units identical to model measurement units for correct converting. \~
    virtual void SetDefaultUnits(const String& units);

    /// \ru Вернуть единицы измерения для вывода. \en Returns measurement units for output. \~
    virtual String GetOutputUnits() const;
    /// \ru Установить единицы измерения для вывода. \en Sets measurement units for output. \~
    virtual void SetOutputUnits(const String& units);

    /// \ru Вернуть true, если положение текста задано пользователем с помощью функции SetTextPosition. \en Returns true if text position is set by user with SetTextPosition function. \~
    bool IsTextPositionUser() const;
    /// \ru Получить позицию текста 2D - размера. \en Returns text position of 2D size. \~
    virtual const MbCartPoint3D GetTextPosition() const;
    /// \ru Установить позицию текста 2D - размера. \en Sets text position of 2D size. \~
    virtual void SetTextPosition(const MbCartPoint3D& textPos);
    /// \ru Вернуть вычисленное значение измерения. \en Returns calculated measurement value. v
    virtual double CalculateValue() const;
protected:
    /// \ru Конструктор с параметрами. \en Constructor with parameters. \~
    DimensionGeometry(DimensionGeometryPrivate& dd, Node* pParent);
    /// \ru Отрисовать размер с помощью OpenGL. \en Renders size with OpenGL. \~
    virtual void OpenGLDraw(const RenderState& state) override;
protected:
    VSN_DECLARE_EX_PRIVATE(DimensionGeometry);
};

VSN_END_NAMESPACE

#endif /* __VSN_DIMENSIONGEOMETRY_H */
