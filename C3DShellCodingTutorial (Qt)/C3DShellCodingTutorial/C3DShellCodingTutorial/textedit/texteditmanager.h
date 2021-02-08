#pragma once
#include <QObject>

namespace ads
{
    class CDockManager;
    class CDockAreaWidget;
    class CDockContainerWidget;
    class CDockWidget;
};

class QToolBar;
class QMenu;
class QListWidget;
class QPushButton;
class QFile;

class TextEditWidget;
class FindTextWidget;
class TextEditor;

class TextEditManager : public QObject
{
    Q_OBJECT
public:
    explicit TextEditManager(QObject* parent, ads::CDockManager* dockManager);

    bool closeAllEditors();
    void textEditorsToggleView(bool open);

    TextEditWidget* activeTextEdit();
    ads::CDockWidget* oneDock();
    void toggleView(bool open);


signals:
    void sendCode(const QString& code, const QString& editorName);
    void signalSendButtonDisplay(QPushButton* buttonDisplay);
    void signalSendFindWidget(FindTextWidget* findWidget);
    void signalSearchInDocumentation(const QString textDoc);
    void actionsEnabled(bool enable);

public slots:
    bool saveAs();
    bool save();
    bool openFiles();
    bool saveFile(const QString& filePath, const QString& source);

    void enableButtonDisplay();
    void disableButtonDisplay();

    void slotShowFindWidget();

    void slotNewEditorByFilePath(const QString& filePath);
    void slotNewEditorBySource(const QString& source);
    void slotCurrentEditorBySource(const QString& source);
    void slotMoveToError(const QString& textEditName, int line, const QString& message);
    void slotErrorsList(const QString& textEditName, QVector<QPair<int, QString>>& errorsList);

protected:
    bool event(QEvent* event) override;
    
    //bool eventFilter(QObject* target, QEvent* event) override;

private slots:
    void slotDisplayCode();
    void slotEditorCloseRequested();
    void slotPress();
    void slotEnter();

    void slotViewToggled(bool Open);
    void slotViewVisibilityChanged(bool Visible);
      
    void slotTextIsChanged();

    void slotFind(const QString& findLine, bool wholeWord, bool caseSensitive,
                  bool wrapAround, bool regexp, bool searchDirection);
    void slotReplace(const QString& findLine, const QString& replaceLine,
                     bool wholeWord, bool caseSensitive, bool regexp);
    void slotReplaceAndFind(const QString& findLine, const QString& replaceLine,
                            bool wholeWord, bool caseSensitive, bool regexp);
    void slotReplaceAll(const QString& findLine, const QString& replaceLine,
                        bool wholeWord, bool caseSensitive, bool regexp);

private:

    bool readyToClosed(TextEditWidget * editorWidget);
    TextEditWidget* createNewEditor(const QString& title, const QString& source);
    QString strippedName(const QFile& filePath);
    void getFindAndButton(TextEditWidget* editor);

private:
    int m_textEditCount = 0;
    TextEditWidget* m_pActiveTextEdit = nullptr;
    ads::CDockWidget* m_pActiveDock = nullptr;
    QString m_currentWorkFolderPath = "";
    ads::CDockManager* m_pDockManager = nullptr;
    QPushButton* m_pButtonDisplay;
    FindTextWidget* m_pFindTextWidget;
};
