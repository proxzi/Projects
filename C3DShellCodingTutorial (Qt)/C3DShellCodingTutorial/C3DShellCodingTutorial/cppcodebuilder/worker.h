#pragma once

#include <QObject>

class CppCodeBuilder;

class Worker : public QObject {
    Q_OBJECT
public:
    Worker(CppCodeBuilder* builder);

public slots:
    void process();
signals:
    void finished(bool res);
    void error(QString err);
private:
    CppCodeBuilder* m_pBuildData;
};