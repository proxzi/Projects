////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru Класс MathSketchRep является вспомогательным классом и представляет 
             API для управления геометрией.
         \en MathSketchRep class is an auxiliary class and represents API to control geometry. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SKETCHREP_H
#define __VSN_SKETCHREP_H

#include <plane_instance.h>

#include "vsn_wireframegeometry.h"
#include "vsn_geometryrep.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
namespace Experiment
{

    class MathSketchRepPrivate;
    //------------------------------------------------------------------------------
    /** \brief \ru Класс MathSketchRep является вспомогательным классом и представляет API для управления геометрией.
               \en MathSketchRep class is an auxiliary class and represents API to control geometry. \~
      \details \ru MathSketchRep создает MathSketchGeometry и содержит его указатель на протяжение всей своей жизни.
                   MathSketchRep представляет ряд полезных функций для управления своей геометрией.Для вычисления шага триангуляции поверхностей и граней,
                     вы можете воспользоваться функцией SetVisualSag и вызвать перегенерацию триангуляции в реальном времени, что влияет на качество
                     отображения геометрии. 

                   Этот класс находиться в разработке, его конечное представление может отличаться от текущего.\n.
               \en NO TRANSLATION;
                   This class is under development, its final representation may differ from the current one.\~


    \ingroup Experiment
    */
    // ---
    class VSN_CLASS MathSketchRep final : public GeometryRep
    {
        VSN_OBJECT(MathSketchRep);
    public:
        /// \ru Конструктор. \en Constructor. \~
        MathSketchRep(Node* pParent = nullptr);
        /// \ru Деструктор. \en Destructor. \~
        virtual ~MathSketchRep();
    public:
        /// \ru Построиь геометрию эскиза. \en Build sketch geometry. \~
        void SetInstance(const MbPlaneInstance * instance);
        /// \ru Построиь геометрию плоского матиматического объекта. \en \~
        void SetInstance(MbPlaneItem & item, const MbPlacement3D & place);
        /// \ru Вернуть математический идентификатор примитива по уникальному идентификатору этой геометрии. \en Returns a math identifier of primitive by the unique identifier of this geometry. \~
        SimpleName GetMathNameByGeometry(uint geomId) const;

        /// \ru Установить максимально допустимый прогиб кривой или поверхности в соседних точках на расстоянии шага.
        /// \en Sets the maximum permissible sag of a curve or surface at adjacent points a step away. \~
        VSN_SLOT(Public, SetVisualSag, void SetVisualSag(double sag))
    private:
        VSN_DISABLE_COPY(MathSketchRep);
        VSN_DECLARE_EX_PRIVATE(MathSketchRep);
    };

}
VSN_END_NAMESPACE

#endif /* __VSN_SKETCHREP_H */
