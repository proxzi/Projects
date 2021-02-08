#pragma once

#include <functional>

#include <QString>
#include <QVector>
#include <QMap>

class QDomNode;

struct Tutorial
{
    QString category;
    QString title;
    QString source;
    QString imagePath;
    QString tutorialPath;
    QString codePath;
    QMap<QString, QString> codeBlocks;
};

class TutorialLoader
{
public:
    TutorialLoader(const QString& directoryPath);

    void readTutorialDirectory();
    QMap<QString, QVector<Tutorial>>& folders();
private:
    void traverseNode(const QString& path, std::function<void(const QDomNode&, const QString& path, Tutorial& tutorial)> traverse);
    void traverseDir(const QString& dirName);
    void traverseTutorial(const QDomNode& node, const QString& path, Tutorial& tutorial);

    QMap<QString, QVector<Tutorial>> m_tutorials;
    QString m_directoryPath;
};
