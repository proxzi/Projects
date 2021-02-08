#include <QFileInfo>
#include <QDir>
#include <QApplication>
#include <QDebug>

#include "pdflistwidget.h"
#include "storagelocation.h"
#include "globaldef.h"

PdfListWidget::PdfListWidget(QWidget* parent)
    : QListWidget(parent)
{
    setStyleSheet("QListWidget::item:hover { background-color: rgba(63, 191, 202, 0.5); padding: 5px;}"
                  "QListWidget::item { padding: 5px;}"
                 );

    setFont(QFont(font().family(), 10, QFont::Bold));
    setSpacing(1);

    QString currentManualsFolderPath;

    if (currentManualsFolderPath.isEmpty())
    {
        currentManualsFolderPath = APP.manualsDir();
    }

    QDir manualsFolderDir(currentManualsFolderPath);
    if (manualsFolderDir.exists())
    {
        auto fileInfoList = manualsFolderDir.entryInfoList();
        
        for (auto& fileInfo : fileInfoList)
        {
            QString fileName = fileInfo.fileName();
            if (fileName.endsWith(".pdf", Qt::CaseInsensitive))
            {
                fileName.remove(".pdf");
                m_pdfList[fileName] = fileInfo.absoluteFilePath();
                auto listItem = new QListWidgetItem(QIcon(svgIcon(QStringLiteral(":/res/icons/pdf.svg"))), fileName);
                addItem(listItem);
            }
        }
    }

    connect(this, &QListWidget::itemPressed, [this](const QListWidgetItem* item)
    {
        emit signalSelectPdfFilePath(m_pdfList[item->text()], item->text());
    });
}