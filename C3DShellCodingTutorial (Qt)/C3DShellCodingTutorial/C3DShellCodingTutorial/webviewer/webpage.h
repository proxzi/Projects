#pragma once
#include <QWebEnginePage>
#include <QStringList>

class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    explicit WebPage(QWebEngineProfile* profile,
        QObject* parent = nullptr);
    ~WebPage();

    static void appendIgnoreLink(const QString& url);
    static void appendDefaultBrowserLink(const QString& url);

protected:
    bool certificateError(const QWebEngineCertificateError& error) override;
    bool acceptNavigationRequest(const QUrl& url, NavigationType type,
        bool isMainFrame) override;

private:
    static QStringList urlsIgnored;
    static QStringList urlsDefaultBrowser;
};