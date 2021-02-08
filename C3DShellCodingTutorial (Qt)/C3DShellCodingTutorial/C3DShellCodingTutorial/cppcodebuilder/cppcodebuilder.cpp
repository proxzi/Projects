#include <QApplication>
#include <QThread>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QRegularExpression>

#include "storagelocation.h"
#include "cppcodebuilder.h"
#include "worker.h"
#include "globaldef.h"

CppCodeBuilder::CppCodeBuilder(QWidget* parent)
    : QWidget(parent)
    , exePath(QApplication::applicationDirPath())
    , consoleProcess(new QProcess(this))
    , m_dll()
{
    connect(consoleProcess, &QProcess::readyReadStandardOutput,
        this, &CppCodeBuilder::readConsoleOutput);
    connect(consoleProcess, &QProcess::readyReadStandardError,
        this, &CppCodeBuilder::readConsoleError);
    connect(consoleProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        this, &CppCodeBuilder::finishedCompilation);

    QFile initCompiler(APP.tempDir() + "/" + g_kDefaultBuilderInitFileName);
    QTextStream txtStream(&initCompiler);
    txtStream.setCodec("UTF-8");

    if (initCompiler.open(QIODevice::WriteOnly))
    {
        txtStream << QString("chcp 65001\r\n");

        QSettings settings(APP.commonDir() + "/settings.ini", QSettings::IniFormat);
        auto compilerPath = settings.value("Build/CompilerPath", R"_(C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat)_").toString().replace("\\", "\\\\");

        txtStream << QString("@call \"%1\"\r\n").arg(compilerPath);
        txtStream << QString("@cd \"%1\"\r\n").arg(APP.tempDir());

        txtStream << QString("cl /UTF-8 /Fo\"%6\"\\ -c /nologo /TP -DUNICODE -D_UNICODE /DWIN32 /D_WINDOWS /GR /EHsc ").arg(APP.tempDir());
#ifdef _DEBUG
        txtStream << QString("/Zi /Ob0 /Od /RTC1 /W4 /D_DEBUG /D_DRAWGI /MP /bigobj -MDd -std:c++14 ");
#else
        txtStream << QString("/O2 /Ob2 -DNDEBUG /W4 /MD -std:c++14 ");
#endif // DEBUG
        txtStream << QString("/I \"%1\" /I \"%2\" \"%3\" \"%4\" && link \"%6\\dllmain.obj\" \"%6\\code.obj\" /out:\"%6\\dllmain.dll\" /dll /machine:x64 /INCREMENTAL:NO \"%5\"")
        /*%1*/.arg(APP.kernelDir())
        /*%2*/.arg(APP.userDir())
        /*%3*/.arg(APP.userDir() + "/" + g_kDefaultBuilderUserMainFileName)
        /*%4*/.arg(APP.builderUserFileName())
        /*%5*/.arg(APP.userDir() + "/c3d.lib")
        /*%6*/.arg(APP.tempDir());

        initCompiler.close();
    }

}

void CppCodeBuilder::readConsoleOutput()
{
    QString str = fromByteArray(consoleProcess->readAllStandardOutput());
    m_consoleOutput.append(str);
    //emit sendToConsole(str, ConsoleText::ResultType::Warning);
}

void CppCodeBuilder::readConsoleError()
{
    QString str = fromByteArray(consoleProcess->readAllStandardError());
    m_consoleError.append(str);
    emit sendToConsole(str, ConsoleText::ResultType::Error);
}

bool CppCodeBuilder::compileCode()
{
    emit startWork();
   
    releaseDll();


    consoleProcess->start(QString("cmd.exe /c \"%1\"").arg(APP.tempDir() + "/" + g_kDefaultBuilderInitFileName));

    return consoleProcess->waitForStarted();
}

void CppCodeBuilder::receiveCode(const QString& txt, const QString& name)
{
    m_currentTextEdit = name;
    QFile file(APP.builderUserFileName());

    if (file.open(QIODevice::WriteOnly)) {
        file.write(txt.toUtf8());
        file.close();
    }

    emit clearConsole();
    m_consoleError.clear();
    m_consoleOutput.clear();

    emit sendToConsole(tr("Compilation started."), ConsoleText::ResultType::Complete);

    if (!compileCode())
    {
        emit sendToConsole(tr("Compilation failed."), ConsoleText::ResultType::Error);
        emit finishWork();
    }
}


void CppCodeBuilder::releaseDll()
{
    if (m_dll.isLoaded())
    {
        if (!m_dll.unload()) {
            emit sendToConsole(tr("Unloading failed!"), ConsoleText::ResultType::Error);
            return;
        }
    }
}

void CppCodeBuilder::workerFinished(bool res)
{
    if (res)
    {
        emit sendToConsole(tr("Rendering..."), ConsoleText::ResultType::Complete);
        emit drawObjects(m_objectsCollection);

        emit sendToConsole(tr("Render completed."), ConsoleText::ResultType::Complete);
    }
    else
    {
        emit sendToConsole(tr("Rendering failed"), ConsoleText::ResultType::Error);
        releaseDll();
    }

    for (const QString& msg : m_messages)
    {
        emit sendToSceneMessage(msg);
    }

    for (const auto& msg : m_messageBoxes)
    {
        QMessageBox::warning(this, msg.first, msg.second);
    }

    emit finishWork();
}

void CppCodeBuilder::finishedCompilation(int exitCode, QProcess::ExitStatus exitStatus)
{
    emit sendToConsole(tr("Compilation completed."), ConsoleText::ResultType::Complete);

    if (exitStatus == QProcess::ExitStatus::CrashExit) return;

    if (exitCode == 0)
    {
        m_dll.setFileName(APP.tempDir() + QString("/dllmain"));

        if (!m_dll.load()) {
            emit sendToConsole(tr("Loading failed!"), ConsoleText::ResultType::Error);
            return;
        }

        auto thread = new QThread;
        auto worker = new Worker(this);
        worker->moveToThread(thread);

        connect(worker, &Worker::error, [this](const QString& msg)
        {
            emit sendToConsole(tr("Rendering failed"), ConsoleText::ResultType::Error);
            emit sendToConsole(msg, ConsoleText::ResultType::Error);
            releaseDll();
            emit finishWork();
        });

        connect(thread, &QThread::started, worker, &Worker::process);
        connect(thread, &QThread::finished, worker, &QThread::deleteLater);
        connect(worker, &Worker::finished, thread, &QThread::deleteLater);
        connect(worker, &Worker::finished, thread, &QThread::quit);
        connect(worker, &Worker::finished, this, &CppCodeBuilder::workerFinished);

        thread->start();
    }
    else if (exitCode == 1 || exitCode == 2)
    {
        emit clearConsole();
        prepareErrorsList();
    }
    else
    {
        emit sendToConsole(tr("Linking failed"), ConsoleText::ResultType::Error);
        prepareErrorsList();
    }
}

void CppCodeBuilder::prepareErrorsList()
{
    m_errorsList.clear();
    m_consoleOutput.remove(0, m_consoleOutput.lastIndexOf("\'x64\'"));
    m_consoleOutput.remove(APP.builderUserFileName());

    QRegularExpression re("\\((\\d+)\\)(.*?)\\n", QRegularExpression::PatternOption::MultilineOption);
    auto it = re.globalMatch(m_consoleOutput);

    while (it.hasNext())
    {
        auto match = it.next();
        m_errorsList.push_back({ match.captured(1).toInt() , match.captured(2) });
    }

    emit signalErrorsList(m_currentTextEdit, m_errorsList);
    emit sendToConsole(m_consoleOutput, ConsoleText::ResultType::Error);
    emit finishWork();
}

void CppCodeBuilder::slotMoveToError(const QString& strLine)
{
    QRegularExpression re("\\((\\d+)\\)(.*)");
    auto match = re.match(strLine);
    if (match.hasMatch()) {
        int line = match.captured(1).toInt();
        QString message = match.captured(2);
        emit signalMoveToError(m_currentTextEdit, line, message);
    }
}
