#pragma once
#include <QWebEngineView>
#include <QStringList>

class WebPage;

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    explicit WebView(const QString& objectName, double zoomFactor = 1.0, QWidget *parent = nullptr);
    ~WebView();

    void setPage(WebPage *page);
    int loadProgress() const;
    bool isWebActionEnabled(QWebEnginePage::WebAction webAction) const;
    void addScripts(const QStringList& scripts);

    qreal zoomFactor() const;
    void setZoomFactor(qreal factor);

public slots:
    void slotRunJavaScript(const QString& code);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool eventFilter(QObject* target, QEvent* event) override;
    bool event(QEvent* event) override;
    void showEvent(QShowEvent* event) override;

signals:
    void webActionEnabledChanged(QWebEnginePage::WebAction webAction, bool enabled);
    void devToolsRequested(QWebEnginePage *source);

private:
    void createWebActionTrigger(QWebEnginePage *page, QWebEnginePage::WebAction);
    void saveState();
    void restoreState();
    double dpiRatioFactor() const;

private:
    int m_loadProgress;
    QStringList m_jsScripts;
    double m_zoomFactorBefore;
};
