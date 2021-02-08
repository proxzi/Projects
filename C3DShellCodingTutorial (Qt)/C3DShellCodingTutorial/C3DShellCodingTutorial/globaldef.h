#pragma once
#include <QIcon>
#include <QStringLiteral>
#include <QObject>
#include <QWidget>
#include <QAction>

#include <model_item.h>

enum class Menus
{
    kFile, kEdit, kView, kTools, kWindow, kHelp
};

enum class ToolBars
{
    kFile, kEdit, kView, kTools, kWindow, kHelp, kNavigator
};

enum class Actions
{
    kNewFile = 0,
    kOpenFile,
    kSaveFile,
    kSaveAsFile,
    kCloseFile,
    kPasteFile,
    kCutFile,
    kCopyFile,
    kExit,
    kFindWidget,
    kAbout,
    kAboutQt,
    kTextEditor,
    kGallery,
    kDocumentation,
    kScene,
    kTutorial,
    kManuals,
    KSceneCon,
    KMessageCon,
    KBackTuGallery,

    kWebHistoryBack,
    kWebHistoryForward,
    kWebStop,
    kWebReload,
    kWebZoomIn,
    kWebZoomOut,
    kWebResetZoom,
    kTutorialZoomIn,
    kTutorialZoomOut,
    kTutorialResetZoom,

    kWebStopReload,
    kWebSwitchLanguage,

    kWebDocOffline,
    kWebDocOnline,
    kWebDocRuLang,
    kWebDocEnLang,
    // scene
    kSceneOpenModel,
    kSceneClean,
    kSceneAddModel,
    kSceneZoomToFit,
    kSceneAnimated,
    // Orientations
    kFront,
    kRear,
    kDown,
    kLeft,
    kRight,
    kUp,
    kIsoXYZ,
    // RenderMode
    kShaded,
    khiddenremoved,
    kShadedwithedges,
    //filter
    kFilter
};

enum class SceneAxisAnimated {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

enum class Mode
{
    WebDocOffline, 
    WebDocOnline
};

inline constexpr int g_kIconSize = 18;
inline const QString g_kDefaultCommonName(QStringLiteral("C3DShellCodingTutorial"));
inline const QString g_kDefaultWorkDirectoryName(QStringLiteral("WorkFolder"));
inline const QString g_kDefaultTutorialsDirectoryName(QStringLiteral("Tutorials"));
inline const QString g_kDefaultBuilderDirectoryName(QStringLiteral("User"));
inline const QString g_kDefaultKernelDirectoryName(QStringLiteral("User/Kernel"));
inline const QString g_kDefaultManualsDirectoryName(QStringLiteral("Manuals"));
inline const QString g_kDefaultModelsDirectoryName(QStringLiteral("Models"));
inline const QString g_kDefaultBuilderUserFileName(QStringLiteral("code.cpp"));
inline const QString g_kDefaultBuilderUserMainFileName(QStringLiteral("dllmain.cpp"));
inline const QString g_kDefaultBuilderInitFileName(QStringLiteral("initc.bat"));
inline const QString g_kDefaultWebDocRoot(QStringLiteral("https://c3d.ascon.%1/doc/math"));
inline const QString g_kDefaultLocalDocRoot(QStringLiteral("Docs/%1"));
inline const QString g_kDefaultEn(QStringLiteral("net"));
inline const QString g_kDefaultRu(QStringLiteral("ru"));
inline const QString g_kDefaultDocPrefix(QStringLiteral("modules.html"));
inline const QString g_kDefaultSettingsFileBaseName(QStringLiteral("settings.ini"));
inline const QString g_kDefaultMSVCPath(QStringLiteral("C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat"));
inline const QString g_kVariableMSVCPath(QStringLiteral("C:/Program Files (x86)/Microsoft Visual Studio/%1/%2/VC/Auxiliary/Build/vcvars64.bat"));
inline const Actions g_kDefaultLanguage = Actions::kWebDocEnLang;




inline QIcon svgIcon(const QString& File)
{
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}

inline QWidget* createExpandingSpacer()
{
    auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return spacer;
}

inline QWidget* createFixWSpacer(int w)
{
    auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    spacer->setFixedWidth(w);
    return spacer;
}

inline QWidget* createFixHSpacer(int h)
{
    auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    spacer->setFixedHeight(h);
    return spacer;
}

// for 1 shortcut
inline QAction* createActionOneS(const QIcon& icon, const QString& text,
    const QKeySequence& shortcut, const QString& statusTip, QObject* parent)
{
    auto action = new QAction(icon, text, parent);
    action->setShortcut(shortcut);
    action->setStatusTip(statusTip);
    return action;
}
// for many shortcuts
inline QAction* createActionManyS(const QIcon& icon, const QString& text,
    const QList<QKeySequence>& shortcuts, const QString& statusTip, QObject* parent)
{
    auto action = new QAction(icon, text, parent);
    action->setShortcuts(shortcuts);
    action->setStatusTip(statusTip);
    return action;
}

inline QString fromByteArray(const QByteArray& byteArray)
{
    QString s = QString::fromUtf8(byteArray);
    if (s.toUtf8() != byteArray) {
        s = QString::fromLatin1(byteArray);
    }
    return s;
}
//------------------------------------------------------------------------------
// \ru Дать значение красного цвета в пределах 0 - 255. \en Get value of red color in range from 0 to 255. 
// ---
inline uint8_t getR(uint32_t rgb_color)
{
    return (uint8_t)(rgb_color);
}
//------------------------------------------------------------------------------
// \ru Дать значение зелёного цвета в пределах 0 - 255. \en Get value of green color in range from 0 to 255. 
// ---
inline uint8_t getG(uint32_t rgb_color)
{
    return (uint8_t)(rgb_color >> 8);
}
//------------------------------------------------------------------------------
// \ru Дать значение синего цвета в пределах 0 - 255. \en Get value of blue color in range from 0 to 255. 
// ---
inline uint8_t getB(uint32_t rgb_color)
{
    return (uint8_t)(rgb_color >> 16);
}
//------------------------------------------------------------------------------
// Стиль элемента
// ---

struct ColorRGB
{
    int r;
    int g;
    int b;
};

class Style {
protected:
    uint32_t color; // Цвет элемента
    uint32_t width; // Толщина линии
    uint32_t style; // Стиль линии

public:
    Style(uint32_t w = 1, uint32_t c = 0xFF7F00) {
        style = 0;
        width = w;
        color = c;
    }
    Style(const Style& init) {
        style = init.style;
        width = init.width;
        color = init.color;
    }
    virtual ~Style() {}

public:
    // Проверка на равенство
    bool operator == (const Style& with) const
    {
        return (style == with.style && width == with.width && color == with.color);
    }
    // Проверка на неравенство
    bool operator != (const Style& with) const
    {
        return !(*this == with);
    }
    // Присвоение значений
    void operator = (const Style& init)
    {
        set(init);
    }
    void set(const Style& init)
    {
        style = init.style;
        width = init.width;
        color = init.color;
    }
    void set(uint32_t s, uint32_t w, uint32_t c)
    {
        style = s;
        width = w;
        color = c;
    }
    void setColor(uint32_t c)
    {
        color = c;
    }
    void setWidth(uint32_t w)
    {
        width = w;
    }
    void setStyle(uint32_t s)
    {
        style = s;
    }
    // Получение значений
    uint32_t getColor() const
    {
        return color;
    }
    int getWidth() const
    {
        return width;
    }
    int getStyle() const
    {
        return style;
    }
    // Выдача на модификация
    uint32_t& setColor()
    {
        return color;
    }
    uint32_t& setWidth()
    {
        return width;
    }
    uint32_t& setStyle()
    {
        return style;
    }
    void init(uint32_t w = 1, uint32_t c = 0)
    {
        width = w;
        color = c;
    }
}; // Style

struct Model
{
    Style style;
    MbItem* item = nullptr;
};