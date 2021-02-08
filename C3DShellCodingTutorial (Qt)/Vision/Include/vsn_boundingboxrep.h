////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс BoundingBoxRep является вспомогательным классом и представляет API 
             для управления геометрией BoundingBoxGeometry. BoundingBoxRep 
             является представлением ограничивающего параллелепипеда и служит
             для отображения информационного габарита узла в сцене по указанному 
             сегменту и вывода численых значений по всем осям в виде
             шкалы.
         \en BoundingBoxRep class is an auxiliary class and presents API to control
             BoundingBoxGeometry geometry. BoundingBoxRep class is a representation of
             a bounding box and serves for displaying informational graph size in a scene
             by the specified segment and outputting numerical values of all axes in the form
             of a scale. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_BOUNDINGBOXREP_H
#define __VSN_BOUNDINGBOXREP_H

#include "vsn_geometryrep.h"
#include "vsn_namespace.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class SceneSegment;
class BoundingBoxRepPrivate;
//------------------------------------------------------------------------------
/** \brief \ru BoundingBoxRep является представлением ограничивающего параллелепипеда
               и служит для отображения информационного габарита узла в сцене по указанному
               сегменту и вывода численых значений по всем осям в виде шкалы.
           \en BoundingBoxRep class is a representation of a bounding box and serves for
               displaying informational graph size in a scene by the specified segment and
               outputting numerical values of all axes in the form of a scale. \~
  \details \ru BoundingBoxRep имеет ряд полезных функций с помощью которых можно изменить
               толщину линий осей, изменить их цвет. BoundingBoxRep дает возможность 
               настроить вид отображения шкалы, ее направления, а также видимость. Есть
               возможность настройки начала координат, совпадение начала координат с миром
               или начала вектора направления осей. \n.
           \en BoundingBoxRep class has a set of useful functions with which you can change
               a thickness of axis lines, change their color. BoundingBoxRep class gives
               an opportunity to set a view of scale displaying, its direction, and also
               visibility. There is a capability of setting origin, a match of origin
               to world and vector origin of axis direction. \n \~
  \ingroup NO GROUP
*/
// ---
class VSN_CLASS BoundingBoxRep : public GeometryRep
{
    VSN_OBJECT(BoundingBoxRep)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    BoundingBoxRep();
    /// \ru Деструктор. \en Destructor. 
    virtual ~BoundingBoxRep();
public:
    /// \ru Вернуть видимость указанной оси. \en Returns visibility of the specified axis. \~
    bool IsVisibleAxis(AxisOrientation orientation) const;
    /// \ru Установить видимость указанной оси. \en Sets visibility of the specified axis. \~
    void SetVisibleAxis(AxisOrientation orientation, bool visible);

    /// \ru Вернуть видимость наконечника указанной оси. \en Returns visibility of the specified axis end. \~
    bool IsVisibleTips(AxisOrientation orientation) const;
    /// \ru Установить видимость наконечника указанной оси. \en Sets visibility of the specified axis end. \~
    void SetVisibleTips(AxisOrientation orientation, bool visible);

    /// \ru Вернуть видимость текста меток указанной оси. \en Returns visibility of the specified axis label text. \~
    bool IsVisibleLabels(AxisOrientation orientation) const;
    /// \ru Установить видимость текста меток указанной оси. \en Sets visibility of the specified axis label text. \~
    void SetVisibleLabels(AxisOrientation orientation, bool visible);

    /// \ru Вернуть обратное направление указанной оси. \en Returns a reversed specified axis. \~
    bool IsReversedAxis(AxisOrientation orientation) const;
    /// \ru Установить обратное направление указанной оси. \en Sets a reversed specified axis. \~
    void SetReversedAxis(AxisOrientation orientation, bool bEnabled);

    /// \ru Вернуть признак совпадения с миром начала координат. Если true, то начало координат совпадает с миром. \en Returns a flag of matching origin to world. If true, origin matches to world. \~
    bool IsAutoAdjustOrigin(AxisOrientation orientation) const;
    /// \ru Установить совпадение начала координат с миром. Если true, то начала координат совпадают с миром. \en Sets a flag of matching origin to world. If true, origin matches to world. \~
    void SetAutoAdjustOrigin(AxisOrientation orientation, bool bAuto);

    /// \ru Вернуть количество рисок шкалы по указанной оси. \en Returns a quantity of scale lines by the specified axis. \~
    int GetSegmentCount(AxisOrientation orientation) const;
    /// \ru Установить количество рисок шкалы по указанной оси. \en Sets a quantity of scale lines by the specified axis. \~
    void SetSegmentCount(AxisOrientation orientation, int count);

    /// \ru Вернуть формат отображения значений по указанной оси. \en Returns format of displaying values by the specified axis. \~
    int GetFormatPrecision(AxisOrientation orientation) const;
    /// \ru Установить формат отображения значений по указанной оси. \en Sets format of displaying values by the specified axis. \~
    void SetFormatPrecision(AxisOrientation orientation, int precision);

    /// \ru Вернуть толщину ребра ограничивающего параллелепипеда. \en Returns a thickness of bounding box edge. \~
    double GetBoundingBoxEdgeWidth() const;
    /// \ru Установить толщину ребра ограничивающего параллелепипеда. \en Sets a thickness of bounding box edge. \~
    void SetBoundingBoxEdgeWidth(double width);

    /// \ru Вернуть видимость габаритного размера параллелепипеда. \en Returns visibility of a bounding box size. \~
    bool IsDimensionVisible() const;
    /// \ru Установить видимость габаритного размера параллелепипеда. \en Sets visibility of a bounding box size. \~
    void SetDimensionVisible(bool bVisible);

    /// \ru Вернуть цвет размеров. \en Returns size color. \~
    Color GetColorDimension() const;
    /// \ru Установить цвет размеров. \en Sets size color. \~
    void SetColorDimension(const Color& color);

    /// \ru Вернуть цвет указанной оси. \en Returns a color of the specified axis. \~
    Color GetColorAxis(AxisOrientation orientation) const;
    /// \ru Установить цвет указанной оси. \en Sets a color of the specified axis. \~
    void SetColorAxis(AxisOrientation orientation, const Color& color);

    /// \ru Вернуть цвет текста указанной оси. \en Returns a text color of the specified axis. \~
    Color GetColorLabels(AxisOrientation orientation) const;
    /// \ru Установить цвет текста указанной оси. \en Sets a text color of the specified axis. \~
    void SetColorLabels(AxisOrientation orientation, const Color& color);

    /// \ru Вернуть указатель на начальный сегмент. \en Returns a pointer to initial segment. \~
    const SceneSegment* GetSceneSegment() const;
    /// \ru Установить начальный сегмент для отображения его габарита в сцене. \en Sets initial segment to display its size in a scene. \~
    void SetSceneSegment(const SceneSegment* pSegment);
public:
    VSN_SLOT(Protected, BoundingBoxModified, void BoundingBoxModified())
private:
    VSN_DECLARE_PRIVATE(BoundingBoxRep);
};

VSN_END_NAMESPACE

#endif /* __VSN_BOUNDINGBOXREP_H */
