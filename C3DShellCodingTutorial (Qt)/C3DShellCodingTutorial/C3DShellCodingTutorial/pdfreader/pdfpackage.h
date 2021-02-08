#pragma once

#include <QObject>

class PdfPackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
public:
    explicit PdfPackage(QObject* parent = nullptr);

    QString url() const;
    void setUrl(const QString& url);

signals:
    void urlChanged(const QString&);

private:
    QString m_url;
};