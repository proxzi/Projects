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

    // ������ * ����������� � ��������, ���� ���� ���������
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

// ������� ������ � ������
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

// ���������� ����� �� ��������� ����
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

// ���������� ����� ������ � ������ � ���������� ����
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

// ���������� ����� � �������� ����
void TextEditWidget::setText(const QString& text)
{
    ui->textEdit->setText(text);
}
//-----------------------------------------------------------------------------

// ������� ������ �����
bool TextEditWidget::find(const QString& findLine, bool wholeWord, bool caseSensitive,
                              bool wrapAround, bool regexp, bool searchDirection)
{
	// ���������� ������� ���������� ��������� ������
    bool searchResult = false;

    // ������� ��������� �������
    int line = 0, index = 0;
    ui->textEdit->getCursorPosition(&line, &index);

	// ��� ������ �����
    if (!searchDirection)
        --index;
	
	// ����� ������� ������ �����
    searchResult = ui->textEdit->findFirst(findLine, regexp, caseSensitive, wholeWord, wrapAround,
                                           searchDirection, line, index, true, false);
	// ������� �����
    if (searchResult)
    {
        findWidget()->infoSearchAndReplace(-1, false);
        m_endSearch = true;
    }
	// ����� ��������
    else if (!searchResult && m_endSearch)
    {
        findWidget()->infoSearchAndReplace(0, false);
        m_endSearch = false;
    }
	// ����� �� �������
    else if (!searchResult && !m_endSearch)
        findWidget()->infoSearchAndReplace(-2, false);

    return searchResult;
}
//-----------------------------------------------------------------------------

// ��������
void TextEditWidget::replace(const QString& findLine, const QString& replaceLine, 
                                 bool wholeWord, bool caseSensitive, bool /*regexp*/)
{
	// ����������� �� ������ ������ �� ������� ������
    if (findLine != replaceLine)
    {
		//��������� ������� �������
        int line = 0, index = 0;
        ui->textEdit->getCursorPosition(&line, &index);

        bool checkReplaceResult = false; 
        //������ � ������ �� ����� ����� � ������� 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && wholeWord && caseSensitive && ui->textEdit->wordAtLineIndex(line, index) == findLine);
        //������ ��� ������
        checkReplaceResult |= (ui->textEdit->selectedText().toLower() == findLine.toLower() && !wholeWord && !caseSensitive);
        //������ � ������ �� ����� �����
        checkReplaceResult |= (ui->textEdit->wordAtLineIndex(line, index).toLower() == findLine.toLower() && ui->textEdit->selectedText() == findLine && wholeWord);
        //������ � ������ �� ������� 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && caseSensitive && !wholeWord);

        // ���� ������ 
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

// �������� � ����� ��������� �����
void TextEditWidget::replaceAndFind(const QString& findLine, const QString& replaceLine, bool wholeWord, bool caseSensitive, bool regexp)
{
    if (findLine != replaceLine)
    {
        int line = 0, index = 0;
        ui->textEdit->getCursorPosition(&line, &index);

        bool checkReplaceResult = false;
        //������ � ������ �� ����� ����� � ������� 
        checkReplaceResult |= (ui->textEdit->selectedText() == findLine && wholeWord && caseSensitive && ui->textEdit->wordAtLineIndex(line, index) == findLine);
        //������ ��� ������
        checkReplaceResult |= (ui->textEdit->selectedText().toLower() == findLine.toLower() && !wholeWord && !caseSensitive);
        //������ � ������ �� ����� �����
        checkReplaceResult |= (ui->textEdit->wordAtLineIndex(line, index).toLower() == findLine.toLower() && ui->textEdit->selectedText() == findLine && wholeWord);
        //������ � ������ �� ������� 
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

// �������� ��� �����
void TextEditWidget::replaceAll(const QString& findLine, const QString& replaceLine,
                                    bool wholeWord, bool caseSensitive, bool regexp)
{
    
    // ����������� ��������� �� ������ ������ � ������� ������  
// � �� ����� �� ������ ������
    if (findLine != replaceLine && !replaceLine.isEmpty())
	    // ���������� ����� �����
        if(find(findLine, wholeWord, caseSensitive, true, regexp, true))
        {
            // ������ ������� ������
            int lineStart, indexStart;
            ui->textEdit->getCursorPosition(&lineStart, &indexStart);
            // �������, ������� ���� ���� ��������
            int countWordsToReplace = 0;

            // ����� ���������� �����
            while(find(findLine, wholeWord, caseSensitive, true, regexp, true))
            {
                // �������� ���������
                int line = 0, index = 0;
                
                // ���� ����� �� ����� �� ������
                while (line != lineStart && index != indexStart)
                {
                    ui->textEdit->getCursorPosition(&line, &index);
                    ui->textEdit->replaceSelectedText(replaceLine);
                    ++countWordsToReplace;
                }
                //����� �����, ���� ������ �� ������
                if (line == lineStart && index == indexStart)
                    break;
            }
            // ���������, ������� ���� ���� ��������
            findWidget()->infoSearchAndReplace(countWordsToReplace, true);
            return;
        }
    findWidget()->infoSearchAndReplace(0, true);
}
//-----------------------------------------------------------------------------

// ����� ����� � ������������
void TextEditWidget::keyPressEvent(QKeyEvent* event) 
{
    int key = event->key();

    // ������� F1
    if (key == Qt::Key_F1)
    {
        QString textDoc;

        int line = 0, index = 0;

        // ���������� �����
        if (ui->textEdit->hasSelectedText())
            textDoc = ui->textEdit->selectedText();
        // �����, ��� ��������� ������
        else
        {
            ui->textEdit->getCursorPosition(&line, &index);
            textDoc = ui->textEdit->wordAtLineIndex(line, index);
        }
        // ����� ������� ��� �������� ����� ��� ������ � ������������
        emit signalSearchInDocumentation(textDoc);
    }
}
//-----------------------------------------------------------------------------

void TextEditWidget::unselectErrors()
{
    // ������ ��������� ���� ������
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
    // ������ ������ 
    for (auto item : errorsList)
    {
        ui->textEdit->markerAdd(item.first - 1, 0);
    }
}
