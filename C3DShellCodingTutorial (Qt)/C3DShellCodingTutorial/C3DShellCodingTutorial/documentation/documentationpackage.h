#pragma once
#include <QObject>
#include <QString>

class DocumentationPackage : public QObject
{
    Q_OBJECT

public:
    explicit DocumentationPackage(QObject* parent = nullptr);

    void setText(const QString& source, const QString& hostUrl);

signals:
    void signalSearchRequest(const QString& className, const QString& classMethod, const QString& hostUrl);
    void signalUpdateCurrentUrl(const QString& url);
    void signalSearchIsSuccess(bool success);

public slots:
    void slotUpdateCurrentUrl(const QString& url);
    void slotSearchIsSuccess(bool success);

private:
    bool m_success;
};