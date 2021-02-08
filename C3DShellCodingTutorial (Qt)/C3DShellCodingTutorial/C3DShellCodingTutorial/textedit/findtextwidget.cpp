#include "findtextwidget.h"
#include "ui_findtextwidget.h"
#include <QtMath>
#include <QDebug>

FindTextWidget::FindTextWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FindTextWidget)
    , searchDirection(false)
{
    ui->setupUi(this);

    //Поиск
    connect(ui->buttonFindNext, &QPushButton::clicked, this, &FindTextWidget::slotFindText);
    connect(ui->buttonFindPrevious, &QPushButton::clicked, this, &FindTextWidget::slotFindText);

    //Замена
    connect(ui->buttonReplace, &QPushButton::clicked, [this]()
    {
        emit clickForReplace(ui->lineEditTextForFind->text(), ui->lineEditTextForReplace->text(),
                             ui->checkBoxWholeWords->isChecked(), ui->checkBoxCaseSensitive->isChecked(),
                             ui->checkBoxRegularExpressions->isChecked());
    });
    connect(ui->buttonReplaceAndFind, &QPushButton::clicked, [this]()
    {
        emit clickForReplaceAndFind(ui->lineEditTextForFind->text(), ui->lineEditTextForReplace->text(),
                                    ui->checkBoxWholeWords->isChecked(), ui->checkBoxCaseSensitive->isChecked(),
                                    ui->checkBoxRegularExpressions->isChecked());
    });
    connect(ui->buttonReplaceAll, &QPushButton::clicked, [this]()
    {
        emit clickForReplaceAll(ui->lineEditTextForFind->text(), ui->lineEditTextForReplace->text(),
                                ui->checkBoxWholeWords->isChecked(), ui->checkBoxCaseSensitive->isChecked(),
                                ui->checkBoxRegularExpressions->isChecked());
    });

    // Неактивна форма замены, если поле поиска пустое
    connect(ui->lineEditTextForFind, &QLineEdit::textChanged, this, &FindTextWidget::slotCheckTextForFind);
  
    // Закрыть форму поиска
    connect(ui->buttonClose, &QPushButton::clicked, this, &QWidget::hide);
}

FindTextWidget::~FindTextWidget()
{
}

void FindTextWidget::slotFindText()
{
    if(ui->buttonFindPrevious == qobject_cast<QPushButton*>(sender()))
    {
        searchDirection = false;
    }
    if (ui->buttonFindNext == qobject_cast<QPushButton*>(sender()))
    {
        searchDirection = true;
    }
    emit clickForFind(ui->lineEditTextForFind->text(), ui->checkBoxWholeWords->isChecked(),
                      ui->checkBoxCaseSensitive->isChecked(), ui->checkBoxWrapAround->isChecked(),
                      ui->checkBoxRegularExpressions->isChecked(), searchDirection);
}

void FindTextWidget::infoSearchAndReplace(int wordCount, bool replace)
{
    // Текст не найден
    if (wordCount == -2)
    {
        ui->labelFindInfo->setText(tr("The following text wasn't found."));
        ui->labelFindInfo->setStyleSheet("color : rgb(122, 0, 0)");
        ui->labelFindInfo->setVisible(true);
    }
	// Поиск закончен
    else if (wordCount == 0 && replace == false)
    {
        ui->labelFindInfo->setText(tr("Search ended."));
        ui->labelFindInfo->setStyleSheet("color : rgb(0, 122, 0)");
        ui->labelFindInfo->setVisible(true);
    }
	// Сколько слов заменено
    else if (wordCount > 0 && replace == true)
    {
        ui->labelFindInfo->setText(QString(tr("Replace all: %1 occurrences replaced.")).arg(wordCount));
        ui->labelFindInfo->setStyleSheet("color : rgb(0, 122, 0)");
        ui->labelFindInfo->setVisible(true);
    }
	// Скрыть сообщение
    else if(wordCount == -1)
        ui->labelFindInfo->setVisible(false);
}

void FindTextWidget::slotCheckTextForFind()
{
    if (ui->lineEditTextForFind->text().isEmpty())
    {
        ui->buttonReplace->setEnabled(false);
        ui->buttonReplaceAndFind->setEnabled(false);
        ui->buttonReplaceAll->setEnabled(false);
        ui->lineEditTextForReplace->setEnabled(false);
    }
    else
    {
        ui->buttonReplace->setEnabled(true);
        ui->buttonReplaceAndFind->setEnabled(true);
        ui->buttonReplaceAll->setEnabled(true);
        ui->lineEditTextForReplace->setEnabled(true);
    }
}

void FindTextWidget::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
    QWidget::changeEvent(event);
}