#pragma once

#include <QListWidget>
#include <QMap>

class PdfListWidget : public QListWidget
{
    Q_OBJECT
public:
    PdfListWidget(QWidget* parent = nullptr);

signals:
    void signalSelectPdfFilePath(const QString& filePath, const QString& fileName);

private:
    QMap<QString, QString> m_pdfList;
};