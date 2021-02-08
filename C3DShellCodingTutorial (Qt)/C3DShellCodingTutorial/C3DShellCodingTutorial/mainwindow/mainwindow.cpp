#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QStyle>
#include <QSettings>
#include <QDebug>
#include <QLabel>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QComboBox>
#include <QInputDialog>
#include <QScreen>
#include <QCloseEvent>
#include <QCheckBox>
#include <QTableView>
//ADS
#include <DockManager.h>
#include <DockWidget.h>
#include <DockAreaWidget.h>
//
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "cppcodebuilder.h"
#include "consoletext.h"
#include "dockwidget.h"

#include "welcomewidget.h"
#include "texteditmanager.h"
#include "documentationwidget.h"
#include "tutorialwidget.h"
#include "webview.h"
#include "colorbutton.h"
#include "tutorialgallerywidget.h"

#include "pdflistwidget.h"
#include "pdfreaderwidget.h"

#include "storagelocation.h"

//-----------------------------------------------------------------------------
// 
// ---
MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , ui(new Ui::MainWindow)
    , m_pWelcomeWidget(new WelcomeWidget(this))
    , m_pCodeBuilder(nullptr)
    , m_defaultCSS(qApp->styleSheet())
    , m_pScene(nullptr)
{
    using ads::CDockManager;
    ui->setupUi(this);

    // Смена языка 
    connect(m_pWelcomeWidget, &WelcomeWidget::setLanguages,
        [this](int language)
        {
            setLang(language);
        });

    // Установка языка из файла settings.ini
    setLang(APP.restoreCommonSettings("GlobalLanguage", 0).toInt());

    m_pDockManager = new CDockManager(this);
    CDockManager::setConfigFlag(CDockManager::FloatingContainerHasWidgetTitle, true);
    CDockManager::setConfigFlag(CDockManager::FloatingContainerHasWidgetIcon, true);

    m_pTextEditManager = new TextEditManager(this, m_pDockManager);

    //connect(m_pDockManager, &ads::CDockManager::floatingWidgetCreated, [this](ads::CFloatingDockContainer* FloatingWidget)
    //{
    //    auto docks = FloatingWidget->dockWidgets();

    //    for (auto dock : docks)
    //    {
    //        qDebug() << "Float" << dock->objectName();
    //    }
    //});

    //connect(m_pDockManager, &ads::CDockManager::dockAreaCreated, [this](ads::CDockAreaWidget* DockArea)
    //{
    //    
    //    auto docks = DockArea->dockWidgets();
    //    for (auto dock : docks)
    //    {
    //        qDebug() << "area created" <<dock->objectName();
    //        auto toolbar = dock->toolBar();
    //        qDebug() << "bar size = " << toolbar->height();

    //    }
    //});

    //Theme
    prepareThemes();

    connect(m_pWelcomeWidget, &WelcomeWidget::signalSwitchTheme, this, &MainWindow::slotSwitchTheme);

    connect(m_pWelcomeWidget, &WelcomeWidget::signalOpenFiles, [this]()
    {
        commonSetup();

        if (m_pTextEditManager->openFiles())
        {
            m_pWelcomeWidget->hide();

            m_pTextEditManager->toggleView(true);
            m_pDockScene->toggleView(true);
            m_pDockConsoleCodeBuilder->toggleView(true);
            m_pDockConsoleSceneMessage->toggleView(true);
            APP.run(true);
            show();
        }
    });

    connect(m_pWelcomeWidget, &WelcomeWidget::signalOpenFile, [this](const QString& filePath)
    {
        commonSetup();

        m_pWelcomeWidget->hide();

        m_pTextEditManager->slotNewEditorByFilePath(filePath);

        m_pTextEditManager->toggleView(true);
        m_pDockScene->toggleView(true);
        m_pDockConsoleCodeBuilder->toggleView(true);
        m_pDockConsoleSceneMessage->toggleView(true);
        APP.run(true);

        show();
    });

    connect(m_pWelcomeWidget, &WelcomeWidget::signalShowTutorialGallery, [this]()
    {
        commonSetup();

        m_pWelcomeWidget->hide();
        m_pDockGallery->toggleView(true);
        APP.run(true);

        show();
    });

    connect(m_pWelcomeWidget, &WelcomeWidget::signalShowDocumentation, [this]()
    {
        commonSetup();

        m_pWelcomeWidget->hide();

        m_pDockDocumentation->toggleView(true);
        APP.run(true);

        show();
    });

    connect(m_pWelcomeWidget, &WelcomeWidget::signalShowManuals, [this]()
    {
        commonSetup();

        m_pWelcomeWidget->hide();

        m_pDockPdfList->toggleView(true);
        APP.run(true);

        show();
    });

    // Default window geometry - center on screen
    resize(QGuiApplication::primaryScreen()->availableGeometry().width() * 8 / 10,
        QGuiApplication::primaryScreen()->availableGeometry().height() * 8 / 10);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,
        frameSize(), QGuiApplication::primaryScreen()->availableGeometry()));
}

//void MainWindow::changeEvent(QEvent* event)
//{
//    if (event->type() == QEvent::LanguageChange) {
//        m_actions[Actions::kDocumentation]->setText(tr("Docs"));
//        m_actions[Actions::kGallery]->setText(tr("Gallery"));
//        m_actions[Actions::kScene]->setText(tr("Scene"));
//        
//        ui->retranslateUi(this);
//        //m_actions[Actions::kDocumentation]->setStatusTip(tr("Docs"));
//    }
//    QWidget::changeEvent(event);
//}

void MainWindow::setLang(int indexLang)
{
    if (indexLang == 0)
    {
        qtLanguageTranslator.load(":/res/russian.qm");
        qApp->installTranslator(&qtLanguageTranslator);
    }
    else
    {
        qtLanguageTranslator.load(":/res/english.qm");
        qApp->installTranslator(&qtLanguageTranslator);
    }
}

//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::commonSetup()
{
    m_pCodeBuilder.reset(new CppCodeBuilder(nullptr));
    //Global
    createActions();
    createToolBars();

    auto consoleArea = buildBuilderConsoleDock(ads::BottomDockWidgetArea);

    buildSceneConsoleDock(ads::CenterDockWidgetArea, consoleArea);

    auto mainArea = buildDocumentationDock(ads::TopDockWidgetArea);

    buildSceneDock(ads::CenterDockWidgetArea, mainArea);
    buildGalleryDock(ads::CenterDockWidgetArea, mainArea);
    buildTutorialDock(ads::CenterDockWidgetArea, mainArea);
    buildPdfListDock(ads::CenterDockWidgetArea, mainArea);

    //buildTextEditorDock(ads::LeftDockWidgetArea);

    createMenus();
    createStatusBar();

    m_menus[Menus::kView]->addAction(m_actions[Actions::kDocumentation]);
    m_menus[Menus::kView]->addAction(m_actions[Actions::kGallery]);
    m_menus[Menus::kView]->addAction(m_actions[Actions::kScene]);

    //m_toolBars[ToolBars::kNavigator]->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
    m_toolBars[ToolBars::kNavigator]->addAction(m_actions[Actions::kDocumentation]);
    m_toolBars[ToolBars::kNavigator]->addAction(m_actions[Actions::kGallery]);
    m_toolBars[ToolBars::kNavigator]->addAction(m_actions[Actions::kScene]);
    m_toolBars[ToolBars::kNavigator]->addWidget(createExpandingSpacer());
    m_toolBars[ToolBars::kNavigator]->addAction(m_actions[Actions::kTutorial]);
    m_toolBars[ToolBars::kNavigator]->addWidget(createExpandingSpacer());
    m_toolBars[ToolBars::kNavigator]->addAction(m_actions[Actions::kManuals]);

    // connections
    connectActions();
    restoreStates();
    restorePerspectives();
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createActions()
{
    // Main
    m_actions[Actions::kAbout] = createActionOneS(svgIcon(QStringLiteral("")), tr("&About"),
        tr(""),
        tr("Show the application's About box"), this);

    m_actions[Actions::kAboutQt] = createActionOneS(svgIcon(QStringLiteral("")), tr("About &Qt"),
        tr(""),
        tr("Show the Qt library's About box"), this);

    // Создание новой вкладки
    m_actions[Actions::kNewFile] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/newfile.svg")), tr("&New"),
        QKeySequence(Qt::CTRL | Qt::Key_N),
        tr("Create a new file"), this);

    // Открыть файл
    m_actions[Actions::kOpenFile] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/open.svg")), tr("&Open..."),
        QKeySequence(Qt::CTRL | Qt::Key_O),
        tr("Open an existing file"), this);

    // Сохранить файл
    m_actions[Actions::kSaveFile] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/save.svg")), tr("&Save"),
        QKeySequence(Qt::CTRL | Qt::Key_S),
        tr("Save the document to disk"), this);

    // Сохранить как
    m_actions[Actions::kSaveAsFile] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/save.svg")), tr("Save &As..."),
        QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N),
        tr("Save the document under a new name"), this);

    // Закрыть программу
    m_actions[Actions::kCloseFile] = createActionOneS(svgIcon(QStringLiteral("")), tr("E&xit"),
        QKeySequence(Qt::CTRL | Qt::Key_Q),
        tr("Exit the application"), this);

    // Действие на сочетание клавиш F + ctrl (Открытие формы поиска и замены)
    m_actions[Actions::kFindWidget] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/find.png")), tr("&Find"),
        QKeySequence(Qt::CTRL | Qt::Key_F), tr("Find"), this);

    m_actions[Actions::kTextEditor] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/editor/editor.svg")), tr("Text Edit"),
        QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_T),
        tr("text edit"), this);
    m_actions[Actions::kTextEditor]->setCheckable(true);
    m_actions[Actions::kTextEditor]->setChecked(true);


    // DocumentationViewer
    m_actions[Actions::kWebStop] = createActionManyS(svgIcon(QStringLiteral("")), tr("&Stop"),
        { QKeySequence(Qt::CTRL | Qt::Key_Period), Qt::Key_Escape },
        tr(""), this);

    m_actions[Actions::kWebReload] = createActionOneS(svgIcon(QStringLiteral("")), tr("Reload Page"),
        QKeySequence::Refresh,
        tr(""), this);

    m_actions[Actions::kWebZoomIn] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomplus.svg")), tr("Zoom &In"),
        QKeySequence(Qt::CTRL | Qt::Key_Plus),
        tr(""), this);

    m_actions[Actions::kWebZoomOut] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomminus.svg")), tr("Zoom &Out"),
        QKeySequence(Qt::CTRL | Qt::Key_Minus),
        tr(""), this);

    m_actions[Actions::kWebResetZoom] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomreset.svg")), tr("Reset &Zoom"),
        QKeySequence(Qt::CTRL | Qt::Key_0),
        tr(""), this);

    m_actions[Actions::kWebSwitchLanguage] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/ru.svg")), tr("Switch &Language"),
        QKeySequence(Qt::CTRL | Qt::Key_L),
        tr("switch to english"), this);

    //Back
    QList<QKeySequence> backShortcuts = QKeySequence::keyBindings(QKeySequence::Back);
    for (auto it = backShortcuts.begin(); it != backShortcuts.end();) {
        // Chromium already handles navigate on backspace when appropriate.
        if ((*it)[0] == Qt::Key_Backspace)
            it = backShortcuts.erase(it);
        else
            ++it;
    }
    // For some reason Qt doesn't bind the dedicated Back key to Back.
    backShortcuts.append(QKeySequence(Qt::Key_Back));

    m_actions[Actions::kWebHistoryBack] = createActionManyS(svgIcon(QStringLiteral(":/res/icons/web/back.svg")),
        tr("Back"),
        backShortcuts,
        tr("Go back in History"), this);
    m_actions[Actions::kWebHistoryBack]->setIconVisibleInMenu(false);
    // Forward
    QList<QKeySequence> fwdShortcuts = QKeySequence::keyBindings(QKeySequence::Forward);
    for (auto it = fwdShortcuts.begin(); it != fwdShortcuts.end();) {
        if (((*it)[0] & Qt::Key_unknown) == Qt::Key_Backspace)
            it = fwdShortcuts.erase(it);
        else
            ++it;
    }
    fwdShortcuts.append(QKeySequence(Qt::Key_Forward));

    m_actions[Actions::kWebHistoryForward] = createActionManyS(svgIcon(QStringLiteral(":/res/icons/web/forward.svg")),
        tr("Forward"),
        fwdShortcuts,
        tr("Go forward in History"), this);
    m_actions[Actions::kWebHistoryForward]->setIconVisibleInMenu(false);

    m_actions[Actions::kWebStopReload] = new QAction(this);

    m_actions[Actions::kWebDocOffline] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/offline.svg")), tr("Open offline"),
        tr(""),
        tr("Open offline"), this);

    m_actions[Actions::kWebDocOnline] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/online.svg")), tr("Open online"),
        tr(""),
        tr("Open online"), this);

    // Scene
    m_actions[Actions::kSceneOpenModel] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/Open.svg")), tr("Open..."),
        tr(""),
        tr("Open model"), this);

    m_actions[Actions::kSceneAddModel] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/Add.svg")), tr("Add..."),
        tr(""),
        tr("Add model"), this);

    m_actions[Actions::kSceneClean] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/Clean.svg")), tr("Clean"),
        tr(""),
        tr("Clean scene"), this);

    m_actions[Actions::kSceneZoomToFit] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/Zoom.svg")), tr("Zoom to fit"),
        tr(""), tr("Zoom to fit"), this);

    m_actions[Actions::kSceneAnimated] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/rotate.png")), tr("Animated"),
        tr(""), tr("Animated"), this);

    m_actions[Actions::kFront] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_front.png")), tr("Front"),
        tr(""), tr("Front"), this);

    m_actions[Actions::kRear] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_back.png")), tr("Rear"),
        tr(""), tr("Rear"), this);

    m_actions[Actions::kDown] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_bottom.png")), tr("Down"),
        tr(""), tr("Down"), this);

    m_actions[Actions::kLeft] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_left.png")), tr("Left"),
        tr(""), tr("Left"), this);

    m_actions[Actions::kRight] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_right.png")), tr("Right"),
        tr(""), tr("Right"), this);

    m_actions[Actions::kUp] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/view_top.png")), tr("Up"),
        tr(""), tr("Up"), this);

    m_actions[Actions::kIsoXYZ] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/isometry.png")), tr("Isometry"),
        tr(""), tr("Isometry"), this);

    m_actions[Actions::kShaded] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/shaded.png")), tr("Shaded"),
        tr(""), tr("Shaded"), this);

    m_actions[Actions::khiddenremoved] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/hiddenremoved.png")), tr("Hiddenremoved"),
        tr(""), tr("Hiddenremoved"), this);

    m_actions[Actions::kShadedwithedges] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/shadedwithedges.png")), tr("Shaded with edges"),
        tr(""), tr("Shaded with edges"), this);

    m_actions[Actions::kFilter] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/scene/filterbody.png")), tr("Enable body selection"),
        tr(""), tr("Enable body selection"), this);
    m_actions[Actions::kFilter]->setCheckable(true);
    // Tutorial
    m_actions[Actions::kTutorialZoomIn] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomplus.svg")), tr("Zoom &In"),
        QKeySequence(Qt::CTRL | Qt::Key_Plus),
        tr(""), this);

    m_actions[Actions::kTutorialZoomOut] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomminus.svg")), tr("Zoom &Out"),
        QKeySequence(Qt::CTRL | Qt::Key_Minus),
        tr(""), this);

    m_actions[Actions::kTutorialResetZoom] = createActionOneS(svgIcon(QStringLiteral(":/res/icons/web/zoomreset.svg")), tr("Reset &Zoom"),
        QKeySequence(Qt::CTRL | Qt::Key_0),
        tr(""), this);
}
//-----------------------------------------------------------------------------
// 
// Создание панели инструментов
void MainWindow::createToolBars()
{
    m_toolBars[ToolBars::kFile] = addToolBar(tr("File"));
    m_toolBars[ToolBars::kFile]->setObjectName("ToolBarFile");

    m_toolBars[ToolBars::kFile]->addActions({ m_actions[Actions::kNewFile],
                                              m_actions[Actions::kOpenFile],
                                              m_actions[Actions::kSaveFile],
                                            //m_actions[Actions::kSaveAsFile] 
        });
    m_toolBars[ToolBars::kFile]->setFloatable(false);

    m_toolBars[ToolBars::kView] = addToolBar(tr("View"));
    m_toolBars[ToolBars::kView]->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
    m_toolBars[ToolBars::kView]->setObjectName("ToolBarView");
    m_toolBars[ToolBars::kView]->setMovable(false);
    m_toolBars[ToolBars::kView]->addSeparator();
    m_toolBars[ToolBars::kView]->addAction(m_actions[Actions::kTextEditor]);
    m_toolBars[ToolBars::kView]->addSeparator();
    m_toolBars[ToolBars::kView]->setIconSize({ g_kIconSize, g_kIconSize });
    QMainWindow::addToolBar(Qt::ToolBarArea::BottomToolBarArea, m_toolBars[ToolBars::kView]);

    m_toolBars[ToolBars::kNavigator] = addToolBar(tr("Navigator"));
    m_toolBars[ToolBars::kNavigator]->setObjectName("ToolNavigator");
    m_toolBars[ToolBars::kNavigator]->setMovable(false);
    m_toolBars[ToolBars::kNavigator]->setIconSize({ g_kIconSize * 3, g_kIconSize * 3 });
    m_toolBars[ToolBars::kNavigator]->setFixedWidth(g_kIconSize * 3);
    QMainWindow::addToolBar(Qt::ToolBarArea::RightToolBarArea, m_toolBars[ToolBars::kNavigator]);
}
//-----------------------------------------------------------------------------
// 
// Создание меню
void MainWindow::createMenus()
{
    m_menus[Menus::kFile] = menuBar()->addMenu(tr("&File"));
    m_menus[Menus::kFile]->addActions({ m_actions[Actions::kNewFile],
                                        m_actions[Actions::kOpenFile],
                                        m_actions[Actions::kSaveFile],
                                        m_actions[Actions::kSaveAsFile] });

    m_menus[Menus::kFile]->addSeparator();
    m_menus[Menus::kFile]->addAction(m_actions[Actions::kCloseFile]);

    m_menus[Menus::kEdit] = menuBar()->addMenu(tr("&Edit"));
    m_menus[Menus::kEdit]->addActions({ m_actions[Actions::kFindWidget] });
    menuBar()->addSeparator();

    m_menus[Menus::kView] = menuBar()->addMenu(tr("&View"));
    m_menus[Menus::kView]->addActions({ m_actions[Actions::kDocumentation],
                                        m_actions[Actions::kScene],
                                        m_actions[Actions::kGallery],
                                        m_actions[Actions::kManuals]});
    menuBar()->addSeparator();

    m_menus[Menus::kHelp] = menuBar()->addMenu(tr("&Help"));
    m_menus[Menus::kHelp]->addActions({ m_actions[Actions::kAbout],
                                        m_actions[Actions::kAboutQt] });

}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createDocumentationToolBar()
{
    Q_ASSERT(m_pDockDocumentation != nullptr);
    auto navigationBar = m_pDockDocumentation->createDefaultToolBar();
    navigationBar->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
    navigationBar->setMinimumHeight(g_kIconSize + 2);
    navigationBar->setIconSize({ g_kIconSize, g_kIconSize });

    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kWebHistoryBack]);
    navigationBar->addAction(m_actions[Actions::kWebHistoryForward]);
    navigationBar->addAction(m_actions[Actions::kWebStopReload]);
    navigationBar->addSeparator();
    navigationBar->addWidget(createExpandingSpacer());
    navigationBar->addSeparator();

    auto title = m_pDocumentation->webTitle();
    title->setMinimumWidth(200);
    navigationBar->addWidget(title);

    navigationBar->addSeparator();
    navigationBar->addWidget(createExpandingSpacer());
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kWebSwitchLanguage]);
    navigationBar->addSeparator();
    navigationBar->addWidget(createFixWSpacer(50));
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kWebZoomIn]);
    navigationBar->addAction(m_actions[Actions::kWebZoomOut]);
    navigationBar->addAction(m_actions[Actions::kWebResetZoom]);
    navigationBar->addSeparator();
    navigationBar->addWidget(createFixWSpacer(50));
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kWebDocOffline]);
    navigationBar->addAction(m_actions[Actions::kWebDocOnline]);
    navigationBar->addSeparator();
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectDocumentation()
{
    Q_ASSERT(m_pDocumentation != nullptr);

    connect(m_actions[Actions::kWebStop], &QAction::triggered, [this]()
    {
        m_pDocumentation->triggerWebPageAction(QWebEnginePage::Stop);
    });

    connect(m_actions[Actions::kWebReload], &QAction::triggered, [this]()
    {
        m_pDocumentation->triggerWebPageAction(QWebEnginePage::Reload);
    });

    connect(m_actions[Actions::kWebZoomIn], &QAction::triggered, [this]()
    {
        m_pDocumentation->setZoomFactor(m_pDocumentation->zoomFactor() + 0.15);
    });

    connect(m_actions[Actions::kWebZoomOut], &QAction::triggered, [this]()
    {
        m_pDocumentation->setZoomFactor(m_pDocumentation->zoomFactor() - 0.15);
    });

    connect(m_actions[Actions::kWebResetZoom], &QAction::triggered, [this]()
    {
        m_pDocumentation->setZoomFactor(1.0);
    });

    connect(m_actions[Actions::kWebHistoryBack], &QAction::triggered, [this]()
    {
        m_pDocumentation->triggerWebPageAction(QWebEnginePage::Back);
    });

    connect(m_actions[Actions::kWebHistoryForward], &QAction::triggered, [this]()
    {
        m_pDocumentation->triggerWebPageAction(QWebEnginePage::Forward);
    });

    connect(m_actions[Actions::kWebStopReload], &QAction::triggered, [this]()
    {
        m_pDocumentation->triggerWebPageAction(QWebEnginePage::WebAction(
            m_actions[Actions::kWebStopReload]->data().toInt())
        );
    });

    connect(m_actions[Actions::kWebDocOffline], &QAction::triggered, [this]()
    {
        m_pDocumentation->slotSwitchMode(Mode::WebDocOffline);
    });

    connect(m_actions[Actions::kWebDocOnline], &QAction::triggered, [this]()
    {
        m_pDocumentation->slotSwitchMode(Mode::WebDocOnline);
    });

    connect(m_actions[Actions::kWebSwitchLanguage], &QAction::triggered, [this]()
    {
        static QIcon ruIcon(svgIcon(QStringLiteral(":/res/icons/web/ru.svg")));
        static QIcon enIcon(svgIcon(QStringLiteral(":/res/icons/web/en.svg")));

        if (m_pDocumentation->currentLanguage() == Actions::kWebDocRuLang)
        {
            m_pDocumentation->slotSwitchLanguage(Actions::kWebDocEnLang);
            m_actions[Actions::kWebSwitchLanguage]->setIcon(ruIcon);
            m_actions[Actions::kWebSwitchLanguage]->setToolTip(tr("switch to russian"));
        }
        else
        {
            m_pDocumentation->slotSwitchLanguage(Actions::kWebDocRuLang);
            m_actions[Actions::kWebSwitchLanguage]->setIcon(enIcon);
            m_actions[Actions::kWebSwitchLanguage]->setToolTip(tr("switch to english"));
        }
    });

    connect(m_pDocumentation, &WebViewWidget::webActionEnabledChanged,
        this, &MainWindow::slotWebActionEnabledChanged);

    connect(m_pDocumentation, &DocumentationWidget::loadProgress,
        this, &MainWindow::slotWebViewLoadProgress);

    connect(m_pDocumentation, &WebViewWidget::devToolsRequested,
        [this](QWebEnginePage* source)
    {
        auto dockDevTools = new ads::CDockWidget("Documentation DevTools");
        //auto docDevProfile = new QWebEngineProfile("DocDevTools");
        //docDevProfile->setCachePath(m_currentAppExecutablePath + "/WebCache/DocDev");

        auto devTools = new WebViewWidget("Documentation DevTools", nullptr);

        dockDevTools->setWidget(devTools->webView());
        source->setDevToolsPage(devTools->webView()->page());
        source->triggerAction(QWebEnginePage::InspectElement);

        dockDevTools->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);

        auto area = m_pDockConsoleCodeBuilder->dockAreaWidget();
        m_pDockManager->addDockWidget(ads::CenterDockWidgetArea, dockDevTools, area);

        m_pDockConsoleCodeBuilder->toggleView(true);
        area->setCurrentDockWidget(dockDevTools);
    });

    connect(m_pDocumentation, &DocumentationWidget::signalToggledView, [this](int open)
    {
        m_pDockDocumentation->toggleView(open);
    });
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildDocumentationDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockDocumentation = new ads::CDockWidget("Documentation");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockDocumentation, area);

    auto icon = QIcon(QStringLiteral(":/res/icons/doc.svg"));
    m_pDockDocumentation->setIcon(icon);
    m_pDockDocumentation->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);

    m_actions[Actions::kDocumentation] = m_pDockDocumentation->toggleViewAction();
    m_actions[Actions::kDocumentation]->setShortcut(QString("Ctrl+Shift+D"));
    m_actions[Actions::kDocumentation]->setIcon(icon);
    m_actions[Actions::kDocumentation]->setText(tr("Docs"));

    connect(m_pDockDocumentation, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pDocumentation == nullptr)
        {
            //auto docProfile = new QWebEngineProfile("Documentation");
            //docProfile->setCachePath(m_currentAppExecutablePath + "/WebCache/Doc");
            m_pDocumentation = new DocumentationWidget("Documentation", nullptr);
            m_pDockDocumentation->setWidget(m_pDocumentation);
            m_pDockDocumentation->setWindowTitle(tr("Documentation"));

            createDocumentationToolBar();
            connectDocumentation();
        }
    });

    m_pDockDocumentation->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createSceneToolBar()
{
    Q_ASSERT(m_pDockScene != nullptr);

    auto navigationBar = m_pDockScene->createDefaultToolBar();
    navigationBar->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
    navigationBar->setMinimumHeight(g_kIconSize + 2);
    navigationBar->setIconSize({ g_kIconSize, g_kIconSize });

    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kSceneOpenModel]);
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kSceneAddModel]);
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kSceneClean]);
    navigationBar->addSeparator();

    navigationBar->addWidget(createFixWSpacer(20));
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kSceneZoomToFit]);
    m_pCheckBoxZoomFit = new QCheckBox();
    m_pCheckBoxZoomFit->setText(tr("Auto"));
    //m_pCheckBoxZoomFit->setIcon(svgIcon(QStringLiteral(":/res/icons/scene/ZoomAuto.svg")));
    //m_pCheckBoxZoomFit->setFixedWidth(30);
    m_pCheckBoxZoomFit->setChecked(true);
    navigationBar->addWidget(m_pCheckBoxZoomFit);
    navigationBar->addSeparator();
    navigationBar->addWidget(createFixWSpacer(20));

    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kSceneAnimated]);
    navigationBar->addSeparator();
    //----------------------
    navigationBar->addWidget(createExpandingSpacer());

    //navigationBar->addSeparator();
    //auto menuBar = new QMenuBar(navigationBar);
    //menuBar->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    //auto menu = new QMenu("Test", menuBar);
    //
    //auto Action = menu->addAction(tr("Choice 1")/*, sender, SLOT()*/);
    //Action = menu->addAction(tr("Choice 2")/*, sender, SLOT()*/);
    //menu->addAction(tr("Choice 3")/*, sender, SLOT()*/);
    //
    //menuBar->addMenu(menu);
    //navigationBar->addWidget(menuBar);

    ColorButton* ModelColor = new ColorButton();
    ModelColor->setText(QObject::tr("Model"));
    connect(ModelColor, &ColorButton::colorChangedForModel, m_pScene.get(), &VisionScene::slotModelColor);
    ModelColor->setColorFor(ColorFor::Model);
    ModelColor->setColor(QColor(220,220,220));

    ColorButton* highlightColor = new ColorButton();
    highlightColor->setText(QObject::tr("Highlight"));
    connect(highlightColor, &ColorButton::colorChanged, m_pScene.get(), &VisionScene::slotHighlightColor);
    highlightColor->setColorFor(ColorFor::SOrH);
    highlightColor->setColor(m_pScene->highlightColor());

    ColorButton* selectionColor = new ColorButton();
    selectionColor->setText(QObject::tr("Selection"));
    connect(selectionColor, &ColorButton::colorChanged, m_pScene.get(), &VisionScene::slotSelectionColor);
    selectionColor->setColorFor(ColorFor::SOrH);
    selectionColor->setColor(m_pScene->selectionColor());

    navigationBar->addSeparator();
    navigationBar->addWidget(ModelColor);
    navigationBar->addWidget(highlightColor);
    navigationBar->addWidget(selectionColor);
    navigationBar->addSeparator();
    // Filter
    navigationBar->addAction(m_actions[Actions::kFilter]);
    // Orientations
    navigationBar->addSeparator();
    navigationBar->addAction(m_actions[Actions::kFront]);

    navigationBar->addAction(m_actions[Actions::kDown]);

    navigationBar->addAction(m_actions[Actions::kLeft]);

    navigationBar->addAction(m_actions[Actions::kRight]);

    navigationBar->addAction(m_actions[Actions::kUp]);

    navigationBar->addAction(m_actions[Actions::kRear]);

    navigationBar->addAction(m_actions[Actions::kIsoXYZ]);
    navigationBar->addSeparator();
    //RenderMode

    navigationBar->addAction(m_actions[Actions::kShaded]);

    navigationBar->addAction(m_actions[Actions::khiddenremoved]);

    navigationBar->addAction(m_actions[Actions::kShadedwithedges]);

    navigationBar->addSeparator();
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectScene() 
{
    Q_ASSERT(m_pDockScene != nullptr);
    Q_ASSERT(m_pScene != nullptr);

    connect(m_actions[Actions::kFilter], &QAction::triggered, [this]()
    {
        m_pScene->setFilter(m_actions[Actions::kFilter]->isChecked());
    });
    // Orientations
    connect(m_actions[Actions::kFront], &QAction::triggered, [this]() 
    {
        m_pScene->changeOrientation(Orientation::Front);
    });
    connect(m_actions[Actions::kDown], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::Down);
    });
    connect(m_actions[Actions::kLeft], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::Left);
    });
    connect(m_actions[Actions::kRight], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::Right);
    });
    connect(m_actions[Actions::kUp], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::Up);
    });
    connect(m_actions[Actions::kRear], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::Rear);
    });
    connect(m_actions[Actions::kIsoXYZ], &QAction::triggered, [this]()
    {
        m_pScene->changeOrientation(Orientation::IsoXYZ);
    });
    // RenderMode

    connect(m_actions[Actions::kShaded], &QAction::triggered, [this]()
    {
        m_pScene->changeRenderMode(RenderMode::rm_Shaded);
    });

    connect(m_actions[Actions::kShadedwithedges], &QAction::triggered, [this]()
    {
        m_pScene->changeRenderMode(RenderMode::rm_ShadedWithEdges);
    });

    connect(m_actions[Actions::khiddenremoved], &QAction::triggered, [this]()
    {
        m_pScene->changeRenderMode(RenderMode::rm_HiddenLinesRemoved);
    });


    connect(m_pCheckBoxZoomFit, &QCheckBox::stateChanged, m_pScene.get(), [this](int enable) 
    {
        m_pScene->m_isZoomToFit = (bool)enable;
    });
    connect(m_actions[Actions::kSceneAnimated], &QAction::triggered, [this]()
    {
        m_pScene->animated();
    });

    connect(m_actions[Actions::kSceneOpenModel], &QAction::triggered, [this]()
    {
        m_pScene->openModel();
    });

    connect(m_actions[Actions::kSceneAddModel], &QAction::triggered, [this]()
    {
        m_pScene->addModel();
    });

    connect(m_actions[Actions::kSceneClean], &QAction::triggered, [this]()
    {
        m_pScene->cleanScene();
    });

    connect(m_actions[Actions::kSceneZoomToFit], &QAction::triggered, [this]()
    {
        if (m_pScene->ObjectsSegment->GetBoundingBox().IsEmpty()) 
            m_pScene->viewport()->ZoomToFit(m_pScene->sceneContent()->GetBoundingBox());
        else 
            m_pScene->viewport()->ZoomToFit(m_pScene->ObjectsSegment->GetBoundingBox());

        m_pScene->update();
    });

    // Send Message
    connect(m_pScene.get(), &VisionScene::sendToSceneMessage, [this](const QString& txt, ConsoleText::ResultType t)
    {
        m_pDockConsoleSceneMessage->toggleView(true);
        m_pConsoleSceneMessage->addText(txt, t);
    });

    connect(m_pScene.get(), &VisionScene::sendToSceneMessageColor, [this](const QString& txt, const QColor& color)
    {
        m_pDockConsoleSceneMessage->toggleView(true);
        m_pConsoleSceneMessage->addText(txt, color);
    });
    connect(m_pScene.get(), &VisionScene::clearConsole, m_pConsoleSceneMessage, &ConsoleText::clear);
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildSceneDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockScene = new ads::CDockWidget("Vision");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockScene, area);
    auto icon = svgIcon(QStringLiteral(":/res/icons/scene.svg"));
    m_pDockScene->setIcon(icon);
    m_pDockScene->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    m_actions[Actions::kScene] = m_pDockScene->toggleViewAction();
    m_actions[Actions::kScene]->setShortcut(QString("Ctrl+Shift+V"));
    m_actions[Actions::kScene]->setIcon(icon);
    m_actions[Actions::kScene]->setText(tr("Scene"));

    connect(m_pDockScene, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pScene == nullptr)
        {
            m_pScene.reset(new VisionScene());
            m_pDockScene->setWidget(m_pScene.get());
            m_pDockScene->setWindowTitle(tr("Vision"));

            createSceneToolBar();
            connectScene();
        }
    });

    m_pDockScene->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createTutorialToolBar()
{
    Q_ASSERT(m_pDockTutorial != nullptr);

    auto navigationBar = m_pDockTutorial->createDefaultToolBar();
    navigationBar->setSizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
    navigationBar->setMinimumHeight(g_kIconSize + 6);
    navigationBar->setIconSize({ g_kIconSize, g_kIconSize });

    m_pButtonBackToGallery = new QPushButton(svgIcon(QStringLiteral(":/res/icons/gallery.svg")), tr("Back to gallery"));
    m_pButtonBackToGallery->setMinimumHeight(g_kIconSize + 8);
    m_pButtonBackToGallery->setIconSize({ g_kIconSize, g_kIconSize });
    m_pButtonBackToGallery->setStyleSheet("padding: 6px;");
    //m_pButtonBackToGallery->setFixedWidth(250);

    navigationBar->addWidget(m_pButtonBackToGallery);
    navigationBar->addWidget(createExpandingSpacer());
    navigationBar->addSeparator();
    navigationBar->addActions({ m_actions[Actions::kTutorialZoomIn],
                                m_actions[Actions::kTutorialZoomOut],
                                m_actions[Actions::kTutorialResetZoom]
        });
    navigationBar->addSeparator();
    navigationBar->addWidget(createFixWSpacer(20));
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectTutorial()
{
    connect(m_pTutorial, &TutorialWidget::signalSearchInDoc, [this](const QString& text)
    {
        Q_ASSERT(m_pDockDocumentation != nullptr);
        if (m_pDocumentation == nullptr)
        {
            m_pDockDocumentation->toggleView(true);
        }
        m_pDocumentation->slotSearchInDoc(text);
    });

    // Поиск слова в документации из редактора кода
    connect(m_pTextEditManager, &TextEditManager::signalSearchInDocumentation, [this](const QString& text)
    {
        Q_ASSERT(m_pDockDocumentation != nullptr);
        if (m_pDocumentation == nullptr)
        {
            m_pDockDocumentation->toggleView(true);
        }
        // Поиск слова в документации
        m_pDocumentation->slotSearchInDoc(text);
    });

    connect(m_pTutorial, &TutorialWidget::signalCodeBlockForCurrentEdit, [this](const QString& id)
    {
        if (m_pGallery == nullptr)
        {
            m_pDockGallery->toggleView(true);
        }
        m_pTextEditManager->slotCurrentEditorBySource(m_pGallery->codeBlockById(id));
    });

    connect(m_pTutorial, &TutorialWidget::signalCodeBlockForNewEdit, [this](const QString& id)
    {
        if (m_pGallery == nullptr)
        {
            m_pDockGallery->toggleView(true);
        }
        m_pTextEditManager->slotNewEditorBySource(m_pGallery->codeBlockById(id));
    });

    connect(m_actions[Actions::kTutorial], &QAction::triggered, [this]()
    {
        Q_ASSERT(m_pDockTutorial != nullptr);
        Q_ASSERT(m_pDockDocumentation != nullptr);

        m_pDockTutorial->toggleView(true);
        m_actions[Actions::kTutorial]->setVisible(false);
    });

    connect(m_pTutorial, &WebViewWidget::devToolsRequested,
        [this](QWebEnginePage* source)
    {
        auto dockDevTools = new ads::CDockWidget("Tutorial DevTools");

        //auto tutDevProfile = new QWebEngineProfile("TutorialDevTools");
        //tutDevProfile->setCachePath(m_currentAppExecutablePath + "/WebCache/TutorialDev");
        auto devTools = new WebViewWidget("Tutorial DevTools", nullptr);

        dockDevTools->setWidget(devTools->webView());
        source->setDevToolsPage(devTools->webView()->page());
        source->triggerAction(QWebEnginePage::InspectElement);

        dockDevTools->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);

        auto area = m_pDockConsoleCodeBuilder->dockAreaWidget();
        m_pDockManager->addDockWidget(ads::CenterDockWidgetArea, dockDevTools, area);

        m_pDockConsoleCodeBuilder->toggleView(true);
        area->setCurrentDockWidget(dockDevTools);
    });

    connect(m_pDockTutorial, &ads::CDockWidget::visibilityChanged, [this](bool  visible)
    {
        m_actions[Actions::kTutorial]->setVisible(visible != true);
    });

    connect(m_pButtonBackToGallery, &QPushButton::clicked, [this]()
    {
        m_actions[Actions::kTutorial]->setVisible(false);
        m_pDockGallery->toggleView(true);
    });

    connect(m_actions[Actions::kTutorialZoomIn], &QAction::triggered, [this]()
    {
        m_pTutorial->setZoomFactor(m_pTutorial->zoomFactor() + 0.15);
    });

    connect(m_actions[Actions::kTutorialZoomOut], &QAction::triggered, [this]()
    {
        m_pTutorial->setZoomFactor(m_pTutorial->zoomFactor() - 0.15);
    });

    connect(m_actions[Actions::kTutorialResetZoom], &QAction::triggered, [this]()
    {
        m_pTutorial->setZoomFactor(1.0);
    });
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildTutorialDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockTutorial = new ads::CDockWidget("Tutorial");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockTutorial, area);


    auto icon = svgIcon(QStringLiteral(":/res/icons/backtotutorial.svg"));
    m_pDockTutorial->setIcon(icon);

    m_pDockTutorial->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);

    m_actions[Actions::kTutorial] = m_pDockTutorial->toggleViewAction();
    m_actions[Actions::kTutorial]->setIcon(icon);
    m_actions[Actions::kTutorial]->setText(tr("back to tutorial"));
    m_actions[Actions::kTutorial]->setVisible(false);

    //auto tutProfile = new QWebEngineProfile("Tutorial");
    //tutProfile->setCachePath(m_currentAppExecutablePath + "/WebCache/Tutorial");
    m_pTutorial = new TutorialWidget("Tutorial", nullptr);

    m_pDockTutorial->setWidget(m_pTutorial);
    m_pDockTutorial->setWindowTitle(tr("Tutorial"));

    createTutorialToolBar();
    connectTutorial();
    connect(m_pDockTutorial, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pTutorial == nullptr)
        {
        }
    });
    m_pDockTutorial->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createGalleryToolBar()
{
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectGallery()
{
    connect(m_pGallery, &TutorialGalleryWidget::signalRunTutorial, [this](const QString& tutorialSource, const QString& tutorialPath)
    {
        m_pDockTutorial->toggleView(true);
        m_pTutorial->slotReceiveSource(tutorialSource, tutorialPath);
    });
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildGalleryDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockGallery = new ads::CDockWidget("Tutorials Gallery");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockGallery, area);

    auto icon = svgIcon(QStringLiteral(":/res/icons/gallery.svg"));
    m_pDockGallery->setIcon(icon);
    m_pDockGallery->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    m_actions[Actions::kGallery] = m_pDockGallery->toggleViewAction();
    m_actions[Actions::kGallery]->setShortcut(QString("Ctrl+Shift+G"));
    m_actions[Actions::kGallery]->setIcon(icon);
    m_actions[Actions::kGallery]->setText(tr("Gallery"));

    connect(m_pDockGallery, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pGallery == nullptr)
        {
            m_pGallery = new TutorialGalleryWidget();

            m_pDockGallery->setWidget(m_pGallery);
            m_pDockGallery->setWindowTitle(tr("Tutorials Gallery"));

            createGalleryToolBar();
            connectGallery();
        }
    });

    m_pDockGallery->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createBuilderConsoleToolbar()
{

}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectBuilderConsole()
{
    connect(m_pConsoleCodeBuilder, &ConsoleText::signalMoveToError, m_pCodeBuilder.get(), &CppCodeBuilder::slotMoveToError);
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildBuilderConsoleDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockConsoleCodeBuilder = new ads::CDockWidget("Console output");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockConsoleCodeBuilder, area);

    auto icon = svgIcon(QStringLiteral(":/res/icons/console.svg"));
    m_pDockConsoleCodeBuilder->setIcon(icon);
    m_actions[Actions::KSceneCon] = m_pDockConsoleCodeBuilder->toggleViewAction();
    m_actions[Actions::KSceneCon]->setIcon(icon);
    m_actions[Actions::KSceneCon]->setText(tr("Console output"));
    m_toolBars[ToolBars::kView]->addAction(m_actions[Actions::KSceneCon]);

    connect(m_pDockConsoleCodeBuilder, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pConsoleCodeBuilder == nullptr)
        {
            m_pConsoleCodeBuilder = new ConsoleText();
            m_pDockConsoleCodeBuilder->setWidget(m_pConsoleCodeBuilder);
            m_pDockConsoleCodeBuilder->setWindowTitle(tr("Console output"));

            createBuilderConsoleToolbar();
            connectBuilderConsole();
        }
    });

    m_pDockConsoleCodeBuilder->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createSceneConsoleToolbar()
{

}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectSceneConsole()
{

}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildSceneConsoleDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockConsoleSceneMessage = new ads::CDockWidget("Scene message");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockConsoleSceneMessage, area);

    auto icon = svgIcon(QStringLiteral(":/res/icons/console.svg"));
    m_pDockConsoleSceneMessage->setIcon(icon);
    m_actions[Actions::KMessageCon] = m_pDockConsoleSceneMessage->toggleViewAction();
    m_actions[Actions::KMessageCon]->setIcon(icon);
    m_actions[Actions::KMessageCon]->setText(tr("Scene message"));
    m_toolBars[ToolBars::kView]->addAction(m_actions[Actions::KMessageCon]);

    connect(m_pDockConsoleSceneMessage, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pConsoleSceneMessage == nullptr)
        {
            m_pConsoleSceneMessage = new ConsoleText();
            m_pDockConsoleSceneMessage->setWidget(m_pConsoleSceneMessage);
            m_pDockConsoleSceneMessage->setWindowTitle(tr("Scene message"));

            createSceneConsoleToolbar();
            connectSceneConsole();
        }
    });

    m_pDockConsoleSceneMessage->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createPdfListToolBar()
{
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectPdfList()
{
    connect(m_pPdfListWidget, &PdfListWidget::signalSelectPdfFilePath, [this](const QString& filePath, const QString& fileName)
    {
        auto icon = QIcon(svgIcon(QStringLiteral(":/res/icons/pdf.svg")));

        auto pdfDock = new ads::CDockWidget(fileName);
        auto pdf= new PdfReaderWidget(fileName, filePath);
        pdfDock->setWidget(pdf);
        pdfDock->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);
        pdfDock->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
        pdfDock->setIcon(icon);
        auto action = pdfDock->toggleViewAction();
        action->setIcon(icon);
        m_toolBars[ToolBars::kNavigator]->insertAction(m_actions[Actions::kManuals], action);

        auto area = m_pDockPdfList->dockAreaWidget();
        /*auto newArea = */m_pDockManager->addDockWidget(ads::CenterDockWidgetArea, pdfDock, area);
    });
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildPdfListDock(ads::DockWidgetArea place, ads::CDockAreaWidget* area)
{
    m_pDockPdfList = new ads::CDockWidget("Manuals");
    auto newArea = m_pDockManager->addDockWidget(place, m_pDockPdfList, area);
    auto icon = svgIcon(QStringLiteral(":/res/icons/manuals.svg"));
    m_pDockPdfList->setIcon(icon);
    m_pDockPdfList->setToggleViewActionMode(ads::CDockWidget::ActionModeShow);
    m_actions[Actions::kManuals] = m_pDockPdfList->toggleViewAction();
    m_actions[Actions::kManuals]->setShortcut(QString("Ctrl+Shift+M"));
    m_actions[Actions::kManuals]->setIcon(icon);
    m_actions[Actions::kManuals]->setText(tr("Manuals"));

    connect(m_pDockPdfList, &ads::CDockWidget::visibilityChanged, [this](bool visible)
    {
        if (visible == true && m_pPdfListWidget == nullptr)
        {
            m_pPdfListWidget = new PdfListWidget();
            m_pDockPdfList->setWidget(m_pPdfListWidget);
            m_pDockPdfList->setWindowTitle(tr("Manuals"));


            createPdfListToolBar();
            connectPdfList();
        }
    });

    m_pDockPdfList->toggleView(false);
    return newArea;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::createTextEditorToolBar()
{

}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectTextEditorList()
{
   
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockAreaWidget* MainWindow::buildTextEditorDock(ads::DockWidgetArea /*place*/, ads::CDockAreaWidget* /*area*/)
{
    auto icon = svgIcon(QStringLiteral(":/res/icons/editor.svg"));

    //auto newArea = m_pTextEditManager->buildFirstEditor(place, area);

    //m_actions[Actions::kTextEditor] = m_pTextEditManager->firstEditorToggleViewAction();
    m_actions[Actions::kTextEditor]->setShortcut(QString("Ctrl+Shift+T"));
    m_actions[Actions::kTextEditor]->setIcon(icon);
    m_actions[Actions::kTextEditor]->setText(tr("Text Editor"));


    createTextEditorToolBar();
    connectTextEditorList();

    return nullptr;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::connectActions()
{
    // Сохранение файла
    connect(m_actions[Actions::kSaveFile], &QAction::triggered, m_pTextEditManager, &TextEditManager::save);

    // Сохранить как
    connect(m_actions[Actions::kSaveAsFile], &QAction::triggered, m_pTextEditManager, &TextEditManager::saveAs);

    // Открытие файла (файлов)
    connect(m_actions[Actions::kOpenFile], &QAction::triggered, m_pTextEditManager, &TextEditManager::openFiles);

    // Открытие формы поиска при нажатии сочетания клавиш ctrl + F
    connect(m_actions[Actions::kFindWidget], &QAction::triggered,
        m_pTextEditManager, &TextEditManager::slotShowFindWidget);

    // Создание новой вкладки
    connect(m_actions[Actions::kNewFile], &QAction::triggered, [this]()
    {
        m_pTextEditManager->slotNewEditorByFilePath("");
    });

    connect(m_actions[Actions::kTextEditor], &QAction::triggered, [this]()
    {
        m_pTextEditManager->textEditorsToggleView(m_actions[Actions::kTextEditor]->isChecked());
    });

    // Закрытие программы
    connect(m_actions[Actions::kCloseFile], &QAction::triggered, this, &MainWindow::close);

    connect(m_actions[Actions::kAbout], &QAction::triggered, [this]() {
        QMessageBox::about(this, tr("About Application"), tr("The <b>Application</b> Todo."));
    });
    connect(m_actions[Actions::kAboutQt], &QAction::triggered, qApp, &QApplication::aboutQt);

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::drawObjects, [this](const QVector<Model>& items)
    {
        m_pDockScene->toggleView(true);
        m_pScene->drawObjects(items);
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::sendToConsole, [this](const QString& txt, ConsoleText::ResultType t)
    {
        m_pDockConsoleCodeBuilder->toggleView(true);
        m_pConsoleCodeBuilder->addText(txt, t);
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::sendToSceneMessage, [this](const QString& txt, ConsoleText::ResultType t)
    {
        m_pDockConsoleSceneMessage->toggleView(true);
        m_pConsoleSceneMessage->addText(txt, t);
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::sendToSceneMessageColor, [this](const QString& txt, const QColor& color)
    {
        m_pDockConsoleSceneMessage->toggleView(true);
        m_pConsoleSceneMessage->addText(txt, color);
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::clearConsole, [this]()
    {
        if (m_pConsoleCodeBuilder == nullptr)
        {
            m_pDockConsoleCodeBuilder->toggleView(true);
        }
        m_pConsoleCodeBuilder->clear();
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::clearConsole, [this]()
    {
        if (m_pConsoleSceneMessage == nullptr)
        {
            m_pDockConsoleSceneMessage->toggleView(true);
        }
        m_pConsoleSceneMessage->clear();
    });

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::startWork, m_pTextEditManager, &TextEditManager::disableButtonDisplay);
    connect(m_pCodeBuilder.get(), &CppCodeBuilder::finishWork, m_pTextEditManager, &TextEditManager::enableButtonDisplay);

    connect(m_pCodeBuilder.get(), &CppCodeBuilder::signalMoveToError, m_pTextEditManager, &TextEditManager::slotMoveToError);
    connect(m_pCodeBuilder.get(), &CppCodeBuilder::signalErrorsList, m_pTextEditManager, &TextEditManager::slotErrorsList);





    connect(m_pTextEditManager, &TextEditManager::sendCode, m_pCodeBuilder.get(), &CppCodeBuilder::receiveCode);

}
//-----------------------------------------------------------------------------
// 
// ---
const QString& MainWindow::themePath(const QString& name)
{
    return m_themesPathList[name];
}
//-----------------------------------------------------------------------------
// 
// ---
QStringList MainWindow::themesList()
{
    QStringList themesList = m_themesPathList.keys();
    return themesList;
}
//-----------------------------------------------------------------------------
// 
// ---
const QString& MainWindow::themeName() const
{
    return m_themeName;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::showPreview()
{
    m_pWelcomeWidget->show();
}

//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::prepareThemes()
{
    m_themesPathList["default"] = "";
    //m_themesPathList["breeze_light"] = ":/light.qss";
    //m_themesPathList["breeze_dark"] = ":/dark.qss";
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::slotSwitchTheme(const QString& themeName)
{
    if (themeName == m_themeName) return;

    if (themeName == "default")
    {
        qApp->setStyleSheet(m_defaultCSS);
        m_themeName = themeName;
        return;
    }

    QFile file(themePath(themeName));

    if (!file.exists())
    {
        qDebug() << "Unable to set stylesheet, theme not found\n";
    }
    else
    {
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&file);
        qApp->setStyleSheet(ts.readAll());
    }
    m_themeName = themeName;
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::closeEvent(QCloseEvent* event)
{
    m_pWelcomeWidget->deleteLater();

    if (!m_pTextEditManager->closeAllEditors())
    {
        event->ignore();
        return;
    }
    savePerspectives();
    saveStates();

    QMainWindow::closeEvent(event);
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::saveStates()
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);
    
    settings.setValue("mainWindow/Geometry", saveGeometry());
    settings.setValue("mainWindow/State", saveState());
    settings.setValue("mainWindow/DockingState", m_pDockManager->saveState());
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::restoreStates()
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);
    
    restoreGeometry(settings.value("mainWindow/Geometry").toByteArray());
    restoreState(settings.value("mainWindow/State").toByteArray());
    m_pDockManager->restoreState(settings.value("mainWindow/DockingState").toByteArray());
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::savePerspectives()
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);
    m_pDockManager->savePerspectives(settings);
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::restorePerspectives()
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);
    m_pDockManager->loadPerspectives(settings);
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::slotWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled)
{
    switch (action) {
    case QWebEnginePage::Back:
        m_actions[Actions::kWebHistoryBack]->setEnabled(enabled);
        break;
    case QWebEnginePage::Forward:
        m_actions[Actions::kWebHistoryForward]->setEnabled(enabled);
        break;
    case QWebEnginePage::Reload:
        m_actions[Actions::kWebReload]->setEnabled(enabled);
        break;
    case QWebEnginePage::Stop:
        m_actions[Actions::kWebStop]->setEnabled(enabled);
        break;
    default:
        qWarning("Unhandled webActionChanged signal");
    }
}
//-----------------------------------------------------------------------------
// 
// ---
void MainWindow::slotWebViewLoadProgress(int progress)
{
    static QIcon stopIcon(svgIcon(QStringLiteral(":/res/icons/web/stop.svg")));
    static QIcon reloadIcon(svgIcon(QStringLiteral(":/res/icons/web/reload.svg")));

    if (0 < progress && progress < 100) {
        m_actions[Actions::kWebStopReload]->setData(QWebEnginePage::Stop);
        m_actions[Actions::kWebStopReload]->setIcon(stopIcon);
        m_actions[Actions::kWebStopReload]->setText(tr("Stop"));
        m_actions[Actions::kWebStopReload]->setToolTip(tr("Stop loading the current page"));
        m_pDocumentation->setProgress(progress);
    }
    else {
        m_actions[Actions::kWebStopReload]->setData(QWebEnginePage::Reload);
        m_actions[Actions::kWebStopReload]->setText(tr("Reload"));
        m_actions[Actions::kWebStopReload]->setIcon(reloadIcon);
        m_actions[Actions::kWebStopReload]->setToolTip(tr("Reload the current page"));
        m_pDocumentation->setProgress(0);
    }
}