#ifndef __VSN_LABELGEOMETRY_H
#define __VSN_LABELGEOMETRY_H

#include "vsn_global.h"
#include "vsn_geometryrep.h"
#include "vsn_wireframegeometry.h"


#include <string>
#include <mb_rect.h>
#include <mb_placement3d.h>

VSN_BEGIN_NAMESPACE


class LabelGeometryPrivate;
namespace Experiment
{
//------------------------------------------------------------------------------
/** \brief  \ru Класс LabelGeometry - геометрический объект отображающий текст в рамке на плоскости.
            \en NO TRANSLATION. \~


            Этот класс находиться в разработке, его конечное представление может отличаться от текущего.
            This class is under development, its final representation may differ from the current one.

    \ingroup Experiment
*/
// ---
    class VSN_CLASS LabelGeometry : public WireframeGeometry
    {
        VSN_OBJECT(LabelGeometry)
    public:
        enum Border
        {
            brd_Left = 1,
            brd_Rigth = 1 << 1,
            brd_Top = 1 << 2,
            brd_Bottom = 1 << 3
        };

        enum class TextOrientation
        {
            Freeze,     ///< \ru В плоскости размера. \en NO TRANSLATION.
            ScreenOnly, ///< \ru В плоскости экрана. \en NO TRANSLATION.
            Readable,   ///< \ru В плоскости размера с доворотом по вектору взгляда. \en NO TRANSLATION.
        };
    public:
        /// \ru Конструктор. \en NO TRANSLATION.\~
        LabelGeometry(Node* pParent = nullptr);
        /// \ru Конструктор с инициализацией текста. \en NO TRANSLATION.\~
        LabelGeometry(const String & text, Node* pParent = nullptr);
        /// \ru Деструктор. \en NO TRANSLATION.\~
        virtual ~LabelGeometry();

        /// \ru Инициализировать параметры. \en NO TRANSLATION.\~
        void Init(const String & text, const MbPlacement3D & place, int border = 0);

        /// \ru Установить плоскость в которой будет отображаться текст. \en NO TRANSLATION.\~
        void SetPlace(const MbPlacement3D & place);

        /// \ru Задать текст. \en NO TRANSLATION.\~
        void SetText(const WString & text);

        /// \ru Задать видимые границы рамки. \en NO TRANSLATION.\~
        void SetBorder(int);

        /// \ru Получить видимые границы рамки. \en NO TRANSLATION.\~
        void SetFontSize(unsigned int size);

        /// \ru вернуть ширину метки в маштабе 1:1. \en NO TRANSLATION.\~
        float GetWidth() const;
        /// \ru вернуть высоту метки в маштабе 1:1. \en NO TRANSLATION.\~
        float GetHeight() const;

        /// \ru вернуть ширину текста в маштабе 1:1. \en NO TRANSLATION.\~
        float GetTextWidth() const;
        /// \ru вернуть высоту текста в маштабе 1:1. \en NO TRANSLATION.\~
        float GetTextHeight() const;

        /// \ru Сделать текст масштабируемым. \en NO TRANSLATION.\~
        void SetScalable(bool value);
        /// \ru Узнать являеться ли текст масштабируемым \en NO TRANSLATION.\~
        bool IsScalable() const;

        /// \ru Установить тип отображения текста. \en NO TRANSLATION.\~
        void            SetOrientation(TextOrientation);
        /// \ru Получить тип отображения текста. \en NO TRANSLATION.\~
        TextOrientation GetOrientation() const;

        /// \ru Установить отступы текста снаружи от границ. \en NO TRANSLATION.\~
        void           SetOffset(const MbRect & offset);
        /// \ru Получить отступы текста снаружи от границ. \en NO TRANSLATION.\~
        const MbRect & GetOffset() const;

        /// \ru Установить отступы текста внутри от границ. \en NO TRANSLATION.\~
        void           SetMargin(const MbRect & margin);
        /// \ru Получить отступы текста внутри от границ. \en NO TRANSLATION.\~
        const MbRect & GetMargin() const;

        /// \ru Установить позицию текста. \en NO TRANSLATION.\~
        void             SetOrigin(MbVector & origin);
        /// \ru Получить позицию текста. \en NO TRANSLATION.\~
        const MbVector & GetOrigin() const;

    public:
        /// \ru Отрисовать с помощью OpenGL. \en Draw a box with OpenGL.\~
        virtual void OpenGLDraw(const RenderState& state) override;
        /// \ru Получить габаритный куб. \en Returns bounding box.\~
        virtual const MbCube& GetBoundingBox() override;
        /// \ru Блокировать PixelCulling для этой геометрии. \en NO TRANSLATION.\~
        virtual bool IsIgnorePixelCulling() const override;

    protected:
        VSN_DECLARE_EX_PRIVATE(LabelGeometry)
    };
}


VSN_END_NAMESPACE

#endif /*__VSN_LABELGEOMETRY_H*/