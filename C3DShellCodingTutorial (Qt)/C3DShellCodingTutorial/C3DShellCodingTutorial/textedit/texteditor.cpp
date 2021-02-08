#include <QMessageBox>
#include <QtWidgets>
#include <QApplication>
#include <QMessageBox>

#include "storagelocation.h"
#include "globaldef.h"
#include "texteditor.h"
#include "lexercxx.h"

#include "Qsci/qsciapis.h"

TextEditor::TextEditor(QWidget* parent) : QsciScintilla(parent)
{
    setUtf8(true); // Кириллица
    m_pLexerCxx = new LexerCxx(this);
    setLexer(m_pLexerCxx); // Лексер

    // Объект для автодополнения
    api = new QsciAPIs(m_pLexerCxx);
    
    // Блоки скрытия
    setFolding(QsciScintilla::CircledTreeFoldStyle, 2);

    // Текущая строка кода и ее подсветка
    setCaretLineVisible(true);
    setCaretLineBackgroundColor(QColor("gainsboro"));

    // Выравниевание(отступ 4 пробела)
    setAutoIndent(true);
    setIndentationWidth(4);

    // Показывает отступ в 4 пробела
    setIndentationGuides(true);

    // Полоска слева, на которой располагается нумерация строк
    setMarginsBackgroundColor(QColor("gainsboro"));
    setMarginType(1, QsciScintilla::NumberMargin);
    setMarginWidth(1, "0000");

    // Метки
    setMarginType(0, QsciScintilla::SymbolMargin);
    setMarginWidth(0, "00");
    SendScintilla(QsciScintilla::SCI_MARKERSETFORE, 0, QColor("black"));
    SendScintilla(QsciScintilla::SCI_MARKERSETBACK, 0, QColor("red"));
    setMarginMarkerMask(0, 0b10000);

    // Отображение вертикальной линии на 80 символе
    setEdgeMode(QsciScintilla::EdgeLine);
    setEdgeColumn(80);

    // Режим обертывания
    setWrapMode(QsciScintilla::WrapWord);

    // Подсветка соответствий скобок
    setBraceMatching(QsciScintilla::SloppyBraceMatch);
    // Функция для цвета скобок соответствия
    setBraceColor(QColor("yellow"), QColor("blue"),
                  QColor("orange"), QColor("red"));

    // Автодополнение
    // Автодополнение из всех источников
    setAutoCompletionSource(QsciScintilla::AcsAPIs);
    // Удаляется слово и пишется выбранное слово
    setAutoCompletionReplaceWord(true);
    // Если слово одно в списке автодополнения, оно сразу дополнится
    setAutoCompletionUseSingle(QsciScintilla::AcusAlways);

    // Убрать подсветку со всех слов
    connect(this, &QsciScintilla::textChanged,
        [this]()
    {
        SendScintilla(QsciScintilla::SCI_INDICATORCLEARRANGE, 0, text().length());
    });

    // Добавление классов из заголовочных файлов ядра c3d
    connect(this, &QsciScintilla::textChanged,
        this, &TextEditor::slotSearchIncludes);

    // Выделение текущего слова
    connect(this, &QsciScintilla::cursorPositionChanged,
        this, &TextEditor::slotHighlighCurrentWord);

    // Заменяет таб на пробелы
    SendScintilla(SCI_SETUSETABS, false);

    // Добавление изображений для списка автодополнения
    auto autoCmplCxx = QPixmap(":/res/iconsAutoComplete/c++.png");
    auto autoCmplClass = QPixmap(":/res/iconsAutoComplete/class.png");
    auto autoCmplEnum = QPixmap(":/res/iconsAutoComplete/enum.png");
    auto autoCmplFunction = QPixmap(":/res/iconsAutoComplete/function.png");
    auto autoCmplPreprocessor = QPixmap(":/res/iconsAutoComplete/preprocessor.png");
    auto autoCmplVariable = QPixmap(":/res/iconsAutoComplete/variable.png");
    auto autoCmplNamespace = QPixmap(":/res/iconsAutoComplete/namespace.png");
    auto autoCmplsubClass = QPixmap(":/res/iconsAutoComplete/subClass.png");
    registerImage(1, autoCmplCxx);
    registerImage(2, autoCmplClass);
    registerImage(3, autoCmplEnum);
    registerImage(4, autoCmplFunction);
    registerImage(5, autoCmplPreprocessor);
    registerImage(6, autoCmplVariable);
    registerImage(7, autoCmplNamespace);
    registerImage(8, autoCmplsubClass);

    QString cxxWords = m_pLexerCxx->keywords(1);
    for (QString cxx : cxxWords.split(" "))
        m_keyWordsCxx.append(cxx);
}

TextEditor::~TextEditor()
{
    if (api != nullptr)
        delete api;
}

void TextEditor::setBraceColor(const QColor& mb, const QColor& mf,
    const QColor& ub, const QColor& uf)
{
    // Цвет для скобок у которых есть пара
    setMatchedBraceBackgroundColor(mb);
    setMatchedBraceForegroundColor(mf);
    // Цвет для скобок у которых нет пары
    setUnmatchedBraceBackgroundColor(ub);
    setUnmatchedBraceForegroundColor(uf);
}

void TextEditor::keyPressEvent(QKeyEvent* e)
{
    if ((e->modifiers() == Qt::CTRL) && (e->key() == Qt::Key_Space)) { // Ctrl+<Space>
        setAutoCompletionUseSingle(QsciScintilla::AcusAlways);
        autoCompleteFromAPIs();

        return;
    }

    QsciScintilla::keyPressEvent(e);
}

// Подсветка текущего слова
void TextEditor::slotHighlighCurrentWord(int line, int index)
{
    // Метод убирает подсветку с прошлого слова
    clearHighlighWord();

    // Весь текст с редактора
    QString document(text());

    // Регулярное выражение - выделенное слово
    QRegExp selectedCurText(selectedText());

    // Слово где находится курсор
    m_currentWord = wordAtLineIndex(line, index);

    CommentPosition comment;

    QRegularExpression regExpLineCommentPattern("\\/\\/.*?\\n", QRegularExpression::PatternOption::MultilineOption);
    QRegularExpression regExpBlockCommentsPattern("\\/\\*[\\s\\S]*?\\*\\/", QRegularExpression::PatternOption::MultilineOption);

    QRegularExpressionMatchIterator  iRegitComment = regExpLineCommentPattern.globalMatch(document);

    // Строчные комментарии
    while (iRegitComment.hasNext())
    {
        QRegularExpressionMatch matchComment = iRegitComment.next();
        int firstSymbCommentPos = document.toUtf8().indexOf(matchComment.captured().toUtf8());
        int lastSymbCommentPos = matchComment.captured().toUtf8().length() + document.toUtf8().indexOf(matchComment.captured().toUtf8());
        comment.m_positionsCommentStart.append(firstSymbCommentPos);
        comment.m_positionsCommentEnd.append(lastSymbCommentPos);
    }

    iRegitComment = regExpBlockCommentsPattern.globalMatch(document);

    // Блочные комментарии
    while (iRegitComment.hasNext())
    {
        QRegularExpressionMatch matchComment = iRegitComment.next();
        int firstSymbCommentPos = document.toUtf8().indexOf(matchComment.captured().toUtf8());
        int lastSymbCommentPos = matchComment.captured().toUtf8().length() + document.toUtf8().indexOf(matchComment.captured().toUtf8());
        comment.m_positionsCommentStart.append(firstSymbCommentPos);
        comment.m_positionsCommentEnd.append(lastSymbCommentPos);
    }

    bool cursorInComment = false;

    int currentPositionCursor = positionFromLineIndex(line, index); 

    for (int i = 0; i < comment.m_positionsCommentStart.length(); ++i)
        cursorInComment |= (comment.m_positionsCommentStart.at(i) < currentPositionCursor) && (comment.m_positionsCommentEnd.at(i) > currentPositionCursor);

    // Подсветка происходит у слов
    // если курсор стоит не в комментарии
    if (!cursorInComment)
        // Условие для подсветки слов
        if ((hasSelectedText() == (selectedText().toUtf8() == m_currentWord)) ||
            selectedCurText.exactMatch(wordAtLineIndex(line, index))
            && !m_currentWord.isEmpty())
        {
            // Позиция последнего слова для выделения
            int lastPositionCurrentWord = document.toUtf8().lastIndexOf(m_currentWord);

            // Если слово является ключевым словом языка C++
            // подсветка не выполнится
            QString cppWords = m_pLexerCxx->keywords(1);
            for (auto& count : cppWords.split(" "))
                if (m_currentWord == count || "#" + m_currentWord == count)
                {
                    return;
                }

            // Регулярное выражение, если это число
            // или слово начинается с цифры
            QRegExp isDigital("(\\d\\w+)|(\\d)");

            // Если регулярное выражение будет найдено
            // то подсветка не выполнится
            if (isDigital.exactMatch(m_currentWord))
                return;

            // Переменная которая хранит позицию слова
            int currentPosition = 0;

            while (currentPosition != lastPositionCurrentWord)
            {
                // Позиция слова в редакторе кода
                currentPosition = document.toUtf8().indexOf(m_currentWord, currentPosition + 1);

                // Получение новой линии и индекса позиции исходя из позиции слова
                lineIndexFromPosition(currentPosition, &line, &index);
                bool isComment = false;

                // Каждое слово, которое должно быть подсвечено проверяется находится ли оно в комментариях
                for (int i = 0; i < comment.m_positionsCommentStart.length(); ++i)
                    isComment |= (comment.m_positionsCommentStart.at(i) < currentPosition) && (comment.m_positionsCommentEnd.at(i) > currentPosition);

                if (!isComment)
                    if (m_currentWord == wordAtLineIndex(line, index))
                    {
                        // Длина для посветки слова
                        SendScintilla(QsciScintilla::SCI_INDICATORFILLRANGE,
                            currentPosition, m_currentWord.toUtf8().length());
                        // Обращение к сцинтилле для подсветки слова
                        SendScintilla(QsciScintilla::SCI_INDICSETSTYLE, 0, 7);
                        // Добавление позиции слова в массив, 
                        // для последующего удаления подсветки
                        m_positionsCurrentWord.append(currentPosition);
                    }
                    else {}
                else
                    continue;
            }

        }
}

// Убрать подсветку с прошлого слова
void TextEditor::clearHighlighWord()
{
    // Цикл обхода всех позиций и очистка подсветки
    for (int position : m_positionsCurrentWord)
        SendScintilla(QsciScintilla::SCI_INDICATORCLEARRANGE, position, m_currentWord.toUtf8().length());
    // Удаление всех элементов массива
    m_positionsCurrentWord.clear();
}

void TextEditor::slotSearchIncludes()
{
    QStringList tempIncludes;

    // Поиск заголовков в редакторе кода
    QRegularExpression regExpIncludesPattern("#include\\s+(?:(\"(.*?)\")|(<(.*?)>))");
    QRegularExpressionMatchIterator iRegInclude = regExpIncludesPattern.globalMatch(text());

    while (iRegInclude.hasNext())
    {
        QRegularExpressionMatch match = iRegInclude.next();
        QString include = !match.captured(2).isEmpty() ? match.captured(2) : match.captured(4);
        if (!tempIncludes.contains(include))
            tempIncludes.append(include);
    }

    // Добавление новых элементов в лексер и автокомплит
    if (tempIncludes != m_Includes)
    {
        m_Includes.clear();
        m_AllHeaders.clear();
        m_headers.clear();

        m_c3dTypesAutoCmpl.clear();
        m_c3dTypesHighlight.clear();
        m_c3dFunctionsAutoCmpl.clear();
        m_c3dFunctionsHighlight.clear();

        api->clear();

        // Добавление новых заголовков
        for (int i = 0; i < tempIncludes.length(); ++i)
            m_Includes.append(tempIncludes[i]);

        // Поиск классов, методов и т.д. и добавление их
        // в массивы для подсветки и автодополнения
        for (QString include : m_Includes)
            traversalHeaders(include, regExpIncludesPattern);

        // Передача названий классов, структур, перечислителей
        // объединений и пространства имен для подсветки
        QString typesHighlight;
        for (QString typeName : m_c3dTypesHighlight)
        {
            typesHighlight += typeName + " ";
        }
        m_pLexerCxx->setClasses(typesHighlight.toStdString());
        
        // Передача названий глобальных функций, методов 
        // и конструкторов для подсветки
        QString functionsHighlight;

        // Добавление функций программы
        // в массив m_c3dFunctionsHighlight
        defaultFunctionsHighlight(); 
        for (QString functionName : m_c3dFunctionsHighlight)
        {
            functionsHighlight += functionName + " ";
        }
        m_pLexerCxx->setFunctions(functionsHighlight.toStdString());

        // Добавление всех названий 
        // в список автодополнения
        prepareAutoComplete();

        setLexer(m_pLexerCxx);

        // Возвращаются настройки для скобок
        setBraceColor(QColor("yellow"), QColor("blue"),
                      QColor("orange"), QColor("red"));
    }
    searchVariables();
}

void TextEditor::traversalHeaders(const QString include, const QRegularExpression regExpIncludesPattern)
{
    QFile header;

    if (include == "setup.h")
        header.setFileName(APP.userDir() + "/" + include);
    else
        header.setFileName(APP.kernelDir() + "/" + include);

    // Проверка был ли этот заголовок уже осмотрен
    if (!m_headers.contains(include))
    {
        if (header.exists() && header.open(QIODevice::ReadOnly))
        {
            // Содержимое файла
            QString fileSource = header.readAll();
            header.close();

            // Поиск заголовков в файле
            QRegularExpressionMatch match = regExpIncludesPattern.match(fileSource);
            QRegularExpressionMatchIterator iRegInclude = regExpIncludesPattern.globalMatch(fileSource);

            if (match.hasMatch())
            {
                while (iRegInclude.hasNext())
                {
                    // Поиск новых заголовков для обхода
                    QRegularExpressionMatch matchInc = iRegInclude.next();
                    QString include = !matchInc.captured(2).isEmpty() ? matchInc.captured(2) : matchInc.captured(4);
                    header.setFileName(APP.kernelDir() + "/" + include);

                    if (header.exists() && header.open(QIODevice::ReadOnly))
                    {
                        header.close();
                        if (!m_AllHeaders.contains(include))
                        {
                            m_AllHeaders.append(include);
                            // Рекурсивный обход заголовков
                            traversalHeaders(include, regExpIncludesPattern);
                        }
                        else
                            continue;
                    }
                    else
                        continue;
                }
            }

            // Поиск глобальных функций
             const QString strRegExFunctions("(?:^\\s*typedef\\s+|^\\s*MATH_FUNC\\s*\\(\\s*)(\\w+\\W*)(?:\\(\\s*\\*|\\s*\\**\\s*\\)\\s*)(\\w+)(?:[^(]*)(\\([\\s\\S]*?\\));");

             QRegularExpression regExpFunctionsPattern(strRegExFunctions, QRegularExpression::PatternOption::MultilineOption);
             QRegularExpressionMatchIterator  iRegFunctions = regExpFunctionsPattern.globalMatch(fileSource);
    
             while (iRegFunctions.hasNext())
             {
                 QRegularExpressionMatch matchFunctions = iRegFunctions.next();
                 QString tempStrFunction = QString("%2?4%3 -> %1").arg(matchFunctions.captured(1)).arg(matchFunctions.captured(2)).arg(matchFunctions.captured(3)).simplified();
                 if (!m_c3dFunctionsAutoCmpl.contains(tempStrFunction))
                 {
                     // Для callTips
                     m_c3dFunctionsAutoCmpl.append(tempStrFunction.simplified());
                     m_c3dFunctionsAutoCmpl.append("::" + tempStrFunction.simplified());
                     //qDebug() << tempStrFunction.trimmed();
                     // Добавление слов для автокомплита
                     if (!m_c3dFunctionsHighlight.contains(matchFunctions.captured(2)))
                         m_c3dFunctionsHighlight.append(matchFunctions.captured(2));
                 }
             }

            // Поиск классов, структур, перечислений и объединений
            QRegularExpression regExpObjectsPattertn("(?:(class|struct).*?\\s+(\\w+?)\\s*[:;{]|(enum|unione).*?\\s+(\\w+?)\\s*[:;{]|(namespace).*?\\s+(\\w+?)\\s*[:;{])");
            QRegularExpressionMatchIterator iRegClass = regExpObjectsPattertn.globalMatch(fileSource);

            while (iRegClass.hasNext())
            {
                QRegularExpressionMatch match = iRegClass.next();
                // Перечисления и объединения
                if (!match.captured(4).isEmpty())
                {
                    if (!m_c3dTypesHighlight.contains(match.captured(4)))
                    {
                        m_c3dTypesAutoCmpl.append(match.captured(4) + "?3");
                        m_c3dTypesHighlight.append(match.captured(4));
                    }
                }
                // Классы и структуры
                else if (!match.captured(2).isEmpty())
                {
                    if (!m_c3dTypesHighlight.contains(match.captured(2)))
                    {
                        m_c3dTypesHighlight.append(match.captured(2));
                        m_classes.append(match.captured(2));
                    }
                }
                // Пространства имен
                else if (!match.captured(6).isEmpty())
                {
                    if (!m_c3dTypesHighlight.contains(match.captured(6)))
                    {
                        m_c3dTypesHighlight.append(match.captured(6));
                        m_c3dTypesAutoCmpl.append(match.captured(6) + "?7");
                    }
                }
            }

            //Поиск содержимого каждого класса
            QString strRegExClassSourse("^\\s*(class|struct)\\s+(?:MATH_CLASS\\s+)?(\\w+)\\s+(?::[^{]+)?({(?>[^{}]+|(?3))*})");

            QRegularExpression regExpClassPattertn(strRegExClassSourse, QRegularExpression::PatternOption::MultilineOption);
            QRegularExpressionMatchIterator  iRegitClass = regExpClassPattertn.globalMatch(fileSource);
            
            while (iRegitClass.hasNext())
            {
                QRegularExpressionMatch matchClass = iRegitClass.next();
                QString type = matchClass.captured(1);
                QString className = matchClass.captured(2);

                // Поиск внутри каждого класса между public: и (private: | protected:)
                QString strRegExPublic("^\\s*(?:public\\s*:)([\\s\\S]*?)(?:private\\s*:|protected\\s*:|};)");
                QRegularExpression regExpPublicPattern(strRegExPublic, QRegularExpression::PatternOption::MultilineOption);
                QRegularExpressionMatchIterator iRegitPublic = regExpPublicPattern.globalMatch(matchClass.captured(3));
            
                while (iRegitPublic.hasNext())
                {
                    QRegularExpressionMatch matchPublic = iRegitPublic.next();
                    QString publicContent = matchPublic.captured();
                    
                    // Удаление комментариев, так как в них есть 
                    // конструкции похожие на методы
                    deleteCommentsRegExp(publicContent);
                    
                    // Удаление деструкторов
                    QRegularExpression regExpDstPattern("~.*?\\n", QRegularExpression::PatternOption::MultilineOption); 
                    QRegularExpressionMatchIterator  iRegitDst = regExpDstPattern.globalMatch(publicContent);
                    
                    while (iRegitDst.hasNext())
                    {
                        QRegularExpressionMatch matchDst = iRegitDst.next();
                        publicContent.remove(matchDst.captured());
                    }

                    // Поиск методов каждого класса
                    QString strRegExMethods("\\s*(?:virtual)?\\s*(\\w+\\s*[*&]?)(|\\s*(?:operator\\s*(?:\\(\\)|\\w+))|\\s+\\w+)\\s*(\\([\\s\\S]*?\\)?)(?:;|{|\\s+\\:)");
                    QRegularExpression regExpMethodsPattern(strRegExMethods, QRegularExpression::PatternOption::MultilineOption);
                    QRegularExpressionMatchIterator  iRegitMethods = regExpMethodsPattern.globalMatch(publicContent);
                    
                    while (iRegitMethods.hasNext())
                    {
                        QRegularExpressionMatch matchMethods = iRegitMethods.next();

                        // Конструкторы классов
                        if (className == matchMethods.captured(1).trimmed() || (className == matchMethods.captured(2).trimmed() && matchMethods.captured(1).trimmed() == "explicit"))
                        {
                                QString classCtr = QString("%1?2%2.").arg(className).arg(matchMethods.captured(3)).simplified();
                                if (!m_c3dFunctionsAutoCmpl.contains(classCtr.simplified()))
                                    m_c3dFunctionsAutoCmpl.append(classCtr.simplified()); 
                        }
                         // Конструкторы классов, которые содержатся в другом классе
                        else if (matchMethods.captured(2) != className)
                        {
                            if (matchMethods.captured(1) == "explicit")
                            {
                                
                                QString classMethod = QString("%1?8%2. %3 %4.").arg(matchMethods.captured(2)).arg(matchMethods.captured(3))
                                    .arg(type).arg(className).simplified();
                                if (!m_c3dFunctionsAutoCmpl.contains(classMethod.simplified()))
                                    m_c3dFunctionsAutoCmpl.append(classMethod.simplified());
                                if (!m_c3dFunctionsHighlight.contains(matchMethods.captured(2)))
                                    m_c3dFunctionsHighlight.append(matchMethods.captured(2));
                            }
                            // Методы
                            else
                            {
                                if (matchMethods.captured(1) != "return")
                                {
                                    QString classMethod = QString("%2?4%3 -> %1. %4 %5.")
                                        .arg(matchMethods.captured(1)).arg(matchMethods.captured(2)).arg(matchMethods.captured(3))
                                        .arg(type).arg(className).simplified();
                                    if (!m_c3dFunctionsAutoCmpl.contains(classMethod.simplified()))
                                        m_c3dFunctionsAutoCmpl.append(classMethod.simplified());
                                    if (!m_c3dFunctionsHighlight.contains(matchMethods.captured(2)))
                                        m_c3dFunctionsHighlight.append(matchMethods.captured(2));
                                }
                            }
                        }
                        
                    }
                }
            }
        }
        // Добавляем название файла, чтобы не обходить его снова
        m_headers.append(include);
    }
}

void TextEditor::deleteCommentsRegExp(QString& source)
{
    //Удаление комментариев
    QRegularExpression regExpLineCommentPattern("\\/\\/.*?\\n", QRegularExpression::PatternOption::MultilineOption);
    QRegularExpression regExpBlockCommentsPattern("\\/\\*[\\s\\S]*?\\*\\/", QRegularExpression::PatternOption::MultilineOption);

    QRegularExpressionMatchIterator  iRegitComment = regExpLineCommentPattern.globalMatch(source);

    // Удаление строчных комментариев
    while (iRegitComment.hasNext())
    {
        QRegularExpressionMatch matchComment = iRegitComment.next();
        source.remove(matchComment.captured());
    }

    iRegitComment = regExpBlockCommentsPattern.globalMatch(source);

    // Удаление блочных комментариев
    while (iRegitComment.hasNext())
    {
        QRegularExpressionMatch matchComment = iRegitComment.next();
        source.remove(matchComment.captured());
    }
}

void TextEditor::searchVariables()
{
    QString currentDoc = text();
    QStringList tempVariables;

    // Удаление комментариев, чтобы 
    // не захватывать переменные из комментариев
    deleteCommentsRegExp(currentDoc);

    // Поиск переменных
    QString strRegExVariables("^(?:[\\s\\W])*(?:constexpr|inline|extern|const|static|volatile|mutable)*\\s[\\w]+(?:<[^>]*>)*(?:[\\s*&]|const)+(\\w+)");
    QRegularExpression regExpVariablesPattern(strRegExVariables, QRegularExpression::PatternOption::MultilineOption);
    QRegularExpressionMatchIterator  iRegitVariables = regExpVariablesPattern.globalMatch(currentDoc);

    while (iRegitVariables.hasNext())
    {
        QRegularExpressionMatch matchVariables = iRegitVariables.next();
        QString variable = matchVariables.captured(1);
        if (!tempVariables.contains(variable))
            tempVariables.append(variable);
    }
    
    if (m_variables != tempVariables)
    {
        api->clear();
        m_variables.clear();
        for (QString variable : tempVariables)
        {
            // Конструкции которые похожи на переменные не добавляются в список автодополнения
            // если их название есть в остальных объектах
            if (m_c3dFunctionsHighlight.contains(variable + " ") || m_c3dTypesHighlight.contains(variable + " ") ||
                m_keyWordsCxx.contains(variable + " "))
                continue;
            else
            {
                api->add(variable + "?6");
                m_variables.append(variable);
            }
        }
        prepareAutoComplete();
    }
}

void TextEditor::prepareAutoComplete()
{
    for (QString classes : m_classes)
    {
        if (!m_c3dTypesAutoCmpl.contains(classes + "?2"))
            m_c3dTypesAutoCmpl.append(classes + "?2");
    }
    // Передача названий классов, структур, перечислителей
    // объединений и пространства имен для автодополнения
    for (QString typeName : m_c3dTypesAutoCmpl)
    {
        api->add(typeName + "\n");
    }

    // Передача названий глобальных функций, методов 
    // и конструкторов для автодополнения
    for (QString functionName : m_c3dFunctionsAutoCmpl)
    {
        api->add(functionName + "\n");
    }
    defaultFunctionsAutoCmpl();

    api->load(":/res/autocompleteCpp.api");
    api->load(APP.tempDir() + "/" + "autocompleteHeaders.api");

    api->prepare();
}

void TextEditor::defaultFunctionsHighlight()
{
    m_c3dFunctionsHighlight.append("show ");
    m_c3dFunctionsHighlight.append("run ");
    m_c3dFunctionsHighlight.append("message ");
    m_c3dFunctionsHighlight.append("messageBox ");;
}

void TextEditor::defaultFunctionsAutoCmpl()
{
    api->add("show?4(const Style& style, MbSpaceItem* refItem) -> void. \n");
    api->add("show?4(const Style& style, MbPlaneItem* refItem, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("show?4(const Style& style, MbPlaneItem* refItem, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("show?4(uint32_t color, MbSpaceItem* refItem) -> void. \n");
    api->add("show?4(uint32_t color, MbPlaneItem* refItem, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("show?4(MbSpaceItem* refItem) -> void. \n");
    api->add("show?4(MbPlaneItem* refItem, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("show?4(uint32_t color, const MbCartPoint& cartPoint, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("show?4(const MbCartPoint& cartPoint, const MbPlacement3D* p = nullptr) -> void. \n");
    api->add("message?4(const std::string& msg) -> void. \n");
    api->add("messageBox?4(const std::string& title, const std::string& msg) -> void. \n");
    api->add("messageBox?4(const std::string& msg) -> void. \n");
    api->add("run?4() -> bool. \n");
}           

void TextEditor::getIncludes()
{
    QStringList includes;
    // Добавление в массив includes всех названий заголовочных
    // файлой ядра c3d
    QDir c3dKernel = APP.kernelDir();
    for (QString include : c3dKernel.entryList())
        if (!includes.contains(include))
            includes.append(include + "?1\n");

    // Создание файла, который хранит все заголовки ядра
    // которые используются для автодополнения
    QFile autocopleteHeaders;
    autocopleteHeaders.setFileName(APP.tempDir() + "/" + "autocompleteHeaders.api");
    if (autocopleteHeaders.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&autocopleteHeaders);
        for (QString include : includes)
            stream << include;
        autocopleteHeaders.close();
    }
}