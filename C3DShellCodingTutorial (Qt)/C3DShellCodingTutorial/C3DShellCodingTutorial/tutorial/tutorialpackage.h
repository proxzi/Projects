#pragma once

#include <QObject>
#include <QString>

class TutorialPackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source MEMBER m_source NOTIFY textChanged FINAL)
    Q_PROPERTY(QString tutorialPath MEMBER m_tutorialPath  NOTIFY setPath FINAL)

public:
    explicit TutorialPackage(QObject* parent = nullptr);

    void setText(const QString& source, const QString& tutorialPath);

signals:
    void textChanged(const QString& source, const QString& tutorialPath);
    void setPath(const QString& tutorialPath);

private:
    QString m_source;
    QString m_tutorialPath;
};