////////////////////////////////////////////////////////////////////////////////
/** 
  \file  
  \brief \ru Класс ProcessEvent является событием, а также базовым классом для всех классов событий.
         \en ProcessEvent class is the event and also base class for all event classes. \~

*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_PROCESSEVENT_H
#define __VSN_PROCESSEVENT_H

#include <mb_cart_point.h>
#include <mb_cube.h>
#include "vsn_size.h"
#include "vsn_point.h"
#include "vsn_rect.h"
#include "vsn_region.h"
#include "vsn_string.h"
#include "vsn_namespace.h"

#include "vsn_global.h"

VSN_BEGIN_NAMESPACE

class ProcessEventPrivate;
//------------------------------------------------------------------------------
/** \brief \ru Класс ProcessEvent является событием, а также базовым классом для всех классов событий. Объекты событий содержат параметры события.
           \en ProcessEvent class is the event and also base class for all event classes. Event objects contain event parameters. \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS ProcessEvent
{
public:
    /// \ru Тип события, который определяет состояние мыши, клавиатуры и подобных устройств в реальном режиме времени. \en The event type defines state of mouse, keyboard and such devices in real time mode.
    enum EventType
    {
        None = 0,           ///< \ru Недействительное событие. \en Invalid event.

        LButtonDown,        ///< \ru Левая кнопка мыши нажата. \en The left mouse button is pressed.
        LButtonUp,          ///< \ru Левая кнопка мыши отпущена. \en The left mouse button is released.
        LButtonDblClk,      ///< \ru Левая кнопка мыши нажата дважды. \en The left mouse button is double-clicked.

        MButtonDown,        ///< \ru Средняя кнопка мыши нажата. \en The middle mouse button is pressed.
        MButtonUp,          ///< \ru Средняя кнопка мыши отпущена. \en The middle mouse button is released.
        MButtonDblClk,      ///< \ru Средняя кнопка мыши нажата дважды. \en The middle mouse button is double-clicked.

        RButtonDown,        ///< \ru Правая кнопка мыши нажата. \en The right mouse button is pressed.
        RButtonUp,          ///< \ru Правая кнопка мыши отпущена. \en The right mouse button is released.
        RButtonDblClk,      ///< \ru Правая кнопка мыши нажата дважды. \en The right mouse button is double-clicked.

        MouseMove,          ///< \ru Курсор мыши движется. \en The mouse cursor moves.
        HoverMove,          ///< \ru Курсор мыши над объектом. \en NO TRANSLATION.

        MouseWheel,         ///< \ru Колесико мыши крутится. \en The mouse wheel moves.
        MouseWheelUp,       ///< \ru Колесико мыши прокручивается вверх. \en The mouse wheel is scrolled up.
        MouseWheelDown,     ///< \ru Колесико мыши прокручивается вниз. \en The mouse wheel is scrolled down.
        Resize,             ///< \ru Изменились размеры. \en Resize.
        Close,
        Timer,              ///< \ru Говорит само за себя. \en Self-explanatory.

        KeyDown,            ///< \ru Клавиша на клавиатуре нажата. \en A key on the keyboard is pressed.
        KeyUp,              ///< \ru Клавиша на клавиатуре отпущена. \en A key on the keyboard is released.

        Selection,          ///< \ru Событие общего выбора. \en General selection event.

        JoyStickTranslate,  ///< \ru Трехмерное перемещение вектора от 3D устройства. \en Vector movement from a 3D device.
        JoyStickRotate,     ///< \ru Набор значений поворота от 3D устройства. \en A rotation set values from a 3D device.
        JoyStickButton,     ///< \ru Кнопка нажатая от 3D устройства. \en A button pressed from a 3D device.

        Camera,             ///< \ru Изменение позиции камеры. \en Repositioning camera.
        ChildRemoved,
        Show,
        Draw,
        Expose,
        WindowStateModified,
        UpdateInquiry,      ///< \ru Окно должно быть перерисовано

        WinEventAct,
        ThreadChange,
        DeferredDelete,     ///< \ru Отложенное удаление. \en Deferred delete.
        NonClientAreaMouseMove, 
        SockAct,
        Quit,
        FutureCallOut,
        MetaCall,
        NullTimerEvent,
        PlatformRenderingArea,   ///< \ru Область отображения платформы, созданная или подлежащая уничтожению. \en NOT TRANSLATED

        User = 500,         ///< \ru Идентификатор начального события пользователя. \en First user event id.
        MaxUser = 65535     ///< \ru Идентификатор конечного события пользователя. \en Last user event id.
    };

public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    explicit ProcessEvent(EventType type);
    /// \ru Конструктор копирования. \en Copy constructor. 
    ProcessEvent(const ProcessEvent& other);
    /// \ru Деструктор. \en Destructor. 
    virtual ~ProcessEvent();
public:
    /// \ru Вернуть идентификатор типа событий. \en Returns event type identifier. 
    EventType GetType() const;
    void SetApplied(bool bApplied);
    bool IsApplied() const;
    void SetApply();
    void SetReject();
protected:
    ProcessEventPrivate* m_pData;
private:
    friend class ThreadData;
    friend class BaseApplication;
    friend class BaseApplicationPrivate;
};

//------------------------------------------------------------------------------
/** \brief \ru Класс InputEvent является базовым классом для событий, который описывает вводимые пользователем данные.
           \en InputEvent class is the base class for events that describes user input. \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS InputEvent : public ProcessEvent
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    InputEvent(EventType type);
    /// \ru Конструктор копирования. \en Copy constructor. 
    InputEvent(const InputEvent& other);
    /// \ru Деструктор. \en Destructor.
    ~InputEvent();
public:
    /// \ru True, если клавиша Ctrl сейчас нажата. \en True if Ctrl key is currently pressed.
    bool Control() const      { return(m_flags & mb_Control) != 0; }
    /// \ru True, если клавиша Shift сейчас нажата. \en True if Shift key is currently pressed.
    bool Shift() const          { return(m_flags & mb_Shift) != 0; }
    /// \ru True, если клавиша Alt сейчас нажата. \en True if Alt key is currently pressed.
    bool Alt() const          { return(m_flags & mb_Alt) != 0; }
    /// \ru True, если левая клавиша Alt нажата. \en True if the left Alt key is pressed.
    bool LeftAlt() const      { return(m_flags & mb_Left_Alt) != 0; }
    /// \ru True, если левая клавиша Ctrl нажата. \en True if the left Ctrl key is pressed.
    bool LeftControl() const  { return(m_flags & mb_Left_Control) != 0; }
    /// \ru True, если левая клавиша Shift нажата. \en True if the left Shift key is pressed.
    bool LeftShift() const      { return(m_flags & mb_Left_Shift) != 0; }
    /// \ru True, если правая клавиша Alt нажата. \en True if the right Alt key is pressed.
    bool RightAlt() const      { return(m_flags & mb_Right_Alt) != 0; }
    /// \ru True, если правая клавиша Ctrl нажата. \en True if the right Ctrl key is pressed.
    bool RightControl() const { return(m_flags & mb_Right_Control) != 0; }
    /// \ru True, если правая клавиша Shift нажата. \en True if the right Shift key is pressed.
    bool RightShift() const   { return(m_flags & mb_Right_Shift) != 0; }

    /// \ru Возвращает бит ProcessEvent флагов, таких как mb_LButton, для специальных событий клавиш Shift, Ctrl и левая, средняя и правая кнопки мыши. \en Returns ProcessEvent bit flags like mb_LButton for special events of Shift and Ctrl keys as well as left, middle and right mouse buttons.
    unsigned int GetFlags() const { return m_flags; }

    /** \brief \ru Этот метод устанавливает побитовые флаги, которые показывают состояние кнопок мыши, клавиш Shift и Ctrl.
                \en This method sets bitwise flags that shows the state of mouse buttons, Shift and Ctrl keys. \~
        \param[in] flags - \ru Побитовые флаги для состояния мыши и клавиш. Например, если и клавиша Shift, и левая кнопка мыши нажаты, пропустить mb_Shift|mb_LButton.   
                            \en Bitwise flags for mouse and key states. For example, if both Shift key and left mouse button are pressed, pass mb_Shift|mb_LButton. \~
    */
    void SetFlags(int flags) { m_flags = flags; }

protected:
    unsigned int m_flags; ///< \ru Флаги показывают, какая из кнопок мыши нажата и нажаты ли клавиши Shift и Ctrl на клавиатуре. \en Flags indicate which of mouse buttons is pressed and if Shift and Ctrl keyboard keys are pressed.
};

//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS KeyEvent : public InputEvent
{
public:
    KeyEvent(EventType type, int key, const String& text = String(),
        bool autorep = false, unsigned short count = 1);
    KeyEvent(EventType type, int key, uint32 nativeScanCode, uint32 nativeVirtualKey, uint32 nativeModifiers,
        const String &text = String(), bool autorep = false, unsigned short count = 1);
    ~KeyEvent();

    void Init(EventType type, int key, const String& text = String(), 
        bool autorep = false, unsigned short count = 1);
    void Init(EventType type, int key, uint32 nativeScanCode, uint32 nativeVirtualKey, 
        uint32 nativeModifiers, const String &text = String(), bool autorep = false, unsigned short count = 1 );
public:
    int GetKey() const { return k; }
    inline String GetText() const { return txt; }
    inline bool IsAutoRepeat() const { return autor; }
    inline int GetCount() const { return int(c); }

    inline uint32 nativeScanCode() const { return nScanCode; }
    inline uint32 nativeVirtualKey() const { return nVirtualKey; }
    inline uint32 nativeModifiers() const { return nModifiers; }
protected:
    String txt;
    int k;
    uint32 nScanCode;
    uint32 nVirtualKey;
    uint32 nModifiers;
    unsigned short c;
    unsigned short autor : 1;
};

//------------------------------------------------------------------------------
/** \brief \ru Класс MouseEvent содержит параметры, которые описывают события мыши.
           \en MouseEvent class contains parameters that describe a mouse event. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS MouseEvent : public InputEvent
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    MouseEvent(EventType type);
    /// \ru Конструктор копирования. \en Copy constructor. 
    MouseEvent(const MouseEvent& other);
    /// \ru Деструктор. \en Destructor.
    ~MouseEvent();
public:
    /// \ru True, если левая кнопка мыши нажата. \en True if the left mouse button is pressed.
    bool LButton() const    { return(m_flags & mb_LButton) != 0; }
    /// \ru True, если средняя кнопка мыши нажата. \en True if the middle mouse button is pressed.
    bool MButton() const    { return(m_flags & mb_MButton) != 0; }
    /// \ru True, если правая кнопка мыши нажата. \en True if the right mouse button is pressed.
    bool RButton() const    { return(m_flags & mb_RButton) != 0; }
public:
    /// \ru Возвращает позицию мыши в координатах окна. \en Returns the mouse position in window coordinates.
    inline const IntPoint& GetScreenPos() const { return m_pntScreen; }
    /** \brief \ru Этот метод получает и хранит информацию о событиях мыши в координатах окна.
                \en This method receives and stores mouse event information in window coordinates. \~
        \param[in] point - \ru Точка в координатах окна.
                            \en IntPoint in window coordinates. \~
    */
    inline void SetScreenPos(const IntPoint& point) { m_pntScreen = point; }
    // TODO:
    inline const IntPoint& GetWindowPos() const { return m_pntWindow; }
    // TODO:
    inline void SetWindowPos(const IntPoint& point) { m_pntWindow = point; }
    // TODO:
    inline const IntPoint& GetClientPos() const { return m_pntClient; }
    // TODO:
    inline void SetClientPos(const IntPoint& point) { m_pntClient = point; }
protected:
    IntPoint m_pntScreen;
    IntPoint m_pntWindow;
    IntPoint m_pntClient;
};

class VSN_CLASS HoverEvent : public InputEvent
{
public:
    HoverEvent(EventType type, const IntPoint& pos, const IntPoint& oldPos);
    ~HoverEvent();
public:
    /// \ru True, если левая кнопка мыши нажата. \en True if the left mouse button is pressed.
    bool LButton() const { return(m_flags & mb_LButton) != 0; }
    /// \ru True, если средняя кнопка мыши нажата. \en True if the middle mouse button is pressed.
    bool MButton() const { return(m_flags & mb_MButton) != 0; }
    /// \ru True, если правая кнопка мыши нажата. \en True if the right mouse button is pressed.
    bool RButton() const { return(m_flags & mb_RButton) != 0; }
    inline IntPoint GetPosition() const { return m_pnt; }
    inline IntPoint GetOldPosition() const { return m_oldPnt; }
protected:
    IntPoint m_pnt;
    IntPoint m_oldPnt;
};


//------------------------------------------------------------------------------
/** \brief \ru Класс WheelEvent содержит параметры, которые описывают события колесика мыши.
           \en WheelEvent class contains parameters that describes a scroll wheel event. \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS WheelEvent : public InputEvent
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor.
    WheelEvent();
    /// \ru Конструктор копирования. \en Copy constructor. 
    WheelEvent(const WheelEvent& other);
    /// \ru Деструктор. \en Destructor.
    ~WheelEvent();
public:
    /// \ru Возвращает измененное значение позиции колесика мыши. \en Returns the mouse wheel position changed value.
    int GetWheelDelta() const { return m_wheelDelta; }
    /** \brief  \ru Этот метод устанавливает измененное значение позиции колесика мыши.
                \en This method sets the mouse wheel position changed value. \~
        \param[in] wheelDelta - \ru Новое измененное значение колесика мыши.
                                  \en New mouse wheel changed value. \~
    */
    void SetWheelDelta(int wheelDelta);
    // TODO:
    inline const IntPoint& GetWindowPos() const { return m_pntWindow; }
    // TODO:
    inline void SetWindowPos(const IntPoint& point) { m_pntWindow = point; }
protected:
    int  m_wheelDelta;
    IntPoint m_pntWindow;
};


//------------------------------------------------------------------------------
/** \brief \ru Событие изменения положения камеры.
           \en Camera position change event. \~
  \ingroup Vision_Process
*/
// ---
class VSN_CLASS CameraEvent : public ProcessEvent
{
public:
  /** \brief \ru Конструктор по умолчанию.
             \en Default constructor. \~ 
    \param[in] x - \ru Значение вдоль оси Ox.
                   \en Value along X-axis. \~
    \param[in] y - \ru Значение вдоль оси Oy.
                   \en Value along Y-axis. \~
  */
  CameraEvent(double x = 0.0, double y = 0.0);

  /// \ru Деструктор. \en Destructor. 
  virtual ~CameraEvent();

public:
  /** \brief \ru Вернуть пользовательскую позицию.
             \en Returns user position. \~ 
    \return \ru Точка.
            \en IntPoint. \~
  */
  const MbCartPoint& GetPosition() const;

  /** \brief \ru Установить позицию.
             \en Sets position. \~ 
    \param[in] point - \ru Точка.
                       \en IntPoint. \~
  */
  void SetPosition( const MbCartPoint& point );

  /** \brief \ru Установить позицию.
             \en Sets position. \~ 
    \param[in] x - \ru Значение вдоль оси Ox.
                   \en Value along X-axis. \~
    \param[in] y - \ru Значение вдоль оси Oy.
                   \en Value along Y-axis. \~
  */
  void SetPosition( double x, double y );

  /** \brief \ru Вернуть нормализацию центра касания.
             \en Returns normalization of touch center. \~ 
    \return \ru Нормализация положения центра касаний.
            \en Normalization of touch center position. \~
  */
  const MbVector& GetNormalizeTouchCenter() const;

  /** \brief \ru Установить нормализацию центра касания.
             \en Sets normalization of touch center. \~ 
    \param[in] normalize - \ru Вектор.
                           \en Vector. \~
  */
  void SetNormalizeTouchCenterPosition( const MbVector& normalize );

  /** \brief \ru Вернуть вектор перемещения.
             \en Returns movement vector. \~ 
    \return \ru Вектор перемещения.
            \en Movement vector. \~
  */
  const MbVector& GetTranslation() const;

  /** \brief \ru Установить вектор перемещения.
             \en Sets movement vector. \~ 
    \param[in] translation - \ru Вектор перемещения.
                             \en Movement vector. \~
  */
  void SetTranslation(const MbVector& translation);

  /** \brief \ru Установить данные для трансформации.
             \en Sets transformation data. \~ 
    \param[in] translation - \ru Вектор перемещения.
                             \en Movement vector. \~
    \param[in] rotation - \ru Угол поворота.
                          \en Rotation angle. \~
    \param[in] zoomFactor - \ru Коэффициент масштабирования.
                            \en Zoom factor. \~
  */
  void SetTransformation(const MbVector& translation, double rotation = 0.0, double zoomFactor = 1.0);

  /** \brief \ru Вернуть габаритный куб.
             \en Returns bounding box. \~ 
    \return \ru Габаритный куб.
            \en Bounding box. \~
  */
  const MbCube& GetBoundingBox() const;

  /** \brief \ru Установить габаритный куб.
             \en Sets bounding box. \~ 
    \param[in] boundingBox - \ru Габаритный куб.
                             \en Bounding box. \~
  */
  void SetBoundingBox( const MbCube& boundingBox );

  /** \brief \ru Вернуть угол поворота.
             \en Returns rotation angle. \~ 
    \return \ru Угол поворота.
            \en Rotation angle. \~
  */
  double GetRotationAngle() const;

  /** \brief \ru Установить угол поворота.
             \en Sets rotation angle. \~ 
    \param[in] rotation - \ru Угол поворота.
                          \en Rotation angle. \~
  */
  void SetRotation( double rotation );

  /** \brief \ru Вернуть коэффициент масштабирования.
             \en Returns zoom factor. \~ 
    \return \ru Коэффициент масштабирования.
            \en Zoom factor. \~
  */
  double GetZoomFactor() const;

  /** \brief \ru Установить коэффициент масштабирования.
             \en Sets zoom factor. \~ 
    \param[in] zoomFactor - \ru Коэффициент масштабирования.
                            \en Zoom factor. \~
  */
  void SetZoomFactor( double zoomFactor );

  /** \brief \ru Вернуть признак того, что преобразование было установлено.
             \en Returns flag that transformation is set. \~ 
    \return \ru True, если преобразование было установлено.
            \en True if transformation is set. \~
  */
  bool IsTransformation() const;

private:
    MbCartPoint m_position;     ///< \ru Положение пользовательского ввода. \en User input position.
    MbVector m_normalize;       ///< \ru Нормализация положения центра касаний. \en Normalization of touch center position.
    MbVector m_translation;     ///< \ru Данные трансформации. \en Transformation data.
    MbCube m_boundingBox;       ///< \ru Габаритный куб объекта. \en Object bounding box.
    double m_rotation;          ///< \ru Угол поворота. \en Rotation angle.
    double m_zoomFactor;       ///< \ru Коэффициент масштаба. \en Zoom factor.
    bool m_isTransformationIs;  ///< \ru Признак того, что преобразование было установлено. \en Flag that transformation is set.
};

//------------------------------------------------------------------------------
/** \brief \ru Событие CloseEvent содержит параметры, описывающие событие close.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS CloseEvent : public ProcessEvent
{
public:
    // Конструктор по умолчанию. \en Default constructor.
    explicit CloseEvent();
    /// \ru Конструктор копирования. \en Copy constructor. 
    CloseEvent(const CloseEvent& other);
    /// \ru Деструктор. \en Destructor.
    ~CloseEvent();
};

//------------------------------------------------------------------------------
/** \brief \ru Событие TimerEvent содержит параметры, описывающие событие таймера.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS TimerEvent : public ProcessEvent
{
public:
    // Конструктор по умолчанию. \en Default constructor.
    explicit TimerEvent(int timerId);
    /// \ru Деструктор. \en Destructor.
    ~TimerEvent();
public:
    int GetTimerId() const;
protected:
    int m_timerid;
};

//------------------------------------------------------------------------------
/** \brief \ru Событие TimerEvent содержит параметры, описывающие событие таймера.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS ResizeEvent : public ProcessEvent// widget resize event
{
public:
    ResizeEvent(const Size& size, const Size& oldSize);
public:
    const Size& GetSize() const;
    const Size& GetOldSize() const;
protected:
    Size sz, oldsz;
};

//------------------------------------------------------------------------------
/** \brief \ru 
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS ShowEvent : public ProcessEvent
{
public:
    ShowEvent();
    ~ShowEvent();
};

//-----------------------------------------------------------------------------
/** \brief \ru Класс PlatformRenderingAreaEvent используется для уведомления о реальных событиях на поверхности платформы.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS PlatformRenderingAreaEvent : public ProcessEvent
{
public:
    enum RenderingAreaEventType 
    {
        ra_Created,
        ra_AboutToBeDestroyed
    };
public:
    explicit PlatformRenderingAreaEvent(RenderingAreaEventType eventType);
    ~PlatformRenderingAreaEvent();
public:
    inline RenderingAreaEventType GetRenderingAreaEventType() const { return m_renderingAreaEventType; }
protected:
    RenderingAreaEventType m_renderingAreaEventType;
};

//-----------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS DrawEvent : public ProcessEvent
{
public:
    explicit DrawEvent(const Region& drawRegion);
    explicit DrawEvent(const IntRect& drawRect = IntRect());
    ~DrawEvent();
public:
    inline const IntRect& GetRect() const { return m_rect; }
    inline const Region& GetRegion() const { return m_region; }
protected:
    IntRect m_rect;
    Region m_region;
    bool m_erased;
};

//-----------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS ExposeEvent : public ProcessEvent
{
public:
    explicit ExposeEvent(const Region& rgn);
    ~ExposeEvent();
    inline const Region& GetRegion() const { return m_region; }
protected:
    Region m_region;
};

//-----------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class VSN_CLASS WindowStateModifiedEvent : public ProcessEvent
{
public:
    explicit WindowStateModifiedEvent(WindowStates oldState, bool isOverride = false);
    ~WindowStateModifiedEvent();
public:
    inline WindowStates GetOldState() const { return m_state; }
    bool IsOverride() const;
private:
    WindowStates m_state;
    bool m_override;
};

class Object;
//-----------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class ChildEvent : public ProcessEvent
{
public:
    explicit ChildEvent(EventType type, Object* pObject);
    ~ChildEvent();
public:
    Object* m_pObject;
};

//-----------------------------------------------------------------------------
/** \brief \ru NOT TRANSLATED.
           \en NOT TRANSLATED. \~
    \ingroup Vision_Process
*/
// ---
class DeferredDeleteEvent : public ProcessEvent
{
public:
    explicit DeferredDeleteEvent();
    ~DeferredDeleteEvent();
public:
    int GetCycleLevel() const { return level; }
private:
    int level;
    friend class BaseApplication;
};

VSN_END_NAMESPACE

#endif /* __VSN_PROCESSEVENT_H */
