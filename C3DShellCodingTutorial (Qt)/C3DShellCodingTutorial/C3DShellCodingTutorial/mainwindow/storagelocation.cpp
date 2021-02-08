#include <functional>

#include <QApplication>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QVector>
#include <QPair>
#include <QDomNode>
#include <QDirIterator>
#include <QFileInfo>
#include <QSettings>

#include "storagelocation.h"
#include "globaldef.h"

StorageLocation& StorageLocation::instance()
{
    static StorageLocation singleton(qApp->applicationDirPath());
    return singleton;
}

StorageLocation::StorageLocation(const QString& appPath)
    : m_appPath(appPath)
    , m_tempDirPath()
{
    //if (m_temporaryDir.isValid()) {
    //   m_tempDirPath = m_temporaryDir.path();
    //}

    auto tempDirPathList = QStandardPaths::standardLocations(QStandardPaths::TempLocation);
    Q_ASSERT(!tempDirPathList.empty());
    m_tempDirPath = tempDirPathList.front();

    QDir tempDir_(tempDir());
    if (!tempDir_.exists()) {
        tempDir_.mkpath(".");
    }

    auto documentDirPathList = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    Q_ASSERT(!documentDirPathList.empty());
    m_documentsDirPath = documentDirPathList.front();

    QDir workDir_(workDir());
    if (!workDir_.exists()) {
        workDir_.mkpath(".");
    }

    QDirIterator itWorkDir(":/res/texts/workfolder", QDirIterator::Subdirectories);
    while (itWorkDir.hasNext()) {
        auto srcFileName = itWorkDir.next();
        QString dstFileName = QString("%1/%2").arg(workDir()).arg(QFileInfo(srcFileName).fileName());
        if (!QFile::exists(dstFileName))
        {
            QFile::copy(srcFileName, dstFileName);
            QFile(dstFileName).setPermissions(QFile::ReadOther | QFile::WriteOther);
        }
    }

    QDir userDir_(userDir());
    if (!userDir_.exists()) {
        userDir_.mkpath(".");
    }

    QDirIterator itUserDir(":/res/texts/user", QDirIterator::Subdirectories);
    while (itUserDir.hasNext()) {
        auto srcFileName = itUserDir.next();
        QString dstFileName = QString("%1/%2").arg(userDir()).arg(QFileInfo(srcFileName).fileName());
        if (!QFile::exists(dstFileName))
            QFile::copy(srcFileName, dstFileName);
    }
   
#ifdef _DEBUG
    QString libFile(":/res/texts/debug/c3d.lib");
#else
    QString libFile(":/res/texts/release/c3d.lib");
#endif // DEBUG

    QFileInfo fileInfo(userDir() + "/c3d.lib");
    if (fileInfo.exists())
    {
        QFile file(userDir() + "/c3d.lib");
        file.setPermissions(QFile::ReadOther | QFile::WriteOther);
        file.remove();
    }

    QFile file(userDir() + "/c3d.lib");
    file.setPermissions(QFile::ReadOther | QFile::WriteOther);
    QFile::copy(libFile, userDir() + "/c3d.lib");


    QDir kernelDir_(kernelDir());
    if (!kernelDir_.exists()) {
        kernelDir_.mkpath(".");
    }

    QDirIterator itKernelDir(":/res/texts/kernel", QDirIterator::Subdirectories);

    while (itKernelDir.hasNext()) {
        auto srcFileName = itKernelDir.next();
        QString dstFileName = QString("%1/%2").arg(kernelDir()).arg(QFileInfo(srcFileName).fileName());
        if (!QFile::exists(dstFileName))
            QFile::copy(srcFileName, dstFileName);
    }
}

QString StorageLocation::commonDir() const
{
#ifdef _DEBUG
    return QString("%1/%2").arg(m_appPath).arg(g_kDefaultCommonName);
#else
    return QString("%1/%2").arg(m_documentsDirPath).arg(g_kDefaultCommonName);
#endif // DEBUG
}

QString StorageLocation::tempDir() const
{
    return QString("%1/%2").arg(m_tempDirPath).arg(g_kDefaultCommonName);
}

QString StorageLocation::workDir() const
{
    return QString("%1/%2").arg(commonDir()).arg(g_kDefaultWorkDirectoryName);
}

QString StorageLocation::workDirName() const
{
    return g_kDefaultWorkDirectoryName;
}

QString StorageLocation::tutorialsDir() const
{
    return m_appPath + "/" + g_kDefaultTutorialsDirectoryName;
}

QString StorageLocation::userDir() const
{
    return QString("%1/%2").arg(commonDir()).arg(g_kDefaultBuilderDirectoryName);
}

QString StorageLocation::kernelDir() const
{
    return QString("%1/%2").arg(commonDir()).arg(g_kDefaultKernelDirectoryName);
}

QString StorageLocation::manualsDir() const
{
    return m_appPath + "/" + g_kDefaultManualsDirectoryName;
}

QString StorageLocation::modelsDir() const
{
    return m_appPath + "/" + g_kDefaultModelsDirectoryName;
}

QString StorageLocation::builderUserFileBaseName() const
{
    return g_kDefaultBuilderUserFileName;
}

QString StorageLocation::builderUserFileName() const
{
    return tempDir() + "/" + builderUserFileBaseName();
}

QString StorageLocation::webDocRoot() const
{
    return g_kDefaultWebDocRoot;
}

QString StorageLocation::localDocRoot() const
{
    return m_appPath + "/" + g_kDefaultLocalDocRoot;
}

QString StorageLocation::docEn() const
{
    return g_kDefaultEn;
}

QString StorageLocation::docRu() const
{
    return g_kDefaultRu;
}

QString StorageLocation::docPrefix() const
{
    return g_kDefaultDocPrefix;
}

void StorageLocation::saveCommonSettings(const QString& key, const QVariant& value)
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);

    settings.setValue(key, value);
}

QVariant StorageLocation::restoreCommonSettings(const QString& key, const QVariant& defaultValue) const
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);
    return settings.value(key, defaultValue);
}

bool StorageLocation::isSavedCommonSettings(const QString& key) const
{
    QSettings settings(QString("%1/%2")
        .arg(APP.commonDir())
        .arg(g_kDefaultSettingsFileBaseName), QSettings::IniFormat);

    return settings.contains(key);
}
//-----------------------------------------------------------------------------
// 
// ---
QVector<QPair<QString, QString>> StorageLocation::readFromWorkFolder() const
{
    QVector<QPair<QString, QString>> listWorks;

    std::function<void(const QDomNode& node)> traverseNode = [this, &traverseNode, &listWorks](const QDomNode& node)
    {
        QDomNode domNode = node.firstChild();
        while (!domNode.isNull()) {
            if (domNode.isElement()) {
                QDomElement domElement = domNode.toElement();
                if (!domElement.isNull()) {

                    if (domElement.tagName() == "file") {

                        QString path;

                        if (!domElement.attribute("fullpath").isEmpty())
                        {
                            path = domElement.attribute("fullpath");
                        }
                        else
                        {
                            path = QString("%1/%2").arg(workDir()).arg(domElement.attribute("path"));
                        }

                        listWorks.push_back({ domElement.attribute("title") , path });
                    }
                }
            }
            traverseNode(domNode);
            domNode = domNode.nextSibling();
        }
    };

    QDomDocument domDoc;
    QFile file(projectPath());
    if (file.open(QIODevice::ReadOnly)) {
        if (domDoc.setContent(&file)) {
            QDomElement domElement = domDoc.documentElement();
            traverseNode(domElement);
        }
        file.close();
    }

    return listWorks;
}
//-----------------------------------------------------------------------------
// 
// ---
void StorageLocation::writeToWorkFolder(const QString& title_, const QString& fullpath_, const QString& path_)
{
    auto createFile = [this](QDomDocument& domDoc, const QString& title, const QString& fullpath, const QString& path)
    {
        auto domElement = domDoc.createElement("file");

        auto attrTitle = domDoc.createAttribute("title");
        attrTitle.setValue(title);
        domElement.setAttributeNode(attrTitle);

        auto attrFP = domDoc.createAttribute("fullpath");
        attrFP.setValue(fullpath);
        domElement.setAttributeNode(attrFP);

        auto attrPath = domDoc.createAttribute("path");
        attrPath.setValue(path);
        domElement.setAttributeNode(attrPath);

        return domElement;
    };

    QDomDocument domDoc;

    QFile file(projectPath());

    if (file.open(QIODevice::ReadWrite)) {
        if (domDoc.setContent(&file)) {
            QDomElement domElement = domDoc.documentElement();
            auto fileElement = createFile(domDoc, title_, fullpath_, path_);
            domElement.appendChild(fileElement);

            QTextStream textStream(&file);
            textStream.setCodec("UTF-8");
            textStream.seek(0);
            textStream << domDoc.toString();
        }
        file.close();
    }
}
//-----------------------------------------------------------------------------
// 
// ---
QString StorageLocation::projectPath() const
{
    QSettings profile("profile.ini", QSettings::IniFormat);
    QString currentWorkFolderPath = profile.value("WorkFolder/path", workDir()).toString();

    QDir workFolderDir(currentWorkFolderPath);

    if (!workFolderDir.exists())
    {
        workFolderDir.cd(workDir());
    }

    auto path = QString("%1/%2").arg(workFolderDir.absolutePath()).arg("Projects.xml");
    if (workFolderDir.exists())
    {
        QFile file(path);
        if (!file.exists())
        {
            if (file.open(QIODevice::WriteOnly))
            {
                QDomDocument doc;
                doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
                QDomElement domElement = doc.createElement("projects");
                doc.appendChild(domElement);
                QTextStream(&file) << doc.toString();
                file.close();
            }
        }
    }
    return path;
}

void StorageLocation::run(bool r)
{
    b_isAlreadyRun = r;
}

bool StorageLocation::isRun()
{
    return b_isAlreadyRun;
}