////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Функции узла сцены.
           \en Scene segment features. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __VSN_SEGMENTFEATURES_H
#define __VSN_SEGMENTFEATURES_H

#include "vsn_feature.h"

VSN_BEGIN_NAMESPACE

namespace Features
{
    class ScreenPlaneOnlyPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Экранная ориентация сегмента сцены.
                \en Screen only orientation. \~

        \details \ru Модификатор который доворачивает сегмент до экранных координат(XY).\n
                 \en The Feature that rotate the scene segment to the screen orientation(XY). \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS ScreenPlaneOnly : public Feature
    {
    public:
        ScreenPlaneOnly(Node* pParent = nullptr);
        ~ScreenPlaneOnly();
    private:
        VSN_DECLARE_EX_PRIVATE(ScreenPlaneOnly);
    };

    class NoScalablePrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Не масштабируемый сегмент сцены.
                \en No scalable segment. \~

        \details \ru Модификатор который делайт узел сцены не масштабируемым.\n
                 \en The Feature that makes scene segment not scalable. \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS NoScalable : public Feature
    {
    public:
        NoScalable(Node* pParent = nullptr);
        ~NoScalable();
    private:
        VSN_DECLARE_EX_PRIVATE(NoScalable);
    };

    class DoubleSidedLightingPrivate;
    //------------------------------------------------------------------------------
    /** \brief  \ru Двустороннее освещение
                \en Double-Side Lighting. \~

        \details \ru Модификатор который включает двустороннее освещение у объекта.\n
                 \en The Feature that turns on double-side lighting of the object. \~

        \ingroup Features
    */
    // ---
    class VSN_CLASS DoubleSidedLighting : public Feature
    {
    public:
        DoubleSidedLighting(Node* pParent = nullptr);
        ~DoubleSidedLighting();
    private:
        VSN_DECLARE_EX_PRIVATE(DoubleSidedLighting);
    };
}

VSN_END_NAMESPACE

#endif // __VSN_SEGMENTFEATURES_H
