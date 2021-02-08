#include <QToolbar>

#include <DockWidget.h>
#include <DockAreaWidget.h>

#include "webviewwidget.h"
#include "webview.h"
#include "webpage.h"

WebViewWidget::WebViewWidget(const QString& title, QWebEngineProfile* profile, double zoomFactor, QWidget* parent)
    : QWidget(parent)
    , m_pWebView(new WebView(title, zoomFactor))
    , m_profile(profile) 
{
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

WebView* WebViewWidget::webView()
{
    return m_pWebView;
}

void WebViewWidget::triggerWebPageAction(QWebEnginePage::WebAction action)
{
    m_pWebView->triggerPageAction(action);
    m_pWebView->setFocus();
}

void WebViewWidget::setZoomFactor(double zoomFactor_)
{
    m_pWebView->setZoomFactor(zoomFactor_);
}

void WebViewWidget::connectDevTools()
{
    connect(m_pWebView, &WebView::devToolsRequested, this, &WebViewWidget::devToolsRequested);
}

QWebEngineProfile* WebViewWidget::pageProfile()
{
    return m_profile;
}

double WebViewWidget::zoomFactor() const
{
    return m_pWebView->zoomFactor();
}

void WebViewWidget::setUrl(const QUrl& url)
{
    m_pWebView->setUrl(url);
    m_pWebView->setFocus();
}

void WebViewWidget::reload()
{
    m_pWebView->reload();
}