#pragma once

#include <Qsci/qsciscintilla.h>

class LexerCxx;
class QsciAPIs;

//struct ClassContent{
//    QStringList inheritanceList;
//    QStringList methodsList;
//};
//
//struct HeaderContent {
//    QMap<QString, ClassContent> classList;
//    QStringList functionsList;
//};

class TextEditor : public QsciScintilla
{
    Q_OBJECT
    public:
    explicit TextEditor(QWidget* parent = nullptr);
    ~TextEditor();
    LexerCxx* m_pLexerCxx;
    
    QList<int> m_positionsCurrentWord;
    QString m_currentWord;
        
    struct CommentPosition
    {
        QList<int> m_positionsCommentStart;
        QList<int> m_positionsCommentEnd;
    };

    QStringList m_Includes;
    QStringList m_AllHeaders;
    QStringList m_headers;

    QStringList m_classes;

    QsciAPIs* api = nullptr;

    QStringList m_c3dTypesAutoCmpl;
    QStringList m_c3dTypesHighlight;

    QStringList m_c3dFunctionsAutoCmpl;
    QStringList m_c3dFunctionsHighlight;

    QStringList m_variables;
    QStringList m_keyWordsCxx;

    void defaultFunctionsHighlight();
    void defaultFunctionsAutoCmpl();

    // Рекурсивный обход заголовочных фалйлов c3d 
    // и добавление названий классов функций и др в массивы.
    void traversalHeaders(const QString include, const QRegularExpression regExpIncludesPattern);

    void searchVariables();
    
    // Функция для цвета скобок соответствия
    void setBraceColor(const QColor& mb, const QColor& mf,
                       const QColor& ub, const QColor& uf);
    
    void clearHighlighWord();

    void prepareAutoComplete();

    static void getIncludes();

    void deleteCommentsRegExp(QString& source);

    protected:
    void keyPressEvent(QKeyEvent* e) override;
    
    public slots:
        
    // Выделение слов при смене курсора
    void slotHighlighCurrentWord(int line, int index);
    void slotSearchIncludes();
};