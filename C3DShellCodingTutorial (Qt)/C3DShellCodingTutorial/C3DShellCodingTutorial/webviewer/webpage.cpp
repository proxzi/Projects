#include <QMessageBox>
#include <QStyle>
#include <QDesktopServices>
#include <QWebEngineCertificateError>
#include <QWebEngineProfile>
#include "webpage.h"

QStringList WebPage::urlsIgnored = QStringList();
QStringList WebPage::urlsDefaultBrowser = QStringList();

WebPage::WebPage(QWebEngineProfile* profile, QObject* parent)
    : QWebEnginePage(profile, parent)
{
}
WebPage::~WebPage()
{
}
//-----------------------------------------------------------------------------
// 
// ---
void WebPage::appendIgnoreLink(const QString& url)
{
    urlsIgnored.append(url);
}
//-----------------------------------------------------------------------------
// 
// ---
void WebPage::appendDefaultBrowserLink(const QString& url)
{
    urlsDefaultBrowser.append(url);
}
//-----------------------------------------------------------------------------
// 
// ---
bool WebPage::certificateError(const QWebEngineCertificateError& error)
{
    QMessageBox::critical(static_cast<QWidget*>(parent()), ("Certificate Error"), error.errorDescription());
    return false;
}
//-----------------------------------------------------------------------------
// 
// ---
bool WebPage::acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        for (const auto& link : urlsDefaultBrowser)
        {
            if (link == url.toString())
            {
                QDesktopServices::openUrl(url);
                return false;
            }
        }
        for (const auto& link : urlsIgnored)
        {
            if (link == url.toString())
            {
                return false;
            }
        }
    }
    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}