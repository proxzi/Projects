#pragma once

#include <QWebEngineProfile>
#include <QPushButton>

#include "webviewwidget.h"
#include "documentationpackage.h"

class QProgressBar;

class DocumentationWidget : public WebViewWidget
{
    Q_OBJECT

public:
    explicit DocumentationWidget(const QString& title, QWebEngineProfile* profile = QWebEngineProfile::defaultProfile(),
        double zoomFactor = 1.0, QWidget* parent = nullptr);
    ~DocumentationWidget();
    QWidget* webTitle();
    Actions currentLanguage();
    void setProgress(int progress);
signals:
    void linkHovered(const QString& link);
    void loadProgress(int progress);
    void urlChanged(const QUrl& url);
    void signalToggledView(bool open);

public slots:
    void slotSearchInDoc(const QString& text);
    void slotSwitchMode(Mode mode);
    void slotSwitchLanguage(Actions lang);



private:
    void updateSearchUrl();
    void saveState();
    void restoreState();

private:
    DocumentationPackage m_package;
    QProgressBar* m_pProgressBar;
    QLabel* m_pTitle;
    QString m_currentRoot;
    QString m_currentLang;
    QString m_currentUrl;
    QString m_lastSearch;
    Mode m_webMode;
    Actions m_currentLanguageMode;
};