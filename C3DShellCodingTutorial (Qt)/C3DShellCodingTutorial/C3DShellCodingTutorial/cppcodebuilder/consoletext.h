#pragma once

#include <QTextEdit>
#include <QDebug>

class ConsoleText : public QTextEdit
{
    Q_OBJECT

public:

    ConsoleText(QWidget* parent = nullptr);

    QColor stdColor() const;
    void setStdColor(QColor c);
    QColor errColor() const;
    void setErrColor(QColor c);
    QColor warningColor() const;
    void setWarningColor(QColor c);
    QColor completionColor() const;
    void setCompletionColor(QColor c);

    enum class ResultType {Standart, Error, Warning, Complete};

signals:
    void signalMoveToError(const QString& strLine);

protected:
    QSize sizeHint() const override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    QColor m_stdColor, m_errColor, m_warningColor, m_completionColor;
    QString m_currentLine;
    
public slots:
    void addText(const QString& result, ResultType t = ResultType::Standart);
    void addText(const QString& result, const QColor& color);
    void clear();
};
