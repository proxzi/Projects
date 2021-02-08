#include <QGuiApplication>
#include <QComboBox>
#include <QScreen>
#include <QListWidget>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>

#include "ui_compilersearch.h"
#include "compilersearch.h"
#include "storagelocation.h"
#include "globaldef.h"

//-----------------------------------------------------------------------------
//
// ---
CompilerSearch::CompilerSearch(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CompilerSearch)
    , m_path(g_kDefaultMSVCPath)
    , m_type("Community")
    , m_year("2019")
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);
    ui->labelPath->setText(m_path);


    // Default window geometry - center on screen

    resize(QGuiApplication::primaryScreen()->availableGeometry().width() * 2 / 6, 
        QGuiApplication::primaryScreen()->availableGeometry().height() * 2 / 7);

    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight, Qt::AlignCenter, frameSize(),
        QGuiApplication::primaryScreen()->availableGeometry()));

    ui->typeListWidget->addItems(
        { 
            "Visual Studio Community",
            "Visual Studio Professional",
            "Visual Studio Enterprise",
            "BuildTools" 
        });

    ui->yearListWidget->addItems({"2019", "2017", "2015"});

    connect(ui->typeListWidget, qOverload<int>(&QComboBox::activated), [this](int index)
    {
        switch (index)
        {
        case 3:
            m_type = "BuildTools";
            break;
        case 2:
            m_type = "Enterprise";
            break;
        case 1:
            m_type = "Professional";
            break;
        case 0:
            Q_FALLTHROUGH();
        default:
            m_type = "Community";
            break;
        }
        m_path = g_kVariableMSVCPath.arg(m_year).arg(m_type);
        ui->labelPath->setText(m_path);
    });

    connect(ui->yearListWidget, qOverload<const QString&>(&QComboBox::activated), [this](const QString& value)
    {
        m_year = value;
        m_path = g_kVariableMSVCPath.arg(m_year).arg(m_type);
        ui->labelPath->setText(m_path);
    });

    connect(ui->radioButtonDefault, &QRadioButton::clicked, [this](bool checked)
    {
        if (lastChoice != 0)
        {
            ui->typeListWidget->setDisabled(true);
            ui->yearListWidget->setDisabled(true);
            ui->pushButtonOpen->setDisabled(true);

            lastChoice = 0;
            m_path = g_kDefaultMSVCPath;
            ui->labelPath->setText(m_path);
        }
    });

    connect(ui->radioButtonFromList, &QRadioButton::clicked, [this](bool checked)
    {
        if (lastChoice != 1)
        {
            ui->typeListWidget->setEnabled(true);
            ui->yearListWidget->setEnabled(true);
            ui->pushButtonOpen->setDisabled(true);
            lastChoice = 1;

            m_path = g_kVariableMSVCPath.arg(m_year).arg(m_type);
            ui->labelPath->setText(m_path);
        }
    });

    connect(ui->radioButtonPath, &QRadioButton::clicked, [this](bool checked)
    {
        if (lastChoice != 2)
        {
            ui->typeListWidget->setDisabled(true);
            ui->yearListWidget->setDisabled(true);
            ui->pushButtonOpen->setEnabled(true);
            lastChoice = 2;
        }
    });

    connect(ui->pushButtonOpen, &QRadioButton::clicked, [this](bool checked)
    {
        auto fileName = QFileDialog::getOpenFileName(this, tr("Path to vcvars64.bat"),
            QString("C:/Program Files (x86)/Microsoft Visual Studio/)_"), tr("*.bat"));
        if (fileName.isEmpty()) { return false; }
        ui->labelPath->setText(fileName);
    });


    connect(ui->pushButtonAccept, &QPushButton::clicked, [this]()
    {
        if (QFileInfo(m_path).fileName() == "vcvars64.bat")
        {
            APP.saveCommonSettings("Build/CompilerPath", m_path);
        }
        close();
    });

    connect(ui->pushButtonSkip, &QPushButton::clicked, [this]()
    {
        close();
    });
}

void CompilerSearch::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}