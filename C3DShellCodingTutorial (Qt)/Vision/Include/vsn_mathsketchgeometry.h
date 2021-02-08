////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathSketchGeometry представляет геометрию для последующей отрисовки, 
             которая была сгенерирована с помощью математического представления.
         \en Class MathSketchGeometry presents geometry for next rendering that was
             generated with math representation. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SKETCHGEOMETRY_H
#define __VSN_SKETCHGEOMETRY_H

#include <plane_instance.h>

#include "vsn_wireframegeometry.h"
#include "vsn_global.h"



VSN_BEGIN_NAMESPACE
namespace Experiment
{
    class MathSketchGeometryPrivate;
    //------------------------------------------------------------------------------
    /** \brief \ru Класс MathSketchGeometry представляет геометрию для последующей отрисовки, которая была сгенерирована с помощью математического представления.
               \en Class MathSketchGeometry presents geometry for next rendering that was generated with math representation. \~
        \details \ru Класс MathSketchGeometry принимает указатель на математическое представление эскиза MbPlaneInstance для последующей генерации визуального представления.
                     Класс MathSketchGeometry представляет ряд полезных функций. С помощью функции GetMathNameByGeometry GetGeometryNameByMath вы можете получить идентификацию примитивов из
                     визуального представления в математическое и наоборот.
                     Этот класс находиться в разработке, его конечное представление может отличаться от текущего.\n.
                 \en NO TRANSLATION;
                     This class is under development, its final representation may differ from the current one.\~


        \ingroup Experiment
        */
        // ---
    class VSN_CLASS MathSketchGeometry final : public WireframeGeometry
    {
        VSN_OBJECT(MathSketchGeometry);
    public:
        /// \ru Конструктор. \en Constructor. \~
        MathSketchGeometry(Node* pParent = nullptr);
        /// \ru Деструктор. \en Destructor. \~
        virtual ~MathSketchGeometry();
    public:
        void Clear();
        /// \ru Построиь геометрию эскиза. \en Build sketch geometry. \~
        void Rebuild(const MbPlaneInstance & instance, double sag = Math::visualSag);
        /// \ru Вернуть математический идентификатор примитива по уникальному идентификатору этой геометрии. \en Returns a math identifier of primitive by the unique identifier of this geometry. \~
        SimpleName GetMathNameByGeometry(uint geomId) const;
        /// \ru Вернуть геометрический идентификатор примитива по уникальному идентификатору математического примитива. \en Returns a geometric identifier of primitive by the unique identifier of math primitive. \~
        uint       GetGeometryNameByMath(SimpleName mathId) const;
    public:
        /// \ru Получить габаритный куб объекта. \en Returns object bounding box. \~
        virtual const MbCube & GetBoundingBox() override;

    private:
        /// \ru Отрисовка тела. \en Renders a solid body. \~
        virtual void OpenGLDraw(const RenderState& state) override;
    private:
        VSN_DISABLE_COPY(MathSketchGeometry);
        VSN_DECLARE_EX_PRIVATE(MathSketchGeometry);
    };
}
VSN_END_NAMESPACE

#endif /* __VSN_SKETCHGEOMETRY_H */
