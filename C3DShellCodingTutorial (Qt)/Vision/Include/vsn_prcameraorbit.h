////////////////////////////////////////////////////////////////////////////////
/**
\file
\brief \ru Класс PrCameraOrbit обеспечивает интерактивные действия пользователя, а именно управление 
           камерой, ее вращением по орбите.
       \en PrCameraOrbit class provides interactive user actions, i.e. camera control and its orbiting. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRCAMERAORBIT_H
#define __VSN_PRCAMERAORBIT_H

#include "vsn_prabscamera.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE
class PrCameraOrbitPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrCameraOrbit обеспечивает интерактивное вращение камеры вокруг сцены.
           \en NO TRANSLATION. \~
    \details \ru Назначение горячих кнопок мыши и клавиатуры в процессах PrCameraOrbit можно настроить 
                 по своему усмотрению с помощью дополнительного функционала в базовом классе SetMouseButtonsActivate и
                 SetKeyboardButtonsActivate. Например, для активации процесса можно назначить левую кнопку мыши 
                 с одновременной нажатой клавишой клавиатуры Ctrl. Когда мышь перемещается в плоскости экрана, 
                 вы будете наблюдать перемещение камеры вокруг модели.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrCameraOrbit : public PrAbstractCamera
{
    VSN_OBJECT(PrCameraOrbit)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    PrCameraOrbit(Node* pParent = nullptr);
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrCameraOrbit();
public:
    /// \ru Выдать угловую позицию камеры. \en Returns an angular camera position. \~
    void GetAngles(double& alpha, double& beta, double& gamma);
    /// \ru Cбросить все углы в ноль. \en Resets all angles to zero. \~
    void ResetAngles();
public:
    /// \ru Слот для активизации и инициализации данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Public, slotActiveModified, void slotActiveModified(bool bIsActive))
protected:
    /// \ru Слот для непосредственной работы данного процесса. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotProcessed, void slotProcessed(float dt))
private:
    VSN_DECLARE_EX_PRIVATE(PrCameraOrbit);
    VSN_DISABLE_COPY(PrCameraOrbit);
};

VSN_END_NAMESPACE

#endif /* __VSN_PRCAMERAORBIT_H */
