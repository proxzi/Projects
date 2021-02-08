#pragma once

#include <QString>
#include <QTemporaryDir>

#define APP StorageLocation::instance()

class StorageLocation
{
public:
    static StorageLocation& instance();

public:
    void run(bool r);
    bool isRun();
    QString tempDir() const;
    QString workDir() const;
    QString commonDir() const;
    QString workDirName() const;
    QString tutorialsDir() const;
    QString userDir() const;
    QString kernelDir() const;
    QString manualsDir() const;
    QString modelsDir() const;
    QString builderUserFileBaseName() const;
    QString builderUserFileName() const;
    QString webDocRoot() const;
    QString localDocRoot() const;
    QString docEn() const;
    QString docRu() const;
    QString docPrefix() const;
    void saveCommonSettings(const QString& key, const QVariant& value);
    QVariant restoreCommonSettings(const QString& key, const QVariant& defaultValue = QVariant()) const;
    bool isSavedCommonSettings(const QString& key) const;

    QVector<QPair<QString, QString>> readFromWorkFolder() const;
    void writeToWorkFolder(const QString& title, const QString& fullpath, const QString& path);

private:
    const QString m_appPath;
    QString m_tempDirPath;
    QString m_documentsDirPath;
    QTemporaryDir m_temporaryDir;
    bool b_isAlreadyRun = false;
private:
    QString projectPath() const;

    StorageLocation(const QString& appPath);
    StorageLocation() = default;
    ~StorageLocation() = default;
    StorageLocation(const StorageLocation&) = delete;
    StorageLocation& operator=(const StorageLocation&) = delete;
};