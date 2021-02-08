#include <QGuiApplication>
#include <QComboBox>
#include <QScreen>
#include <QListWidget>
#include <QFileDialog>
#include <QSettings>

#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "mainwindow.h"
#include "compilersearch.h"
#include "storagelocation.h"

//-----------------------------------------------------------------------------
//
// ---
WelcomeWidget::WelcomeWidget(QWidget* parent)
    : QWidget(nullptr)
    , ui(new Ui::WelcomeWidget)
    , m_pMainWindow(qobject_cast<MainWindow*>(parent))
    , m_workSelected("")
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint |
        Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

    ui->setupUi(this);
    ui->listWidget->setItemDelegate(new FileItemDelegate(ui->listWidget));


    // Default window geometry - center on screen
    resize(QGuiApplication::primaryScreen()->availableGeometry().width() * 2 / 8, 
        QGuiApplication::primaryScreen()->availableGeometry().height() * 2 / 5);

    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()));

}
//-----------------------------------------------------------------------------
//
// ---
void WelcomeWidget::showEvent(QShowEvent* /*event*/)
{
    if (!APP.isSavedCommonSettings("Build/CompilerPath"))
    {
        auto pCompilerSearch = new CompilerSearch(this);
        pCompilerSearch->setWindowModified(true);
        pCompilerSearch->show();
    }

    connect(ui->buttonOpen, &QPushButton::clicked, [this]()
    {
        emit signalOpenFiles();
    });

    connect(ui->buttonCreate, &QPushButton::clicked, [this]()
    {
        emit signalOpenFile(QString());
    });

    connect(ui->buttonTutorialGallery, &QPushButton::clicked, [this]()
    {
        emit signalShowTutorialGallery();
    });

    connect(ui->buttonDocumentation, &QPushButton::clicked, [this]()
    {
        emit signalShowDocumentation();
    });

    connect(ui->buttonManuals, &QPushButton::clicked, [this]()
    {
        emit signalShowManuals();
    });

    connect(ui->listWidget, &QListWidget::itemPressed, [this]()
    {
        m_workSelected = m_workList[ui->listWidget->currentRow()].second;
        emit signalOpenFile(m_workSelected);
    });

    connect(ui->comboBoxLanguages, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index) 
        { 
            APP.saveCommonSettings("GlobalLanguage", index);
            emit setLanguages(index); 
        });

    setupThemesComboBox();

    ui->listWidget->clear();
    m_workList = APP.readFromWorkFolder();
    for (auto &file : m_workList)
    {
        QListWidgetItem* listItem = new QListWidgetItem(file.first);
        listItem->setToolTip(file.second);
        listItem->setIcon(svgIcon(QStringLiteral(":/res/icons/editor.svg")));
        ui->listWidget->addItem(listItem);
    }

    ui->comboBoxLanguages->setCurrentIndex(APP.restoreCommonSettings("GlobalLanguage", 0).toInt());
}
//-----------------------------------------------------------------------------
// 
// ---
void WelcomeWidget::setupThemesComboBox()
{
    ui->comboBoxThemes->clear();
    if (!m_pMainWindow) return;

    auto themesList = m_pMainWindow->themesList();
    ui->comboBoxThemes->addItems(themesList);
    auto t = m_pMainWindow->themeName();
    ui->comboBoxThemes->setCurrentText(m_pMainWindow->themeName());

    connect(ui->comboBoxThemes, &QComboBox::currentTextChanged, [this](const QString& themeName)
        {
            emit signalSwitchTheme(themeName);
        });
}

void WelcomeWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}