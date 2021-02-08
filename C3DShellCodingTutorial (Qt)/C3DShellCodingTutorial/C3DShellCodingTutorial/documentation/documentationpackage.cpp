#include "documentationpackage.h"

DocumentationPackage::DocumentationPackage(QObject* parent)
    : QObject(parent)
{
}

void DocumentationPackage::setText(const QString& text, const QString& hostUrl)
{
    auto classAndMethod = text.split("::");

    if (classAndMethod.size() == 2)
    {
        emit signalSearchRequest(classAndMethod[0], classAndMethod[1], hostUrl);
    }
    else if (classAndMethod.size() == 1)
    {
        emit signalSearchRequest(classAndMethod[0], QString(), hostUrl);
    }
}

void DocumentationPackage::slotSearchIsSuccess(bool success)
{
    emit signalSearchIsSuccess(success);
}

void DocumentationPackage::slotUpdateCurrentUrl(const QString& url)
{
    emit signalUpdateCurrentUrl(url);
}

