////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс PrCameraZoom обеспечивает масштабирование сцены относительно ее центра.
         \en PrCameraZoom class provides scene zooming about its center. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAZOOM_H
#define __VSN_PRCAMERAZOOM_H

#include "vsn_prabscamera.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE
class Viewport;
class PrCameraZoomPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraZoom масштабирования сцены относительно ее центра.
           \en PrCameraZoom class provides scene zooming about its center. \~
  \details \ru Особенность процесса PrCameraZoom - увеличение размера по направлению к цели. PrCameraZoom
               осуществляет два режима работы: с помощью колеса мыши, если IsZoomWheel взведена, как true,
               иначе PrCameraZoom реализует действия "наезд/отъезд" камеры на цель. PrCameraZoom также имеет возможность,
               как и остальные процессы управления, назначить горячие кнопки мыши и клавиатуры для активизации действий
               по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
               SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши
               с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана,
               вы будете наблюдать перемещение камеры вокруг модели.
           \en NO TRANSLATION.\n \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraZoom : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraZoom)
public:
    /** \brief \ru Конструктор по умолчанию.
               \en Default constructor. \~ 
        \param[in] pViewport - \ru Порт представления.
                               \en Representation port. \~
    */
    PrCameraZoom(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraZoom();
public:
    /// \ru Вернуть признак масштабирования с помощью колеса мыши. \en NO TRANSLATION. \~
    bool IsZoomWheel() const;
    /// \ru Установить признак масштабирования с помощью колеса мыши. \en NO TRANSLATION. \~
    void SetZoomWheel(bool bWheel);

    /// \ru Возвратить коэффициент масштабирования. \en Returns zoom factor. \~
    double GetMaxZoomFactor() const;
    /// \ru Установить максимальный коэффициент масштаба. \en NO TRANSLATION. \~
    void SetMaxZoomFactor(double factor);
public:
    /// \ru Слот для активизации и инициализации данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotActiveModified, void slotActiveModified(bool bIsActive))
    /// \ru Слот для считывания данных мыши при использовании колеса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseWheel, void slotMouseWheel(WheelEventObject* pWheel))
protected:
    /// \ru Слот для непосредственной работы данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotProcessed, void slotProcessed(float dt))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraZoom);
    VSN_DISABLE_COPY(PrCameraZoom);
};
VSN_END_NAMESPACE

#endif /* __VSN_PRCAMERAZOOM_H */
