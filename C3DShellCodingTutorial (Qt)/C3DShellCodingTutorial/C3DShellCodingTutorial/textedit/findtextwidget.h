#pragma once
#include <QWidget>
#include <QScopedPointer>

namespace Ui { class FindTextWidget; }

class FindTextWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FindTextWidget(QWidget* parent = nullptr);
    ~FindTextWidget() override;

    void infoSearchAndReplace(int wordCount, bool replace);

private:
    QScopedPointer<Ui::FindTextWidget> ui;

    bool searchDirection;

protected:
    void changeEvent(QEvent* event) override;

signals:
    void clickForFind(const QString& findLine, bool wholeWord, bool caseSensitive,
                      bool wrapAround, bool regexp, bool searchDirection);
    void clickForReplace(const QString& findLine, const QString& replaceLine,
                         bool wholeWord, bool caseSensitive, bool regexp);
    void clickForReplaceAndFind(const QString& findLine, const QString& replaceLine, 
                                bool wholeWord, bool caseSensitive, bool regexp);
    void clickForReplaceAll(const QString& findLine, const QString& replaceLine,
                            bool wholeWord, bool caseSensitive, bool regexp);

public slots:
    void slotFindText();
    void slotCheckTextForFind();
};
