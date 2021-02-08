#include <QProgressBar>
#include <QMenu>
#include <QScreen>
#include <QToolbar>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QWebChannel>

#include <DockWidget.h>
#include <DockAreaWidget.h>

#include "pdfreaderwidget.h"
#include "webview.h"
#include "webpage.h"

PdfReaderWidget::PdfReaderWidget( const QString& title, const QString& pdfFilePath, QWebEngineProfile* profile,
    double zoomFactor,  QWidget* parent)
    : WebViewWidget(title, profile, zoomFactor, parent)
{
    auto currentWebView = webView();
  
    auto  webPage = new WebPage(pageProfile(), currentWebView);
    currentWebView->setPage(webPage);

    auto webChannel = new QWebChannel(this);

    m_package.setUrl(pdfFilePath);
    webChannel->registerObject(QStringLiteral("pdfPackage"), &m_package);
    webPage->setWebChannel(webChannel);

    webView()->load(QUrl::fromLocalFile(qApp->applicationDirPath() + "/pdfjs/web/viewer.html"));
    
    connectDevTools();

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(currentWebView);
    setLayout(layout);
}