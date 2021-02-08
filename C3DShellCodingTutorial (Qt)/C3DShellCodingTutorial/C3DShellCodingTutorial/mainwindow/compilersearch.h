#pragma once

#include <QWidget>
#include <QScopedPointer>

namespace Ui { class CompilerSearch; }

class CompilerSearch : public QWidget
{
    Q_OBJECT

public:
    explicit CompilerSearch(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent* event) override;

private:
    QScopedPointer<Ui::CompilerSearch> ui;
    int lastChoice = 0;
    QString m_path;
    QString m_type;
    QString m_year;
};