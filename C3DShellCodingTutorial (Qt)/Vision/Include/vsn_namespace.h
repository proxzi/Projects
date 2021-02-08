////////////////////////////////////////////////////////////////////////////////
/** 
    \file
    \brief \ru
           \en
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __VSN_NAMESPACE_H
#define __VSN_NAMESPACE_H

#include <mb_vector3d.h>
#include <system_types.h>

#include "vsn_flags.h"
#include "vsn_mathdefs.h"
#include "vsn_global.h"


VSN_BEGIN_NAMESPACE

// настройки осей по умолчанию
// вектор X
const MbVector3D X_AXIS(1.0, 0.0, 0.0);
// вектор Y
const MbVector3D Y_AXIS(0.0, 1.0, 0.0);
// вектор Z
const MbVector3D Z_AXIS(0.0, 0.0, 1.0);

// буфер смещения используется для вершинного буфера
#define BUFFER_OFFSET(i) ((char*)nullptr + (i))

typedef void *HANDLE;

enum ConnectionType 
{
    AutoConnection,
    DirectConnection,
    QueuedConnection,
    BlockingQueuedConnection,
    UniqueConnection = 0x80
};

// ---
enum WindowType
{
    wt_Control  = 0x00000000,
    wt_Window   = 0x00000001,
    wt_Dialog   = 0x00000002 | wt_Window,
    wt_Modal    = 0x00000004 | wt_Window,
    wt_Popup    = 0x00000008 | wt_Window,
    wt_Tool     = wt_Popup | wt_Dialog,
    wt_ToolTip  = wt_Popup | wt_Modal,
    wt_SplashScreen  = wt_ToolTip | wt_Dialog,
    wt_Desktop       = 0x00000010 | wt_Window,
    wt_ForeignWindow = 0x00000020 | wt_Window,
    wt_Mask          = 0x000000ff,
    /// \ru Флаги, которые можно использовать для настройки внешнего вида окон верхнего уровня. \en NO TRANSLATION.
    // Hint
    wh_MSFixedSizeDialogHint = 0x00000100,
    wh_MSOwnDC               = 0x00000200,
    wh_FramelessHint         = 0x00000800,
    wh_TitleHint             = 0x00001000,
    wh_SystemMenuHint        = 0x00002000,
    wh_MinButtonHint         = 0x00004000,
    wh_MaxButtonHint         = 0x00008000,
    wh_MinMaxButtonsHint     = wh_MinButtonHint | wh_MaxButtonHint,
    wh_ContextHelpButtonHint = 0x00010000,
    wh_ShadeButtonHint       = 0x00020000,
    wh_StaysOnTopHint        = 0x00040000,
    wh_TransparentForInput   = 0x00080000,

    wh_CustomizeHint         = 0x02000000,
    wh_StaysOnBottomHint     = 0x04000000,

    wh_CloseButtonHint       = 0x08000000,
    wh_FullscreenButtonHint  = 0x80000000,
};
VSN_DECLARE_FLAGS(WindowFlags, WindowType)

enum WindowState 
{
    ws_NoState    = 0x00000000,
    ws_Minimized  = 0x00000001,
    ws_Maximized  = 0x00000002,
    ws_FullScreen = 0x00000004,
    ws_Active     = 0x00000008
};
VSN_DECLARE_FLAGS(WindowStates, WindowState)

//------------------------------------------------------------------------------
/** \brief \ru Политика поиска вложений.
           \en Attachment find Policy. \~
    \ingroup Vision_Base
*/
// ---
enum ChildFindingPolicy
{
    FindOnlyDirectChildren = 0x0, ///< \ru Найти только прямых детей. \en Find only direct children.
    FindAllNestedChildren  = 0x1  ///< \ru Найти всех вложенных детей. \en Find all nested children.
};
VSN_DECLARE_FLAGS(ChildFindingPolicies, ChildFindingPolicy)

//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Process
*/
// ---
enum AppAttribute
{
    aa_appDesktopOpenGL     = 0,
    aa_appOpenGLES          = 1,
    aa_appSoftwareOpenGL    = 2,
    aa_RegisteredWindows    = 3,
};

//------------------------------------------------------------------------------
/** \brief \ru NO TRANSLATION.
           \en NO TRANSLATION. \~
    \ingroup Vision_Process
*/
// ---
enum MouseButton
{
    mb_Control              = 1 << 1,   ///< \ru mb_Control Любая клавиша Ctrl. \en mb_Control Any Ctrl Key.
    mb_Shift                = 1 << 2,   ///< \ru mb_Shift Любая клавиша Shift. \en mb_Shift Any Shift Key.
    mb_Alt                  = 1 << 3,   ///< \ru mb_Alt Любая клавиша Alt. \en mb_Alt Any Alt Key.
    mb_LButton              = 1 << 4,   ///< \ru mb_LButton Левая клавиша мыши. \en mb_LButton Left Mouse Button.
    mb_MButton              = 1 << 5,   ///< \ru mb_MButton Средняя клавиша мыши. \en mb_MButton Middle Mouse Button.
    mb_RButton              = 1 << 6,   ///< \ru mb_RButton Правая клавиша мыши. \en mb_RButton Right Mouse Button.
    mb_Right_Control        = 1 << 7,   ///< \ru mb_Right_Control Правая клавиша Ctrl. \en mb_Right_Control Right Ctrl Key.
    mb_Right_Shift          = 1 << 8,   ///< \ru mb_Right_Shift Правая клавиша Shift. \en mb_Right_Shift Right Shift Key.
    mb_Right_Alt            = 1 << 9,   ///< \ru mb_Right_Alt Правая клавиша Alt. \en mb_Right_Alt Right Alt Key.
    mb_Left_Control         = 1 << 10,  ///< \ru mb_Left_Control Левая клавиша Ctrl. \en mb_Left_Control Left Ctrl Key.
    mb_Left_Shift           = 1 << 11,  ///< \ru mb_Left_Shift Левая клавиша Shift. \en mb_Left_Shift Left Shift Key.
    mb_Left_Alt             = 1 << 12,  ///< \ru mb_Left_Alt Левая клавиша Alt. \en mb_Left_Alt Left Alt Key.
    mb_Left_Arrow           = 1 << 13,  ///< \ru mb_Left_Arrow Клавиша стрелка влево. \en mb_Left_Arrow Left Arrow Key.
    mb_Up_Arrow             = 1 << 14,  ///< \ru mb_Up_Arrow Клавиша стрелка вверх. \en mb_Up_Arrow Up Arrow Key.
    mb_Right_Arrow          = 1 << 15,  ///< \ru mb_Right_Arrow Клавиша стрелка вправо. \en mb_Right_Arrow Right Arrow Key.
    mb_Down_Arrow           = 1 << 16,  ///< \ru mb_Down_Arrow Клавиша стрелка вниз. \en mb_Down_Arrow Down Arrow Key.
    mb_Joystick_Button_1    = 1 << 17,  ///< \ru mb_Joystick_Button_1 Кнопка джойстика 1. \en mb_Joystick_Button_1 Joystick Button 1.
    mb_Joystick_Button_2    = 1 << 18,  ///< \ru mb_Joystick_Button_2 Кнопка джойстика 2. \en mb_Joystick_Button_2 Joystick Button 2.
    mb_Joystick_Button_3    = 1 << 19,  ///< \ru mb_Joystick_Button_3 Кнопка джойстика 3. \en mb_Joystick_Button_3 Joystick Button 3.
    mb_Joystick_Button_4    = 1 << 20,  ///< \ru mb_Joystick_Button_4 Кнопка джойстика 4. \en mb_Joystick_Button_4 Joystick Button 4.
    mb_Joystick_Button_5    = 1 << 21,  ///< \ru mb_Joystick_Button_5 Кнопка джойстика 5. \en mb_Joystick_Button_5 Joystick Button 5.
    mb_Joystick_Button_6    = 1 << 22,  ///< \ru mb_Joystick_Button_6 Кнопка джойстика 6. \en mb_Joystick_Button_6 Joystick Button 6.
    mb_Joystick_Button_7    = 1 << 23,  ///< \ru mb_Joystick_Button_7 Кнопка джойстика 7. \en mb_Joystick_Button_7 Joystick Button 7.
    mb_Joystick_Button_8    = 1 << 24,  ///< \ru mb_Joystick_Button_8 Кнопка джойстика 8. \en mb_Joystick_Button_8 Joystick Button 8.
};

//------------------------------------------------------------------------------
/** \brief \ru В перечислителе показаны символьные имена констант, шестнадцатеричные значения и эквиваленты мыши или 
               клавиатуры для кодов виртуальных клавиш, используемых системой. Коды перечислены в числовом порядке.
            \en NO TRANSLATION. \~
    \ingroup Vision_Process
*/
// ---
enum KeyCodes
{
    kc_Escape    = 0x01000000,
    kc_Tab       = 0x01000001,
    kc_Backtab   = 0x01000002,
    kc_Backspace = 0x01000003,
    kc_Return    = 0x01000004,
    kc_Enter     = 0x01000005,
    kc_Insert    = 0x01000006,
    kc_Delete    = 0x01000007,
    kc_Pause     = 0x01000008,
    kc_Print     = 0x01000009,
    kc_SysReq    = 0x0100000a,
    kc_Clear     = 0x0100000b,
    kc_Home      = 0x01000010,
    kc_End       = 0x01000011,
    kc_Left      = 0x01000012,
    kc_Up        = 0x01000013,
    kc_Right     = 0x01000014,
    kc_Down      = 0x01000015,
    kc_PageUp    = 0x01000016,
    kc_PageDown  = 0x01000017,
    kc_Shift     = 0x01000020,
    kc_Control   = 0x01000021,
    kc_Meta      = 0x01000022,
    kc_Alt       = 0x01000023,
    kc_CapsLock  = 0x01000024,
    kc_NumLock   = 0x01000025,
    kc_ScrollLock= 0x01000026,
    // function keys
    kc_F1  = 0x01000030,
    kc_F2  = 0x01000031,
    kc_F3  = 0x01000032,
    kc_F4  = 0x01000033,
    kc_F5  = 0x01000034,
    kc_F6  = 0x01000035,
    kc_F7  = 0x01000036,
    kc_F8  = 0x01000037,
    kc_F9  = 0x01000038,
    kc_F10 = 0x01000039,
    kc_F11 = 0x0100003a,
    kc_F12 = 0x0100003b,
    kc_F13 = 0x0100003c,
    kc_F14 = 0x0100003d,
    kc_F15 = 0x0100003e,
    kc_F16 = 0x0100003f,
    kc_F17 = 0x01000040,
    kc_F18 = 0x01000041,
    kc_F19 = 0x01000042,
    kc_F20 = 0x01000043,
    kc_F21 = 0x01000044,
    kc_F22 = 0x01000045,
    kc_F23 = 0x01000046,
    kc_F24 = 0x01000047,

    // 7 bit printable ASCII
    kc_Space = 0x20,
    kc_Any = kc_Space,
    kc_Plus = 0x2b,
    kc_Minus = 0x2d,

    kc_0 = 0x30,
    kc_1 = 0x31,
    kc_2 = 0x32,
    kc_3 = 0x33,
    kc_4 = 0x34,
    kc_5 = 0x35,
    kc_6 = 0x36,
    kc_7 = 0x37,
    kc_8 = 0x38,
    kc_9 = 0x39,

    kc_A = 0x41,
    kc_B = 0x42,
    kc_C = 0x43,
    kc_D = 0x44,
    kc_E = 0x45,
    kc_F = 0x46,
    kc_G = 0x47,
    kc_H = 0x48,
    kc_I = 0x49,
    kc_J = 0x4a,
    kc_K = 0x4b,
    kc_L = 0x4c,
    kc_M = 0x4d,
    kc_N = 0x4e,
    kc_O = 0x4f,
    kc_P = 0x50,
    kc_Q = 0x51,
    kc_R = 0x52,
    kc_S = 0x53,
    kc_T = 0x54,
    kc_U = 0x55,
    kc_V = 0x56,
    kc_W = 0x57,
    kc_X = 0x58,
    kc_Y = 0x59,
    kc_Z = 0x5a,
    kc_unknown = 0x01ffffff
};

enum TimerType 
{
    tt_PreciseTimer,
    tt_CoarseTimer,
    tt_VeryCoarseTimer
};

enum FocusReason
{
    MouseFocusReason,
    TabFocusReason,
    BacktabFocusReason,
    ActiveWindowFocusReason,
    PopupFocusReason,
    ShortcutFocusReason,
    MenuBarFocusReason,
    OtherFocusReason,
    NoFocusReason
};

enum EventPriority 
{
    HighEventPriority = 1,
    NormalEventPriority = 0,
    LowEventPriority = -1
};

enum ClippingPlaneId
{
    LeftPlane   = 0, // левая плоскость отсечения
    RightPlane  = 1, // правая плоскость отсечения
    TopPlane    = 2, // верхняя плоскость отсечения
    BottomPlane = 3, // нижняя плоскость отсечения
    NearPlane   = 4, // ближайшая плоскость отсечения
    FarPlane    = 5  // дальняя плоскость отсечения
};

enum FrustumClassification
{
    InFrustum = 0,
    IntersectFrustum = 1,
    OutFrustum  = 2
};

// стандартные типы ориентаций отображения
enum Orientation
{
    Front,    // Спереди  - Фронтальная плоскость
    Rear,     // Сзади
    Up,       // Сверху   - Горизонтальная плоскость
    Down,     // Снизу
    Left,     // Слева    - Профильная плоскость
    Right,    // Справа
    IsoXYZ,   // Изометрия XYZ
};

enum AxisOrientation
{
    AxisOrientationNone = 0,
    AxisOrientationX    = 1,
    AxisOrientationY    = 2,
    AxisOrientationZ    = 4
};

// состояние визуализации геометрии
enum RenderingState
{
    NormalRenderState = 0,
    SpecialMaterialState,
    SpecialTransparencyState,
    SpecialMaterialTransparencyState,
    SpecialMaterialPrimitiveState,
    PrimitiveSelectedState,
    BodySelectionState,
    PrimitiveSelectionState
};

// флаги отображения геометрии
enum RenderMode
{
    rm_Shaded,
    rm_ShadedWithEdges,
    rm_Wireframe,
    rm_HiddenLinesRemoved,
    rm_WireframeQuadrangle,
    rm_Transparent,
    rm_OutlineSilhouette,
    rm_Annotation,
    rm_Inherit,
};

// применяемый тип Vertex Buffer Object
enum VertexBufferObjectType
{
    buf_Vertex = 10,
    buf_Color,
    buf_Index,
    buf_Normal,
    buf_Texel,
};

enum class ObjectType
{ 
    None     = 0,
    Segment  = 1,
    Body     = 2,
    Vertex   = 3,
    Edge     = 4,
    Face     = 5,
};

enum TypeTriangulation
{
    Triangles,
    TrianglesStrip,
    TrianglesFan,
};

enum class HighlighterType
{
    ht_Solid,
    ht_Grid
};

// тип представления
enum TypeRep
{
    Geometry_VBO = 1
};

// Texture filter
enum class TextureFilter
{
    Nearest,
    // bilinear filtering
    Linear,
    //Trilinear filtering using mipmaps
    NearestNearest,
    NearestLinear,
    LinearNearest,
    LinearLinear,
};

// Texture wrap value
enum class TextureWrap
{
    Repeat,
    ClampToEdge
};

// a texel's format
enum class TextureFormat
{
    BGR,
    BGRA,
};

enum class TextDirection
{
    Left,
    Right,
};

enum class ViewportIntersections : int
{
    LeftEdge = 1,
    TopEdge = 1 << 1,
    RightEdge = 1 << 2,
    BottomEdge = 1 << 3
};


VSN_END_NAMESPACE

#endif /* __VSN_NAMESPACE_H */


