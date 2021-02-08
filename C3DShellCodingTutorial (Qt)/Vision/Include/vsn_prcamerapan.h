////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс PrCameraPan панорамирует камеру относительно текущего вида.
         \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAPAN_H
#define __VSN_PRCAMERAPAN_H

#include "vsn_prabscamera.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class Viewport;
class PrCameraPanPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraPan панорамирует камеру относительно текущего вида.
           \en NO TRANSLATION. \~
    \details \ru Назначение горячих кнопок мыши и клавиатуры в процессах PrCameraPan можно настроить
                 по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
                 с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
                 вы будете наблюдать перемещение камеры вокруг модели.
             \en NO TRANSLATION.\n \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraPan : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraPan)
public:
    /** \brief \ru Конструктор по умолчанию.
                \en Default constructor. \~ 
        \param[in] pViewport - \ru Порт представления.
                               \en Representation port. \~
    */
    PrCameraPan(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. 
    virtual ~PrCameraPan();
public:
    /// \ru Слот для активизации и инициализации данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Public, slotActiveModified, void slotActiveModified(bool bIsActive))
protected:
    /// \ru Слот для непосредственной работы данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotProcessed, void slotProcessed(float dt))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraPan);
    VSN_DISABLE_COPY(PrCameraPan);
};


VSN_END_NAMESPACE

#endif /* __VSN_PRCAMERAPAN_H */
