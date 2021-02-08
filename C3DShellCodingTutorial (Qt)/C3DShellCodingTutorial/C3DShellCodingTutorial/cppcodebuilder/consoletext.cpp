#include "consoletext.h"
#include <QFontDatabase>
#include <QTextBlock>

ConsoleText::ConsoleText(QWidget* parent)
    : QTextEdit(parent)
    , m_stdColor(Qt::black)
    , m_errColor(Qt::red)
    , m_warningColor(Qt::darkYellow)
    , m_completionColor(Qt::darkGreen)
{
    setReadOnly(true);
    int id = QFontDatabase::addApplicationFont(":/res/fonts/FiraCode-Retina.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    setFont(f);


    connect(this, &ConsoleText::cursorPositionChanged, [this]()
    {
        m_currentLine = textCursor().block().text();
    });
}

QColor ConsoleText::stdColor() const
{
    return m_stdColor;
}

void ConsoleText::setStdColor(QColor c)
{
    m_stdColor = c;
}

QColor ConsoleText::errColor() const
{
    return m_errColor;
}

void ConsoleText::setErrColor(QColor c)
{
    m_errColor = c;
}

QColor ConsoleText::warningColor() const
{
    return m_warningColor;
}

void ConsoleText::setWarningColor(QColor c)
{
    m_warningColor = c;
}

QColor ConsoleText::completionColor() const
{
    return m_completionColor;
}

void ConsoleText::setCompletionColor(QColor c)
{
    m_completionColor = c;
}

void ConsoleText::addText(const QString& result, const QColor& color)
{
    setTextColor(color);
    append(result);

    moveCursor(QTextCursor::End);
}

void ConsoleText::addText(const QString& result, ResultType type)
{
    QColor textColor;

    switch (type)
    {
    case ResultType::Error:
        textColor = m_errColor;
        break;
    case ResultType::Warning:
        textColor = m_warningColor;
        break;
    case ResultType::Complete:
        textColor = m_completionColor;
        break;
    case ResultType::Standart:
        Q_FALLTHROUGH();
    default:
        textColor = m_stdColor;
        break;
    }

    addText(result, textColor);
}

QSize ConsoleText::sizeHint() const
{
    return QSize({ parentWidget()->width(), parentWidget()->height() / 4});
}

void ConsoleText::mouseDoubleClickEvent(QMouseEvent* /*e*/)
{
    emit signalMoveToError(m_currentLine);
}

void ConsoleText::clear()
{
    QTextEdit::clear();
}