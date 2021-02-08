////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Файл содержит класс геометрической сетки.
         \en File contain a class of the geometry grid. \~

    \class Experiment::GridGeometry

    \ru Пример использования: \en Usage example: \~

    \code{.cpp}
      // create a grid on the XY plane.
      auto grid = new GridGeometry(Experiment::GridGeometry::XYPlane, *viewport());

      // change colors
      grid->SetFirstAxisColor(Color(200, 50, 50));
      grid->SetSecondAxisColor(Color(50, 200, 50));
      grid->SetGridLinesColor(Color(130,200,255));

      // add to scene
      new SceneSegment(new GeometryRep(grid), rootSegment);
    \endcode

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_GRIDGEOMETRY_H
#define __VSN_GRIDGEOMETRY_H

#include "vsn_global.h"
#include "vsn_geometryrep.h"
#include "vsn_wireframegeometry.h"
#include <mb_placement3d.h>
#include <surf_plane.h>

VSN_BEGIN_NAMESPACE

class GridGeometryPrivate;
//------------------------------------------------------------------------------
/** \brief  \ru Класс GridGeometry являеться геометрическим представлением плоской сетки.
            \en NOT TRANSLATED. \~
    \details \ru Сетка имеет два типа отображения:
                    1) ScreenOnly Паралельно экрану. В данном случае она растягиваеться по всему окну.
                    Если сетка не паралельна окну тогда она не отображаеться
                    2) ScreenPlane Так же как и при выборе ScreenOnly.
                    Если сетка не паралельна экрану тогда она отображаеться на плоскости в центре ск с размером 2x2xUnitSize\n
                    Этот класс находиться в разработке, его конечное представление может отличаться от текущего.

                \en NOT TRANSLATED.
                    This class is under development, its final representation may differ from the current one. \n \~
    \ingroup Experiment     
*/
// ---
class VSN_CLASS GridGeometry : public WireframeGeometry
{
public:
    enum GridType
    {
        Points,  // draw lines
        Lines,   // draw points
    };

public:
    /// \ru Конструктор. \en Сonstructor. \~
    GridGeometry(const MbPlacement3D & place,  const Viewport & ,Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~GridGeometry();
public:
    /// \ru Установить тип сетки. \en NO TRANSLATION. \~
    void     SetType(GridType);
    /// \ru Вернуть тип сетки. \en NO TRANSLATION. \~
    GridType GetType() const;

    /// \ru Получить плоскость сетки. \en NO TRANSLATION. \~
    const MbPlane& GetPlane() const;
    /// \ru Установить плоскость сетки. \en NO TRANSLATION. \~
    virtual void SetPlane(const MbPlane& plane);

    /// \ru Установить цвет горизонтальной оси. \en Set a color to the horizontal axis. \~
    void SetFirstAxisColor(Color color);
    /// \ru Установить цвет вертикальной оси. \en Set a color to the vertical axis. \~
    void SetSecondAxisColor(Color color);
    /// \ru Получить цвет горизонтальной оси. \en Get a color to the horizontal axis. \~
    Color GetFirstAxisColor()  const;
    /// \ru Получить цвет вертикальной оси. \en Get a color to the vertical axis. \~
    Color GetSecondAxisColor() const;
    /// \ru Задать цвет сетки. \en Set a color of the grid. \~
    void  SetGridColor( Color color );
    /// \ru Получить цвет сетки. \Get a color of the grid. \~
    Color GetGridLinesColor() const;   

    /// \ru Установить размер ячейки сетки. \en Set grid cell size. \~
    void SetUnitSize(float);
    /// \ru Получить размер ячейки сетки. \en NOT TRANSLATED. \~
    float GetUnitSize() const;

    /// \ru Установить кол-во дополнительный деленийю в одной ячейке \en Set an amount of the minor marking in the unit
    void SetMinorCount( uint8_t x /*= 25*/, uint8_t y /*= 25*/ );
    /// \ru Установить кол-во основных деленийю в одной ячейке \en Set an amount of the major marking in the unit
    void SetMajorCount( uint8_t x /*= 5*/,  uint8_t y /*= 5*/  );
    /// \ru Установить кол-во дополнительный деленийю в одной ячейке \en Set an amount of the minor marking in the unit
    void SetMinorCount(uint8_t value);
    /// \ru Установить кол-во основных деленийю в одной ячейке \en Set an amount of the major marking in the unit
    void SetMajorCount(uint8_t value);

    /// \ru Округлить значение координаты, используя параметры сетки. \en NOT TRANSLATED. \~
    MbCartPoint3D  AroundMinor(const MbCartPoint3D &, double eps = Math::LengthEps) const;
    /// \ru Округлить значение координаты, используя параметры сетки. \en NOT TRANSLATED. \~
    MbCartPoint3D  AroundMajor(const MbCartPoint3D &, double eps = Math::LengthEps) const;

protected:
    /// \ru Отрисовать с помощью OpenGL. \en Draw a box with OpenGL.
    virtual void OpenGLDraw(const RenderState& state) override;
    /// \ru Получить габаритный куб. \en Returns bounding box.
    virtual const MbCube& GetBoundingBox() override;
public:
    static MbPlacement3D XYPlane;
    static MbPlacement3D YZPlane;
    static MbPlacement3D XZPlane;

protected:
    VSN_DECLARE_EX_PRIVATE(GridGeometry)
};



VSN_END_NAMESPACE

#endif /*__VSN_GRIDGEOMETRY_H*/