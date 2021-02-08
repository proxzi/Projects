#include "tutorialpackage.h"

TutorialPackage::TutorialPackage(QObject* parent)
    : QObject(parent)
{

}

void TutorialPackage::setText(const QString& text, const QString& tutorialPath)
{
    if (text == m_source)
        return;
    m_source = text;
    m_tutorialPath = tutorialPath;
    emit setPath(tutorialPath);
    emit textChanged(m_source, tutorialPath);
}