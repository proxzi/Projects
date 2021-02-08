#include <QDebug>
#include <QInputMethodQueryEvent>
#include <QPushButton>

#include <DockWidget.h>


#include "ui_texteditwidget.h"
#include "texteditwidget.h"

#include "findtextwidget.h"

//-----------------------------------------------------------------------------

// ---
TextEditWidget::TextEditWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TextEditWidget)
    , m_pDisplayButtom(nullptr)
    , m_pFindWidget(nullptr)
    , m_pDockWidget(nullptr)
    , m_bIsSaved(false)
{
    ui->setupUi(this);

    connect(this, &TextEditWidget::signalClear, ui->textEdit, &TextEditor::clear);

    connect(ui->textEdit, &TextEditor::cursorPositionChanged, this, &TextEditWidget::slotCurrentLineAndCol);

    // Символ * добавляется в название, если файл изменился
    connect(ui->textEdit, &QsciScintilla::textChanged, [this] ()
    {
        setSaved(false);
        emit signalTextChanged();
    });

    ui->textEdit->installEventFilter(this);

    m_endSearch = false;
}
//-----------------------------------------------------------------------------

TextEditWidget::~TextEditWidget()
{
}

// ---
void TextEditWidget::setDock(ads::CDockWidget* dock)
{
    m_pDockWidget = dock;
}
//-----------------------------------------------------------------------------

// ---
QString TextEditWidget::dockTitle() const
{
    return m_pDockWidget->windowTitle();
}
//-----------------------------------------------------------------------------

// ---
void TextEditWidget::setDockTitle(const QString& title)
{
    m_pDockWidget->setWindowTitle(title);
}
//-----------------------------------------------------------------------------

// ---
QString TextEditWidget::dockObjectName() const
{
    return m_pDockWidget->objectName();
}

// Текущая строка и индекс
void TextEditWidget::slotCurrentLineAndCol(int line, int col)
{
    QString las = QString(tr("Line: %1, Col: %2").arg(line+1).arg(col+1));
    ui->labelLineAndSymbol->setText(las);
}
//-----------------------------------------------------------------------------

// ---
bool TextEditWidget::eventFilter(QObject* target, QEvent* event)
{
    if (target == ui->textEdit) {

        if (event->type() == QEvent::InputMethodQuery)
        {
            emit signalPress();
        }
        else if (event->type() == QEvent::Enter)
        {
            emit signalEnter();
        }
    }
    return false;
}
//-----------------------------------------------------------------------------

// ---
void TextEditWidget::closeEvent(QCloseEvent* event)
{
    if (m_pDisplayButtom != nullptr) m_pDisplayButtom->setParent(nullptr);
    if (m_pFindWidget != nullptr) m_pFindWidget->setParent(nullptr);
    QWidget::closeEvent(event);
}

//QSize TextEditWidget::sizeHint() const
//{
//    return QSize();
//}
//
//QSize TextEditWidget::minimumSizeHint() const
//{
//    return QSize();
//}
//-----------------------------------------------------------------------------

// ---
void TextEditWidget::slotClear()
{
    emit signalClear();
}
//-----------------------------------------------------------------------------

// Возвращает текст из редактора кода
QString TextEditWidget::text()
{
    return ui->textEdit->text();
}

void TextEditWidget::setSaved(bool save)
{
    m_bIsSaved = save;
}

bool TextEditWidget::isSaved()
{
    return m_bIsSaved;
}

void TextEditWidget::setFilePath(const QString& filePath)
{
    m_filePath = filePath;
}

QString TextEditWidget::filePath()
{
    return m_filePath;
}
//-----------------------------------------------------------------------------

// ---
void TextEditWidget::setButtonDisplay(QPushButton* buttonDisplay)
{
    if (buttonDisplay == nullptr) return;
    m_pDisplayButtom = buttonDisplay;
    layout()->addWidget(m_pDisplayButtom);
}
//-----------------------------------------------------------------------------

// Добавление формы поиска в виджет с редактором кода
void TextEditWidget::setFindWidget(FindTextWidget* findWidget)
{
    if (findWidget == nullptr) return;
    m_pFindWidget = findWidget;
    ui->layoutMain->addWidget(m_pFindWidget);
}
//-----------------------------------------------------------------------------

// ---
QPushButton* TextEditWidget::buttonDisplay()
{
    return m_pDisplayButtom;
}
//-----------------------------------------------------------------------------

// ---
FindTextWidget* TextEditWidget::findWidget()
{
    return m_pFindWidget;
}
//-----------------------------------------------------------------------------

// ---
void TextEditWidget::setModified(bool val)
{
    ui->textEdit->setModified(val);
}

bool TextEditWidget::isModified()
{
    return ui->textEdit->isModified();
}
//-----------------------------------------------------------------------------

// Установить текст в редактор кода
void TextEditWidget::setText(const QString& text)
{
    ui->textEdit->setText(text);
}
//-----------------------------------------------------------------------------

// Функция поиска слова
bool TextEditWidget::find(const QString& findLine, bool wholeWord, bool caseSensitive,
                              bool wrapAround, bool regexp, bool searchDirection)
{
	// Переменная которая возвращает результат поиска
    bool searchResult = false;

    // Текущие положение курсора
    int line = 0, index = 0;
    ui->textEdit->getCursorPosition(&line, &index);

	// Для поиска назад
    if (!searchDirection)
        --index;
	
	// Вызов функции поиска слова
    searchResult = ui->textEdit->findFirst(findLine, regexp, caseSensitive, wholeWord, wrapAround,
                                           searchDirection, line, index, true, false);
	// Удачный поиск
    if (searchResult)
    {
        findWidget()->infoSearchAndReplace(-1, false);
        m_endSearch = true;
    }
	// Поиск закончен
    else if (!searchResult && m_endSearch)
    {
        findWidget()->infoSearchAndReplace(0, false);
        m_endSearch = false;
    }
	// Слово не найдено
    else if (!searchResult && !m_endSearch)
        findWidget()->infoSearchAndReplace(-2, false);

    return searchResult;
}
//-----------------------------------------------------------------------------

// Заменить
void TextEditWidget::replace(const QString& findLine, const QString& replaceLine, 
                                 bool wholeWord, bool caseSensitive, bool /*regexp*/)
{
	// Проверяется ли строка поиска со строкой замены
    if (findLine != replaceLine)
    {
		//Получение позиции курсора
        int line = 0, index = 0;
        ui->textEdit->getCursorPosition(&line, &index);

        bool checkReplaceResult = false; 
        //Замена с флагом на целое слово и регистр 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && wholeWord && caseSensitive && ui->textEdit->wordAtLineIndex(line, index) == findLine);
        //Замена без флагов
        checkReplaceResult |= (ui->textEdit->selectedText().toLower() == findLine.toLower() && !wholeWord && !caseSensitive);
        //Замена с флагом на целое слово
        checkReplaceResult |= (ui->textEdit->wordAtLineIndex(line, index).toLower() == findLine.toLower() && ui->textEdit->selectedText() == findLine && wholeWord);
        //Замена с флагом на регистр 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && caseSensitive && !wholeWord);

        // Если замена 
        if (checkReplaceResult)
        {
            ui->textEdit->replaceSelectedText(replaceLine);
            findWidget()->infoSearchAndReplace(-1, true);
        }
        else
        {
            findWidget()->infoSearchAndReplace(0, true);
        }
    }
}
//-----------------------------------------------------------------------------

// Заменить и найти следующее слово
void TextEditWidget::replaceAndFind(const QString& findLine, const QString& replaceLine, bool wholeWord, bool caseSensitive, bool regexp)
{
    if (findLine != replaceLine)
    {
        int line = 0, index = 0;
        ui->textEdit->getCursorPosition(&line, &index);

        bool checkReplaceResult = false;
        //Замена с флагом на целое слово и регистр 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && wholeWord && caseSensitive && ui->textEdit->wordAtLineIndex(line, index) == findLine);
        //Замена без флагов
        checkReplaceResult |= (ui->textEdit->selectedText().toLower() == findLine.toLower() && !wholeWord && !caseSensitive);
        //Замена с флагом на целое слово
        checkReplaceResult |= (ui->textEdit->wordAtLineIndex(line, index).toLower() == findLine.toLower() && ui->textEdit->selectedText() == findLine && wholeWord);
        //Замена с флагом на регистр 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && caseSensitive && !wholeWord);

        if (checkReplaceResult)
            ui->textEdit->replaceSelectedText(replaceLine);
    
        if (find(findLine, wholeWord, caseSensitive, true, regexp, true))
        {
            findWidget()->infoSearchAndReplace(-1, true);
            return;
        }
        findWidget()->infoSearchAndReplace(-2, true);
    }
    
}
//-----------------------------------------------------------------------------

// Заменить все слова
void TextEditWidget::replaceAll(const QString& findLine, const QString& replaceLine,
                                    bool wholeWord, bool caseSensitive, bool regexp)
{
    
    // Проверяется совпадает ли строка поиска с строкой замены  
// и не пуста ли строка замены
    if (findLine != replaceLine && !replaceLine.isEmpty())
	    // Проводится поиск слова
        if(find(findLine, wholeWord, caseSensitive, true, regexp, true))
        {
            // Начало позиции замены
            int lineStart, indexStart;
            ui->textEdit->getCursorPosition(&lineStart, &indexStart);
            // Счетчик, сколько слов было изменено
            int countWordsToReplace = 0;

            // Поиск следующего слова
            while(find(findLine, wholeWord, caseSensitive, true, regexp, true))
            {
                // Текущиее положение
                int line = 0, index = 0;
                
                // Пока поиск не дошел до начала
                while (line != lineStart && index != indexStart)
                {
                    ui->textEdit->getCursorPosition(&line, &index);
                    ui->textEdit->replaceSelectedText(replaceLine);
                    ++countWordsToReplace;
                }
                //Конец цикла, если дойдет до начала
                if (line == lineStart && index == indexStart)
                    break;
            }
            // Сообщение, сколько слов было изменено
            findWidget()->infoSearchAndReplace(countWordsToReplace, true);
            return;
        }
    findWidget()->infoSearchAndReplace(0, true);
}
//-----------------------------------------------------------------------------

// Поиск слова в документации
void TextEditWidget::keyPressEvent(QKeyEvent* event) 
{
    int key = event->key();

    // Клавиша F1
    if (key == Qt::Key_F1)
    {
        QString textDoc;

        int line = 0, index = 0;

        // Выделенное слово
        if (ui->textEdit->hasSelectedText())
            textDoc = ui->textEdit->selectedText();
        // Слово, где находится курсор
        else
        {
            ui->textEdit->getCursorPosition(&line, &index);
            textDoc = ui->textEdit->wordAtLineIndex(line, index);
        }
        // Вызов сигнала для передачи слова для поиска в документации
        emit signalSearchInDocumentation(textDoc);
    }
}
//-----------------------------------------------------------------------------

void TextEditWidget::unselectErrors()
{
    // Убрать выделение всех ошибок
    ui->textEdit->markerDeleteAll();
}

void TextEditWidget::moveToError(int line, const QString&)
{
    ui->textEdit->setCursorPosition(line - 1, 0);
    ui->textEdit->setFocus(Qt::FocusReason::ActiveWindowFocusReason);
}

void TextEditWidget::errorsList(QVector<QPair<int, QString>>& errorsList)
{
    ui->textEdit->markerDefine(QsciScintilla::Circle, 0);
    // Массив ошибок 
    for (auto item : errorsList)
    {
        ui->textEdit->markerAdd(item.first - 1, 0);
    }
}
