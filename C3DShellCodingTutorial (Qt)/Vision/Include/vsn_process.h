////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс Process является базой для классов, которые управляют входными данными пользователя, в том числе манипуляцией со сценой.
         \en Process class is a base for classes that handle user input or manipulate with the scene. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PROCESS_H
#define __VSN_PROCESS_H

#include "vsn_essence.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE
class Viewport;
class GraphicsScene;
class ProcessPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс Process служит в качестве базового класса для классов, который управляет входными данными пользователя, в том числе манипуляцией со сценой.
           \en Process class serves as a base for classes and handles user input or manipulates with the scene. \~
  \details \ru Process предоставляет поддержку для преобразования входных данных пользователя в логику взаимодействия. Объект пользовательского процесса 
               реализует виртуальные функции, которые предоставляются для управления процессом такими устройствами, как мышь и клавиатура и т. д. В качестве примера, 
               если бы приложение нуждалось во вращении камеры по орбите с помощью мышки, производный процесс рализовал бы методы OnLButtonDown, OnLButtonDownAndMove, 
               и OnLButtonUp, чтобы предоставить логику вращению камеры по орбите. \n 
               Модуль Vision/GUI предоставляет поддержку для преобразования специальных UI событий в соответствующий метод текущего process, связанного с видом.
               Аналогично, приложение могло бы вручную преобразовать UI событие в совпадающий метод в текущем процессе без использования Vision/GUI toolkit.    
           \en Process provides support for converting user input to interaction logic. A custom process object implements
               the virtual functions that are provided in order to handle process with such devices as mouse and keyboard, etc. For example,
               if the application needed to orbit the camera with the mouse, the derived process would implement the OnLButtonDown, OnLButtonDownAndMove, 
               and OnLButtonUp methods to provide logic for orbiting the camera. \n
               The Vision/GUI module provides support for converting special UI events to the corresponding method of the current 
               process associated with the view. Alternately, the application could manually convert a UI event to the 
               matching method in the current process without relying on the Vision/GUI toolkit.

  \ingroup Vision_Process
*/
// ---
class VSN_CLASS Process : public Essence
{
    VSN_OBJECT(Process);
protected:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    Process(Viewport* pViewport, Node* pParent = nullptr);
public:
    /// \ru Деструктор. \en Destructor. 
    virtual ~Process();
public:
    /// \ru Вернуть указатель на отрисовочный порт. \en NO TRANSLATION.
    Viewport* GetViewport() const;
    /// \ru Установить отрисовочный порт. \en NO TRANSLATION.
    virtual void SetViewport(Viewport* pViewport);

    /// \ru Вернуть указатель на сцену. \en NO TRANSLATION.
    GraphicsScene* GetGraphicsScene() const;
    /// \ru Установить указатель на сцену. \en NO TRANSLATION.
    virtual void SetGraphicsScene(GraphicsScene* pGraphicsScene);
public:
    /// \ru Сигнал генерируется, если в сцене произошли изменения относительно камеры. \en NO TRANSLATION. \~
    VSN_SIGNAL(Public, OnModified, void OnModified())
protected:
    explicit Process(ProcessPrivate& dd, Node* parent = nullptr);
private:
    VSN_DECLARE_EX_PRIVATE(Process);
};
VSN_END_NAMESPACE

#endif /* __VSN_PROCESS_H */
