#pragma once

#include <QString>
#include <QWebEngineProfile>
#include "webviewwidget.h"
#include "tutorialpackage.h"

class TutorialWidget : public WebViewWidget
{
    Q_OBJECT

public:
    explicit TutorialWidget(const QString& title, QWebEngineProfile* profile = QWebEngineProfile::defaultProfile(), double zoomFactor = 1.0, QWidget* parent = nullptr);

signals:
    void signalSearchInDoc(const QString& text);
    void signalCodeBlockForCurrentEdit(const QString& id);
    void signalCodeBlockForNewEdit(const QString& id);

public slots:
    void slotReceiveSource(const QString& filePath, const QString& tutorialPath);
private:
    QString m_filePath;
    QString m_content;
    TutorialPackage m_package;

};