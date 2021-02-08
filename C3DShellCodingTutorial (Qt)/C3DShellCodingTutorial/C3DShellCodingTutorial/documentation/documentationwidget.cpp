#include <QProgressBar>
#include <QMenu>
#include <QScreen>
#include <QToolbar>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <QWebChannel>
#include <QMessageBox>

#include <DockWidget.h>
#include <DockAreaWidget.h>

#include "documentationwidget.h"
#include "storagelocation.h"
#include "webview.h"
#include "webpage.h"

DocumentationWidget::DocumentationWidget(const QString& title, QWebEngineProfile* profile,
    double zoomFactor, QWidget* parent)
    : WebViewWidget(title, profile, zoomFactor, parent)
    , m_pProgressBar(new QProgressBar(this))
    , m_pTitle(new QLabel("", this))
{
    WebPage::appendDefaultBrowserLink("http://www.doxygen.nl/index.html");

    QStringList scripts{
        ":/res/scripts/qwebchannel.js",
        ":/res/scripts/documentation.js"
    };

    auto currentWebView = webView();
    currentWebView->addScripts(scripts);

    auto webChannel = new QWebChannel(this);
    webChannel->registerObject(QStringLiteral("documentationPackage"), &m_package);

    WebPage* webPage = new WebPage(pageProfile(), currentWebView);
    webPage->setWebChannel(webChannel);

    currentWebView->setPage(webPage);

    connect(&m_package, &DocumentationPackage::signalUpdateCurrentUrl, [this](const QString& url)
    {
        m_lastSearch = url;
    });

    connect(&m_package, &DocumentationPackage::signalSearchIsSuccess, this, &DocumentationWidget::signalToggledView);

    connect(currentWebView, &QWebEngineView::titleChanged, [this](const QString& title) {
        m_pTitle->setText(title);
    });

    connect(currentWebView, &QWebEngineView::urlChanged, [this](const QUrl& url) {
        emit urlChanged(url);

        QString url_ = url.toString();
        if (url_.startsWith("file:///"))
        {
            m_currentUrl = url_.remove(QString("file:///%1/").arg(m_currentRoot.arg(m_currentLang)));
        }
        else
        {
            m_currentUrl = url_.remove(QString("%1/").arg(m_currentRoot.arg(m_currentLang)));
        }

        //m_currentUrl = url_.remove(QRegExp(QString("^(file:///)?%1/").arg(m_currentRoot.arg(m_currentLang))));
    });

    connect(currentWebView, &QWebEngineView::loadProgress, [this](int progress) {
        emit loadProgress(progress);
    });

    connect(currentWebView, &WebView::webActionEnabledChanged, [this](QWebEnginePage::WebAction action, bool enabled) {
        emit webActionEnabledChanged(action, enabled);
    });

    connectDevTools();

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    m_pProgressBar->setMaximumHeight(5);
    m_pProgressBar->setTextVisible(false);
    m_pProgressBar->setStyleSheet(QStringLiteral(
        "QProgressBar {border: 0px}"
        "QProgressBar::chunk {background-color: #da4453}"
    ));

    layout->addWidget(m_pProgressBar);
    layout->addWidget(currentWebView);

    setLayout(layout);

    emit loadProgress(0);
    emit webActionEnabledChanged(QWebEnginePage::Back, false);
    emit webActionEnabledChanged(QWebEnginePage::Forward, false);
    emit webActionEnabledChanged(QWebEnginePage::Stop, false);
    emit webActionEnabledChanged(QWebEnginePage::Reload, true);

    restoreState();

    m_lastSearch = QString("%1/%2").arg(m_currentRoot.arg(m_currentLang)).arg(m_currentUrl);
    slotSwitchLanguage(m_currentLanguageMode);
    slotSwitchMode(m_webMode);
}
DocumentationWidget::~DocumentationWidget()
{
    saveState();
}
QWidget* DocumentationWidget::webTitle()
{
    return m_pTitle;
}

Actions DocumentationWidget::currentLanguage()
{
    return m_currentLanguageMode;
}

void DocumentationWidget::setProgress(int progress)
{
    m_pProgressBar->setValue(progress);
}

void DocumentationWidget::slotSwitchMode(Mode mode)
{
    m_webMode = mode;

    switch (mode)
    {
    case Mode::WebDocOnline:
        m_currentRoot = APP.webDocRoot();
        break;
    case Mode::WebDocOffline:
        Q_FALLTHROUGH();
    default:
        m_currentRoot = APP.localDocRoot();
        break;
    }

    updateSearchUrl();
}

void DocumentationWidget::slotSwitchLanguage(Actions lang)
{
    m_currentLanguageMode = lang;

    switch (lang)
    {
    case Actions::kWebDocRuLang:
        m_currentLang = g_kDefaultRu;
        break;
    case Actions::kWebDocEnLang:
        Q_FALLTHROUGH();
    default:
        m_currentLang = g_kDefaultEn;
        break;
    }

    updateSearchUrl();
}

void DocumentationWidget::updateSearchUrl()
{
    m_lastSearch = QString("%1/%2").arg(m_currentRoot.arg(m_currentLang)).arg(m_currentUrl);
    setUrl(QUrl::fromUserInput(m_lastSearch));
}

void DocumentationWidget::slotSearchInDoc(const QString& text)
{
    m_package.setText(text, m_currentRoot.arg(m_currentLang));
}
//-----------------------------------------------------------------------------
// 
// ---
void DocumentationWidget::saveState()
{
    APP.saveCommonSettings("Documentation/Web/Root", m_currentRoot);
    APP.saveCommonSettings("Documentation/Web/Lang", m_currentLang);
    APP.saveCommonSettings("Documentation/Web/Url", m_currentUrl);

    QString lang;
    if (m_currentLanguageMode == Actions::kWebDocRuLang)
    {
        lang = "Ru";
    }
    else if (m_currentLanguageMode == Actions::kWebDocEnLang)
    {
        lang = "En";
    }
    APP.saveCommonSettings("Documentation/Lang", lang);

    QString mode;
    if (m_webMode == Mode::WebDocOnline)
    {
        mode = "Online";
    }
    else if (m_webMode == Mode::WebDocOffline)
    {
        mode = "Local";
    }
    APP.saveCommonSettings("Documentation/Mode", mode);
}
//-----------------------------------------------------------------------------
// 
// ---
void DocumentationWidget::restoreState()
{
    m_currentRoot = APP.restoreCommonSettings("Documentation/Web/Root", APP.localDocRoot()).toString();
    m_currentLang = APP.restoreCommonSettings("Documentation/Web/Lang", g_kDefaultEn).toString();
    m_currentUrl = APP.restoreCommonSettings("Documentation/Web/Url", g_kDefaultDocPrefix).toString();

    if (!APP.isSavedCommonSettings("Documentation/Lang"))
    {
        m_currentLanguageMode = g_kDefaultLanguage;
    }
    else if (APP.restoreCommonSettings("Documentation/Lang").toString() == "Ru")
    {
        m_currentLanguageMode = Actions::kWebDocRuLang;
    }
    else if (APP.restoreCommonSettings("Documentation/Lang").toString() == "En")
    {
        m_currentLanguageMode = Actions::kWebDocEnLang;
    }

    if (!APP.isSavedCommonSettings("Documentation/Mode"))
    {
        m_webMode = Mode::WebDocOffline;

    }
    else if (APP.restoreCommonSettings("Documentation/Mode").toString() == "Online")
    {
        m_webMode = Mode::WebDocOnline;

    }
    else if (APP.restoreCommonSettings("Documentation/Mode").toString() == "Local")
    {
        m_webMode = Mode::WebDocOffline;
    }
}