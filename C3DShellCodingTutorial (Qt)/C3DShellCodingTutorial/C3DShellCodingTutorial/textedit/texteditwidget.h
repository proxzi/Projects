#pragma once

#include <QWidget>
#include <QScopedPointer>

namespace Ui { class TextEditWidget; }

namespace ads { class CDockWidget; }

class TextEditor;
class QPushButton;
class FindTextWidget;

class TextEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget* parent = nullptr);
    ~TextEditWidget();

    void setDock(ads::CDockWidget* dock);
    QString dockTitle() const;
    void setDockTitle(const QString& title);
    QString dockObjectName() const;

    void setButtonDisplay(QPushButton* buttonDisplay);
    QPushButton* buttonDisplay();

    void setFindWidget(FindTextWidget* findWidget);
    FindTextWidget* findWidget();

    void setModified(bool val);
    bool isModified();
    
    void setText(const QString& text);
    QString text();

    void setSaved(bool save);
    bool isSaved();

    void setFilePath(const QString& filePath);
    QString filePath();

    bool find(const QString& findLine, bool wholeWord, bool caseSensitive,
        bool wrapAround, bool regexp, bool searchDirection);
    void replace(const QString& findLine, const QString& replaceLine,
        bool wholeWord, bool caseSensitive, bool regexp);
    void replaceAndFind(const QString& findLine, const QString& replaceLine,
        bool wholeWord, bool caseSensitive, bool regexp);
    void replaceAll(const QString& findLine, const QString& replaceLine,
        bool wholeWord, bool caseSensitive, bool regexp);

    void unselectErrors();
    void moveToError(int line, const QString& message);
    void errorsList(QVector<QPair<int, QString>>& errorsList);
signals:
    void signalEnter();
    void signalPress();
    void signalClear();
    void signalTextChanged();
    void signalSearchInDocumentation(const QString textDoc);
    void signalSearchInDocumentationNext(const QString textDoc);

public slots:
    void slotClear();

    void slotCurrentLineAndCol(int line, int col);

protected:
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* target, QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    //virtual QSize sizeHint() const;
    //virtual QSize minimumSizeHint() const;

private:
    QScopedPointer<Ui::TextEditWidget> ui;
    QPushButton* m_pDisplayButtom;
    FindTextWidget* m_pFindWidget;
    ads::CDockWidget* m_pDockWidget;
    //bool m_searchDirection;
    bool m_endSearch;
    bool m_bIsSaved;
    QString m_filePath;
};