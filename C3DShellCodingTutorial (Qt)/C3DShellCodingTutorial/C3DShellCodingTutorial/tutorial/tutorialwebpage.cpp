
#include <QWebEngineProfile>
#include <QRegExp>
#include "tutorialwebpage.h"


TutorialWebPage::TutorialWebPage(QWebEngineProfile* profile, QObject* parent)
    : WebPage(profile, parent)
{

}
//-----------------------------------------------------------------------------
// 
// ---
TutorialWebPage::~TutorialWebPage()
{

}
//-----------------------------------------------------------------------------
// 
// ---
bool TutorialWebPage::acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame)
{
    if (type == QWebEnginePage::NavigationTypeLinkClicked)
    {
        if (url.scheme() == QString("doc"))
        {
            QString shortUrl = url.toString().remove("doc::/");
            emit signalSearchInDoc(shortUrl);
            return false;
        }
        if (url.scheme() == QString("edit-current"))
        {
            QString id = url.toString().remove("edit-current::/");
            emit signalCodeBlockForCurrentEdit(id);

            return false;
        }
        if (url.scheme() == QString("edit-new"))
        {
            QString id = url.toString().remove("edit-new::/");
            emit signalCodeBlockForNewEdit(id);
            return false;
        }
    }
    return WebPage::acceptNavigationRequest(url, type, isMainFrame);
}