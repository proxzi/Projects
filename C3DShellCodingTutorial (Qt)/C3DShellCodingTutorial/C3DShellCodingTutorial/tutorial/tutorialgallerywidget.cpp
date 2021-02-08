#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QTabwidget>
#include <QListWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>

#include "storagelocation.h"
#include "globaldef.h"
#include "tutorialgallerywidget.h"

TutorialGalleryWidget::TutorialGalleryWidget(QWidget* parent)
    : QWidget(parent)
    , m_currentTutorial(nullptr)
    , m_loader(new TutorialLoader(APP.tutorialsDir()))
{
    auto layout = new QVBoxLayout(this);
    auto mainTabWidget = new QTabWidget();

    m_loader->readTutorialDirectory();
    for (auto &category: m_loader->folders().keys())
    {
        auto listWidget = new QListWidget();
        listWidget->setItemDelegate(new TutorialItemDelegate(listWidget));
        listWidget->setIconSize({100, 100});
        listWidget->setStyleSheet("QListWidget::item:hover { background-color: rgba(63, 191, 202, 0.5); }");
        listWidget->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        for (auto& tutorial : m_loader->folders()[category])
        {
            QListWidgetItem* listItem = new QListWidgetItem(tutorial.title);
            listItem->setIcon(QPixmap(tutorial.imagePath));
            listWidget->addItem(listItem);
        }

        connect(listWidget, &QListWidget::doubleClicked,
            this, &TutorialGalleryWidget::slotOnListDoubleClicked);
        mainTabWidget->addTab(listWidget, category);
    }

    layout->addWidget(mainTabWidget);
    setLayout(layout);
}

void TutorialGalleryWidget::slotOnListDoubleClicked(const QModelIndex& index) 
{

    if (!index.isValid()) 
    {
        return;
    }

    if (QListWidget* listWgt = dynamic_cast<QListWidget*>(sender()))
    {
        if (QListWidgetItem* item = listWgt->item(index.row()))
        {
            for (auto& tutorials : m_loader->folders())
            {
                for (auto& tutorial : tutorials)
                {
                    if (tutorial.title == item->text())
                    {
                        m_currentTutorial = &tutorial;
                        emit signalRunTutorial(m_currentTutorial->source, m_currentTutorial->tutorialPath);
                    }
                }
            }
        }
    }
}

const QString& TutorialGalleryWidget::codeBlockById(const QString& id)
{
    if (m_currentTutorial != nullptr)
    {
        return m_currentTutorial->codeBlocks[id];
    }
}
