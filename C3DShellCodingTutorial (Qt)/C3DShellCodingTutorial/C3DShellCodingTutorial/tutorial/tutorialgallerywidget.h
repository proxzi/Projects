#pragma once

#include <QStyledItemDelegate>
#include <QWidget>

#include "tutorialloader.h"


class TutorialGalleryWidget : public QWidget
{
    Q_OBJECT
public:
    TutorialGalleryWidget(QWidget* parent = nullptr);

    const QString& codeBlockById(const QString& id);
signals:
    void signalRunTutorial(const QString& tutorialSource, const QString& tutorialPath);
public slots:

private slots:
    void slotOnListDoubleClicked(const QModelIndex& index);
private:
    Tutorial *m_currentTutorial;
    TutorialLoader* m_loader;

    class TutorialItemDelegate : public QStyledItemDelegate
    {
    public:
        TutorialItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
        {
            QSize newSize = QStyledItemDelegate::sizeHint(option, index);
            newSize.setHeight(100);
            return newSize;
        }
    };
};