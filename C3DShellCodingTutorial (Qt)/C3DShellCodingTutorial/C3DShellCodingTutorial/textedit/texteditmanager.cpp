#include <functional>

#include <QToolButton>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QEvent>
#include <QApplication>
#include <QDomDocument>
#include <QSettings>
#include <QDomElement>
#include <QDate>
//ads
#include <DockManager.h>
#include <DockWidget.h>
#include <DockAreaWidget.h>
#include <DockAreaTitleBar.h>
#include <DockAreaTabBar.h>
#include <FloatingDockContainer.h>
#include <DockComponentsFactory.h>

#include "storagelocation.h"
#include "texteditmanager.h"
#include "texteditwidget.h"
#include "findtextwidget.h"
#include "texteditor.h"
#include "globaldef.h"

//-----------------------------------------------------------------------------
// 
// ---
class CCustomComponentsFactory : public ads::CDockComponentsFactory
{
public:
    using DockFactory = ads::CDockComponentsFactory;
    ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* DockArea) const override
    {

        auto TitleBar = new ads::CDockAreaTitleBar(DockArea);
        auto CustomButton = new QToolButton(DockArea);
        CustomButton->setToolTip(QObject::tr("Help"));
        CustomButton->setIcon(svgIcon(QStringLiteral(":/res/icons/editor.svg")));
        CustomButton->setAutoRaise(true);
        int Index = TitleBar->indexOf(TitleBar->button(ads::TitleBarButtonTabsMenu));
        TitleBar->insertWidget(Index + 1, CustomButton);
        return TitleBar;
    }
};
//-----------------------------------------------------------------------------
// 
// ---
TextEditManager::TextEditManager(QObject* parent, ads::CDockManager* dockManager)
    : QObject(parent)
    , m_pDockManager(dockManager)
    , m_pFindTextWidget(new FindTextWidget(nullptr))
    , m_pButtonDisplay (new QPushButton(QObject::tr("Display"), nullptr))
//    , m_currentAppExecutablePath(QApplication::applicationDirPath())
//    , m_listWorks()
{
    m_pButtonDisplay->setStyleSheet("border: 4px solid green;");
    m_pButtonDisplay->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_pButtonDisplay->setFixedHeight(52);

    connect(m_pButtonDisplay, &QPushButton::clicked, this, &TextEditManager::slotDisplayCode);

    connect(m_pFindTextWidget, &FindTextWidget::clickForFind, this, &TextEditManager::slotFind);
    connect(m_pFindTextWidget, &FindTextWidget::clickForReplace, this, &TextEditManager::slotReplace);
    connect(m_pFindTextWidget, &FindTextWidget::clickForReplaceAndFind, this, &TextEditManager::slotReplaceAndFind);
    connect(m_pFindTextWidget, &FindTextWidget::clickForReplaceAll, this, &TextEditManager::slotReplaceAll);

    // Добавление заголовочных файлов ядра c3d
    // в список для автодополнения
    TextEditor::getIncludes();
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotNewEditorByFilePath(const QString& filePath)
{
    emit actionsEnabled(false);

    auto path = (filePath.isEmpty() ? QString(":/res/texts/untitle.cpp") : filePath);

    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(nullptr, tr("Application"),
            tr("Cannot read file %1:\n%2.")
            .arg(path)
            .arg(file.errorString()));
        return;
    }
    QTextStream in(&file);

    if (path == filePath)
    {
        m_pActiveTextEdit = createNewEditor(strippedName(file), in.readAll());
        m_pActiveTextEdit->setSaved(true);
        m_pActiveTextEdit->setFilePath(filePath);
    }
    else
    {
        m_pActiveTextEdit = createNewEditor(strippedName(file), "");
        m_pActiveTextEdit->setSaved(false);
        m_pActiveTextEdit->setText(in.readAll());
    }
    emit actionsEnabled(true);
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotNewEditorBySource(const QString& source)
{
    emit actionsEnabled(false);
    m_pActiveTextEdit = createNewEditor("untitle", "");
    m_pActiveTextEdit->setSaved(false);
    m_pActiveTextEdit->setText(source);
    emit actionsEnabled(true);
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotCurrentEditorBySource(const QString& source)
{
    emit actionsEnabled(false);
    if (m_pActiveTextEdit == nullptr)
    {
        slotNewEditorBySource(source);
    }
    else
    {
        m_pActiveTextEdit->slotClear();
        m_pActiveTextEdit->setText(source);
    }
    emit actionsEnabled(true);
}
//-----------------------------------------------------------------------------
// 
// ---
bool TextEditManager::readyToClosed(TextEditWidget* editorWidget)
{
    auto result = QMessageBox::No;

    if (!editorWidget->isSaved())
    {
        result = QMessageBox::question(qobject_cast<QWidget*>(parent()),
            tr("Close Editor"), QString(tr("Editor %1  contains unsaved changes?\nWould you like to close it?")).arg(editorWidget->dockTitle())
            /*,
            QMessageBox::StandardButton::Save | 
            QMessageBox::StandardButton::SaveAll | 
            QMessageBox::StandardButton::Yes | 
            QMessageBox::StandardButton::YesToAll | 
            QMessageBox::StandardButton::No | 
            QMessageBox::StandardButton::NoToAll*/
        );
    }
    else
    {
        result = QMessageBox::Yes;
    }
    return result == QMessageBox::Yes;
}
//-----------------------------------------------------------------------------
// 
// ---
TextEditWidget* TextEditManager::createNewEditor(const QString& title, const QString& source)
{
    ads::CDockWidget* dockWidget = nullptr;
    QString name;
    QStringList statesList;
    bool haveState = false;
    if (0 == m_textEditCount && APP.isSavedCommonSettings("textName")/* && (APP.isRun == false)*/)
    {
        name = APP.restoreCommonSettings("textName").toString();
        statesList = m_pDockManager->perspectiveNames();
        haveState = statesList.contains(name);
    }
    else
    {
        name = QString("editor\"%1\"").arg(QDate::currentDate().toString("yy/M/dd") + "/" + QTime::currentTime().toString("hh:mm:ss.zzz") + title);
    }

    dockWidget = new ads::CDockWidget(name);

    auto editor = new TextEditWidget();
    editor->setText(source);
    editor->setDock(dockWidget);

    dockWidget->setWidget(editor);
    dockWidget->setWindowTitle(title);
    dockWidget->setIcon(svgIcon(QStringLiteral(":/res/icons/editor/editor.svg")));
    dockWidget->setFeature(ads::CDockWidget::CustomCloseHandling, true);
    dockWidget->setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);

    QMenu* optionsMenu = new QMenu(dockWidget);
    optionsMenu->setTitle(QObject::tr("Options"));
    optionsMenu->setToolTip(optionsMenu->title());
    optionsMenu->setIcon(svgIcon(QStringLiteral(":/res/icons/editor/settings.svg")));
    auto menuAction = optionsMenu->menuAction();
    
    auto actionClear = optionsMenu->addAction(QObject::tr("Clear Editor"));
    auto actionCloseEditors = optionsMenu->addAction(QObject::tr("Close all Editors"));
    auto actionCreateEditor = new QAction(dockWidget);
    actionCreateEditor->setToolTip(QObject::tr("Create Editor"));
    actionCreateEditor->setText(tr("Add"));
    actionCreateEditor->setIcon(svgIcon(QStringLiteral(":/res/icons/editor/newplus.svg")));
    
    dockWidget->setTitleBarActions({ actionCreateEditor, menuAction });



    auto activeDock = oneDock();

    if (activeDock == nullptr)
    {
        m_pDockManager->addDockWidget(ads::LeftDockWidgetArea, dockWidget);
    }
    else
    {
        auto area = activeDock->dockAreaWidget();
        m_pDockManager->addDockWidgetTabToArea(dockWidget, area);
    }

    if (0 == m_textEditCount && haveState)
    {
        if (APP.isRun() == false)
        {
            m_pDockManager->openPerspective(name);
        }
        else
        {
            auto a = dockWidget->dockAreaWidget();
            auto per = qobject_cast<QMainWindow*>(parent());
            if (per != nullptr)
            {
                a->resize({ per->width(), per->height()});
            }
        }
        m_pDockManager->removePerspectives(statesList);
    }

    ++m_textEditCount;

    connect(editor, &TextEditWidget::signalPress,
        this, &TextEditManager::slotPress);
    connect(editor, &TextEditWidget::signalEnter,
        this, &TextEditManager::slotEnter);
    // Поиск слова в документации из редактора кода F1
    connect(editor, &TextEditWidget::signalSearchInDocumentation,
        [this](const QString textDoc) { emit signalSearchInDocumentation(textDoc); });
    connect(editor, &TextEditWidget::signalTextChanged,
        this, &TextEditManager::slotTextIsChanged);

    connect(dockWidget, &ads::CDockWidget::closeRequested,
        this, &TextEditManager::slotEditorCloseRequested);
    connect(dockWidget, &ads::CDockWidget::viewToggled,
        this, &TextEditManager::slotViewToggled);
    connect(dockWidget, &ads::CDockWidget::visibilityChanged,
        this, &TextEditManager::slotViewVisibilityChanged);

    connect(actionClear, &QAction::triggered, editor,
        &TextEditWidget::slotClear);
    connect(actionCreateEditor, &QAction::triggered,
        [this]() { slotNewEditorByFilePath(""); });
    connect(actionCloseEditors, &QAction::triggered,
        [this]() { closeAllEditors(); });

    connect(this, &TextEditManager::actionsEnabled,
        menuAction, &QAction::setEnabled);
    connect(this, &TextEditManager::actionsEnabled,
        actionCreateEditor, &QAction::setEnabled);

    dockWidget->toggleView(true);
    return editor;
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotDisplayCode()
{
    QPushButton* displayButton = qobject_cast<QPushButton*>(sender());
    Q_ASSERT(displayButton != nullptr);

    QObject* buttonParent = displayButton->parent();
    Q_ASSERT(buttonParent != nullptr);

    TextEditWidget* activeTextEdit = qobject_cast<TextEditWidget*>(buttonParent);
    Q_ASSERT(activeTextEdit != nullptr);

    m_pActiveTextEdit = activeTextEdit;
    emit sendCode(m_pActiveTextEdit->text(), activeTextEdit->dockObjectName());
    m_pActiveTextEdit->unselectErrors();
}
//-----------------------------------------------------------------------------
 
// Вызов формы поиска и замены слов
void TextEditManager::slotShowFindWidget()
{
    // Если редактор кода закрыт, окно поиска не откроется
    if (m_pActiveTextEdit == nullptr) return;

    // Добавление формы поиска в активную вкладку
    m_pActiveTextEdit->setFindWidget(m_pFindTextWidget);

    // Открытие и закрытие формы поиска
    (!m_pFindTextWidget->isVisible()) ? m_pFindTextWidget->show() : m_pFindTextWidget->hide();  
}
//-----------------------------------------------------------------------------

// ---
void TextEditManager::slotEnter()
{
    m_pButtonDisplay->hide();

    auto widget = qobject_cast<TextEditWidget*>(sender());
    if (!widget) return;

    widget->setButtonDisplay(m_pButtonDisplay);
    m_pButtonDisplay->show();
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotPress()
{
    auto widget = qobject_cast<TextEditWidget*>(sender());
    if (!widget) return;
    m_pActiveTextEdit = widget;
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::enableButtonDisplay()
{
    m_pButtonDisplay->setEnabled(true);
    m_pButtonDisplay->setStyleSheet("border: 4px solid green;");
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::disableButtonDisplay()
{
    m_pButtonDisplay->setDisabled(true);
    m_pButtonDisplay->setStyleSheet("border: 1px solid gray;");

}
//-----------------------------------------------------------------------------
// 
// ---
bool TextEditManager::event(QEvent* event)
{
    if (event->type() == QEvent::Close)
    {
        if (m_pFindTextWidget != nullptr)
        {
            m_pFindTextWidget->setParent(nullptr);
            delete m_pFindTextWidget;
        }

        if (m_pButtonDisplay != nullptr)
        {
            m_pButtonDisplay->setParent(nullptr);
            delete m_pButtonDisplay;
        }
    }
    return QObject::event(event);
}
//-----------------------------------------------------------------------------
// 
// ---
QString TextEditManager::strippedName(const QFile& filePath)
{
    return QFileInfo(filePath).baseName();
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::getFindAndButton(TextEditWidget* editor)
{
    if (editor->findWidget())
    {
        auto findWidget = editor->findWidget();

        findWidget->hide();
        m_pFindTextWidget = findWidget;
        m_pFindTextWidget->setParent(nullptr);
    }
    if (editor->buttonDisplay())
    {
        auto buttonDisplay = editor->buttonDisplay();

        buttonDisplay->hide();
        m_pButtonDisplay = buttonDisplay;
        m_pButtonDisplay->setParent(nullptr);
    }
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotEditorCloseRequested()
{
    auto dockWidget = qobject_cast<ads::CDockWidget*>(sender());
    auto editorWidget = qobject_cast<TextEditWidget*>(dockWidget->widget());

    if (editorWidget == m_pActiveTextEdit)
    {
        m_pActiveTextEdit = nullptr;
    }

    if (readyToClosed(editorWidget))
    {
        getFindAndButton(editorWidget);
        if (m_pActiveDock == dockWidget)
        {
            m_pActiveDock = nullptr;
        }
        if (m_textEditCount == 1)
        {
            auto name = dockWidget->objectName();
            APP.saveCommonSettings("textName", name);
            m_pDockManager->addPerspective(name);
        }

        dockWidget->closeDockWidget();
        --m_textEditCount;
    }
}
//-----------------------------------------------------------------------------
// 
// ---
TextEditWidget* TextEditManager::activeTextEdit()
{
    return m_pActiveTextEdit;
}
//-----------------------------------------------------------------------------
// 
// ---
ads::CDockWidget* TextEditManager::oneDock()
{
    if (!m_pActiveDock)
    {
        auto docks = m_pDockManager->dockWidgetsMap();
        for (auto dock : docks)
        {
            auto name = dock->objectName();
            if (name.startsWith("editor"))
            {
                m_pActiveDock = dock;
                break;
            }
        }
    }
    return m_pActiveDock;
}
//-----------------------------------------------------------------------------
// 
// ---
bool TextEditManager::closeAllEditors()
{
    bool isReady = true;
    auto docks = m_pDockManager->dockWidgetsMap();
    if (!docks.isEmpty())
  {
        for (auto dock : docks)
        {
            auto name = dock->objectName();
            if (name.startsWith("editor"))
            {
                auto editorWidget = qobject_cast<TextEditWidget*>(dock->widget());
                if (readyToClosed(editorWidget))
                {
                    getFindAndButton(editorWidget);
                    if (m_pActiveDock == dock)
                    {
                        m_pActiveDock = nullptr;
                    }
                    if (m_textEditCount == 1)
                    {
                        auto name = dock->objectName();
                        APP.saveCommonSettings("textName", name);
                        m_pDockManager->addPerspective(name);
                    }
                    dock->closeDockWidget();
                    --m_textEditCount;
                }
                else
                {
                    isReady = false;
                    dock->toggleView(true);
                }
            }
        }
    }
   
    m_pActiveTextEdit = nullptr;
    return isReady;
}
void TextEditManager::textEditorsToggleView(bool open)
{
    auto docks = m_pDockManager->dockWidgetsMap();
    for (auto dock : docks)
    {
        auto name = dock->objectName();
        if (name.startsWith("editor"))
        {
            dock->toggleView(open);
        }
    }
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::toggleView(bool open)
{
    auto dock = oneDock();
    if (dock)
    {
        dock->toggleView(open);
    }
}
//-----------------------------------------------------------------------------
// 
// Отмечается, если файл изменился
void TextEditManager::slotTextIsChanged()
{
	// Текущая вкладка редактора кода
    auto editorWidget = qobject_cast<TextEditWidget*>(sender());

    // Получение названия текущей вкладки
    QString titleName = editorWidget->dockTitle();

    if (editorWidget->isModified())
    {
		// Если название не имеет *, то он добавляется
        if (!titleName.endsWith("*"))
        {
            titleName = editorWidget->dockTitle() + "*";
            editorWidget->setDockTitle(titleName);
        }
    }
}
//-----------------------------------------------------------------------------
// 
// Поиск слова
void TextEditManager::slotFind(const QString& findLine, bool wholeWord, bool caseSensitive,
    bool wrapAround, bool regexp, bool searchDirection)
{
    m_pActiveTextEdit->find(findLine, wholeWord, caseSensitive, wrapAround, regexp, searchDirection);
}
//-----------------------------------------------------------------------------

// Замена слова
void TextEditManager::slotReplace(const QString& findLine, const QString& replaceLine,
    bool wholeWord, bool caseSensitive, bool regexp)
{
    m_pActiveTextEdit->replace(findLine, replaceLine, wholeWord, caseSensitive, regexp);
}
//-----------------------------------------------------------------------------

// Замена и поиск далее
void TextEditManager::slotReplaceAndFind(const QString& findLine, const QString& replaceLine,
    bool wholeWord, bool caseSensitive, bool regexp)
{
    m_pActiveTextEdit->replaceAndFind(findLine, replaceLine, wholeWord, caseSensitive, regexp);
}
//-----------------------------------------------------------------------------

// Замена всех слов
void TextEditManager::slotReplaceAll(const QString& findLine, const QString& replaceLine,
    bool wholeWord, bool caseSensitive, bool regexp)
{
    m_pActiveTextEdit->replaceAll(findLine, replaceLine, wholeWord, caseSensitive, regexp);
}
//-----------------------------------------------------------------------------

// Сохранить как
bool TextEditManager::saveAs()
{
    if (m_pActiveTextEdit != nullptr)
    {
		// Удаление символа * в названии вкладки
        auto title = m_pActiveTextEdit->dockTitle();
        title.remove("*");

        // Сохранение (создание) файла
        QString filePath = QFileDialog::getSaveFileName(m_pDockManager,
            tr("Save file"),
            QString("%1/%2").arg(APP.workDir()).arg(title),
            ("*.cpp *.cxx, *.cc, *.c"));

        if (filePath.isEmpty())
            return false;
        // Запись текста в файл
        bool isOk = saveFile(filePath, m_pActiveTextEdit->text());
        if (isOk)
        {
			// Информация о файле
            QFileInfo fileInfo(filePath);
            
			// Установить название файла для вкладки
            m_pActiveTextEdit->setDockTitle(fileInfo.baseName());
			// Установить путь к файлу
            m_pActiveTextEdit->setFilePath(filePath);
            m_pActiveTextEdit->setSaved(true);
            
			// Добавление файлов для запуска из стартового окна,
			// если файлы сохранены не в папке workFolder
            QString path;
            if (fileInfo.absolutePath() != APP.workDir())
            {
                path = fileInfo.absoluteFilePath();
            }
            APP.writeToWorkFolder(fileInfo.baseName(), path, fileInfo.fileName());
        }
    }
}
//-----------------------------------------------------------------------------
// 
// Сохранить
bool TextEditManager::save()
{
    if (m_pActiveTextEdit != nullptr)
    {
		// Есть ли откртая вкладка
        if (!m_pActiveTextEdit->isSaved())
        {
			// Сохранен ли файл ( в тексте есть изменения)
            if (m_pActiveTextEdit->filePath().isEmpty())
            {
				// Если файла ещё нет
                if (saveAs())
                {
					// Вызывается сохранить как
                    m_pActiveTextEdit->setSaved(true);
                    return true;
                }
            }
			// Если файл уже есть
            else
            {
				// Путь к файлу
                auto filePath = m_pActiveTextEdit->filePath();
                if (!filePath.isEmpty())
                {
					// Путь к файлу
                    if (saveFile(filePath, m_pActiveTextEdit->text()))
                    {
						// Изменение названия вкладки
                        auto title = m_pActiveTextEdit->dockTitle();
                        title.remove("*");
                        m_pActiveTextEdit->setDockTitle(title);
                        m_pActiveTextEdit->setSaved(true);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
//-----------------------------------------------------------------------------
// 
// Запись текста в файл
bool TextEditManager::saveFile(const QString& filePath, const QString& source)
{
	// Файл для записи
    QFile file(filePath);
	// Сообщение предупреждение, если в файл невозможно записать
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(m_pDockManager, tr("Application"),
            tr("Cannot write file %1:\n%2.")
            .arg(file.fileName())
            .arg(file.errorString()));
        return false;
    }
    // Поток для записи в файл
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
	// Запись в файл
    out << source;
    QApplication::restoreOverrideCursor();

    return true;
}
//-----------------------------------------------------------------------------
// 
// Открыть файлы
bool TextEditManager::openFiles()
{
	// Названия файлов
    QStringList files = QFileDialog::getOpenFileNames(m_pDockManager,
        tr("Select one or more files to open"),
        APP.workDir(),
        ("*.cpp *.cxx, *.cc, *.c"));

    if (files.empty())
    {
        return false;
    }

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

    // Создание файлов
    for (QString& filePath : files)
    {
        slotNewEditorByFilePath(filePath);
    }

    QApplication::restoreOverrideCursor();

    return true;
}

void TextEditManager::slotMoveToError(const QString& textEditName, int line, const QString& message)
{
    auto docks = m_pDockManager->dockWidgetsMap();
    for (auto dock : docks)
    {
        if (textEditName == dock->objectName())
        {
            auto textEdit = qobject_cast<TextEditWidget*>(dock->widget());
            if (textEdit != nullptr)
            {
                textEdit->moveToError(line, message);
            }
            break;
        }
    }
}

void TextEditManager::slotErrorsList(const QString& textEditName, QVector<QPair<int, QString>>& errorsList)
{
    auto docks = m_pDockManager->dockWidgetsMap();
    for (auto dock : docks)
    {
        if (textEditName == dock->objectName())
        {
            auto textEdit = qobject_cast<TextEditWidget*>(dock->widget());
            if (textEdit != nullptr)
            {
                textEdit->errorsList(errorsList);
            }
            break;
        }
    }
}
//-----------------------------------------------------------------------------
// 
// ---
void TextEditManager::slotViewToggled(bool Open)
{
    auto dockWidget = qobject_cast<ads::CDockWidget*>(sender());
    if (!dockWidget) return;

    //qDebug() << dockWidget->objectName() << " viewToggled(" << Open << ")";
}
//============================================================================
void TextEditManager::slotViewVisibilityChanged(bool Visible)
{
    auto dockWidget = qobject_cast<ads::CDockWidget*>(sender());
    if (!dockWidget) return;
    //qDebug() << dockWidget->objectName() << " visibilityChanged(" << Visible << ")";
}
//============================================================================

//void TextEditManager::customEvent(QEvent* event)
//{
//   if (event->type() == QEvent::LanguageChange) {
//       tr("Application");
//       tr("Cannot write file %1:\n%2.");
//       m_pButtonDisplay->setText(QObject::tr("Display"));
//       QObject::tr("Display");
//       tr("Close Editor");
//       QString(tr("Editor %1  contains unsaved changes?\n"
//           "Would you like to close it?"));
//       tr("Add");
//       tr("Save file");
//       tr("Cannot write file %1:\n%2.");
//       tr("Select one or more files to open");
//   }
//   QObject::customEvent(event);
//   
//}

