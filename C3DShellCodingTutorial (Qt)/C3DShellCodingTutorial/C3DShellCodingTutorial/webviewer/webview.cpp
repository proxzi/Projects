#include <QContextMenuEvent>
#include <QApplication>
#include <QDebug>
#include <QMenu>
#include <QSettings>
#include <QMessageBox>
#include <QTimer>
#include <QIcon>
#include <QWebEngineScriptCollection>

#include "webpage.h"
#include "webview.h"
#include "storagelocation.h"

#include "globaldef.h"

WebView::WebView(const QString& objectName_, double zoomFactor_, QWidget* parent)
    : QWebEngineView(parent)
    , m_loadProgress(100)
    , m_jsScripts()
    , m_zoomFactorBefore(zoomFactor_)
{
    setObjectName(objectName_);

    connect(this, &QWebEngineView::loadStarted, [this]() {

        m_loadProgress = 0;
        });
    connect(this, &QWebEngineView::loadProgress, [this](int progress) {
        m_loadProgress = progress;

        });
    connect(this, &QWebEngineView::loadFinished, [this](bool success) {
        m_loadProgress = success ? 100 : -1;

        if (success == true)
        {
            setZoomFactor(m_zoomFactorBefore);
            for (const auto& script : m_jsScripts)
            {
                page()->runJavaScript(script);
            }
        }
        });

    connect(this, &QWebEngineView::renderProcessTerminated,
        [this](QWebEnginePage::RenderProcessTerminationStatus termStatus,
            int statusCode)
        {
            QString status;
            switch (termStatus)
            {
            case QWebEnginePage::NormalTerminationStatus:
                status = ("Render process normal exit");
                break;
            case QWebEnginePage::AbnormalTerminationStatus:
                status = ("Render process abnormal exit");
                break;
            case QWebEnginePage::CrashedTerminationStatus:
                status = ("Render process crashed");
                break;
            case QWebEnginePage::KilledTerminationStatus:
                status = ("Render process killed");
                break;
            }
            QMessageBox::StandardButton btn = QMessageBox::question(window(), status,
            QString("Render process exited with code: %1\n"
                    "Do you want to reload the page ?").arg(statusCode));
            if (btn == QMessageBox::Yes)
            {
                QTimer::singleShot(0, [this]
                    {
                        reload();
                    });
            }
        });

    restoreState();
    QApplication::instance()->installEventFilter(this);
    setMouseTracking(true);
}
//-----------------------------------------------------------------------------
// 
// ---
WebView::~WebView()
{
    saveState();
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::setPage(WebPage* page)
{
    createWebActionTrigger(page, QWebEnginePage::Forward);
    createWebActionTrigger(page, QWebEnginePage::Back);
    createWebActionTrigger(page, QWebEnginePage::Reload);
    createWebActionTrigger(page, QWebEnginePage::Stop);
    QWebEngineView::setPage(page);
}
//-----------------------------------------------------------------------------
// 
// ---
int WebView::loadProgress() const
{
    return m_loadProgress;
}
//-----------------------------------------------------------------------------
// 
// ---
bool WebView::isWebActionEnabled(QWebEnginePage::WebAction webAction) const
{
    return page()->action(webAction)->isEnabled();
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::addScripts(const QStringList& scripts)
{
    QFile file;
    auto readJsFile = [&file](const QString& fileName)
    {
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        QString res = file.readAll();
        file.close();
        return res;
    };

    for (auto& scriptName : scripts)
    {
        m_jsScripts.append(readJsFile(scriptName));
    }
}
//-----------------------------------------------------------------------------
// 
// ---
qreal WebView::zoomFactor() const
{
    return QWebEngineView::zoomFactor() / dpiRatioFactor();
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::setZoomFactor(qreal factor)
{
    QWebEngineView::setZoomFactor(factor * dpiRatioFactor());
    m_zoomFactorBefore = factor;
}
//-----------------------------------------------------------------------------
// 
// ---
bool WebView::eventFilter(QObject* target, QEvent* event)
{
    if (target->parent() == this) 
    {

        if (event->type() == QEvent::MouseButtonPress)
        {
            auto mouseButtonPress(static_cast<QMouseEvent*>(event));
            if (mouseButtonPress->buttons() == Qt::ForwardButton)
            {
                forward();
                return true;
            }
            else if (mouseButtonPress->buttons() == Qt::BackButton)
            {
                back();
                return true;
            }
        }
        else if (event->type() == QEvent::Wheel)
        {
            auto mouseWheel(static_cast<QWheelEvent*>(event));
            if (mouseWheel->modifiers() == Qt::CTRL && mouseWheel->delta() > 0)
            {
                setZoomFactor(m_zoomFactorBefore + 0.15);
            }
            else if (mouseWheel->modifiers() == Qt::CTRL && mouseWheel->delta() < 0)
            {
                setZoomFactor(m_zoomFactorBefore - 0.15);
            }
        }
    }
    //else if (target == this)
    //{
    //    if (event->type() == QEvent::Close)
    //    {
    //        qDebug() << event;
    //        saveState();
    //    }
    //}
    return false;
}
//-----------------------------------------------------------------------------
// 
// ---
bool WebView::event(QEvent* event)
{
    return QWebEngineView::event(event);
}

void WebView::showEvent(QShowEvent* event)
{
    QWebEngineView::setZoomFactor(m_zoomFactorBefore * dpiRatioFactor());
    QWebEngineView::showEvent(event);
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::createWebActionTrigger(QWebEnginePage* page,
    QWebEnginePage::WebAction webAction)
{
    QAction* action = page->action(webAction);
    connect(action, &QAction::changed, [this, action, webAction]
        {
            emit webActionEnabledChanged(webAction, action->isEnabled());
        });
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::saveState()
{
    APP.saveCommonSettings(QString("webView%1/zoomFactor").arg(objectName()), zoomFactor());
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::restoreState()
{
    m_zoomFactorBefore = APP.restoreCommonSettings(QString("webView%1/zoomFactor").arg(objectName()), m_zoomFactorBefore).toReal();
    setZoomFactor(m_zoomFactorBefore);
}
double WebView::dpiRatioFactor() const
{
    double ratio = 1.0;

    switch (logicalDpiX())
    {
    case 96:
        ratio = 1.0;
        break;
    case 120:
        ratio = 1.25;
        break;
    case 144:
        ratio = 1.5;
        break;
    case 192:
        ratio = 2.0;
        break;
    case 240:
        ratio = 2.5;
        break;
    case 288:
        ratio = 3.0;
        break;
    case 384:
        ratio = 4.0;
        break;
    default:
        ratio = 1.0;
        break;
    }

    return ratio;
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu* menu = page()->createStandardContextMenu();

    menu->removeAction(page()->action(QWebEnginePage::ViewSource));
    menu->removeAction(page()->action(QWebEnginePage::SavePage));
    menu->removeAction(page()->action(QWebEnginePage::Unselect));

#ifdef _DEBUG
    QAction* action = new QAction(menu);
    action->setText("Open DevTools");
    connect(action, &QAction::triggered, [this]()
        { 
            emit devToolsRequested(page()); 
        });
    menu->addAction(action);
#endif
    menu->popup(event->globalPos());
}
//-----------------------------------------------------------------------------
// 
// ---
void WebView::slotRunJavaScript(const QString& code)
{
    page()->runJavaScript(code, [this](const QVariant& answer)
        {
            qDebug() << answer.toString();
        });
}
