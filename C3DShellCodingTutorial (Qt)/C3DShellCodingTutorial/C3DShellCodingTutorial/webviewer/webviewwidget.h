#pragma once

#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWidget>

#include "globaldef.h"

class QLabel;
class WebView;

class WebViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WebViewWidget(const QString& title, QWebEngineProfile* profile = QWebEngineProfile::defaultProfile(),
        double zoomFactor = 1.0, QWidget* parent = nullptr);

    WebView* webView();
    QWebEngineProfile* pageProfile();

    double zoomFactor() const;

signals:
    void webActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
    void devToolsRequested(QWebEnginePage* source);

public slots:
    void setUrl(const QUrl& url);
    void triggerWebPageAction(QWebEnginePage::WebAction action);
    void setZoomFactor(double zoomFactor_);

protected:
    void connectDevTools();

private slots:
    void reload();

private:
    WebView* m_pWebView;
    QWebEngineProfile* m_profile;
};