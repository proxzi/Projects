#include "tutorialloader.h"

#include <QRegularExpression>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDir>
#include <QDebug>

using namespace std::placeholders;

TutorialLoader::TutorialLoader(const QString& directoryPath)
    : m_directoryPath(directoryPath)
{
}

void TutorialLoader::traverseDir(const QString& dirName)
{
    QDir dir(dirName);
    QFileInfoList infoList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    for (const auto& fileInfo : infoList)
    {
        auto path = fileInfo.absoluteFilePath();
        if (fileInfo.isDir())
        {
            traverseDir(path);
        }
        else
        {
            if (fileInfo.fileName() == "tutorial.xml")
            {
                Tutorial tutorial;
                QDomDocument domDoc;
                QFile file(path);

                if (file.open(QIODevice::ReadOnly))
                {
                    if (domDoc.setContent(&file))
                    {
                        QDomElement domElement = domDoc.documentElement();
                        traverseTutorial(domElement, fileInfo.absoluteDir().path(), tutorial);
                    }
                    file.close();
                }

                m_tutorials[tutorial.category].append(tutorial);

            }
        }
    }
}

void TutorialLoader::readTutorialDirectory()
{
    if (!m_tutorials.isEmpty())
    {
        m_tutorials.clear();
    }
    traverseDir(m_directoryPath);
}

QMap<QString, QVector<Tutorial>>& TutorialLoader::folders()
{
    return m_tutorials;
}

void TutorialLoader::traverseNode(const QString& path, std::function<void(const QDomNode&, const QString& path, Tutorial& tutorial)> traverse)
{
    QDomDocument domDoc;
    QFile file(path);
    
    if (file.open(QIODevice::ReadOnly))
    {
        if (domDoc.setContent(&file))
        {
            QDomElement domElement = domDoc.documentElement();
        }
        file.close();
    }
}

void TutorialLoader::traverseTutorial(const QDomNode& node, const QString& path, Tutorial& tutorial)
{
    QDomNode domNode = node.firstChild();
    while (!domNode.isNull()) {
        if (domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if (!domElement.isNull()) {
                if (domElement.tagName() == "preview") {
                    tutorial.imagePath = QString("%1/%2")
                        .arg(path)
                        .arg(domElement.text());
                }
                if (domElement.tagName() == "source") {
                    tutorial.tutorialPath = path;
                    tutorial.category = domElement.attribute("category");
                    tutorial.title = domElement.attribute("displayName");
                    tutorial.source = QString("%1/%2")
                        .arg(path)
                        .arg(domElement.text());
                }
                if (domElement.tagName() == "code") {
                    tutorial.codePath = QString("%1/%2")
                        .arg(path)
                        .arg(domElement.text());

                    QFile file(tutorial.codePath);
                    if (file.open(QIODevice::ReadOnly))
                    {
                        QString codeBlocksStr = file.readAll();
                        QRegularExpression re("\\[id = \"(.*)\"\\]\\s*\\[begin\\]\\r?\\n?([\\s\\S]*?)\\r?\\n?\\[end\\]");
                        auto it = re.globalMatch(codeBlocksStr);
                        while (it.hasNext()) {
                            auto match = it.next();
                            tutorial.codeBlocks[match.captured(1)] = match.captured(2);
                        }
                    }
                }
            }
        }
        traverseTutorial(domNode, path, tutorial);
        domNode = domNode.nextSibling();
    }
}