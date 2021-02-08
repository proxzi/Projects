#pragma once

#include <QString>
#include <QWebEngineProfile>
#include "webviewwidget.h"

#include "pdfpackage.h"

class PdfReaderWidget : public WebViewWidget
{
    Q_OBJECT

public:
    explicit PdfReaderWidget(const QString& title, const QString& pdfFilePath,
        QWebEngineProfile* profile = QWebEngineProfile::defaultProfile(),
        double zoomFactor = 1.0, QWidget* parent = nullptr);

private:
    PdfPackage m_package;
};