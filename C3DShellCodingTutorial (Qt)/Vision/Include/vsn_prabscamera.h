////////////////////////////////////////////////////////////////////////////////
/**
\file
    \brief \ru Класс PrAbstractCamera является базовым классом, который обрабатывает 
               пользовательский ввод и работает над управлением сценой.
           \en NO TRANSLATION. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PRABSCAMERA_H
#define __VSN_PRABSCAMERA_H

#include "vsn_process.h"
#include "vsn_mouseevent.h"
#include "vsn_global.h"

VSN_BEGIN_NAMESPACE
class PrAbstractCameraPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс PrAbstractCamera является базовым классом, который обрабатывает 
               пользовательский ввод и работает над управлением сценой.
           \en NO TRANSLATION. \~
    \details \ru PrAbstractCamera обеспечивает поддержку пользовательского ввода и логику взаимодействия.
                 Класс PrAbstractCamera реализует функции для настройки активности данного процесса для основных устройств,
                 таких, например, как мышь и клавиатура. Пользователь может настроить взаимодействие этих устройств 
                 по своему усмотрению с помощью функций SetMouseButtonsActivate и SetKeyboardButtonsActivate.
             \en NO TRANSLATION.\n \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PrAbstractCamera : public Process
{
    VSN_OBJECT(PrAbstractCamera);
    VSN_PROP_READ_WRITE_NOTIFY(linearSpeed, GetLinearSpeed, SetLinearSpeed, OnLinearSpeedModified)
public:
    /// \ru Деструктор. \en Destructor. \~ 
    virtual ~PrAbstractCamera();
protected:
    /// \ru Конструктор для внутреннего использования. \en NO TRANSLATION. \~ 
    explicit PrAbstractCamera(PrAbstractCameraPrivate& dd, Node* parent = nullptr);
public:
    /// \ru Вернуть текущую линейную скорость процесса камеры. Линейная скорость определяет скорость движения камеры. \en NO TRANSLATION. \~
    float GetLinearSpeed() const;
    /// \ru Установить линейную скорость процесса камеры. Линейная скорость определяет скорость движения камеры. \en NO TRANSLATION. \~
    void SetLinearSpeed(float linearSpeed);

    // \ru Вернуть кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    std::vector<int> GetMouseButtonsActivate() const;
    // \ru Установить кнопки мыши для активации процесса. \en NO TRANSLATION. \~
    void SetMouseButtonsActivate(const std::vector<int>& vecKey);

    // \ru Вернуть кнопки клавиатуры для активации процесса. \en NO TRANSLATION. \~
    std::vector<int> GetKeyboardButtonsActivate() const;
    // \ru Установить кнопки клавиатуры для активации процесса. \en NO TRANSLATION. \~
    void SetKeyboardButtonsActivate(const std::vector<int>& vecKey);

    /// \ru Активировать процесс. \en Activates process. \~
    virtual void Activate(ProcessEvent* /*event*/) {}
    /// \ru Обработка события перемещения мыши. \en Processing mouse move event. \~
    virtual bool Motion(ProcessEvent* /*event*/) { return 0; }
public:
    /// \ru Сигнал генерируется, если в сцене произошли изменения относительно камеры. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnCameraModified, void OnCameraModified())
    /// \ru Сигнал будет сгенерирован при изменении линейной скорости движения камеры. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnLinearSpeedModified, void OnLinearSpeedModified())
protected:
    /// \ru Слот принимает события от манипулятора мышь. \en NO TRANSLATION. \~
    VSN_SLOT(Protected, slotMouseMove, void slotMouseMove(MouseEventObject* pMouse))
private:
    VSN_DECLARE_EX_PRIVATE(PrAbstractCamera);
};
VSN_END_NAMESPACE

#endif /* __VSN_PRABSCAMERA_H */
