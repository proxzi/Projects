#pragma once
#include "webpage.h"

class TutorialWebPage : public WebPage
{
    Q_OBJECT

public:
    explicit TutorialWebPage(QWebEngineProfile* profile,
        QObject* parent = nullptr);
    ~TutorialWebPage();

protected:
    bool acceptNavigationRequest(const QUrl& url, NavigationType type,
        bool isMainFrame) override;

signals:
    void signalSearchInDoc(const QString& text);
    void signalCodeBlockForCurrentEdit(const QString& id);
    void signalCodeBlockForNewEdit(const QString& id);
};