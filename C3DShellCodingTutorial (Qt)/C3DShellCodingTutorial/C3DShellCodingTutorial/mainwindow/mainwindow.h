#pragma once

#include <QMainWindow>
#include <QScopedPointer>
#include <QMap>
#include <QString>
#include <QWebEnginePage>
#include <QPushButton>
#include <QTranslator>

#include "ads_globals.h"

#include "globaldef.h"
#include "visionscene.h"

namespace Ui { class MainWindow; }
namespace ads 
{ 
    class CDockManager; 
    class CDockWidget; 
    class CDockAreaWidget;
}

class QMenu;
class ToolBar;
class QAction;
class QComboBox;
class QDomNode;
class QPushButton;
class QCheckBox;
class QTableView;

class CppCodeBuilder;
class WelcomeWidget;
class TextEditManager;
class ConsoleText;
class TutorialGalleryWidget;
class DocumentationWidget;
class TutorialWidget;
class PdfListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags());

    MainWindow(const MainWindow& other) = delete;
    MainWindow& operator= (const MainWindow& other) = delete;

    void showPreview();
    /// \ru Todo. \en ToDo. \~
    QStringList themesList();
    const QString& themeName() const;

    void commonSetup();

protected:
    void closeEvent(QCloseEvent* event) override;
    //void changeEvent(QEvent* event) override;

private slots:
    void slotSwitchTheme(const QString& themeName);

    // Documentation slots
    void slotWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
    void slotWebViewLoadProgress(int progress);

private:
    QTranslator qtLanguageTranslator;

    // Documentation 
    void createDocumentationToolBar();
    void connectDocumentation();
    ads::CDockAreaWidget* buildDocumentationDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // Scene
    void createSceneToolBar();
    void connectScene();
    ads::CDockAreaWidget* buildSceneDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // Tutorial
    void createTutorialToolBar();
    void connectTutorial();
    ads::CDockAreaWidget* buildTutorialDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // Gallery
    void createGalleryToolBar();
    void connectGallery();
    ads::CDockAreaWidget* buildGalleryDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // BuilderConsole
    void createBuilderConsoleToolbar();
    void connectBuilderConsole();
    ads::CDockAreaWidget* buildBuilderConsoleDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // SceneConsole
    void createSceneConsoleToolbar();
    void connectSceneConsole();
    ads::CDockAreaWidget* buildSceneConsoleDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // PdfList
    void createPdfListToolBar();
    void connectPdfList();
    ads::CDockAreaWidget* buildPdfListDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);
    // TextEditor
    void createTextEditorToolBar();
    void connectTextEditorList();
    ads::CDockAreaWidget* buildTextEditorDock(ads::DockWidgetArea place,
        ads::CDockAreaWidget* area = nullptr);

    void prepareThemes();
    const QString& themePath(const QString& name);
    /// \ru Todo. \en ToDo. \~
    void createActions();
    void connectActions();

    void createMenus();
    void createToolBars();
    void createStatusBar();
    /// \ru Todo. \en ToDo. \~
    void saveStates();
    void savePerspectives();
    void restoreStates();
    void restorePerspectives();

    void setLang(int indexLang);

private:
    /// \ru Todo. \en ToDo. \~
    QScopedPointer<Ui::MainWindow> ui;
    WelcomeWidget* m_pWelcomeWidget;
    QScopedPointer<CppCodeBuilder> m_pCodeBuilder;
    QString m_defaultCSS;

    QScopedPointer<VisionScene> m_pScene;

    QString m_themeName = "default";
    QMap<QString, QString> m_themesPathList = {};
    /// \ru Todo. \en ToDo. \~
    ads::CDockManager* m_pDockManager = nullptr;
    ads::CDockWidget* m_pDockScene = nullptr;
    ads::CDockWidget* m_pDockConsoleCodeBuilder = nullptr;
    ads::CDockWidget* m_pDockConsoleSceneMessage = nullptr;
    ads::CDockWidget* m_pDockGallery = nullptr;
    ads::CDockWidget* m_pDockPdfList = nullptr;
    ads::CDockWidget* m_pDockDocumentation = nullptr;
    ads::CDockWidget* m_pDockTutorial = nullptr;

    TextEditManager* m_pTextEditManager = nullptr;
    /// \ru Todo. \en ToDo. \~
    TutorialGalleryWidget* m_pGallery = nullptr;
    ConsoleText* m_pConsoleCodeBuilder = nullptr;
    ConsoleText* m_pConsoleSceneMessage = nullptr;
    PdfListWidget* m_pPdfListWidget = nullptr;
    DocumentationWidget* m_pDocumentation = nullptr;
    TutorialWidget* m_pTutorial = nullptr;

    /// \ru Todo. \en ToDo. \~
    QMap<Menus, QMenu*> m_menus = {};
    QMap<Actions, QAction*> m_actions = {};
    QMap<ToolBars, QToolBar*> m_toolBars = {};

    QPushButton* m_pButtonBackToGallery = nullptr;
    QCheckBox* m_pCheckBoxZoomFit = nullptr;
    QTableView* m_pTable = nullptr;
    QComboBox* m_pComboBox = nullptr;
};