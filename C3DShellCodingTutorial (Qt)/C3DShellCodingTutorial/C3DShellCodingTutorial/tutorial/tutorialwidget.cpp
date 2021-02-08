#include <QProgressBar>
#include <QMenu>
#include <QScreen>
#include <QToolbar>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

#include <QWebChannel>

#include <DockWidget.h>
#include <DockAreaWidget.h>

#include "tutorialwidget.h"
#include "webview.h"
#include "tutorialwebpage.h"

TutorialWidget::TutorialWidget( const QString& title, QWebEngineProfile* profile,
    double zoomFactor,  QWidget* parent)
    : WebViewWidget(title, profile, zoomFactor, parent)
{
    auto currentWebView = webView();
  
    TutorialWebPage* webPage = new TutorialWebPage(pageProfile(), currentWebView);
    currentWebView->setPage(webPage);

    auto webChannel = new QWebChannel(this);
    webChannel->registerObject(QStringLiteral("tutorialPackage"), &m_package);
    webPage->setWebChannel(webChannel);

    webView()->load(QUrl("qrc:/res/texts/tutorialbody.html"));
    
    connect(webPage, &TutorialWebPage::signalSearchInDoc, this, &TutorialWidget::signalSearchInDoc);
    connect(webPage, &TutorialWebPage::signalCodeBlockForCurrentEdit, this, &TutorialWidget::signalCodeBlockForCurrentEdit);
    connect(webPage, &TutorialWebPage::signalCodeBlockForNewEdit, this, &TutorialWidget::signalCodeBlockForNewEdit);

    connectDevTools();


    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(currentWebView);
    setLayout(layout);
}

void TutorialWidget::slotReceiveSource(const QString& filePath, const QString& tutorialPath)
{
    QFile source(filePath);
    source.open(QIODevice::ReadOnly);
    m_content = source.readAll();
    m_package.setText(m_content, tutorialPath);
}