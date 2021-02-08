#pragma once

#include <QWidget>
#include <QScopedPointer>
#include <QStyledItemDelegate>
#include <QPair>
#include <QVector>

namespace Ui { class WelcomeWidget; }

class MainWindow;

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = nullptr);

signals:
    void signalOpenFile(const QString &filepath);
    void signalOpenFiles();
    void signalShowTutorialGallery();
    void signalShowDocumentation();
    void signalShowManuals();
    void signalSwitchTheme(const QString& themeName);
    void setLanguages(int);

public slots:

protected:
    /// \ru Todo. \en ToDo. \~
    void showEvent(QShowEvent* event) override;
    void changeEvent(QEvent* event) override;

private:
    QScopedPointer<Ui::WelcomeWidget> ui;
    MainWindow* m_pMainWindow;
    /// \ru Todo. \en ToDo. \~
    void setupThemesComboBox();

    QVector<QPair<QString, QString>> m_workList = {};
    QString m_workSelected;

    class FileItemDelegate : public QStyledItemDelegate
    {
    public:
        FileItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
        {
            QSize newSize = QStyledItemDelegate::sizeHint(option, index);
            newSize.setHeight(50);
            return newSize;
        }
    };
};