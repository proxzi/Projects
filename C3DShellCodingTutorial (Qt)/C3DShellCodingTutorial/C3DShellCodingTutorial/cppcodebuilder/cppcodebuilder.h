#pragma once

#include <QLibrary>
#include <QWidget>
#include <QVector>
#include <QPair>
#include <QProcess>
#include "consoletext.h"
#include "globaldef.h"

class CppCodeBuilder : public QWidget
{
    Q_OBJECT
public:
    explicit CppCodeBuilder(QWidget* parent = nullptr);

    bool compileCode();
    void releaseDll();
    MbPlacement3D* getPlace();

signals:
    void clearConsole();

    void sendToConsole(const QString& txt, ConsoleText::ResultType t = 
        ConsoleText::ResultType::Standart);

    void sendToSceneMessage(const QString& txt, ConsoleText::ResultType t = ConsoleText::ResultType::Standart);
    void sendToSceneMessageColor(const QString& txt, const QColor& color);

    void drawObjects(const QVector<Model>&items);
    void finishWork();
    void startWork();

    void signalMoveToError(const QString& textEditName, int line, const QString& message);
    void signalErrorsList(const QString& textEditName, QVector<QPair<int, QString>> &errorsList);

public slots:
    void receiveCode(const QString& txt, const QString& name);
    void finishedCompilation(int exitCode, QProcess::ExitStatus exitStatus);
    void readConsoleOutput();
    void readConsoleError();
    void slotMoveToError(const QString& strLine);

private:
    void prepareErrorsList();
    void workerFinished(bool res);

    QString m_consoleOutput;
    QString m_consoleError;

    QProcess *consoleProcess;
    QString exePath;

    QVector<Model> m_objectsCollection;
    QVector<QString> m_messages;
    QVector<QPair<QString, QString>> m_messageBoxes;
    QVector<QPair<int, QString>> m_errorsList;
    QLibrary m_dll;
    QString m_currentTextEdit;

    friend class Worker;
};